#ifndef FUNCTION_6_H
#define FUNCTION_6_H

#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
typedef struct {
    uint32_t unknown_field_0; // Not mentioned in documentation...
    uint32_t unknown_field_1;
    uint32_t tab_flags;
    uint32_t base_strength;
    uint32_t base_perception;
    uint32_t base_endurance;
    uint32_t base_charisma;
    uint32_t base_intelligence;
    uint32_t base_agility;
    uint32_t base_luck;
    uint32_t base_hitpoints;
    uint32_t base_action_points;
    uint32_t base_armor_class;
    uint32_t unknown_field_2;
    uint32_t base_melee_damage;
    uint32_t base_carry_weight;
    uint32_t base_sequence;
    uint32_t base_healing_rate;
    uint32_t base_critical_chance;
    uint32_t base_critical_hit_table_roll_modifier;
    uint32_t base_damage_threshold_normal;
    uint32_t base_damage_threshold_laser;
    uint32_t base_damage_threshold_fire;
    uint32_t base_damage_threshold_plasma;
    uint32_t base_damage_threshold_electrical;
    uint32_t base_damage_threshold_EMP;
    uint32_t base_damage_threshold_explosive;
    uint32_t base_damage_resistance_normal;
    uint32_t base_damage_resistance_laser;
    uint32_t base_damage_resistance_fire;
    uint32_t base_damage_resistance_plasma;
    uint32_t base_damage_resistance_electrical;
    uint32_t base_damage_resistance_EMP;
    uint32_t base_damage_resistance_explosive;
    uint32_t base_radiation_resistance;
    uint32_t base_poison_resistance;
    uint32_t starting_age;
    uint32_t gender;
    uint32_t bonus_to_strength;
    uint32_t bonus_to_perception;
    uint32_t bonus_to_endurance;
    uint32_t bonus_to_charisma;
    uint32_t bonus_to_intelligence;
    uint32_t bonus_to_agility;
    uint32_t bonus_to_luck;
    uint32_t bonus_to_maximum_hit_points;
    uint32_t bonus_to_action_points;
    uint32_t bonus_AC;
    uint32_t unknown_field_3;
    uint32_t bonus_melee_damage;
    uint32_t bonus_carry_weight;
    uint32_t bonus_sequence;
    uint32_t bonus_healing_rate;
    uint32_t bonus_critical_chance;
    uint32_t bonus_to_critical_hit_table_rolls;
    uint32_t bonus_to_damage_threshold_normal;
    uint32_t bonus_to_damage_threshold_laser;
    uint32_t bonus_to_damage_threshold_fire;
    uint32_t bonus_to_damage_threshold_plasma;
    uint32_t bonus_to_damage_threshold_electrical;
    uint32_t bonus_to_damage_threshold_EMP;
    uint32_t bonus_to_damage_threshold_explosive;
    uint32_t bonus_to_damage_resistance_normal;
    uint32_t bonus_to_damage_resistance_laser;
    uint32_t bonus_to_damage_resistance_fire;
    uint32_t bonus_to_damage_resistance_plasma;
    uint32_t bonus_to_damage_resistance_electrical;
    uint32_t bonus_to_damage_resistance_EMP;
    uint32_t bonus_to_damage_resistance_explosive;
    uint32_t bonus_to_radiation_resistance;
    uint32_t bonus_to_poison_resistance;
    uint32_t bonus_to_age;
    uint32_t additional_gender;
    uint32_t skills[0x12];
    uint32_t proto_id;
    uint64_t unknown_field_4;
    uint32_t description_line_number;
} function_6_t;
#pragma pack(pop)

/**
 * Loads Function 6 data from the specified file at the given offset, returning
 * a pointer to a newly allocated function_6_t structure containing the data.
 * If an error occurs during reading or allocation, NULL is returned.
 *
 * @param file
 *     The file from which to load Function 6 data.
 *
 * @param offset
 *     The offset within the file where Function 6 data begins.
 *
 * @return
 *     A pointer to the newly allocated function_6_t structure, or NULL if
 *     an error occurs.
 */
function_6_t* load_function_6(FILE *file, uint32_t offset);

/**
 * Frees the memory allocated for a function_6_t structure.
 *
 * @param func6
 *     The function_6_t structure to be freed.
 */
void free_function_6(function_6_t *func6);

/**
 * Prints the information contained within a Function 6 structure in a
 * human-readable format.
 *
 * @param func6
 *     The function_6_t structure whose contents are to be printed.
 */
void print_function_6(const function_6_t *func6);

#endif