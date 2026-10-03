# MiniJail

MiniJail is a trivial program for FreeBSD which jails a process with all default configurations, essentially a wrapper around the `jail_set` system call. I created it as a way to explore the low-level behavior of jails on FreeBSD.

The `test` executable is a static executable which just prints "Hello world", and waits for 60 seconds, allowing you to see the running jail with `jls`.

## Usage

``` sh
minijail /path/to/root/ /path/to/root/executable/under/that/root
```

## Notes

- A process must be jailed in a directory above it.
- Only the root user has permission to create a jail.
- If your jail root does not contain `/libexec/ld-elf.so.1`, then you cannot jail a dynamic executable. 

## Build and IDE setup

``` sh
mkdir build
cd build
cmake .. [-G"Ninja"] [-DCMAKE_CXX_COMPILER=clang++22] [-DCMAKE_BUILD_TYPE=Release]
cmake --build .
```

This will also generate the `compile_commands.json` file for `clangd`.


## Disclaimer

- THIS PROGRAM IS HEAVILY WIP AND ONLY INTENDED FOR LEARNING PURPOSES

## License

Licensed under the 3-clause BSD License, Copyright (c) 2026 Maki (ProfCreeptonius on Github)

