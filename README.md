# Jack VM Translator

This is a VM translator made as an assignment for the [Nand To Tetris Course: Part 2](https://nand2tetris.org/project07). It assumes that the VM files do not have errors for now.

## Requirements

You need a C++ compiler and `make` to develop, build, and run this project.

## Installation

1. Clone this repo:

```
git clone https://github.com/hazemKrimi/jack-vm-translator
```

2. To run this against VM files, run the following command with the path of the `.vm` file (or directory):

```
./out/vm-translator <path_to_vm_file_or_directory>
```

The result `.asm` file will be written in the same location as the source file.

## Build

- To build this project run the following command:

```
make
```

- To build for release run the following command:

```
make MODE=release
```

You will find the executable in the `out/` directory.

## Reference

This project is based on the [Nand To Tetrass Course: Part 2](https://www.nand2tetris.org/).
