#ifndef ITEM_H
#define ITEM_H

#include <stdint.h>
#include <stdio.h>

/**
 * An enumeration of the different item categories.
 */
typedef enum {
    /**
     * An unknown item category.
     */
    ITEM_UNKNOWN,

    /**
     * A weapon item.
     */
    ITEM_WEAPON,

    /**
     * An ammunition item.
     */
    ITEM_AMMO,

    /**
     * An armor item.
     */
    ITEM_ARMOR,

    /**
     * A drug item.
     */
    ITEM_DRUG,

    /**
     * A miscellaneous item.
     */
    ITEM_MISC

} item_category_t;

/**
 * Struct containing information about a specific item type.
 */
typedef struct {
    /**
     * The unique identifier for the item.
     */
    uint32_t id;
    
    /**
     * A description of the item.
     */
    const char *desc;

} item_info_t;

static const item_info_t WEAPONS[] = {
    { 9, "10mm SMG" },
    { 8, "10mm Pistol" },
    { 6, "Sledgehammer" },
    { 12, "Minigun" },
    { 13, "Rocket Launcher" },
    { 5, "Club" },
    { 11, "Flamer" },
    { 10, "Hunting Rifle" },
    { 4, "Knife" },
    { 7, "Spear" },
    { 15, "Plasma Rifle" },
    { 16, "Laser Pistol" },
    { 18, "Desert Eagle .44" },
    { 19, "Rock" },
    { 20, "Crowbar" },
    { 21, "Brass Knuckles" },
    { 22, "14mm Pistol" },
    { 23, "Assault Rifle" },
    { 24, "Plasma Pistol" },
    { 25, "Grenade (Frag)" },
    { 26, "Grenade (Plasma)" },
    { 27, "Grenade (Pulse)" },
    { 28, "Gatling Laser" },
    { 45, "Throwing Knife" },
    { 79, "Flare" },
    { 94, "Shotgun" },
    { 115, "Super Sledge" },
    { 116, "Ripper" },
    { 118, "Laser Rifle" },
    { 120, "Alien Blaster" },
    { 122, "9mm Mauser" },
    { 143, "Sniper Rifle" },
    { 159, "Molotov Cocktail" },
    { 160, "Cattle Prod" },
    { 161, "Red Ryder BB Gun" },
    { 162, "Red Ryder LE BB Gun" },
    { 205, "Flare" },
    { 233, "Turbo Plasma Rifle" },
    { 234, "Spiked Knuckles" },
    { 235, "Power Fist" },
    { 236, "Combat Knife" },
    { 241, ".223 Pistol" },
    { 242, "Combat Shotgun" },
    { 261, "Jonnys BB Gun" },
    { 268, "H&K CAWS" },
    { 270, "Robo Rocket Launcher" },
    { 280, "Sharpened Spear" },
    { 283, "Tommy Gun" },
    { 287, "Scoped Hunting Rifle" },
    { 290, "Robo Melee Weapon 1" },
    { 291, "Robo Melee Weapon 2" },
    { 292, "Boxing Gloves" },
    { 293, "Plated Boxing Gloves" },
    { 296, "HK P90c" },
    { 299, "Pipe Rifle" },
    { 300, "Zip Gun" },
    { 313, ".44 Magnum Revolver" },
    { 319, "Switchblade" },
    { 320, "Sharpened Pole" },
    { 332, "M3A1 \"Grease Gun\" SMG" },
    { 350, "Bozar" },
    { 351, "FN FAL" },
    { 352, "H&K G11" },
    { 353, "XL70E3" },
    { 354, "Pancor Jackhammer" },
    { 355, "Light Support Weapon" },
    { 365, "Plant Spike" },
    { 371, "Claw" },
    { 372, "Claw" },
    { 383, "Shiv" },
    { 384, "Wrench" },
    { 385, "Sawed-Off Shotgun" },
    { 386, "Louisville Slugger" },
    { 387, "M60" },
    { 388, "Needler Pistol" },
    { 389, "Avenger Minigun" },
    { 390, "Solar Scorcher" },
    { 391, "H&K G11E" },
    { 392, "M72 Gauss Rifle" },
    { 393, "Phazer" },
    { 394, "PPK12 Gauss Pistol" },
    { 395, "Vindicator Minigun" },
    { 396, "YK32 Pulse Pistol" },
    { 397, "YK42B Pulse Rifle" },
    { 398, ".44 Magnum (Speed Load)" },
    { 399, "Super Cattle Prod" },
    { 400, "Improved Flamer" },
    { 401, "Laser Rifle (Ex Cap.)" },
    { 402, "Magneto-Laser Pistol" },
    { 403, "FN FAL (Night Sight)" },
    { 404, "Desert Eagle (Exp. Mag.)" },
    { 405, "Assault Rifle (Exp. Mag.)" },
    { 406, "Plasma Pistol (Ex Cap.)" },
    { 407, "Mega Power Fist" },
    { 421, "Holy Hand Grenade" },
    { 423, "Gold Nugget" },
    { 426, "Uranium Ore" },
    { 427, "Flame Breath" },
    { 486, "Refined Uranium Ore" },
    { 489, "Special Boxer Weapon" },
    { 496, "Boxing Gloves" },
    { 497, "Plated Boxing Gloves" },
    { 498, "Dual Plasma Cannon" },
    { 500, "FN FAL HPFA" },
    { 517, "\"Little Jesus\"" },
    { 518, "Dual Minigun" },
    { 520, "Heavy Dual Minigun" },
    { 522, "Wakizashi Blade" },
    { 530, "End Boss Knife" },
    { 531, "End Boss Plasma Gun" }
};

static const item_info_t AMMO[] = {
    { 14, "Explosive Rocket" },
    { 29, "10mm JHP" },
    { 30, "10mm AP" },
    { 31, ".44 Magnum JHP" },
    { 32, "Flamethrower Fuel" },
    { 33, "14mm AP" },
    { 34, ".223 FMJ" },
    { 35, "5mm JHP" },
    { 36, "5mm AP" },
    { 37, "Rocket AP" },
    { 38, "Small Energy Cell" },
    { 39, "Micro Fusion Cell" },
    { 95, "12 ga. Shotgun Shells" },
    { 111, ".44 magnum FMJ" },
    { 121, "9mm ball" },
    { 163, "BB's" },
    { 274, "Robo Rocket Ammo" },
    { 357, ".45 Caliber" },
    { 358, "2mm EC" },
    { 359, "4.7mm Caseless" },
    { 360, "9mm" },
    { 361, "HN Needler Cartridge" },
    { 362, "HN AP Needler Cartridge" },
    { 363, "7.62mm" },
    { 382, "Flamethrower Fuel MKII" },
};

static const item_info_t ARMOR[] = {
    { 2, "Metal Armor" },
    { 1, "Leather Armor" },
    { 3, "Power Armor" },
    { 17, "Combat Armor" },
    { 74, "Leather Jacket" },
    { 113, "Robes" },
    { 232, "Hardened Power Armor" },
    { 239, "Brotherhood Armor" },
    { 240, "Tesla Armor" },
    { 265, "Combat Leather Jacket" },
    { 348, "Advanced Power Armor" },
    { 349, "Adv. Power Armor MKII" },
    { 379, "Leather Armor Mark II" },
    { 380, "Metal Armor Mark II" },
    { 381, "Combat Armor Mark II" },
    { 524, "Bridgekeeper's Robes" },
};

static const item_info_t DRUGS[] = {
    { 40, "Stimpak" },
    { 48, "RadAway" },
    { 49, "Antidote" },
    { 53, "Mentats" },
    { 71, "Fruit" },
    { 81, "Iguana-on-a-stick" },
    { 87, "Buffout" },
    { 103, "Iguana-on-a-stick" },
    { 106, "Nuka-Cola" },
    { 109, "Rad-X" },
    { 110, "Psycho" },
    { 124, "Beer" },
    { 125, "Booze" },
    { 144, "Super Stimpak" },
    { 259, "Jet" },
    { 260, "Jet Antidote" },
    { 273, "Healing Powder" },
    { 310, "Gamma Gulp Beer" },
    { 311, "Roentgen Rum" },
    { 334, "Poison" },
    { 378, "Cookie" },
    { 424, "Monument Chunk" },
    { 469, "Rot Gut" },
    { 473, "Mutated Toe" },
    { 480, "Bonus +1 Agility" },
    { 481, "Bonus +1 Intelligence" },
    { 482, "Bonus +1 Strength" },
    { 525, "Hypo" },
};

static const item_info_t MISC[] = {
    { 41, "Money" },
    { 47, "First Aid Kit" },
    { 50, "Reserved (do not use)" },
    { 51, "Dynamite" },
    { 52, "Geiger Counter" },
    { 54, "Stealth Boy" },
    { 55, "Water Chip" },
    { 56, "Dog Tags" },
    { 57, "Bug" },
    { 58, "Tape" },
    { 59, "Motion Sensor" },
    { 72, "Briefcase" },
    { 73, "Big Book of Science" },
    { 75, "Tool" },
    { 76, "Deans Electronics" },
    { 77, "Electronic Lockpick" },
    { 78, "Fuzzy Painting" },
    { 80, "First Aid Book" },
    { 84, "Lockpicks" },
    { 85, "Plastic Explosives" },
    { 86, "Scout Handbook" },
    { 88, "Watch" },
    { 89, "Motor" },
    { 91, "Doctor's Bag" },
    { 92, "Scorpion Tail" },
    { 98, "Junk" },
    { 99, "Gold Locket" },
    { 100, "Radio" },
    { 101, "Lighter" },
    { 102, "\"Guns and Bullets\"" },
    { 104, "Tape Recorder" },
    { 112, "Urn" },
    { 114, "Tangler's Hand" },
    { 117, "Flower" },
    { 119, "Knecklace" },
    { 123, "Psychic Nullifier" },
    { 126, "Water Flask" },
    { 127, "Rope" },
    { 140, "Access Card" },
    { 141, "COC Badge" },
    { 142, "COC Badge" },
    { 148, "Bookshelf (do not use)" },
    { 150, "Bookshelf (do not use)" },
    { 154, "Shelves (do not use)" },
    { 156, "Shelves (do not use)" },
    { 164, "Brotherhood Tape" },
    { 190, "FEV Disk" },
    { 191, "Security Disk" },
    { 192, "Alpha Experiment Disk" },
    { 193, "Delta Experiment Disk" },
    { 194, "Vree's Experiment Disk" },
    { 195, "Brotherhood Honor Code" },
    { 196, "Mutant Transmission" },
    { 206, "Dynamite (ticking)" },
    { 207, "Geiger Counter (on)" },
    { 208, "Motion Sensor (on)" },
    { 209, "Plastic Explosives (ticking)" },
    { 210, "Stealth Boy (on)" },
    { 212, "Tandi (do not use)" },
    { 215, "Brotherhood History" },
    { 216, "Maxon's History" },
    { 217, "Maxson's Journal" },
    { 218, "Light Healing (do not use)" },
    { 219, "Medium Healing (do not use)" },
    { 220, "Heavy Healing (do not use)" },
    { 221, "Security Card" },
    { 222, "Field Switch" },
    { 224, "Small Statuette" },
    { 225, "Cat's Paw Magazine" },
    { 226, "Box of Noodles" },
    { 227, "Small Dusty Box of Some Sort" },
    { 228, "Technical Manual" },
    { 229, "Small Piece of Machinery" },
    { 230, "Vault Records" },
    { 231, "Military Base Security Codes" },
    { 237, "Chemistry Journals" },
    { 238, "Regulator Transmission" },
    { 251, "Anna's Bones" },
    { 252, "Anna's Gold Locket" },
    { 253, "Fuel Cell Controller" },
    { 254, "Fuel Cell Regulator" },
    { 255, "Day Pass" },
    { 256, "False Citizenship Papers" },
    { 257, "Cornelius' Gold Watch" },
    { 258, "Hydroelectric Part" },
    { 262, "Rubber Boots" },
    { 263, "Slag Message" },
    { 264, "Smith's Cool Item (do not use)" },
    { 266, "Vic's Radio" },
    { 267, "Vic's Water Flask" },
    { 269, "Robot Parts" },
    { 271, "Broc Flower" },
    { 272, "Xander Root" },
    { 275, "Trophy of Recognition" },
    { 276, "Gecko Pelt" },
    { 277, "Golden Gecko Pelt" },
    { 278, "Flint" },
    { 279, "Neural Interface" },
    { 281, "Dixon's Eye" },
    { 282, "Clifton's Eye" },
    { 284, "Meat Jerky" },
    { 285, "Radscorpion Limbs" },
    { 286, "Firewood" },
    { 288, "Car Fuel Cell (do not use)" },
    { 289, "Shovel" },
    { 294, "Vault 13 Holodisk" },
    { 295, "Cheezy Poofs" },
    { 297, "Metal Pole" },
    { 298, "Trapper Town Key" },
    { 301, "Clipboard" },
    { 302, "Gecko Holodisk" },
    { 303, "Reactor Holodisk" },
    { 304, "Deck of \"Tragic Cards\"" },
    { 305, "Yellow Reactor Keycard" },
    { 306, "Red Reactor Keycard" },
    { 307, "3 Step Plasma Transformer" },
    { 308, "Super Tool Kit" },
    { 309, "Talisman" },
    { 312, "Part Requesition Form" },
    { 314, "Condom (blue package)" },
    { 315, "Condom (green package)" },
    { 316, "Condom (red package)" },
    { 317, "Cosmetics Case" },
    { 318, "Empty Hypodermic Needle" },
    { 321, "Cybernetic Brain" },
    { 322, "Human Brain" },
    { 323, "Chimpanzee Brain" },
    { 324, "Abnormal Brain" },
    { 325, "Dice" },
    { 326, "Loaded Dice" },
    { 327, "Easter Egg" },
    { 328, "Magic 8 Ball" },
    { 329, "Mutagenic Serum" },
    { 331, "Cat's Paw Issue 5" },
    { 333, "Heart Pills" },
    { 335, "Moore's Briefcase" },
    { 336, "Moore's Briefcase" },
    { 337, "Lynette Holodisk" },
    { 338, "Westin Holodisk" },
    { 339, "NCR Spy Holodisk" },
    { 340, "Doctor's Papers" },
    { 341, "Presidential Pass" },
    { 342, "Ranger's Pin" },
    { 343, "Ranger's Map" },
    { 356, "Voice Recognition Module" },
    { 364, "Robot Motivator" },
    { 366, "GECK" },
    { 373, "Vault 15 Keycard" },
    { 377, "Vault 15 Computer Parts" },
    { 408, "Field Medic First Aid Kit" },
    { 409, "Paramedic's Bag" },
    { 410, "Expanded Lockpick Set" },
    { 411, "Electronic Lockpick MKII" },
    { 412, "Oil Can" },
    { 413, "Stables ID Badge" },
    { 414, "Vault 15 Shack Key" },
    { 415, "Spectacles" },
    { 416, "Empty Jet Canister" },
    { 417, "Oxygen Tank" },
    { 418, "Poison Tank" },
    { 419, "Mine Parts" },
    { 420, "Morningstar Script" },
    { 422, "Excavator Chip" },
    { 428, "Medical Supplies" },
    { 429, "Gold Tooth" },
    { 430, "Howitzer Shell" },
    { 431, "Ramirez Box (closed)" },
    { 432, "Ramirez Box (open)" },
    { 433, "Mirrored Shades" },
    { 436, "Deck of Cards" },
    { 437, "Deck of Marked Cards" },
    { 439, "Pocket Lint" },
    { 440, "Bio-Med Gel" },
    { 441, "Blondie's Dog-Tags" },
    { 442, "Angel Eyes' Dog-Tags" },
    { 443, "Tuco's Dog-Tags" },
    { 444, "Raider's Map" },
    { 445, "Sheriff's Badge" },
    { 446, "Vertibird Plans" },
    { 447, "Bishop's Holodisk" },
    { 448, "Account Book" },
    { 449, "<unused>" },
    { 450, "Torn Paper 1" },
    { 451, "Torn Paper 2" },
    { 452, "Torn Paper 3" },
    { 453, "Password Paper" },
    { 454, "Explosive switch" },
    { 457, "Hubologists' Field Report" },
    { 458, "Military Base Holodisk 5" },
    { 459, "Military Base Holodisk 1" },
    { 460, "Military Base Holodisk 2" },
    { 461, "Military Base Holodisk 3" },
    { 462, "Military Base Holodisk 4" },
    { 463, "Evacuation Holodisk" },
    { 464, "Experiment Holodisk" },
    { 465, "Medical Holodisk" },
    { 466, "Password Paper" },
    { 468, "Smitty's Meal" },
    { 470, "Ball Gag" },
    { 471, "\"The Lavender Flower\"" },
    { 472, "Hubologists' Holodisk" },
    { 474, "Daisies" },
    { 475, "<unused>" },
    { 476, "Enlightened One's Letter" },
    { 477, "Broadcast Holodisk" },
    { 478, "Sierra Mission Holodisk" },
    { 479, "NavCom Parts" },
    { 483, "Fallout 2 Hintbook" },
    { 484, "Player's Ear" },
    { 485, "Masticator's Ear" },
    { 487, "Note From Francis" },
    { 488, "K-9 Motivator" },
    { 490, "NCR History Holodisk" },
    { 491, "Mr. Nixon Doll" },
    { 492, "Tanker Fob" },
    { 493, "Teachings Holodisk" },
    { 494, "Kokoweef Script" },
    { 495, "Presidential Access Key" },
    { 499, "PIPBoy Lingual Enhancer" },
    { 503, "Blue Memory Module" },
    { 504, "Green Memory Module" },
    { 505, "Red Memory Module" },
    { 506, "Yellow Memory Module" },
    { 507, "Decomposing Body" },
    { 508, "Rubber Doll" },
    { 509, "Damaged Rubber Doll" },
    { 516, "PIPBoy Medical Enhancer" },
    { 519, "Bottle Caps" },
    { 523, "Survey Map" },
};

#pragma pack(push, 1)
/**
 * Represents an item within the game, containing various fields of metadata
 * and status information.
 */
typedef struct {
    /**
     * The quantity of this item.
     */
    uint32_t quantity;

    /**
     * Always 0.
     */
    uint32_t unknown_field_1;

    /**
     * Location of item. Necessarily always -1 (in inventory).
     */
    uint32_t location;

    /**
     * Always 0.
     */
    uint32_t unknown_field_2;

    /**
     * Always 0.
     */
    uint32_t unknown_field_3;

    /**
     * Unknown, 0 for most objects. Only non-zero for some items with
     * special/quest uses. (E.g. poison tank, rubber boots, tool).
     */ 
    uint32_t unknown_field_4;

    /**
     * Unknown, 0 for most objects. Only non-zero for some items with
     * special/quest uses.
     */
    uint32_t unknown_field_5;

    /**
     * Always 0.
     */
    uint32_t unknown_field_6;

    /**
     * Unknown, 0 for most objects. For plant spikes, this is 1,
     * and for sharpened poles, 2.
     */
    uint32_t unknown_field_7;

    /**
     * Item's on-ground image.
     */
    uint32_t on_ground_image;

    /**
     * A bitfield: 0x01000000 indicates the item is held in the right hand,
     * 0x02000000 - in the left hand, and 0x04000000 - worn (as armor).
     * Use of other bits is unknown.
     */
    uint32_t bitfield;

    /**
     * 0, 1, or 2. Map level, which is irrelevant since it's in inventory.
     */
    uint32_t map_level;

    /**
     * Object ID.
     */
    uint32_t object_id;

    /**
     * Always -1.
     */
    uint32_t unknown_field_9;

    /**
     * For Roentgen Rum and Gamma Gulp Beer, this is 0x00000001, for all others 0.
     */
    uint32_t unknown_field_10;

    /**
     * For Roentgen Rum and Gamma Gulp Beer, this is 0x00010000, for all others 0.
     */
    uint32_t unknown_field_11;

    /**
     * Always 0.
     */
    uint32_t unknown_field_12;

    /**
     * Script ID; -1 for none.
     */
    uint32_t script_id;

    /**
     * Always -1.
     */
    uint32_t unknown_field_13;

    /**
     * Usually 0; for containers it is the number of items in the container.
     * The enclosed items are the ones immediately following it.
     */ 
    uint32_t num_items;

    /**
     * Unknown. Non-zero only for containers.
     */
    uint32_t unknown_field_14;

    /**
     * Unknown. Non-zero only for containers.
     */
    uint32_t unknown_field_15;
    /**
     * Always 0.
     */
    uint32_t unknown_field_16;

    /**
     * Specific values depending on the item type.
     */
    uint32_t multiple_uses;

    /**
     * The type of ammo that is used. Only exists if the item is a gun type.
     */
    uint32_t ammo_type;
} item_t;
#pragma pack(pop)

/**
 * Determines the category of an item based on its object ID.
 *
 * @param object_id
 *     The object ID used to determine the item category.
 * 
 * @return
 *     The item category of the item with the given object ID.
 */
item_category_t get_item_category(uint32_t object_id);

/**
 * Calculates the size of a given item, taking into account its category
 * and whether it has additional fields (e.g., multiple uses or ammo type).
 *
 * @param item
 *     The item for which to calculate the size.
 * 
 * @return
 *     The size of the item in bytes.
 */
size_t get_item_size(const item_t* item);

/**
 * Reads an item from the given file at the specified offset and returns
 * a pointer to a newly allocated item_t structure containing the item data.
 * If reading fails, NULL is returned.
 *
 * @param file
 *     The file from which to read the item.
 *
 * @param offset
 *     The offset in the file where the item data is located.
 * 
 * @return
 *     A pointer to a newly allocated item_t structure, or NULL if an
 *     error occurs.
 */
item_t* read_item(FILE* file, uint32_t offset);

/**
 * Prints out the contents of an item structure in a human-readable format.
 *
 * @param item
 *     The item whose details are to be printed.
 */
void print_item(const item_t *item);

/**
 * Frees the memory allocated for an item_t structure.
 *
 * @param item
 *     The item to be freed.
 */
void free_item(item_t *item);

#endif