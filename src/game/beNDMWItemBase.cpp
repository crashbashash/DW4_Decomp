#include "dw4/reflected.h"
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

extern "C" void beMessenger_SendNamed(...);
extern "C" void * beMessenger_GetObject(...);
extern "C" int strcmp(int a, int *b);
extern "C" void Gap__Bec__beNDMWItemWeapon__vfunc_21(int a0, int a1);
extern "C" int Gap__Bec__beNDMWItemWeapon__vfunc_20(void);
extern "C" void Gap__Bec__beNDMWItemBlueArmor__vfunc_21(int a0, int a1);
extern "C" int Gap__Bec__beNDMWItemBlueArmor__vfunc_20(void);
extern "C" void Gap__Bec__beNDMWItemYellowArmor__vfunc_21(int a0, int a1);
extern "C" int Gap__Bec__beNDMWItemYellowArmor__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemAbilityChip__vfunc_20(void);
extern "C" void Gap__Bec__beNDMWItemDisk__vfunc_21(int a0, int a1);
extern "C" int Gap__Bec__beNDMWItemDisk__vfunc_20(void);
extern "C" int FUN_00236f80(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int FUN_003f9c80(...);
extern "C" int FUN_003f9e20(...);
extern "C" int FUN_00447b00(...);
extern "C" int FUN_00447b40(...);
extern "C" int SYSsetGateStage(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" void Gap__Bec__beNDMWItemInstant__vfunc_21(int a0, int a1);
extern "C" void *FUN_003a9250(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" void *igProperty_GetRecord(...);
extern "C" void Gap__Bec__beNDMWItemImportant__vfunc_21(int a0, int a1);
extern "C" void FUN_00448f00(void *arg0, int arg1);
extern "C" void Gap__Bec__beNDMWItemWaza__vfunc_21(int a0, int a1);
extern "C" int Gap__Bec__beNDMWItemWaza__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemImportant__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWItemInstant__vfunc_20(void);
extern "C" char DATABASE_2[];
extern "C" char GETDATABASE_2[];
extern "C" char abChip[];
extern "C" int beDataBase_GetRecordInt(beDataBase *, int, const char *);
extern "C" unsigned long long beDataBase_GetRecordBool(beDataBase *, int, const char *);
extern "C" char *beDataBase_GetRecordString(beDataBase *, int, const char *);
/* Dispatch-only ABI projection. MW's two-word vtable prefix plus 21 slots gives 92. */
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
extern "C" beDataBase *beNDMWItemBase_RequestDataBase(beNDMWItemBase *self, beNDMWStatus *status, const char *name);
extern "C" int beNDMWItemBase_GetRecordInt(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
extern "C" unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
extern "C" char *beNDMWItemBase_GetRecordString(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
extern "C" beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *self, beNDMWStatus *status);
typedef struct A6 { int v[6]; } A6;
extern "C" A6 DAT_004cfe90;
extern "C" A6 DAT_004cfeb0;
extern "C" int DAT_0051d570[];
extern "C" int DAT_0051d578[];
extern "C" int FUN_00447ed0(beNDMWItemRevisionPocketBase *arg0, int arg1, int arg2);
extern "C" int FUN_00448050(igObjectList *arg0, int arg1);
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class Rng { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
 virtual unsigned int draw(); };
extern "C" void FUN_004480a0(beNDMWItemRevisionBase *out, beNDMWStatus *a, unsigned int level);
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual call (slot 24 = genrand) */
class Rnd { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned v24(); };
extern "C" void FUN_00448190(beNDMWItemRevisionPocketBase *out, beNDMWStatus *ctx, int x);
extern "C" char DAT_0051d580[];
extern "C" void FUN_004482c0(beNDMWItemWeapon *arg0, int arg1, int arg2, int arg3);
extern "C" void FUN_004482e0(beNDMWItemWeapon *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Bec__beNDMWItemWeapon__vfunc_23(beNDMWItemWeapon *a);
extern "C" int g_beNDMWItemWeapon_metaObject[4];
extern "C" void Gap__Bec__beNDMWItemWeapon__vfunc_24(beNDMWItemWeapon *self, int packed);
extern "C" char DAT_0051d588[];
extern "C" void FUN_00448410(beNDMWItemBlueArmor *arg0, int arg1, int arg2, int arg3);
extern "C" void FUN_00448430(beNDMWItemBlueArmor *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Bec__beNDMWItemBlueArmor__vfunc_23(beNDMWItemBlueArmor *arg0);
extern "C" int g_beNDMWItemBlueArmor_metaObject[4];
extern "C" void Gap__Bec__beNDMWItemBlueArmor__vfunc_24(beNDMWItemBlueArmor *self, int packed);
extern "C" char DAT_0051d590[];
extern "C" void FUN_00448560(beNDMWItemYellowArmor *arg0, int arg1, int arg2);
extern "C" void FUN_00448580(beNDMWItemYellowArmor *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Bec__beNDMWItemYellowArmor__vfunc_23(beNDMWItemYellowArmor *arg0);
extern "C" int g_beNDMWItemYellowArmor_metaObject[4];
extern "C" void Gap__Bec__beNDMWItemYellowArmor__vfunc_24(beNDMWItemYellowArmor *self, int packed);
extern "C" void FUN_00448660(beNDMWItemAbilityChip *arg0, int arg1);
extern "C" int Gap__Bec__beNDMWItemAbilityChip__vfunc_23(beNDMWItemAbilityChip *arg0);
extern "C" int g_beNDMWItemAbilityChip_metaObject[4];
extern "C" void Gap__Bec__beNDMWItemAbilityChip__vfunc_24(beNDMWItemAbilityChip *self, int packed);
extern "C" char DAT_0051d5a0[];
extern "C" void FUN_00448710(beNDMWItemDisk *arg0, int arg1);
extern "C" int Gap__Bec__beNDMWItemDisk__vfunc_23(beNDMWItemDisk *self);
extern "C" int g_beNDMWItemDisk_metaObject[4];
extern "C" void Gap__Bec__beNDMWItemDisk__vfunc_24(beNDMWItemDisk *self, int packed);
extern "C" int DAT_0051d5a8[4];
extern "C" int DAT_0051d5b0[4];
extern "C" int DAT_0051d5b8[4];
extern "C" int DAT_0051d5c0[4];
extern "C" int DAT_0051d5d0[4];
extern "C" int DAT_0051d5d8[4];
extern "C" int DAT_0051d5e8[4];
extern "C" int DAT_0051d5f8[4];
extern "C" int DAT_0051d600[4];
extern "C" int g_beLua_metaObject[4];
extern "C" int g_beNDMWGameRam_metaObject[4];
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
extern "C" int Gap__Bec__beNDMWItemDisk__vfunc_22(beNDMWItemDisk *arg0, beNDMWGameRam *arg1, int arg2);
extern "C" char DAT_0051d610[];
extern "C" void FUN_00448ad0(beNDMWItemInstant *arg0, int arg1);
extern "C" int DAT_0051d618[4];
extern "C" int DAT_0051d628[4];
extern "C" int DAT_0051d630[4];
extern "C" int DAT_0051d640[4];
extern "C" int DAT_0051d648[4];
extern "C" int DAT_0051d658[4];
extern "C" int DAT_0051d668[4];
extern "C" int DAT_0051d670[4];
extern "C" int DAT_0051d680[4];
extern "C" int DAT_0051d688[4];
extern "C" int DAT_0051d690[4];
/* matching construct: dummy-virtual class so vX() dispatches through vtable slot 22 of the random-source object */
class RandomSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned vX(); };
extern "C" int Gap__Bec__beNDMWItemInstant__vfunc_22(beNDMWItemInstant *arg0, beNDMWGameRam *arg1, int arg2);
extern "C" char DAT_0051d768[];
extern "C" char DAT_0051d770[];
extern "C" void FUN_00448f30(beNDMWItemWaza *arg0, int arg1, int arg2);
extern "C" int g_beNDMWItemWaza_metaObject[4];
extern "C" int g_beNDMWItemImportant_metaObject[4];
extern "C" int g_beNDMWItemInstant_metaObject[4];

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

int FUN_00447ed0(beNDMWItemRevisionPocketBase *arg0, int arg1, int arg2) {
    A6 sp50;
    A6 sp30;
    int var_v0;

    if (strcmp(arg2, DAT_0051d570) == 0) {
        var_v0 = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)arg0, (beNDMWStatus *)arg1, (const char *)DAT_0051d570);
        if (arg0->_kindNo == 2) {
            var_v0 += arg0->_revision * 100;
        } else if (arg0->_kindNo == 0 || arg0->_kindNo == 1) {
            var_v0 += arg0->_revision * 100;
            sp50 = DAT_004cfe90;
            var_v0 += sp50.v[arg0->_pocket];
        }
    } else {
        var_v0 = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)arg0, (beNDMWStatus *)arg1, (const char *)DAT_0051d578);
        if (arg0->_kindNo == 2) {
            var_v0 += arg0->_revision * 25;
        } else if (arg0->_kindNo == 0 || arg0->_kindNo == 1) {
            var_v0 += arg0->_revision * 25;
            sp30 = DAT_004cfeb0;
            var_v0 += sp30.v[arg0->_pocket];
        }
    }
    return var_v0;
}

int FUN_00448050(igObjectList *arg0, int arg1) {
    int i;
    beNDMWItemDisk **p;
    int n = arg0->_count;
    i = 0;
    if (0 < n) {
        p = (beNDMWItemDisk **)arg0->_data;
        do {
            if (arg1 == (*p)->_recNo) return i;
            i++;
            p++;
        } while (i < n);
    }
    return -1;
}

void FUN_004480a0(beNDMWItemRevisionBase *out, beNDMWStatus *a, unsigned int level) {
    int first = (((Rng *)((beSystem *)a->_system)->_random)->draw() % 6000U) + 1;
    int second = (((Rng *)((beSystem *)a->_system)->_random)->draw() % level) + 1;
    int v;
    if (first == 1) {
        v = level + 1;
    } else if (first < 3001) {
        v = second - first / 10;
    } else {
        v = 0;
    }
    if (v < 0) v = 0;
    out->_revision = v;
}

void FUN_00448190(beNDMWItemRevisionPocketBase *out, beNDMWStatus *ctx, int x) {
    int v = (((Rnd *)((beSystem *)ctx->_system)->_random)->v24() % 620U) + 1 - ((x / 10 + 10) / 10);
    int r = 1;
    if (v == 1) {
        r = 5;
    } else if (v < 4) {
        r = 4;
    } else if (v < 8) {
        r = 3;
    } else if (v < 16) {
        r = 2;
    } else if (v < 32) {
        r = 1;
    } else {
        r = 0;
    }
    out->_pocket = r;
}

void Gap__Bec__beNDMWItemWeapon__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase((beNDMWItemBase *)a0, (beNDMWStatus *)a1, (const char *)DAT_0051d580);
}

void FUN_004482c0(beNDMWItemWeapon *arg0, int arg1, int arg2, int arg3) {
    arg0->_kindNo = 0;
    arg0->_recNo = arg1;
    arg0->_isEquip = 0;
    arg0->_pocket = arg2;
    arg0->_revision = arg3;
}

void FUN_004482e0(beNDMWItemWeapon *arg0, int arg1, int arg2, int arg3) {
    FUN_00448190((beNDMWItemRevisionPocketBase *)arg0, (beNDMWStatus *)arg2, arg3);
    FUN_004480a0((beNDMWItemRevisionBase *)arg0, (beNDMWStatus *)arg2, (unsigned int)arg3);
    FUN_004482c0(arg0, arg1, arg0->_pocket, arg0->_revision);
}

int Gap__Bec__beNDMWItemWeapon__vfunc_23(beNDMWItemWeapon *a) {
    int r = a->_recNo;
    r |= a->_isEquip ? 0x400 : 0;
    r |= a->_kindNo << 12;
    r |= a->_pocket << 16;
    r |= a->_revision << 20;
    return r;
}

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record number, bit 10
 * equipped flag (a byte store), bits 12-15 item kind. A weapon adds two fields above that: bits
 * 16-19 the pocket and bits 20-30 the revision. */









/* Unpacks an inventory word into this item's reflected fields. */
void Gap__Bec__beNDMWItemWeapon__vfunc_24(beNDMWItemWeapon *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_pocket = (int) ((packed >> ITEM_POCKET_SHIFT) & ITEM_POCKET_MASK);
    self->_revision = (int) ((packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK);
}

void Gap__Bec__beNDMWItemBlueArmor__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase((beNDMWItemBase *)a0, (beNDMWStatus *)a1, (const char *)DAT_0051d588);
}

void FUN_00448410(beNDMWItemBlueArmor *arg0, int arg1, int arg2, int arg3) {
    arg0->_kindNo = 1;
    arg0->_recNo = arg1;
    arg0->_isEquip = 0;
    arg0->_pocket = arg2;
    arg0->_revision = arg3;
}

void FUN_00448430(beNDMWItemBlueArmor *arg0, int arg1, int arg2, int arg3) {
    FUN_00448190((beNDMWItemRevisionPocketBase *)arg0, (beNDMWStatus *)arg2, arg3);
    FUN_004480a0((beNDMWItemRevisionBase *)arg0, (beNDMWStatus *)arg2, (unsigned int)arg3);
    FUN_00448410(arg0, arg1, arg0->_pocket, arg0->_revision);
}

int Gap__Bec__beNDMWItemBlueArmor__vfunc_23(beNDMWItemBlueArmor *arg0) {
    int v;
    int r = arg0->_recNo;
    if (arg0->_isEquip != 0) { v = 0x400; } else { v = 0; ; }
    r |= v;
    r |= arg0->_kindNo << 0xC;
    r |= arg0->_pocket << 0x10;
    r |= arg0->_revision << 0x14;
    return r;
}

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record number, bit 10
 * equipped flag (a byte store), bits 12-15 item kind. Blue armor adds two fields above that: bits
 * 16-19 the pocket and bits 20-30 the revision. */









/* Unpacks an inventory word into this item's reflected fields. */
void Gap__Bec__beNDMWItemBlueArmor__vfunc_24(beNDMWItemBlueArmor *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_pocket = (int) ((packed >> ITEM_POCKET_SHIFT) & ITEM_POCKET_MASK);
    self->_revision = (int) ((packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK);
}

void Gap__Bec__beNDMWItemYellowArmor__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase((beNDMWItemBase *)a0, (beNDMWStatus *)a1, (const char *)DAT_0051d590);
}

void FUN_00448560(beNDMWItemYellowArmor *arg0, int arg1, int arg2) {
    arg0->_kindNo = 2;
    arg0->_recNo = arg1;
    arg0->_isEquip = 0;
    arg0->_revision = arg2;
}

void FUN_00448580(beNDMWItemYellowArmor *arg0, int arg1, int arg2, int arg3) {
    FUN_004480a0((beNDMWItemRevisionBase *)arg0, (beNDMWStatus *)arg2, (unsigned int)arg3);
    FUN_00448560(arg0, arg1, arg0->_revision);
}

int Gap__Bec__beNDMWItemYellowArmor__vfunc_23(beNDMWItemYellowArmor *arg0) {
    int v;
    int r = arg0->_recNo;
    if (arg0->_isEquip != 0) { v = 0x400; } else { v = 0; ; }
    r |= v;
    r |= arg0->_kindNo << 0xC;
    r |= arg0->_revision << 0x14;
    return r;
}

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record number, bit 10
 * equipped flag, bits 12-15 item kind, and one subclass-specific field above that. The disk folder
 * stores its entries as (count << 16) | (0x4000 + type). */







/* Unpack an inventory word into this item's fields.  An armor's extra field is its _revision. */
void Gap__Bec__beNDMWItemYellowArmor__vfunc_24(beNDMWItemYellowArmor *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_revision = (int) ((packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK);
}

/* The ability-chip item's database is the "abChip" table. */
beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *self,
                                                      beNDMWStatus *status) {
    beDataBase *result = beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, abChip);


    return result;
}

void FUN_00448660(beNDMWItemAbilityChip *arg0, int arg1) {
    arg0->_kindNo = 3;
    arg0->_recNo = arg1;
    arg0->_isEquip = 0;
}

int Gap__Bec__beNDMWItemAbilityChip__vfunc_23(beNDMWItemAbilityChip *arg0) {
    int a = arg0->_recNo;
    int v;
    if (arg0->_isEquip != 0) {
        v = 0x400;
    } else {
        v = 0;
    }
    a = a | v;
    a = a | (arg0->_kindNo << 0xC);
    return a;
}

/* Unpacks a packed item word into the reflected fields: bits 0-9 are the record number (_recNo),
 * bit 10 the equipped flag (_isEquip) and bits 12-15 the kind number (_kindNo). The sibling
 * beNDMWItem* classes (Weapon, Disk, ...) share the same unpacking. */
void Gap__Bec__beNDMWItemAbilityChip__vfunc_24(beNDMWItemAbilityChip *self, int packed) {
    self->_recNo = (int) (packed & 0x3FF);
    self->_isEquip = (char) ((packed & 0x400) != 0);
    self->_kindNo = (int) ((packed >> 0xC) & 0xF);
}

void Gap__Bec__beNDMWItemDisk__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase((beNDMWItemBase *)a0, (beNDMWStatus *)a1, (const char *)DAT_0051d5a0);
}

void FUN_00448710(beNDMWItemDisk *arg0, int arg1) {
    arg0->_kindNo = 4;
    arg0->_recNo = arg1;
    arg0->_isEquip = 0;
    arg0->_kazu = 0;
}

int Gap__Bec__beNDMWItemDisk__vfunc_23(beNDMWItemDisk *self) {
    int packed = self->_recNo;
    packed |= self->_isEquip ? 0x400 : 0;
    packed |= self->_kindNo << 12;
    packed |= self->_kazu << 16;
    return packed;
}

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record number, bit 10
 * equipped flag, bits 12-15 item kind, and one subclass-specific field above that. The disk folder
 * stores its entries as (count << 16) | (0x4000 + type). */







/* Unpack an inventory word into this item's fields.  A disk's extra field is its stack count (_kazu). */
void Gap__Bec__beNDMWItemDisk__vfunc_24(beNDMWItemDisk *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_kazu = (int) ((packed >> ITEM_DISK_COUNT_SHIFT) & ITEM_DISK_COUNT_MASK);
}

int Gap__Bec__beNDMWItemDisk__vfunc_22(beNDMWItemDisk *arg0, beNDMWGameRam *arg1, int arg2) {
    int v = arg0->_recNo;
    switch (v) {
    case 9: {
        int s3 = FUN_00236f80(arg1->_insight, g_beNDMWGameRam_metaObject[0]);
        FUN_003f9c80(s3, arg2, beNDMWItemBase_GetRecordInt((beNDMWItemBase *)arg0, (beNDMWStatus *)arg1, (const char *)&DAT_0051d5a8[0]), -1);
        FUN_003f9e20(s3, arg2, beNDMWItemBase_GetRecordInt((beNDMWItemBase *)arg0, (beNDMWStatus *)arg1, (const char *)&DAT_0051d5b0[0]));
        return 0;
    }
    }
    switch (v) {
    case 0: case 1: case 2: {
        int r = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)arg0, (beNDMWStatus *)arg1, (const char *)&DAT_0051d5a8[0]);
        FUN_003f9c80(FUN_00236f80(arg1->_insight, g_beNDMWGameRam_metaObject[0]), arg2, r, -1);
        return 0;
    }
    }
    switch (v) {
    case 3: case 4: case 5: {
        int r = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)arg0, (beNDMWStatus *)arg1, (const char *)&DAT_0051d5b0[0]);
        FUN_003f9e20(FUN_00236f80(arg1->_insight, g_beNDMWGameRam_metaObject[0]), arg2, r);
        return 0;
    }
    }
    switch (v) {
    case 6: {
        int s0 = arg1->_messenger;
        beMessenger_SendNamed(s0, &DAT_0051d5b8[0], 0, arg2, &DAT_0051d5c0[0]);
        void *t1 = beMessenger_GetObject(s0, 0);
        beNDMWMdlPEBaseInfoWork *t0 = (beNDMWMdlPEBaseInfoWork *)beMessenger_GetObject(s0, 1);
        if (FUN_00447b00(t0) != 0) {
            int a1 = t0->_poisonEndurance;
            DW4VC_96_1 *a0 = (DW4VC_96_1 *)(*(int *)((char *)(arg1->_system) + 48));
            if ((8 - a1) >= (int)(a0->vX(a1) % 10U)) {
                FUN_00447b40(t0, t1);
            }
        }
        return 0;
    }
    case 7: {
        int s1 = arg1->_messenger;
        beMessenger_SelectGroup(s1, &DAT_0051d5d0[0]);
        beMessenger_AppendString(s1, &DAT_0051d5d8[0]);
        beMessenger_AppendInt(s1, arg2);
        beMessenger_AppendInt(s1, arg2);
        beMessenger_AppendInt(s1, -0x32);
        beMessenger_DispatchSelected(s1, &DAT_0051d5e8[0]);
        return 0;
    }
    case 8: {
        int s1 = FUN_00236f80(arg1->_insight, g_beLua_metaObject[0]);
        SYSsetGateStage(&DAT_0051d5f8[0], arg2);
        beLua__RunNamedChunk(s1, &DAT_0051d600[0], 0);
        return 1;
    }
    }
    return 0;
}

void Gap__Bec__beNDMWItemInstant__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase((beNDMWItemBase *)a0, (beNDMWStatus *)a1, (const char *)DAT_0051d610);
}

void FUN_00448ad0(beNDMWItemInstant *arg0, int arg1) {
    arg0->_recNo = arg1;
    arg0->_kindNo = 5;
}

int Gap__Bec__beNDMWItemInstant__vfunc_22(beNDMWItemInstant *arg0, beNDMWGameRam *arg1, int arg2) {
    unsigned v;
    int obj;
    int lvl;
    int lo;
    int dmg;
    int add;
    igDataList *lst;
    int hi;
    int s3;
    int cur;
    int s2;
    int s1;
    void *rec;
    int idx;
    int a2;
    int off;
    int val;
    s3 = arg1->_messenger;
    beMessenger_SelectGroup(s3, &DAT_0051d5d0[0]);
    beMessenger_AppendInt(s3, arg2);
    beMessenger_DispatchSelected(s3, &DAT_0051d618[0]);
    s2 = (int)beMessenger_GetObject(s3, 0);
    s1 = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)arg0, (beNDMWStatus *)arg1, (const char *)&DAT_0051d628[0]);
    v = arg0->_recNo;
    switch (v) {
    case 0: {
        beMessenger_SendGroup(s3, &DAT_0051d5d0[0], &DAT_0051d630[0]);
        obj = (int)beMessenger_GetObject(s3, 0);
        lvl = *(int *)((char *)igProperty_GetRecord(obj, &DAT_0051d640[0]) + 12);
        dmg = *(int *)((char *)igProperty_GetRecord(obj, &DAT_0051d648[0]) + 12);
        beMessenger_SendGroup(s3, &DAT_0051d5d0[0], &DAT_0051d658[0]);
        s3 = (int)beMessenger_GetObject(s3, 0);
        cur = *(int *)((char *)igProperty_GetRecord(s2, &DAT_0051d668[0]) + 12);
        igProperty_GetRecord(s3, &DAT_0051d670[0]);
        if (lvl < 0x13) { lo = 0xA; hi = 0x37; }
        else if (lvl < 0x27) { lo = 0x37; hi = 0x64; }
        else if (lvl < 0x3C) { lo = 0x57; hi = 0xC3; }
        else if (lvl < 0x5E) { lo = 0xA2; hi = 0x15E; }
        else if (lvl < 0x6C) { lo = 0xE8; hi = 0x208; }
        else if (lvl < 0x90) { lo = 0x154; hi = 0x2BC; }
        else if (lvl < 0xCB) { lo = 0x1BE; hi = 0x35C; }
        else { lo = 0x236; hi = 0x488; }
        { unsigned r = ((RandomSource *)((beSystem *)arg1->_system)->_random)->vX() % (unsigned)(hi - lo); a2 = r + lo; }
        add = a2 * (dmg + 100) / 100;
        rec = igProperty_GetRecord(s2, &DAT_0051d668[0]);
        *(int *)((char *)rec + 12) = cur + add;
        arg0->_value = add;
        break;
    }
    case 1: case 2: case 3: {
        int c = *(int *)((char *)igProperty_GetRecord(s2, &DAT_0051d680[0]) + 12);
        rec = igProperty_GetRecord(s2, &DAT_0051d680[0]);
        *(int *)((char *)rec + 12) = c + s1;
        break;
    }
    default:
        break;
    case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25: {
        idx = 0;
        switch (v - 4) {
        case 0: case 1: idx = 2; break;
        case 2: case 3: idx = 3; break;
        case 4: case 5: case 6: case 7: idx = 0; break;
        case 8: case 9: idx = 4; break;
        case 10: case 11: idx = 5; break;
        case 12: case 13: idx = 6; break;
        case 14: case 15: idx = 7; break;
        case 16: case 17: idx = 8; break;
        case 18: case 19: idx = 9; break;
        case 20: case 21: idx = 10; break;
        }
        rec = FUN_003a9250(s2, &DAT_0051d688[0]);
        off = idx * 4;
        { int el = *(int *)(((igDataList *)*(int *)((char *)rec + 12))->_data + off); val = el + s1; }
        lst = (igDataList *)*(void **)((char *)FUN_003a9250(s2, &DAT_0051d688[0]) + 12);
        if (lst->_count != 0 && idx >= 0 && idx < lst->_count) {
            *(int *)(lst->_data + off) = val;
        }
        beMessenger_SelectGroup(s3, &DAT_0051d5d0[0]);
        beMessenger_AppendInt(s3, arg2);
        beMessenger_DispatchSelected(s3, &DAT_0051d690[0]);
        return 1;
    }
    }
    return 0;
}

void Gap__Bec__beNDMWItemImportant__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase((beNDMWItemBase *)a0, (beNDMWStatus *)a1, (const char *)DAT_0051d768);
}

void FUN_00448f00(void *arg0, int arg1) {
    *(int *)((char *)arg0 + 12) = arg1;
    *(int *)((char *)arg0 + 8) = 6;
}

void Gap__Bec__beNDMWItemWaza__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase((beNDMWItemBase *)a0, (beNDMWStatus *)a1, (const char *)DAT_0051d770);
}

void FUN_00448f30(beNDMWItemWaza *arg0, int arg1, int arg2) {
    arg0->_recNo = arg1;
    arg0->_baseNo = arg2;
    arg0->_kindNo = 9;
    arg0->_isEquip = 0;
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

