#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beDataBase.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/ndmw/beNDMWMdlEnemy.h"
#include "dw4/game/ndmw/beNDMWMdlEnemyInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlPEBase.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include <string.h>
#include "dw4/support/emptyString.h"

/* beNDMWMdlEnemy: the model controller of an enemy Digimon. It answers KIND_ENEMY, registers as an
 * ENEMY receiver, and on GENERATE creates the enemy's info work from the message (database record
 * and HP), asks the enemy database for the record's RARITY and, when it is set, sends SETRAREICON
 * back to the enemy's own info after a delay of 60. */

extern "C" int KIND_ENEMY[4];
extern "C" int ENEMY_3[4];
extern "C" int DATABASE_8[4];
extern "C" int enemy_2[4];
extern "C" int GETDATABASE_8[4];
extern "C" int RARITY[4];
extern "C" int SETRAREICON[4];

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

extern "C" unsigned char beNDMWMdlEnemy_IsKind(int self, int kind);
extern "C" void beNDMWMdlEnemy_RegisterReceiver(beNDMWMdlEnemy *self, int info, char *unused);
extern "C" void beNDMWMdlEnemy_OnGenerate(beNDMWMdlEnemy *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlEnemy_OnSequenceChange(beNDMWMdlEnemy *self, beBaseInfoRam *ram);
extern "C" int beNDMWMdlEnemy__GetMeta(void);

#pragma push
#pragma readonly_strings on

unsigned char beNDMWMdlEnemy_IsKind(int self, int kind) {
    return strcmp((const char *)kind, (const char *)KIND_ENEMY) == 0;
}

void beNDMWMdlEnemy_RegisterReceiver(beNDMWMdlEnemy *self, int info, char *unused)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, (const char *)ENEMY_3);
}

void beNDMWMdlEnemy_OnGenerate(beNDMWMdlEnemy *self, beBaseInfoRam *ram) {
    beBaseInfo *info;
    beModelCtrlInfoRamData *record;
    const char *infoName;
    int rarity;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        igMemoryPoolView *allocator = ((Gap::Core::igObject *)ram)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        igObject *created = beBaseInfoDataList_Create((int)allocator);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x68 does) */
        DataListSlot::adopt(ram, created);
    }
    record = (beModelCtrlInfoRamData *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, "ONE");
    {
        igMemoryPoolView *allocator = ((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        InfoWorkRef work(beNDMWMdlEnemyInfoWork_Create((int)allocator));
        igObject *held = work.p;
        if (held != 0) held->_refCount = held->_refCount + 1;
        ReleaseObject((igObject *)record->_work);
        record->_work = (int)held;
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) != 0) {
            ((beNDMWMdlEnemyInfoWork *)work.p)->_recNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            ((beDataObjInt *)((beNDMWMdlEnemyInfoWork *)work.p)->_mHp)->_data = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            ((beDataObjInt *)((beNDMWMdlEnemyInfoWork *)work.p)->_hp)->_data = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            beMessenger_PushArgContext((beMessenger *)self->_messenger);
            beMessenger_SendNamed((beMessenger *)self->_messenger, (const char *)DATABASE_8, (const char *)enemy_2, 0, (const char *)GETDATABASE_8);
            rarity = beDataBase_GetRecordInt((beDataBase *)beMessenger_GetObject((beMessenger *)self->_messenger, 0), ((beNDMWMdlEnemyInfoWork *)work.p)->_recNo, (const char *)RARITY);
            if (rarity != 0) {
                int ramNo = ram->_ramNo;
                infoName = info->_name ? (const char *)info->_name : (const char *)emptyString;
                beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, (const char *)ENEMY_3, infoName, ramNo);
                beMessenger_AppendInt((beMessenger *)self->_messenger, rarity);
                beMessenger_EnqueueSelected((beMessenger *)self->_messenger, (const char *)SETRAREICON, RARE_ICON_DELAY);
            }
            beMessenger_PopArgContext((beMessenger *)self->_messenger);
        }
    }
    beModelCtrl__OnGenerate((beModelCtrl *)self, ram);
}

void beNDMWMdlEnemy_OnSequenceChange(beNDMWMdlEnemy *self, beBaseInfoRam *ram)
{
    beNDMWMdlPEBase_OnSequenceChange((beNDMWMdlPEBase *)self, ram);
}

int beNDMWMdlEnemy__GetMeta(void)
{
    return (int)g_beNDMWMdlEnemy_metaObject;
}

#pragma pop
