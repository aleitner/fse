#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fse/header.h"
#include "fse/function_1.h"
#include "fse/function_5.h"
#include "fse/function_6.h"
#include "fse/endian_conversion.h"

typedef enum { LOC_HEADER, LOC_FUNC5, LOC_FUNC6, LOC_SKILL } stat_location_t;
typedef enum { TYPE_INT32, TYPE_STRING } stat_type_t;

typedef struct {
    const char *name;
    stat_location_t location;
    stat_type_t type;
    size_t offset;
    size_t max_len; // for strings only
} stat_entry_t;

#define HEADER_STR(field) { #field, LOC_HEADER, TYPE_STRING, offsetof(header_t, field), sizeof(((header_t*)0)->field) }
#define FUNC5_STAT(field) { #field, LOC_FUNC5, TYPE_INT32, offsetof(function_5_t, field), 0 }
#define FUNC6_STAT(field) { #field, LOC_FUNC6, TYPE_INT32, offsetof(function_6_t, field), 0 }
#define SKILL_STAT(name, idx) { name, LOC_SKILL, TYPE_INT32, idx, 0 }

static const stat_entry_t STAT_TABLE[] = {
    // Header strings
    HEADER_STR(player_name),
    HEADER_STR(savegame_name),
    HEADER_STR(current_map_filename),

    // Function 5 stats
    FUNC5_STAT(hitpoints),
    FUNC5_STAT(radiation_level),
    FUNC5_STAT(poison_level),
    FUNC5_STAT(crippled_body_parts),

    // Function 6 base stats
    FUNC6_STAT(base_strength),
    FUNC6_STAT(base_perception),
    FUNC6_STAT(base_endurance),
    FUNC6_STAT(base_charisma),
    FUNC6_STAT(base_intelligence),
    FUNC6_STAT(base_agility),
    FUNC6_STAT(base_luck),
    FUNC6_STAT(base_hitpoints),
    FUNC6_STAT(base_action_points),
    FUNC6_STAT(base_armor_class),
    FUNC6_STAT(base_melee_damage),
    FUNC6_STAT(base_carry_weight),
    FUNC6_STAT(base_sequence),
    FUNC6_STAT(base_healing_rate),
    FUNC6_STAT(base_critical_chance),
    FUNC6_STAT(base_damage_threshold_normal),
    FUNC6_STAT(base_damage_resistance_normal),
    FUNC6_STAT(base_radiation_resistance),
    FUNC6_STAT(base_poison_resistance),

    // Function 6 bonus stats
    FUNC6_STAT(bonus_to_strength),
    FUNC6_STAT(bonus_to_perception),
    FUNC6_STAT(bonus_to_endurance),
    FUNC6_STAT(bonus_to_charisma),
    FUNC6_STAT(bonus_to_intelligence),
    FUNC6_STAT(bonus_to_agility),
    FUNC6_STAT(bonus_to_luck),
    FUNC6_STAT(bonus_to_maximum_hit_points),
    FUNC6_STAT(bonus_to_action_points),
    FUNC6_STAT(bonus_AC),
    FUNC6_STAT(bonus_melee_damage),
    FUNC6_STAT(bonus_carry_weight),
    FUNC6_STAT(bonus_critical_chance),

    // Skills (index into skills array)
    SKILL_STAT("small_guns", 0),
    SKILL_STAT("big_guns", 1),
    SKILL_STAT("energy_weapons", 2),
    SKILL_STAT("unarmed", 3),
    SKILL_STAT("melee_weapons", 4),
    SKILL_STAT("throwing", 5),
    SKILL_STAT("first_aid", 6),
    SKILL_STAT("doctor", 7),
    SKILL_STAT("sneak", 8),
    SKILL_STAT("lockpick", 9),
    SKILL_STAT("steal", 10),
    SKILL_STAT("traps", 11),
    SKILL_STAT("science", 12),
    SKILL_STAT("repair", 13),
    SKILL_STAT("speech", 14),
    SKILL_STAT("barter", 15),
    SKILL_STAT("gambling", 16),
    SKILL_STAT("outdoorsman", 17),
};

#define STAT_COUNT (sizeof(STAT_TABLE) / sizeof(STAT_TABLE[0]))

static const stat_entry_t* find_stat(const char *name) {
    for (size_t i = 0; i < STAT_COUNT; i++) {
        if (strcasecmp(STAT_TABLE[i].name, name) == 0)
            return &STAT_TABLE[i];
    }
    return NULL;
}

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  %s <SAVE.DAT>                        Show header info\n", prog);
    fprintf(stderr, "  %s <SAVE.DAT> player                 Show player status\n", prog);
    fprintf(stderr, "  %s <SAVE.DAT> stats                  Show stats and skills\n", prog);
    fprintf(stderr, "  %s <SAVE.DAT> inventory              Show inventory\n", prog);
    fprintf(stderr, "  %s <SAVE.DAT> all                    Show everything\n", prog);
    fprintf(stderr, "  %s <SAVE.DAT> set <stat> <value>     Set a stat\n", prog);
    fprintf(stderr, "  %s --list                            List editable stats\n", prog);
}

static void print_stat_list(void) {
    printf("Editable stats:\n\n");
    printf("Save Info (strings):\n");
    printf("  player_name, savegame_name, current_map_filename\n\n");
    printf("Player Status:\n");
    printf("  hitpoints, radiation_level, poison_level, crippled_body_parts\n\n");
    printf("Base Attributes:\n");
    printf("  base_strength, base_perception, base_endurance, base_charisma\n");
    printf("  base_intelligence, base_agility, base_luck\n\n");
    printf("Derived Stats:\n");
    printf("  base_hitpoints, base_action_points, base_armor_class\n");
    printf("  base_melee_damage, base_carry_weight, base_sequence\n");
    printf("  base_healing_rate, base_critical_chance\n");
    printf("  base_damage_threshold_normal, base_damage_resistance_normal\n");
    printf("  base_radiation_resistance, base_poison_resistance\n\n");
    printf("Bonus Stats:\n");
    printf("  bonus_to_strength, bonus_to_perception, bonus_to_endurance\n");
    printf("  bonus_to_charisma, bonus_to_intelligence, bonus_to_agility\n");
    printf("  bonus_to_luck, bonus_to_maximum_hit_points, bonus_to_action_points\n");
    printf("  bonus_AC, bonus_melee_damage, bonus_carry_weight, bonus_critical_chance\n\n");
    printf("Skills:\n");
    printf("  small_guns, big_guns, energy_weapons, unarmed, melee_weapons\n");
    printf("  throwing, first_aid, doctor, sneak, lockpick, steal, traps\n");
    printf("  science, repair, speech, barter, gambling, outdoorsman\n");
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--list") == 0) {
        print_stat_list();
        return EXIT_SUCCESS;
    }

    if (argc < 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *command = (argc >= 3) ? argv[2] : NULL;

    int want_header = 1;
    int want_player = 0;
    int want_stats = 0;
    int want_inventory = 0;
    int want_set = 0;

    if (command) {
        if (strcmp(command, "player") == 0) {
            want_header = 0;
            want_player = 1;
        } else if (strcmp(command, "stats") == 0) {
            want_header = 0;
            want_stats = 1;
        } else if (strcmp(command, "inventory") == 0) {
            want_header = 0;
            want_inventory = 1;
        } else if (strcmp(command, "all") == 0) {
            want_player = 1;
            want_stats = 1;
            want_inventory = 1;
        } else if (strcmp(command, "set") == 0) {
            if (argc != 5) {
                fprintf(stderr, "Usage: %s <SAVE.DAT> set <stat> <value>\n", argv[0]);
                return EXIT_FAILURE;
            }
            want_header = 0;
            want_set = 1;
        } else {
            fprintf(stderr, "Unknown command '%s'\n", command);
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    FILE *saveFile = NULL;
    header_t *header = NULL;
    function_1_t *function_1 = NULL;
    function_5_t *function_5 = NULL;
    function_6_t *function_6 = NULL;
    uint32_t function_5_offset = 0;
    uint32_t function_6_offset = 0;
    uint32_t camera;
    int return_code = EXIT_SUCCESS;

    saveFile = fopen(filename, "r+b");
    if (!saveFile) {
        fprintf(stderr, "Error opening file '%s'.\n", filename);
        return EXIT_FAILURE;
    }

    header = load_header(saveFile);
    if (!header) {
        fprintf(stderr, "Failed to load header.\n");
        return_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (want_player || want_stats || want_inventory || want_set) {
        function_1 = load_function_1(saveFile, sizeof(header_t));
        if (!function_1) {
            fprintf(stderr, "Failed to load function 1 data.\n");
            return_code = EXIT_FAILURE;
            goto cleanup;
        }

        function_5_offset = find_function_5_offset(saveFile);
        if (function_5_offset == 0) {
            fprintf(stderr, "Function 5 signature not found.\n");
            return_code = EXIT_FAILURE;
            goto cleanup;
        }

        function_5 = load_function_5(saveFile, function_5_offset, &camera);
        if (!function_5) {
            fprintf(stderr, "Failed to load function 5 data.\n");
            return_code = EXIT_FAILURE;
            goto cleanup;
        }

        size_t func5_size = get_function_5_size(function_5);
        function_6_offset = function_5_offset + func5_size;
        function_6 = load_function_6(saveFile, function_6_offset);
        if (!function_6) {
            fprintf(stderr, "Failed to load function 6 data.\n");
            return_code = EXIT_FAILURE;
            goto cleanup;
        }
    }

    if (want_set) {
        const char *stat_name = argv[3];
        const char *new_value_str = argv[4];

        const stat_entry_t *stat = find_stat(stat_name);
        if (!stat) {
            fprintf(stderr, "Unknown stat '%s'. Use --list to see available stats.\n", stat_name);
            return_code = EXIT_FAILURE;
            goto cleanup;
        }

        int need_save_header = 0, need_save_func5 = 0, need_save_func6 = 0;

        if (stat->type == TYPE_STRING) {
            char *target = NULL;

            switch (stat->location) {
                case LOC_HEADER:
                    target = (char *)header + stat->offset;
                    need_save_header = 1;
                    break;
                default:
                    fprintf(stderr, "String stat in unexpected location.\n");
                    return_code = EXIT_FAILURE;
                    goto cleanup;
            }

            printf("Changing %s: \"%.*s\" -> \"%s\"\n", stat_name, (int)stat->max_len, target, new_value_str);

            if (strlen(new_value_str) > stat->max_len)
                fprintf(stderr, "Warning: value truncated to %zu characters\n", stat->max_len);

            memset(target, 0, stat->max_len);
            strncpy(target, new_value_str, stat->max_len);

        } else {
            int32_t new_value = atoi(new_value_str);
            uint32_t *target = NULL;

            switch (stat->location) {
                case LOC_FUNC5:
                    target = (uint32_t *)((char *)function_5 + stat->offset);
                    need_save_func5 = 1;
                    break;
                case LOC_FUNC6:
                    target = (uint32_t *)((char *)function_6 + stat->offset);
                    need_save_func6 = 1;
                    break;
                case LOC_SKILL:
                    target = &function_6->skills[stat->offset];
                    need_save_func6 = 1;
                    break;
                default:
                    break;
            }

            int32_t old_value = (int32_t)from_savefile_byte_order_32(*target);
            *target = to_savefile_byte_order_32((uint32_t)new_value);

            printf("Changing %s: %d -> %d\n", stat_name, old_value, new_value);
        }

        if (need_save_header && save_header(saveFile, header, 0) != 0) {
            fprintf(stderr, "Failed to save header.\n");
            return_code = EXIT_FAILURE;
            goto cleanup;
        }
        if (need_save_func5 && save_function_5(saveFile, function_5, camera, function_5_offset) != 0) {
            fprintf(stderr, "Failed to save function 5 data.\n");
            return_code = EXIT_FAILURE;
            goto cleanup;
        }
        if (need_save_func6 && save_function_6(saveFile, function_6, function_6_offset) != 0) {
            fprintf(stderr, "Failed to save function 6 data.\n");
            return_code = EXIT_FAILURE;
            goto cleanup;
        }

        printf("Saved successfully!\n");
    } else {
        if (want_header) {
            print_header(header);
        }
        if (want_player) {
            if (want_header) printf("\n");
            print_function_5(function_5, PRINT_PLAYER);
        }
        if (want_stats) {
            if (want_header || want_player) printf("\n");
            print_function_6(function_6);
        }
        if (want_inventory) {
            if (want_header || want_player || want_stats) printf("\n");
            print_function_5(function_5, PRINT_INVENTORY);
        }
    }

cleanup:
    free(function_6);
    free(function_5);
    free(function_1);
    free(header);

    if (saveFile)
        fclose(saveFile);

    return return_code;
}