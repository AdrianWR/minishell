# This Makefile has improved a lot from the tips given by Lunderberg.
# While his main focus was to build projects with C++, we could take
# a lot of great ideas to use here as well. Check out his work on
# http://www.lunderberg.com/2015/08/24/cpp-makefile-multiple-libraries/

NAME = minishell

# Default build variables, can be overridden by command line options.

CC			=	clang
CPPFLAGS	=
CFLAGS		=	-g -O3
LDFLAGS		=
LDLIBS		=
RM			=	rm -f
BUILD		=	default

BUILD_SHARED = 0
BUILD_STATIC = 1

ifneq ($(BUILD),default)
    include build-targets/$(BUILD).inc
endif

# Additional flags that are necessary to compile.
# Even if not specified on the command line, these should be present.

override CPPFLAGS	+= -Iinclude
override CFLAGS		+= -Wall -Wextra -Werror
override LDFLAGS	+= -Llib -Wl,-rpath,\$$ORIGIN/../lib -Wl,--no-as-needed
override LDLIBS	+=

#vpath %.c src

.SECONDARY:
.SECONDEXPANSION:
.PHONY: all clean fclean re force

# Find the source files that will be used.
#EXEC_SRC_FILES = $(wildcard *.c)
#EXECUTABLES = $(patsubst %.c,%,$(EXEC_SRC_FILES))
SRC_FILES = $(wildcard src/*.c)
O_FILES = $(patsubst %.c,build/$(BUILD)/build/%.o,$(SRC_FILES))

# Allow build and link of multiple libraries
LIBRARY_FOLDERS = $(wildcard lib?*)
LIBRARY_INCLUDES = $(patsubst %,-I%/include,$(LIBRARY_FOLDERS))
override CPPFLAGS += $(LIBRARY_INCLUDES)
LIBRARY_FLAGS = $(patsubst lib%,-l%,$(LIBRARY_FOLDERS))
override LDLIBS += $(LIBRARY_FLAGS)
library_src_files = $(wildcard lib$(1)/src/*.c)
library_o_files   = $(patsubst %.c,build/$(BUILD)/build/%.o,$(call library_src_files,$(1)))
library_os_files  = $(addsuffix s,$(call library_o_files,$(1)))

ifneq ($(BUILD_SHARED),0)
    SHARED_LIBRARY_OUTPUT = $(patsubst %,lib/%.so,$(LIBRARY_FOLDERS))
endif

ifneq ($(BUILD_STATIC),0)
    STATIC_LIBRARY_OUTPUT = $(patsubst %,lib/%.a,$(LIBRARY_FOLDERS))
endif

all: $(SHARED_LIBRARY_OUTPUT) $(STATIC_LIBRARY_OUTPUT) $(NAME)

override CPPFLAGS += -MMD
-include $(shell find build -name "*.d" 2> /dev/null)

ifneq ($(BUILD),default)
    include build-targets/$(BUILD).inc
endif

.build-target: force
	@echo $(BUILD) | cmp -s - $@ || echo $(BUILD) > $@

$(NAME): build/$(BUILD)/bin/$(NAME) .build-target
	mkdir -p $(@D)
	cp -f $< $@

lib/%: build/$(BUILD)/lib/% .build-target
	mkdir -p $(@D)
	cp -f $< $@

ifeq ($(shell test $(BUILD_SHARED) -gt $(BUILD_STATIC); echo $$?),0)
build/$(BUILD)/bin/%: $(O_FILES) | $(SHARED_LIBRARY_OUTPUT)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
else
build/$(BUILD)/bin/%: $(O_FILES) $(STATIC_LIBRARY_OUTPUT)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
endif

#build/$(BUILD)/bin/%: build/$(BUILD)/build/%.o $(O_FILES) | $(LIBRARY_OUTPUT)
#	mkdir -p $(@D)
#	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

build/$(BUILD)/build/%.os: %.c
	mkdir -p $(@D)
	$(CC) -c -fPIC $(CPPFLAGS) $(CFLAGS) $< -o $@

build/$(BUILD)/build/%.o: %.c
	mkdir -p $(@D)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@


define library_variables
CPPFLAGS_EXTRA =
CXXFLAGS_EXTRA =
LDFLAGS_EXTRA  =
SHARED_LDLIBS  =
-include $(1)/Makefile.inc
build/$(1)/%.o: override CPPFLAGS := $$(CPPFLAGS) $$(CPPFLAGS_EXTRA)
build/$(1)/%.o: override CFLAGS := $$(CFLAGS) $$(CXXFLAGS_EXTRA)
lib/$(1).so:  override LDFLAGS  := $$(LDFLAGS)  $$(LDFLAGS_EXTRA)
lib/$(1).so:  override LDLIBS := $$(LDLIBS)
endef

$(foreach lib,$(LIBRARY_FOLDERS),$(eval $(call library_variables,$(lib))))

build/$(BUILD)/lib/lib%.a: $$(call library_o_files,%)
	mkdir -p $(@D)
	$(AR) rcs $@ $^

build/$(BUILD)/lib/lib%.so: $$(call library_os_files,%)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -shared $(SHARED_LDLIBS) -o $@


clean:
	$(RM) -r bin build lib .build-target

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

test: $(NAME)
	./$(NAME)
