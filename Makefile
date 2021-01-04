# This Makefile has improved a lot from the tips given by Lunderberg.
# While his main focus was to build projects with C++, we could take
# a lot of great ideas to use here as well. Check out his work on
# http://www.lunderberg.com/2015/08/24/cpp-makefile-multiple-libraries/

NAME = minishell

# Default build variables, can be overridden by command line options.

CC			=	clang
CPPFLAGS	=
CFLAGS		=	-g
LDFLAGS		=
LDLIBS		=
RM			=	rm -f
BUILD		=	default

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
.PHONY: all clean fclean re force test shell

# Find the source files that will be used.
SRC_FILES = $(wildcard src/*.c)
O_FILES = $(patsubst %.c,build/$(BUILD)/build/%.o,$(SRC_FILES))

# Allow build and link of multiple libraries
LIBRARY_FOLDERS = libft libhash
LIBRARY_INCLUDES = $(patsubst %,-I%/include,$(LIBRARY_FOLDERS))
override CPPFLAGS += $(LIBRARY_INCLUDES)
LIBRARY_FLAGS = $(patsubst lib%,-l%,$(LIBRARY_FOLDERS))
override LDLIBS += $(LIBRARY_FLAGS)
library_src_files = $(wildcard lib$(1)/src/*.c)
library_o_files   = $(patsubst %.c,build/$(BUILD)/build/%.o,$(call library_src_files,$(1)))
STATIC_LIBRARY_OUTPUT = $(patsubst %,lib/%.a,$(LIBRARY_FOLDERS))

all: $(NAME)

override CPPFLAGS += -MMD
-include $(shell find build -name "*.d" 2> /dev/null)

ifneq ($(BUILD),default)
    include build-targets/$(BUILD).inc
endif

.build-target: force
	echo $(BUILD) | cmp -s - $@ || echo $(BUILD) > $@

$(NAME): build/$(BUILD)/bin/$(NAME) .build-target $(STATIC_LIBRARY_OUTPUT)
	mkdir -p $(@D)
	cp -f $< $@

lib/%: build/$(BUILD)/lib/% .build-target
	mkdir -p $(@D)
	cp -f $< $@

build/$(BUILD)/bin/%: $(O_FILES) $(STATIC_LIBRARY_OUTPUT)
	mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

build/$(BUILD)/build/%.o: %.c
	mkdir -p $(@D)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(foreach lib,$(LIBRARY_FOLDERS),$(eval $(call library_variables,$(lib))))

build/$(BUILD)/lib/lib%.a: $$(call library_o_files,%)
	mkdir -p $(@D)
	$(AR) rcs $@ $^

clean:
	$(RM) -r bin build lib .build-target

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

test: $(NAME)

shell: $(NAME)
	./$(NAME)
