#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

/* beNDMWMdlEnemy: the model controller of an enemy Digimon. It answers KIND_ENEMY, registers as an
 * ENEMY receiver, and on GENERATE creates the enemy's info work from the message (database record
 * and HP), asks the enemy database for the record's RARITY and, when it is set, sends SETRAREICON
 * back to the enemy's own info after a delay of 60. */

extern "C" int strcmp(int, int *);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" void *beBaseInfoDataList_Create(...);
extern "C" void beModelCtrl__OnGenerate(...);
extern "C" void *beNDMWMdlEnemyInfoWork_Create(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int beDataBase_GetRecordInt(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_EnqueueSelected(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_PopArgContext(...);
extern "C" int beMessenger_PrepareDelayedSelection(...);
extern "C" int beMessenger_PushArgContext(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int igObject_GetAllocator(...);
extern "C" beModelCtrlInfoRamData *igProperty_FindByName(...);
extern "C" void beNDMWMdlPEBase_OnSequenceChange(void);
extern "C" int KIND_ENEMY[4];
extern "C" int emptyString[4];
extern "C" int ENEMY_3[4];
extern "C" int ONE_5[4];
extern "C" int DATABASE_8[4];
extern "C" int enemy_2[4];
extern "C" int GETDATABASE_8[4];
extern "C" int RARITY[4];
extern "C" int SETRAREICON[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int g_beNDMWMdlEnemy_metaObject[4];

/* Delay before the rare icon request is delivered. */
#define RARE_ICON_DELAY 60

static inline void ReleaseObject(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7fffff) == 0) igObject_Destroy(object);
    }
}

/* Owning stack reference to the new enemy info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

struct DataListSlot {
    static inline void set(beBaseInfoRam *ram, const igSmartPointer<igObject> &list) {
        igObject *held = list.p;
        if (held != 0) held->_refCount = held->_refCount + 1;
        ReleaseObject((igObject *)ram->_dataList);
        ram->_dataList = (int)held;
    }
    static inline void adopt(beBaseInfoRam *ram, igObject *created) { igSmartPointer<igObject> list(created); set(ram, list); }
};

extern "C" int beNDMWMdlEnemy__IsKind(int self, int kind);
extern "C" void beNDMWMdlEnemy__RegisterReceiver(beNDMWMdlEnemy *self, int info, char *unused);
extern "C" void beNDMWMdlEnemy__OnGenerate(beNDMWMdlEnemy *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlEnemy__OnSequenceChange(void);
extern "C" int beNDMWMdlEnemy__GetMeta(void);

int beNDMWMdlEnemy__IsKind(int self, int kind) {
    return strcmp(kind, &KIND_ENEMY[0]) == 0;
}

void beNDMWMdlEnemy__RegisterReceiver(beNDMWMdlEnemy *self, int info, char *unused)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, ((char *)ENEMY_3));
}

void beNDMWMdlEnemy__OnGenerate(beNDMWMdlEnemy *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    beModelCtrlInfoRamData *record;
    int *infoName;
    int rarity;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        int allocator = igObject_GetAllocator(ram);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(allocator);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x68 does) */
        DataListSlot::adopt(ram, created);
    }
    record = igProperty_FindByName((void *)ram->_dataList, g_propertyNameField[0], &ONE_5[0]);
    {
        int allocator = igObject_GetAllocator(self);
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        InfoWorkRef work((igObject *)beNDMWMdlEnemyInfoWork_Create(allocator));
        igObject *held = work.p;
        if (held != 0) held->_refCount = held->_refCount + 1;
        ReleaseObject((igObject *)record->_work);
        record->_work = (int)held;
        if (beMessenger_GetIntCount(self->_messenger) != 0) {
            ((beNDMWMdlEnemyInfoWork *)work.p)->_recNo = beMessenger_GetInt(self->_messenger, 0);
            ((beDataObjInt *)((beNDMWMdlEnemyInfoWork *)work.p)->_mHp)->_data = beMessenger_GetInt(self->_messenger, 1);
            ((beDataObjInt *)((beNDMWMdlEnemyInfoWork *)work.p)->_hp)->_data = beMessenger_GetInt(self->_messenger, 1);
            beMessenger_PushArgContext(self->_messenger);
            beMessenger_SendNamed(self->_messenger, &DATABASE_8[0], &enemy_2[0], 0, &GETDATABASE_8[0]);
            rarity = beDataBase_GetRecordInt(beMessenger_GetObject(self->_messenger, 0), ((beNDMWMdlEnemyInfoWork *)work.p)->_recNo, &RARITY[0]);
            if (rarity != 0) {
                int ramNo = ram->_ramNo;
                infoName = info->_name ? (int *)info->_name : &emptyString[0];
                beMessenger_PrepareDelayedSelection(self->_messenger, &ENEMY_3[0], infoName, ramNo);
                beMessenger_AppendInt(self->_messenger, rarity);
                beMessenger_EnqueueSelected(self->_messenger, &SETRAREICON[0], RARE_ICON_DELAY);
            }
            beMessenger_PopArgContext(self->_messenger);
        }
    }
    beModelCtrl__OnGenerate(self, ram);
}

void beNDMWMdlEnemy__OnSequenceChange(void)
{
    beNDMWMdlPEBase_OnSequenceChange();
}

int beNDMWMdlEnemy__GetMeta(void)
{
    return g_beNDMWMdlEnemy_metaObject[0];
}
