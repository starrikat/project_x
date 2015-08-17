enum ItemSlot {
    SLOT_NONE,
    ARMOR_HEAD,
    ARMOR_TORSO,
    ARMOR_LEGS,
    ARMOR_LEFT_SHOE,
    ARMOR_RIGHT_SHOE,
    ARMOR_LEFT_HAND,
    ARMOR_RIGHT_HAND,
    ARMOR_BACK,
    WATER_BOTTLE,
    WEAPON_BOW,
    AMMO_BOW,
};

enum ItemFlag {
    /*
      TODO Replace slots with these
     */
    _SLOT_NONE = 0,
    _ARMOR_HEAD,
    _ARMOR_TORSO,
    _ARMOR_LEGS,
    _ARMOR_LEFT_SHOE,
    _ARMOR_RIGHT_SHOE,
    _ARMOR_LEFT_HAND,
    _ARMOR_RIGHT_HAND,
    _ARMOR_BACK,
    _WATER_BOTTLE,
    _WEAPON_BOW,
    _AMMO_BOW,
    VEHICLE,
    CRAFTING_ONLY,
    PUT_ON_SHOULDER,
    PUT_ON_NECK
};

struct ItemInfo {
    const char *name;

    ItemSlot slot; // remove this

    vector<enum ItemFlag> flags;

    // the size of the item in grid units
    int grid_size_x;
    int grid_size_y;
    // the size when deployed on a hardpoint
    int grid_size_on_hp_x;
    int grid_size_on_hp_y;
    // the size of the container attached to the item
    int container_size_x;
    int container_size_y;
    // where to offset the item's container in the inventory display
    float container_offset_x;
    float container_offset_y;

    // how many items can be stacked on top of each other. Stacked items
    // are one item
    int16_t maxStack;
    int weight; // [g]

    /*
      TODO replace these bools with flags
     */
    bool isContainer;
    bool isSkill;
    bool isLocation;
    bool isLiquid;
    bool isEncounterAction;
    // can the item be damaged. Some items can't be damaged, those
    // are already treated as undamagable. This is for items that don't
    // meet those conditions.
    bool canBeDamaged;
    // can it be applied to a body part (i.e. bandages and disinfectants)?
    bool apply_to_body;
    // when applied to a body part, is it consumed (i.e. disinfectants)?
    bool consumed_on_application;
    // when used, is it consumed (i.e. food, water, medicine)?
    bool consumed_on_use;
    float improves_hydration;
    float improves_satiety;
    // how much warmth this item gives when equipped on a hardpoint
    float warmth;
    // weapon damage [0,1]
    float weapon_damage;
    // weapon range [0-]
    int weapon_range;
    // item with runtime text
    bool is_text_item;
    bool is_scavenge_tool;
    float scavenge_loot_mult;
    float scavenge_safety_mult;
    float scavenge_sneak_mult;

    // sprite when item is on a normal grid
    ALLEGRO_BITMAP *sprite;
    // sprite when items is on a hardpoint
    ALLEGRO_BITMAP *sprite_on_hp;

    void save(ostream &os);
    void load(istream &is);
};

static int find_bitmap_index(ALLEGRO_BITMAP *searched);

void ItemInfo::save(ostream &os) {
    os << "name " << strlen(name) << ' ' << name << endl;
    os << "\tItemSlot " << slot << endl;
    os << "\tgrid_size_x " << grid_size_x << endl;
    os << "\tgrid_size_y " << grid_size_y << endl;
    os << "\tgrid_size_on_hp_x " << grid_size_on_hp_x << endl;
    os << "\tgrid_size_on_hp_y " << grid_size_on_hp_y << endl;
    os << "\tcontainer_size_x " << container_size_x << endl;
    os << "\tcontainer_size_y " << container_size_y << endl;
    os << "\tcontainer_offset_x " << container_offset_x << endl;
    os << "\tcontainer_offset_y " << container_offset_y << endl;
    os << "\tmaxStack " << maxStack << endl;
    os << "\tweight " << weight << endl;
    os << "\tisContainer " << isContainer << endl;
    os << "\tisSkill " << isSkill << endl;
    os << "\tisLocation " << isLocation << endl;
    os << "\tisLiquid " << isLiquid << endl;
    os << "\tisEncounterAction " << isEncounterAction << endl;
    os << "\tcanBeDamaged " << canBeDamaged << endl;
    os << "\tapply_to_body " << apply_to_body << endl;
    os << "\tconsumed_on_application " << consumed_on_application << endl;
    os << "\tconsumed_on_use " << consumed_on_use << endl;
    os << "\timproves_hydration " << improves_hydration << endl;
    os << "\timproves_satiety " << improves_satiety << endl;
    os << "\twarmth " << warmth << endl;
    os << "\tweapon_damage " << weapon_damage << endl;
    os << "\tweapon_range " << weapon_range << endl;
    os << "\tis_text_item " << is_text_item << endl;
    os << "\tis_scavenge_tool " << is_scavenge_tool << endl;
    os << "\tscavenge_loot_mult " << scavenge_loot_mult << endl;
    os << "\tscavenge_safety_mult " << scavenge_safety_mult << endl;
    os << "\tscavenge_sneak_mult " << scavenge_sneak_mult << endl;
    os << "\tsprite " << find_bitmap_index(sprite) << endl;
    os << "\tsprite_on_hp " << find_bitmap_index(sprite_on_hp) << endl;
    os << "\tflags: " << flags.size();
    for(auto&& flag : flags) {
        os << ' '<< flag;
    }
    os << endl;
}

void ItemInfo::load(istream &is) {
    is.ignore(256, ' ');
    int len;
    is >> len;
    is.ignore(1);
    char *read_name = (char *)malloc(len + 1);
    is.read(&read_name[0], len);
    read_name[len] = '\0';
    this->name = read_name;

    int slot_i;
    is.ignore(256, ' ');    is >> slot_i;
    slot = (ItemSlot)slot_i;
    is.ignore(256, ' ');    is >> grid_size_x;
    is.ignore(256, ' ');    is >> grid_size_y;
    is.ignore(256, ' ');    is >> grid_size_on_hp_x;
    is.ignore(256, ' ');    is >> grid_size_on_hp_y;
    is.ignore(256, ' ');    is >> container_size_x;
    is.ignore(256, ' ');    is >> container_size_y;
    is.ignore(256, ' ');    is >> container_offset_x;
    is.ignore(256, ' ');    is >> container_offset_y;
    is.ignore(256, ' ');    is >> maxStack;
    is.ignore(256, ' ');    is >> weight;
    is.ignore(256, ' ');    is >> isContainer;
    is.ignore(256, ' ');    is >> isSkill;
    is.ignore(256, ' ');    is >> isLocation;
    is.ignore(256, ' ');    is >> isLiquid;
    is.ignore(256, ' ');    is >> isEncounterAction;
    is.ignore(256, ' ');    is >> canBeDamaged;
    is.ignore(256, ' ');    is >> apply_to_body;
    is.ignore(256, ' ');    is >> consumed_on_application;
    is.ignore(256, ' ');    is >> consumed_on_use;
    is.ignore(256, ' ');    is >> improves_hydration;
    is.ignore(256, ' ');    is >> improves_satiety;
    is.ignore(256, ' ');    is >> warmth;
    is.ignore(256, ' ');    is >> weapon_damage;
    is.ignore(256, ' ');    is >> weapon_range;
    is.ignore(256, ' ');    is >> is_text_item;
    is.ignore(256, ' ');    is >> is_scavenge_tool;
    is.ignore(256, ' ');    is >> scavenge_loot_mult;
    is.ignore(256, ' ');    is >> scavenge_safety_mult;
    is.ignore(256, ' ');    is >> scavenge_sneak_mult;

    is.ignore(256, ' ');
    int sprite_i;
    is >> sprite_i;
    if(sprite_i < 0) sprite = NULL; else sprite = g.bitmaps[sprite_i];
    is.ignore(256, ' ');
    is >> sprite_i;
    if(sprite_i < 0) sprite_on_hp = NULL; else sprite_on_hp = g.bitmaps[sprite_i];

    /*
      read in iteminfo flags
     */
    is.ignore(256, ' ');
    int flags_size = -1;
    is >> flags_size;
    flags.resize(flags_size);
    for(auto&& flag : flags) {
        int read_flag = -1;
        is >> read_flag;
        flag = (ItemFlag)read_flag;
    }
    is.ignore(1); // \n
}

void save_ItemInfo(void) {
    ofstream out("data/item_info.txt", ios::out);
    if(out.fail() == true)
        errorQuit("failed to open data/item_info.txt for writing");

    out << g.item_info.size() - 1 << endl;

    for(auto&& ii : g.item_info)
        ii.save(out);

    out.close();
}

void load_ItemInfo(void) {
    ifstream in("data/item_info.txt", ios::in);
    if(in.fail() == true)
        errorQuit("failed to open data/item_info.txt for reading");

    int item_info_size;
    in >> item_info_size;

    ItemInfo tmp;
    for(int i = 0; i <= item_info_size; i++) {
        tmp.load(in);
        g.item_info.push_back(tmp);
    }
    in.close();
}

//#define REWRITE_ITEMDEFS
#ifdef REWRITE_ITEMDEFS
void init_iteminfo(void) {
    ItemInfo tmp;
    // 00
    tmp.name = "none";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 1;
    tmp.grid_size_on_hp_x = -1;
    tmp.grid_size_on_hp_y = -1;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = NULL;
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.isLocation = false;
    tmp.isEncounterAction = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.container_offset_x = 0;
    tmp.container_offset_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.canBeDamaged = true;
    tmp.slot = SLOT_NONE;
    tmp.warmth = 0;
    tmp.weapon_damage = 0.001;
    tmp.weapon_range = 1;
    tmp.is_text_item = false;
    tmp.is_scavenge_tool = false;
    tmp.scavenge_loot_mult = 0;
    tmp.scavenge_safety_mult = 0;
    tmp.scavenge_sneak_mult = 0;
    tmp.flags = { };
    g.item_info.push_back(tmp);

    // 01
    tmp.name = "backpack";
    tmp.grid_size_x = 6;
    tmp.grid_size_y = 6;
    tmp.maxStack = 1;
    tmp.weight = 1000;
    tmp.sprite = g.bitmaps[24];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = true;
    tmp.container_size_x = 10;
    tmp.container_size_y = 10;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_BACK;
    tmp.warmth = 0.05;
    g.item_info.push_back(tmp);

    // 02
    tmp.name = "first aid kit";
    tmp.grid_size_x = 4;
    tmp.grid_size_y = 4;
    tmp.maxStack = 1;
    tmp.weight = 750;
    tmp.sprite = g.bitmaps[22];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = true;
    tmp.container_size_x = 4;
    tmp.container_size_y = 4;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    tmp.warmth = 0;
    g.item_info.push_back(tmp);

    // 03
    tmp.name = "crowbar";
    tmp.grid_size_x = 14;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = 2500;
    tmp.sprite = g.bitmaps[20];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    tmp.weapon_damage = 0.15;
    tmp.weapon_range = 3;
    tmp.is_scavenge_tool = true;
    tmp.scavenge_loot_mult = 10.0;
    tmp.scavenge_safety_mult = 1.0;
    tmp.scavenge_sneak_mult = 1.0;
    tmp.flags = { PUT_ON_SHOULDER };
    g.item_info.push_back(tmp);

    // 04
    tmp.name = "shopping trolley";
    tmp.grid_size_x = 12;
    tmp.grid_size_y = 12;
    tmp.maxStack = 1;
    tmp.weight = 5000;
    tmp.sprite = g.bitmaps[26];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = true;
    tmp.container_size_x = 20;
    tmp.container_size_y = 20;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    tmp.weapon_damage = 0.0;
    tmp.weapon_range = 1;
    tmp.is_scavenge_tool = false;
    tmp.scavenge_loot_mult = 0;
    tmp.scavenge_safety_mult = 0;
    tmp.scavenge_sneak_mult = 0;
    tmp.flags = { VEHICLE };
    g.item_info.push_back(tmp);

    // 05
    tmp.name = "pill bottle";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = 50;
    tmp.sprite = g.bitmaps[27];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = true;
    tmp.container_size_x = 1;
    tmp.container_size_y = 2;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    tmp.flags = { };
    g.item_info.push_back(tmp);

    // 06
    tmp.name = "Flee";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[31];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 07
    tmp.name = "Single attack";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[32];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 08
    tmp.name = "bullet";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 1;
    tmp.maxStack = 5;
    tmp.weight = 5;
    tmp.sprite = g.bitmaps[34];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    tmp.weapon_damage = 0.001;
    g.item_info.push_back(tmp);

    // 09
    tmp.name = "arrow";
    tmp.grid_size_x = 10;
    tmp.grid_size_y = 1;
    tmp.maxStack = 5;
    tmp.weight = 75;
    tmp.sprite = g.bitmaps[35];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = AMMO_BOW;
    tmp.weapon_damage = 0.005;
    g.item_info.push_back(tmp);

    // 10
    tmp.name = "Quick";
    tmp.grid_size_x = 6;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[36];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = true;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    tmp.weapon_damage = 0.0;
    g.item_info.push_back(tmp);

    // 11
    tmp.name = "Lockpicking";
    tmp.grid_size_x = 6;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[37];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = true;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 12
    tmp.name = "Myopia";
    tmp.grid_size_x = 6;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[38];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = true;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 13
    tmp.name = "Metabolism";
    tmp.grid_size_x = 6;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[39];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = true;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 14
    tmp.name = "whiskey";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 2;
    tmp.maxStack = 5;
    tmp.weight = 50;
    tmp.sprite = g.bitmaps[40];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = true;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = true;
    tmp.consumed_on_application = true;
    tmp.consumed_on_use = true;
    tmp.improves_hydration = 0.1;
    tmp.improves_satiety = 0.05;
    tmp.slot = WATER_BOTTLE;
    g.item_info.push_back(tmp);

    // 15
    tmp.name = "clean rag";
    tmp.grid_size_x = 3;
    tmp.grid_size_y = 2;
    tmp.maxStack = 10;
    tmp.weight = 50;
    tmp.sprite = g.bitmaps[41];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = true;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 16
    tmp.name = "Factory";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[42];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isLocation = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 17
    tmp.name = "Shack in the woods";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[43];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isLocation = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 18
    tmp.name = "water bottle";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 4;
    tmp.maxStack = 1;
    tmp.weight = 100;
    tmp.sprite = g.bitmaps[49];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = true;
    tmp.isLocation = false;
    tmp.container_size_x = 1;
    tmp.container_size_y = 2;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 19
    tmp.name = "red hoodie";
    tmp.grid_size_x = 3;
    tmp.grid_size_y = 2;
    tmp.grid_size_on_hp_x = 9;
    tmp.grid_size_on_hp_y = 9;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = g.bitmaps[50];
    tmp.sprite = g.bitmaps[51];
    tmp.isContainer = true;
    tmp.container_size_x = 2;
    tmp.container_size_y = 4;
    tmp.container_offset_x = -185;
    tmp.container_offset_y = 220;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_TORSO;
    tmp.warmth = 0.1;
    g.item_info.push_back(tmp);

    // 20
    tmp.name = "blue jeans";
    tmp.grid_size_x = 3;
    tmp.grid_size_y = 2;
    tmp.grid_size_on_hp_x = 6;
    tmp.grid_size_on_hp_y = 11;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = g.bitmaps[52];
    tmp.sprite = g.bitmaps[53];
    tmp.isContainer = true;
    tmp.container_size_x = 2;
    tmp.container_size_y = 2;
    tmp.container_offset_x = -165;
    tmp.container_offset_y = +150;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_LEGS;
    tmp.warmth = 0.5;
    g.item_info.push_back(tmp);

    // 21
    tmp.name = "ski mask";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.grid_size_on_hp_x = -1;
    tmp.grid_size_on_hp_y = -1;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = g.bitmaps[54];
    tmp.sprite = g.bitmaps[55];
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.container_offset_x = 0;
    tmp.container_offset_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_HEAD;
    tmp.warmth = 0.1;
    g.item_info.push_back(tmp);

    // 22
    tmp.name = "right glove";
    tmp.grid_size_x = 3;
    tmp.grid_size_y = 3;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = NULL;
    tmp.sprite = g.bitmaps[56];
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_RIGHT_HAND;
    tmp.warmth = 0.1;
    g.item_info.push_back(tmp);

    // 23
    tmp.name = "left glove";
    tmp.grid_size_x = 3;
    tmp.grid_size_y = 3;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = NULL;
    tmp.sprite = g.bitmaps[57];
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_LEFT_HAND;
    tmp.warmth = 0.1;
    g.item_info.push_back(tmp);

    // 24
    tmp.name = "right shoe";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.grid_size_on_hp_x = 3;
    tmp.grid_size_on_hp_y = 3;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = NULL;
    tmp.sprite = g.bitmaps[85];
    tmp.sprite_on_hp = g.bitmaps[58];
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_RIGHT_SHOE;
    tmp.warmth = 0.1;
    tmp.weapon_damage = 0.005;
    g.item_info.push_back(tmp);

    // 25
    tmp.name = "left shoe";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.grid_size_on_hp_x = 3;
    tmp.grid_size_on_hp_y = 3;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = NULL;
    tmp.sprite = g.bitmaps[86];
    tmp.sprite_on_hp = g.bitmaps[59];
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = ARMOR_LEFT_SHOE;
    tmp.warmth = 0.1;
    tmp.weapon_damage = 0.005;
    g.item_info.push_back(tmp);

    // 26
    tmp.name = "Retreat";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.grid_size_on_hp_x = -1;
    tmp.grid_size_on_hp_y = -1;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[80];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 27
    tmp.name = "Advance";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[81];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 28
    tmp.name = "fist";
    tmp.grid_size_x = 3;
    tmp.grid_size_y = 3;
    tmp.maxStack = 1;
    tmp.weight = 500;
    tmp.sprite_on_hp = NULL;
    tmp.sprite = g.bitmaps[82];
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.isEncounterAction = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.canBeDamaged = false;
    tmp.slot = SLOT_NONE;
    tmp.warmth = 0.1;
    tmp.weapon_damage = 0.1;
    tmp.weapon_range = 1;
    g.item_info.push_back(tmp);

    // 29
    tmp.name = "makeshift wood bow";
    tmp.grid_size_x = 14;
    tmp.grid_size_y = 3;
    tmp.maxStack = 1;
    tmp.weight = 1500;
    tmp.sprite_on_hp = NULL;
    tmp.sprite = g.bitmaps[84];
    tmp.isContainer = true;
    tmp.container_size_x = 10;
    tmp.container_size_y = 1;
    tmp.container_offset_x = -250;
    tmp.container_offset_y = 80;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.canBeDamaged = true;
    tmp.slot = WEAPON_BOW;
    tmp.warmth = 0.0;
    tmp.weapon_damage = 0.2;
    tmp.weapon_range = 8;
    g.item_info.push_back(tmp);

    // 30
    tmp.name = "moldy bread";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = 300;
    tmp.sprite_on_hp = NULL;
    tmp.sprite = g.bitmaps[96];
    tmp.isContainer = false;
    tmp.container_size_x = -1;
    tmp.container_size_y = -1;
    tmp.container_offset_x = 0;
    tmp.container_offset_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = true;
    tmp.improves_hydration = 0.005;
    tmp.improves_satiety = 0.1;
    tmp.canBeDamaged = true;
    tmp.slot = SLOT_NONE;
    tmp.warmth = 0.0;
    tmp.weapon_damage = 0.0001;
    tmp.weapon_range = 1;
    g.item_info.push_back(tmp);

    // 31
    tmp.name = "water";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 2;
    tmp.maxStack = 5;
    tmp.weight = 50;
    tmp.sprite = g.bitmaps[97];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = true;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = true;
    tmp.consumed_on_application = true;
    tmp.consumed_on_use = true;
    tmp.improves_hydration = 0.3;
    tmp.improves_satiety = 0.05;
    tmp.slot = WATER_BOTTLE;
    g.item_info.push_back(tmp);

    // 32
    tmp.name = "clear water";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 2;
    tmp.maxStack = 5;
    tmp.weight = 50;
    tmp.sprite = g.bitmaps[97];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = true;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = true;
    tmp.consumed_on_application = true;
    tmp.consumed_on_use = true;
    tmp.improves_hydration = 0.3;
    tmp.improves_satiety = 0.05;
    tmp.slot = WATER_BOTTLE;
    g.item_info.push_back(tmp);

    // 33
    tmp.name = "wild berries";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = 300;
    tmp.sprite = g.bitmaps[100];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = true;
    tmp.improves_hydration = 0.1;
    tmp.improves_satiety = 0.2;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 34
    tmp.name = "matches";
    tmp.grid_size_x = 1;
    tmp.grid_size_y = 1;
    tmp.maxStack = 5;
    tmp.weight = 50;
    tmp.sprite = g.bitmaps[101];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.slot = SLOT_NONE;
    tmp.is_scavenge_tool = true;
    tmp.scavenge_loot_mult = 1.0;
    tmp.scavenge_safety_mult = 2.0;
    tmp.scavenge_sneak_mult = 0.5;
    g.item_info.push_back(tmp);

    // 35
    tmp.name = "rope";
    tmp.grid_size_x = 5;
    tmp.grid_size_y = 5;
    tmp.maxStack = 1;
    tmp.weight = 1000;
    tmp.sprite = g.bitmaps[102];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.slot = WATER_BOTTLE;
    tmp.is_scavenge_tool = true;
    tmp.scavenge_loot_mult = 1.0;
    tmp.scavenge_safety_mult = 4.0;
    tmp.scavenge_sneak_mult = 1.0;
    g.item_info.push_back(tmp);

    // 36
    tmp.name = "gasoline can";
    tmp.grid_size_x = 4;
    tmp.grid_size_y = 5;
    tmp.maxStack = 1;
    tmp.weight = 750;
    tmp.sprite = g.bitmaps[103];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = true;
    tmp.container_size_x = 3;
    tmp.container_size_y = 3;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.slot = SLOT_NONE;
    tmp.is_scavenge_tool = false;
    tmp.scavenge_loot_mult = 0;
    tmp.scavenge_safety_mult = 0;
    tmp.scavenge_sneak_mult = 0;
    g.item_info.push_back(tmp);

    // 37
    tmp.name = "wood";
    tmp.grid_size_x = 8;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = 5000;
    tmp.sprite = g.bitmaps[104];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.container_size_x = -1;
    tmp.container_size_y = -1;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 38
    tmp.name = "fire";
    tmp.grid_size_x = 3;
    tmp.grid_size_y = 3;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[105];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.container_size_x = -1;
    tmp.container_size_y = -1;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.slot = SLOT_NONE;
    tmp.flags = { CRAFTING_ONLY };
    g.item_info.push_back(tmp);

    // 39
    tmp.name = "cooking pot";
    tmp.grid_size_x = 4;
    tmp.grid_size_y = 3;
    tmp.maxStack = 1;
    tmp.weight = 1000;
    tmp.sprite = g.bitmaps[106];
    tmp.sprite_on_hp = NULL;
    tmp.isLiquid = false;
    tmp.isContainer = false;
    tmp.container_size_x = -1;
    tmp.container_size_y = -1;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.improves_hydration = 0.0;
    tmp.improves_satiety = 0.0;
    tmp.slot = SLOT_NONE;
    tmp.flags = { };
    g.item_info.push_back(tmp);

    // 40
    tmp.name = "Wait";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[115];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 40
    tmp.name = "Warn";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[116];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);

    // 40
    tmp.name = "Leave";
    tmp.grid_size_x = 2;
    tmp.grid_size_y = 2;
    tmp.maxStack = 1;
    tmp.weight = -1;
    tmp.sprite = g.bitmaps[117];
    tmp.sprite_on_hp = NULL;
    tmp.isContainer = false;
    tmp.isEncounterAction = true;
    tmp.container_size_x = 0;
    tmp.container_size_y = 0;
    tmp.isSkill = false;
    tmp.apply_to_body = false;
    tmp.consumed_on_application = false;
    tmp.consumed_on_use = false;
    tmp.slot = SLOT_NONE;
    g.item_info.push_back(tmp);
}
#endif
