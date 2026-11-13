#include "dw4/reflected.h"
#include "dw4/igVec3f.h"

/* The _kindNo each beNDMWItem* class stamps on its items. */
enum ItemKind {
    ITEM_KIND_WEAPON = 0,
    ITEM_KIND_BLUE_ARMOR = 1,
    ITEM_KIND_YELLOW_ARMOR = 2,
    ITEM_KIND_ABILITY_CHIP = 3,
    ITEM_KIND_DISK = 4,
    ITEM_KIND_INSTANT = 5,
    ITEM_KIND_IMPORTANT = 6,
    ITEM_KIND_WAZA = 9
};

/* Inventory word shared by every beNDMWItem* class: bits 0-9 record number, bit 10 equipped flag,
 * bits 12-15 kind. Weapons and blue armor add the pocket in bits 16-19, every armor and weapon the
 * revision in bits 20-30, and a disk its stack count in bits 16-19. */
#define ITEM_REC_NO_MASK 0x3FF
#define ITEM_EQUIPPED_BIT 0x400
#define ITEM_KIND_SHIFT 12
#define ITEM_KIND_MASK 0xF
#define ITEM_POCKET_SHIFT 16
#define ITEM_POCKET_MASK 0xF
#define ITEM_REVISION_SHIFT 20
#define ITEM_REVISION_MASK 0x7FF
#define ITEM_DISK_COUNT_SHIFT 16
#define ITEM_DISK_COUNT_MASK 0xF

/* A GAMERAM player or common record field found by name: its value sits after the 12-byte header. */
typedef struct IntProperty {
    char _header[12];
    int _value;
} IntProperty;
typedef struct IntListProperty {
    char _header[12];
    igDataList *_value;
} IntListProperty;

extern "C" void beMessenger_SendNamed(...);
extern "C" void *beMessenger_GetObject(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int strcmp(const char *a, const char *b);
extern "C" int FUN_00236f80(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int beNDMWGameRam_ChangeHp(...);
extern "C" int beNDMWGameRam_ChangeMp(...);
extern "C" int FUN_00447b00(...);
extern "C" int FUN_00447b40(...);
extern "C" int SYSsetGateStage(...);
extern "C" void *igProperty_GetRecordIntList(...);
extern "C" void *igProperty_GetRecord(...);
extern "C" int beDataBase_GetRecordInt(beDataBase *, int, const char *);
extern "C" unsigned long long beDataBase_GetRecordBool(beDataBase *, int, const char *);
extern "C" char *beDataBase_GetRecordString(beDataBase *, int, const char *);

extern "C" char DATABASE_2[];
extern "C" char GETDATABASE_2[];
extern "C" char HANBAI[];
extern "C" char KAITORI[];
extern "C" char weapon[];
extern "C" char armor1[];
extern "C" char armor2[];
extern "C" char abChip[];
extern "C" char conItem[];
extern "C" char HP_2[];
extern "C" char MP_2[];
extern "C" char PLAYER[];
extern "C" char GETPEBASEWORK_2[];
extern "C" char GAMERAM_4[];
extern "C" char P2PKOUKAMAGIC_2[];
extern "C" char FIGHTCALC_2[];
extern "C" char Player[];
extern "C" char gatedisc_lua[];
extern "C" char insItem[];
extern "C" char GETPLAYER_2[];
extern "C" char UP[];
extern "C" char GETPLAYER1[];
extern "C" char LEVEL_4[];
extern "C" char BITRITSU[];
extern "C" char GETCOMMON_3[];
extern "C" char BIT_2[];
extern "C" char DIFFICULTY_2[];
extern "C" char XDATA[];
extern "C" char UPCNT_2[];
extern "C" char RECALCPLAYER_2[];
extern "C" char impItem[];
extern "C" char pcTech[];
extern "C" int g_beLua_metaObject[4];
extern "C" int g_beNDMWGameRam_metaObject[4];
extern "C" int g_beNDMWItemWeapon_metaObject[4];
extern "C" int g_beNDMWItemBlueArmor_metaObject[4];
extern "C" int g_beNDMWItemYellowArmor_metaObject[4];
extern "C" int g_beNDMWItemAbilityChip_metaObject[4];
extern "C" int g_beNDMWItemDisk_metaObject[4];
extern "C" int g_beNDMWItemInstant_metaObject[4];
extern "C" int g_beNDMWItemImportant_metaObject[4];
extern "C" int g_beNDMWItemWaza_metaObject[4];

/* Dispatch-only ABI projection of an item: MW's two-word vtable prefix plus 21 slots puts the
 * database selector (vfunc_21) at 92. */
class ItemDatabaseDispatch {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual beDataBase *databaseForStatus(beNDMWStatus *);
};

/* Dispatch-only ABI projection of the system's igMersenneTwisterRandomNumber: genrand is vtable
 * slot 24. */
class RandomNumberDispatch {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void sgenrand(unsigned int seed);
    virtual unsigned int genrand();
};

static inline RandomNumberDispatch *systemRandom(int system) {
    return (RandomNumberDispatch *)((beSystem *)system)->_random;
}

extern "C" beDataBase *beNDMWItemBase_RequestDataBase(beNDMWItemBase *self, beNDMWStatus *status, const char *name);
extern "C" int beNDMWItemBase_GetRecordInt(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
extern "C" unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
extern "C" char *beNDMWItemBase_GetRecordString(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
extern "C" igVec3f beNDMWItemBase_GetRevisionColor(beNDMWItemBase *item);
extern "C" int beNDMWItemRevisionPocketBase_GetPrice(beNDMWItemRevisionPocketBase *self, beNDMWStatus *status, const char *priceKey);
extern "C" int beNDMWItemBase_IndexOfRecNo(igObjectList *items, int recNo);
extern "C" void beNDMWItemRevisionBase_RollRevision(beNDMWItemRevisionBase *self, beNDMWStatus *status, unsigned int level);
extern "C" void beNDMWItemRevisionPocketBase_RollPocket(beNDMWItemRevisionPocketBase *self, beNDMWStatus *status, int level);
extern "C" beDataBase *Gap__Bec__beNDMWItemWeapon__vfunc_21(beNDMWItemWeapon *self, beNDMWStatus *status);
extern "C" void beNDMWItemWeapon_Set(beNDMWItemWeapon *self, int recNo, int pocket, int revision);
extern "C" void beNDMWItemWeapon_SetRandom(beNDMWItemWeapon *self, int recNo, beNDMWStatus *status, int level);
extern "C" int Gap__Bec__beNDMWItemWeapon__vfunc_23(beNDMWItemWeapon *self);
extern "C" void Gap__Bec__beNDMWItemWeapon__vfunc_24(beNDMWItemWeapon *self, int packed);
extern "C" beDataBase *Gap__Bec__beNDMWItemBlueArmor__vfunc_21(beNDMWItemBlueArmor *self, beNDMWStatus *status);
extern "C" void beNDMWItemBlueArmor_Set(beNDMWItemBlueArmor *self, int recNo, int pocket, int revision);
extern "C" void beNDMWItemBlueArmor_SetRandom(beNDMWItemBlueArmor *self, int recNo, beNDMWStatus *status, int level);
extern "C" int Gap__Bec__beNDMWItemBlueArmor__vfunc_23(beNDMWItemBlueArmor *self);
extern "C" void Gap__Bec__beNDMWItemBlueArmor__vfunc_24(beNDMWItemBlueArmor *self, int packed);
extern "C" beDataBase *Gap__Bec__beNDMWItemYellowArmor__vfunc_21(beNDMWItemYellowArmor *self, beNDMWStatus *status);
extern "C" void beNDMWItemYellowArmor_Set(beNDMWItemYellowArmor *self, int recNo, int revision);
extern "C" void beNDMWItemYellowArmor_SetRandom(beNDMWItemYellowArmor *self, int recNo, beNDMWStatus *status, int level);
extern "C" int Gap__Bec__beNDMWItemYellowArmor__vfunc_23(beNDMWItemYellowArmor *self);
extern "C" void Gap__Bec__beNDMWItemYellowArmor__vfunc_24(beNDMWItemYellowArmor *self, int packed);
extern "C" beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *self, beNDMWStatus *status);
extern "C" void beNDMWItemAbilityChip_Set(beNDMWItemAbilityChip *self, int recNo);
extern "C" int Gap__Bec__beNDMWItemAbilityChip__vfunc_23(beNDMWItemAbilityChip *self);
extern "C" void Gap__Bec__beNDMWItemAbilityChip__vfunc_24(beNDMWItemAbilityChip *self, int packed);
extern "C" beDataBase *Gap__Bec__beNDMWItemDisk__vfunc_21(beNDMWItemDisk *self, beNDMWStatus *status);
extern "C" void beNDMWItemDisk_Set(beNDMWItemDisk *self, int recNo);
extern "C" int Gap__Bec__beNDMWItemDisk__vfunc_23(beNDMWItemDisk *self);
extern "C" void Gap__Bec__beNDMWItemDisk__vfunc_24(beNDMWItemDisk *self, int packed);
extern "C" int Gap__Bec__beNDMWItemDisk__vfunc_22(beNDMWItemDisk *self, beNDMWGameRam *gameRam, int playerNo);
extern "C" beDataBase *Gap__Bec__beNDMWItemInstant__vfunc_21(beNDMWItemInstant *self, beNDMWStatus *status);
extern "C" void beNDMWItemInstant_Set(beNDMWItemInstant *self, int recNo);
extern "C" int Gap__Bec__beNDMWItemInstant__vfunc_22(beNDMWItemInstant *self, beNDMWGameRam *gameRam, int playerNo);
extern "C" beDataBase *Gap__Bec__beNDMWItemImportant__vfunc_21(beNDMWItemImportant *self, beNDMWStatus *status);
extern "C" void beNDMWItemImportant_Set(beNDMWItemImportant *self, int recNo);
extern "C" beDataBase *Gap__Bec__beNDMWItemWaza__vfunc_21(beNDMWItemWaza *self, beNDMWStatus *status);
extern "C" void beNDMWItemWaza_Set(beNDMWItemWaza *self, int recNo, int baseNo);
extern "C" int Gap__Bec__beNDMWItemWaza__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemImportant__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemInstant__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemDisk__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemAbilityChip__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemYellowArmor__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemBlueArmor__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemWeapon__vfunc_20(void);

/* Send "DATABASE <name>" / "GETDATABASE" to the status messenger and return the database object it
 * answers with. */
beDataBase *beNDMWItemBase_RequestDataBase(beNDMWItemBase *self, beNDMWStatus *status,
                                           const char *name) {
    void *messenger = (void *)status->_messenger;
    beMessenger_SendNamed(messenger, DATABASE_2, name, 0, GETDATABASE_2);
    return (beDataBase *)beMessenger_GetObject(messenger, 0);
}

int beNDMWItemBase_GetRecordInt(beNDMWItemBase *self, beNDMWStatus *status, const char *key) {
    return beDataBase_GetRecordInt(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                   self->_recNo, key);
}

unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *self, beNDMWStatus *status,
                                                const char *key) {
    return beDataBase_GetRecordBool(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                    self->_recNo, key);
}

char *beNDMWItemBase_GetRecordString(beNDMWItemBase *self, beNDMWStatus *status, const char *key) {
    return beDataBase_GetRecordString(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                      self->_recNo, key);
}

/* Text colour of an item name: grey for chips, disks, consumables and key items and for the three
 * blank equipment records, otherwise by revision from cyan (1-30) through green, yellow and orange
 * to magenta (1000 and above). */
igVec3f beNDMWItemBase_GetRevisionColor(beNDMWItemBase *item) {
    igVec3f color(0.9f, 0.9f, 0.9f);
    int kind = item->_kindNo;

    if (kind == ITEM_KIND_ABILITY_CHIP || kind == ITEM_KIND_DISK || kind == ITEM_KIND_INSTANT ||
        kind == ITEM_KIND_IMPORTANT) {
        return color;
    }
    if ((kind == ITEM_KIND_WEAPON && item->_recNo == 276) ||
        (kind == ITEM_KIND_BLUE_ARMOR && item->_recNo == 31) ||
        (kind == ITEM_KIND_YELLOW_ARMOR && item->_recNo == 44)) {
        return color;
    }
    {
        int revision = ((beNDMWItemRevisionBase *)item)->_revision;
        if (revision >= 1000) {
            color = igVec3f(1.0f, 0.0f, 0.9f);
        } else if (revision >= 501) {
            color = igVec3f(1.0f, 0.6f, 0.1f);
        } else if (revision >= 101) {
            color = igVec3f(0.9f, 0.8f, 0.1f);
        } else if (revision >= 31) {
            color = igVec3f(0.4f, 1.0f, 0.6f);
        } else if (revision > 0) {
            color = igVec3f(0.1f, 0.9f, 1.0f);
        }
    }
    return color;
}

/* Shop price of a revised item: the record's HANBAI (sale) or KAITORI (buy-back) value, plus 100
 * or 25 per revision point, plus a pocket bonus for weapons and blue armor. */
int beNDMWItemRevisionPocketBase_GetPrice(beNDMWItemRevisionPocketBase *self, beNDMWStatus *status,
                                          const char *priceKey) {
    int price;

    if (strcmp(priceKey, HANBAI) == 0) {
        price = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)self, status, HANBAI);
        if (self->_kindNo == ITEM_KIND_YELLOW_ARMOR) {
            price += self->_revision * 100;
        } else if (self->_kindNo == ITEM_KIND_WEAPON || self->_kindNo == ITEM_KIND_BLUE_ARMOR) {
            price += self->_revision * 100;
            int pocketBonus[6] = {0, 500, 1500, 6000, 12000, 24000};
            price += pocketBonus[self->_pocket];
        }
    } else {
        price = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)self, status, KAITORI);
        if (self->_kindNo == ITEM_KIND_YELLOW_ARMOR) {
            price += self->_revision * 25;
        } else if (self->_kindNo == ITEM_KIND_WEAPON || self->_kindNo == ITEM_KIND_BLUE_ARMOR) {
            price += self->_revision * 25;
            int pocketBonus[6] = {0, 250, 750, 3000, 6000, 12000};
            price += pocketBonus[self->_pocket];
        }
    }
    return price;
}

/* Index of the first item in `items` whose record number is `recNo`, or -1. */
int beNDMWItemBase_IndexOfRecNo(igObjectList *items, int recNo) {
    int i;
    beNDMWItemBase **item;
    int count = items->_count;

    i = 0;
    if (0 < count) {
        item = (beNDMWItemBase **)items->_data;
        do {
            if (recNo == (*item)->_recNo) return i;
            i++;
            item++;
        } while (i < count);
    }
    return -1;
}

/* One draw in 6000 gives revision level + 1; the first half of the range gives a random 1..level
 * less a tenth of the first draw, floored at 0; the rest give 0. */
void beNDMWItemRevisionBase_RollRevision(beNDMWItemRevisionBase *self, beNDMWStatus *status,
                                         unsigned int level) {
    int roll = (systemRandom(status->_system)->genrand() % 6000U) + 1;
    int bonus = (systemRandom(status->_system)->genrand() % level) + 1;
    int revision;

    if (roll == 1) {
        revision = level + 1;
    } else if (roll < 3001) {
        revision = bonus - roll / 10;
    } else {
        revision = 0;
    }
    if (revision < 0) revision = 0;
    self->_revision = revision;
}

/* A draw out of 620, shifted down by the level, picks 0 to 5 pockets: each extra pocket halves
 * the odds. */
void beNDMWItemRevisionPocketBase_RollPocket(beNDMWItemRevisionPocketBase *self,
                                             beNDMWStatus *status, int level) {
    int roll = (systemRandom(status->_system)->genrand() % 620U) + 1 - ((level / 10 + 10) / 10);
    int pocket = 1;

    if (roll == 1) {
        pocket = 5;
    } else if (roll < 4) {
        pocket = 4;
    } else if (roll < 8) {
        pocket = 3;
    } else if (roll < 16) {
        pocket = 2;
    } else if (roll < 32) {
        pocket = 1;
    } else {
        pocket = 0;
    }
    self->_pocket = pocket;
}

beDataBase *Gap__Bec__beNDMWItemWeapon__vfunc_21(beNDMWItemWeapon *self, beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, weapon);
}

void beNDMWItemWeapon_Set(beNDMWItemWeapon *self, int recNo, int pocket, int revision) {
    self->_kindNo = ITEM_KIND_WEAPON;
    self->_recNo = recNo;
    self->_isEquip = 0;
    self->_pocket = pocket;
    self->_revision = revision;
}

void beNDMWItemWeapon_SetRandom(beNDMWItemWeapon *self, int recNo, beNDMWStatus *status, int level) {
    beNDMWItemRevisionPocketBase_RollPocket((beNDMWItemRevisionPocketBase *)self, status, level);
    beNDMWItemRevisionBase_RollRevision((beNDMWItemRevisionBase *)self, status, level);
    beNDMWItemWeapon_Set(self, recNo, self->_pocket, self->_revision);
}

/* Packs this item into an inventory word. */
int Gap__Bec__beNDMWItemWeapon__vfunc_23(beNDMWItemWeapon *self) {
    int packed = self->_recNo;
    packed |= self->_isEquip ? ITEM_EQUIPPED_BIT : 0;
    packed |= self->_kindNo << ITEM_KIND_SHIFT;
    packed |= self->_pocket << ITEM_POCKET_SHIFT;
    packed |= self->_revision << ITEM_REVISION_SHIFT;
    return packed;
}

/* Unpacks an inventory word into this item. */
void Gap__Bec__beNDMWItemWeapon__vfunc_24(beNDMWItemWeapon *self, int packed) {
    self->_recNo = packed & ITEM_REC_NO_MASK;
    self->_isEquip = (packed & ITEM_EQUIPPED_BIT) != 0;
    self->_kindNo = (packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK;
    self->_pocket = (packed >> ITEM_POCKET_SHIFT) & ITEM_POCKET_MASK;
    self->_revision = (packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK;
}

beDataBase *Gap__Bec__beNDMWItemBlueArmor__vfunc_21(beNDMWItemBlueArmor *self, beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, armor1);
}

void beNDMWItemBlueArmor_Set(beNDMWItemBlueArmor *self, int recNo, int pocket, int revision) {
    self->_kindNo = ITEM_KIND_BLUE_ARMOR;
    self->_recNo = recNo;
    self->_isEquip = 0;
    self->_pocket = pocket;
    self->_revision = revision;
}

void beNDMWItemBlueArmor_SetRandom(beNDMWItemBlueArmor *self, int recNo, beNDMWStatus *status,
                                   int level) {
    beNDMWItemRevisionPocketBase_RollPocket((beNDMWItemRevisionPocketBase *)self, status, level);
    beNDMWItemRevisionBase_RollRevision((beNDMWItemRevisionBase *)self, status, level);
    beNDMWItemBlueArmor_Set(self, recNo, self->_pocket, self->_revision);
}

/* Packs this item into an inventory word. */
int Gap__Bec__beNDMWItemBlueArmor__vfunc_23(beNDMWItemBlueArmor *self) {
    int packed = self->_recNo;
    packed |= self->_isEquip ? ITEM_EQUIPPED_BIT : 0;
    packed |= self->_kindNo << ITEM_KIND_SHIFT;
    packed |= self->_pocket << ITEM_POCKET_SHIFT;
    packed |= self->_revision << ITEM_REVISION_SHIFT;
    return packed;
}

/* Unpacks an inventory word into this item. */
void Gap__Bec__beNDMWItemBlueArmor__vfunc_24(beNDMWItemBlueArmor *self, int packed) {
    self->_recNo = packed & ITEM_REC_NO_MASK;
    self->_isEquip = (packed & ITEM_EQUIPPED_BIT) != 0;
    self->_kindNo = (packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK;
    self->_pocket = (packed >> ITEM_POCKET_SHIFT) & ITEM_POCKET_MASK;
    self->_revision = (packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK;
}

beDataBase *Gap__Bec__beNDMWItemYellowArmor__vfunc_21(beNDMWItemYellowArmor *self, beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, armor2);
}

void beNDMWItemYellowArmor_Set(beNDMWItemYellowArmor *self, int recNo, int revision) {
    self->_kindNo = ITEM_KIND_YELLOW_ARMOR;
    self->_recNo = recNo;
    self->_isEquip = 0;
    self->_revision = revision;
}

void beNDMWItemYellowArmor_SetRandom(beNDMWItemYellowArmor *self, int recNo, beNDMWStatus *status,
                                     int level) {
    beNDMWItemRevisionBase_RollRevision((beNDMWItemRevisionBase *)self, status, level);
    beNDMWItemYellowArmor_Set(self, recNo, self->_revision);
}

/* Packs this item into an inventory word. */
int Gap__Bec__beNDMWItemYellowArmor__vfunc_23(beNDMWItemYellowArmor *self) {
    int packed = self->_recNo;
    packed |= self->_isEquip ? ITEM_EQUIPPED_BIT : 0;
    packed |= self->_kindNo << ITEM_KIND_SHIFT;
    packed |= self->_revision << ITEM_REVISION_SHIFT;
    return packed;
}

/* Unpacks an inventory word into this item. */
void Gap__Bec__beNDMWItemYellowArmor__vfunc_24(beNDMWItemYellowArmor *self, int packed) {
    self->_recNo = packed & ITEM_REC_NO_MASK;
    self->_isEquip = (packed & ITEM_EQUIPPED_BIT) != 0;
    self->_kindNo = (packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK;
    self->_revision = (packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK;
}

beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *self,
                                                      beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, abChip);
}

void beNDMWItemAbilityChip_Set(beNDMWItemAbilityChip *self, int recNo) {
    self->_kindNo = ITEM_KIND_ABILITY_CHIP;
    self->_recNo = recNo;
    self->_isEquip = 0;
}

/* Packs this item into an inventory word. */
int Gap__Bec__beNDMWItemAbilityChip__vfunc_23(beNDMWItemAbilityChip *self) {
    int packed = self->_recNo;
    packed |= self->_isEquip ? ITEM_EQUIPPED_BIT : 0;
    packed |= self->_kindNo << ITEM_KIND_SHIFT;
    return packed;
}

/* Unpacks an inventory word into this item. */
void Gap__Bec__beNDMWItemAbilityChip__vfunc_24(beNDMWItemAbilityChip *self, int packed) {
    self->_recNo = packed & ITEM_REC_NO_MASK;
    self->_isEquip = (packed & ITEM_EQUIPPED_BIT) != 0;
    self->_kindNo = (packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK;
}

beDataBase *Gap__Bec__beNDMWItemDisk__vfunc_21(beNDMWItemDisk *self, beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, conItem);
}

void beNDMWItemDisk_Set(beNDMWItemDisk *self, int recNo) {
    self->_kindNo = ITEM_KIND_DISK;
    self->_recNo = recNo;
    self->_isEquip = 0;
    self->_kazu = 0;
}

/* Packs this item into an inventory word. */
int Gap__Bec__beNDMWItemDisk__vfunc_23(beNDMWItemDisk *self) {
    int packed = self->_recNo;
    packed |= self->_isEquip ? ITEM_EQUIPPED_BIT : 0;
    packed |= self->_kindNo << ITEM_KIND_SHIFT;
    packed |= self->_kazu << ITEM_DISK_COUNT_SHIFT;
    return packed;
}

/* Unpacks an inventory word into this item. */
void Gap__Bec__beNDMWItemDisk__vfunc_24(beNDMWItemDisk *self, int packed) {
    self->_recNo = packed & ITEM_REC_NO_MASK;
    self->_isEquip = (packed & ITEM_EQUIPPED_BIT) != 0;
    self->_kindNo = (packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK;
    self->_kazu = (packed >> ITEM_DISK_COUNT_SHIFT) & ITEM_DISK_COUNT_MASK;
}

/* Uses a disk on player `playerNo`. Records 0-2 restore HP, 3-5 MP and 9 both, by the record's HP
 * and MP values; 6 may clear the player's poison timer, 7 sends the player's fight calculation a
 * -50 magic effect and 8 runs the gate disc script, the only use that returns 1. */
int Gap__Bec__beNDMWItemDisk__vfunc_22(beNDMWItemDisk *self, beNDMWGameRam *gameRam, int playerNo) {
    int recNo = self->_recNo;

    switch (recNo) {
    case 9: {
        int ram = FUN_00236f80(gameRam->_insight, g_beNDMWGameRam_metaObject[0]);
        beNDMWGameRam_ChangeHp(ram, playerNo, beNDMWItemBase_GetRecordInt((beNDMWItemBase *)self, (beNDMWStatus *)gameRam, HP_2), -1);
        beNDMWGameRam_ChangeMp(ram, playerNo, beNDMWItemBase_GetRecordInt((beNDMWItemBase *)self, (beNDMWStatus *)gameRam, MP_2));
        return 0;
    }
    }
    switch (recNo) {
    case 0: case 1: case 2: {
        int hp = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)self, (beNDMWStatus *)gameRam, HP_2);
        beNDMWGameRam_ChangeHp(FUN_00236f80(gameRam->_insight, g_beNDMWGameRam_metaObject[0]), playerNo, hp, -1);
        return 0;
    }
    }
    switch (recNo) {
    case 3: case 4: case 5: {
        int mp = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)self, (beNDMWStatus *)gameRam, MP_2);
        beNDMWGameRam_ChangeMp(FUN_00236f80(gameRam->_insight, g_beNDMWGameRam_metaObject[0]), playerNo, mp);
        return 0;
    }
    }
    switch (recNo) {
    case 6: {
        int messenger = gameRam->_messenger;
        beMessenger_SendNamed(messenger, PLAYER, 0, playerNo, GETPEBASEWORK_2);
        void *model = beMessenger_GetObject(messenger, 0);
        beNDMWMdlPEBaseInfoWork *work = (beNDMWMdlPEBaseInfoWork *)beMessenger_GetObject(messenger, 1);
        if (FUN_00447b00(work) != 0) {
            int endurance = work->_poisonEndurance;
            if ((8 - endurance) >= (int)(systemRandom(gameRam->_system)->genrand() % 10U)) {
                FUN_00447b40(work, model);
            }
        }
        return 0;
    }
    case 7: {
        int messenger = gameRam->_messenger;
        beMessenger_SelectGroup(messenger, GAMERAM_4);
        beMessenger_AppendString(messenger, P2PKOUKAMAGIC_2);
        beMessenger_AppendInt(messenger, playerNo);
        beMessenger_AppendInt(messenger, playerNo);
        beMessenger_AppendInt(messenger, -50);
        beMessenger_DispatchSelected(messenger, FIGHTCALC_2);
        return 0;
    }
    case 8: {
        int lua = FUN_00236f80(gameRam->_insight, g_beLua_metaObject[0]);
        SYSsetGateStage(Player, playerNo);
        beLua__RunNamedChunk(lua, gatedisc_lua, 0);
        return 1;
    }
    }
    return 0;
}

beDataBase *Gap__Bec__beNDMWItemInstant__vfunc_21(beNDMWItemInstant *self, beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, insItem);
}

void beNDMWItemInstant_Set(beNDMWItemInstant *self, int recNo) {
    self->_recNo = recNo;
    self->_kindNo = ITEM_KIND_INSTANT;
}

/* Uses a consumable on player `playerNo`, by the record's UP value. Record 0 pays bits: a random
 * amount from a band set by the first player's level, raised by its BITRITSU percentage, kept in
 * _value. Records 1-3 add to the player's XDATA; 4-25 add to one UPCNT counter and recalculate the
 * player, the only use that returns 1. */
int Gap__Bec__beNDMWItemInstant__vfunc_22(beNDMWItemInstant *self, beNDMWGameRam *gameRam, int playerNo) {
    unsigned int recNo;
    int leader;
    int level;
    int low;
    int rate;
    int amount;
    igDataList *counters;
    int high;
    int messenger;
    int common;
    int bits;
    int player;
    int up;
    IntProperty *field;
    IntListProperty *upcnt;
    int counter;
    int roll;
    int count;

    messenger = gameRam->_messenger;
    beMessenger_SelectGroup(messenger, GAMERAM_4);
    beMessenger_AppendInt(messenger, playerNo);
    beMessenger_DispatchSelected(messenger, GETPLAYER_2);
    player = (int)beMessenger_GetObject(messenger, 0);
    up = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)self, (beNDMWStatus *)gameRam, UP);
    recNo = self->_recNo;
    switch (recNo) {
    case 0: {
        beMessenger_SendGroup(messenger, GAMERAM_4, GETPLAYER1);
        leader = (int)beMessenger_GetObject(messenger, 0);
        level = ((IntProperty *)igProperty_GetRecord(leader, LEVEL_4))->_value;
        rate = ((IntProperty *)igProperty_GetRecord(leader, BITRITSU))->_value;
        beMessenger_SendGroup(messenger, GAMERAM_4, GETCOMMON_3);
        common = (int)beMessenger_GetObject(messenger, 0);
        bits = ((IntProperty *)igProperty_GetRecord(player, BIT_2))->_value;
        igProperty_GetRecord(common, DIFFICULTY_2);
        if (level < 19) { low = 10; high = 55; }
        else if (level < 39) { low = 55; high = 100; }
        else if (level < 60) { low = 87; high = 195; }
        else if (level < 94) { low = 162; high = 350; }
        else if (level < 108) { low = 232; high = 520; }
        else if (level < 144) { low = 340; high = 700; }
        else if (level < 203) { low = 446; high = 860; }
        else { low = 566; high = 1160; }
        {
            unsigned int draw = systemRandom(gameRam->_system)->genrand() % (unsigned int)(high - low);
            roll = draw + low;
        }
        amount = roll * (rate + 100) / 100;
        field = (IntProperty *)igProperty_GetRecord(player, BIT_2);
        field->_value = bits + amount;
        self->_value = amount;
        break;
    }
    case 1: case 2: case 3: {
        int xdata = ((IntProperty *)igProperty_GetRecord(player, XDATA))->_value;
        field = (IntProperty *)igProperty_GetRecord(player, XDATA);
        field->_value = xdata + up;
        break;
    }
    default:
        break;
    case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25: {
        counter = 0;
        switch (recNo - 4) {
        case 0: case 1: counter = 2; break;
        case 2: case 3: counter = 3; break;
        case 4: case 5: case 6: case 7: counter = 0; break;
        case 8: case 9: counter = 4; break;
        case 10: case 11: counter = 5; break;
        case 12: case 13: counter = 6; break;
        case 14: case 15: counter = 7; break;
        case 16: case 17: counter = 8; break;
        case 18: case 19: counter = 9; break;
        case 20: case 21: counter = 10; break;
        }
        upcnt = (IntListProperty *)igProperty_GetRecordIntList(player, UPCNT_2);
        {
            int current = ((int *)upcnt->_value->_data)[counter];
            count = current + up;
        }
        counters = ((IntListProperty *)igProperty_GetRecordIntList(player, UPCNT_2))->_value;
        if (counters->_count != 0 && counter >= 0 && counter < counters->_count) {
            ((int *)counters->_data)[counter] = count;
        }
        beMessenger_SelectGroup(messenger, GAMERAM_4);
        beMessenger_AppendInt(messenger, playerNo);
        beMessenger_DispatchSelected(messenger, RECALCPLAYER_2);
        return 1;
    }
    }
    return 0;
}

beDataBase *Gap__Bec__beNDMWItemImportant__vfunc_21(beNDMWItemImportant *self, beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, impItem);
}

void beNDMWItemImportant_Set(beNDMWItemImportant *self, int recNo) {
    self->_recNo = recNo;
    self->_kindNo = ITEM_KIND_IMPORTANT;
}

beDataBase *Gap__Bec__beNDMWItemWaza__vfunc_21(beNDMWItemWaza *self, beNDMWStatus *status) {
    return beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, pcTech);
}

void beNDMWItemWaza_Set(beNDMWItemWaza *self, int recNo, int baseNo) {
    self->_recNo = recNo;
    self->_baseNo = baseNo;
    self->_kindNo = ITEM_KIND_WAZA;
    self->_isEquip = 0;
}

int Gap__Bec__beNDMWItemWaza__vfunc_20(void)
{
    return g_beNDMWItemWaza_metaObject[0];
}

int Gap__Bec__beNDMWItemImportant__vfunc_20(void)
{
    return g_beNDMWItemImportant_metaObject[0];
}

int Gap__Bec__beNDMWItemInstant__vfunc_20(void)
{
    return g_beNDMWItemInstant_metaObject[0];
}

int Gap__Bec__beNDMWItemDisk__vfunc_20(void)
{
    return g_beNDMWItemDisk_metaObject[0];
}

int Gap__Bec__beNDMWItemAbilityChip__vfunc_20(void)
{
    return g_beNDMWItemAbilityChip_metaObject[0];
}

int Gap__Bec__beNDMWItemYellowArmor__vfunc_20(void)
{
    return g_beNDMWItemYellowArmor_metaObject[0];
}

int Gap__Bec__beNDMWItemBlueArmor__vfunc_20(void)
{
    return g_beNDMWItemBlueArmor_metaObject[0];
}

int Gap__Bec__beNDMWItemWeapon__vfunc_20(void)
{
    return g_beNDMWItemWeapon_metaObject[0];
}
