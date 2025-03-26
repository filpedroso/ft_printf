# ft_printf

A 42 School project to reimplement the C standard library's `printf` function.

## Overview

`ft_printf` is a custom implementation of the `printf` function, handling formatted output with various specifiers like `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, and `%p`, and the flags '0', '.' and '-'.

## Installation and Compilation

To use `ft_printf` in your project, compile it into a static library:

```sh
make
```

This will generate `compiled_ft_printf.a`, which can be linked with other programs.

## Usage

To use `ft_printf` in a program, include the header and link the library:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s!\n", "world");
    return 0;
}
```

Compile with:

```sh
gcc main.c compiled_ft_printf.a
```

## Testing

### Manual Testing

Run:
```bash
make test
./test
```

## Cleaning Up

To remove compiled files:

```sh
make clean  # Removes object files  
make fclean # Removes object files and the library  
```

To recompile from scratch:

```sh
make re
```

