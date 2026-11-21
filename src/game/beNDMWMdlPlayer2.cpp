#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beBaseInfoManagerDispatchView.h"
#include "dw4/game/ndmw/listSet.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer2.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer2InfoWork.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beTargetObj.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include <stdio.h>
#include <string.h>
#include "dw4/game/beDBManager.h"

extern "C" int beNDMWMdlPlayer2_GetMeta(void);
extern "C" unsigned char beNDMWMdlPlayer2_IsKind(int dummy0, int kind);
extern "C" void beNDMWMdlPlayer2_Start(beNDMWMdlPlayer2 *self);
extern "C" char KIND_PLAYER2[];
extern "C" char PLAYER2_2[];
extern "C" void beNDMWMdlPlayer2_RegisterReceiver(beNDMWMdlPlayer2 * p0, int p1, char * p2);
extern "C" char ONE_13[];
extern "C" char GAMERAM_15[];
extern "C" char GETCOMMON_7[];
extern "C" char BKCHIPSTAGE[];
extern "C" char BKCHIPPOS[];
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    igObject *p;
    ValueRef(igObject *o) : p(o) {}
    ~ValueRef() { igObject *o = p; igObject::release(o); }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own references (+0x74 below +0x7c/+0x78), as retail does. */

struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int alloc = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(a));
        /* matching construct: retained, released and stored by hand; through igSmartPointer::operator= this
         * unit's profile leaves the operator an out-of-line call inside the inline */
        igObject *s0 = list.p;
        igObject::ref(s0);
        igObject::release((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
} };
extern "C" void beNDMWMdlPlayer2_OnGenerate(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram);
extern "C" char PLAYER_8[];
extern "C" char NEAR_3[];
extern "C" char SQ_SWON[];
extern "C" char SQ_SWOF[];
extern "C" int text_end_g_000bcaps_lua[4];
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

extern "C" void beNDMWMdlPlayer2_UpdateControl(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram);

/* After the shared igObject slot 23 body, caches the pad manager registered with the insight core
 * (_padManager), found by its class metaObject; the same binding step as the other managers' slot
 * 23. */
void beNDMWMdlPlayer2_Start(beNDMWMdlPlayer2 *self) {
    beBaseInfoManager_Start((beBaseInfoManager *)self);
    self->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
}

unsigned char beNDMWMdlPlayer2_IsKind(int dummy0, int kind) {
    return strcmp((const char *)kind, KIND_PLAYER2) == 0;
}

void beNDMWMdlPlayer2_RegisterReceiver(beNDMWMdlPlayer2 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)p0->_messenger, (beBaseInfoRam *)p1, PLAYER2_2);
}

void beNDMWMdlPlayer2_OnGenerate(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram) {
    igVec3f t;
    beModelCtrlInfoRamData *r;
    beDataObjStringList *s4;
    beDataObjFloatList *s3;
    int s2;
    igStringRef *e;
    int s1;
    RamDataList::Ensure(ram);
    r = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, ONE_13);
    {
        int alloc = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        ValueRef value(beNDMWMdlPlayer2InfoWork_Create(a));
        (igSmartPointer<igObject> &)r->_work = value.p;
    }
    beModelCtrl__OnGenerate((beModelCtrl *)self, ram);
    beMessenger_SendGroup((beMessenger *)self->_messenger, GAMERAM_15, GETCOMMON_7);
    {
        int o = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        s4 = igProperty_GetRecordStringList((igObject *)o, BKCHIPSTAGE);
        s3 = igProperty_GetRecordFloatList((igObject *)o, BKCHIPPOS);
    }
    beSystem *cfg = (beSystem *)self->_system;
    s2 = cfg->_stageName;
    s1 = ram->_ramNo;
    {
        igStringRef name((char *)s2);
        igStringRefList *l = (igStringRefList *)s4->_data;
        int n = l->_count;
        if (n != 0 && s1 >= 0 && s1 < n) {
            e = &((igStringRef *)l->_data)[s1];
            *e = name;
        }
    }
    igMatrix44f_GetTranslation((const float *)((char *)r->_node + 32), t.vec);
    {
        float *v = &t[0];
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 0;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 0] = *v; }
        }
    }
    {
        float *v = &t[1];
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 1;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 1] = *v; }
        }
    }
    {
        float *v = &t[2];
        igFloatList *l = (igFloatList *)s3->_data;
        int n = l->_count;
        if (n != 0) {
            int i = s1 * 3 + 2;
            if (i >= 0 && i < n) { float *d = (float *)l->_data; d[s1 * 3 + 2] = *v; }
        }
    }
}

void beNDMWMdlPlayer2_UpdateControl(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram) {
    beModelCtrlInfoRamData *prop;
    beNDMWMdlPlayer2InfoWork *q;
    float f;
    if (ram->_dataList == 0) {
        int alloc = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int a;
        if (g_useOwnerAllocator != 0) {
            a = alloc;
        } else {
            a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        igObject::ref(s0);
        igObject *old = (igObject *)ram->_dataList;
        igObject::release(old);
        ram->_dataList = (int)s0;
    }
    prop = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, ONE_13);
    q = (beNDMWMdlPlayer2InfoWork *)prop->_work;
    if (q->_timerCount < 10) {
        q->_timerCount = q->_timerCount + 1;
    }
    bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, ram->_ramNo);
    if (beTargetObj_SelectTarget((float *)(prop->_node + 32), PLAYER_8, NEAR_3)) {
        f = beTargetObj_GetTargetDistanceSq();
        if (q->_isPowerOn == 0) {
            if (f < 900.0f) {
                q->_isPowerOn = 1;
                ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, SQ_SWON);
            }
        } else if (!(f <= 900.0f)) {
            q->_isPowerOn = 0;
            ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, SQ_SWOF);
        }
    } else {
        beLua__RunNamedChunk((beLua *)self->_luaManager, (const char *)text_end_g_000bcaps_lua, 0);
    }
}

extern "C" char GENERATE_15[];
extern "C" char REMOVE_6[];
extern "C" char GENESTAGE[];
extern "C" char MODELCTRL_22[];
extern "C" char g_000bcaps_2[];
extern "C" char SQ_ENTR_dP[];
extern "C" char RAISE_2[];
extern "C" char ISRUN_11[];
extern "C" char GETPLAYER_15[];
extern "C" char HP_7[];
extern "C" char DIGIMONNAME_4[];
extern "C" char p_agumon[];
extern "C" char SQ_CMBK[];
extern "C" char BKCHIPDATA_2[];
extern "C" char BIT_8[];
extern "C" char BKCHIPNAME_2[];
extern "C" char EXP_3[];
extern "C" char SQ_EXIT_3[];

/* Element of a float list. */
static inline float floatAt(igFloatList *list, const int &index) { return ((float *)list->_data)[index]; }

/* Field accessors. */
static inline igStringRefList *getData(beDataObjStringList *record) { return (igStringRefList *)record->_data; }
static inline int getRamNo(beBaseInfoRam *ram) { return ram->_ramNo; }

/* Stores a retained copy of value at list[index] when the index is in range, releasing the token it
 * replaces. */
static inline void setStringAt(igStringRefList *list, int index, const igStringRef &value) {
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        char **slot = (char **)list->_data + index;
        retainString(value.p);
        releaseString(*slot);
        *slot = value.p;
    }
}

extern "C" int beNDMWMdlPlayer2_OnPreMessage(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram, const char *command);
int beNDMWMdlPlayer2_OnPreMessage(beNDMWMdlPlayer2 *self, beBaseInfoRam *ram, const char *command)
{
    if (strcmp(command, GENERATE_15) == 0) {
        if (ram->_isRun != 0)
            ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, REMOVE_6);
    } else if (strcmp(command, GENESTAGE) == 0) {
        beMessenger_SendGroup((beMessenger *)self->_messenger, GAMERAM_15, GETCOMMON_7);
        int common = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        igStringRefList *stages = getData(igProperty_GetRecordStringList((igObject *)common, BKCHIPSTAGE));
        igFloatList *positions = (igFloatList *)igProperty_GetRecordFloatList((igObject *)common, BKCHIPPOS)->_data;
        int ramNo = getRamNo(ram);
        if (StringList_CopyRetained(stages, ramNo).p != 0
            && strcmp((const char *)((beSystem *)self->_system)->_stageName, (const char *)StringList_CopyRetained(stages, ramNo).p) == 0) {
            float x = floatAt(positions, ramNo * 3);
            float y = floatAt(positions, ramNo * 3 + 1);
            float z = floatAt(positions, ramNo * 3 + 2);
            float pos[3];
            char sequence[16];
            beMessenger_PrepareDelayedSelection((beMessenger *)self->_messenger, MODELCTRL_22, g_000bcaps_2, getRamNo(ram));
            pos[0] = x;
            pos[1] = y;
            pos[2] = z;
            beMessenger_AppendVec3((beMessenger *)self->_messenger, pos);
            sprintf(sequence, SQ_ENTR_dP, getRamNo(ram) + 1);
            beMessenger_AppendString((beMessenger *)self->_messenger, sequence);
            beMessenger_EnqueueSelected((beMessenger *)self->_messenger, GENERATE_15, 1);
        }
        return 1;
    } else if (strcmp(command, RAISE_2) == 0) {
        RamDataList::Ensure(ram);
        beNDMWMdlPlayer2InfoWork *work = (beNDMWMdlPlayer2InfoWork *)((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, ONE_13))->_work;
        if (work->_timerCount < 10)
            return 1;
        float matrix[16];
        beMessenger_GetMatrix(matrix, (beMessenger *)self->_messenger, 0);
        int percent = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        int hp = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
        bool running = false;
        beMessenger_SendNamed((beMessenger *)self->_messenger, PLAYER_8, 0, getRamNo(ram), ISRUN_11);
        int count = beMessenger_GetBoolCount((beMessenger *)self->_messenger);
        for (int i = 0; i < count; i++) {
            if (beMessenger_GetBool((beMessenger *)self->_messenger, i) == 1) {
                running = true;
                break;
            }
        }
        beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_15);
        beMessenger_AppendInt((beMessenger *)self->_messenger, getRamNo(ram));
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_15);
        int player = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        if (!running) {
            igProperty_GetRecord((igObject *)player, HP_7)->_data = hp;
            const char *digimon = (const char *)igProperty_GetRecordString((igObject *)player, DIGIMONNAME_4)->_data;
            if (*digimon == 0) digimon = p_agumon;
            beMessenger_SelectReceivers((beMessenger *)self->_messenger, MODELCTRL_22, digimon, getRamNo(ram));
            beMessenger_AppendMatrix((beMessenger *)self->_messenger, matrix);
            beMessenger_AppendString((beMessenger *)self->_messenger, SQ_CMBK);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, GENERATE_15);
        }
        beMessenger_SendGroup((beMessenger *)self->_messenger, GAMERAM_15, GETCOMMON_7);
        int common = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        int bitIndex = getRamNo(ram) * 2;
        int *chipData = (int *)((igIntList *)igProperty_GetRecordIntList((igObject *)common, BKCHIPDATA_2)->_data)->_data;
        int bit = chipData[bitIndex];
        bit += igProperty_GetRecord((igObject *)player, BIT_8)->_data;
        igProperty_GetRecord((igObject *)player, BIT_8)->_data = bit;
        {
            igIntList *chips = (igIntList *)igProperty_GetRecordIntList((igObject *)common, BKCHIPDATA_2)->_data;
            ListSet(chips, bitIndex, 0);
        }
        const char *digimon = (const char *)igProperty_GetRecordString((igObject *)player, DIGIMONNAME_4)->_data;
        const char *chipName = (const char *)StringList_CopyRetained(getData(igProperty_GetRecordStringList((igObject *)common, BKCHIPNAME_2)), getRamNo(ram)).p;
        if (strcmp(digimon, chipName) == 0) {
            int expIndex = getRamNo(ram) * 2 + 1;
            chipData = (int *)((igIntList *)igProperty_GetRecordIntList((igObject *)common, BKCHIPDATA_2)->_data)->_data;
            int chipExp = chipData[expIndex];
            int exp = (chipExp * percent) / 100;
            exp += igProperty_GetRecord((igObject *)player, EXP_3)->_data;
            igProperty_GetRecord((igObject *)player, EXP_3)->_data = exp;
            igIntList *chips = (igIntList *)igProperty_GetRecordIntList((igObject *)common, BKCHIPDATA_2)->_data;
            ListSet(chips, expIndex, 0);
        }
        beMessenger_SendDelayedNamed((beMessenger *)self->_messenger, PLAYER2_2, 0, getRamNo(ram), SQ_EXIT_3, 0);
        beMessenger_SendGroup((beMessenger *)self->_messenger, GAMERAM_15, GETCOMMON_7);
        common = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        setStringAt(getData(igProperty_GetRecordStringList((igObject *)common, BKCHIPSTAGE)), getRamNo(ram), igStringRef());
        return 1;
    }
    return 0;
}

int beNDMWMdlPlayer2_GetMeta(void)
{
    return (int)g_beNDMWMdlPlayer2_metaObject;
}
