# nm_otool

Custom C implementation of nm and otool commands.

* `ft_nm <args>` displays the name list (symbol table of nlist structures) of the <args> files
* `ft_otool`  displays the content of the (__TEXT,__text) segment

This project will makes you understand how Mach-O files are structured.

## How to use
### Build

```
make
# Clean commands
make clean
make fclean
make re
```

### Usage
```
# Files supported: exec, .a, .so, .dylib, .o.
./ft_nm file
./ft_otool file
```

## Implementation

* Support for archives
* Support for fat binaries
* Support for debug symbols (`gcc -g <args>` files).
* Many flags (see ./ft_nm -h or ./ft_otool -h)
* Checks for corruption


