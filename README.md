# Fallout Save Editor (FSE)

This project provides a tool for reading and potentially editing the contents of savegame files for the classic game Fallout. This tool gives you the capability to view and modify various aspects of save files, including player stats, inventory, and game world state.

## Overview

Fallout Savegame Editor (FSE) reads `.DAT` files which are archived data files containing everything about the player, party members, global variables, and state of the world map. Note that information about each town is stored in individual `.SAV` files instead of `.DAT` files.

## Installation

To install FSE, follow these steps:

1. Make sure you have the development files for GCC.
2. Clone the repository or download the source code.
3. `cd` into the root directory of the project.
4. Run `make install` to compile and install the tool.

The project contains a Makefile for easy building of the tool.

## Usage

After successfully building and installing FSE, you can use it with the following command:

```sh
fallout_save_editor <path to SAVE.DAT>
```

Replace `<path to SAVE.DAT>` with the actual path to your Fallout savegame `.DAT` file.

## Build Targets

* `all`: Build the shared library and CLI tool.
* `library-shared`: Build a shared library.
* `cli`: Build the command-line interface.
* `clean`: Remove all compiled binaries and object files.
* `install`: Install all necessary components for using the tool.
* `uninstall`: Remove all installed components of the tool.

## Contributing

Contributions are welcome!

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

I would like to give a special mention to the detailed documentation provided by [falloutmods.fandom.com](https://falloutmods.fandom.com/wiki/SAVE.DAT_File_Format) for their extensive breakdown of the `SAVE.DAT` file format, which has been invaluable to the development of this tool.


## Disclaimer

This project is in no way affiliated with the developers or publishers of Fallout. It is an independent project developed by someone made he made a bad character.