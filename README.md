# minishell ![build](https://github.com/GustavoAriadno/42-minishell/workflows/build/badge.svg) ![norminette](https://github.com/GustavoAriadno/42-minishell/workflows/norminette/badge.svg) ![test](https://github.com/GustavoAriadno/42-minishell/workflows/test/badge.svg)

> A seashell or sea shell, also known simply as a shell, is a hard, protective outer layer usually created by an animal that lives in the sea. The shell is part of the body of the animal. Empty seashells are often found washed up on beaches by beachcombers. The shells are empty because the animal has died and the soft parts have been eaten by another animal or have decomposed.

Minishell is our own implementation of a simple UNIX shell, capable of process forking, persistency of environment variables and default shell operators, such as redirects and signal handling. As part of the 42 schools curriculum, minishell requires to work in team, and for that I thank [Gustavo Ariadno](https://github.com/GustavoAriadno) for the long nights working before submitting this masterpiece. 😎

## Getting Started

To compile `minishell`, one must simply clone this repository and proceed to the compilation with `make`. It's required to have `clang` installed on your system. The libraries required will be compiled on-the-fly, as well as the binary of interest. If curious, one may run the test suite with `make test`.

```shell
git clone 
cd minishell
make
```

After the compilation is done, you may run the program by simply invoking `./minishell`, and that's all good. 🙂

### Features

This shell has a prompt! 🥳 It takes your `USER` and `HOST` environement variables to update prompt information, in a similiar fashion as it's done by `bash`.

This shell includes the following built-in functions, which don't require the spawning of a new process. Check out the [shell docs](https://pubs.opengroup.org/onlinepubs/7908799/xcu/chap2.html#tag_001_003) to take a peek on each function behavior and parameters. That's the ones:

| cd     | echo | env   | exit |
|--------|------|-------|------|
| **export** | **pwd**  | **unset** |      |

This shell let commands to be run from the system binaries, such as `ls`, `rm` and others that may be found on your `PATH` environment variable. To achieve this, `minishell` forks the new process when it identifies a command that's not in the list of built-ins.

This shell let users redirect the standard file descriptors with the symbols `<`, `>` and `>>`. This way, one may read the contents of a file into another binary, or may write or append the output of a program into one or more files.

This shell let users pipe the process spawned by it with the `|` operator. Also, it let different pipe streams to take place by using the `;` separator.

This shell has its own environment variables. Implemented by a hash table data structure, these variables control the behavior of the shell (such as `PATH` or `USER`) or may be used by programs forked from it. Variables may be set during the execution of some binary (`VAR=value ./program`), to the extent of `./minishell` (`VAR=value`) or may be used by shells forked from a parent one `export VAR=value`. Environment variables may be deleted with `unset`.
