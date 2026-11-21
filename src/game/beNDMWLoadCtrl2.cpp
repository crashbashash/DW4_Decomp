#include "dw4/support/reflected.h"
#include "dw4/game/ndmw/beNDMWDegiData.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2CommonIntf.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2MesWin.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2TextOrder.h"
#include "dw4/game/ndmw/beNDMWMcUtilCtrl.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/be.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beBaseInfoRam.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beFont.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/ndmw/beNDMWItemAbilityChip.h"
#include "dw4/game/ndmw/beNDMWItemBlueArmor.h"
#include "dw4/game/ndmw/beNDMWItemDisk.h"
#include "dw4/game/ndmw/beNDMWItemWeapon.h"
#include "dw4/game/ndmw/beNDMWItemYellowArmor.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2CtrlData.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2Info.h"
#include "dw4/game/ndmw/beNDMWLoadSavePlWork.h"
#include "dw4/game/ndmw/beNDMWLoadSlotPlayer.h"
#include "dw4/game/ndmw/beNDMWMcSlotGC.h"
#include "dw4/game/ndmw/beNDMWMcSlotPS2.h"
#include "dw4/game/ndmw/beNDMWMcSlotXbox.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beSystem.h"
#include "dw4/game/beUnicodeObj.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include <string.h>
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define MCU(common) ((beNDMWMcUtilCtrl *)(common)->_mcUtilCtrl)
#define MCSLOT(common, i) (((beNDMWMcSlot **)((beNDMWMcSlotList *)MCU(common)->_slot)->_data)[i])
/* matching construct: the code reads the reference count as a signed int (igObject._refCount is reflected unsigned) */
#define REFS(o) (*(int *)&(o)->_refCount)
#define SLOT_PLAYER(p) ((beNDMWLoadSlotPlayer *)(p))
#define DEGI(p) ((beNDMWDegiData *)(p))
#define DNAME(d) ((unsigned short *)(d)->_dmNameUni)
#define REL(o) { igObject *rr = (o); if (rr != 0) { REFS(rr) = REFS(rr) - 1; if (((unsigned long long)((long long)REFS(rr) << 0x29) >> 0x29) == 0) { igObject_Destroy((igObject *)rr); } } }
#define ALLOC(a, self) { a = ((void *)((Gap::Core::igObject *)(self))->getMemoryPool()); a = g_useOwnerAllocator ? a : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1)); }
#define PLW_AT(list, off) (*(beNDMWLoadSavePlWork **)((char *)((beNDMWLoadSavePlWorkList *)(list))->_data + (off)))
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igTDataList.h"
#include "dw4/game/ndmw/beNDMWItemBaseDispatchView.h"
#include "dw4/support/list-services.h"
#define IDS(DST, REC, CAP, RESIZE) { igObjectList *l = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, REC)->_data); int i; if (RESIZE) { if (l->_count > CAP) ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)l))->setCount(CAP); } i = 0; if (0 < l->_count) { do { DST[i] = ((IdObject **)l->_data)[i]->GetId(); i++; } while (i < l->_count); } if (i < CAP) { do { DST[i] = -1; i++; } while (i < CAP); } }
#define BYTES(DST, FN, REC) { igTDataList<unsigned char> *l = (igTDataList<unsigned char> *)FN((igObject *)props, REC)->_data; int i = 0; if (0 < l->_count) { do { DST[i] = l->_data[i]; i++; } while (i < l->_count); } }
#define FINDN(DST, REC, N) { igObjectList *l = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, REC)->_data); igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data); int a; for (a = 0; a < N; a++) { IdObject *v = ((IdObject **)l->_data)[a]; if (v == 0) { DST[a] = -1; } else { DST[a] = t->find(v); } } }
#define FIND1(DSTV, REC) { igObjectList *l = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, REC)->_data); igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data); IdObject *v = ((IdObject **)l->_data)[0]; if (v == 0) { DSTV = -1; } else { DSTV = t->find(v); } }
#define FINDV(DST, REC) { igObjectList *l = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, REC)->_data); igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data); int a; for (a = 0; a < l->_count; a++) { IdObject *v = ((IdObject **)l->_data)[a]; if (v == 0) { DST[a] = -1; } else { DST[a] = t->find(v); } } }
#define INTS(DST, FN, REC) { igIntList *l = (igIntList *)FN((igObject *)props, REC)->_data; int i = 0; if (0 < l->_count) { do { DST[i] = ((int *)l->_data)[i]; i++; } while (i < l->_count); } }
#define OWNER_ALLOCATOR(dst, obj) { int alloc = (int)((Gap::Core::igObject *)(obj))->getMemoryPool(); if (g_useOwnerAllocator != 0) { dst = alloc; } else { dst = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); } }

extern "C" void beNDMWDegiData__CopyFrom(beNDMWDegiData *dst, beNDMWDegiData *src);
/* kept local: Gap::Core::igObjectList::setCount has no include/dw4 home (only CoreLibrary.h declares it). */
extern "C" int beNDMWLoadCtrl2__GetInfoMeta(void);
extern "C" int beNDMWLoadCtrl2__GetMeta(void);
extern "C" void TextOrder_Configure(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font, const char *text, int align, int color);
extern "C" void TextOrder_PublishLine(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font);
/* One text line of a load-screen message: the text-control line it fills and the font it uses. */
struct LoadMessageLine { const char *line; int player; int fontIndex; };
/* A load-screen message: its id (group in bits 12-15), the text call number the txt_ script plays,
 * and its lines. A message with a follow-up also plays the next entry's call number. The table
 * ends with an id of -1. */
struct LoadMessage { unsigned int id:20; unsigned int hasFollowUp:1; unsigned int pad:11; int txtCallNo; LoadMessageLine *lines; };
#pragma push
#pragma readonly_strings on

extern "C" {
LoadMessageLine g_loadMessageLines_404[] = { {"CHRSELFONT06", 0, 0}, {"CHRSELFONT06", 0, 1}, {"CHRSELFONT06", 0, 2}, {"CHRSELFONT06", 0, 3}, {"CHRSELFONT16", 0, 0}, {"CHRSELFONT16", 0, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10500[] = { {"CHRSELFONT06", 1, 0}, {"CHRSELFONT06", 1, 1}, {"CHRSELFONT06", 1, 2}, {"CHRSELFONT06", 1, 3}, {"CHRSELFONT16", 1, 0}, {"CHRSELFONT16", 1, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20500[] = { {"CHRSELFONT06", 2, 0}, {"CHRSELFONT06", 2, 1}, {"CHRSELFONT06", 2, 2}, {"CHRSELFONT06", 2, 3}, {"CHRSELFONT16", 2, 0}, {"CHRSELFONT16", 2, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30500[] = { {"CHRSELFONT06", 3, 0}, {"CHRSELFONT06", 3, 1}, {"CHRSELFONT06", 3, 2}, {"CHRSELFONT06", 3, 3}, {"CHRSELFONT16", 3, 0}, {"CHRSELFONT16", 3, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_504[] = { {"CHRSELFONT16", 0, 0}, {"CHRSELFONT16", 0, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10504[] = { {"CHRSELFONT16", 1, 0}, {"CHRSELFONT16", 1, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20504[] = { {"CHRSELFONT16", 2, 0}, {"CHRSELFONT16", 2, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30504[] = { {"CHRSELFONT16", 3, 0}, {"CHRSELFONT16", 3, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_400[] = { {"CHRSELFONT01", 0, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10400[] = { {"CHRSELFONT01", 1, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20400[] = { {"CHRSELFONT01", 2, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30400[] = { {"CHRSELFONT01", 3, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_401[] = { {"CHRSELFONT02", 0, 0}, {"CHRSELFONT02", 0, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10401[] = { {"CHRSELFONT02", 1, 0}, {"CHRSELFONT02", 1, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20401[] = { {"CHRSELFONT02", 2, 0}, {"CHRSELFONT02", 2, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30401[] = { {"CHRSELFONT02", 3, 0}, {"CHRSELFONT02", 3, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_403[] = { {"CHRSELFONT15", 0, 0}, {"CHRSELFONT15", 0, 1}, {"CHRSELFONT15", 0, 2}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_100C[] = { {"CHRSELFONT07", 0, 0}, {"CHRSELFONT07", 0, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_1100C[] = { {"CHRSELFONT07", 1, 0}, {"CHRSELFONT07", 1, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_2100C[] = { {"CHRSELFONT07", 2, 0}, {"CHRSELFONT07", 2, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_3100C[] = { {"CHRSELFONT07", 3, 0}, {"CHRSELFONT07", 3, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_110[] = { {"CHRSELFONT09", 0, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10110[] = { {"CHRSELFONT09", 1, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20110[] = { {"CHRSELFONT09", 2, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30110[] = { {"CHRSELFONT09", 3, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10[] = { {"CHRSELFONT09", 0, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10010[] = { {"CHRSELFONT09", 1, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20010[] = { {"CHRSELFONT09", 2, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30010[] = { {"CHRSELFONT09", 3, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_300[] = { {"CHRSELFONT08", 0, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10300[] = { {"CHRSELFONT08", 1, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20300[] = { {"CHRSELFONT08", 2, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30300[] = { {"CHRSELFONT08", 3, 0}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_301[] = { {"CHRSELFONT08", 0, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10301[] = { {"CHRSELFONT08", 1, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20301[] = { {"CHRSELFONT08", 2, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30301[] = { {"CHRSELFONT08", 3, 1}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_302[] = { {"CHRSELFONT08", 0, 2}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10302[] = { {"CHRSELFONT08", 1, 2}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20302[] = { {"CHRSELFONT08", 2, 2}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30302[] = { {"CHRSELFONT08", 3, 2}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_303[] = { {"CHRSELFONT08", 0, 3}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_10303[] = { {"CHRSELFONT08", 1, 3}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_20303[] = { {"CHRSELFONT08", 2, 3}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_30303[] = { {"CHRSELFONT08", 3, 3}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_1100[] = { {"CHRSELFONT07", 0, 10}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_11100[] = { {"CHRSELFONT07", 1, 10}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_21100[] = { {"CHRSELFONT07", 2, 10}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_31100[] = { {"CHRSELFONT07", 3, 10}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_102E[] = { {"CHRSELFONT07", 0, 11}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_1102E[] = { {"CHRSELFONT07", 1, 11}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_2102E[] = { {"CHRSELFONT07", 2, 11}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_3102E[] = { {"CHRSELFONT07", 3, 11}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_F0001[] = { {"TITLEFONT01", 1, 0}, {"TITLEFONT01", 1, 1}, {"TITLEFONT01", 1, 6}, {"TITLEFONT01", 1, 7}, {"TITLEFONT01", 1, 8}, {"TITLEFONT01", 1, 9}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_F0002[] = { {"TITLEFONT01", 1, 3}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_F0004[] = { {"TITLEFONT01", 1, 4}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_F0007[] = { {"TITLEFONT01", 1, 5}, {0, 0, 0} };
LoadMessageLine g_loadMessageLines_F0006[] = { {"TITLEFONT01", 1, 2}, {0, 0, 0} };
LoadMessage g_loadMessageTable[] = {
    {0xF0001, 0, 0, 30, g_loadMessageLines_F0001},
    {0xF0002, 0, 0, 40, g_loadMessageLines_F0002},
    {0xF0003, 0, 0, 41, g_loadMessageLines_F0002},
    {0xF0004, 0, 0, 42, g_loadMessageLines_F0004},
    {0xF0005, 0, 0, 43, g_loadMessageLines_F0004},
    {0xF0006, 0, 0, 44, g_loadMessageLines_F0006},
    {0xF0007, 0, 0, 45, g_loadMessageLines_F0007},
    {0xF0008, 0, 0, 46, g_loadMessageLines_F0007},
    {0xF0009, 0, 0, 47, g_loadMessageLines_F0007},
    {0xF000A, 0, 0, 48, g_loadMessageLines_F0007},
    {0xF000B, 0, 0, 49, g_loadMessageLines_F0007},
    {0xF000C, 0, 0, 50, g_loadMessageLines_F0007},
    {0xF000D, 0, 0, 51, g_loadMessageLines_F0007},
    {0x10, 0, 0, 116, g_loadMessageLines_10},
    {0x110, 0, 0, 136, g_loadMessageLines_110},
    {0x300, 0, 0, 150, g_loadMessageLines_300},
    {0x301, 0, 0, 151, g_loadMessageLines_301},
    {0x302, 0, 0, 152, g_loadMessageLines_302},
    {0x303, 0, 0, 153, g_loadMessageLines_303},
    {0x400, 0, 0, 160, g_loadMessageLines_400},
    {0x401, 0, 0, 161, g_loadMessageLines_401},
    {0x402, 0, 0, 163, g_loadMessageLines_401},
    {0x403, 0, 0, 165, g_loadMessageLines_403},
    {0x404, 0, 0, 168, g_loadMessageLines_404},
    {0x500, 0, 0, 200, g_loadMessageLines_404},
    {0x502, 0, 0, 201, g_loadMessageLines_404},
    {0x503, 1, 0, 204, g_loadMessageLines_404},
    {0x504, 0, 0, 300, g_loadMessageLines_504},
    {0x505, 0, 0, 205, g_loadMessageLines_404},
    {0x507, 0, 0, 208, g_loadMessageLines_404},
    {0x508, 0, 0, 211, g_loadMessageLines_404},
    {0x50A, 0, 0, 213, g_loadMessageLines_404},
    {0x50B, 0, 0, 216, g_loadMessageLines_404},
    {0x50D, 0, 0, 218, g_loadMessageLines_404},
    {0x50E, 0, 0, 221, g_loadMessageLines_404},
    {0x510, 0, 0, 222, g_loadMessageLines_404},
    {0x511, 0, 0, 225, g_loadMessageLines_404},
    {0x513, 0, 0, 227, g_loadMessageLines_404},
    {0x515, 0, 0, 230, g_loadMessageLines_404},
    {0x517, 0, 0, 232, g_loadMessageLines_404},
    {0x519, 0, 0, 235, g_loadMessageLines_404},
    {0x51B, 0, 0, 236, g_loadMessageLines_404},
    {0x51C, 0, 0, 239, g_loadMessageLines_404},
    {0x51D, 0, 0, 240, g_loadMessageLines_404},
    {0x51F, 0, 0, 243, g_loadMessageLines_404},
    {0x521, 0, 0, 246, g_loadMessageLines_404},
    {0x522, 0, 0, 248, g_loadMessageLines_404},
    {0x523, 0, 0, 250, g_loadMessageLines_404},
    {0x524, 0, 0, 251, g_loadMessageLines_404},
    {0x525, 0, 0, 252, g_loadMessageLines_404},
    {0x527, 0, 0, 255, g_loadMessageLines_404},
    {0x529, 0, 0, 257, g_loadMessageLines_404},
    {0x52A, 0, 0, 260, g_loadMessageLines_404},
    {0x52B, 0, 0, 262, g_loadMessageLines_404},
    {0x52C, 0, 0, 264, g_loadMessageLines_404},
    {0x52D, 0, 0, 265, g_loadMessageLines_404},
    {0x52F, 0, 0, 268, g_loadMessageLines_404},
    {0x530, 0, 0, 270, g_loadMessageLines_404},
    {0x1000, 0, 0, 1000, g_loadMessageLines_404},
    {0x1002, 0, 0, 1002, g_loadMessageLines_404},
    {0x1003, 0, 0, 1005, g_loadMessageLines_404},
    {0x1004, 0, 0, 1007, g_loadMessageLines_404},
    {0x1005, 0, 0, 1009, g_loadMessageLines_404},
    {0x1007, 0, 0, 1012, g_loadMessageLines_404},
    {0x1008, 0, 0, 1015, g_loadMessageLines_404},
    {0x1009, 0, 0, 1017, g_loadMessageLines_404},
    {0x100A, 0, 0, 1019, g_loadMessageLines_404},
    {0x100B, 0, 0, 1021, g_loadMessageLines_404},
    {0x100C, 0, 0, 1050, g_loadMessageLines_100C},
    {0x100D, 0, 0, 1100, g_loadMessageLines_404},
    {0x100E, 0, 0, 1102, g_loadMessageLines_404},
    {0x100F, 0, 0, 1104, g_loadMessageLines_404},
    {0x1010, 0, 0, 1106, g_loadMessageLines_404},
    {0x1011, 0, 0, 1108, g_loadMessageLines_404},
    {0x1012, 0, 0, 1110, g_loadMessageLines_404},
    {0x1013, 0, 0, 1112, g_loadMessageLines_404},
    {0x1014, 0, 0, 1114, g_loadMessageLines_404},
    {0x1015, 0, 0, 1117, g_loadMessageLines_404},
    {0x1016, 0, 0, 1119, g_loadMessageLines_404},
    {0x1017, 0, 0, 1120, g_loadMessageLines_404},
    {0x1018, 0, 0, 1122, g_loadMessageLines_404},
    {0x101A, 0, 0, 1125, g_loadMessageLines_404},
    {0x101B, 0, 0, 1127, g_loadMessageLines_404},
    {0x101D, 0, 0, 1130, g_loadMessageLines_404},
    {0x101E, 0, 0, 1132, g_loadMessageLines_404},
    {0x101F, 0, 0, 1134, g_loadMessageLines_404},
    {0x1024, 0, 0, 1144, g_loadMessageLines_404},
    {0x1026, 0, 0, 1147, g_loadMessageLines_404},
    {0x1027, 0, 0, 1150, g_loadMessageLines_404},
    {0x1028, 0, 0, 1152, g_loadMessageLines_404},
    {0x1029, 0, 0, 1154, g_loadMessageLines_404},
    {0x102A, 0, 0, 1156, g_loadMessageLines_404},
    {0x102B, 0, 0, 1300, g_loadMessageLines_404},
    {0x102C, 0, 0, 1301, g_loadMessageLines_404},
    {0x102D, 0, 0, 1302, g_loadMessageLines_404},
    {0x102E, 0, 0, 1304, g_loadMessageLines_102E},
    {0x1100, 0, 0, 1200, g_loadMessageLines_1100},
    {0x1101, 0, 0, 1201, g_loadMessageLines_1100},
    {0x1102, 0, 0, 1202, g_loadMessageLines_1100},
    {0x1103, 0, 0, 1203, g_loadMessageLines_1100},
    {0x1104, 0, 0, 1204, g_loadMessageLines_1100},
    {0x1105, 0, 0, 1205, g_loadMessageLines_1100},
    {0x10010, 0, 0, 10116, g_loadMessageLines_10010},
    {0x10110, 0, 0, 10136, g_loadMessageLines_10110},
    {0x10300, 0, 0, 10150, g_loadMessageLines_10300},
    {0x10301, 0, 0, 10151, g_loadMessageLines_10301},
    {0x10302, 0, 0, 10152, g_loadMessageLines_10302},
    {0x10303, 0, 0, 10153, g_loadMessageLines_10303},
    {0x10400, 0, 0, 10160, g_loadMessageLines_10400},
    {0x10401, 0, 0, 10161, g_loadMessageLines_10401},
    {0x10500, 0, 0, 10200, g_loadMessageLines_10500},
    {0x10502, 0, 0, 10201, g_loadMessageLines_10500},
    {0x10503, 1, 0, 10204, g_loadMessageLines_10500},
    {0x10504, 0, 0, 10300, g_loadMessageLines_10504},
    {0x10505, 0, 0, 10205, g_loadMessageLines_10500},
    {0x10507, 0, 0, 10208, g_loadMessageLines_10500},
    {0x10508, 0, 0, 10211, g_loadMessageLines_10500},
    {0x1050A, 0, 0, 10213, g_loadMessageLines_10500},
    {0x1050B, 0, 0, 10216, g_loadMessageLines_10500},
    {0x1050D, 0, 0, 10218, g_loadMessageLines_10500},
    {0x1050E, 0, 0, 10221, g_loadMessageLines_10500},
    {0x10510, 0, 0, 10222, g_loadMessageLines_10500},
    {0x10511, 0, 0, 10225, g_loadMessageLines_10500},
    {0x10513, 0, 0, 10227, g_loadMessageLines_10500},
    {0x10515, 0, 0, 10230, g_loadMessageLines_10500},
    {0x10517, 0, 0, 10232, g_loadMessageLines_10500},
    {0x10519, 0, 0, 10235, g_loadMessageLines_10500},
    {0x1051B, 0, 0, 10236, g_loadMessageLines_10500},
    {0x1051C, 0, 0, 10239, g_loadMessageLines_10500},
    {0x1051D, 0, 0, 10240, g_loadMessageLines_10500},
    {0x1051F, 0, 0, 10243, g_loadMessageLines_10500},
    {0x10521, 0, 0, 10246, g_loadMessageLines_10500},
    {0x10522, 0, 0, 10248, g_loadMessageLines_10500},
    {0x10523, 0, 0, 10250, g_loadMessageLines_10500},
    {0x10524, 0, 0, 10251, g_loadMessageLines_10500},
    {0x10525, 0, 0, 10252, g_loadMessageLines_10500},
    {0x10527, 0, 0, 10255, g_loadMessageLines_10500},
    {0x10529, 0, 0, 10257, g_loadMessageLines_10500},
    {0x1052A, 0, 0, 10260, g_loadMessageLines_10500},
    {0x1052B, 0, 0, 10262, g_loadMessageLines_10500},
    {0x1052C, 0, 0, 10264, g_loadMessageLines_10500},
    {0x1052D, 0, 0, 10265, g_loadMessageLines_10500},
    {0x1052F, 0, 0, 10268, g_loadMessageLines_10500},
    {0x10530, 0, 0, 10270, g_loadMessageLines_10500},
    {0x11000, 0, 0, 11000, g_loadMessageLines_10500},
    {0x11002, 0, 0, 11002, g_loadMessageLines_10500},
    {0x11003, 0, 0, 11005, g_loadMessageLines_10500},
    {0x11004, 0, 0, 11007, g_loadMessageLines_10500},
    {0x11005, 0, 0, 11009, g_loadMessageLines_10500},
    {0x11007, 0, 0, 11012, g_loadMessageLines_10500},
    {0x11008, 0, 0, 11015, g_loadMessageLines_10500},
    {0x11009, 0, 0, 11017, g_loadMessageLines_10500},
    {0x1100A, 0, 0, 11019, g_loadMessageLines_10500},
    {0x1100B, 0, 0, 11021, g_loadMessageLines_10500},
    {0x1100C, 0, 0, 11050, g_loadMessageLines_1100C},
    {0x1100D, 0, 0, 11100, g_loadMessageLines_10500},
    {0x1100E, 0, 0, 11102, g_loadMessageLines_10500},
    {0x1100F, 0, 0, 11104, g_loadMessageLines_10500},
    {0x11010, 0, 0, 11106, g_loadMessageLines_10500},
    {0x11011, 0, 0, 11108, g_loadMessageLines_10500},
    {0x11012, 0, 0, 11110, g_loadMessageLines_10500},
    {0x11013, 0, 0, 11112, g_loadMessageLines_10500},
    {0x11014, 0, 0, 11114, g_loadMessageLines_10500},
    {0x11015, 0, 0, 11117, g_loadMessageLines_10500},
    {0x11016, 0, 0, 11119, g_loadMessageLines_10500},
    {0x11017, 0, 0, 11120, g_loadMessageLines_10500},
    {0x11018, 0, 0, 11122, g_loadMessageLines_10500},
    {0x1101A, 0, 0, 11125, g_loadMessageLines_10500},
    {0x1101B, 0, 0, 11127, g_loadMessageLines_10500},
    {0x1101D, 0, 0, 11130, g_loadMessageLines_10500},
    {0x1101E, 0, 0, 11132, g_loadMessageLines_10500},
    {0x1101F, 0, 0, 11134, g_loadMessageLines_10500},
    {0x11024, 0, 0, 11144, g_loadMessageLines_10500},
    {0x11026, 0, 0, 11147, g_loadMessageLines_10500},
    {0x11027, 0, 0, 11150, g_loadMessageLines_10500},
    {0x11028, 0, 0, 11152, g_loadMessageLines_10500},
    {0x11029, 0, 0, 11154, g_loadMessageLines_10500},
    {0x1102A, 0, 0, 11156, g_loadMessageLines_10500},
    {0x1102B, 0, 0, 11300, g_loadMessageLines_10500},
    {0x1102C, 0, 0, 11301, g_loadMessageLines_10500},
    {0x1102D, 0, 0, 11302, g_loadMessageLines_10500},
    {0x1102E, 0, 0, 11304, g_loadMessageLines_1102E},
    {0x11100, 0, 0, 11200, g_loadMessageLines_11100},
    {0x11101, 0, 0, 11201, g_loadMessageLines_11100},
    {0x11102, 0, 0, 11202, g_loadMessageLines_11100},
    {0x11103, 0, 0, 11203, g_loadMessageLines_11100},
    {0x11104, 0, 0, 11204, g_loadMessageLines_11100},
    {0x11105, 0, 0, 11205, g_loadMessageLines_11100},
    {0x20010, 0, 0, 20116, g_loadMessageLines_20010},
    {0x20110, 0, 0, 20136, g_loadMessageLines_20110},
    {0x20300, 0, 0, 20150, g_loadMessageLines_20300},
    {0x20301, 0, 0, 20151, g_loadMessageLines_20301},
    {0x20302, 0, 0, 20152, g_loadMessageLines_20302},
    {0x20303, 0, 0, 20153, g_loadMessageLines_20303},
    {0x20400, 0, 0, 20160, g_loadMessageLines_20400},
    {0x20401, 0, 0, 20161, g_loadMessageLines_20401},
    {0x20500, 0, 0, 20200, g_loadMessageLines_20500},
    {0x20502, 0, 0, 20201, g_loadMessageLines_20500},
    {0x20503, 1, 0, 20204, g_loadMessageLines_20500},
    {0x20504, 0, 0, 20300, g_loadMessageLines_20504},
    {0x20505, 0, 0, 20205, g_loadMessageLines_20500},
    {0x20507, 0, 0, 20208, g_loadMessageLines_20500},
    {0x20508, 0, 0, 20211, g_loadMessageLines_20500},
    {0x2050A, 0, 0, 20213, g_loadMessageLines_20500},
    {0x2050B, 0, 0, 20216, g_loadMessageLines_20500},
    {0x2050D, 0, 0, 20218, g_loadMessageLines_20500},
    {0x2050E, 0, 0, 20221, g_loadMessageLines_20500},
    {0x20510, 0, 0, 20222, g_loadMessageLines_20500},
    {0x20511, 0, 0, 20225, g_loadMessageLines_20500},
    {0x20513, 0, 0, 20227, g_loadMessageLines_20500},
    {0x20515, 0, 0, 20230, g_loadMessageLines_20500},
    {0x20517, 0, 0, 20232, g_loadMessageLines_20500},
    {0x20519, 0, 0, 20235, g_loadMessageLines_20500},
    {0x2051B, 0, 0, 20236, g_loadMessageLines_20500},
    {0x2051C, 0, 0, 20239, g_loadMessageLines_20500},
    {0x2051D, 0, 0, 20240, g_loadMessageLines_20500},
    {0x2051F, 0, 0, 20243, g_loadMessageLines_20500},
    {0x20521, 0, 0, 20246, g_loadMessageLines_20500},
    {0x20522, 0, 0, 20248, g_loadMessageLines_20500},
    {0x20523, 0, 0, 20250, g_loadMessageLines_20500},
    {0x20524, 0, 0, 20251, g_loadMessageLines_20500},
    {0x20525, 0, 0, 20252, g_loadMessageLines_20500},
    {0x20527, 0, 0, 20255, g_loadMessageLines_20500},
    {0x20529, 0, 0, 20257, g_loadMessageLines_20500},
    {0x2052A, 0, 0, 20260, g_loadMessageLines_20500},
    {0x2052B, 0, 0, 20262, g_loadMessageLines_20500},
    {0x2052C, 0, 0, 20264, g_loadMessageLines_20500},
    {0x2052D, 0, 0, 20265, g_loadMessageLines_20500},
    {0x2052F, 0, 0, 20268, g_loadMessageLines_20500},
    {0x20530, 0, 0, 20270, g_loadMessageLines_20500},
    {0x21000, 0, 0, 21000, g_loadMessageLines_20500},
    {0x21002, 0, 0, 21002, g_loadMessageLines_20500},
    {0x21003, 0, 0, 21005, g_loadMessageLines_20500},
    {0x21004, 0, 0, 21007, g_loadMessageLines_20500},
    {0x21005, 0, 0, 21009, g_loadMessageLines_20500},
    {0x21007, 0, 0, 21012, g_loadMessageLines_20500},
    {0x21008, 0, 0, 21015, g_loadMessageLines_20500},
    {0x21009, 0, 0, 21017, g_loadMessageLines_20500},
    {0x2100A, 0, 0, 21019, g_loadMessageLines_20500},
    {0x2100B, 0, 0, 21021, g_loadMessageLines_20500},
    {0x2100C, 0, 0, 21050, g_loadMessageLines_2100C},
    {0x2100D, 0, 0, 21100, g_loadMessageLines_20500},
    {0x2100E, 0, 0, 21102, g_loadMessageLines_20500},
    {0x2100F, 0, 0, 21104, g_loadMessageLines_20500},
    {0x21010, 0, 0, 21106, g_loadMessageLines_20500},
    {0x21011, 0, 0, 21108, g_loadMessageLines_20500},
    {0x21012, 0, 0, 21110, g_loadMessageLines_20500},
    {0x21013, 0, 0, 21112, g_loadMessageLines_20500},
    {0x21014, 0, 0, 21114, g_loadMessageLines_20500},
    {0x21015, 0, 0, 21117, g_loadMessageLines_20500},
    {0x21016, 0, 0, 21119, g_loadMessageLines_20500},
    {0x21017, 0, 0, 21120, g_loadMessageLines_20500},
    {0x21018, 0, 0, 21122, g_loadMessageLines_20500},
    {0x2101A, 0, 0, 21125, g_loadMessageLines_20500},
    {0x2101B, 0, 0, 21127, g_loadMessageLines_20500},
    {0x2101D, 0, 0, 21130, g_loadMessageLines_20500},
    {0x2101E, 0, 0, 21132, g_loadMessageLines_20500},
    {0x2101F, 0, 0, 21134, g_loadMessageLines_20500},
    {0x21024, 0, 0, 21144, g_loadMessageLines_20500},
    {0x21026, 0, 0, 21147, g_loadMessageLines_20500},
    {0x21027, 0, 0, 21150, g_loadMessageLines_20500},
    {0x21028, 0, 0, 21152, g_loadMessageLines_20500},
    {0x21029, 0, 0, 21154, g_loadMessageLines_20500},
    {0x2102A, 0, 0, 21156, g_loadMessageLines_20500},
    {0x2102B, 0, 0, 21300, g_loadMessageLines_20500},
    {0x2102C, 0, 0, 21301, g_loadMessageLines_20500},
    {0x2102D, 0, 0, 21302, g_loadMessageLines_20500},
    {0x2102E, 0, 0, 21304, g_loadMessageLines_2102E},
    {0x21100, 0, 0, 21200, g_loadMessageLines_21100},
    {0x21101, 0, 0, 21201, g_loadMessageLines_21100},
    {0x21102, 0, 0, 21202, g_loadMessageLines_21100},
    {0x21103, 0, 0, 21203, g_loadMessageLines_21100},
    {0x21104, 0, 0, 21204, g_loadMessageLines_21100},
    {0x21105, 0, 0, 21205, g_loadMessageLines_21100},
    {0x30010, 0, 0, 30116, g_loadMessageLines_30010},
    {0x30110, 0, 0, 30136, g_loadMessageLines_30110},
    {0x30300, 0, 0, 30150, g_loadMessageLines_30300},
    {0x30301, 0, 0, 30151, g_loadMessageLines_30301},
    {0x30302, 0, 0, 30152, g_loadMessageLines_30302},
    {0x30303, 0, 0, 30153, g_loadMessageLines_30303},
    {0x30400, 0, 0, 30160, g_loadMessageLines_30400},
    {0x30401, 0, 0, 30161, g_loadMessageLines_30401},
    {0x30500, 0, 0, 30200, g_loadMessageLines_30500},
    {0x30502, 0, 0, 30201, g_loadMessageLines_30500},
    {0x30503, 1, 0, 30204, g_loadMessageLines_30500},
    {0x30504, 0, 0, 30300, g_loadMessageLines_30504},
    {0x30505, 0, 0, 30205, g_loadMessageLines_30500},
    {0x30507, 0, 0, 30208, g_loadMessageLines_30500},
    {0x30508, 0, 0, 30211, g_loadMessageLines_30500},
    {0x3050A, 0, 0, 30213, g_loadMessageLines_30500},
    {0x3050B, 0, 0, 30216, g_loadMessageLines_30500},
    {0x3050D, 0, 0, 30218, g_loadMessageLines_30500},
    {0x3050E, 0, 0, 30221, g_loadMessageLines_30500},
    {0x30510, 0, 0, 30222, g_loadMessageLines_30500},
    {0x30511, 0, 0, 30225, g_loadMessageLines_30500},
    {0x30513, 0, 0, 30227, g_loadMessageLines_30500},
    {0x30515, 0, 0, 30230, g_loadMessageLines_30500},
    {0x30517, 0, 0, 30232, g_loadMessageLines_30500},
    {0x30519, 0, 0, 30235, g_loadMessageLines_30500},
    {0x3051B, 0, 0, 30236, g_loadMessageLines_30500},
    {0x3051C, 0, 0, 30239, g_loadMessageLines_30500},
    {0x3051D, 0, 0, 30240, g_loadMessageLines_30500},
    {0x3051F, 0, 0, 30243, g_loadMessageLines_30500},
    {0x30521, 0, 0, 30246, g_loadMessageLines_30500},
    {0x30522, 0, 0, 30248, g_loadMessageLines_30500},
    {0x30523, 0, 0, 30250, g_loadMessageLines_30500},
    {0x30524, 0, 0, 30251, g_loadMessageLines_30500},
    {0x30525, 0, 0, 30252, g_loadMessageLines_30500},
    {0x30527, 0, 0, 30255, g_loadMessageLines_30500},
    {0x30529, 0, 0, 30257, g_loadMessageLines_30500},
    {0x3052A, 0, 0, 30260, g_loadMessageLines_30500},
    {0x3052B, 0, 0, 30262, g_loadMessageLines_30500},
    {0x3052C, 0, 0, 30264, g_loadMessageLines_30500},
    {0x3052D, 0, 0, 30265, g_loadMessageLines_30500},
    {0x3052F, 0, 0, 30268, g_loadMessageLines_30500},
    {0x30530, 0, 0, 30270, g_loadMessageLines_30500},
    {0x31000, 0, 0, 31000, g_loadMessageLines_30500},
    {0x31002, 0, 0, 31002, g_loadMessageLines_30500},
    {0x31003, 0, 0, 31005, g_loadMessageLines_30500},
    {0x31004, 0, 0, 31007, g_loadMessageLines_30500},
    {0x31005, 0, 0, 31009, g_loadMessageLines_30500},
    {0x31007, 0, 0, 31012, g_loadMessageLines_30500},
    {0x31008, 0, 0, 31015, g_loadMessageLines_30500},
    {0x31009, 0, 0, 31017, g_loadMessageLines_30500},
    {0x3100A, 0, 0, 31019, g_loadMessageLines_30500},
    {0x3100B, 0, 0, 31021, g_loadMessageLines_30500},
    {0x3100C, 0, 0, 31050, g_loadMessageLines_3100C},
    {0x3100D, 0, 0, 31100, g_loadMessageLines_30500},
    {0x3100E, 0, 0, 31102, g_loadMessageLines_30500},
    {0x3100F, 0, 0, 31104, g_loadMessageLines_30500},
    {0x31010, 0, 0, 31106, g_loadMessageLines_30500},
    {0x31011, 0, 0, 31108, g_loadMessageLines_30500},
    {0x31012, 0, 0, 31110, g_loadMessageLines_30500},
    {0x31013, 0, 0, 31112, g_loadMessageLines_30500},
    {0x31014, 0, 0, 31114, g_loadMessageLines_30500},
    {0x31015, 0, 0, 31117, g_loadMessageLines_30500},
    {0x31016, 0, 0, 31119, g_loadMessageLines_30500},
    {0x31017, 0, 0, 31120, g_loadMessageLines_30500},
    {0x31018, 0, 0, 31122, g_loadMessageLines_30500},
    {0x3101A, 0, 0, 31125, g_loadMessageLines_30500},
    {0x3101B, 0, 0, 31127, g_loadMessageLines_30500},
    {0x3101D, 0, 0, 31130, g_loadMessageLines_30500},
    {0x3101E, 0, 0, 31132, g_loadMessageLines_30500},
    {0x3101F, 0, 0, 31134, g_loadMessageLines_30500},
    {0x31024, 0, 0, 31144, g_loadMessageLines_30500},
    {0x31026, 0, 0, 31147, g_loadMessageLines_30500},
    {0x31027, 0, 0, 31150, g_loadMessageLines_30500},
    {0x31028, 0, 0, 31152, g_loadMessageLines_30500},
    {0x31029, 0, 0, 31154, g_loadMessageLines_30500},
    {0x3102A, 0, 0, 31156, g_loadMessageLines_30500},
    {0x3102B, 0, 0, 31300, g_loadMessageLines_30500},
    {0x3102C, 0, 0, 31301, g_loadMessageLines_30500},
    {0x3102D, 0, 0, 31302, g_loadMessageLines_30500},
    {0x3102E, 0, 0, 31304, g_loadMessageLines_3102E},
    {0x31100, 0, 0, 31200, g_loadMessageLines_31100},
    {0x31101, 0, 0, 31201, g_loadMessageLines_31100},
    {0x31102, 0, 0, 31202, g_loadMessageLines_31100},
    {0x31103, 0, 0, 31203, g_loadMessageLines_31100},
    {0x31104, 0, 0, 31204, g_loadMessageLines_31100},
    {0x31105, 0, 0, 31205, g_loadMessageLines_31100},
    {0xFFFFF, 1, 0x7FF, 0, 0}
};
/* Font names by player (row) and font (column). */
const char *g_loadFontNames[4][20] = {
    {"font000", "font001", "font002", "font003", "font004", "font005", "font006", "font007", "font008", "font009", "font010", "font011", "font012", "font013", "font014", "font015", "font016", "font017", "font018", "font019"},
    {"font100", "font101", "font102", "font103", "font104", "font105", "font106", "font107", "font108", "font109", "font110", "font111", "font112", "font113", "font114", "font115", "font116", "font117", "font118", "font119"},
    {"font200", "font201", "font202", "font203", "font204", "font205", "font206", "font207", "font208", "font209", "font210", "font211", "font212", "font213", "font214", "font215", "font216", "font217", "font218", "font219"},
    {"font300", "font301", "font302", "font303", "font304", "font305", "font306", "font307", "font308", "font309", "font310", "font311", "font312", "font313", "font314", "font315", "font316", "font317", "font318", "font319"}
};
}
extern "C" unsigned char beNDMWLoadIntf2MesWin__IsSequencePlaying(beNDMWLoadIntf2MesWin *win, int player, const char *target, const char *sequence);

/* Owning stack reference to the new slot player: constructed from the creating call and released
 * on scope exit (reference count in the low 23 bits of _refCount). Its destructor is emitted out
 * of line. */
class SlotPlayerRef {
public:
    igObject *p;
    SlotPlayerRef(igObject *o) : p(o) {}
    ~SlotPlayerRef() { igObject *o = p; igObject::release(o); }
};
/* Owning stack reference to one Digimon record (a new one appended to the slot player, then each
 * one re-read from its list): released at the end of each loop pass. Its destructor is emitted out
 * of line. */
class DegiDataRef {
public:
    igObject *p;
    DegiDataRef(igObject *o) : p(o) {}
    ~DegiDataRef() { igObject *o = p; igObject::release(o); }
};
/* A Digimon's save block: the data block of a beNDMWDegiData, one record per property of the
 * save. playerName[0] is 0xFFFF once the name has been converted to unicode. */
struct DegiSaveRecord {
    unsigned char isUse; char pad1[3];
    int unique;
    char digimonName[32];
    unsigned short playerName[16];
    int level, hp, maxHp, mp, maxMp, xdata, bit;
    int deviceFolder[36];
    int diskFolder[12];
    unsigned char cardList[50]; char pad294[2];
    int bankDevice[96];
    int bankBit;
    int powerSocket[3];
    int powerPocket[5];
    int mainSlot;
    int mainPocket[5];
    int subSlot;
    unsigned char baseFlag[1024];
    unsigned char baseFlagFolder[12];
    int baseCounter[16];
    unsigned char baseIsUse[16];
    int baseLevel[16];
    int baseExp[16];
    int baseSkill[144];
    int baseUpcnt[176];
};
extern "C" void beNDMWDegiData__UpdateFieldsFromData(beNDMWDegiData *degi);
extern "C" void beNDMWDegiData__LoadFromBuffer(beNDMWDegiData *degi, int buffer);
class IdObject {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22();
    virtual int GetId();
};

static inline int listCount(const igObjectList *l) { return l->_count; }
struct RefCounted { int vtable; int refCount; };
struct RefCountedOps {
    static inline void Release(RefCounted *o) {
        if (o) {
            --o->refCount;
            if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)o);
        }
    }
};
/* matching construct: one RAII releasing holder per retail destructor copy; the cleanup table at 0x544c5c names 0x3832d0 (chunk buffer) and 0x1363f0 (list element / created item) */
struct ChunkRef { RefCounted *p; ChunkRef(RefCounted *x) : p(x) {} ~ChunkRef() { RefCounted *o = p; if (o != 0) { --o->refCount; if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0) igObject_Destroy((igObject *)o); } } };
struct ItemRef { RefCounted *p; ItemRef() {} ItemRef(RefCounted *x) : p(x) {} ItemRef(RefCounted *x, RetainReference) : p(x) { RefCounted *o = p; if (o != 0) ++o->refCount; } ~ItemRef() { RefCounted *o = p; if (o != 0) { --o->refCount; if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0) igObject_Destroy((igObject *)o); } } };
struct ObjectListOps {
    static inline void ReleaseAll(igObjectList *l) {
        int n = l->_count;
        int i;
        for (i = 0; i < n; i++)
            RefCountedOps::Release(((RefCounted **)l->_data)[i]);
    }
    static inline void ZeroAll(igObjectList *l) {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++)
            ((RefCounted **)l->_data)[j] = 0;
    }
    static inline void Clear(igObjectList *l) {
        if (listCount(l) > 0) {
            ReleaseAll(l);
            ZeroAll(l);
            l->_count = 0;
        }
    }
};
extern "C" ItemRef beNDMWDegiData__CreateItem(void *owner, int id);
extern "C" void beNDMWLoadSlotPlayer__WriteToBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer, int replaceIndex, beNDMWDegiData *replacement);
extern "C" void beNDMWLoadSlotPlayer__ReadFromBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer);
/* Owning stack reference to a new slot window of one of the three slot classes (kind 0..2 follows
 * kindHard), released on scope exit (reference count in the low 23 bits of _refCount). */
template <int kind> class SlotRef {
public:
    igObject *p;
    SlotRef(igObject *o) : p(o) {}
    ~SlotRef() { igObject *o = p; igObject::release(o); }
};
extern "C" void beNDMWLoadCtrl2_Prepare(beNDMWLoadCtrl2 *self);
extern "C" void beNDMWLoadCtrl2_OnAddRam(beNDMWLoadCtrl2 *self, int info);
extern "C" void beNDMWLoadCtrl2_UpdateRam(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram);
/* Owning stack references while the controller list is wired up; each releases its object on scope
 * exit. */

class CtrlDataRef {
public:
    igObject *p;
    CtrlDataRef(igObject *o) : p(o) {}
    ~CtrlDataRef() { igObject *o = p; igObject::release(o); }
};
class CommonIntfRef {
public:
    igObject *p;
    CommonIntfRef(igObject *o) : p(o) {}
    ~CommonIntfRef() { igObject *o = p; igObject::release(o); }
};
class FlagWorkRef {
public:
    igObject *p;
    FlagWorkRef(igObject *o) : p(o) {}
    ~FlagWorkRef() { igObject *o = p; igObject::release(o); }
};
/* Releases an object reference, used for the old list during the list install. */
struct ReleaseRef { static inline void Apply(igObject *object) {
    igObject::release(object);
} };
extern "C" int beNDMWLoadCtrl2_OnMessage(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram, beBaseInfo *info);

void TextOrder_Configure(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font, const char *text, int align, int color) {
    switch (align) {
    case 0:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_AppendString((beMessenger *)order->_messenger, "LEFT");
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "ALIGN");
        break;
    case 1:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_AppendString((beMessenger *)order->_messenger, "CENTER");
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "ALIGN");
        break;
    case 2:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_AppendString((beMessenger *)order->_messenger, "RIGHT");
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "ALIGN");
        break;
    }
    switch (color) {
    case 0:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "DEFAULTCOLOR");
        break;
    case 1:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "CANCELCOLOR");
        break;
    case 2:
        break;
    }
    beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)order->_messenger, line);
    beMessenger_AppendString((beMessenger *)order->_messenger, font);
    beMessenger_AppendString((beMessenger *)order->_messenger, text);
    beMessenger_DispatchSelected((beMessenger *)order->_messenger, "TEXTSET");
    beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)order->_messenger, line);
    beMessenger_AppendString((beMessenger *)order->_messenger, font);
    beMessenger_AppendString((beMessenger *)order->_messenger, "SET");
    beMessenger_DispatchSelected((beMessenger *)order->_messenger, "SWITCH");
}

void TextOrder_PublishLine(beNDMWLoadIntf2TextOrder *order, const char *line, const char *font) {
    beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)order->_messenger, line);
    beMessenger_AppendString((beMessenger *)order->_messenger, font);
    beMessenger_AppendString((beMessenger *)order->_messenger, "CLR");
    beMessenger_DispatchSelected((beMessenger *)order->_messenger, "SWITCH");
}

void TextOrder_ConfigureFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, const char *text, int align, int color) {
    TextOrder_Configure(order, line, g_loadFontNames[player][fontIndex], text, align, color);
}

void TextOrder_ClearFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex) {
    TextOrder_PublishLine(order, line, g_loadFontNames[player][fontIndex]);
}

void beNDMWLoadIntf2TextOrder_PublishIdLines(beNDMWLoadIntf2TextOrder *order, int messageId, int withFollowUp) {
    int group;
    int index;
    int i;
    int off;
    LoadMessage *e;
    LoadMessageLine *p;
    index = -1;
    i = 0;
    e = g_loadMessageTable;
    for (;;) {
        if (*(int *)e == -1) break;
        if (e->id == messageId) { index = i; break; }
        e++;
        i++;
    }
    if (index != -1) {
        off = index * (int)sizeof(LoadMessage);
        p = *(LoadMessageLine **)((char *)&g_loadMessageTable->lines + off);
        for (;;) {
            if (p->line == 0) break;
            TextOrder_PublishLine(order, p->line, g_loadFontNames[p->player][p->fontIndex]);
            p++;
        }
        group = messageId & 0xF000;
        g_txtCallNo = *(int *)((char *)&g_loadMessageTable->txtCallNo + off);
        g_mdlEntity = 0;
        switch (group) {
        case 0:
            beLua__RunNamedChunk((beLua *)order->_lua, "txt_mem.lua", 0);
            break;
        case 0x1000:
        case 0x2000:
        case 0x3000:
            beLua__RunNamedChunk((beLua *)order->_lua, "txt_Tar.lua", 0);
            break;
        }
        if (withFollowUp == 1 && (*(int *)((char *)g_loadMessageTable + off) & 0x100000)) {
            g_txtCallNo = *(int *)((char *)&g_loadMessageTable->txtCallNo + (index + 1) * (int)sizeof(LoadMessage));
            g_mdlEntity = 0;
            switch (group) {
            case 0:
                beLua__RunNamedChunk((beLua *)order->_lua, "txt_mem.lua", 0);
                break;
            case 0x1000:
            case 0x2000:
            case 0x3000:
                beLua__RunNamedChunk((beLua *)order->_lua, "txt_Tar.lua", 0);
                break;
            }
        }
    }
}

void TextOrder_PublishLineListOnly(beNDMWLoadIntf2TextOrder *order, int messageId) {
    LoadMessage *e; int i; LoadMessageLine *q;
    i = 0;
    e = g_loadMessageTable;
    for (;;) { if (e->id == messageId) break; e = e + 1; i = i + 1; }
    if (i != -1) {
        q = g_loadMessageTable[i].lines;
        for (;;) {
            if (q->line == 0) break;
            TextOrder_PublishLine(order, q->line, g_loadFontNames[q->player][q->fontIndex]);
            q = q + 1;
        }
    }
}

void TextOrder_ConfigureUnicode(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, beUnicodeObj *unicodeText, int align, int color) {
    const char *font;

    beMessenger_SelectGroup((beMessenger *)order->_messenger, "TEXTCTL");
    beMessenger_AppendObject((beMessenger *)order->_messenger, unicodeText);
    beMessenger_AppendInt((beMessenger *)order->_messenger, 0x3F);
    beMessenger_DispatchSelected((beMessenger *)order->_messenger, "REPLACEUNKNOWN");
    font = g_loadFontNames[player][fontIndex];
    switch (align) {
    case 0:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_AppendString((beMessenger *)order->_messenger, "LEFT");
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "ALIGN");
        break;
    case 1:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_AppendString((beMessenger *)order->_messenger, "CENTER");
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "ALIGN");
        break;
    case 2:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_AppendString((beMessenger *)order->_messenger, "RIGHT");
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "ALIGN");
        break;
    }
    beMessenger_SelectGroup((beMessenger *)order->_messenger, "TEXTCTL");
    beMessenger_AppendString((beMessenger *)order->_messenger, line);
    beMessenger_AppendString((beMessenger *)order->_messenger, font);
    beMessenger_AppendObject((beMessenger *)order->_messenger, unicodeText);
    beMessenger_DispatchSelected((beMessenger *)order->_messenger, "TEXTSET");
    beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)order->_messenger, line);
    beMessenger_AppendString((beMessenger *)order->_messenger, font);
    beMessenger_AppendString((beMessenger *)order->_messenger, "SET");
    beMessenger_DispatchSelected((beMessenger *)order->_messenger, "SWITCH");
    switch (color) {
    case 0:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "DEFAULTCOLOR");
        return;
    case 1:
        beMessenger_SelectReceivers((beMessenger *)order->_messenger, "TEXTCTL", 0, -1);
        beMessenger_AppendString((beMessenger *)order->_messenger, line);
        beMessenger_AppendString((beMessenger *)order->_messenger, font);
        beMessenger_DispatchSelected((beMessenger *)order->_messenger, "CANCELCOLOR");
    case 2:
        ;
    }
}

void beNDMWLoadIntf2MesWin__Update(beNDMWLoadIntf2MesWin *win) {
    int line;
    if (win->_isWinOpen == 1) {
        if (win->_isSystemMes != 1) {
            if (win->_isCtrl == 1) {
                switch (win->_kindCtrl) {
                case 0:
                    switch (win->_statCtrl) {
                    case 0:
                        if (win->_curPoint == 0) {
                            beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_LINESL00");
                        } else {
                            beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_LINESL01");
                        }
                        win->_statCtrl = win->_statCtrl + 1;
                        break;
                    case 1: {
                        bePadData *pad = bePadManager_GetPadForPlayer((bePadManager *)win->_padManager, win->_ramNo);
                        int trigger = pad->_trigger;
                        int repeat = pad->_repeat;
                        int stick = pad->_lTrg | pad->_lRpt;
                        bool up = true;
                        if (!(stick & 1) && !((trigger | repeat) & 0x10)) up = false;
                        bool down = true;
                        if (!(stick & 4) && !((trigger | repeat) & 0x40)) down = false;
                        if (up) {
                            if (win->_curPoint == 1) {
                                win->_curPoint = 0;
                                beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_LINEUP00");
                                win->_statCtrl = 2;
                            }
                        } else if (down) {
                            if (win->_curPoint == 0) {
                                win->_curPoint = 1;
                                beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_LINEDW01");
                                win->_statCtrl = 3;
                            }
                        } else if (trigger & 0x4000) {
                            if (win->_curPoint == 0) {
                                beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_LINEON00");
                            } else {
                                beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_LINEON01");
                            }
                            win->_statCtrl = 4;
                        }
                        break;
                    }
                    case 2:
                        if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, "j_chrselmesswin", "SQ_LINEUP00") == 0) win->_statCtrl = 1;
                        break;
                    case 3:
                        if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, "j_chrselmesswin", "SQ_LINEDW01") == 0) win->_statCtrl = 1;
                        break;
                    case 4:
                        if (win->_curPoint == 0) {
                            if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, "j_chrselmesswin", "SQ_LINEON00") == 0) {
                                beNDMWLoadIntf2MesWin__RequestMesErase(win);
                                win->_isSelect = 1;
                                win->_isCtrl = 0;
                            }
                        } else if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, "j_chrselmesswin", "SQ_LINEON01") == 0) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(win);
                            win->_isSelect = 1;
                            win->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                case 1:
                    switch (win->_statCtrl) {
                    case 0:
                        beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_NEXTSL00");
                        win->_statCtrl = win->_statCtrl + 1;
                        break;
                    case 1:
                        if (bePadManager_GetPadForPlayer((bePadManager *)win->_padManager, win->_ramNo)->_trigger & 0x4000) {
                            beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_NEXTON00");
                            win->_statCtrl = win->_statCtrl + 1;
                        }
                        break;
                    case 2:
                        if (beNDMWLoadIntf2MesWin__IsSequencePlaying(win, win->_ramNo, "j_chrselmesswin", "SQ_NEXTON00") == 0) {
                            beNDMWLoadIntf2MesWin__RequestMesErase(win);
                            win->_isSelect = 1;
                            win->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                }
            }
        } else {
            switch (win->_sysStat) {
            case 0:
                beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_WAIT");
                win->_sysStat = win->_sysStat + 1;
                break;
            case 1:
                break;
            }
        }
        if (win->_isMesCom == 1) {
            if (win->_isSystemMes == 1) {
                beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)win->_textOrder, win->_sysMesNo, 1);
            } else if (win->_isMesErase == 0) {
                win->_isDisp = 1;
                beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)win->_textOrder, win->_mesNo, 1);
            } else {
                line = 0;
                do {
                    TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)win->_textOrder, "CHRSELFONT06", win->_ramNo, line);
                    line += 1;
                } while (line < 4);
                line = 4;
                do {
                    TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)win->_textOrder, "CHRSELFONT16", win->_ramNo, line - 4);
                    line += 1;
                } while (line < 6);
                win->_isMesErase = 0;
                win->_isDisp = 0;
                if (win->_isWinClose == 1) {
                    win->_isWinOpen = 0;
                }
            }
            win->_isMesCom = 0;
        }
    }
}

unsigned char beNDMWLoadIntf2MesWin__IsSequencePlaying(beNDMWLoadIntf2MesWin *win, int player, const char *target, const char *sequence) {
    beMessenger_SelectReceivers((beMessenger *)win->_messenger, "MODELCTRL", target, player);
    beMessenger_AppendString((beMessenger *)win->_messenger, sequence);
    beMessenger_DispatchSelected((beMessenger *)win->_messenger, "ISSEQNAME");
    return beMessenger_GetBool((beMessenger *)win->_messenger, 0);
}

void beNDMWLoadIntf2MesWin__RequestOpen(beNDMWLoadIntf2MesWin *win) {
    win->_isWinOpen = 1;
    win->_isWinClose = 0;
    win->_isSelect = 0;
    win->_isCtrl = 0;
    win->_isSystemMes = 0;
    win->_isMesErase = 0;
    win->_isMesCom = 0;
}

void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *win) {
    beNDMWLoadIntf2MesWin__RequestMesErase(win);
    win->_isWinClose = 1;
}

void beNDMWLoadIntf2MesWin__RequestMessage(beNDMWLoadIntf2MesWin *win, int messageNo) {
    win->_isMesCom = 1;
    win->_mesNo = messageNo;
}

void beNDMWLoadIntf2MesWin__RequestQuestion(beNDMWLoadIntf2MesWin *win, int messageNo, int cursor) {
    win->_isMesCom = 1;
    win->_isCtrl = 1;
    win->_mesNo = messageNo;
    win->_curPoint = cursor;
    win->_statCtrl = 0;
    win->_kindCtrl = 0;
}

void beNDMWLoadIntf2MesWin__RequestPrompt(beNDMWLoadIntf2MesWin *win, int messageNo) {
    win->_isMesCom = 1;
    win->_isCtrl = 1;
    win->_mesNo = messageNo;
    win->_statCtrl = 0;
    win->_kindCtrl = 1;
}

void beNDMWLoadIntf2MesWin__Cancel(beNDMWLoadIntf2MesWin *win) {
    win->_isCtrl = 0;
    beMessenger_SendNamed((beMessenger *)win->_messenger, "MODELCTRL", "j_chrselmesswin", win->_ramNo, "SQ_WAIT");
    beNDMWLoadIntf2MesWin__RequestMesErase(win);
}

/* Whether a question or prompt is still waiting for the player. */
unsigned char beNDMWLoadIntf2MesWin__GetIsCtrl(beNDMWLoadIntf2MesWin *win)
{
    return win->_isCtrl;
}

int beNDMWLoadIntf2MesWin__GetCurPoint(beNDMWLoadIntf2MesWin *win)
{
    return win->_curPoint;
}

void beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *win) {
    win->_isMesErase = 1;
    win->_isMesCom = 1;
}

void beNDMWLoadIntf2MesWin__RequestSystemMessage(beNDMWLoadIntf2MesWin *win, int messageNo) {
    win->_isMesCom = 1;
    win->_isSystemMes = 1;
    win->_sysMesNo = messageNo;
    win->_sysStat = 0;
}

void beNDMWLoadIntf2MesWin__EndSystemMessage(beNDMWLoadIntf2MesWin *win) {
    win->_isSystemMes = 0;
    if (win->_isDisp == 1) {
        if (win->_isCtrl == 1) {
            switch (win->_kindCtrl) {
            case 0:
                beNDMWLoadIntf2MesWin__RequestQuestion(win, win->_mesNo, win->_curPoint);
                return;
            case 1:
                beNDMWLoadIntf2MesWin__RequestPrompt(win, win->_mesNo);
                return;
            }
        } else {
            beNDMWLoadIntf2MesWin__RequestMessage(win, win->_mesNo);
        }
    } else {
        beNDMWLoadIntf2MesWin__RequestMesErase(win);
    }
}

/* The interface's const accessor for its memory-card utility; it takes the interface by reference, as
 * a member function takes `this`. The compiler does not reuse a loop guard's read of a const object
 * in the loop's body, so the loop below loads the utility again for each use. */
static inline beNDMWMcUtilCtrl *mcUtilCtrl(const beNDMWLoadCtrl2CommonIntf &intf) { return (beNDMWMcUtilCtrl *)intf._mcUtilCtrl; }

void beNDMWLoadCtrl2CommonIntf__UpdateCutConnect(beNDMWLoadCtrl2CommonIntf *intf) {
    int slot;
    int slotPlayer;
    igIntList *accessList;
    int k;
    beNDMWMcUtilCtrl__Update(mcUtilCtrl(*intf));
    PLW(intf, 0)->_isCutConnect = 0;
    PLW(intf, 1)->_isCutConnect = 0;
    PLW(intf, 2)->_isCutConnect = 0;
    PLW(intf, 3)->_isCutConnect = 0;
    for (slot = 0; slot < ((beNDMWMcSlotList *)mcUtilCtrl(*intf)->_slot)->_count; slot++) {
        if (((beNDMWMcSlot **)((beNDMWMcSlotList *)mcUtilCtrl(*intf)->_slot)->_data)[slot]->_isConnect == 0) {
            for (slotPlayer = 0; slotPlayer < ((beNDMWLoadSlotPlayerList *)intf->_slotSaveData)->_count; slotPlayer++) {
                if (slot == ((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)intf->_slotSaveData)->_data)[slotPlayer]->_connectNO) {
                    accessList = (igIntList *)((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)intf->_slotSaveData)->_data)[slotPlayer]->_accessPlList;
                    for (k = 0; k < accessList->_count; k++) {
                        PLW(intf, ((int *)accessList->_data)[k])->_isCutConnect = 1;
                    }
                }
            }
        }
    }
}

int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int promptNo, int questionNo, int cursor, int depth) {
    int point;
    int result;
    int state;
    beNDMWLoadSavePlWork *work;

    result = 0;
    state = 0;
    switch (depth) {
    case 0:
        state = PLW(intf, player)->_sysStat0;
        break;
    case 1:
        state = PLW(intf, player)->_sysStat1;
        break;
    case 2:
        state = PLW(intf, player)->_sysStat2;
        break;
    case 3:
        state = PLW(intf, player)->_sysStat3;
        break;
    }
    switch (state) {
    case 0:
        beNDMWLoadIntf2MesWin__RequestPrompt(mesWin, promptNo);
        state += 1;
        break;
    case 1:
        if (beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) == 0) {
            state += 1;
        }
        break;
    case 2:
        beNDMWLoadIntf2MesWin__RequestQuestion(mesWin, questionNo, cursor);
        state += 1;
        break;
    case 3:
        if (beNDMWLoadIntf2MesWin__GetIsCtrl(mesWin) == 0) {
            point = beNDMWLoadIntf2MesWin__GetCurPoint(mesWin);
            switch (point) {
            case 0:
                result = 1;
                break;
            case 1:
                result = 2;
                break;
            }
        }
        break;
    }
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state;
        work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth) {
    int result;
    int state;
    beNDMWMcUtilCtrl *util;
    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 3, slot);
        state += 1;
        break;
    case 1:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: state += 1; break;
            default: result = 2; break;
            }
        }
        break;
    case 2:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 1, slot);
        state += 1;
        break;
    case 3:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: result = 1; break;
            default: result = 2; break;
            }
        }
        break;
    }
    switch (depth) {
    case 0: {
        beNDMWLoadSavePlWork *r = PLW(intf, player);
        r->_sysStat0 = state; r->_sysStat3 = 0; r->_sysStat2 = 0; r->_sysStat1 = 0;
        break; }
    case 1: {
        beNDMWLoadSavePlWork *r = PLW(intf, player);
        r->_sysStat1 = state; r->_sysStat3 = 0; r->_sysStat2 = 0;
        break; }
    case 2: {
        beNDMWLoadSavePlWork *r = PLW(intf, player);
        r->_sysStat2 = state; r->_sysStat3 = 0;
        break; }
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

extern "C" {
PlayerModelRow g_playerModelRow[17] = {
    {"p_agumon", "SQ_agumonOPEN", "SQ_p_agumon"},
    {"p_vmon", "SQ_vmonOPEN", "SQ_p_vmon"},
    {"p_girumon", "SQ_girumonOPEN", "SQ_p_girumon"},
    {"p_dorumon", "SQ_dorumonOPEN", "SQ_p_dorumon"},
    {"p_weregaru", "SQ_weregaruOPEN", "SQ_p_weregaru"},
    {"p_hekabut", "SQ_hekabutOPEN", "SQ_p_hekabut"},
    {"p_wargrey", "SQ_wargreyOPEN", "SQ_p_wargrey"},
    {"p_angelr", "SQ_angelrOPEN", "SQ_p_angelr"},
    {"p_beelzeb", "SQ_beelzebOPEN", "SQ_p_beelzeb"},
    {"p_alpha", "SQ_alphaOPEN", "SQ_p_alpha"},
    {"p_bwargrey", "SQ_bwargreyOPEN", "SQ_p_bwargrey"},
    {"p_impdrafm", "SQ_impdrafmOPEN", "SQ_p_impdrafm"},
    {"p_impdrapm", "SQ_impdrapmOPEN", "SQ_p_impdrapm"},
    {"p_metalgaru", "SQ_metalgaruOPEN", "SQ_p_metalgaru"},
    {"p_dukecrim", "SQ_dukecrimOPEN", "SQ_p_dukecrim"},
    {"p_susanoo", "SQ_susanooOPEN", "SQ_p_susanoo"},
    {"", "SQ_nofaceOPEN", "SQ_p_noface"}
};
}

int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth) {
    int result;
    int state;
    int messageNo;
    beNDMWLoadSavePlWork *work;
    beNDMWMcUtilCtrl *util;
    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        messageNo = -1;
        switch (intf->_kindHard) {
        case 0: messageNo = (player << 16) | 0x1003; break;
        case 1: messageNo = (player << 16) | 0x2003; break;
        case 2: messageNo = (player << 16) | 0x3003; break;
        }
        beNDMWLoadIntf2MesWin__RequestMessage(mesWin, messageNo);
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 6, slot);
        state += 1;
        break;
    case 1:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: state += 1; break;
            default: result = 2; break;
            }
        }
        break;
    case 2:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 0, slot);
        beBaseInfoRam_StartTimer((beBaseInfoRam *)intf->_inforam, "MakeDataTime", 0xB2D05E00ULL);
        state += 1;
        break;
    case 3:
        if (MCSLOT(intf, slot)->_isConnect == 1) {
            if (beBaseInfoRam_IsTimerExpired((beBaseInfoRam *)intf->_inforam, "MakeDataTime") == 1) {
                state += 1;
                goto waitResult;
            }
            break;
        } else {
            state += 1;
        }
    case 4:
    waitResult:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: result = 1; break;
            default: result = 2; break;
            }
        }
        break;
    }
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state; work->_sysStat3 = 0; work->_sysStat2 = 0; work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state; work->_sysStat3 = 0; work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state; work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

static inline int countOf(const igIntList *list) { return list->_count; }

int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth) {
    int result;
    int state;
    void *alloc;
    int count;
    igIntList *accessList;
    int i;
    int j;
    beNDMWLoadSavePlWork *work;
    unsigned short *unicodeText;
    int charIndex;
    int nextState;
    unsigned short *digimonName;

    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 4, (int)slot);
        nextState = state + 1;
        goto storeState;
    case 1:
        if (MCU(intf)->_isResult == 1) {
            result = 2;
            switch (MCU(intf)->_result) {
            case 2: {
                result = 1;
                ALLOC(alloc, intf);
                SlotPlayerRef slotPlayer((igObject *)beNDMWLoadSlotPlayer_Create((int)alloc));
                for (i = 0; i < 4; i++) {
                    ALLOC(alloc, intf);
                    DegiDataRef degi((igObject *)beNDMWDegiData_Create((int)alloc));
                    ((Gap::Core::igObjectList *)(SLOT_PLAYER(slotPlayer.p)->_saveDataList))->append((Gap::Core::igObject *)degi.p);
                }
                beNDMWLoadSlotPlayer__ReadFromBuffer((beNDMWLoadSlotPlayer *)slotPlayer.p, (int)(((beSaveDataDeliver *)MCU(intf)->_svData)->_data));
                SLOT_PLAYER(slotPlayer.p)->_connectNO = slot;
                accessList = (igIntList *)SLOT_PLAYER(slotPlayer.p)->_accessPlList;
                count = accessList->_count;
                if (count < accessList->_capacity) accessList->_count = countOf(accessList) + 1;
                else ((Gap::Core::igDataList *)accessList)->resizeAndSetCount(count + 1, 4);
                ((int *)accessList->_data)[count] = player;
                ((Gap::Core::igObjectList *)intf->_slotSaveData)->append((Gap::Core::igObject *)slotPlayer.p);
                for (j = 0; j < 4; j++) {
                    DegiDataRef degi((igObject *)((beNDMWDegiData **)((igObjectList *)SLOT_PLAYER(slotPlayer.p)->_saveDataList)->_data)[j]);
                    if (degi.p != 0) REFS(degi.p) = REFS(degi.p) + 1;
                    if (DEGI(degi.p)->_isUse == 1 && DNAME(DEGI(degi.p))[0] != 0xFFFF) {
                        digimonName = (unsigned short *)DEGI(degi.p)->_dmName;
                        beFont *font = (beFont *)igInsightCore_FindManager((igInsightCore *)intf->_insight, g_beFont_metaObject);
                        igSmartPointer<beUnicodeObj> str(beFont_ConvertToUnicode(font, (const char *)digimonName));
                        unicodeText = (unsigned short *)str->_buffer;
                        for (charIndex = 0; ; ) {
                            ((unsigned short *)DEGI(degi.p) + 5)[charIndex] /* matching construct: object-based index keeps the addu operand order */ = unicodeText[charIndex];
                            if (unicodeText[charIndex] == 0) break;
                            charIndex++;
                            if (charIndex >= 8) break;
                        }
                        for (; charIndex < 8; charIndex++) {
                            ((unsigned short *)DEGI(degi.p) + 5)[charIndex] = 0;
                        }
                        DNAME(DEGI(degi.p))[0] = 0xFFFF;
                    }
                }
                PLW(intf, player)->_haveSaveData = (int)slotPlayer.p;
                /* matching construct: leaving the block through this jump to the state store releases the slot
                 * player on the jump path, which keeps retail's branch after the release; falling out of the
                 * switch folds it away */
                nextState = state;
                goto storeState;
            }
            }
        }
        break;
    }
    nextState = state;
storeState:
    state = nextState;
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state;
        work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

int beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int saveIndex, int depth) {
    int result;
    int state;
    beNDMWLoadSavePlWork *work;
    beNDMWMcUtilCtrl *util;
    result = 0;
    state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWLoadSlotPlayer__WriteToBuffer((beNDMWLoadSlotPlayer *)PLW(intf, player)->_haveSaveData, ((beSaveDataDeliver *)MCU(intf)->_svData)->_data, saveIndex, ((beNDMWDegiData **)((beNDMWDegiDataList *)intf->_gameUseData)->_data)[player]);
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 5, slot);
        beBaseInfoRam_StartTimer((beBaseInfoRam *)intf->_inforam, "SaveDataTime", 0xB2D05E00ULL);
        state += 1;
        break;
    case 1:
        if (MCSLOT(intf, slot)->_isConnect == 1) {
            if (beBaseInfoRam_IsTimerExpired((beBaseInfoRam *)intf->_inforam, "SaveDataTime") == 1) {
                state += 1;
                goto waitResult;
            }
            break;
        } else {
            state += 1;
        }
    case 2:
    waitResult:
        util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) {
            case 2: result = 1; beNDMWDegiData__CopyFrom(((beNDMWDegiData **)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)PLW(intf, player)->_haveSaveData)->_saveDataList)->_data)[saveIndex], ((beNDMWDegiData **)((beNDMWDegiDataList *)intf->_gameUseData)->_data)[player]); break;
            default: result = 2; break;
            }
        }
        break;
    }
    switch (depth) {
    case 0:
        work = PLW(intf, player);
        work->_sysStat0 = state; work->_sysStat3 = 0; work->_sysStat2 = 0; work->_sysStat1 = 0;
        break;
    case 1:
        work = PLW(intf, player);
        work->_sysStat1 = state; work->_sysStat3 = 0; work->_sysStat2 = 0;
        break;
    case 2:
        work = PLW(intf, player);
        work->_sysStat2 = state; work->_sysStat3 = 0;
        break;
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(beNDMWLoadCtrl2CommonIntf *intf, int player, beNDMWLoadIntf2MesWin *mesWin, int slot, int depth) {
    int result = 0;
    int state = 0;
    switch (depth) {
    case 0: state = PLW(intf, player)->_sysStat0; break;
    case 1: state = PLW(intf, player)->_sysStat1; break;
    case 2: state = PLW(intf, player)->_sysStat2; break;
    case 3: state = PLW(intf, player)->_sysStat3; break;
    }
    switch (state) {
    case 0:
        beNDMWMcUtilCtrl__Request((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl, 2, slot);
        state++;
        MCU(intf)->_isFormatRun = 1;
        break;
    case 1: {
        beNDMWMcUtilCtrl *util = MCU(intf);
        if (util->_isResult == 1) {
            switch (util->_result) { case 2: result = 1; break; default: result = 2; break; }
        }
        break;
    }
    }
    switch (depth) {
    case 0: {
        beNDMWLoadSavePlWork *work = PLW(intf, player);
        work->_sysStat0 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        break;
    }
    case 1: {
        beNDMWLoadSavePlWork *work = PLW(intf, player);
        work->_sysStat1 = state;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        break;
    }
    case 2: {
        beNDMWLoadSavePlWork *work = PLW(intf, player);
        work->_sysStat2 = state;
        work->_sysStat3 = 0;
        break;
    }
    case 3:
        PLW(intf, player)->_sysStat3 = state;
        break;
    }
    return result;
}

void beNDMWLoadCtrl2CommonIntf__GiveCtrlTo(beNDMWLoadCtrl2CommonIntf *intf, int player) {
    int i;
    beNDMWLoadSavePlWork *work;
    i = 0;
    do {
        work = PLW(intf, i);
        work->_sysStat0 = 1;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        PLW(intf, i)->_isCtrl = 0;
        PLW(intf, i)->_sysCount0 = 60;
        i++;
    } while (i < 4);
    work = PLW(intf, player);
    work->_sysStat0 = 0;
    work->_sysStat3 = 0;
    work->_sysStat2 = 0;
    work->_sysStat1 = 0;
    PLW(intf, player)->_isCtrl = 1;
    PLW(intf, player)->_sysCount0 = 0;
}

void beNDMWLoadCtrl2CommonIntf__StartUtilFor(beNDMWLoadCtrl2CommonIntf *intf, int player, int state) {
    int playerOffset;
    int i;
    int offset;
    int *count;
    beNDMWLoadSavePlWork *work;

    i = 0;
    offset = 0;
    do {
        work = PLW_AT(intf->_flagWork, offset);
        work->_sysStat0 = 1;
        work->_sysStat3 = 0;
        work->_sysStat2 = 0;
        work->_sysStat1 = 0;
        PLW_AT(intf->_flagWork, offset)->_isCtrl = 0;
        work = PLW_AT(intf->_flagWork, offset);
        count = &work->_sysCount0;
        if (*count <= 0) {
            *count = 0xA;
        }
        i += 1;
        offset += 4;
    } while (i < 4);
    playerOffset = player * 4;
    work = PLW_AT(intf->_flagWork, playerOffset);
    work->_sysStat0 = state;
    work->_sysStat3 = 0;
    work->_sysStat2 = 0;
    work->_sysStat1 = 0;
    PLW_AT(intf->_flagWork, playerOffset)->_isCtrl = 1;
    PLW_AT(intf->_flagWork, playerOffset)->_sysCount0 = 0;
    intf->_utilUsePlNo = player;
}

void beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(beNDMWLoadCtrl2CommonIntf *intf, int player) {
    bool found = false;
    beNDMWLoadSlotPlayerList *slotPlayers = (beNDMWLoadSlotPlayerList *)intf->_slotSaveData;
    for (int i = slotPlayers->_count - 1; i >= 0; i--) {
        int offset; igIntList *accessList; int j; int count; igIntList *list;
        accessList = (igIntList *)((beNDMWLoadSlotPlayer **)slotPlayers->_data)[i]->_accessPlList; count = accessList->_count; list = accessList; j = 0;
        if (j < count) { offset = 0;
          do { if (player == *(int*)(list->_data + offset)) { List_RemoveWordAt((igDataList *)accessList, j); found = true; break; } j++; offset += 4; list = accessList; } while (j < count); }
        if (found == true) break;
    }
    if (found == true) {
        for (int i = slotPlayers->_count - 1; i >= 0; i--) {
            beNDMWLoadSlotPlayer *slotPlayer = ((beNDMWLoadSlotPlayer **)slotPlayers->_data)[i];
            if (((igIntList *)slotPlayer->_accessPlList)->_count == 0) {
                igObject::release(slotPlayer);
                List_RemoveWordAt((igDataList *)slotPlayers, i);
                ((beNDMWLoadSlotPlayer **)slotPlayers->_data)[slotPlayers->_count] = 0;
            }
        }
    }
}

/* The size reads as unsigned, so it is loaded before the copy's other arguments. */
static inline unsigned dataSize(const beNDMWDegiData *data) { return data->_dataSize; }

void beNDMWDegiData__CopyFrom(beNDMWDegiData *dst, beNDMWDegiData *src) {
    memcpy((void *)dst->_data, (const void *)src->_data, dataSize(dst));
    beNDMWDegiData__UpdateFieldsFromData(dst);
}

void beNDMWDegiData__UpdateFieldsFromData(beNDMWDegiData *degi) {
    DegiSaveRecord *record;
    int name, v, old;
    int *header;
    record = (DegiSaveRecord *)degi->_data;
    degi->_isUse = record->isUse;
    degi->_lv = record->level;
    degi->_hp = record->hp;
    degi->_maxHp = record->maxHp;
    degi->_mp = record->mp;
    degi->_maxMp = record->maxMp;
    if (g_stringPool == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
        g_stringPool = (StringPool *)v;
    }
    name = ((int)StringPool_Intern(g_stringPool, record->digimonName));
    old = degi->_dmkind;
    if (old != 0) {
        header = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
    }
    degi->_dmkind = name;
    if (g_stringPool == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
        g_stringPool = (StringPool *)v;
    }
    name = ((int)StringPool_Intern(g_stringPool, (char *)record->playerName));
    old = degi->_dmName;
    if (old != 0) {
        header = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
    }
    degi->_dmName = name;
    {
        int n;
        unsigned short *pa;
        char *p;
        pa = record->playerName;
        n = 0;
        p = (char *)degi;
        degi->_id = record->unique;
        do {
            unsigned short v = *pa;
            if (v == 0) break;
            *(unsigned short *)(p + 8) = v;
            n += 1;
            pa += 1;
            p += 2;
        } while (n < 9);
        for (; n < 9; n++) {
            *(unsigned short *)((char *)degi + n * 2 + 8) = 0;
        }
    }
}


void beNDMWDegiData__LoadFromBuffer(beNDMWDegiData *degi, int buffer) {
    memcpy((void *)degi->_data, (const void *)buffer, dataSize(degi));
    beNDMWDegiData__UpdateFieldsFromData((beNDMWDegiData *)degi);
}

void beNDMWDegiData__LoadFromProperties(beNDMWDegiData *degi, int props) {
    DegiSaveRecord *record = (DegiSaveRecord *)degi->_data;
    record->isUse = igProperty_GetRecordByte((igObject *)props, "ISUSE")->_data;
    record->unique = igProperty_GetRecord((igObject *)props, "UNIQUE")->_data;
    record->level = igProperty_GetRecord((igObject *)props, "LEVEL")->_data;
    record->hp = igProperty_GetRecord((igObject *)props, "HP")->_data;
    record->maxHp = igProperty_GetRecord((igObject *)props, "MHP")->_data;
    record->mp = igProperty_GetRecord((igObject *)props, "MP")->_data;
    record->maxMp = igProperty_GetRecord((igObject *)props, "MMP")->_data;
    {
        igStringObjList *sl = (igStringObjList *)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "PLAYERNAME")->_data);
        if (sl->_count != 0) {
            igSmartPointer<beUnicodeObj> s(((beUnicodeObj **)sl->_data)[0], kRetainReference);
            {
                unsigned short *src;
                unsigned short *base;
                int i;
                unsigned short *dst;
                base = record->playerName;
                i = 0;
                dst = base;
                src = (unsigned short *)s.p->_buffer;
            L1: dst[1] = *src;
                if (*src == 0) { dst = base + i; goto T; }
                src++; dst++; i++; goto L1;
            B:  dst[1] = 0; dst++; i++;
            T:  if (i < 8) goto B;
                base[0] = 0xffff;
            }
        }
    }
    {
        beDataObjString *rs = igProperty_GetRecordString((igObject *)props, "DIGIMONNAME");
        char *str = (char *)rs->_data;
        if (str != 0) strcpy(record->digimonName, str);
    }
    record->xdata = igProperty_GetRecord((igObject *)props, "XDATA")->_data;
    record->bit = igProperty_GetRecord((igObject *)props, "BIT")->_data;
    IDS(record->deviceFolder, "DEVICEFOLDER", 36, 1)
    IDS(record->diskFolder, "DISKFOLDER", 12, 1)
    BYTES(record->cardList, igProperty_GetRecordArray, "CARDLIST")
    IDS(record->bankDevice, "BANKDEVICE", 96, 0)
    record->bankBit = igProperty_GetRecord((igObject *)props, "BANKBIT")->_data;
    FINDN(record->powerSocket, "POWERSOCKET", 3)
    FINDN(record->powerPocket, "POWERPOCKET", 5)
    FIND1(record->mainSlot, "MAINSLOT")
    FINDV(record->mainPocket, "MAINPOCKET")
    FIND1(record->subSlot, "SUBSLOT")
    BYTES(record->baseFlag, igProperty_GetRecordArray, "BASE_FLAG")
    BYTES(record->baseFlagFolder, igProperty_GetRecordArray, "BASE_FLAGFOLDER")
    INTS(record->baseCounter, igProperty_GetRecordIntList, "BASE_COUNTER")
    BYTES(record->baseIsUse, igProperty_GetRecordArray, "BASE_ISUSE")
    INTS(record->baseLevel, igProperty_GetRecordIntList, "BASE_LEVEL")
    INTS(record->baseExp, igProperty_GetRecordIntList, "BASE_EXP")
    INTS(record->baseSkill, igProperty_GetRecordIntList, "BASE_SKILL")
    INTS(record->baseUpcnt, igProperty_GetRecordIntList, "BASE_UPCNT")
    beNDMWDegiData__UpdateFieldsFromData((beNDMWDegiData *)degi);
}

/* matching construct: one releasing holder class per retail destructor copy (the table at 0x544c20 names 0x3d9d50, 0x3d9cd0, 0x3d9c50, 0x3d9bd0 and 0x3b9ba0; the last is not the copy other members of this file name for their holders) */
template <int K> struct CreatedItemRef { igObject *p; CreatedItemRef(igObject *o) : p(o) {} ~CreatedItemRef() { igObject *o = p; igObject::release(o); } };

static inline int itemAllocator(void *owner) {
    int alloc = (int)((Gap::Core::igObject *)owner)->getMemoryPool();
    int a;
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    }
    return a;
}

ItemRef beNDMWDegiData__CreateItem(void *owner, int id) {
    int kind = (id >> 12) & 0xF;
    if (kind == 0) {
        {
            CreatedItemRef<1> item((igObject *)beNDMWItemWeapon_Create(itemAllocator(owner)));
            ((beNDMWItemBaseDispatchView *)item.p)->Unpack(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 1) {
        {
            CreatedItemRef<2> item((igObject *)beNDMWItemBlueArmor_Create(itemAllocator(owner)));
            ((beNDMWItemBaseDispatchView *)item.p)->Unpack(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 2) {
        {
            CreatedItemRef<3> item((igObject *)beNDMWItemYellowArmor_Create(itemAllocator(owner)));
            ((beNDMWItemBaseDispatchView *)item.p)->Unpack(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 3) {
        {
            CreatedItemRef<4> item((igObject *)beNDMWItemAbilityChip_Create(itemAllocator(owner)));
            ((beNDMWItemBaseDispatchView *)item.p)->Unpack(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else if (kind == 4) {
        {
            CreatedItemRef<5> item((igObject *)beNDMWItemDisk_Create(itemAllocator(owner)));
            ((beNDMWItemBaseDispatchView *)item.p)->Unpack(id);
            return ItemRef((RefCounted *)item.p, kRetainReference);
        }
    } else {
        return ItemRef(0, kRetainReference);
    }
}

void beNDMWDegiData__StoreToProperties(beNDMWDegiData *degi, void *props, int font) {
    DegiSaveRecord *record = (DegiSaveRecord *)degi->_data;
    igProperty_GetRecordByte((igObject *)props, "ISUSE")->_data = record->isUse;
    igProperty_GetRecord((igObject *)props, "UNIQUE")->_data = record->unique;
    igProperty_GetRecord((igObject *)props, "LEVEL")->_data = record->level;
    igProperty_GetRecord((igObject *)props, "HP")->_data = record->hp;
    igProperty_GetRecord((igObject *)props, "MHP")->_data = record->maxHp;
    igProperty_GetRecord((igObject *)props, "MP")->_data = record->mp;
    igProperty_GetRecord((igObject *)props, "MMP")->_data = record->maxMp;
    char *digimonName = record->digimonName;
    beDataObjString *rs = igProperty_GetRecordString((igObject *)props, "DIGIMONNAME");
    if (((void *)g_stringPool) == 0) {
        void *p = StringPool_Allocate(16);
        if (p != 0)
            p = StringPool_Construct((StringPool *)p);
        ((void *)g_stringPool) = p;
    }
    char *interned = StringPool_Intern((StringPool *)g_stringPool, digimonName);
    char *old = (char *)rs->_data;
    if (old != 0) {
        int *hdr = (int *)old - 2;
        int rc = hdr[1] - 1;
        hdr[1] = rc;
        if (rc == 0)
            StringChunk_ReleaseHeader((StringChunk *)hdr[0], (StringTokenHeader *)hdr);
    }
    rs->_data = (int)interned;
    igObjectList *playerNameList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "PLAYERNAME")->_data);
    ObjectListOps::Clear(playerNameList);
    int alloc = (int)((Gap::Core::igObject *)degi)->getMemoryPool();
    int a;
    if (g_useOwnerAllocator != 0)
        a = alloc;
    else
        a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    {
    ChunkRef nameText((RefCounted *)beUnicodeObj_Create(a));
    beUnicodeObj_AllocateBuffer((beUnicodeObj *)nameText.p, 8);
    unsigned short *dst = (unsigned short *)((beUnicodeObj *)nameText.p)->_buffer;
    unsigned short *q = record->playerName;
    if (q[0] != 0xffff) {
        igSmartPointer<beUnicodeObj> converted(beFont_ConvertToUnicode((beFont *)font, (const char *)degi->_dmName));
        unsigned short *src = (unsigned short *)converted->_buffer;
        int i = 0;
        for (; i < 8; i++) {
            dst[i] = src[i];
            if (src[i] == 0)
                break;
        }
        for (; i < 8; i++)
            dst[i] = 0;
    } else {
        int i = 0;
        for (; i < 8; i++) {
            dst[i] = (q + 1)[i];
            if (dst[i] == 0)
                break;
        }
        for (; i < 8; i++)
            dst[i] = 0;
    }
    ((Gap::Core::igObjectList *)playerNameList)->append((Gap::Core::igObject *)nameText.p);
    }
    igProperty_GetRecord((igObject *)props, "XDATA")->_data = record->xdata;
    igProperty_GetRecord((igObject *)props, "BIT")->_data = record->bit;
    igObjectList *deviceFolderList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data);
    ObjectListOps::Clear(deviceFolderList);
    for (int i = 0; i < 36; i++) {
        int id = record->deviceFolder[i];
        if (id == -1)
            break;
        ItemRef item = beNDMWDegiData__CreateItem(degi, id);
        ((Gap::Core::igObjectList *)deviceFolderList)->append((Gap::Core::igObject *)item.p);
    }
    igObjectList *diskFolderList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DISKFOLDER")->_data);
    ObjectListOps::Clear(diskFolderList);
    for (int i = 0; i < 12; i++) {
        int id = record->diskFolder[i];
        if (id == -1)
            break;
        ItemRef item = beNDMWDegiData__CreateItem(degi, id);
        ((Gap::Core::igObjectList *)diskFolderList)->append((Gap::Core::igObject *)item.p);
    }
    igUnsignedCharList *cardList = (igUnsignedCharList *)((igTDataList<unsigned char> *)igProperty_GetRecordArray((igObject *)props, "CARDLIST")->_data);
    for (int i = 0; i < 50; i++) {
        unsigned char v = record->cardList[i];
        if (cardList->_count != 0 && i >= 0 && i < cardList->_count)
            ((unsigned char *)cardList->_data)[i] = v;
    }
    igObjectList *bankDeviceList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "BANKDEVICE")->_data);
    ObjectListOps::Clear(bankDeviceList);
    for (int i = 0; i < 96; i++) {
        int id = record->bankDevice[i];
        if (id == -1)
            break;
        ItemRef item = beNDMWDegiData__CreateItem(degi, id);
        ((Gap::Core::igObjectList *)bankDeviceList)->append((Gap::Core::igObject *)item.p);
    }
    igProperty_GetRecord((igObject *)props, "BANKBIT")->_data = record->bankBit;
    igObjectList *powerSocketList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "POWERSOCKET")->_data);
    ObjectListOps::Clear(powerSocketList);
    for (int i = 0; i < 3; i++) {
        int id = record->powerSocket[i];
        if (id != -1) {
            ItemRef item(((RefCounted **)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data)->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ((Gap::Core::igObjectList *)powerSocketList)->append((Gap::Core::igObject *)item.p);
        } else {
            ((Gap::Core::igObjectList *)powerSocketList)->append(0);
        }
    }
    igObjectList *powerPocketList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "POWERPOCKET")->_data);
    ObjectListOps::Clear(powerPocketList);
    for (int i = 0; i < 5; i++) {
        int id = record->powerPocket[i];
        if (id != -1) {
            ItemRef item(((RefCounted **)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data)->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ((Gap::Core::igObjectList *)powerPocketList)->append((Gap::Core::igObject *)item.p);
        } else {
            ((Gap::Core::igObjectList *)powerPocketList)->append(0);
        }
    }
    igObjectList *mainSlotList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "MAINSLOT")->_data);
    ObjectListOps::Clear(mainSlotList);
    {
        int id = record->mainSlot;
        if (id != -1) {
            ItemRef item(((RefCounted **)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data)->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ((Gap::Core::igObjectList *)mainSlotList)->append((Gap::Core::igObject *)item.p);
        } else {
            ((Gap::Core::igObjectList *)mainSlotList)->append(0);
        }
    }
    igObjectList *mainPocketList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "MAINPOCKET")->_data);
    ObjectListOps::Clear(mainPocketList);
    for (int i = 0; i < 5; i++) {
        int id = record->mainPocket[i];
        if (id != -1) {
            ItemRef item(((RefCounted **)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data)->_data)[id]);
            if (item.p)
                item.p->refCount++;
            ((Gap::Core::igObjectList *)mainPocketList)->append((Gap::Core::igObject *)item.p);
        } else {
            ((Gap::Core::igObjectList *)mainPocketList)->append(0);
        }
    }
    igObjectList *subSlotList = ((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "SUBSLOT")->_data);
    int subSlotId = record->subSlot;
    ObjectListOps::Clear(subSlotList);
    if (subSlotId != -1) {
        ItemRef item(((RefCounted **)((igObjectList *)igProperty_GetRecordFolder((igObject *)props, "DEVICEFOLDER")->_data)->_data)[subSlotId]);
        if (item.p)
            item.p->refCount++;
        ((Gap::Core::igObjectList *)subSlotList)->append((Gap::Core::igObject *)item.p);
    } else {
        ((Gap::Core::igObjectList *)subSlotList)->append(0);
    }
    igUnsignedCharList *baseFlagList = (igUnsignedCharList *)((igTDataList<unsigned char> *)igProperty_GetRecordArray((igObject *)props, "BASE_FLAG")->_data);
    for (int i = 0; i < 1024; i++) {
        unsigned char v = record->baseFlag[i];
        if (baseFlagList->_count != 0 && i >= 0 && i < baseFlagList->_count)
            ((unsigned char *)baseFlagList->_data)[i] = v;
    }
    igUnsignedCharList *baseFlagFolderList = (igUnsignedCharList *)((igTDataList<unsigned char> *)igProperty_GetRecordArray((igObject *)props, "BASE_FLAGFOLDER")->_data);
    for (int i = 0; i < 12; i++) {
        unsigned char v = record->baseFlagFolder[i];
        if (baseFlagFolderList->_count != 0 && i >= 0 && i < baseFlagFolderList->_count)
            ((unsigned char *)baseFlagFolderList->_data)[i] = v;
    }
    igIntList *baseCounterList = ((igIntList *)igProperty_GetRecordIntList((igObject *)props, "BASE_COUNTER")->_data);
    for (int i = 0; i < 16; i++) {
        int v = record->baseCounter[i];
        if (baseCounterList->_count != 0 && i >= 0 && i < baseCounterList->_count)
            ((int *)baseCounterList->_data)[i] = v;
    }
    igUnsignedCharList *baseIsUseList = (igUnsignedCharList *)((igTDataList<unsigned char> *)igProperty_GetRecordArray((igObject *)props, "BASE_ISUSE")->_data);
    for (int i = 0; i < 16; i++) {
        unsigned char v = record->baseIsUse[i];
        if (baseIsUseList->_count != 0 && i >= 0 && i < baseIsUseList->_count)
            ((unsigned char *)baseIsUseList->_data)[i] = v;
    }
    igIntList *baseLevelList = ((igIntList *)igProperty_GetRecordIntList((igObject *)props, "BASE_LEVEL")->_data);
    for (int i = 0; i < 16; i++) {
        int v = record->baseLevel[i];
        if (baseLevelList->_count != 0 && i >= 0 && i < baseLevelList->_count)
            ((int *)baseLevelList->_data)[i] = v;
    }
    igIntList *baseExpList = ((igIntList *)igProperty_GetRecordIntList((igObject *)props, "BASE_EXP")->_data);
    for (int i = 0; i < 16; i++) {
        int v = record->baseExp[i];
        if (baseExpList->_count != 0 && i >= 0 && i < baseExpList->_count)
            ((int *)baseExpList->_data)[i] = v;
    }
    igIntList *baseSkillList = ((igIntList *)igProperty_GetRecordIntList((igObject *)props, "BASE_SKILL")->_data);
    for (int i = 0; i < 144; i++) {
        int v = record->baseSkill[i];
        if (baseSkillList->_count != 0 && i >= 0 && i < baseSkillList->_count)
            ((int *)baseSkillList->_data)[i] = v;
    }
    igIntList *baseUpcntList = ((igIntList *)igProperty_GetRecordIntList((igObject *)props, "BASE_UPCNT")->_data);
    for (int i = 0; i < 176; i++) {
        if (baseUpcntList->_count != 0 && i >= 0 && i < baseUpcntList->_count)
            ((int *)baseUpcntList->_data)[i] = record->baseUpcnt[i];
    }
}

void beNDMWLoadSlotPlayer__WriteToBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer, int replaceIndex, beNDMWDegiData *replacement) {
    int index = replaceIndex;
    beNDMWDegiData *record = replacement;
    int pos = buffer;
    beNDMWDegiDataList *list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
    int i = 0;
    int data, size;
    beNDMWDegiData *degi;
    while (i < list->_count) {
        if (i == index) {
            data = record->_data;
            size = record->_dataSize;
        } else {
            degi = ((beNDMWDegiData **)list->_data)[i];
            data = degi->_data;
            size = degi->_dataSize;
        }
        memcpy((void *)pos, (const void *)data, size);
        list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
        i++;
        pos += size;
    }
}

void beNDMWLoadSlotPlayer__ReadFromBuffer(beNDMWLoadSlotPlayer *slotPlayer, int buffer) {
    int i;
    int offset;
    beNDMWDegiDataList *list;

    list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
    i = 0;
    if (0 < list->_count) {
        offset = 0;
        do {
            beNDMWDegiData__LoadFromBuffer((beNDMWDegiData *)(*(int *)(list->_data + offset)), buffer);
            list = (beNDMWDegiDataList *)slotPlayer->_saveDataList;
            i += 1;
            buffer += ((beNDMWDegiData *)*(int *)(list->_data + offset))->_dataSize;
            offset += 4;
        } while (i < list->_count);
    }
}

void beNDMWMcUtilCtrl__Init(beNDMWMcUtilCtrl *util, int messenger, int kindHard) {
    int i;

    util->_messenger = messenger;
    util->_isRun = 0;
    util->_isResult = 0;
    util->_isRdy = 0;
    switch (kindHard) {
    case 0:
        for (i = 0; i < 5; i++) {
            int owner = (int)((Gap::Core::igObject *)util)->getMemoryPool();
            int alloc = g_useOwnerAllocator ? owner : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
            SlotRef<0> slot(beNDMWMcSlotPS2_Create(alloc));
            ((Gap::Core::igObjectList *)util->_slot)->append((Gap::Core::igObject *)slot.p);
        }
        return;
    case 1:
        for (i = 0; i < 2; i++) {
            int owner = (int)((Gap::Core::igObject *)util)->getMemoryPool();
            int alloc = g_useOwnerAllocator ? owner : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
            SlotRef<1> slot(beNDMWMcSlotGC_Create(alloc));
            ((Gap::Core::igObjectList *)util->_slot)->append((Gap::Core::igObject *)slot.p);
        }
        return;
    case 2:
        for (i = 0; i < 9; i++) {
            int owner = (int)((Gap::Core::igObject *)util)->getMemoryPool();
            int alloc = g_useOwnerAllocator ? owner : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
            SlotRef<2> slot(beNDMWMcSlotXbox_Create(alloc));
            ((Gap::Core::igObjectList *)util->_slot)->append((Gap::Core::igObject *)slot.p);
        }
        break;
    }
}

void beNDMWMcUtilCtrl__Generate(beNDMWMcUtilCtrl *util) {
    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
    beMessenger_AppendInt((beMessenger *)util->_messenger, 4);
    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "GENERATE");
    if (beMessenger_GetBoolCount((beMessenger *)util->_messenger) > 0) {
        util->_isUseUtil = 1;
    } else {
        util->_isUseUtil = 0;
    }
}

unsigned char beNDMWMcUtilCtrl__CheckReady(beNDMWMcUtilCtrl *util) {
    unsigned char ready = 0;
    if (util->_isUseUtil == 1) {
        beMessenger_SendNamed((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1, "ISRDY");
        if (beMessenger_GetBool((beMessenger *)util->_messenger, 0) == 1) {
            util->_isRdy = 1;
            ready = 1;
        }
    } else {
        util->_isRdy = 1;
        ready = 1;
    }
    return ready;
}

void beNDMWMcUtilCtrl__Remove(beNDMWMcUtilCtrl *util) {
    if (util->_isUseUtil == 1) {
        beMessenger_SendNamed((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1, "REMOVE");
    }
}

bool beNDMWMcUtilCtrl__IsRemoved(beNDMWMcUtilCtrl *util) {
    bool removed = false;
    if (util->_isUseUtil == 1) {
        beMessenger_SendNamed((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1, "ISRDY");
        if (beMessenger_GetBool((beMessenger *)util->_messenger, 0) == 0) {
            removed = true;
        }
    } else {
        removed = true;
    }
    return removed;
}

void beNDMWMcUtilCtrl__Request(beNDMWMcUtilCtrl *util, int kind, int slot) {
    util->_tgCon = slot;
    util->_kind = kind;
    util->_result = 0;
    util->_isResult = 0;
    util->_isRun = 1;
    util->_isFormatRun = 0;
    util->_st0 = 0;
    util->_st3 = 0;
    util->_st2 = 0;
    util->_st1 = 0;
}

static inline unsigned int sizeOf(const beSaveDataDeliver *d) { return d->_size; }

void beNDMWMcUtilCtrl__Update(beNDMWMcUtilCtrl *util) {
    if (util->_isRdy == 1) {
        if (util->_isUseUtil == 1) {
            beSvDeliver *deliver;
            beNDMWMcSlotList *slots;
            int i;
            int off;
            beMessenger_SendNamed((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1, "GETDELIVER");
            deliver = (beSvDeliver *)beMessenger_GetObject((beMessenger *)util->_messenger, 0);
            slots = (beNDMWMcSlotList *)util->_slot;
            i = 0;
            if (i < slots->_count) {
                off = 0;
                do {
                    if (*(int *)((char *)((igIntList *)deliver->_actConnect)->_data + off) == 1) {
                        (*(beNDMWMcSlot **)((char *)slots->_data + off))->_isConnect = 1;
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_totalSize = *(int *)((char *)((igIntList *)deliver->_totalSizeList)->_data + off);
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_freeSize = *(int *)((char *)((igIntList *)deliver->_freeSizeList)->_data + off);
                        if (*(int *)((char *)((igIntList *)deliver->_formatList)->_data + off) == 1) {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_isFormat = 1;
                        } else {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)util->_slot)->_data + off))->_isFormat = 0;
                        }
                    } else {
                        (*(beNDMWMcSlot **)((char *)slots->_data + off))->_isConnect = 0;
                    }
                    slots = (beNDMWMcSlotList *)util->_slot;
                    i++;
                    off += 4;
                } while (i < slots->_count);
            }
            if (deliver->_useMtap == 1) {
                util->_isMtap = 1;
            } else {
                util->_isMtap = 0;
            }
        } else {
            int i;
            int offset;
            beNDMWMcSlotList *slots;
            util->_isMtap = 1;
            slots = (beNDMWMcSlotList *)util->_slot;
            i = 0;
            if (i < slots->_count) {
                offset = 0;
                do {
                    i++;
                    (*(beNDMWMcSlot **)((char *)slots->_data + offset))->_isConnect = 1;
                    slots = (beNDMWMcSlotList *)util->_slot;
                    offset += 4;
                } while (i < slots->_count);
            }
        }
    }
    if (util->_isRun == 1) {
        if (util->_isUseUtil == 1) {
            switch (util->_st0) {
            default:
                break;
            case 0:
                switch (util->_kind) {
                case 0:
                    memset((void *)((beSaveDataDeliver *)util->_svData)->_data, 0, sizeOf((beSaveDataDeliver *)util->_svData));
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_AppendObject((beMessenger *)util->_messenger, (igObject *)util->_svData);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REQUEST_FILEMAKE");
                    break;
                case 1:
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REQUEST_FILEFIND");
                    break;
                case 2:
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REQUEST_FORMAT");
                    break;
                case 3:
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REQUEST_USE_CHECK");
                    break;
                case 4:
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_AppendObject((beMessenger *)util->_messenger, (igObject *)util->_svData);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REQUEST_READ_MEDIA");
                    break;
                case 5:
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_AppendObject((beMessenger *)util->_messenger, (igObject *)util->_svData);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REQUEST_WRITE_MEDIA");
                    break;
                case 6:
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REQUEST_GETFREESIZE");
                    break;
                case 7:
                    beMessenger_SelectReceivers((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1);
                    beMessenger_AppendInt((beMessenger *)util->_messenger, util->_tgCon);
                    beMessenger_DispatchSelected((beMessenger *)util->_messenger, "REPORT_GAMEDATA");
                    break;
                }
                util->_st0 = util->_st0 + 1;
                util->_st3 = 0;
                util->_st2 = 0;
                util->_st1 = 0;
                break;
            case 1:
                beMessenger_SendNamed((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1, "ISBUSY");
                if (beMessenger_GetBool((beMessenger *)util->_messenger, 0) == 0) {
                    util->_st0 = util->_st0 + 1;
                    util->_st3 = 0;
                    util->_st2 = 0;
                    util->_st1 = 0;
                }
                break;
            case 2:
                beMessenger_SendNamed((beMessenger *)util->_messenger, "SAVEUTILITY", 0, -1, "GETRESULT");
                util->_result = beMessenger_GetInt((beMessenger *)util->_messenger, 0);
                util->_isRun = 0;
                util->_isResult = 1;
                util->_st0 = util->_st0 + 1;
                util->_st3 = 0;
                util->_st2 = 0;
                util->_st1 = 0;
                break;
            case 3:
                break;
            }
        } else {
            util->_result = 2;
            util->_isRun = 0;
            util->_isResult = 1;
        }
    }
}

void beNDMWLoadCtrl2_Prepare(beNDMWLoadCtrl2 *self) {
    igObject *found;
    igObject *previous;
    if (self->_padManager == 0) {
        found = (igObject *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
        igObject::ref(found);
        previous = (igObject *)self->_padManager;
        igObject::release(previous);
        self->_padManager = (int)found;
    }
}

static inline int st1(const beNDMWLoadCtrl2CtrlData *data) { return data->_st1; }

void beNDMWLoadCtrl2_UpdateRam(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram) {
    beNDMWLoadCtrl2CtrlData *ctrl;
    beNDMWLoadCtrl2CommonIntf *intf;
    int i;
    int readyCount;
    unsigned char allClosed;
    int j;
    beNDMWLoadSavePlWorkList *flagWork;
    int k;
    beNDMWLoadSavePlWorkList *flagList;

    if (ram->_dataList == 0) return;
    {
        if (ram->_dataList == 0) {
            igObject *o;
            igObject *old;
            int base = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
            int a;
            if (g_useOwnerAllocator != 0) { a = base; } else { a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }
            igSmartPointer<igObject> list((igObject *)beBaseInfoDataList_Create(a));
            o = list.p;
            if (o != 0) o->_refCount = o->_refCount + 1;
            old = (igObject *)ram->_dataList;
            igObject::release(old);
            ram->_dataList = (int)o;
        }
        ctrl = (beNDMWLoadCtrl2CtrlData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "CTRL");
        if (ram->_dataList == 0) {
            igObject *o;
            igObject *old;
            int base = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
            int a;
            if (g_useOwnerAllocator != 0) { a = base; } else { a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }
            igSmartPointer<igObject> list((igObject *)beBaseInfoDataList_Create(a));
            o = list.p;
            if (o != 0) o->_refCount = o->_refCount + 1;
            old = (igObject *)ram->_dataList;
            igObject::release(old);
            ram->_dataList = (int)o;
        }
        intf = (beNDMWLoadCtrl2CommonIntf *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "COMMONINTF");
        switch (ctrl->_st0) {
        case 0:
            break;
        case 1:
            switch (ctrl->_st1) {
            case 0:
                beNDMWMcUtilCtrl__Generate((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl);
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 1:
                if (beNDMWMcUtilCtrl__CheckReady((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl) == 1) {
                    ctrl->_st0 = 2;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                }
                break;
            }
            break;
        case 2:
            switch (st1(ctrl)) {
            case 0:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "GENERATE");
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "SQ_OPEN");
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 1:
                switch (ctrl->_st2) {
                case 0:
                    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0);
                    beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_OPEN");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ISSEQNAME");
                    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 0) {
                        if (ctrl->_isTitle == 1) {
                            ctrl->_st2 = ctrl->_st2 + 1;
                            ctrl->_st3 = 0;
                        } else {
                            ctrl->_st1 = ctrl->_st1 + 1;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                        }
                    }
                    break;
                case 1:
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_fadewn01", 0, "ISRUN");
                    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 1) {
                        beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_fadewn01", 0, "SQ_WTIN60");
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    break;
                case 2:
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_fadewn01", 0, "ISRUN");
                    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 0) {
                        ctrl->_st1 = ctrl->_st1 + 1;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                    }
                    break;
                }
                break;
            case 2:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "LOADINTF2_ALL", 0, -1, "GENERATE");
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 3:
                switch (intf->_intfStat) {
                case 0:
                    beNDMWLoadCtrl2CommonIntf__UpdateCutConnect(intf);
                    break;
                case 2:
                    break;
                case 3:
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    break;
                }
                break;
            case 4:
                switch (ctrl->_st2) {
                case 0:
                    i = 0;
                    do {
                        beNDMWLoadSavePlWork *u;
                        PLW(intf, i)->_isClose = 0;
                        u = PLW(intf, i);
                        i++;
                        u->_sysStat0 = 2;
                        u->_sysStat3 = 0;
                        u->_sysStat2 = 0;
                        u->_sysStat1 = 0;
                    } while (i < 4);
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    break;
                case 1:
                    allClosed = 1;
                    j = 0;
                    flagWork = (beNDMWLoadSavePlWorkList *)intf->_flagWork;
                    do {
                        if (((beNDMWLoadSavePlWork **)flagWork->_data)[j]->_isClose != 1) { allClosed = 0; break; }
                        j++;
                        flagWork = (beNDMWLoadSavePlWorkList *)intf->_flagWork;
                    } while (j < 4);
                    if (allClosed == 1) {
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                    }
                    break;
                case 2:
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_fadewn01", 0, "GENERATE");
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_fadewn01", 0, "SQ_BLOUT30");
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "SQ_CLOSE");
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    break;
                case 3:
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_chrselback", 0, "ISRUN");
                    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 0) {
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                    }
                    break;
                case 4: {
                    int common;
                    int difficulty, cameraMode, lightMode;
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "LOADINTF2_ALL", 0, -1, "SETSELECT_DATA");
                    {
                    readyCount = 0;
                    k = 0;
                    goto cnt_pre;
                cnt_body:
                    if (((beNDMWLoadSavePlWork **)flagList->_data)[k]->_isRdy == 1) readyCount++;
                    k++;
                cnt_test:
                    if (k < 4) goto cnt_body;
                    }
                    beMessenger_SendGroup((beMessenger *)self->_messenger, "GAMERAM", "GETCOMMON");
                    common = ((int)beMessenger_GetObject((beMessenger *)self->_messenger, 0));
                    igProperty_GetRecord((igObject *)common, "NINZU")->_data = readyCount;
                    if (ctrl->_isTitle == 1) {
                        difficulty = intf->_difficultMode;
                        igProperty_GetRecord((igObject *)common, "DIFFICULTY")->_data = difficulty;
                        cameraMode = self->_cameraMode;
                        igProperty_GetRecord((igObject *)common, "CAMERAMODE")->_data = cameraMode;
                        lightMode = self->_lightMode;
                        igProperty_GetRecord((igObject *)common, "LIGHTMODE")->_data = lightMode;
                        beMessenger_SendGroup((beMessenger *)self->_messenger, "TITLE2", "GAMESTART");
                    }
                    ctrl->_st0 = 3;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                    break;
                }
                }
                break;
            }
            break;
        case 3:
            switch (ctrl->_st1) {
            case 0:
                beNDMWMcUtilCtrl__Remove((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl);
                ctrl->_st1 = ctrl->_st1 + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                break;
            case 1:
                if (beNDMWMcUtilCtrl__IsRemoved((beNDMWMcUtilCtrl *)intf->_mcUtilCtrl) == 1) {
                    if (ctrl->_isTitle == 0) {
                        beMessenger_SelectReceivers((beMessenger *)self->_messenger, "PLAYERPOINT", 0, -1);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, 4);
                        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETGENERATEPOS");
                    } else {
                        g_mdlEntity = 0;
                        beLua__RunNamedChunk((beLua *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject), "gameStart.lua", 0);
                        beMessenger_SelectReceivers((beMessenger *)self->_messenger, "PLAYERPOINT", 0, -1);
                        beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
                        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETGENERATEPOS");
                    }
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "STAGECTL");
                    beMessenger_AppendString((beMessenger *)self->_messenger, "stagML11");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "NEXTSTAGE");
                    ctrl->_st0 = ctrl->_st0 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                }
                break;
            }
            break;
        }
    }
    return;
cnt_pre:
    flagList = (beNDMWLoadSavePlWorkList *)intf->_flagWork;
    goto cnt_test;
}

int beNDMWLoadCtrl2__GetInfoMeta(void)
{
    return (int)g_beNDMWLoadCtrl2Info_metaObject;
}

/* Registers the load controller with its messenger as the LOADCTRL2 receiver. */
void beNDMWLoadCtrl2_OnAddRam(beNDMWLoadCtrl2 *self, int info)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, "LOADCTRL2");
}

int beNDMWLoadCtrl2_OnMessage(beNDMWLoadCtrl2 *self, beBaseInfoRam *ram, beBaseInfo *info) {
    int message;
    int j;
    int i;
    message = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, LoadCtrl2Message_GetMetaEnum(), (const char *)info->_dataList);
    if (message == 0 || message == 1) {
        if (message == 1) {
            if (beMessenger_GetIntCount((beMessenger *)self->_messenger) > 0) {
                self->_cameraMode = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                self->_lightMode = beMessenger_GetInt((beMessenger *)self->_messenger, 1);
            } else {
                self->_cameraMode = 0;
                self->_lightMode = 0;
            }
        }
        if (ram->_dataList == 0) {
            int a;
            OWNER_ALLOCATOR(a, self);
            {
            igSmartPointer<igObject> list(((igObject *)beBaseInfoDataList_Create(a)));
            igObject *t = list.p;
            if (t != 0) t->_refCount++;
            ReleaseRef::Apply((igObject *)ram->_dataList);
            ram->_dataList = (int)t;
            OWNER_ALLOCATOR(a, self);
            {
            CtrlDataRef ctrl(beNDMWLoadCtrl2CtrlData_Create(a));
            ((Gap::Core::igObjectList *)ram->_dataList)->append((Gap::Core::igObject *)ctrl.p);
            beNDMWLoadCtrl2CtrlData *o = (beNDMWLoadCtrl2CtrlData *)ctrl.p;
            i = 1;
            o->_st0 = i;
            o->_st3 = 0;
            o->_st2 = 0;
            o->_st1 = 0;
            if (message == 1) {
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = i;
                j = 0;
                do {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                    beMessenger_AppendInt((beMessenger *)self->_messenger, j);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GAMEDATAINIT");
                    j++;
                } while (j < 4);
            } else {
                do {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                    beMessenger_AppendInt((beMessenger *)self->_messenger, i);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETPLAYER");
                    if (igProperty_GetRecordByte(beMessenger_GetObject((beMessenger *)self->_messenger, 0), "ISUSE")->_data != 1) {
                        beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                        beMessenger_AppendInt((beMessenger *)self->_messenger, i);
                        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GAMEDATAINIT");
                    }
                    i++;
                } while (i < 4);
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = 0;
            }
            }
            OWNER_ALLOCATOR(a, self);
            {
            CommonIntfRef common(beNDMWLoadCtrl2CommonIntf_Create(a));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_system = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_inforam = (int)ram;
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_insight = self->_insight;
            if (message == 1) {
                ((beNDMWLoadCtrl2CommonIntf *)common.p)->_isTitle = 1;
            }
            i = 0;
            do {
                OWNER_ALLOCATOR(a, self);
                {
                DegiDataRef degi(((igObject *)beNDMWDegiData_Create(a)));
                ((Gap::Core::igObjectList *)(((beNDMWLoadCtrl2CommonIntf *)common.p)->_gameUseData))->append((Gap::Core::igObject *)degi.p);
                }
                OWNER_ALLOCATOR(a, self);
                {
                FlagWorkRef flag(beNDMWLoadSavePlWork_Create(a));
                ((Gap::Core::igObjectList *)(((beNDMWLoadCtrl2CommonIntf *)common.p)->_flagWork))->append((Gap::Core::igObject *)flag.p);
                }
                i++;
            } while (i < 4);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_kindHard = 0;
            beNDMWMcUtilCtrl__Init((beNDMWMcUtilCtrl *)(((beNDMWLoadCtrl2CommonIntf *)common.p)->_mcUtilCtrl), (int)self->_messenger, 0);
            ((Gap::Core::igObjectList *)ram->_dataList)->append((Gap::Core::igObject *)common.p);
            }
            }
        }
        return 1;
    }
    igObject *p = (igObject *)ram->_dataList;
    if (p == 0) return 1;
    if (p == 0) {
        int a;
        OWNER_ALLOCATOR(a, ram);
        {
        igSmartPointer<igObject> fresh(((igObject *)beBaseInfoDataList_Create(a)));
        igObject *t = fresh.p;
        if (t != 0) t->_refCount++;
        ReleaseRef::Apply((igObject *)ram->_dataList);
        ram->_dataList = (int)t;
        }
    }
    ((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "CTRL");
    switch (message) {
    case 2:
        return 1;
    case 3:
        if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) == 0) {
            if (ram->_dataList == 0) {
                int a;
                OWNER_ALLOCATOR(a, ram);
                {
                igSmartPointer<igObject> fresh(((igObject *)beBaseInfoDataList_Create(a)));
                igObject *t = fresh.p;
                if (t != 0) t->_refCount++;
                ReleaseRef::Apply((igObject *)ram->_dataList);
                ram->_dataList = (int)t;
                }
            }
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)((int)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "COMMONINTF")));
        }
        return 1;
    default:
        return 0;
    }
}

int beNDMWLoadCtrl2__GetMeta(void)
{
    return (int)g_beNDMWLoadCtrl2_metaObject;
}

#pragma pop
