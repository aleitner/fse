#include "fse/function_6.h"

#include <arpa/inet.h>
#include <stdlib.h>

function_6_t* load_function_6(FILE *file, uint32_t offset) {
    if (file == NULL) {
        fprintf(stderr, "Invalid file pointer.\n");
        return NULL;
    }

    function_6_t *func1 = malloc(sizeof(function_6_t));
    if (func1 == NULL) {
        fprintf(stderr, "Memory allocation for function_6_t failed.\n");
        return NULL;
    }
    
    fseek(file, offset, SEEK_SET);
    
    size_t num_read = fread(func1, sizeof(function_6_t), 1, file);

    if (num_read != 1) {
        fprintf(stderr, "Failed to read function_6_t from file.\n");
        free(func1);
        return NULL;
    }

    return func1;
}

static void print_skills(const uint32_t skills[0x12]) {
    const char* skill_names[] = {
        "Small Guns",
        "Big Guns",
        "Energy Weapons",
        "Unarmed",
        "Melee Weapons",
        "Throwing",
        "First Aid",
        "Doctor",
        "Sneak",
        "Lockpick",
        "Steal",
        "Traps",
        "Science",
        "Repair",
        "Speech",
        "Barter",
        "Gambling",
        "Outdoorsman"
    };

    for (size_t i = 0; i < 0x12; i++) {
        printf("%s: %d\n", skill_names[i], ntohl(skills[i]));
    }
}

void print_function_6(const function_6_t *func6) {
    if (func6 == NULL) {
        printf("Function 5 data is NULL.\n");
        return;
    }

    // printf("unknown field 1: 0x%.8hx\n", ntohs(func6->unknown_field_1));
    printf("tab_flags: 0x%.8hx\n", ntohs(func6->tab_flags));
    printf("base_strength: %d\n", ntohl(func6->base_strength));
    printf("base_perception: %d\n", ntohl(func6->base_perception));
    printf("base_endurance: %d\n", ntohl(func6->base_endurance));
    printf("base_charisma: %d\n", ntohl(func6->base_charisma));
    printf("base_intelligence: %d\n", ntohl(func6->base_intelligence));
    printf("base_agility: %d\n", ntohl(func6->base_agility));
    printf("base_luck: %d\n", ntohl(func6->base_luck));
    printf("base_hitpoints: %d\n", ntohl(func6->base_hitpoints));
    printf("base_action_points: %d\n", ntohl(func6->base_action_points));
    printf("base_armor_class: %d\n", ntohl(func6->base_armor_class));
    // printf("unknown_field_2: 0x%.8hx\n", ntohl(func6->unknown_field_2));
    printf("base_melee_damage: %d\n", ntohl(func6->base_melee_damage));
    printf("base_carry_weight: %d\n", ntohl(func6->base_carry_weight));
    printf("base_sequence: %d\n", ntohl(func6->base_sequence));
    printf("base_healing_rate: %d\n", ntohl(func6->base_healing_rate));
    printf("base_critical_chance: %d\n", ntohl(func6->base_critical_chance));
    printf("base_critical_hit_table_roll_modifier: %d\n", ntohl(func6->base_critical_hit_table_roll_modifier));
    printf("base_damage_threshold_normal: %d\n", ntohl(func6->base_damage_threshold_normal));
    printf("base_damage_threshold_laser: %d\n", ntohl(func6->base_damage_threshold_laser));
    printf("base_damage_threshold_fire: %d\n", ntohl(func6->base_damage_threshold_fire));
    printf("base_damage_threshold_plasma: %d\n", ntohl(func6->base_damage_threshold_plasma));
    printf("base_damage_threshold_electrical: %d\n", ntohl(func6->base_damage_threshold_electrical));
    printf("base_damage_threshold_EMP: %d\n", ntohl(func6->base_damage_threshold_EMP));
    printf("base_damage_threshold_explosive: %d\n", ntohl(func6->base_damage_threshold_explosive));
    printf("base_damage_resistance_normal: %d\n", ntohl(func6->base_damage_resistance_normal));
    printf("base_damage_resistance_laser: %d\n", ntohl(func6->base_damage_resistance_laser));
    printf("base_damage_resistance_fire: %d\n", ntohl(func6->base_damage_resistance_fire));
    printf("base_damage_resistance_plasma: %d\n", ntohl(func6->base_damage_resistance_plasma));
    printf("base_damage_resistance_electrical: %d\n", ntohl(func6->base_damage_resistance_electrical));
    printf("base_damage_resistance_EMP: %d\n", ntohl(func6->base_damage_resistance_EMP));
    printf("base_damage_resistance_explosive: %d\n", ntohl(func6->base_damage_resistance_explosive));
    printf("base_radiation_resistance: %d\n", ntohl(func6->base_radiation_resistance));
    printf("base_poison_resistance: %d\n", ntohl(func6->base_poison_resistance));
    printf("starting_age: %d\n", ntohl(func6->starting_age));
    printf("gender: %d\n", ntohl(func6->gender));
    printf("bonus_to_strength: %d\n", ntohl(func6->bonus_to_strength));
    printf("bonus_to_perception: %d\n", ntohl(func6->bonus_to_perception));
    printf("bonus_to_endurance: %d\n", ntohl(func6->bonus_to_endurance));
    printf("bonus_to_charisma: %d\n", ntohl(func6->bonus_to_charisma));
    printf("bonus_to_intelligence: %d\n", ntohl(func6->bonus_to_intelligence));
    printf("bonus_to_agility: %d\n", ntohl(func6->bonus_to_agility));
    printf("bonus_to_luck: %d\n", ntohl(func6->bonus_to_luck));
    printf("bonus_to_maximum_hit_points: %d\n", ntohl(func6->bonus_to_maximum_hit_points));
    printf("bonus_to_action_points: %d\n", ntohl(func6->bonus_to_action_points));
    printf("bonus_AC: %d\n", ntohl(func6->bonus_AC));
    // printf("unknown_field_3: 0x%.8hx\n", ntohl(func6->unknown_field_3));
    printf("bonus_melee_damage: %d\n", ntohl(func6->bonus_melee_damage));
    printf("bonus_carry_weight: %d\n", ntohl(func6->bonus_carry_weight));
    printf("bonus_sequence: %d\n", ntohl(func6->bonus_sequence));
    printf("bonus_healing_rate: %d\n", ntohl(func6->bonus_healing_rate));
    printf("bonus_critical_chance: %d\n", ntohl(func6->bonus_critical_chance));
    printf("bonus_to_critical_hit_table_rolls: %d\n", ntohl(func6->bonus_to_critical_hit_table_rolls));
    printf("bonus_to_damage_threshold_normal: %d\n", ntohl(func6->bonus_to_damage_threshold_normal));
    printf("bonus_to_damage_threshold_laser: %d\n", ntohl(func6->bonus_to_damage_threshold_laser));
    printf("bonus_to_damage_threshold_fire: %d\n", ntohl(func6->bonus_to_damage_threshold_fire));
    printf("bonus_to_damage_threshold_plasma: %d\n", ntohl(func6->bonus_to_damage_threshold_plasma));
    printf("bonus_to_damage_threshold_electrical: %d\n", ntohl(func6->bonus_to_damage_threshold_electrical));
    printf("bonus_to_damage_threshold_EMP: %d\n", ntohl(func6->bonus_to_damage_threshold_EMP));
    printf("bonus_to_damage_threshold_explosive: %d\n", ntohl(func6->bonus_to_damage_threshold_explosive));
    printf("bonus_to_damage_resistance_normal: %d\n", ntohl(func6->bonus_to_damage_resistance_normal));
    printf("bonus_to_damage_resistance_laser: %d\n", ntohl(func6->bonus_to_damage_resistance_laser));
    printf("bonus_to_damage_resistance_fire: %d\n", ntohl(func6->bonus_to_damage_resistance_fire));
    printf("bonus_to_damage_resistance_plasma: %d\n", ntohl(func6->bonus_to_damage_resistance_plasma));
    printf("bonus_to_damage_resistance_electrical: %d\n", ntohl(func6->bonus_to_damage_resistance_electrical));
    printf("bonus_to_damage_resistance_EMP: %d\n", ntohl(func6->bonus_to_damage_resistance_EMP));
    printf("bonus_to_damage_resistance_explosive: %d\n", ntohl(func6->bonus_to_damage_resistance_explosive));
    printf("bonus_to_radiation_resistance: %d\n", ntohl(func6->bonus_to_radiation_resistance));
    printf("bonus_to_poison_resistance: %d\n", ntohl(func6->bonus_to_poison_resistance));
    printf("bonus_to_age: %d\n", ntohl(func6->bonus_to_age));
    printf("additional_gender: %d\n", ntohl(func6->additional_gender));
    print_skills(func6->skills);
    printf("proto_id: %d\n", ntohl(func6->proto_id));
    printf("description_line_number: 0x%.8hx\n", ntohl(func6->description_line_number));
}

void free_function_6(function_6_t *func6) {
    free(func6);
}