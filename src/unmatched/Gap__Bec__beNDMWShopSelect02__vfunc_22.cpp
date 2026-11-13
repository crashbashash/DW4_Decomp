/* Matches retail only with the same build settings as the neighbouring ShopSelect00/A0/B0 vfunc_22
 * units: the content-pinned alternate compiler with -O3,p; an 0x0043dc10 entry is needed in both
 * tables. Matching constructs: `a` is volatile (the retail ref lives in a stack slot that is
 * stored and reloaded); the loop keeps explicit p/off induction variables; the declaration order
 * fixes the saved-register assignment. */
#include "dw4/reflected.h"
typedef struct QTbl { int *v[4]; } __attribute__((aligned(16))) QTbl;
extern "C" {
extern QTbl DAT_004cfac0;
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringList_AppendRetained(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beNDMWWindow_RunMessageScript(...);
extern int DAT_0051c4a0[4];
extern int DAT_0051c4e0[4];
extern int DAT_0051c4e8[4];
extern int DAT_0051c4f0[4];
extern int DAT_0051c4f8[4];
extern int DAT_0051c500[4];
extern int DAT_0051c508[4];
extern int DAT_0051c518[4];
extern int DAT_0051c520[4];
extern int DAT_0051c530[4];
extern int DAT_0051c540[4];
extern int DAT_0051c548[4];
extern int DAT_0051c558[4];
extern int DAT_0051c560[4];
extern int DAT_0051c570[4];
extern int DAT_0051c580[4];
extern int DAT_0051c588[4];
extern int DAT_0051c598[4];
extern int DAT_00586f20[4];
int beMessenger_SelectGroup(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SendNamed(...);
int igProperty_GetRecordByte(...);
int igProperty_GetRecordFolder(...);
int igProperty_GetRecord(...);
int beDataBase_GetRecordString(...);
int beNDMWWindow_QueueText(...);
int beNDMWWindow_QueueObjectText(...);
int igObject_Destroy(...);
}
/* matching construct: inline helper struct reproduces the retail string-pool intern/release sequences */
struct Str { static inline int intern(int *s) {
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool)
                pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = StringPool_Intern(DAT_00586f20[0], s);
    }
    return ref;
}
static inline void release(int ref) {
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
} };
extern "C" void Gap__Bec__beNDMWShopSelect02__vfunc_22(beNDMWShopSelect02 *arg0);
void Gap__Bec__beNDMWShopSelect02__vfunc_22(beNDMWShopSelect02 *arg0) {
    volatile int a;
    int b;
    int slot1;
    int slot2;
    int slot3;
    int slot4;
    int slot5;
    int slot6;
    int slot7;
    int slot8;
    int slot9;
    int slot10;
    int slot11;
    int slot12;
    int slot13;
    int slot14;
    int slot15;
    int slot16;
    int slot17;
    int slot18;
    QTbl tbl;
    int i;
    int obj;
    int off;
    int **p;
    int pno;
    igIntList *lst;
    int pool;
    int ref;
    int old;
    igIntList *fld;
    igObject *tt;
    switch (arg0->_entCode) {
    case -1:
        tbl = DAT_004cfac0;
        p = (int **)&tbl;
        lst = (igIntList *)arg0->_playerNoList;
        if (0 < lst->_count) {
        i = 0;
        off = 0;
        do {
            pno = *(int *)(lst->_data + off);
            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c500[0]);
            beMessenger_AppendInt(arg0->_messenger, pno);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c508[0]);
            obj = beMessenger_GetObject(arg0->_messenger, 0);
            igProperty_GetRecordByte(obj, &DAT_0051c518[0]);
            fld = (igIntList *)*(int *)(igProperty_GetRecordFolder(obj, &DAT_0051c520[0]) + 12);
            if (fld->_count > 0) {
                a = **(int **)&fld->_data;
                tt = (igObject *)a;
                if (tt) tt->_refCount = tt->_refCount + 1;
                b = a;
                tt = (igObject *)b;
                if (tt) tt->_refCount = tt->_refCount + 1;
                beNDMWWindow_QueueObjectText(arg0, &DAT_0051c530[0], (int)*p, (int *)&b, &DAT_0051c540[0]);
                tt = (igObject *)b;
                if (tt) {
                    tt->_refCount = tt->_refCount - 1;
                    tt = (igObject *)b;
                    if (((unsigned long long)((long long)(int)tt->_refCount << 0x29) >> 0x29) == 0)
                        igObject_Destroy(tt);
                }
                tt = (igObject *)a;
                if (tt) {
                    tt->_refCount = tt->_refCount - 1;
                    if (((unsigned long long)((long long)(int)tt->_refCount << 0x29) >> 0x29) == 0)
                        igObject_Destroy(tt);
                }
            }
            beMessenger_SendNamed(arg0->_messenger, &DAT_0051c548[0], &DAT_0051c558[0], 0, &DAT_0051c560[0]);
            beNDMWWindow_QueueText(arg0, &DAT_0051c588[0], (int)*p, beDataBase_GetRecordString(beMessenger_GetObject(arg0->_messenger, 0), *(int *)(igProperty_GetRecord(obj, &DAT_0051c570[0]) + 12), &DAT_0051c580[0]), &DAT_0051c540[0]);
            lst = (igIntList *)arg0->_playerNoList;
            i++;
            off += 4;
            p++;
        } while (i < lst->_count);
        }
        arg0->_selectMax = ((igIntList *)arg0->_playerNoList)->_count;
        break;
    case 1262:
    case 1268:
    case 2003:
    case 2005:
    case 2008:
        slot1 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot1);
        Str::release(slot1);
        slot2 = Str::intern(&DAT_0051c4e0[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot2);
        Str::release(slot2);
        slot3 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot3);
        Str::release(slot3);
        slot4 = Str::intern(&DAT_0051c4e8[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot4);
        Str::release(slot4);
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], arg0->_entCode);
        arg0->_selectMax = 2;
        break;
    case 2:
    case 3:
    case 4:
        arg0->_selectMax = 4;
        slot5 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot5);
        Str::release(slot5);
        slot6 = Str::intern(&DAT_0051c4e0[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot6);
        Str::release(slot6);
        slot7 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot7);
        Str::release(slot7);
        slot8 = Str::intern(&DAT_0051c4e8[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot8);
        Str::release(slot8);
        slot9 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot9);
        Str::release(slot9);
        slot10 = Str::intern(&DAT_0051c4f0[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot10);
        Str::release(slot10);
        slot11 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot11);
        Str::release(slot11);
        slot12 = Str::intern(&DAT_0051c4f8[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot12);
        Str::release(slot12);
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x7EE);
        break;
    case 1:
        arg0->_selectMax = 3;
        slot13 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot13);
        Str::release(slot13);
        slot14 = Str::intern(&DAT_0051c4e0[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot14);
        Str::release(slot14);
        slot15 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot15);
        Str::release(slot15);
        slot16 = Str::intern(&DAT_0051c4e8[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot16);
        Str::release(slot16);
        slot17 = Str::intern(&DAT_0051c530[0]);
        StringList_AppendRetained(arg0->_textCloseTypeList, &slot17);
        Str::release(slot17);
        slot18 = Str::intern(&DAT_0051c4f0[0]);
        StringList_AppendRetained(arg0->_textCloseNameList, &slot18);
        Str::release(slot18);
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x7F2);
        break;
    }
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool)
            pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    ref = StringPool_Intern(DAT_00586f20[0], &DAT_0051c598[0]);
    old = arg0->_infoName;
    Str::release(old);
    arg0->_infoName = ref;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    if (arg0->_entCode == 0x7D3) {
        arg0->_isNoCancel = 1;
        return;
    }
    arg0->_isNoCancel = 0;
}
