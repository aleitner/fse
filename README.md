# Fallout Save Editor (FSE)

A command-line tool for reading and editing savegame files for Fallout 1.

## Overview

FSE reads and modifies `SAVE.DAT` files, which contain player stats, inventory, and world state. Town-specific data is stored in separate `.SAV` files (not currently supported).

## Installation

```sh
git clone https://github.com/aleitner/fse
cd fallout-save-editor
make install
```

## Usage

```sh
# View save header (quick overview)
fallout_save_editor SAVE.DAT

# View player status (HP, rads, poison, location)
fallout_save_editor SAVE.DAT player

# View stats and skills
fallout_save_editor SAVE.DAT stats

# View inventory
fallout_save_editor SAVE.DAT inventory

# View everything
fallout_save_editor SAVE.DAT all

# Edit a stat
fallout_save_editor SAVE.DAT set <stat> <value>

# List editable stats
fallout_save_editor --list
```

### Examples

```sh
# Clear radiation (useful after The Glow)
fallout_save_editor ~/SLOT01/SAVE.DAT set radiation_level 0

# Max out small guns
fallout_save_editor ~/SLOT01/SAVE.DAT set small_guns 200

# Rename your character
fallout_save_editor ~/SLOT01/SAVE.DAT set player_name "Mad Max"

# Check current HP and status
fallout_save_editor ~/SLOT01/SAVE.DAT player
```

### Editable Stats

**Save Info:** `player_name`, `savegame_name`, `current_map_filename`

**Player Status:** `hitpoints`, `radiation_level`, `poison_level`, `crippled_body_parts`

**Base Attributes:** `base_strength`, `base_perception`, `base_endurance`, `base_charisma`, `base_intelligence`, `base_agility`, `base_luck`

**Derived Stats:** `base_hitpoints`, `base_action_points`, `base_armor_class`, `base_melee_damage`, `base_carry_weight`, `base_sequence`, `base_healing_rate`, `base_critical_chance`, `base_damage_threshold_normal`, `base_damage_resistance_normal`, `base_radiation_resistance`, `base_poison_resistance`

**Bonus Stats:** `bonus_to_strength`, `bonus_to_perception`, `bonus_to_endurance`, `bonus_to_charisma`, `bonus_to_intelligence`, `bonus_to_agility`, `bonus_to_luck`, `bonus_to_maximum_hit_points`, `bonus_to_action_points`, `bonus_AC`, `bonus_melee_damage`, `bonus_carry_weight`, `bonus_critical_chance`

**Skills:** `small_guns`, `big_guns`, `energy_weapons`, `unarmed`, `melee_weapons`, `throwing`, `first_aid`, `doctor`, `sneak`, `lockpick`, `steal`, `traps`, `science`, `repair`, `speech`, `barter`, `gambling`, `outdoorsman`

## Build Targets

| Target | Description |
|--------|-------------|
| `all` | Build shared library and CLI |
| `library-shared` | Build shared library only |
| `cli` | Build CLI only |
| `clean` | Remove build artifacts |
| `install` | Install library, CLI, and headers |
| `uninstall` | Remove installed files |

## Library Usage

```c
#include <fse/header.h>
#include <fse/function_5.h>
#include <fse/function_6.h>
#include <fse/endian_conversion.h>

FILE *f = fopen("SAVE.DAT", "r+b");

header_t *header = load_header(f);
print_header(header);

uint32_t offset = find_function_5_offset(f);
uint32_t camera;
function_5_t *player = load_function_5(f, offset, &camera);

// Clear radiation
player->radiation_level = to_savefile_byte_order_32(0);
save_function_5(f, player, camera, offset);

free(player);
free(header);
fclose(f);
```

## File Format

Save files use big-endian byte order. The file is divided into a header followed by 27 "functions" containing different data types. See the [format documentation](https://falloutmods.fandom.com/wiki/SAVE.DAT_File_Format) for details.

## License

[MIT License](LICENSE)

## Acknowledgments

Format documentation from [Vault-Tec Labs](https://falloutmods.fandom.com/wiki/SAVE.DAT_File_Format).

## Disclaimer

Not affiliated with the developers or publishers of Fallout. Built by someone who made a bad character and didn't want to start over.
