#ifndef DW4_BEC_LIBRARY_H
#define DW4_BEC_LIBRARY_H

#include "dw4/reflected.h"
static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }
#define OBJ(m) if (&m) { o = (igObject *)m; if (o != 0) { rc = (int)o->_refCount - 1; o->_refCount = rc; if (((unsigned long long) ((long long) (int)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } } }
#define STR(m) if (&m) { p = (void *)m; if (p != 0) { h = (int *)((char *)(p) - 8); rc = *(int *)((char *)(p) - 4) - 1; *(int *)((char *)(p) - 4) = rc; if (rc == 0) { StringChunk_ReleaseHeader(*h, h); } } }
#define RELEASE_OBJ(o) { \
    if (o) { \
        --(o)->_refCount; \
        if (((unsigned long long)(long long)(o)->_refCount & 0x7fffffULL) == 0) \
            igObject_Destroy(o); \
    } }
#define BEDATABASE_NO_INDEX (-1)
#include "dw4/igTDataList.h"
typedef void (*igMetaObjectCallback)();
typedef igMetaField *(*FieldFactory)(void *);
extern "C" void FUN_0019d4f0(void);
extern "C" igMetaField *igObjectRefMetaField_Create(void *);
extern "C" igMetaField *igStringMetaField_Create(void *);
extern "C" igMetaField *igFloatMetaField_Create(void *);
extern "C" igMetaField *igUnsignedIntMetaField_Create(void *);
extern "C" igMetaField *FUN_00187890(void *);
extern "C" igMetaField *igLongMetaField_Create(void *);
extern "C" igMetaField *igIntMetaField_Create(void *);
extern "C" igMetaField *igBoolMetaField_Create(void *);
extern "C" igMetaField *igMemoryRefMetaField_Create(void *);
extern "C" igMetaField *igShortMetaField_Create(void *);
extern "C" igMetaField *igIntArrayMetaField_Create(void *);
extern "C" igMetaField *igUnsignedShortMetaField_Create(void *);
extern "C" igMetaField *igShortArrayMetaField_Create(void *);
extern "C" igMetaField *igFloatArrayMetaField_Create(void *);
extern "C" igMetaField *igCharArrayMetaField_Create(void *);
extern "C" igMetaField *igUnsignedLongMetaField_Create(void *);
extern "C" igMetaField *igCharMetaField_Create(void *);
extern "C" igMetaField *FUN_00187b50(void *);
extern "C" igMetaField *FUN_00188660(void *);
extern "C" igMetaField *igBoolArrayMetaField_Create(void *);
extern "C" igMetaField *igRawRefMetaField_Create(void *);
extern "C" igMetaField *FUN_001872a0(void *);
extern "C" igMetaField *igEnumMetaField_Create(void *);
extern "C" void FUN_0019ccc0(void);
extern "C" void igNamedObjectList_EnsureRegistered(void);
extern "C" void FUN_001a60c0(void);
extern "C" void FUN_0014ba20(void);
extern "C" void igFloatList_EnsureRegistered(void);
extern "C" void igIntList_EnsureRegistered(void);
extern "C" void igFloatListList_EnsureRegistered(void);
extern "C" void FUN_0018a180(void);
extern "C" void FUN_00195f50(void);
extern "C" void FUN_001a5e90(void);
extern "C" void FUN_00132cf0(void);
extern "C" void FUN_001e42e0(void);
extern "C" void igStringRefList_EnsureRegistered(void);
extern "C" void igDirectory_EnsureRegistered(void);
extern "C" void igStringObj_EnsureRegistered(void);
extern "C" void igInfoList_EnsureRegistered(void);
extern "C" void FUN_0019f330(void);
extern "C" void FUN_00196ad0(void);
extern "C" void FUN_0019cf10(void);
extern "C" void FUN_0019b800(void);
extern "C" void igBoolList_EnsureRegistered(void);
extern "C" void igObjectList_EnsureRegistered(void);
extern "C" void FUN_001964d0(void);
extern "C" void FUN_0019fc00(void);
extern "C" void FUN_0019b270(void);
extern "C" void FUN_00336f10(void);
extern "C" void FUN_0013afe0(void);
extern "C" void FUN_0018a780(void);
extern "C" void FUN_0018a5d0(void);
extern "C" void FUN_00195c00(void);
extern "C" void igLongList_EnsureRegistered(void);
extern "C" void FUN_00189a80(void);
extern "C" void igIntListList_EnsureRegistered(void);
extern "C" void igLuaGlue_EnsureRegistered(void);
extern "C" void FUN_0019dcd0(void);
extern "C" void FUN_00139720(void);
extern "C" void FUN_0013a040(void);
extern "C" void FUN_00139000(void);
extern "C" void FUN_0019e890(void);
extern "C" void FUN_00188190(void);
extern "C" void FUN_0013a5b0(void);
extern "C" void FUN_00459e40(void);
extern "C" void igDirectoryList_EnsureRegistered(void);
extern "C" void igFile_EnsureRegistered(void);
extern "C" void igNamedObject_EnsureRegistered(void);
extern "C" void igCharList_EnsureRegistered(void);
extern "C" void igShortList_EnsureRegistered(void);
extern "C" void FUN_00335260(void);
extern "C" void FUN_0019f7a0(void);
extern "C" void FUN_001a4670(void);
extern "C" void FUN_00232de0(void);
extern "C" void igObject_EnsureRegistered(void);
extern "C" void FUN_0019fa10(void);
extern "C" void FUN_0045b590(void);
extern "C" void FUN_001314b0(void);
extern "C" void FUN_00135f40(void);
extern "C" void FUN_001aa6a0(void);
extern "C" void FUN_001a7b00(void);
extern "C" void FUN_0014e050(void);

extern "C" void FUN_0033bf50(void);
extern "C" void BecLibrary_MarkRegistered(void);
extern "C" void *FUN_0033c900(void);
extern "C" int __dl__FPv(...);
extern "C" int igObject_Destroy(...);
extern "C" void **FUN_0033cda0(void **arg0, short arg1);
extern "C" void **FUN_0033cf20(void **arg0, long long arg1);
extern "C" void **FUN_0033cfa0(void **arg0, int arg1);
extern "C" void **FUN_0033d020(void **arg0, short arg1);
extern "C" void **FUN_0033d120(void **arg0, long long arg1);
extern "C" void **FUN_0033d220(void **arg0, long long arg1);
extern "C" void **FUN_0033d2a0(void **arg0, short arg1);
extern "C" void **FUN_0033d3a0(void **arg0, short arg1);
extern "C" void **FUN_0033d5a0(void **arg0, int arg1);
extern "C" void **FUN_0033d620(void **arg0, short arg1);
extern "C" void **FUN_0033d720(void **arg0, long long arg1);
extern "C" void **FUN_0033d8a0(void **arg0, short arg1);
extern "C" void **FUN_0033d9a0(void **arg0, short arg1);
extern "C" void **FUN_0033dba0(void **arg0, int arg1);
extern "C" void **FUN_0033dc20(void **arg0, short arg1);
extern "C" void **FUN_0033dd20(void **arg0, long long arg1);
extern "C" void **FUN_0033de20(void **arg0, short arg1);
extern "C" void **FUN_0033dea0(void **arg0, short arg1);
extern "C" void **FUN_0033dfa0(void **arg0, short arg1);
extern "C" int *FUN_0033e0a0(int *p);
extern "C" int *FUN_0033e0b0(int *p);
extern "C" int *FUN_0033e0c0(int *p);
extern "C" int *FUN_0033e0d0(int *p);
extern "C" int *FUN_0033e0e0(int *p);
extern "C" int *FUN_0033e0f0(int *p);
extern "C" int *FUN_0033e100(int *p);
extern "C" int *FUN_0033e110(int *p);
extern "C" int *FUN_0033e120(int *p);
extern "C" int *FUN_0033e130(int *p);
extern "C" int *FUN_0033e140(int *p);
extern "C" int *FUN_0033e150(int *p);
extern "C" int *FUN_0033e160(int *p);
extern "C" int *FUN_0033e170(int *p);
extern "C" int *FUN_0033e180(int *p);
extern "C" int *FUN_0033e190(int *p);
extern "C" int *FUN_0033e1a0(int *p);
extern "C" int *FUN_0033e1b0(int *p);
extern "C" int *FUN_0033e1c0(int *p);
extern "C" int *FUN_0033e1d0(int *p);
extern "C" int *FUN_0033e1e0(int *p);
extern "C" int *FUN_0033e1f0(int *p);
extern "C" int *FUN_0033e200(int *p);
extern "C" int *FUN_0033e210(int *p);
extern "C" int *FUN_0033e220(int *p);
extern "C" int *FUN_0033e230(int *p);
extern "C" int *FUN_0033e240(int *p);
extern "C" int *FUN_0033e250(int *p);
extern "C" int *FUN_0033e260(int *p);
extern "C" int *FUN_0033e270(int *p);
extern "C" int *FUN_0033e280(int *p);
extern "C" int *FUN_0033e290(int *p);
extern "C" int *FUN_0033e2a0(int *p);
extern "C" int *FUN_0033e2b0(int *p);
extern "C" int *FUN_0033e2c0(int *p);
extern "C" int *FUN_0033e2d0(int *p);
extern "C" int *FUN_0033e2e0(int *p);
extern "C" int *FUN_0033e2f0(int *p);
extern "C" int *FUN_0033e300(int *p);
extern "C" int igObject_InitHeader(...);
extern "C" int **FUN_0033e310(int **arg0);
extern "C" void igMetaObject_RunStaticInit(...);
extern "C" void FUN_0033e350(void);
extern "C" void * igMetaObject_RegisterClass(...);
extern "C" void *igInsightPlugin_Register(void);
extern "C" int libBecRuntimePlugin_GetVTable(void);
extern "C" void *libBecRuntimePlugin_Register(void);
extern "C" void libBecRuntimePlugin_GetMetaObject(void);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void * igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" void libBecRuntimePlugin_InitFields(void);
extern "C" void *FUN_0033e830(void);
extern "C" int beWeaponInfoRam_GetVTable(void);
extern "C" int Memory_FreeBufferAliasC(...);
extern "C" void FUN_0033ea40(void);
extern "C" void *beWeaponInfoRam_Register(void);
extern "C" void beWeaponInfoRam_GetMetaObject(void);
extern "C" igMetaObject *FUN_0033eaf0(void);
extern "C" void *FUN_0033eb00(void);
extern "C" int FUN_001958f0(...);
extern "C" int FUN_00199450(...);
extern "C" int beWeaponInfo_GetVTable(void);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" void FUN_0033ee30(void);
extern "C" void *beWeaponInfo_Register(void);
extern "C" void beWeaponInfo_GetMetaObject(void);
extern "C" igMetaObject *FUN_0033eef0(void);
extern "C" int FUN_0019cbe0(void);
extern "C" int igNamedObjectList_GetOrCreateMetaObject(...);
extern "C" void beWeaponInfo_InitFields(void);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" igMetaObject *igMetaObject_Create(int);
extern "C" igMetaObject *FUN_0033efe0(void);
extern "C" void *FUN_0033f030(void);
extern "C" int beWeaponSeqDataList_GetVTable(void);
extern "C" void FUN_0033f0c0(void);
extern "C" void *igObjectList_Register(void);
extern "C" void *beWeaponSeqDataList_Register(void);
extern "C" void beWeaponSeqDataList_GetMetaObject(void);
extern "C" void *FUN_0033f170(void);
extern "C" int beWeaponSeqData_GetVTable(void);
extern "C" void FUN_0033f290(void);
extern "C" void *igNamedObject_Register(void);
extern "C" void *beWeaponSeqData_Register(void);
extern "C" void beWeaponSeqData_GetMetaObject(void);
extern "C" void beWeaponSeqData_InitFields(void);
extern "C" igMetaEnum *igMetaEnum_Create(const char *name, const char **names, int *values, int count);
extern "C" igMetaEnum *FUN_0033f3b0(void);
extern "C" int igMetaObject_CreateInstance(...);
extern "C" void beWeapon_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0033f450(void);
extern "C" void *FUN_0033f4a0(void);
extern "C" int beWeapon_GetVTable(void);
extern "C" void **FUN_0033f560(void **arg0, int arg1);
extern "C" void **FUN_0033f6d0(void **arg0, short arg1);
extern "C" void FUN_0033f750(void);
extern "C" void *beWeapon_Register(void);
extern "C" void beWeapon_GetMetaObject(void);
extern "C" igMetaObject *FUN_0033f810(void);
extern "C" void beWeapon_InitFields(void);
extern "C" void FUN_0033f8b0(int arg0);
extern "C" igMetaObject *FUN_0033f8f0(void);
extern "C" int beWeaponAttachDataList_GetVTable(void);
extern "C" void FUN_0033f9d0(void);
extern "C" void *beWeaponAttachDataList_Register(void);
extern "C" void beWeaponAttachDataList_GetMetaObject(void);
extern "C" void FUN_0033fa80(int arg0);
extern "C" int beWeaponAttachData_GetVTable(void);
extern "C" void FUN_0033fbf0(void);
extern "C" void *igObject_Register(void);
extern "C" void *beWeaponAttachData_Register(void);
extern "C" void beWeaponAttachData_GetMetaObject(void);
extern "C" void beWeaponAttachData_InitFields(void);
extern "C" igMetaObject *FUN_0033fd70(void);
extern "C" int igAppearanceListList_GetVTable(void);
extern "C" void FUN_0033fe50(void);
extern "C" void *igAppearanceListList_Register(void);
extern "C" void igAppearanceListList_GetMetaObject(void);
extern "C" igMetaObject *FUN_0033ff00(void);
extern "C" int igModelViewMatrixBoneSelectList_587aa0_GetVTable(void);
extern "C" void FUN_0033ffe0(void);
extern "C" void *igModelViewMatrixBoneSelectList_587aa0_Register(void);
extern "C" void igModelViewMatrixBoneSelectList_587aa0_GetMetaObject(void);
extern "C" void *FUN_00340090(void);
extern "C" int FUN_001338d0(int *, int);
extern "C" int FUN_001354b0(int *, int);
extern "C" int igSmartPointer_igIntList_Destruct(int *, int);
extern "C" int beWaterPlainInfoRam_GetVTable(void);
extern "C" void **FUN_00340240(void **arg0, long long arg1);
extern "C" void FUN_003402c0(void);
extern "C" void *beWaterPlainInfoRam_Register(void);
extern "C" void beWaterPlainInfoRam_GetMetaObject(void);
extern "C" int FUN_0014b980(void);
extern "C" int igFloatListList_GetOrCreateMetaObject(void);
extern "C" int igFloatList_GetOrCreateMetaObject(void);
extern "C" int igIntList_GetOrCreateMetaObject(void);
extern "C" void beWaterPlainInfoRam_InitFields(void);
extern "C" igMetaObject *FUN_00340490(void);
extern "C" void *FUN_003404e0(void);
extern "C" int beWaterMove_GetVTable(void);
extern "C" void FUN_003405c0(void);
extern "C" void *beWaterMove_Register(void);
extern "C" void beWaterMove_GetMetaObject(void);
extern "C" void beWaterMove_InitFields(void);
extern "C" igMetaObject *FUN_00340720(void);
extern "C" void *FUN_00340770(void);
extern "C" int beWaterMoveDataList_GetVTable(void);
extern "C" void FUN_00340800(void);
extern "C" void *beWaterMoveDataList_Register(void);
extern "C" void beWaterMoveDataList_GetMetaObject(void);
extern "C" void *FUN_003408b0(void);
extern "C" int beWaterMoveData_GetVTable(void);
extern "C" void FUN_00340990(void);
extern "C" void *beWaterMoveData_Register(void);
extern "C" void beWaterMoveData_GetMetaObject(void);
extern "C" int FUN_0018a0a0(void);
extern "C" void beWaterMoveData_InitFields(void);
extern "C" void *FUN_00340af0(void);
extern "C" int beWaterPlainInfo_GetVTable(void);
extern "C" void FUN_00340bb0(void);
extern "C" void *beWaterPlainInfo_Register(void);
extern "C" void beWaterPlainInfo_GetMetaObject(void);
extern "C" igMetaEnum *FUN_00340c60(void);
extern "C" void beWaterPlain_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00340d00(void);
extern "C" void *FUN_00340d50(void);
extern "C" int beWaterPlain_GetVTable(void);
extern "C" void FUN_00340e80(void);
extern "C" void *beWaterPlain_Register(void);
extern "C" void beWaterPlain_GetMetaObject(void);
extern "C" void *FUN_00340f30(void);
extern "C" int beUnicode_GetVTable(void);
extern "C" void FUN_00340fc0(void);
extern "C" void *beUnicode_Register(void);
extern "C" void beUnicode_GetMetaObject(void);
extern "C" void *FUN_00341070(void);
extern "C" int beTransformSync_GetVTable(void);
extern "C" void FUN_003411e0(void);
extern "C" void *igTransform_Register(void);
extern "C" void *beTransformSync_Register(void);
extern "C" void beTransformSync_GetMetaObject(void);
extern "C" int FUN_00195e70(void);
extern "C" void beTransformSync_InitFields(void);
extern "C" void beTimer_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00341380(void);
extern "C" void *FUN_003413d0(void);
extern "C" int beTimer_GetVTable(void);
extern "C" void FUN_00341500(void);
extern "C" void *igInfoManager_Register(void);
extern "C" void *beTimer_Register(void);
extern "C" void beTimer_GetMetaObject(void);
extern "C" void beTimer_InitFields(void);
extern "C" igMetaObject *FUN_003416b0(void);
extern "C" void *FUN_00341700(void);
extern "C" int beTimerDataList_GetVTable(void);
extern "C" void FUN_00341790(void);
extern "C" void *beTimerDataList_Register(void);
extern "C" void beTimerDataList_GetMetaObject(void);
extern "C" int beTimerData_GetVTable(void);
extern "C" void FUN_00341950(void);
extern "C" void *beTimerData_Register(void);
extern "C" void beTimerData_GetMetaObject(void);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" void beTimerData_InitFields(void);
extern "C" int beTextureCtrlInfoList_GetVTable(void);
extern "C" void FUN_00341b30(void);
extern "C" void *beTextureCtrlInfoList_Register(void);
extern "C" void beTextureCtrlInfoList_GetMetaObject(void);
extern "C" int beTextureCtrlInfo_GetVTable(void);
extern "C" void FUN_00341cb0(void);
extern "C" void *beTextureCtrlInfo_Register(void);
extern "C" void beTextureCtrlInfo_GetMetaObject(void);
extern "C" void beTextureCtrlInfo_InitFields(void);
extern "C" int beTextureCtrlAttr_GetVTable(void);
extern "C" void FUN_00341f40(void);
extern "C" void *beTextureCtrlAttr_Register(void);
extern "C" void beTextureCtrlAttr_GetMetaObject(void);
extern "C" int FUN_001a5d70(void);
extern "C" void beTextureCtrlAttr_InitFields(void);
extern "C" void *FUN_00342090(void);
extern "C" int beTextureCtrlData_GetVTable(void);
extern "C" void FUN_003421c0(void);
extern "C" void *beTextureCtrlData_Register(void);
extern "C" void beTextureCtrlData_GetMetaObject(void);
extern "C" int FUN_00132ba0(void);
extern "C" void beTextureCtrlData_InitFields(void);
extern "C" void beTextureCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00342350(void);
extern "C" void *FUN_003423a0(void);
extern "C" int beTextureCtrl_GetVTable(void);
extern "C" void **FUN_00342460(void **arg0, short arg1);
extern "C" void FUN_003424e0(void);
extern "C" void *beTextureCtrl_Register(void);
extern "C" void beTextureCtrl_GetMetaObject(void);
extern "C" void beTextureCtrl_InitFields(void);
extern "C" void FUN_00342630(int arg0);
extern "C" igMetaObject *FUN_00342670(void);
extern "C" void *FUN_003426c0(void);
extern "C" int beTextureCtrlWork_GetVTable(void);
extern "C" void FUN_003427f0(void);
extern "C" void *beTextureCtrlWork_Register(void);
extern "C" void beTextureCtrlWork_GetMetaObject(void);
extern "C" void beTextureCtrlWork_InitFields(void);
extern "C" void beTargetObj_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_003429b0(void);
extern "C" void *FUN_00342a00(void);
extern "C" int FUN_001374b0(int *, int);
extern "C" int FUN_00231030(...);
extern "C" int beTargetObj_GetVTable(void);
extern "C" void FUN_00342b00(void);
extern "C" void *beTargetObj_Register(void);
extern "C" void beTargetObj_GetMetaObject(void);
extern "C" void beTargetObj_InitFields(void);
extern "C" void beSystem_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00342ce0(void);
extern "C" void *FUN_00342d30(void);
extern "C" int igSmartPointer_igStringObj_Destruct(int *, int);
extern "C" int igSmartPointer_igStringRefList_Destruct(int *, int);
extern "C" int igSmartPointer_igInfoList_Destruct(int *, int);
extern "C" int igSmartPointer_igDirectory_Destruct(int *, int);
extern "C" int FUN_00229350(int *, int);
extern "C" int igStringRef_Destruct(...);
extern "C" int beSystem_GetVTable(void);
extern "C" void **FUN_00342eb0(void **arg0, short arg1);
extern "C" void FUN_00342f30(void);
extern "C" void *beSystem_Register(void);
extern "C" void beSystem_GetMetaObject(void);
extern "C" int FUN_0019f210(void);
extern "C" int FUN_001e4240(void);
extern "C" int igStringRefList_GetOrCreateMetaObject(void);
extern "C" int igStringObj_GetOrCreateMetaObject(void);
extern "C" int igInfoList_GetOrCreateMetaObject(void);
extern "C" int igDirectory_GetOrCreateMetaObject(void);
extern "C" int igBoolMetaField_SetDefaultValue(void *, int);
extern "C" int igFloatMetaField_SetDefault(void *, float);
extern "C" void beSystem_InitFields(void);
extern "C" void *FUN_00343190(void);
extern "C" int beSwitchCtrlInfo_GetVTable(void);
extern "C" void FUN_003432e0(void);
extern "C" void *beSwitchCtrlInfo_Register(void);
extern "C" void beSwitchCtrlInfo_GetMetaObject(void);
extern "C" int FUN_00196930(void);
extern "C" void beSwitchCtrlInfo_InitFields(void);
extern "C" igMetaEnum *beSwitchCtrl_GetMessageEnum(void);
extern "C" void beSwitchCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_003434d0(void);
extern "C" void *FUN_00343520(void);
extern "C" int beSwitchCtrl_GetVTable(void);
extern "C" void FUN_00343650(void);
extern "C" void *beSwitchCtrl_Register(void);
extern "C" void beSwitchCtrl_GetMetaObject(void);
extern "C" igMetaEnum *FUN_00343700(void);
extern "C" void beStaticInfoCtl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_003437a0(void);
extern "C" void *FUN_003437f0(void);
extern "C" int beStaticInfoCtl_GetVTable(void);
extern "C" void FUN_003438b0(void);
extern "C" void *beStaticInfoCtl_Register(void);
extern "C" void beStaticInfoCtl_GetMetaObject(void);
extern "C" void beStaticInfoCtl_InitFields(void);
extern "C" void *FUN_00343a10(void);
extern "C" int beStaticInfo_GetVTable(void);
extern "C" void FUN_00343ad0(void);
extern "C" void *beStaticInfo_Register(void);
extern "C" void beStaticInfo_GetMetaObject(void);
extern "C" void *FUN_00343b80(void);
extern "C" void FUN_00343bd0(void);
extern "C" void *beBinDataObject_Register(void);
extern "C" void beBinDataObject_GetMetaObject(void);
extern "C" igMetaObject *FUN_00343c80(void);
extern "C" int igCharMetaField_GetDefaultDescriptor(...);
extern "C" void beBinDataObject_InitFields(void);
extern "C" int beSoundInfo_GetVTable(void);
extern "C" void FUN_00343e00(void);
extern "C" void *beSoundInfo_Register(void);
extern "C" void beSoundInfo_GetMetaObject(void);
extern "C" void beSoundInfo_InitFields(void);
extern "C" int beSoundData_GetVTable(void);
extern "C" void FUN_003440d0(void);
extern "C" void *beSoundData_Register(void);
extern "C" void beSoundData_GetMetaObject(void);
extern "C" int igIntMetaField_SetDefault(...);
extern "C" int igShortMetaField_SetDefault(int, int);
extern "C" void beSoundData_InitFields(void);
extern "C" igMetaEnum *beSound_GetMessageEnum(void);
extern "C" void beSound_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_003442f0(void);
extern "C" int beSound_GetVTable(void);
extern "C" void **FUN_00344440(void **arg0, short arg1);
extern "C" void FUN_003444c0(void);
extern "C" void *beSound_Register(void);
extern "C" void beSound_GetMetaObject(void);
extern "C" void beSound_InitFields(void);
extern "C" igMetaObject *FUN_00344630(void);
extern "C" int bePlaySEList_GetVTable(void);
extern "C" void FUN_00344710(void);
extern "C" void *bePlaySEList_Register(void);
extern "C" void bePlaySEList_GetMetaObject(void);
extern "C" void bePlaySE_CreateInstance(int arg0);
extern "C" void *FUN_00344800(void);
extern "C" int bePlaySE_GetVTable(void);
extern "C" void FUN_00344890(void);
extern "C" void *bePlaySE_Register(void);
extern "C" void bePlaySE_GetMetaObject(void);
extern "C" void bePlaySE_InitFields(void);
extern "C" igMetaObject *FUN_003449b0(void);
extern "C" void *FUN_00344a00(void);
extern "C" int beShadow01InfoList_GetVTable(void);
extern "C" void FUN_00344a90(void);
extern "C" void *beShadow01InfoList_Register(void);
extern "C" void beShadow01InfoList_GetMetaObject(void);
extern "C" void *FUN_00344b40(void);
extern "C" int FUN_00198210(char *, int);
extern "C" int beShadow01Info_GetVTable(void);
extern "C" void FUN_00344cc0(void);
extern "C" void *beShadow01Info_Register(void);
extern "C" void beShadow01Info_GetMetaObject(void);
extern "C" int FUN_0019b440(void);
extern "C" int FUN_0019cd50(void);
extern "C" void beShadow01Info_InitFields(void);
extern "C" void beShadow01_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00344e80(void);
extern "C" void *FUN_00344ed0(void);
extern "C" int beShadow01_GetVTable(void);
extern "C" void FUN_00345010(void);
extern "C" void *beShadow01_Register(void);
extern "C" void beShadow01_GetMetaObject(void);
extern "C" void beShadow01_InitFields(void);
extern "C" void *FUN_00345170(void);
extern "C" int beSelectCtrlInfo_GetVTable(void);
extern "C" void FUN_00345230(void);
extern "C" void *beSelectCtrlInfo_Register(void);
extern "C" void beSelectCtrlInfo_GetMetaObject(void);
extern "C" void *FUN_003452e0(void);
extern "C" int beSelectCtrlInfoRamData_GetVTable(void);
extern "C" void FUN_00345490(void);
extern "C" void *beSelectCtrlInfoRamData_Register(void);
extern "C" void beSelectCtrlInfoRamData_GetMetaObject(void);
extern "C" int ObjectPointerList_FindIndex(...);
extern "C" int igMetaObject_FinalizeAndReplaceField(...);
extern "C" void **igMetaObject_FindFieldByName(...);
extern "C" void beSelectCtrlInfoRamData_InitFields(void);
extern "C" void beSelectCtrlInfoWork_Create(int arg0);
extern "C" igMetaObject *FUN_003456c0(void);
extern "C" void *FUN_00345710(void);
extern "C" int beSelectCtrlInfoWork_GetVTable(void);
extern "C" void FUN_00345830(void);
extern "C" void *beSelectCtrlInfoWork_Register(void);
extern "C" void beSelectCtrlInfoWork_GetMetaObject(void);
extern "C" int igBoolList_GetOrCreateMetaObject(void);
extern "C" void beSelectCtrlInfoWork_InitFields(void);
extern "C" igMetaEnum *beSelectCtrl_GetMessageEnum(void);
extern "C" void beSelectCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00345a40(void);
extern "C" void *FUN_00345a90(void);
extern "C" int beSelectCtrl_GetVTable(void);
extern "C" void FUN_00345bc0(void);
extern "C" void *beSelectCtrl_Register(void);
extern "C" void beSelectCtrl_GetMetaObject(void);
extern "C" void beSelectCtrl_InitFields(void);
extern "C" void *FUN_00345d30(void);
extern "C" int beSeInfo_GetVTable(void);
extern "C" void FUN_00345df0(void);
extern "C" void *beSeInfo_Register(void);
extern "C" void beSeInfo_GetMetaObject(void);
extern "C" void *FUN_00345ea0(void);
extern "C" int beSeInfoData_GetVTable(void);
extern "C" void FUN_00345fd0(void);
extern "C" void *beSeInfoData_Register(void);
extern "C" void beSeInfoData_GetMetaObject(void);
extern "C" void beSeInfoData_InitFields(void);
extern "C" igMetaObject *FUN_00346120(void);
extern "C" int beSeDataList_GetVTable(void);
extern "C" void FUN_00346200(void);
extern "C" void *beSeDataList_Register(void);
extern "C" void beSeDataList_GetMetaObject(void);
extern "C" int beSeData_GetVTable(void);
extern "C" void FUN_003463d0(void);
extern "C" void *beSeData_Register(void);
extern "C" void beSeData_GetMetaObject(void);
extern "C" void beSeData_InitFields(void);
extern "C" void beSeCtl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00346530(void);
extern "C" int beSeCtl_GetVTable(void);
extern "C" void FUN_003466b0(void);
extern "C" void *beSeCtl_Register(void);
extern "C" void beSeCtl_GetMetaObject(void);
extern "C" void beSeCtl_InitFields(void);
extern "C" int beSaveUtilInfoRam_GetVTable(void);
extern "C" void FUN_00346950(void);
extern "C" void *beSaveUtilInfoRam_Register(void);
extern "C" void beSaveUtilInfoRam_GetMetaObject(void);
extern "C" void beSaveUtilInfoRam_InitFields(void);
extern "C" void *FUN_00346ab0(void);
extern "C" int beSaveUtilInfo_GetVTable(void);
extern "C" void FUN_00346b70(void);
extern "C" void *beSaveUtilInfo_Register(void);
extern "C" void beSaveUtilInfo_GetMetaObject(void);
extern "C" igMetaEnum *FUN_00346c20(void);
extern "C" void beSaveUtil_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00346cc0(void);
extern "C" void *FUN_00346d10(void);
extern "C" int beSaveUtil_GetVTable(void);
extern "C" void **FUN_00346df0(void **arg0, int arg1);
extern "C" void **FUN_00346e70(void **arg0, short arg1);
extern "C" void FUN_00346ef0(void);
extern "C" void *beSaveUtil_Register(void);
extern "C" void beSaveUtil_GetMetaObject(void);
extern "C" void beSaveUtil_InitFields(void);
extern "C" void *FUN_00347060(void);
extern "C" int beSvPlatDataPC_GetVTable(void);
extern "C" void FUN_003471f0(void);
extern "C" void *beSvPlatDataPC_Register(void);
extern "C" void beSvPlatDataPC_GetMetaObject(void);
extern "C" igMetaObject *FUN_003472a0(void);
extern "C" void *FUN_003472b0(void);
extern "C" int beSvPlatDataXbox_GetVTable(void);
extern "C" void FUN_003473f0(void);
extern "C" void *beSvPlatDataXbox_Register(void);
extern "C" void beSvPlatDataXbox_GetMetaObject(void);
extern "C" void beSvPlatDataXbox_InitFields(void);
extern "C" igMetaObject *FUN_00347600(void);
extern "C" void *FUN_00347650(void);
extern "C" int beXboxImage24k_GetVTable(void);
extern "C" void FUN_003476e0(void);
extern "C" void *beXboxImage24k_Register(void);
extern "C" void beXboxImage24k_GetMetaObject(void);
extern "C" void beXboxImage24k_InitFields(void);
extern "C" void *FUN_00347820(void);
extern "C" int igSmartPointer_igObjectList_Destruct(...);
extern "C" int beSvPlatDataPS2_GetVTable(void);
extern "C" void FUN_00347970(void);
extern "C" void *beSvPlatDataPS2_Register(void);
extern "C" void beSvPlatDataPS2_GetMetaObject(void);
extern "C" int igObjectList_GetOrCreateMetaObject(...);
extern "C" void beSvPlatDataPS2_InitFields(void);
extern "C" void *FUN_00347c50(void);
extern "C" int beSvPs2McImage128k_GetVTable(void);
extern "C" void FUN_00347ce0(void);
extern "C" void *beSvPs2McImage128k_Register(void);
extern "C" void beSvPs2McImage128k_GetMetaObject(void);
extern "C" void beSvPs2McImage128k_InitFields(void);
extern "C" void *FUN_00347e20(void);
extern "C" int beSvPlatDataGC_GetVTable(void);
extern "C" void FUN_00347f50(void);
extern "C" void *beSvPlatDataGC_Register(void);
extern "C" void beSvPlatDataGC_GetMetaObject(void);
extern "C" void beSvPlatDataGC_InitFields(void);
extern "C" void FUN_00348170(int arg0);
extern "C" igMetaObject *FUN_003481b0(void);
extern "C" void *FUN_00348200(void);
extern "C" int beSvConnectCheck_GetVTable(void);
extern "C" void FUN_00348530(void);
extern "C" void *beSvConnectCheck_Register(void);
extern "C" void beSvConnectCheck_GetMetaObject(void);
extern "C" igMetaObject *FUN_003485e0(void);
extern "C" void FUN_003485f0(int arg0);
extern "C" void *FUN_00348630(void);
extern "C" int beSvEndApi_GetVTable(void);
extern "C" void FUN_003487c0(void);
extern "C" void *beSvEndApi_Register(void);
extern "C" void beSvEndApi_GetMetaObject(void);
extern "C" void beSvEndApi_InitFields(void);
extern "C" void FUN_00348930(int arg0);
extern "C" int beSvStartApi_GetVTable(void);
extern "C" void FUN_00348b00(void);
extern "C" void *beSvStartApi_Register(void);
extern "C" void beSvStartApi_GetMetaObject(void);
extern "C" void beSvStartApi_InitFields(void);
extern "C" void FUN_00348c70(int arg0);
extern "C" int beSvGetFreeSizeApi_GetVTable(void);
extern "C" void FUN_00348e40(void);
extern "C" void *beSvGetFreeSizeApi_Register(void);
extern "C" void beSvGetFreeSizeApi_GetMetaObject(void);
extern "C" void beSvGetFreeSizeApi_InitFields(void);
extern "C" void FUN_00348f60(int arg0);
extern "C" int beSvWriteMediaApi_GetVTable(void);
extern "C" void **FUN_00349080(void **arg0, long long arg1);
extern "C" void FUN_00349100(void);
extern "C" void *beSvWriteMediaApi_Register(void);
extern "C" void beSvWriteMediaApi_GetMetaObject(void);
extern "C" void beSvWriteMediaApi_InitFields(void);
extern "C" void FUN_00349270(int arg0);
extern "C" int beSvReadMediaApi_GetVTable(void);
extern "C" void FUN_00349430(void);
extern "C" void *beSvReadMediaApi_Register(void);
extern "C" void beSvReadMediaApi_GetMetaObject(void);
extern "C" void beSvReadMediaApi_InitFields(void);
extern "C" void FUN_003495f0(int arg0);
extern "C" void *FUN_00349630(void);
extern "C" int beSvUseCheckApi_GetVTable(void);
extern "C" void FUN_003497c0(void);
extern "C" void *beSvUseCheckApi_Register(void);
extern "C" void beSvUseCheckApi_GetMetaObject(void);
extern "C" void FUN_00349870(int arg0);
extern "C" void *FUN_003498b0(void);
extern "C" int beSvFormatApi_GetVTable(void);
extern "C" void FUN_00349a40(void);
extern "C" void *beSvFormatApi_Register(void);
extern "C" void beSvFormatApi_GetMetaObject(void);
extern "C" void FUN_00349af0(int arg0);
extern "C" void *FUN_00349b30(void);
extern "C" int beSvFileFindApi_GetVTable(void);
extern "C" void FUN_00349cc0(void);
extern "C" void *beSvFileFindApi_Register(void);
extern "C" void beSvFileFindApi_GetMetaObject(void);
extern "C" void FUN_00349d70(int arg0);
extern "C" void *FUN_00349db0(void);
extern "C" int beSvFileMakeApi_GetVTable(void);
extern "C" void FUN_00349e90(void);
extern "C" void *beSvFileMakeApi_Register(void);
extern "C" void beSvFileMakeApi_GetMetaObject(void);
extern "C" void beSvFileMakeApi_InitFields(void);
extern "C" igMetaObject *FUN_0034a000(void);
extern "C" void *FUN_0034a050(void);
extern "C" void FUN_0034a0a0(void);
extern "C" void *beSaveApi_Register(void);
extern "C" void beSaveApi_GetMetaObject(void);
extern "C" void beSaveApi_InitFields(void);
extern "C" igMetaObject *FUN_0034a210(void);
extern "C" void *FUN_0034a260(void);
extern "C" int beSvPlatBaseData_GetVTable(void);
extern "C" void FUN_0034a340(void);
extern "C" void *beSvPlatBaseData_Register(void);
extern "C" void beSvPlatBaseData_GetMetaObject(void);
extern "C" void beSvPlatBaseData_InitFields(void);
extern "C" igMetaObject *FUN_0034a4a0(void);
extern "C" void *FUN_0034a4f0(void);
extern "C" int beSvSlotDataList_GetVTable(void);
extern "C" void FUN_0034a580(void);
extern "C" void *beSvSlotDataList_Register(void);
extern "C" void beSvSlotDataList_GetMetaObject(void);
extern "C" void *FUN_0034a630(void);
extern "C" int beSvSlotPS2_GetVTable(void);
extern "C" void FUN_0034a6c0(void);
extern "C" void *beSvSlotPS2_Register(void);
extern "C" void beSvSlotPS2_GetMetaObject(void);
extern "C" igMetaObject *FUN_0034a770(void);
extern "C" void *FUN_0034a780(void);
extern "C" int beSvSlotGC_GetVTable(void);
extern "C" void FUN_0034a810(void);
extern "C" void *beSvSlotGC_Register(void);
extern "C" void beSvSlotGC_GetMetaObject(void);
extern "C" void *FUN_0034a8c0(void);
extern "C" int beSvSlotXbox_GetVTable(void);
extern "C" void FUN_0034a9a0(void);
extern "C" void *beSvSlotXbox_Register(void);
extern "C" void beSvSlotXbox_GetMetaObject(void);
extern "C" void beSvSlotXbox_InitFields(void);
extern "C" void FUN_0034ab30(void);
extern "C" void *beSvSlotData_Register(void);
extern "C" void beSvSlotData_GetMetaObject(void);
extern "C" void beSvSlotData_InitFields(void);
extern "C" void beSaveMemoryObj_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0034ac90(void);
extern "C" int beSaveMemoryObj_GetVTable(void);
extern "C" void FUN_0034ad70(void);
extern "C" void *beSaveMemoryObj_Register(void);
extern "C" void beSaveMemoryObj_GetMetaObject(void);
extern "C" void beSaveMemoryObj_InitFields(void);
extern "C" igMetaObject *FUN_0034aeb0(void);
extern "C" int beSaveDataDeliver_GetVTable(void);
extern "C" void FUN_0034af90(void);
extern "C" void *beSaveDataDeliver_Register(void);
extern "C" void beSaveDataDeliver_GetMetaObject(void);
extern "C" void beSaveDataDeliver_InitFields(void);
extern "C" igMetaObject *FUN_0034b0d0(void);
extern "C" int beSvDeliver_GetVTable(void);
extern "C" void FUN_0034b260(void);
extern "C" void *beSvDeliver_Register(void);
extern "C" void beSvDeliver_GetMetaObject(void);
extern "C" int igCharMetaField_SetDefaultValue(void *, int);
extern "C" void beSvDeliver_InitFields(void);
extern "C" void *FUN_0034b4a0(void);
extern "C" int FUN_00195a90(...);
extern "C" int beResetNode_GetVTable(void);
extern "C" void FUN_0034b560(void);
extern "C" void *igGroup_Register(void);
extern "C" void *beResetNode_Register(void);
extern "C" void beResetNode_GetMetaObject(void);
extern "C" void beResetNode_InitFields(void);
extern "C" void FUN_0039c8c0(void);
extern "C" void FUN_0034b690(void);
extern "C" void *FUN_0034b6b0(void);
extern "C" int bePoint01Info_GetVTable(void);
extern "C" void FUN_0034b810(void);
extern "C" void *bePoint01Info_Register(void);
extern "C" void bePoint01Info_GetMetaObject(void);
extern "C" void bePoint01Info_InitFields(void);
extern "C" igMetaEnum *FUN_0034b980(void);
extern "C" void bePoint01_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0034ba20(void);
extern "C" void *FUN_0034ba70(void);
extern "C" int bePoint01_GetVTable(void);
extern "C" void FUN_0034bba0(void);
extern "C" void *bePoint01_Register(void);
extern "C" void bePoint01_GetMetaObject(void);
extern "C" void bePoint01_InitFields(void);
extern "C" void *FUN_0034bcc0(void);
extern "C" int FUN_001a7580(int *, int);
extern "C" int beParticleCtrl2InfoRam_GetVTable(void);
extern "C" void **FUN_0034bdc0(void **arg0, short arg1);
extern "C" void FUN_0034bec0(void);
extern "C" void *beParticleCtrl2InfoRam_Register(void);
extern "C" void beParticleCtrl2InfoRam_GetMetaObject(void);
extern "C" int FUN_00196190(void);
extern "C" void beParticleCtrl2InfoRam_InitFields(void);
extern "C" void FUN_0034c040(int arg0);
extern "C" igMetaObject *FUN_0034c080(void);
extern "C" void *FUN_0034c0d0(void);
extern "C" int beParticleCtrl2InfoWork_GetVTable(void);
extern "C" void **FUN_0034c1b0(void **arg0, short arg1);
extern "C" void FUN_0034c230(void);
extern "C" void *beParticleCtrl2InfoWork_Register(void);
extern "C" void beParticleCtrl2InfoWork_GetMetaObject(void);
extern "C" void beParticleCtrl2InfoWork_InitFields(void);
extern "C" void *FUN_0034c380(void);
extern "C" int beParticleCtrl2Info_GetVTable(void);
extern "C" void FUN_0034c460(void);
extern "C" void *beParticleCtrl2Info_Register(void);
extern "C" void beParticleCtrl2Info_GetMetaObject(void);
extern "C" void beParticleCtrl2Info_InitFields(void);
extern "C" igMetaEnum *FUN_0034c5d0(void);
extern "C" void beParticleCtrl2_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0034c670(void);
extern "C" void *FUN_0034c6c0(void);
extern "C" int beParticleCtrl2_GetVTable(void);
extern "C" void FUN_0034c7f0(void);
extern "C" void *beParticleCtrl2_Register(void);
extern "C" void beParticleCtrl2_GetMetaObject(void);
extern "C" void bePadManager_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0034c8e0(void);
extern "C" void *FUN_0034c930(void);
extern "C" int bePadManager_GetVTable(void);
extern "C" void FUN_0034cb30(void);
extern "C" void *bePadManager_Register(void);
extern "C" void bePadManager_GetMetaObject(void);
extern "C" void bePadManager_InitFields(void);
extern "C" igMetaObject *FUN_0034ccc0(void);
extern "C" void *FUN_0034cd10(void);
extern "C" int bePadDataList_GetVTable(void);
extern "C" void FUN_0034cda0(void);
extern "C" void *bePadDataList_Register(void);
extern "C" void bePadDataList_GetMetaObject(void);
extern "C" void FUN_0034ce50(int arg0);
extern "C" void *FUN_0034ce90(void);
extern "C" int bePadData_GetVTable(void);
extern "C" void FUN_0034cf20(void);
extern "C" void *bePadData_Register(void);
extern "C" void bePadData_GetMetaObject(void);
extern "C" int FUN_0018e2f0(int, int *);
extern "C" void bePadData_InitFields(void);
extern "C" int igInfo_Destroy(...);
extern "C" int beOptInfo_GetVTable(void);
extern "C" void FUN_0034d160(void);
extern "C" void *igInfo_Register(void);
extern "C" void *beOptInfo_Register(void);
extern "C" void beOptInfo_GetMetaObject(void);
extern "C" void beOptInfo_InitFields(void);
extern "C" void FUN_0034d2b0(int arg0);
extern "C" igMetaObject *FUN_0034d2f0(void);
extern "C" int beNumberCtrlInfoWork_GetVTable(void);
extern "C" void FUN_0034d3d0(void);
extern "C" void *beNumberCtrlInfoWork_Register(void);
extern "C" void beNumberCtrlInfoWork_GetMetaObject(void);
extern "C" void beNumberCtrlInfoWork_InitFields(void);
extern "C" int FUN_001971e0(int *, int);
extern "C" int beNumberCtrlInfoRam_GetVTable(void);
extern "C" void **FUN_0034d640(void **arg0, long long arg1);
extern "C" void **FUN_0034d6c0(void **arg0, int arg1);
extern "C" void FUN_0034d740(void);
extern "C" void *beNumberCtrlInfoRam_Register(void);
extern "C" void beNumberCtrlInfoRam_GetMetaObject(void);
extern "C" int FUN_0019fae0(void);
extern "C" void beNumberCtrlInfoRam_InitFields(void);
extern "C" igMetaObject *FUN_0034d8f0(void);
extern "C" int beNumVerDataList_GetVTable(void);
extern "C" void FUN_0034d9d0(void);
extern "C" void *beNumVerDataList_Register(void);
extern "C" void beNumVerDataList_GetMetaObject(void);
extern "C" void *FUN_0034da80(void);
extern "C" int beNumVerData_GetVTable(void);
extern "C" void FUN_0034db60(void);
extern "C" void *beNumVerData_Register(void);
extern "C" void beNumVerData_GetMetaObject(void);
extern "C" void beNumVerData_InitFields(void);
extern "C" igMetaObject *FUN_0034dcd0(void);
extern "C" void *FUN_0034dd20(void);
extern "C" int beNumVerInsideDataList_GetVTable(void);
extern "C" void FUN_0034ddb0(void);
extern "C" void *beNumVerInsideDataList_Register(void);
extern "C" void beNumVerInsideDataList_GetMetaObject(void);
extern "C" int FUN_0034de60(int arg0);
extern "C" void *FUN_0034dea0(void);
extern "C" int beNumVerInsideData_GetVTable(void);
extern "C" void FUN_0034df30(void);
extern "C" void *beNumVerInsideData_Register(void);
extern "C" void beNumVerInsideData_GetMetaObject(void);
extern "C" void beNumVerInsideData_InitFields(void);
extern "C" void *FUN_0034e050(void);
extern "C" int beNumberCtrlInfoList_GetVTable(void);
extern "C" void FUN_0034e0e0(void);
extern "C" void *beNumberCtrlInfoList_Register(void);
extern "C" void beNumberCtrlInfoList_GetMetaObject(void);
extern "C" void *FUN_0034e190(void);
extern "C" int beNumberCtrlInfo_GetVTable(void);
extern "C" void FUN_0034e250(void);
extern "C" void *beNumberCtrlInfo_Register(void);
extern "C" void beNumberCtrlInfo_GetMetaObject(void);
extern "C" igMetaEnum *FUN_0034e300(void);
extern "C" void beNumberCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0034e3a0(void);
extern "C" void *FUN_0034e3f0(void);
extern "C" int beNumberCtrl_GetVTable(void);
extern "C" void FUN_0034e520(void);
extern "C" void *beNumberCtrl_Register(void);
extern "C" void beNumberCtrl_GetMetaObject(void);
extern "C" void *beLoadingNode_ResolveMetaObject(void);
extern "C" int beLoadingNode_GetVTable(void);
extern "C" int FUN_00195970(int **, int);
extern "C" int **FUN_0034e690(int **arg0, long long arg1);
extern "C" void FUN_0034e710(void);
extern "C" void *beLoadingNode_Register(void);
extern "C" void beLoadingNode_GetMetaObject(void);
extern "C" igMetaObject *FUN_0034e7d0(void);
extern "C" void beLoadingNode_InitFields(void);
extern "C" void beLoadingNode_RegisterTraversalFunction(void);
extern "C" void FUN_0034e850(void);
extern "C" void *beNodeAnim_ResolveMetaObject(void);
extern "C" int beNodeAnim_GetVTable(void);
extern "C" void FUN_0034e930(void);
extern "C" void *beNodeAnim_Register(void);
extern "C" void beNodeAnim_GetMetaObject(void);
extern "C" int igLongMetaField_SetDefault(...);
extern "C" void beNodeAnim_InitFields(void);
extern "C" void beNodeAnim_RegisterTraversalFunction(void);
extern "C" void FUN_0034eaf0(void);
extern "C" void *FUN_0034eb10(void);
extern "C" int beMovieInfo_GetVTable(void);
extern "C" void FUN_0034ebd0(void);
extern "C" void *beMovieInfo_Register(void);
extern "C" void beMovieInfo_GetMetaObject(void);
extern "C" void *FUN_0034ec80(void);
extern "C" int FUN_001d3650(int *, int);
extern "C" int FUN_00130720(...);
extern "C" int beMovieInfoData_GetVTable(void);
extern "C" void FUN_0034ed80(void);
extern "C" void *beMovieInfoData_Register(void);
extern "C" void beMovieInfoData_GetMetaObject(void);
extern "C" int FUN_0019aee0(void);
extern "C" void beMovieInfoData_InitFields(void);
extern "C" igMetaEnum *FUN_0034eed0(void);
extern "C" void beMovie_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0034ef70(void);
extern "C" int FUN_003369f0(int *, int);
extern "C" int beMovie_GetVTable(void);
extern "C" void FUN_0034f0a0(void);
extern "C" void *beMovie_Register(void);
extern "C" void beMovie_GetMetaObject(void);
extern "C" int FUN_00336c10(void);
extern "C" void beMovie_InitFields(void);
extern "C" igMetaObject *FUN_0034f210(void);
extern "C" int beModelCtrlSubCom_GetVTable(void);
extern "C" void FUN_0034f340(void);
extern "C" void *beModelCtrlSubCom_Register(void);
extern "C" void beModelCtrlSubCom_GetMetaObject(void);
extern "C" void beModelCtrlSubCom_InitFields(void);
extern "C" void beModelCtrlSCSound_Create(int arg0);
extern "C" int beModelCtrlSCSound_GetVTable(void);
extern "C" void FUN_0034f5c0(void);
extern "C" void *beModelCtrlSCSound_Register(void);
extern "C" void beModelCtrlSCSound_GetMetaObject(void);
extern "C" igMetaObject *FUN_0034f670(void);
extern "C" void beModelCtrlSCSound_InitFields(void);
extern "C" void beModelCtrlSCHitBox_Create(int arg0);
extern "C" int beModelCtrlSCHitBox_GetVTable(void);
extern "C" void FUN_0034f7c0(void);
extern "C" void *beModelCtrlSCHitBox_Register(void);
extern "C" void beModelCtrlSCHitBox_GetMetaObject(void);
extern "C" void beModelCtrlSCHitBox_InitFields(void);
extern "C" void beModelCtrlSCEffect_Create(int arg0);
extern "C" void *FUN_0034f920(void);
extern "C" int beModelCtrlSCEffect_GetVTable(void);
extern "C" void FUN_0034fa30(void);
extern "C" void *beModelCtrlSCEffect_Register(void);
extern "C" void beModelCtrlSCEffect_GetMetaObject(void);
extern "C" void beModelCtrlSCEffect_InitFields(void);
extern "C" void *FUN_0034fb70(void);
extern "C" void FUN_0034fbc0(void);
extern "C" void *beModelCtrlSubComBase_Register(void);
extern "C" void beModelCtrlSubComBase_GetMetaObject(void);
extern "C" void beModelCtrlSubComBase_InitFields(void);
extern "C" void beModelCtrlNode2_Create(int arg0);
extern "C" igMetaObject *FUN_0034fd40(void);
extern "C" void *beModelCtrlNode2_ResolveMetaObject(void);
extern "C" int beModelCtrlNode2_GetVTable(void);
extern "C" void FUN_0034fe80(void);
extern "C" void *beModelCtrlNode2_Register(void);
extern "C" void beModelCtrlNode2_GetMetaObject(void);
extern "C" int FUN_0013af00(void);
extern "C" void beModelCtrlNode2_InitFields(void);
extern "C" void beModelCtrlNode2_RegisterTraversalFunction(void);
extern "C" void FUN_00350000(void);
extern "C" void FUN_00350020(int arg0);
extern "C" igMetaObject *FUN_00350060(void);
extern "C" void *FUN_003500b0(void);
extern "C" void **FUN_00350b10(void **arg0, short arg1);
extern "C" void **FUN_00350c10(void **arg0, long long arg1);
extern "C" void **FUN_00350d90(void **arg0, short arg1);
extern "C" void **FUN_00350e90(void **arg0, short arg1);
extern "C" int *FUN_00350f10(int *p);
extern "C" int *FUN_00350f20(int *p);
extern "C" int *FUN_00350f30(int *p);
extern "C" int *FUN_00350f40(int *p);
extern "C" int *FUN_00350f50(int *p);
extern "C" int *FUN_00350f60(int *p);
extern "C" int *FUN_00350f70(int *p);
extern "C" int *FUN_00350f80(int *p);
extern "C" int *FUN_00350f90(int *p);
extern "C" int *FUN_00350fa0(int *p);
extern "C" void FUN_00350fb0(void);
extern "C" int beModelCtrlInfoWork_GetVTable(void);
extern "C" void *beModelCtrlInfoWork_Register(void);
extern "C" void beModelCtrlInfoWork_GetMetaObject(void);
extern "C" int FUN_0018a6a0(void);
extern "C" void beModelCtrlInfoWork_InitFields(void);
extern "C" void beModelCtrlInfoRideOn4_Create(int arg0);
extern "C" void *FUN_00351460(void);
extern "C" int beModelCtrlInfoRideOn4_GetVTable(void);
extern "C" void FUN_003515b0(void);
extern "C" void *beModelCtrlInfoRideOn4_Register(void);
extern "C" void beModelCtrlInfoRideOn4_GetMetaObject(void);
extern "C" igMetaObject *FUN_00351660(void);
extern "C" void beModelCtrlInfoRideOn4_InitFields(void);
extern "C" void beModelCtrlInfoRideOn3_Create(int arg0);
extern "C" void *FUN_003517c0(void);
extern "C" int beModelCtrlInfoRideOn3_GetVTable(void);
extern "C" void FUN_00351910(void);
extern "C" void *beModelCtrlInfoRideOn3_Register(void);
extern "C" void beModelCtrlInfoRideOn3_GetMetaObject(void);
extern "C" void beModelCtrlInfoRideOn3_InitFields(void);
extern "C" void beModelCtrlInfoRideOn2_Create(int arg0);
extern "C" void *FUN_00351b10(void);
extern "C" int beModelCtrlInfoRideOn2_GetVTable(void);
extern "C" void FUN_00351c60(void);
extern "C" void *beModelCtrlInfoRideOn2_Register(void);
extern "C" void beModelCtrlInfoRideOn2_GetMetaObject(void);
extern "C" void beModelCtrlInfoRideOn2_InitFields(void);
extern "C" void beModelCtrlInfoRideOn_Create(int arg0);
extern "C" igMetaObject *FUN_00351e60(void);
extern "C" void *FUN_00351eb0(void);
extern "C" int beModelCtrlInfoRideOn_GetVTable(void);
extern "C" void FUN_00351ff0(void);
extern "C" void *beModelCtrlInfoRideOn_Register(void);
extern "C" void beModelCtrlInfoRideOn_GetMetaObject(void);
extern "C" void beModelCtrlInfoRideOn_InitFields(void);
extern "C" void beModelCtrlInfoAI_Create(int arg0);
extern "C" igMetaObject *FUN_00352180(void);
extern "C" void *FUN_003521d0(void);
extern "C" int beModelCtrlInfoAI_GetVTable(void);
extern "C" void FUN_003522b0(void);
extern "C" void *beModelCtrlInfoAI_Register(void);
extern "C" void beModelCtrlInfoAI_GetMetaObject(void);
extern "C" void beModelCtrlInfoAI_InitFields(void);
extern "C" void beModelCtrlInfoHitBody_Create(int arg0);
extern "C" igMetaObject *FUN_00352410(void);
extern "C" void *FUN_00352460(void);
extern "C" int beModelCtrlInfoHitBody_GetVTable(void);
extern "C" void FUN_003525e0(void);
extern "C" void *beModelCtrlInfoHitBody_Register(void);
extern "C" void beModelCtrlInfoHitBody_GetMetaObject(void);
extern "C" int FUN_0018a4f0(...);
extern "C" void beModelCtrlInfoHitBody_InitFields(void);
extern "C" igMetaObject *FUN_003527b0(void);
extern "C" int beModelCtrlMoveObjectList_GetVTable(void);
extern "C" void FUN_00352890(void);
extern "C" void *beModelCtrlMoveObjectList_Register(void);
extern "C" void beModelCtrlMoveObjectList_GetMetaObject(void);
extern "C" void beModelCtrlMoveObject_Create(int arg0);
extern "C" int beModelCtrlMoveObject_GetVTable(void);
extern "C" void FUN_00352a10(void);
extern "C" void *beModelCtrlMoveObject_Register(void);
extern "C" void beModelCtrlMoveObject_GetMetaObject(void);
extern "C" void beModelCtrlMoveObject_InitFields(void);
extern "C" int beModelCtrlInfoList_GetVTable(void);
extern "C" void FUN_00352c20(void);
extern "C" void *beModelCtrlInfoList_Register(void);
extern "C" void beModelCtrlInfoList_GetMetaObject(void);
extern "C" int beModelCtrlInfo_GetVTable(void);
extern "C" void FUN_00352da0(void);
extern "C" void *beModelCtrlInfo_Register(void);
extern "C" void beModelCtrlInfo_GetMetaObject(void);
extern "C" void beModelCtrlInfo_InitFields(void);
extern "C" void *FUN_00352ee0(void);
extern "C" int beModelCtrlInfoRamData_GetVTable(void);
extern "C" void FUN_00353040(void);
extern "C" void *beModelCtrlInfoRamData_Register(void);
extern "C" void beModelCtrlInfoRamData_GetMetaObject(void);
extern "C" void beModelCtrlInfoRamData_InitFields(void);
extern "C" igMetaObject *FUN_00353240(void);
extern "C" void *FUN_00353290(void);
extern "C" int beModelCtrlInfoDataTrc_GetVTable(void);
extern "C" void FUN_003533c0(void);
extern "C" void *beModelCtrlInfoDataTrc_Register(void);
extern "C" void beModelCtrlInfoDataTrc_GetMetaObject(void);
extern "C" int FUN_001957c0(...);
extern "C" void beModelCtrlInfoDataTrc_InitFields(void);
extern "C" void *FUN_003535b0(void);
extern "C" int beModelCtrlInfoDataSeq_GetVTable(void);
extern "C" void FUN_003536e0(void);
extern "C" void *beModelCtrlInfoDataSeq_Register(void);
extern "C" void beModelCtrlInfoDataSeq_GetMetaObject(void);
extern "C" void beModelCtrlInfoDataSeq_InitFields(void);
extern "C" void *FUN_003538d0(void);
extern "C" int beModelCtrlInfoDataHit_GetVTable(void);
extern "C" void FUN_00353a00(void);
extern "C" void *beModelCtrlInfoDataHit_Register(void);
extern "C" void beModelCtrlInfoDataHit_GetMetaObject(void);
extern "C" void beModelCtrlInfoDataHit_InitFields(void);
extern "C" void *FUN_00353bf0(void);
extern "C" int beModelCtrlInfoDataAIH_GetVTable(void);
extern "C" void FUN_00353cd0(void);
extern "C" void *beModelCtrlInfoDataAIH_Register(void);
extern "C" void beModelCtrlInfoDataAIH_GetMetaObject(void);
extern "C" void beModelCtrlInfoDataAIH_InitFields(void);
extern "C" void *FUN_00353e90(void);
extern "C" int beModelCtrlInfoDataAIM_GetVTable(void);
extern "C" void FUN_00353fc0(void);
extern "C" void *beModelCtrlInfoDataAIM_Register(void);
extern "C" void beModelCtrlInfoDataAIM_GetMetaObject(void);
extern "C" void beModelCtrlInfoDataAIM_InitFields(void);
extern "C" igMetaObject *FUN_003541b0(void);
extern "C" void *FUN_00354200(void);
extern "C" int beModelCtrlAIMapList_GetVTable(void);
extern "C" void FUN_00354290(void);
extern "C" void *beModelCtrlAIMapList_Register(void);
extern "C" void beModelCtrlAIMapList_GetMetaObject(void);
extern "C" void *FUN_00354340(void);
extern "C" int FUN_00131bc0(...);
extern "C" int beModelCtrlAIMap_GetVTable(void);
extern "C" void FUN_00354510(void);
extern "C" void *beModelCtrlAIMap_Register(void);
extern "C" void beModelCtrlAIMap_GetMetaObject(void);
extern "C" void beModelCtrlAIMap_InitFields(void);
extern "C" igMetaObject *FUN_003546d0(void);
extern "C" void *FUN_00354720(void);
extern "C" int beModelCtrlAIDataList_GetVTable(void);
extern "C" void FUN_003547b0(void);
extern "C" void *beModelCtrlAIDataList_Register(void);
extern "C" void beModelCtrlAIDataList_GetMetaObject(void);
extern "C" void *FUN_00354860(void);
extern "C" int beModelCtrlAIData_GetVTable(void);
extern "C" void FUN_00354940(void);
extern "C" void *beModelCtrlAIData_Register(void);
extern "C" void beModelCtrlAIData_GetMetaObject(void);
extern "C" void beModelCtrlAIData_InitFields(void);
extern "C" void beModelCtrlHITBOX_Create(int arg0);
extern "C" int beModelCtrlHITBOX_GetVTable(void);
extern "C" void FUN_00354b80(void);
extern "C" void *beModelCtrlHITBOX_Register(void);
extern "C" void beModelCtrlHITBOX_GetMetaObject(void);
extern "C" void beModelCtrlHITBOX_InitFields(void);
extern "C" int beModelCtrlMUTEKI_GetVTable(void);
extern "C" void FUN_00354d80(void);
extern "C" void *beModelCtrlMUTEKI_Register(void);
extern "C" void beModelCtrlMUTEKI_GetMetaObject(void);
extern "C" void beModelCtrlMUTEKI_InitFields(void);
extern "C" int beModelCtrlAIMAP_GetVTable(void);
extern "C" void FUN_00354f80(void);
extern "C" void *beModelCtrlAIMAP_Register(void);
extern "C" void beModelCtrlAIMAP_GetMetaObject(void);
extern "C" int beModelCtrlWCHECK_GetVTable(void);
extern "C" void FUN_00355110(void);
extern "C" void *beModelCtrlWCHECK_Register(void);
extern "C" void beModelCtrlWCHECK_GetMetaObject(void);
extern "C" void *FUN_003551c0(void);
extern "C" int beModelCtrlPDMOVE_GetVTable(void);
extern "C" void FUN_003552a0(void);
extern "C" void *beModelCtrlPDMOVE_Register(void);
extern "C" void beModelCtrlPDMOVE_GetMetaObject(void);
extern "C" void beModelCtrlPDMOVE_InitFields(void);
extern "C" void *FUN_003553c0(void);
extern "C" int beModelCtrlMOVERL_GetVTable(void);
extern "C" void FUN_00355520(void);
extern "C" void *beModelCtrlMOVERL_Register(void);
extern "C" void beModelCtrlMOVERL_GetMetaObject(void);
extern "C" void beModelCtrlMOVERL_InitFields(void);
extern "C" void *FUN_00355640(void);
extern "C" int beModelCtrlMOVEEX_GetVTable(void);
extern "C" void FUN_00355720(void);
extern "C" void *beModelCtrlMOVEEX_Register(void);
extern "C" void beModelCtrlMOVEEX_GetMetaObject(void);
extern "C" void beModelCtrlMOVEEX_InitFields(void);
extern "C" void *FUN_00355840(void);
extern "C" int beModelCtrlMOVE_GetVTable(void);
extern "C" void FUN_00355920(void);
extern "C" void *beModelCtrlMOVE_Register(void);
extern "C" void beModelCtrlMOVE_GetMetaObject(void);
extern "C" void beModelCtrlMOVE_InitFields(void);
extern "C" void *FUN_00355a40(void);
extern "C" int beModelCtrlMSGBOX_GetVTable(void);
extern "C" void FUN_00355b20(void);
extern "C" void *beModelCtrlMSGBOX_Register(void);
extern "C" void beModelCtrlMSGBOX_GetMetaObject(void);
extern "C" void *FUN_00355bd0(void);
extern "C" int beModelCtrlCTRL_GetVTable(void);
extern "C" void FUN_00355cb0(void);
extern "C" void *beModelCtrlCTRL_Register(void);
extern "C" void beModelCtrlCTRL_GetMetaObject(void);
extern "C" void *FUN_00355d60(void);
extern "C" int beModelCtrlJUMP_GetVTable(void);
extern "C" void FUN_00355e40(void);
extern "C" void *beModelCtrlJUMP_Register(void);
extern "C" void beModelCtrlJUMP_GetMetaObject(void);
extern "C" void *FUN_00355ef0(void);
extern "C" int beModelCtrlACTION_GetVTable(void);
extern "C" void FUN_00355fd0(void);
extern "C" void *beModelCtrlACTION_Register(void);
extern "C" void beModelCtrlACTION_GetMetaObject(void);
extern "C" void *FUN_00356080(void);
extern "C" int beModelCtrlLABELCTRL_GetVTable(void);
extern "C" void FUN_003561a0(void);
extern "C" void *beModelCtrlLABELCTRL_Register(void);
extern "C" void beModelCtrlLABELCTRL_GetMetaObject(void);
extern "C" void beModelCtrlLABELCTRL_InitFields(void);
extern "C" void *FUN_003562c0(void);
extern "C" int beModelCtrlLABEL_GetVTable(void);
extern "C" void FUN_003563a0(void);
extern "C" void *beModelCtrlLABEL_Register(void);
extern "C" void beModelCtrlLABEL_GetMetaObject(void);
extern "C" int beModelCtrlLUACALL_GetVTable(void);
extern "C" void FUN_00356570(void);
extern "C" void *beModelCtrlLUACALL_Register(void);
extern "C" void beModelCtrlLUACALL_GetMetaObject(void);
extern "C" void beModelCtrlLUACALL_InitFields(void);
extern "C" int beModelCtrlDataList_GetVTable(void);
extern "C" void FUN_00356720(void);
extern "C" void *beModelCtrlDataList_Register(void);
extern "C" void beModelCtrlDataList_GetMetaObject(void);
extern "C" igMetaObject *FUN_003567d0(void);
extern "C" int beModelCtrlData_GetVTable(void);
extern "C" void FUN_00356950(void);
extern "C" void *beModelCtrlData_Register(void);
extern "C" void beModelCtrlData_GetMetaObject(void);
extern "C" void beModelCtrlData_InitFields(void);
extern "C" igMetaEnum *beModelCtrl_GetMessageEnum(void);
extern "C" void FUN_00356b60(void);
extern "C" void *beModelCtrl_Register(void);
extern "C" void beModelCtrl_GetMetaObject(void);
extern "C" void beModelCtrl_InitFields(void);
extern "C" igMetaObject *FUN_00356cc0(void);
extern "C" void *beMeterCtrlNode_ResolveMetaObject(void);
extern "C" int FUN_00195190(int *, int);
extern "C" int beMeterCtrlNode_GetVTable(void);
extern "C" void FUN_00356de0(void);
extern "C" void *beMeterCtrlNode_Register(void);
extern "C" void beMeterCtrlNode_GetMetaObject(void);
extern "C" int igLongList_GetOrCreateMetaObject(void);
extern "C" void beMeterCtrlNode_InitFields(void);
extern "C" void beMeterCtrlNode_RegisterTraversalFunction(void);
extern "C" void FUN_00356f40(void);
extern "C" void *FUN_00356f60(void);
extern "C" int beMeterCtrlInfoList_GetVTable(void);
extern "C" void FUN_00356ff0(void);
extern "C" void *beMeterCtrlInfoList_Register(void);
extern "C" void beMeterCtrlInfoList_GetMetaObject(void);
extern "C" void *FUN_003570a0(void);
extern "C" int beMeterCtrlInfo_GetVTable(void);
extern "C" void FUN_00357170(void);
extern "C" void *beMeterCtrlInfo_Register(void);
extern "C" void beMeterCtrlInfo_GetMetaObject(void);
extern "C" void beMeterCtrlInfo_InitFields(void);
extern "C" void *FUN_003572d0(void);
extern "C" int beMeterCtrlOneData_GetVTable(void);
extern "C" void **FUN_003573d0(void **arg0, long long arg1);
extern "C" void FUN_00357450(void);
extern "C" void *beMeterCtrlOneData_Register(void);
extern "C" void beMeterCtrlOneData_GetMetaObject(void);
extern "C" void beMeterCtrlOneData_InitFields(void);
extern "C" igMetaEnum *FUN_00357600(void);
extern "C" void beMeterCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_003576a0(void);
extern "C" void *FUN_003576f0(void);
extern "C" int beMeterCtrl_GetVTable(void);
extern "C" void FUN_00357820(void);
extern "C" void *beMeterCtrl_Register(void);
extern "C" void beMeterCtrl_GetMetaObject(void);
extern "C" void beMessenger_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00357910(void);
extern "C" void *FUN_00357960(void);
extern "C" int beMessenger_GetVTable(void);
extern "C" void List_RemoveWordAt(void *, int);
extern "C" void List_InsertWords(void *, int, int, void *);
extern "C" void *StringPool_Allocate(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void **FUN_00357b10(void **arg0, int arg1);
extern "C" void **FUN_00357b90(void **arg0, short arg1);
extern "C" void **FUN_00357c90(void **arg0, long long arg1);
extern "C" void FUN_00357d10(void);
extern "C" void *beMessenger_Register(void);
extern "C" void beMessenger_GetMetaObject(void);
extern "C" void beMessenger_InitFields(void);
extern "C" igMetaObject *FUN_00357ee0(void);
extern "C" void *FUN_00357f30(void);
extern "C" int beMessengerWorkList_GetVTable(void);
extern "C" void FUN_00357fc0(void);
extern "C" void *beMessengerWorkList_Register(void);
extern "C" void beMessengerWorkList_GetMetaObject(void);
extern "C" void *beMessengerWork_Create(void *allocator);
extern "C" void beMessengerWork_EnsureRegistered();
extern "C" void *beMessengerGroup_Create(void *allocator);
extern "C" void beMessengerGroup_EnsureRegistered();
extern "C" void *beMessengerDelay_Create(void *allocator);
extern "C" void beMessengerDelay_EnsureRegistered();
extern "C" void *beMessengerArgData_Create(void *allocator);
extern "C" void beMessengerArgData_EnsureRegistered();
extern "C" void *FUN_003580b0(void);
extern "C" int beMessengerWork_GetVTable(void);
extern "C" void *beMessengerWork_Register(void);
extern "C" void beMessengerWork_GetMetaObject(void);
extern "C" void beMessengerWork_InitFields(void);
extern "C" igMetaObject *FUN_00358350(void);
extern "C" void *FUN_003583a0(void);
extern "C" int beMessengerGroupList_GetVTable(void);
extern "C" void FUN_00358430(void);
extern "C" void *beMessengerGroupList_Register(void);
extern "C" void beMessengerGroupList_GetMetaObject(void);
extern "C" void *FUN_00358520(void);
extern "C" int beMessengerGroup_GetVTable(void);
extern "C" void *beMessengerGroup_Register(void);
extern "C" void beMessengerGroup_GetMetaObject(void);
extern "C" void beMessengerGroup_InitFields(void);
extern "C" igMetaObject *FUN_003587c0(void);
extern "C" int beMessengerDelayList_GetVTable(void);
extern "C" void FUN_003588a0(void);
extern "C" void *beMessengerDelayList_Register(void);
extern "C" void beMessengerDelayList_GetMetaObject(void);
extern "C" int beMessengerDelay_GetVTable(void);
extern "C" void *beMessengerDelay_Register(void);
extern "C" void beMessengerDelay_GetMetaObject(void);
extern "C" void beMessengerDelay_InitFields(void);
extern "C" igMetaObject *FUN_00358bf0(void);
extern "C" int beMessengerArgDataList_GetVTable(void);
extern "C" void FUN_00358cd0(void);
extern "C" void *beMessengerArgDataList_Register(void);
extern "C" void beMessengerArgDataList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00358dc0(void);
extern "C" int FUN_001998f0(int *, int);
extern "C" int FUN_00226990(int *, int);
extern "C" int beMessengerArgData_GetVTable(void);
extern "C" void *beMessengerArgData_Register(void);
extern "C" void beMessengerArgData_GetMetaObject(void);
extern "C" int FUN_001899a0(void);
extern "C" void beMessengerArgData_InitFields(void);
extern "C" igMetaObject *FUN_003591e0(void);
extern "C" void *FUN_00359230(void);
extern "C" int beMemory_GetVTable(void);
extern "C" void FUN_00359310(void);
extern "C" void *beMemory_Register(void);
extern "C" void beMemory_GetMetaObject(void);
extern "C" void beMemory_InitFields(void);
extern "C" void FUN_00359480(int arg0);
extern "C" igMetaObject *FUN_003594c0(void);
extern "C" void *FUN_00359510(void);
extern "C" int beMatCtrlInfoWork_GetVTable(void);
extern "C" void FUN_00359640(void);
extern "C" void *beMatCtrlInfoWork_Register(void);
extern "C" void beMatCtrlInfoWork_GetMetaObject(void);
extern "C" int igIntListList_GetOrCreateMetaObject(void);
extern "C" void beMatCtrlInfoWork_InitFields(void);
extern "C" void *FUN_003597c0(void);
extern "C" int beMatCtrlInfoRam_GetVTable(void);
extern "C" void FUN_00359980(void);
extern "C" void *beMatCtrlInfoRam_Register(void);
extern "C" void beMatCtrlInfoRam_GetMetaObject(void);
extern "C" void beMatCtrlInfoRam_InitFields(void);
extern "C" void *FUN_00359ad0(void);
extern "C" int beMatCtrlInfo_GetVTable(void);
extern "C" void **FUN_00359bd0(void **arg0, long long arg1);
extern "C" void **FUN_00359c50(void **arg0, short arg1);
extern "C" void FUN_00359cd0(void);
extern "C" void *beMatCtrlInfo_Register(void);
extern "C" void beMatCtrlInfo_GetMetaObject(void);
extern "C" void beMatCtrlInfo_InitFields(void);
extern "C" igMetaObject *FUN_00359e60(void);
extern "C" void *FUN_00359eb0(void);
extern "C" int beMatCtrlSearchList_GetVTable(void);
extern "C" void FUN_00359f40(void);
extern "C" void *beMatCtrlSearchList_Register(void);
extern "C" void beMatCtrlSearchList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00359ff0(void);
extern "C" void *FUN_0035a040(void);
extern "C" int beMatCtrlSearch_GetVTable(void);
extern "C" void FUN_0035a120(void);
extern "C" void *beMatCtrlSearch_Register(void);
extern "C" void beMatCtrlSearch_GetMetaObject(void);
extern "C" void beMatCtrlSearch_InitFields(void);
extern "C" igMetaObject *FUN_0035a2a0(void);
extern "C" void *FUN_0035a2f0(void);
extern "C" int beMatCtrlDataList_GetVTable(void);
extern "C" void FUN_0035a380(void);
extern "C" void *beMatCtrlDataList_Register(void);
extern "C" void beMatCtrlDataList_GetMetaObject(void);
extern "C" void *FUN_0035a430(void);
extern "C" int beMatCtrlData_GetVTable(void);
extern "C" void FUN_0035a560(void);
extern "C" void *beMatCtrlData_Register(void);
extern "C" void beMatCtrlData_GetMetaObject(void);
extern "C" void beMatCtrlData_InitFields(void);
extern "C" igMetaEnum *beMatCtrl_GetMessageEnum(void);
extern "C" void beMatCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0035a750(void);
extern "C" void *FUN_0035a7a0(void);
extern "C" int beMatCtrl_GetVTable(void);
extern "C" void FUN_0035a880(void);
extern "C" void *beMatCtrl_Register(void);
extern "C" void beMatCtrl_GetMetaObject(void);
extern "C" void beMatCtrl_InitFields(void);
extern "C" void FUN_0035aa20(int arg0);
extern "C" igMetaObject *FUN_0035aa60(void);
extern "C" void *FUN_0035aab0(void);
extern "C" int beLuaState_GetVTable(void);
extern "C" void FUN_0035abe0(void);
extern "C" void *igLuaState_Register(void);
extern "C" void *beLuaState_Register(void);
extern "C" void beLuaState_GetMetaObject(void);
extern "C" int FUN_0035ac90(void);
extern "C" void beLuaState_InitFields(void);
extern "C" int beLuaInfo_GetVTable(void);
extern "C" void FUN_0035ae60(void);
extern "C" void *beLuaInfo_Register(void);
extern "C" void beLuaInfo_GetMetaObject(void);
extern "C" void beLuaInfo_InitFields(void);
extern "C" igMetaObject *FUN_0035afc0(void);
extern "C" int beLuaDataList_GetVTable(void);
extern "C" void FUN_0035b0a0(void);
extern "C" void *beLuaDataList_Register(void);
extern "C" void beLuaDataList_GetMetaObject(void);
extern "C" int beLuaData_GetVTable(void);
extern "C" void FUN_0035b280(void);
extern "C" void *beLuaData_Register(void);
extern "C" void beLuaData_GetMetaObject(void);
extern "C" void beLuaData_InitFields(void);
extern "C" int beLuaDataObjectist_GetVTable(void);
extern "C" void FUN_0035b460(void);
extern "C" void *beLuaDataObjectist_Register(void);
extern "C" void beLuaDataObjectist_GetMetaObject(void);
extern "C" igMetaObject *FUN_0035b510(void);
extern "C" void *FUN_0035b560(void);
extern "C" int beLuaDataObject_GetVTable(void);
extern "C" void FUN_0035b5f0(void);
extern "C" void *beLuaDataObject_Register(void);
extern "C" void beLuaDataObject_GetMetaObject(void);
extern "C" void beLuaDataObject_InitFields(void);
extern "C" void beLua_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0035b770(void);
extern "C" void *FUN_0035b7c0(void);
extern "C" int beLua_GetVTable(void);
extern "C" void **FUN_0035b8c0(void **arg0, short arg1);
extern "C" void FUN_0035b9c0(void);
extern "C" void *beLua_Register(void);
extern "C" void beLua_GetMetaObject(void);
extern "C" int igLuaGlue_GetOrCreateMetaObject(void);
extern "C" void beLua_InitFields(void);
extern "C" igMetaObject *FUN_0035bb70(void);
extern "C" void *FUN_0035bbc0(void);
extern "C" int igLightSetList_GetVTable(void);
extern "C" void FUN_0035bc50(void);
extern "C" void *igLightSetList_Register(void);
extern "C" void igLightSetList_GetMetaObject(void);
extern "C" void *FUN_0035bd00(void);
extern "C" int beLightCtrlInfo_GetVTable(void);
extern "C" void FUN_0035be50(void);
extern "C" void *beLightCtrlInfo_Register(void);
extern "C" void beLightCtrlInfo_GetMetaObject(void);
extern "C" void beLightCtrlInfo_InitFields(void);
extern "C" igMetaEnum *FUN_0035bfb0(void);
extern "C" void beLightCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0035c050(void);
extern "C" void *FUN_0035c0a0(void);
extern "C" int beLightCtrl_GetVTable(void);
extern "C" void FUN_0035c1d0(void);
extern "C" void *beLightCtrl_Register(void);
extern "C" void beLightCtrl_GetMetaObject(void);
extern "C" void *FUN_0035c280(void);
extern "C" int beLayerInfoRam_GetVTable(void);
extern "C" void FUN_0035c370(void);
extern "C" void *beLayerInfoRam_Register(void);
extern "C" void beLayerInfoRam_GetMetaObject(void);
extern "C" void *FUN_0035c420(void);
extern "C" int beLayerInfo_GetVTable(void);
extern "C" void FUN_0035c570(void);
extern "C" void *beLayerInfo_Register(void);
extern "C" void beLayerInfo_GetMetaObject(void);
extern "C" void beLayerInfo_InitFields(void);
extern "C" igMetaObject *FUN_0035c6c0(void);
extern "C" void *FUN_0035c710(void);
extern "C" int beLayerGroupList_GetVTable(void);
extern "C" void FUN_0035c7a0(void);
extern "C" void *beLayerGroupList_Register(void);
extern "C" void beLayerGroupList_GetMetaObject(void);
extern "C" void *FUN_0035c850(void);
extern "C" int beLayerGroup_GetVTable(void);
extern "C" void FUN_0035c930(void);
extern "C" void *beLayerGroup_Register(void);
extern "C" void beLayerGroup_GetMetaObject(void);
extern "C" igMetaEnum *beLayerCtl_GetSwtCtlEnum(void);
extern "C" igMetaEnum *beLayerCtl_GetMessageEnum(void);
extern "C" void beLayerCtl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0035cae0(void);
extern "C" void *FUN_0035cb30(void);
extern "C" int beLayerCtl_GetVTable(void);
extern "C" void FUN_0035cbf0(void);
extern "C" void *beLayerCtl_Register(void);
extern "C" void beLayerCtl_GetMetaObject(void);
extern "C" void beLayerCtl_InitFields(void);
extern "C" int FUN_0013bfe0(int *, int);
extern "C" int FUN_0019ab10(...);
extern "C" int FUN_001aaf00(...);
extern "C" int FUN_001ab380(int *, int);
extern "C" int beLOA_GetVTable(void);
extern "C" void FUN_0035ce60(void);
extern "C" void *beLOA_Register(void);
extern "C" void beLOA_GetMetaObject(void);
extern "C" int FUN_00138f20(void);
extern "C" int FUN_00139640(void);
extern "C" int FUN_00139f10(void);
extern "C" int FUN_0018e670(void *, int *);
extern "C" void beLOA_InitFields(void);
extern "C" void FUN_00389fb0(void);
extern "C" void FUN_0035d050(void);
extern "C" igMetaObject *FUN_0035d070(void);
extern "C" int beKeyboardReceiver_GetVTable(void);
extern "C" void FUN_0035d1a0(void);
extern "C" void *igEventReceiver_Register(void);
extern "C" void *beKeyboardReceiver_Register(void);
extern "C" void beKeyboardReceiver_GetMetaObject(void);
extern "C" void beKeyboardReceiver_InitFields(void);
extern "C" int beHitLandModelInfoRam_GetVTable(void);
extern "C" void FUN_0035d3f0(void);
extern "C" void *beHitLandModelInfoRam_Register(void);
extern "C" void beHitLandModelInfoRam_GetMetaObject(void);
extern "C" int beHitLandModelInfo_GetVTable(void);
extern "C" void FUN_0035d5a0(void);
extern "C" void *beHitLandModelInfo_Register(void);
extern "C" void beHitLandModelInfo_GetMetaObject(void);
extern "C" void beHitLandModelInfo_InitFields(void);
extern "C" igMetaEnum *FUN_0035d720(void);
extern "C" void beHitLandModel_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0035d7c0(void);
extern "C" void *FUN_0035d810(void);
extern "C" int beHitLandModel_GetVTable(void);
extern "C" void **FUN_0035d930(void **arg0, int arg1);
extern "C" void **FUN_0035d9b0(void **arg0, short arg1);
extern "C" void FUN_0035da30(void);
extern "C" void *beHitLandModel_Register(void);
extern "C" void beHitLandModel_GetMetaObject(void);
extern "C" int FUN_0019e6c0(void);
extern "C" void beHitLandModel_InitFields(void);
extern "C" void FUN_0035dbd0(int arg0);
extern "C" igMetaObject *FUN_0035dc10(void);
extern "C" void *FUN_0035dc60(void);
extern "C" int FUN_0019e150(char *, int);
extern "C" int beHitLandModelTraversal_GetVTable(void);
extern "C" void FUN_0035dd30(void);
extern "C" void *igIntersectTraversal_Register(void);
extern "C" void *beHitLandModelTraversal_Register(void);
extern "C" void beHitLandModelTraversal_GetMetaObject(void);
extern "C" int FUN_0035ddf0(void);
extern "C" void beHitLandModelTraversal_InitFields(void);
extern "C" void FUN_0035de90(int arg0);
extern "C" igMetaObject *FUN_0035ded0(void);
extern "C" void *FUN_0035df20(void);
extern "C" int beHitLandModelOrder_GetVTable(void);
extern "C" void FUN_0035e090(void);
extern "C" void *beHitLandModelOrder_Register(void);
extern "C" void beHitLandModelOrder_GetMetaObject(void);
extern "C" int FUN_001880b0(void);
extern "C" int FUN_0018e470(void *, int *);
extern "C" void beHitLandModelOrder_InitFields(void);
extern "C" igMetaObject *FUN_0035e270(void);
extern "C" void *FUN_0035e2c0(void);
extern "C" int beHitLandResultDataList_GetVTable(void);
extern "C" void FUN_0035e350(void);
extern "C" void *beHitLandResultDataList_Register(void);
extern "C" void beHitLandResultDataList_GetMetaObject(void);
extern "C" void FUN_0035e400(int arg0);
extern "C" void *FUN_0035e440(void);
extern "C" int beHitLandResultData_GetVTable(void);
extern "C" void FUN_0035e520(void);
extern "C" void *beHitLandResultData_Register(void);
extern "C" void beHitLandResultData_GetMetaObject(void);
extern "C" void beHitLandResultData_InitFields(void);
extern "C" void *FUN_0035e660(void);
extern "C" int beHitLandDelivInfoRam_GetVTable(void);
extern "C" void FUN_0035e7a0(void);
extern "C" void *beHitLandDelivInfoRam_Register(void);
extern "C" void beHitLandDelivInfoRam_GetMetaObject(void);
extern "C" void beHitLandDelivInfoRam_InitFields(void);
extern "C" void *FUN_0035e9c0(void);
extern "C" int beHitLandDelivInfo_GetVTable(void);
extern "C" void FUN_0035ea80(void);
extern "C" void *beHitLandDelivInfo_Register(void);
extern "C" void beHitLandDelivInfo_GetMetaObject(void);
extern "C" igMetaEnum *FUN_0035eb30(void);
extern "C" void beHitLandDeliv_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0035ebd0(void);
extern "C" void *FUN_0035ec20(void);
extern "C" int beHitLandDeliv_GetVTable(void);
extern "C" void FUN_0035ed50(void);
extern "C" void *beHitLandDeliv_Register(void);
extern "C" void beHitLandDeliv_GetMetaObject(void);
extern "C" igMetaObject *FUN_0035ee00(void);
extern "C" void *FUN_0035ee50(void);
extern "C" int beGroupKeepList_GetVTable(void);
extern "C" void FUN_0035eee0(void);
extern "C" void *beGroupKeepList_Register(void);
extern "C" void beGroupKeepList_GetMetaObject(void);
extern "C" void *FUN_0035ef90(void);
extern "C" int beGroupKeep_GetVTable(void);
extern "C" void FUN_0035f050(void);
extern "C" void *beGroupKeep_Register(void);
extern "C" void beGroupKeep_GetMetaObject(void);
extern "C" void FUN_0035f100(int arg0);
extern "C" igMetaObject *FUN_0035f140(void);
extern "C" int beGeneraterInfoWork_GetVTable(void);
extern "C" void FUN_0035f2b0(void);
extern "C" void *beGeneraterInfoWork_Register(void);
extern "C" void beGeneraterInfoWork_GetMetaObject(void);
extern "C" void beGeneraterInfoWork_InitFields(void);
extern "C" int beGeneraterInfoRam_GetVTable(void);
extern "C" void FUN_0035f5d0(void);
extern "C" void *beGeneraterInfoRam_Register(void);
extern "C" void beGeneraterInfoRam_GetMetaObject(void);
extern "C" void beGeneraterInfoRam_InitFields(void);
extern "C" int beGeneraterInfo_GetVTable(void);
extern "C" void **FUN_0035f7f0(void **arg0, long long arg1);
extern "C" void FUN_0035f870(void);
extern "C" void *beGeneraterInfo_Register(void);
extern "C" void beGeneraterInfo_GetMetaObject(void);
extern "C" void beGeneraterInfo_InitFields(void);
extern "C" igMetaObject *FUN_0035f9d0(void);
extern "C" int beGeneraterDataList_GetVTable(void);
extern "C" void FUN_0035fab0(void);
extern "C" void *beGeneraterDataList_Register(void);
extern "C" void beGeneraterDataList_GetMetaObject(void);
extern "C" void *FUN_0035fb60(void);
extern "C" int beGeneraterData_GetVTable(void);
extern "C" void FUN_0035fd50(void);
extern "C" void *beGeneraterData_Register(void);
extern "C" void beGeneraterData_GetMetaObject(void);
extern "C" void beGeneraterData_InitFields(void);
extern "C" igMetaObject *FUN_0035ff20(void);
extern "C" void *FUN_0035ff70(void);
extern "C" int beGeneraterPlayerDataList_GetVTable(void);
extern "C" void FUN_00360000(void);
extern "C" void *beGeneraterPlayerDataList_Register(void);
extern "C" void beGeneraterPlayerDataList_GetMetaObject(void);
extern "C" void *FUN_003600b0(void);
extern "C" int beGeneraterPlayerData_GetVTable(void);
extern "C" void FUN_003601e0(void);
extern "C" void *beGeneraterPlayerData_Register(void);
extern "C" void beGeneraterPlayerData_GetMetaObject(void);
extern "C" void beGeneraterPlayerData_InitFields(void);
extern "C" igMetaObject *FUN_00360360(void);
extern "C" void *FUN_003603b0(void);
extern "C" int beGeneraterItemDataList_GetVTable(void);
extern "C" void FUN_00360440(void);
extern "C" void *beGeneraterItemDataList_Register(void);
extern "C" void beGeneraterItemDataList_GetMetaObject(void);
extern "C" void *FUN_003604f0(void);
extern "C" int beGeneraterItemData_GetVTable(void);
extern "C" void FUN_00360620(void);
extern "C" void *beGeneraterItemData_Register(void);
extern "C" void beGeneraterItemData_GetMetaObject(void);
extern "C" void beGeneraterItemData_InitFields(void);
extern "C" igMetaObject *FUN_00360780(void);
extern "C" void *FUN_003607d0(void);
extern "C" int beGeneraterItemDataOneList_GetVTable(void);
extern "C" void FUN_00360860(void);
extern "C" void *beGeneraterItemDataOneList_Register(void);
extern "C" void beGeneraterItemDataOneList_GetMetaObject(void);
extern "C" void *FUN_00360910(void);
extern "C" int beGeneraterItemDataOne_GetVTable(void);
extern "C" void FUN_003609f0(void);
extern "C" void *beGeneraterItemDataOne_Register(void);
extern "C" void beGeneraterItemDataOne_GetMetaObject(void);
extern "C" void beGeneraterItemDataOne_InitFields(void);
extern "C" igMetaEnum *FUN_00360b10(void);
extern "C" void beGenerater_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00360bb0(void);
extern "C" void *FUN_00360c00(void);
extern "C" int beGenerater_GetVTable(void);
extern "C" void FUN_00360d30(void);
extern "C" void *beGenerater_Register(void);
extern "C" void beGenerater_GetMetaObject(void);
extern "C" void beGenerater_InitFields(void);
extern "C" void *FUN_00360e90(void);
extern "C" int beFontInfo_GetVTable(void);
extern "C" void FUN_00360fe0(void);
extern "C" void *beFontInfo_Register(void);
extern "C" void beFontInfo_GetMetaObject(void);
extern "C" void beFontInfo_InitFields(void);
extern "C" void *FUN_00361130(void);
extern "C" int FUN_001d97f0(...);
extern "C" int beFontInfoData_GetVTable(void);
extern "C" void FUN_00361210(void);
extern "C" void *beFontInfoData_Register(void);
extern "C" void beFontInfoData_GetMetaObject(void);
extern "C" void beFontInfoData_InitFields(void);
extern "C" igMetaObject *FUN_00361360(void);
extern "C" int beUnicodeObjList_GetVTable(void);
extern "C" void FUN_00361440(void);
extern "C" void *beUnicodeObjList_Register(void);
extern "C" void beUnicodeObjList_GetMetaObject(void);
extern "C" void beUnicodeObj_Create(int arg0);
extern "C" int beUnicodeObj_GetVTable(void);
extern "C" void FUN_00361610(void);
extern "C" void *beUnicodeObj_Register(void);
extern "C" void beUnicodeObj_GetMetaObject(void);
extern "C" int igUnsignedShortMetaField_GetDefaultDescriptor(void);
extern "C" void beUnicodeObj_InitFields(void);
extern "C" igMetaObject *FUN_00361750(void);
extern "C" int beFontImageList_GetVTable(void);
extern "C" void FUN_00361830(void);
extern "C" void *beFontImageList_Register(void);
extern "C" void beFontImageList_GetMetaObject(void);
extern "C" int beFontImage_GetVTable(void);
extern "C" void **FUN_003619a0(void **arg0, short arg1);
extern "C" void FUN_00361c70(void);
extern "C" void *igBitmapFont_Register(void);
extern "C" void *beFontImage_Register(void);
extern "C" void beFontImage_GetMetaObject(void);
extern "C" int FUN_00361d20(void);
extern "C" igMetaEnum *beFont_GetAlignEnum(void);
extern "C" igMetaEnum *beFont_GetSwitchEnum(void);
extern "C" igMetaEnum *beFont_GetMessageEnum(void);
extern "C" void beFont_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00361e90(void);
extern "C" void *FUN_00361ee0(void);
extern "C" int beFont_GetVTable(void);
extern "C" void **FUN_003620f0(void **arg0, short arg1);
extern "C" void FUN_00362170(void);
extern "C" void *beFont_Register(void);
extern "C" void beFont_GetMetaObject(void);
extern "C" void beFont_InitFields(void);
extern "C" igMetaObject *FUN_00362360(void);
extern "C" void *FUN_003623b0(void);
extern "C" int beFontGeomAttrPairList_GetVTable(void);
extern "C" void FUN_00362440(void);
extern "C" void *beFontGeomAttrPairList_Register(void);
extern "C" void beFontGeomAttrPairList_GetMetaObject(void);
extern "C" void beFontGeomAttrPair_Create(int arg0);
extern "C" void *FUN_00362530(void);
extern "C" int beFontGeomAttrPair_GetVTable(void);
extern "C" void FUN_00362690(void);
extern "C" void *beFontGeomAttrPair_Register(void);
extern "C" void beFontGeomAttrPair_GetMetaObject(void);
extern "C" int FUN_0013a4d0(void);
extern "C" void beFontGeomAttrPair_InitFields(void);
extern "C" void beFileListInfoManager_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00362830(void);
extern "C" void *FUN_00362880(void);
extern "C" int igSmartPointer_igDirectoryList_Destruct(int *, int);
extern "C" int beFileListInfoManager_GetVTable(void);
extern "C" void FUN_003629b0(void);
extern "C" void *beFileListInfoManager_Register(void);
extern "C" void beFileListInfoManager_GetMetaObject(void);
extern "C" int igDirectoryList_GetOrCreateMetaObject(void);
extern "C" int FUN_00459380(void);
extern "C" void beFileListInfoManager_InitFields(void);
extern "C" void *FUN_00362c00(void);
extern "C" int beFileListInfo_GetVTable(void);
extern "C" void FUN_00362ce0(void);
extern "C" void *beFileListInfo_Register(void);
extern "C" void beFileListInfo_GetMetaObject(void);
extern "C" void beFileListInfo_InitFields(void);
extern "C" void *FUN_00362e50(void);
extern "C" int beFile_GetVTable(void);
extern "C" void FUN_00362ee0(void);
extern "C" void *beFile_Register(void);
extern "C" void beFile_GetMetaObject(void);
extern "C" void FUN_00362f90(int arg0);
extern "C" void *FUN_00362fd0(void);
extern "C" int beFileChkObj_GetVTable(void);
extern "C" void FUN_003630b0(void);
extern "C" void *beFileChkObj_Register(void);
extern "C" void beFileChkObj_GetMetaObject(void);
extern "C" int igFile_GetOrCreateMetaObject(void);
extern "C" void beFileChkObj_InitFields(void);
extern "C" void beDemoManager_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00363250(void);
extern "C" void *FUN_003632a0(void);
extern "C" int beDemoManager_GetVTable(void);
extern "C" void FUN_00363480(void);
extern "C" void *beDemoManager_Register(void);
extern "C" void beDemoManager_GetMetaObject(void);
extern "C" void beDemoManager_InitFields(void);
extern "C" igMetaObject *FUN_00363630(void);
extern "C" void *FUN_00363680(void);
extern "C" int beDemoManagerWorkList_GetVTable(void);
extern "C" void FUN_00363710(void);
extern "C" void *beDemoManagerWorkList_Register(void);
extern "C" void beDemoManagerWorkList_GetMetaObject(void);
extern "C" void beDemoManagerWork_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00363800(void);
extern "C" void *FUN_00363850(void);
extern "C" int beDemoManagerWork_GetVTable(void);
extern "C" void FUN_00363930(void);
extern "C" void *beDemoManagerWork_Register(void);
extern "C" void beDemoManagerWork_GetMetaObject(void);
extern "C" void beDemoManagerWork_InitFields(void);
extern "C" igMetaObject *FUN_00363a90(void);
extern "C" int beDemoKeepMesList_GetVTable(void);
extern "C" void FUN_00363b70(void);
extern "C" void *beDemoKeepMesList_Register(void);
extern "C" void beDemoKeepMesList_GetMetaObject(void);
extern "C" void beDemoKeepMes_CreateInstance(int arg0);
extern "C" int beDemoKeepMes_GetVTable(void);
extern "C" void FUN_00363d60(void);
extern "C" void *beDemoKeepMes_Register(void);
extern "C" void beDemoKeepMes_GetMetaObject(void);
extern "C" void beDemoKeepMes_InitFields(void);
extern "C" void beDataObjListList_Create(int arg0);
extern "C" igMetaObject *FUN_00363ec0(void);
extern "C" int beDataObjListList_GetVTable(void);
extern "C" void FUN_00363fa0(void);
extern "C" void *beDataObjListList_Register(void);
extern "C" void beDataObjListList_GetMetaObject(void);
extern "C" void beDataObjList_Create(int arg0);
extern "C" igMetaObject *FUN_00364090(void);
extern "C" int beDataObjList_GetVTable(void);
extern "C" void FUN_00364170(void);
extern "C" void *beDataObjList_Register(void);
extern "C" void beDataObjList_GetMetaObject(void);
extern "C" void beDataObjFloatList_Create(int arg0);
extern "C" void *FUN_00364260(void);
extern "C" int beDataObjFloatList_GetVTable(void);
extern "C" void FUN_00364390(void);
extern "C" void *beDataObjFloatList_Register(void);
extern "C" void beDataObjFloatList_GetMetaObject(void);
extern "C" void beDataObjFloatList_InitFields(void);
extern "C" void beDataObjObjectList_Create(int arg0);
extern "C" void *FUN_00364530(void);
extern "C" int beDataObjObjectList_GetVTable(void);
extern "C" void FUN_00364660(void);
extern "C" void *beDataObjObjectList_Register(void);
extern "C" void beDataObjObjectList_GetMetaObject(void);
extern "C" void beDataObjObjectList_InitFields(void);
extern "C" void beDataObjStringList_Create(int arg0);
extern "C" void *FUN_00364800(void);
extern "C" int beDataObjStringList_GetVTable(void);
extern "C" void FUN_00364930(void);
extern "C" void *beDataObjStringList_Register(void);
extern "C" void beDataObjStringList_GetMetaObject(void);
extern "C" void beDataObjStringList_InitFields(void);
extern "C" void beDataObjString_Create(int arg0);
extern "C" void *FUN_00364ad0(void);
extern "C" int beDataObjString_GetVTable(void);
extern "C" void FUN_00364bf0(void);
extern "C" void *beDataObjString_Register(void);
extern "C" void beDataObjString_GetMetaObject(void);
extern "C" void beDataObjString_InitFields(void);
extern "C" void beDataObjBoolList_Create(int arg0);
extern "C" void *FUN_00364d70(void);
extern "C" int beDataObjBoolList_GetVTable(void);
extern "C" void FUN_00364ea0(void);
extern "C" void *beDataObjBoolList_Register(void);
extern "C" void beDataObjBoolList_GetMetaObject(void);
extern "C" void beDataObjBoolList_InitFields(void);
extern "C" void beDataObjBool_Create(int arg0);
extern "C" void *FUN_00365040(void);
extern "C" int beDataObjBool_GetVTable(void);
extern "C" void FUN_00365120(void);
extern "C" void *beDataObjBool_Register(void);
extern "C" void beDataObjBool_GetMetaObject(void);
extern "C" void beDataObjBool_InitFields(void);
extern "C" void beDataObjIntList_Create(int arg0);
extern "C" void *FUN_00365280(void);
extern "C" int beDataObjIntList_GetVTable(void);
extern "C" void FUN_003653b0(void);
extern "C" void *beDataObjIntList_Register(void);
extern "C" void beDataObjIntList_GetMetaObject(void);
extern "C" void beDataObjIntList_InitFields(void);
extern "C" void beDataObjInt_Create(int arg0);
extern "C" igMetaObject *FUN_00365550(void);
extern "C" void *FUN_003655a0(void);
extern "C" int beDataObjInt_GetVTable(void);
extern "C" void FUN_00365680(void);
extern "C" void *beDataObjInt_Register(void);
extern "C" void beDataObjInt_GetMetaObject(void);
extern "C" void beDataObjInt_InitFields(void);
extern "C" void *FUN_003657a0(void);
extern "C" int beDataBaseList_GetVTable(void);
extern "C" void FUN_00365830(void);
extern "C" void *beDataBaseList_Register(void);
extern "C" void beDataBaseList_GetMetaObject(void);
extern "C" igMetaObject *FUN_003658e0(void);
extern "C" void *FUN_00365930(void);
extern "C" int FUN_001648f0(int *, int);
extern "C" int FUN_00164970(int *, int);
extern "C" int beDataBase_GetVTable(void);
extern "C" void FUN_00365b00(void);
extern "C" void *beDataBase_Register(void);
extern "C" void beDataBase_GetMetaObject(void);
extern "C" int igShortList_GetOrCreateMetaObject(void);
extern "C" int igCharList_GetOrCreateMetaObject(void);
extern "C" void beDataBase_InitFields(void);
extern "C" int beDBManagerInfo_GetVTable(void);
extern "C" void **FUN_00365e90(void **arg0, long long arg1);
extern "C" void FUN_00365f10(void);
extern "C" void *beDBManagerInfo_Register(void);
extern "C" void beDBManagerInfo_GetMetaObject(void);
extern "C" void beDBManagerInfo_InitFields(void);
extern "C" igMetaEnum *FUN_00366070(void);
extern "C" void beDBManager_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00366110(void);
extern "C" int beDBManager_GetVTable(void);
extern "C" void FUN_00366290(void);
extern "C" void *beDBManager_Register(void);
extern "C" void beDBManager_GetMetaObject(void);
extern "C" igMetaObject *FUN_00366340(void);
extern "C" int beCriVolume_GetVTable(void);
extern "C" void FUN_00366420(void);
extern "C" void *beCriVolume_Register(void);
extern "C" void beCriVolume_GetMetaObject(void);
extern "C" void beCriVolume_InitFields(void);
extern "C" int beCriSfpData_GetVTable(void);
extern "C" void FUN_00366620(void);
extern "C" void *beCriSfpData_Register(void);
extern "C" void beCriSfpData_GetMetaObject(void);
extern "C" igMetaObject *FUN_003666e0(void);
extern "C" void beCriSfpData_InitFields(void);
extern "C" void beCriSfpData_SetupBufferAlignment(void);
extern "C" void FUN_00366760(void);
extern "C" igMetaObject *FUN_00366780(void);
extern "C" void *FUN_003667d0(void);
extern "C" int beCriHandleList_GetVTable(void);
extern "C" void FUN_00366860(void);
extern "C" void *beCriHandleList_Register(void);
extern "C" void beCriHandleList_GetMetaObject(void);
extern "C" void beCriHandle_Create(int arg0);
extern "C" igMetaObject *FUN_00366950(void);
extern "C" void *FUN_003669a0(void);
extern "C" int beCriHandle_GetVTable(void);
extern "C" void FUN_00366b20(void);
extern "C" void *beCriHandle_Register(void);
extern "C" void beCriHandle_GetMetaObject(void);
extern "C" void beCriHandle_InitFields(void);
extern "C" void *FUN_00366ca0(void);
extern "C" int beCriFxInfo_GetVTable(void);
extern "C" void **FUN_00366d80(void **arg0, int arg1);
extern "C" void FUN_00366e00(void);
extern "C" void *beCriFxInfo_Register(void);
extern "C" void beCriFxInfo_GetMetaObject(void);
extern "C" void beCriFxInfo_InitFields(void);
extern "C" igMetaObject *FUN_00366fa0(void);
extern "C" void *FUN_00366ff0(void);
extern "C" int beCriFxXbData_GetVTable(void);
extern "C" void FUN_00367080(void);
extern "C" void *beCriFxXbData_Register(void);
extern "C" void beCriFxXbData_GetMetaObject(void);
extern "C" void beCriFxXbData_InitFields(void);
extern "C" igMetaObject *FUN_003671a0(void);
extern "C" void *FUN_003671f0(void);
extern "C" int beCriAudio_GetVTable(void);
extern "C" void FUN_00367320(void);
extern "C" void *beCriAudio_Register(void);
extern "C" void beCriAudio_GetMetaObject(void);
extern "C" int FUN_00335130(void);
extern "C" void beCriAudio_InitFields(void);
extern "C" void beCriSndf_Create(int arg0);
extern "C" igMetaObject *FUN_003674d0(void);
extern "C" void *FUN_00367520(void);
extern "C" int beCriSndf_GetVTable(void);
extern "C" void FUN_003675b0(void);
extern "C" void *beCriSndf_Register(void);
extern "C" void beCriSndf_GetMetaObject(void);
extern "C" void beCriSndf_InitFields(void);
extern "C" void *FUN_003676d0(void);
extern "C" int beCriAcxData_GetVTable(void);
extern "C" void FUN_003677b0(void);
extern "C" void *beCriAcxData_Register(void);
extern "C" void beCriAcxData_GetMetaObject(void);
extern "C" void beCri_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_003678a0(void);
extern "C" void *FUN_003678f0(void);
extern "C" int beCri_GetVTable(void);
extern "C" void **FUN_00367a20(void **arg0, short arg1);
extern "C" void FUN_00367b20(void);
extern "C" void *beCri_Register(void);
extern "C" void beCri_GetMetaObject(void);
extern "C" void beCri_InitFields(void);
extern "C" void *FUN_00367d10(void);
extern "C" int beCountry_GetVTable(void);
extern "C" void FUN_00367da0(void);
extern "C" void *beCountry_Register(void);
extern "C" void beCountry_GetMetaObject(void);
extern "C" void *FUN_00367e50(void);
extern "C" int beCopyTransform_GetVTable(void);
extern "C" void FUN_00367f40(void);
extern "C" void *beCopyTransform_Register(void);
extern "C" void beCopyTransform_GetMetaObject(void);
extern "C" void beCopyTransform_InitFields(void);
extern "C" void beCopyTransform_RegisterTraversal(void);
extern "C" void FUN_00368090(void);
extern "C" int beCopyModelCtrl2_GetVTable(void);
extern "C" void FUN_003681a0(void);
extern "C" void *beCopyModelCtrl2_Register(void);
extern "C" void beCopyModelCtrl2_GetMetaObject(void);
extern "C" void beCopyModelCtrl2_InitFields(void);
extern "C" void beCopyModelCtrl2_RegisterTraversal(void);
extern "C" void FUN_003682f0(void);
extern "C" int beChangePosTransformInfoRam_GetVTable(void);
extern "C" void FUN_00368450(void);
extern "C" void *beChangePosTransformInfoRam_Register(void);
extern "C" void beChangePosTransformInfoRam_GetMetaObject(void);
extern "C" void beChangePosTransformInfoRam_InitFields(void);
extern "C" int beChangePosTransformInfo_GetVTable(void);
extern "C" void FUN_00368660(void);
extern "C" void *beChangePosTransformInfo_Register(void);
extern "C" void beChangePosTransformInfo_GetMetaObject(void);
extern "C" void beChangePosTransform_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00368750(void);
extern "C" int beChangePosTransform_GetVTable(void);
extern "C" void FUN_003688d0(void);
extern "C" void *beChangePosTransform_Register(void);
extern "C" void beChangePosTransform_GetMetaObject(void);
extern "C" void beChangePosTransform_InitFields(void);
extern "C" void beCameraMode_Create(int arg0);
extern "C" igMetaObject *FUN_00368a30(void);
extern "C" void *FUN_00368a80(void);
extern "C" int igMatrix44f_SetIdentity(int *);
extern "C" int beCameraMode_GetVTable(void);
extern "C" void FUN_00368bc0(void);
extern "C" void *igViewMode_Register(void);
extern "C" void *beCameraMode_Register(void);
extern "C" void beCameraMode_GetMetaObject(void);
extern "C" int FUN_00368c80(void);
extern "C" int FUN_0019f670(void);
extern "C" int FUN_001a4560(void);
extern "C" int FUN_00232840(void);
extern "C" void beCameraMode_InitFields(void);
extern "C" void *FUN_00368d60(void);
extern "C" int ObjectRef_Destruct_001363f0(int *, int);
extern "C" int beCameraCtrlInfo_GetVTable(void);
extern "C" void FUN_00368e30(void);
extern "C" void *beCameraCtrlInfo_Register(void);
extern "C" void beCameraCtrlInfo_GetMetaObject(void);
extern "C" void beCameraCtrlInfo_InitFields(void);
extern "C" void *FUN_00368f80(void);
extern "C" int beCameraDemoData_GetVTable(void);
extern "C" void FUN_00369060(void);
extern "C" void *beCameraDemoData_Register(void);
extern "C" void beCameraDemoData_GetMetaObject(void);
extern "C" void beCameraDemoData_InitFields(void);
extern "C" void *FUN_003691b0(void);
extern "C" int FUN_0019c220(int *, int);
extern "C" int beCameraBoxData_GetVTable(void);
extern "C" void FUN_003692d0(void);
extern "C" void *beCameraBoxData_Register(void);
extern "C" void beCameraBoxData_GetMetaObject(void);
extern "C" int FUN_0019f930(void);
extern "C" void beCameraBoxData_InitFields(void);
extern "C" void beCameraCtrlInfoRamShake_Create(int arg0);
extern "C" void *FUN_003694e0(void);
extern "C" int beCameraCtrlInfoRamShake_GetVTable(void);
extern "C" void FUN_00369600(void);
extern "C" void *beCameraCtrlInfoRamShake_Register(void);
extern "C" void beCameraCtrlInfoRamShake_GetMetaObject(void);
extern "C" void beCameraCtrlInfoRamShake_InitFields(void);
extern "C" igMetaEnum *beCameraCtrl_GetMessageEnum(void);
extern "C" void beCameraCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00369860(void);
extern "C" void *FUN_003698b0(void);
extern "C" int beCameraCtrl_GetVTable(void);
extern "C" void **FUN_003699a0(void **arg0, long long arg1);
extern "C" void FUN_00369a20(void);
extern "C" void *beCameraCtrl_Register(void);
extern "C" void beCameraCtrl_GetMetaObject(void);
extern "C" int FUN_0045b420(void);
extern "C" void beCameraCtrl_InitFields(void);
extern "C" void *FUN_00369be0(void);
extern "C" int beBkColorInfo_GetVTable(void);
extern "C" void FUN_00369ca0(void);
extern "C" void *beBkColorInfo_Register(void);
extern "C" void beBkColorInfo_GetMetaObject(void);
extern "C" void beBkColorInfo_InitFields(void);
extern "C" void beBkColor_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00369e00(void);
extern "C" void *FUN_00369e50(void);
extern "C" int beBkColor_GetVTable(void);
extern "C" void FUN_00369f80(void);
extern "C" void *beBkColor_Register(void);
extern "C" void beBkColor_GetMetaObject(void);
extern "C" void beBkColor_InitFields(void);
extern "C" igMetaObject *beBaseInfoRamList_GetOrCreateMetaObject(void);
extern "C" void *beBaseInfoRamList_GetReadyMetaObject(void);
extern "C" int beBaseInfoRamList_GetVTable(void);
extern "C" void beBaseInfoRamList_EnsureRegistered(void);
extern "C" void *beBaseInfoRamList_Register(void);
extern "C" void *beBaseInfoRamList_GetMetaObject(void);
extern "C" igMetaObject *FUN_0036a230(void);
extern "C" void *FUN_0036a280(void);
extern "C" int beBaseInfoRam_GetVTable(void);
extern "C" void FUN_0036a360(void);
extern "C" void *beBaseInfoRam_Register(void);
extern "C" void beBaseInfoRam_GetMetaObject(void);
extern "C" void beBaseInfoRam_InitFields(void);
extern "C" void beBaseInfoRamTimer_Create(int arg0);
extern "C" void *FUN_0036a550(void);
extern "C" int beBaseInfoRamTimer_GetVTable(void);
extern "C" void FUN_0036a630(void);
extern "C" void *beBaseInfoRamTimer_Register(void);
extern "C" void beBaseInfoRamTimer_GetMetaObject(void);
extern "C" void beBaseInfoRamTimer_InitFields(void);
extern "C" int beBaseInfoManagerList_GetVTable(void);
extern "C" void FUN_0036a820(void);
extern "C" void *beBaseInfoManagerList_Register(void);
extern "C" void beBaseInfoManagerList_GetMetaObject(void);
extern "C" igMetaObject *FUN_0036a8d0(void);
extern "C" void FUN_0036a970(void);
extern "C" void *beBaseInfoManager_Register(void);
extern "C" void beBaseInfoManager_GetMetaObject(void);
extern "C" void beBaseInfoManager_InitFields(void);
extern "C" igMetaObject *FUN_0036aaf0(void);
extern "C" int beBaseInfoList_GetVTable(void);
extern "C" void FUN_0036abd0(void);
extern "C" void *beBaseInfoList_Register(void);
extern "C" void beBaseInfoList_GetMetaObject(void);
extern "C" igMetaObject *FUN_0036ac80(void);
extern "C" void FUN_0036ad20(void);
extern "C" void *beBaseInfo_Register(void);
extern "C" void beBaseInfo_GetMetaObject(void);
extern "C" void beBaseInfo_InitFields(void);
extern "C" void beBaseInfoDataList_Create(int arg0);
extern "C" igMetaObject *FUN_0036aec0(void);
extern "C" void *FUN_0036af10(void);
extern "C" int beBaseInfoDataList_GetVTable(void);
extern "C" void FUN_0036afa0(void);
extern "C" void *beBaseInfoDataList_Register(void);
extern "C" void beBaseInfoDataList_GetMetaObject(void);
extern "C" void *FUN_0036b050(void);
extern "C" void FUN_0036b0a0(void);
extern "C" void *beBaseInfoData_Register(void);
extern "C" void beBaseInfoData_GetMetaObject(void);
extern "C" void beBaseInfoData_InitFields(void);
extern "C" void *FUN_0036b1c0(void);
extern "C" int beActionStarterInfoRam_GetVTable(void);
extern "C" void FUN_0036b2b0(void);
extern "C" void *beActionStarterInfoRam_Register(void);
extern "C" void beActionStarterInfoRam_GetMetaObject(void);
extern "C" void *FUN_0036b360(void);
extern "C" int beActionStarterInfo_GetVTable(void);
extern "C" void FUN_0036b4b0(void);
extern "C" void *beActionStarterInfo_Register(void);
extern "C" void beActionStarterInfo_GetMetaObject(void);
extern "C" void beActionStarterInfo_InitFields(void);
extern "C" igMetaObject *FUN_0036b600(void);
extern "C" void *FUN_0036b650(void);
extern "C" int beAsTargetModelDataList_GetVTable(void);
extern "C" void FUN_0036b6e0(void);
extern "C" void *beAsTargetModelDataList_Register(void);
extern "C" void beAsTargetModelDataList_GetMetaObject(void);
extern "C" void *FUN_0036b790(void);
extern "C" int beAsTargetModelData_GetVTable(void);
extern "C" void FUN_0036b8c0(void);
extern "C" void *beAsTargetModelData_Register(void);
extern "C" void beAsTargetModelData_GetMetaObject(void);
extern "C" void beAsTargetModelData_InitFields(void);
extern "C" void *FUN_0036ba10(void);
extern "C" int beActionStarterData2_GetVTable(void);
extern "C" void FUN_0036bb30(void);
extern "C" void *beActionStarterData2_Register(void);
extern "C" void beActionStarterData2_GetMetaObject(void);
extern "C" igMetaObject *FUN_0036bbe0(void);
extern "C" void beActionStarterData2_InitFields(void);
extern "C" igMetaObject *FUN_0036bc60(void);
extern "C" void *FUN_0036bcb0(void);
extern "C" int beActionStarterDataList_GetVTable(void);
extern "C" void FUN_0036bd40(void);
extern "C" void *beActionStarterDataList_Register(void);
extern "C" void beActionStarterDataList_GetMetaObject(void);
extern "C" void *FUN_0036bdf0(void);
extern "C" int beActionStarterData_GetVTable(void);
extern "C" void FUN_0036bf10(void);
extern "C" void *beActionStarterData_Register(void);
extern "C" void beActionStarterData_GetMetaObject(void);
extern "C" void beActionStarterData_InitFields(void);
extern "C" void beActionStarter_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0036c070(void);
extern "C" void *FUN_0036c0c0(void);
extern "C" int beActionStarter_GetVTable(void);
extern "C" void FUN_0036c1f0(void);
extern "C" void *beActionStarter_Register(void);
extern "C" void beActionStarter_GetMetaObject(void);
extern "C" void beAction2InfoWork_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0036c2e0(void);
extern "C" int FUN_001d21b0(char *, int);
extern "C" int FUN_00239200(char *, int);
extern "C" int beAction2InfoWork_GetVTable(void);
extern "C" void **FUN_0036c450(void **arg0, short arg1);
extern "C" void FUN_0036c4d0(void);
extern "C" void *beAction2InfoWork_Register(void);
extern "C" void beAction2InfoWork_GetMetaObject(void);
extern "C" int FUN_001313d0(void);
extern "C" int FUN_00135e60(void);
extern "C" void beAction2InfoWork_InitFields(void);
extern "C" int FUN_001a7a00(char *, int);
extern "C" int FUN_001aa310(char *, int);
extern "C" int beAction2InfoRam_GetVTable(void);
extern "C" void **FUN_0036c790(void **arg0, short arg1);
extern "C" void FUN_0036c810(void);
extern "C" void *beAction2InfoRam_Register(void);
extern "C" void beAction2InfoRam_GetMetaObject(void);
extern "C" int FUN_001a5fe0(void);
extern "C" int FUN_001aa5c0(void);
extern "C" void beAction2InfoRam_InitFields(void);
extern "C" int beAction2InfoList_GetVTable(void);
extern "C" void FUN_0036ca50(void);
extern "C" void *beAction2InfoList_Register(void);
extern "C" void beAction2InfoList_GetMetaObject(void);
extern "C" int FUN_001aa390(int *, int);
extern "C" int beAction2Info_GetVTable(void);
extern "C" void FUN_0036cc80(void);
extern "C" void *beAction2Info_Register(void);
extern "C" void beAction2Info_GetMetaObject(void);
extern "C" int FUN_001a7780(void);
extern "C" void beAction2Info_InitFields(void);
extern "C" void *FUN_0036ce10(void);
extern "C" int beAction2FLASHSET_GetVTable(void);
extern "C" void FUN_0036cef0(void);
extern "C" void *beAction2FLASHSET_Register(void);
extern "C" void beAction2FLASHSET_GetMetaObject(void);
extern "C" void *FUN_0036cfa0(void);
extern "C" int beAction2WAITCHECK_GetVTable(void);
extern "C" void FUN_0036d080(void);
extern "C" void *beAction2WAITCHECK_Register(void);
extern "C" void beAction2WAITCHECK_GetMetaObject(void);
extern "C" void beAction2WAITCHECK_InitFields(void);
extern "C" void *FUN_0036d1a0(void);
extern "C" int beAction2FADESET_GetVTable(void);
extern "C" void FUN_0036d280(void);
extern "C" void *beAction2FADESET_Register(void);
extern "C" void beAction2FADESET_GetMetaObject(void);
extern "C" void beAction2FADESET_InitFields(void);
extern "C" void *FUN_0036d3a0(void);
extern "C" int beAction2JOINTSET_GetVTable(void);
extern "C" void FUN_0036d4c0(void);
extern "C" void *beAction2JOINTSET_Register(void);
extern "C" void beAction2JOINTSET_GetMetaObject(void);
extern "C" void beAction2JOINTSET_InitFields(void);
extern "C" void *FUN_0036d5e0(void);
extern "C" int beAction2MOTIONSET_GetVTable(void);
extern "C" void FUN_0036d740(void);
extern "C" void *beAction2MOTIONSET_Register(void);
extern "C" void beAction2MOTIONSET_GetMetaObject(void);
extern "C" void beAction2MOTIONSET_InitFields(void);
extern "C" igMetaObject *FUN_0036d860(void);
extern "C" void *FUN_0036d8b0(void);
extern "C" int beAction2DataList_GetVTable(void);
extern "C" void FUN_0036d940(void);
extern "C" void *beAction2DataList_Register(void);
extern "C" void beAction2DataList_GetMetaObject(void);
extern "C" igMetaObject *FUN_0036d9f0(void);
extern "C" void *FUN_0036da40(void);
extern "C" int beAction2Data_GetVTable(void);
extern "C" void FUN_0036db70(void);
extern "C" void *beAction2Data_Register(void);
extern "C" void beAction2Data_GetMetaObject(void);
extern "C" void beAction2Data_InitFields(void);
extern "C" igMetaEnum *beAction2_GetMessageEnum(void);
extern "C" void beAction2_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0036dd70(void);
extern "C" void *FUN_0036ddc0(void);
extern "C" int beAction2_GetVTable(void);
extern "C" void FUN_0036def0(void);
extern "C" void *beAction2_Register(void);
extern "C" void beAction2_GetMetaObject(void);
extern "C" void be_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0036dfe0(void);
extern "C" void *FUN_0036e030(void);
extern "C" int be_GetVTable(void);
extern "C" void be_EnsureRegistered(void);
extern "C" void *be_Register(void);
extern "C" void be_GetMetaObject(void);
extern "C" void be_InitFields(void);
extern "C" void *FUN_0036e2c0(void);
extern "C" int ParticleArray_GetVTable(void);
extern "C" void FUN_0036e3b0(void);
extern "C" void *igParticleArray_Register(void);
extern "C" void *ParticleArray_Register(void);
extern "C" void ParticleArray_GetMetaObject(void);
extern "C" void ParticleArray_InitFields(void);
extern "C" igMetaObject *FUN_0036e5c0(void);
extern "C" int ParticleTimer_GetVTable(void);
extern "C" void FUN_0036e6d0(void);
extern "C" void *igGeometry_Register(void);
extern "C" void *ParticleTimer_Register(void);
extern "C" void ParticleTimer_GetMetaObject(void);
extern "C" void ParticleTimer_InitFields(void);
extern "C" void FUN_003a3900(void);
extern "C" void FUN_0036e860(void);
extern "C" igMetaEnum *FUN_0036e880(void);
extern "C" igMetaEnum *FUN_0036e8e0(void);
extern "C" igMetaEnum *FUN_0036e940(void);
extern "C" igMetaEnum *FUN_0036e9a0(void);
extern "C" int FUN_00132390(int *, int);
extern "C" int ParticleInfo_GetVTable(void);
extern "C" void FUN_0036eaf0(void);
extern "C" void *igSceneInfo_Register(void);
extern "C" void *ParticleInfo_Register(void);
extern "C" void ParticleInfo_GetMetaObject(void);
extern "C" int FUN_0036ebb0(void);
extern "C" int FUN_0014dfb0(void);
extern "C" int igEnumMetaField_SetDefaultValue(void *field, const int &value);
extern "C" void ParticleInfo_InitFields(void);
extern "C" int memset(int, int, int);
extern "C" int Gap__Core__igObject__resetFields(...);
extern "C" igMetaObject *Gap__Bec__ParticleInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2Data__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2DataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2DataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beAction2MOTIONSET__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2JOINTSET__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2FADESET__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2WAITCHECK__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2FLASHSET__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2Info__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2InfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2InfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beAction2InfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAction2InfoWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beActionStarterDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beActionStarterDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beActionStarterData2__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beActionStarterData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAsTargetModelData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAsTargetModelDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beAsTargetModelDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beActionStarterInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beActionStarterInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoManagerList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoManagerList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoRamTimer__vfunc_20(void);
extern "C" igMetaObject *beBaseInfoRamList_GetMetaObject_Virtual(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoRamList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beBkColorInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCameraCtrlInfoRamShake__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCameraBoxData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCameraDemoData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCameraCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beChangePosTransformInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beChangePosTransformInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCopyModelCtrl2__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCopyTransform__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCountry__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriAcxData__vfunc_20(void);
extern "C" int Memory_FreeBuffer(...);
extern "C" int Gap__Core__igObject__userDestruct(...);
extern "C" igMetaObject *Gap__Bec__beCriSndf__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriAudio__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriFxXbData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriFxInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriHandle__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriHandleList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriHandleList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beCriSfpData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beCriVolume__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDBManagerInfo__vfunc_20(void);
extern "C" int igProperty_FindByName(void *, void *, const char *);
extern "C" igMetaObject *Gap__Bec__beDataBase__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataBaseList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataBaseList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beDataObjInt__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjIntList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjBool__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjBoolList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjString__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjStringList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjObjectList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjFloatList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjListList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDataObjListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beDemoKeepMes__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDemoKeepMesList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDemoKeepMesList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beDemoManagerWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDemoManagerWorkList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beDemoManagerWorkList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beFileChkObj__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFile__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFileListInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFontGeomAttrPair__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFontGeomAttrPairList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFontGeomAttrPairList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beFontImage__vfunc_20(void);
extern "C" int Gap__Gui__igFont__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFontImageList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFontImageList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beUnicodeObjList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beUnicodeObjList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beFontInfoData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beFontInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterItemDataOne__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterItemDataOneList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterItemDataOneList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterItemData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterItemDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterItemDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterPlayerData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterPlayerDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterPlayerDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGeneraterInfoWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGroupKeep__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGroupKeepList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beGroupKeepList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beHitLandDelivInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beHitLandDelivInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beHitLandResultData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beHitLandResultDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beHitLandResultDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beHitLandModelTraversal__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beHitLandModelInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beHitLandModelInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLOA__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLayerGroup__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLayerGroupList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLayerGroupList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beLayerInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLayerInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLightCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__igLightSetList__vfunc_20(void);
extern "C" int Gap__Bec__igLightSetList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beLuaDataObject__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLuaDataObjectist__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLuaDataObjectist__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beLuaData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLuaDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLuaDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beLuaInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlSearch__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlSearchList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlSearchList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMatCtrlInfoWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerArgData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerArgDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerArgDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beMessengerDelay__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerDelayList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerDelayList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beMessengerGroup__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerGroupList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerGroupList__vfunc_22(void);
extern "C" igMetaObject *beMessengerWork_GetMetaObject_Virtual(void);
extern "C" igMetaObject *Gap__Bec__beMessengerWorkList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMessengerWorkList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beMeterCtrlOneData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMeterCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMeterCtrlInfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMeterCtrlInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beMeterCtrlNode__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlLUACALL__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlLABEL__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlLABELCTRL__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlACTION__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlJUMP__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlCTRL__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMSGBOX__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMOVE__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMOVEEX__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMOVERL__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlPDMOVE__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlWCHECK__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlAIMAP__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMUTEKI__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlHITBOX__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlAIData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlAIDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlAIDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlAIMap__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlAIMapList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlAIMapList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoDataAIM__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoDataAIH__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoDataHit__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoDataSeq__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoDataTrc__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoRamData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMoveObject__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMoveObjectList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlMoveObjectList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoHitBody__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoAI__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoRideOn__vfunc_20(void);
extern "C" void Gap__Bec__beModelCtrlInfoRideOn__vfunc_21(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlInfoWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlNode2__vfunc_20(void);
extern "C" int Gap__Bec__beModelCtrlSubComBase__vfunc_24(void);
extern "C" void Gap__Bec__beModelCtrlSCHitBox__vfunc_23(void);
extern "C" igMetaObject *Gap__Bec__beModelCtrlSubCom__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMovieInfoData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beMovieInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beLoadingNode__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNodeAnim__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNumberCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNumberCtrlInfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNumberCtrlInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beNumVerInsideData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNumVerInsideDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNumVerInsideDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beNumVerData__vfunc_20(void);
extern "C" int Gap__Core__igObject__userConstruct(...);
extern "C" int igMetaObject_CountInstances(...);
extern "C" void *igObject_GetAllocator(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void **FUN_0036fa60(void **arg0, short arg1);
extern "C" igMetaObject *Gap__Bec__beNumVerDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNumVerDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beNumberCtrlInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beNumberCtrlInfoWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beOptInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__bePadDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__bePadDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beParticleCtrl2Info__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beParticleCtrl2InfoWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beParticleCtrl2InfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__bePoint01Info__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beResetNode__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvDeliver__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSaveDataDeliver__vfunc_20(void);
extern "C" void Gap__Bec__beSaveDataDeliver__vfunc_07(void **arg0);
extern "C" igMetaObject *Gap__Bec__beSvSlotXbox__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvSlotGC__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvSlotPS2__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvSlotDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvSlotDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beSvPlatDataGC__vfunc_20(void);
extern "C" void Gap__Bec__beSvPlatDataGC__vfunc_07(void **arg0);
extern "C" igMetaObject *Gap__Bec__beSvPs2McImage128k__vfunc_20(void);
extern "C" int Memory_AllocateDefaultBuffer(...);
extern "C" void Gap__Bec__beSvPs2McImage128k__vfunc_08(void *arg0);
extern "C" igMetaObject *Gap__Bec__beSvPlatDataPS2__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beXboxImage24k__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvPlatDataXbox__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvPlatDataPC__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSvPlatBaseData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSaveUtilInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSaveUtilInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSeData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSeDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSeDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beSeInfoData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSeInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSelectCtrlInfoWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSelectCtrlInfoRamData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSelectCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beShadow01Info__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beShadow01InfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beShadow01InfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__bePlaySE__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__bePlaySEList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__bePlaySEList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beSoundData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSoundInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beStaticInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beSwitchCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTextureCtrlWork__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTextureCtrlData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTextureCtrlAttr__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTextureCtrlInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTextureCtrlInfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTextureCtrlInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beTimerData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTimerDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beTimerDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beTransformSync__vfunc_20(void);
extern "C" int igMatrix44f_Copy(...);
extern "C" igMetaObject *Gap__Bec__beUnicode__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWaterPlainInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWaterMoveData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWaterMoveDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWaterMoveDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beWaterMove__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWaterPlainInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__igAppearanceListList__vfunc_20(void);
extern "C" int Gap__Bec__igAppearanceListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beWeaponAttachData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWeaponAttachDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWeaponAttachDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beWeaponSeqData__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWeaponSeqDataList__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWeaponSeqDataList__vfunc_22(void);
extern "C" igMetaObject *Gap__Bec__beWeaponInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beWeaponInfoRam__vfunc_20(void);
extern "C" igMetaObject *Gap__Bec__beBaseInfoRam__vfunc_20(void);
extern "C" void **FUN_00357a90(void **arg0, int arg1);
extern "C" igMetaObject *g_libBecRuntimePlugin_metaObject;
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *FUN_0033cd20(ObjectRefWord *self,int delete_storage);
extern "C" ObjectRefWord *FUN_0033ce20(ObjectRefWord *self,int delete_storage);
struct R { int vt; unsigned int rc; };
extern "C" struct R **FUN_0033cea0(struct R **arg0, short arg1);
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void **FUN_0033d0a0(struct Ref **self, short flag);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
extern "C" O *FUN_0033d1a0(O *arg0, short arg1);
typedef struct S_temp_a0_33d2a0 { char pad4[4]; int f4; } S_temp_a0_33d2a0;
extern "C" ObjectRefWord *FUN_0033d320(ObjectRefWord *self,int delete_storage);
extern "C" ObjectRefWord *FUN_0033d420(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_0033d4a0(struct R **arg0, short arg1);
extern "C" ObjectRefWord *FUN_0033d520(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_0033d6a0(struct Ref **self, short flag);
extern "C" O *FUN_0033d7a0(O *arg0, short arg1);
extern "C" ObjectRefWord *FUN_0033d820(ObjectRefWord *self,int delete_storage);
typedef struct S_temp_a0_33d8a0 { char pad4[4]; int f4; } S_temp_a0_33d8a0;
extern "C" ObjectRefWord *FUN_0033d920(ObjectRefWord *self,int delete_storage);
extern "C" ObjectRefWord *FUN_0033da20(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_0033daa0(struct R **arg0, short arg1);
extern "C" ObjectRefWord *FUN_0033db20(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_0033dca0(struct Ref **self, short flag);
extern "C" O *FUN_0033dda0(O *arg0, short arg1);
typedef struct S_temp_a0_33de20 { char pad4[4]; int f4; } S_temp_a0_33de20;
typedef struct S_temp_a0_33dea0 { char pad4[4]; int f4; } S_temp_a0_33dea0;
extern "C" ObjectRefWord *FUN_0033df20(ObjectRefWord *self,int delete_storage);
extern "C" ObjectRefWord *FUN_0033e020(ObjectRefWord *self,int delete_storage);
extern "C" int DAT_005338a0[4];
struct igMetaObject_33e370;
extern "C" igMetaObject_33e370 *igInsightPlugin_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beWeaponInfoRam_metaObject;
struct G { int pad[9]; int f; };
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[48]; };
extern "C" int DAT_00539e30[4];
extern "C" int DAT_00539e90[4];
extern "C" void * g_objectSystem[4];
typedef struct { int vt; char p[36]; char *m; } S;
extern "C" void *FUN_0033e920(S *arg0, long long arg1);
extern "C" ObjectRefWord *ObjectRef_Destruct_0033e9c0(ObjectRefWord *self,int delete_storage);
struct igMetaObject_33ea60;
extern "C" igMetaObject_33ea60 * beBaseInfoRam_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beWeaponInfo_metaObject;
struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; };
extern "C" int DAT_00539d50[4];
extern "C" igObject **FUN_0033ec00(igObject **arg0, short arg1);
extern "C" int g_igNamedObject_vtable[4];
extern "C" int DAT_0052fde0[4];
extern "C" int DAT_00539dc0[4];
struct R_33ec80 { int w0; int rc; };
struct S_33ec80 {
    void *f0;
    char pad[4];
    int *f8;
    char pad2[8];
    struct R_33ec80 *f20;
    struct R_33ec80 *f24;
};
extern "C" void *FUN_0033ec80(struct S_33ec80 *arg0, short arg1);
struct T { int w0; int refs; };
extern "C" struct T **FUN_0033edb0(struct T **arg0, short arg1);
struct igMetaObject_33ee50;
extern "C" igMetaObject_33ee50 * beBaseInfo_GetPublishedMetaObject(...);
extern "C" int kIGMemoryPoolHandleMetaData[4];
extern "C" igMetaObject *g_beWeaponSeqDataList_metaObject;
union U_33f080 { int vt; char b[32]; };
extern "C" int DAT_00539ce0[4];
struct igMetaObject_33f0e0;
extern "C" igMetaObject_33f0e0 * igObjectList_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beWeaponSeqData_metaObject;
struct T_33f1c0 { int word0; int references; };
extern "C" int DAT_00539c80[4];
struct Obj_33f1c0 {
    int *vt; int w0; int *r1; int *r2;
    inline void rel1() {
        int **self = &r1;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    inline void rel2() {
        int **self = &r2;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
};
struct igMetaObject_33f2b0;
extern "C" igMetaObject_33f2b0 * igNamedObject_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beWeapon_metaObject;
union U_33f4f0 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int DAT_0053b630[4];
extern "C" int DAT_0052cf80[4];
extern "C" int DAT_0053a0d0[4];
typedef struct R_33f5e0 { int w0; int refs; } R_33f5e0;
typedef struct O_33f5e0 { int *vt; int f4; int *str; int f12; int f16; int f20; R_33f5e0 *ref; } O_33f5e0;
extern "C" O_33f5e0 *FUN_0033f5e0(O_33f5e0 *arg0, short arg1);
struct igMetaObject_33f770;
extern "C" igMetaObject_33f770 * beBaseInfoManager_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beWeaponAttachDataList_metaObject;
extern "C" igMetaObject *FUN_0033f940(void);
extern "C" int DAT_00539c10[4];
extern "C" igMetaObject *g_beWeaponAttachData_metaObject;
extern "C" igMetaObject *FUN_0033fac0(void);
struct T_33fb10 { int word0; int references; };
extern "C" int DAT_00539bb0[4];
struct Obj_33fb10 {
    int *vt; char p4[4]; T_33fb10 *m8; T_33fb10 *m12; 
    inline void rel8() {
        T_33fb10 **self = &m8;
        if (self) {
            T_33fb10 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel12() {
        T_33fb10 **self = &m12;
        if (self) {
            T_33fb10 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
struct igMetaObject_33fc10;
extern "C" igMetaObject_33fc10 * igObject_GetMetaObject_ParentAccessor(...);
extern "C" igMetaObject *g_igAppearanceListList_metaObject;
extern "C" igMetaObject *FUN_0033fdc0(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_33fe10;
extern "C" int DAT_00539b40[4];
extern "C" igMetaObject *FUN_0033ff50(void);
struct Obj_33ffa0 { int *vt; char pad[28]; };
extern "C" int DAT_00539ad0[4];
extern "C" igMetaObject *g_beWaterPlainInfoRam_metaObject;
struct Obj_3400e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; int w28; int w29; int w30; int w31; int w32; int w33; int w34; int w35; int w36; int w37; int w38; int w39; int w40; int w41; int w42; int w43; int w44; int w45; int w46; int w47; };
extern "C" int DAT_00539a70[4];
extern "C" void **FUN_003401c0(struct Ref **self, short flag);
extern "C" igMetaObject *g_beWaterMove_metaObject;
struct W { int *vt; int f[11]; };
extern "C" int DAT_00539a10[4];
extern "C" igMetaObject *g_beWaterMoveDataList_metaObject;
struct Obj_3407c0 { int *vt; char pad[28]; };
extern "C" int DAT_005399a0[4];
extern "C" igMetaObject *g_beWaterMoveData_metaObject;
union U_340900 { int vt; char b[32]; };
extern "C" int DAT_00539940[4];
extern "C" igMetaObject *g_beWaterPlainInfo_metaObject;
struct W_340b40 { int *vt; int f[7]; };
extern "C" int DAT_005398d0[4];
extern "C" igMetaObject *g_beWaterPlain_metaObject;
union U_340da0 { int vt; char b[32]; };
extern "C" int DAT_0053b590[4];
extern "C" igMetaObject *g_beUnicode_metaObject;
union U_340f80 { int vt; int w[2]; void *p[2]; char b[8]; };
extern "C" int DAT_00539870[4];
extern "C" igMetaObject *g_beTransformSync_metaObject;
extern "C" int DAT_005284f0[4];
extern "C" int DAT_005397d0[4];
/* igObject, constructed by igObject_InitHeader. */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f, constructed by igMatrix44f_SetIdentity. */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _syncTransformList (igObjectRefMetaField). */
struct SyncTransformListField { int *p; SyncTransformListField() { p = 0; } ~SyncTransformListField(); };
/* Stores a derived vtable before the class's first member constructor runs. */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct TransformSyncVtable { TransformSyncVtable(int **slot) { *slot = DAT_005397d0; } };
struct igNodeView : igObjectView {
    int name, bound, parentList, flags, handle, childList;
    igNodeView() { name = 0; bound = 0; parentList = 0; childList = 0; }
    ~igNodeView();
};
struct igTransformView : igNodeView, igTransformVtable {
    igMatrix44fView m;                      /* +32 _m */
    int target, mvm, transformInput;        /* +96 */
    igTransformView() : igTransformVtable(&vtable) { mvm = 0; transformInput = 0; }
    ~igTransformView();
};
struct TransformSyncView : igTransformView, TransformSyncVtable {
    SyncTransformListField syncTransformList;         /* +108 _syncTransformList */
    TransformSyncView() : TransformSyncVtable(&vtable) { }
    ~TransformSyncView() { vtable = DAT_005397d0; }
};
extern "C" O *FUN_00341160(O *arg0, short arg1);
struct igMetaObject_341200;
extern "C" igMetaObject_341200 * igTransform_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beTimer_metaObject;
extern "C" int DAT_0053b930[4];
struct igMetaObject_341520;
extern "C" igMetaObject_341520 * igInfoManager_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beTimerDataList_metaObject;
struct Obj_341750 { int *vt; char pad[28]; };
extern "C" int DAT_00539760[4];
extern "C" igMetaObject *g_beTimerData_metaObject;
extern "C" igMetaObject *FUN_00341840(void);
extern "C" int DAT_00539700[4];
extern "C" igMetaObject *g_beTextureCtrlInfoList_metaObject;
extern "C" igMetaObject *FUN_00341aa0(void);
struct Obj_341af0 { int *vt; char pad[28]; };
extern "C" int DAT_00539690[4];
extern "C" igMetaObject *g_beTextureCtrlInfo_metaObject;
extern "C" igMetaObject *FUN_00341be0(void);
extern "C" int DAT_00539620[4];
extern "C" igMetaObject *g_beTextureCtrlAttr_metaObject;
extern "C" igMetaObject *FUN_00341e10(void);
union U_341e60 { int vt; char b[16]; };
extern "C" int DAT_005395c0[4];
extern "C" igMetaObject *g_beTextureCtrlData_metaObject;
extern "C" int DAT_00539560[4];
extern "C" igMetaObject *g_beTextureCtrl_metaObject;
typedef struct { int *vt; int w[8]; int s; } Obj_3423f0;
extern "C" int DAT_0053c300[4];
typedef struct S_temp_a0_342460 { char pad4[4]; int f4; } S_temp_a0_342460;
extern "C" igMetaObject *g_beTextureCtrlWork_metaObject;
union U_342710 { int vt; char b[16]; };
extern "C" int DAT_00539500[4];
extern "C" igMetaObject *g_beTargetObj_metaObject;
union U_342a50 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int DAT_0053ba50[4];
extern "C" igMetaObject *g_beSystem_metaObject;
struct Obj_342d80 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" int DAT_0053b510[4];
typedef struct S_temp_a0_342eb0 { char pad4[4]; int f4; } S_temp_a0_342eb0;
extern "C" igMetaObject *g_beSwitchCtrlInfo_metaObject;
struct Obj_3431e0 { int *vt; int w[7]; };
extern "C" int DAT_00539490[4];
extern "C" ObjectRefWord *FUN_00343260(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beSwitchCtrl_metaObject;
union U_343570 { int vt; char b[32]; };
extern "C" int DAT_0053b470[4];
extern "C" igMetaObject *g_beStaticInfoCtl_metaObject;
struct Obj_343840 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_0053b9b0[4];
extern "C" igMetaObject *g_beStaticInfo_metaObject;
union U_343a60 { int vt; char b[32]; };
extern "C" int DAT_00539420[4];
extern "C" igMetaObject *g_beBinDataObject_metaObject;
struct igMetaObject_343bf0;
extern "C" igMetaObject_343bf0 * beBaseInfoData_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beSoundInfo_metaObject;
extern "C" igMetaObject *FUN_00343d20(void);
extern "C" int DAT_005393b0[4];
extern "C" igMetaObject *g_beSoundData_metaObject;
extern "C" igMetaObject *FUN_00343f50(void);
union U_343fa0 { int vt; int w[5]; char b[20]; };
extern "C" int DAT_005392f0[4];
extern "C" int DAT_00539350[4];
struct W_344030 { int *vt; int pad; int *name; };
extern "C" struct W_344030 *FUN_00344030(struct W_344030 *arg0, short arg1);
extern "C" igMetaObject *g_beSound_metaObject;
extern "C" igMetaObject *FUN_00344340(void);
extern "C" int DAT_0053b3d0[4];
extern "C" igMetaObject *g_bePlaySEList_metaObject;
extern "C" igMetaObject *FUN_00344680(void);
struct Obj_3446d0 { int *vt; char pad[28]; };
extern "C" int DAT_00539280[4];
extern "C" igMetaObject *g_bePlaySE_metaObject;
extern "C" int DAT_00539220[4];
extern "C" igMetaObject *g_beShadow01InfoList_metaObject;
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_344a50;
extern "C" int DAT_005391b0[4];
extern "C" igMetaObject *g_beShadow01Info_metaObject;
extern "C" int DAT_00539140[4];
extern "C" ObjectRefWord *FUN_00344c40(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beShadow01_metaObject;
extern "C" int DAT_0053b330[4];
extern "C" struct R **FUN_00344f90(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beSelectCtrlInfo_metaObject;
struct F { int *vt; int w[7]; };
extern "C" int DAT_005390d0[4];
extern "C" igMetaObject *g_beSelectCtrlInfoRamData_metaObject;
struct T_345330 { int word0; int references; };
extern "C" int DAT_00539070[4];
struct Obj_345330 {
    int *vt; int w0; int *r1; int w2; int w3; int w4; int w5; T_345330 *r6;
    inline void rel1() {
        int **self = &r1;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    inline void rel6() {
        T_345330 **self = &r6;
        if (self) {
            T_345330 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" ObjectRefWord *FUN_00345410(ObjectRefWord *self,int delete_storage);
struct T_345550 { int word0; int references; int pad[5]; int f28; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" igMetaObject *g_beSelectCtrlInfoWork_metaObject;
union U_345760 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int DAT_00539010[4];
extern "C" igMetaObject *g_beSelectCtrl_metaObject;
extern "C" int DAT_0053b290[4];
extern "C" igMetaObject *g_beSeInfo_metaObject;
struct W_345d80 { int *vt; int w[7]; };
extern "C" int DAT_00538fa0[4];
extern "C" igMetaObject *g_beSeInfoData_metaObject;
struct T_345ef0 { int word0; int references; };
extern "C" int DAT_00538f40[4];
struct Obj_345ef0 {
    int *vt; char p4[4]; char *m8; char p12[4]; T_345ef0 *m16; char tail[12]; 
    inline void rel8() {
        char **self = &m8;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void rel16() {
        T_345ef0 **self = &m16;
        if (self) {
            T_345ef0 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beSeDataList_metaObject;
extern "C" igMetaObject *FUN_00346170(void);
struct Obj_3461c0 { int *vt; char pad[28]; };
extern "C" int DAT_00538ed0[4];
extern "C" igMetaObject *g_beSeData_metaObject;
extern "C" igMetaObject *FUN_003462b0(void);
extern "C" int DAT_00538e70[4];
/* matching construct: the retail unit inlines the release of each string handle (header at -8/-4 of the string) */
struct SeDataLocal : beSeData {
    inline void relSound() {
        char **self = (char **)&_sound;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void relName() {
        char **self = (char **)&_name;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" igMetaObject *g_beSeCtl_metaObject;
extern "C" igMetaObject *FUN_00346580(void);
union U_3465d0 { int vt; int w[4]; void *p[4]; char b[48]; };
extern "C" int DAT_0053b1f0[4];
extern "C" igMetaObject *g_beSaveUtilInfoRam_metaObject;
extern "C" igMetaObject *FUN_00346810(void);
struct Obj_346860 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; char *w10; int w11; char *w12; int w13; int w14; int w15; };
extern "C" int DAT_00538e10[4];
extern "C" igMetaObject *g_beSaveUtilInfo_metaObject;
extern "C" int DAT_00538da0[4];
struct Obj_346b00 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" igMetaObject *g_beSaveUtil_metaObject;
struct Obj_346d60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_0053c140[4];
extern "C" igMetaObject *g_beSvPlatDataPC_metaObject;
union U_3470b0 { int vt; char b[32]; };
extern "C" int DAT_00538ce0[4];
extern "C" int DAT_00538d40[4];
struct Q { char pad4[4]; int f4; };
struct O_347150 { int *vt; int p4; int p8; Q *m; };
extern "C" O_347150 *FUN_00347150(O_347150 *arg0, short arg1);
struct igMetaObject_347210;
extern "C" igMetaObject_347210 * beSvPlatBaseData_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beSvPlatDataXbox_metaObject;
extern "C" int DAT_00538c80[4];
struct T_3474b0 { int w0; int refs; char pad[20]; int *f1c; };
struct F_3474b0 { char pad[52]; unsigned char b52; char pad2[3]; int f56; };
struct G_3474b0 { char pad[52]; int w52; };
extern "C" igMetaObject *g_beXboxImage24k_metaObject;
struct Obj_3476a0 { int *vt; char pad[12]; };
extern "C" int DAT_00538c20[4];
extern "C" igMetaObject *g_beSvPlatDataPS2_metaObject;
union U_347870 { int vt; char b[224]; };
extern "C" int DAT_00538bc0[4];
extern "C" igMetaObject *g_beSvPs2McImage128k_metaObject;
struct Obj_347ca0 { int *vt; char pad[8]; };
extern "C" int DAT_00538b60[4];
extern "C" igMetaObject *g_beSvPlatDataGC_metaObject;
union U_347e70 { int vt; char b[144]; };
extern "C" int DAT_00538b00[4];
struct T_348000 { int w0; int refs; char pad[20]; int *f1c; };
struct G_348000 { char pad[52]; int w52; };
struct H { char pad[60]; int f60; };
extern "C" igMetaObject *g_beSvConnectCheck_metaObject;
union U_348250 { int vt; char b[144]; };
extern "C" int DAT_0053bc10[4];
extern "C" int DAT_0053c070[4];
struct R_348390 { int w0; int rc; };
struct S_348390 {
    void *f0;
    char pad[44];
    struct R_348390 *f48;
    struct R_348390 *f52;
    struct R_348390 *f56;
};
extern "C" void *FUN_00348390(struct S_348390 *arg0, short arg1);
extern "C" void **FUN_003484b0(struct Ref **self, short flag);
struct igMetaObject_348550;
extern "C" igMetaObject_348550 * beSaveApi_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beSaveApi_metaObject;
extern "C" igMetaObject *g_beSvEndApi_metaObject;
struct T_348680 { int word0; int references; };
extern "C" int DAT_0053bc80[4];
struct Obj_348680 {
    int *vt; int w0[11]; T_348680 *r1; T_348680 *r2; T_348680 *r3; int pad;
    inline void rel(T_348680 **self) {
        if (self) {
            T_348680 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
struct SR { char pad4[4]; int f4; };
extern "C" igMetaObject *g_beSvStartApi_metaObject;
extern "C" igMetaObject *FUN_00348970(void);
union U_3489c0 { int vt; char b[64]; };
extern "C" int DAT_0053bcf0[4];
struct T_348bb0 { int word0; int references; int pad[5]; int f28; };
extern "C" igMetaObject *g_beSvGetFreeSizeApi_metaObject;
extern "C" igMetaObject *FUN_00348cb0(void);
union U_348d00 { int vt; char b[96]; };
extern "C" int DAT_0053bd60[4];
extern "C" igMetaObject *g_beSvWriteMediaApi_metaObject;
extern "C" igMetaObject *FUN_00348fa0(void);
struct Obj_348ff0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int DAT_0053bdd0[4];
extern "C" igMetaObject *g_beSvReadMediaApi_metaObject;
extern "C" igMetaObject *FUN_003492b0(void);
struct Obj_349300 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
extern "C" int DAT_0053be40[4];
extern "C" O *FUN_003493b0(O *arg0, short arg1);
extern "C" igMetaObject *g_beSvUseCheckApi_metaObject;
union U_349680 { int vt; int w[4]; void *p[4]; char b[80]; };
extern "C" int DAT_0053beb0[4];
extern "C" igMetaObject *g_beSvFormatApi_metaObject;
union U_349900 { int vt; char b[56]; };
extern "C" int DAT_0053bf20[4];
extern "C" igMetaObject *g_beSvFileFindApi_metaObject;
union U_349b80 { beSvFileFindApi o; int w[24]; char b[96]; };
extern "C" int DAT_0053bf90[4];
extern "C" igMetaObject *g_beSvFileMakeApi_metaObject;
struct Obj_349e00 { int *vt; int w[263]; };
extern "C" int DAT_0053c000[4];
extern "C" igMetaObject *g_beSvPlatBaseData_metaObject;
struct F_34a2b0 { int *vt; int pad[2]; int *ref; int pad2[4]; };
extern "C" igMetaObject *g_beSvSlotDataList_metaObject;
struct Obj_34a540 { int *vt; char pad[28]; };
extern "C" int DAT_00538a90[4];
extern "C" igMetaObject *g_beSvSlotPS2_metaObject;
struct Obj_34a680 { int *vt; char pad[28]; };
extern "C" int DAT_00538a30[4];
struct igMetaObject_34a6e0;
extern "C" igMetaObject_34a6e0 * beSvSlotData_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beSvSlotGC_metaObject;
struct Obj_34a7d0 { int *vt; char pad[28]; };
extern "C" int DAT_005389d0[4];
extern "C" igMetaObject *g_beSvSlotXbox_metaObject;
union U_34a910 { int vt; char b[64]; };
extern "C" int DAT_00538970[4];
extern "C" igMetaObject *g_beSvSlotData_metaObject;
extern "C" igMetaObject *FUN_0034aae0(void);
extern "C" igMetaObject *g_beSaveMemoryObj_metaObject;
extern "C" igMetaObject *FUN_0034ace0(void);
struct Obj_34ad30 { int *vt; char pad[12]; };
extern "C" int DAT_0053c0e0[4];
extern "C" igMetaObject *g_beSaveDataDeliver_metaObject;
extern "C" igMetaObject *FUN_0034af00(void);
struct Obj_34af50 { int *vt; char pad[12]; };
extern "C" int DAT_00538910[4];
extern "C" igMetaObject *g_beSvDeliver_metaObject;
extern "C" igMetaObject *FUN_0034b120(void);
union U_34b170 { int vt; int w[17]; char b[68]; };
extern "C" int DAT_005388b0[4];
extern "C" igMetaObject *g_beResetNode_metaObject;
struct W_34b4f0 { int *vt; int w[11]; };
extern "C" int DAT_00538810[4];
struct igMetaObject_34b580;
extern "C" igMetaObject_34b580 * igGroup_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_bePoint01Info_metaObject;
extern "C" int DAT_005387a0[4];
extern "C" ObjectRefWord *FUN_0034b790(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_bePoint01_metaObject;
extern "C" int DAT_0053b150[4];
extern "C" igMetaObject *g_beParticleCtrl2InfoRam_metaObject;
struct Obj_34bd10 { int *vt; int w[15]; };
extern "C" int DAT_00538740[4];
typedef struct S_temp_a0_34bdc0 { char pad4[4]; int f4; } S_temp_a0_34bdc0;
extern "C" ObjectRefWord *FUN_0034be40(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beParticleCtrl2InfoWork_metaObject;
union U_34c120 { int vt; char b[32]; };
extern "C" int DAT_005386e0[4];
extern "C" igMetaObject *g_beParticleCtrl2Info_metaObject;
struct Obj_34c3d0 { int *vt; char p4[4]; int f8; char pc[8]; int f14; int f18; int f1c; int f20; char pe[12]; };
extern "C" int DAT_00538670[4];
extern "C" igMetaObject *g_beParticleCtrl2_metaObject;
union U_34c710 { int vt; char b[32]; };
extern "C" int DAT_0053b0b0[4];
extern "C" igMetaObject *g_bePadManager_metaObject;
struct Obj_34c980 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_0053b030[4];
extern "C" ObjectRefWord *FUN_0034ca30(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_0034cab0(struct R **arg0, short arg1);
extern "C" igMetaObject *g_bePadDataList_metaObject;
union U_34cd60 { int vt; char b[32]; };
extern "C" int DAT_00538600[4];
extern "C" igMetaObject *g_bePadData_metaObject;
struct Obj_34cee0 { int *vt; char pad[108]; };
extern "C" int DAT_0053afd0[4];
extern "C" igMetaObject *g_beOptInfo_metaObject;
extern "C" igMetaObject *FUN_0034d080(void);
typedef struct { int *vt; int p4; int f8; int pad[4]; int a; int b; int tail[3]; } Obj_34d0d0;
extern "C" int DAT_00538590[4];
struct igMetaObject_34d180;
extern "C" igMetaObject_34d180 * igInfo_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beNumberCtrlInfoWork_metaObject;
extern "C" igMetaObject *FUN_0034d340(void);
extern "C" int DAT_00538530[4];
extern "C" igMetaObject *g_beNumberCtrlInfoRam_metaObject;
extern "C" igMetaObject *FUN_0034d540(void);
struct W_34d590 { int *vt; int f[19]; };
extern "C" int DAT_005384d0[4];
extern "C" igMetaObject *g_beNumVerDataList_metaObject;
extern "C" igMetaObject *FUN_0034d940(void);
struct Obj_34d990 { int *vt; char pad[28]; };
extern "C" int DAT_00538460[4];
extern "C" igMetaObject *g_beNumVerData_metaObject;
struct Obj_34dad0 { int *vt; char pad[8]; char *m; };
extern "C" int DAT_00538400[4];
extern "C" igMetaObject *g_beNumVerInsideDataList_metaObject;
struct Obj_34dd70 { int *vt; char pad[28]; };
extern "C" int DAT_00538390[4];
extern "C" igMetaObject *g_beNumVerInsideData_metaObject;
struct Obj_34def0 { int *vt; char pad[12]; };
extern "C" int DAT_00538330[4];
extern "C" igMetaObject *g_beNumberCtrlInfoList_metaObject;
struct Obj_34e0a0 { int *vt; char pad[28]; };
extern "C" int DAT_005382c0[4];
extern "C" igMetaObject *g_beNumberCtrlInfo_metaObject;
struct Obj_34e1e0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int DAT_00538250[4];
extern "C" igMetaObject *g_beNumberCtrl_metaObject;
union U_34e440 { int vt; int w[5]; char b[20]; };
extern "C" int DAT_0053b890[4];
extern "C" igMetaObject *g_beLoadingNode_metaObject;
struct Obj_34e620 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; int f30; int f34; int f38; int f3C; int f40; int f44; int f48; int f4C; int f50; int f54; int f58; int f5C; int f60; int f64; int f68; int f6C; int f70; int f74; int f78; int f7C; };
extern "C" int DAT_00538110[4];
extern "C" int DAT_00528dd0[4];
extern "C" int DAT_005381b0[4];
struct igMetaObject_34e730;
extern "C" igMetaObject_34e730 *beNodeAnim_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beNodeAnim_metaObject;
struct Obj_34e8c0 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; int f56; int f60; int f64; int f68; int f72; int f76; int f80; int f84; int f88; int f92; int f96; int f100; int f104; int f108; };
extern "C" igMetaObject *g_beMovieInfo_metaObject;
struct W_34eb60 { int *vt; int w[7]; };
extern "C" int DAT_005380a0[4];
extern "C" igMetaObject *g_beMovieInfoData_metaObject;
struct Obj_34ecd0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; };
extern "C" int DAT_00538040[4];
extern "C" igMetaObject *g_beMovie_metaObject;
extern "C" igMetaObject *FUN_0034efc0(void);
struct Obj_34f010 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_0053bad0[4];
extern "C" igMetaObject *g_beModelCtrlSubCom_metaObject;
extern "C" igMetaObject *FUN_0034f260(void);
extern "C" int DAT_00537fe0[4];
struct Obj_34f2b0 { int *vt; char pad[4]; struct R *p; char pad2[4]; };
extern "C" igMetaObject *g_beModelCtrlSCSound_metaObject;
extern "C" igMetaObject *FUN_0034f4e0(void);
union U_34f530 { int vt; char b[32]; };
extern "C" int DAT_0053ae80[4];
struct igMetaObject_34f5e0;
extern "C" igMetaObject_34f5e0 * beModelCtrlSubComBase_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beModelCtrlSCHitBox_metaObject;
extern "C" igMetaObject *FUN_0034f730(void);
struct Obj_34f780 { int *vt; char pad[60]; };
extern "C" int DAT_0053af60[4];
extern "C" igMetaObject *g_beModelCtrlSCEffect_metaObject;
extern "C" int DAT_0053aef0[4];
extern "C" igMetaObject *g_beModelCtrlSubComBase_metaObject;
extern "C" igMetaObject *g_beModelCtrlNode2_metaObject;
extern "C" int DAT_00537f40[4];
/* _overrideAttrList (igObjectRefMetaField). */
struct OverrideAttrListField { int *p; OverrideAttrListField() { p = 0; } ~OverrideAttrListField(); };
struct ModelCtrlNode2Vtable { ModelCtrlNode2Vtable(int **slot) { *slot = DAT_00537f40; } };
struct ModelCtrlNode2View : igTransformView, ModelCtrlNode2Vtable {
    int pad108;
    long long time;                         /* +112 _time */
    float timeScale;                        /* +120 _timeScale */
    long long timeBias;                     /* +128 _timeBias */
    OverrideAttrListField overrideAttrList;  /* +136 _overrideAttrList */
    ModelCtrlNode2View() : ModelCtrlNode2Vtable(&vtable) { }
    ~ModelCtrlNode2View() { vtable = DAT_00537f40; }
};
extern "C" igMetaObject *g_beModelCtrlInfoWork_metaObject;
extern "C" int g_beModelCtrlInfoWork_vtable[4];
extern "C" void *FUN_00350410(beNDMWMdlPlayer2InfoWork *arg0, long long arg1);
extern "C" void **FUN_00350b90(struct Ref **self, short flag);
extern "C" O *FUN_00350c90(O *arg0, short arg1);
extern "C" ObjectRefWord *FUN_00350d10(ObjectRefWord *self,int delete_storage);
typedef struct S_temp_a0_350d90 { char pad4[4]; int f4; } S_temp_a0_350d90;
extern "C" ObjectRefWord *FUN_00350e10(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beModelCtrlInfoRideOn4_metaObject;
extern "C" int DAT_00537e80[4];
extern "C" int DAT_0053ac90[4];
struct ModelNameField {
    const char *p;
    ModelNameField() { p = 0; }
    ~ModelNameField() {
        const char *s = p;
        if (s) {
            int *header = (int *)s - 2;
            int count = ((int *)s)[-1] - 1;
            ((int *)s)[-1] = count;
            if (count == 0) StringChunk_ReleaseHeader(*header, header);
        }
    }
};
struct ModelNodeField {
    igObject *p;
    ModelNodeField() { p = 0; }
    ~ModelNodeField() {
        igObject *o = p;
        if (o) {
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
    }
};
struct RideOnVtable { RideOnVtable(int **slot) { *slot = DAT_00537e80; } };
struct RideOnView : igObjectView, RideOnVtable {
    ModelNameField modelName;               /* +8 _modelName */
    int modelRamNo;                         /* +12 */
    ModelNodeField modelNode;               /* +16 _modelNode */
    igMatrix44fView oldMatrix;              /* +20 _oldMatrix */
    RideOnView() : RideOnVtable(&vtable) { }
    ~RideOnView() { vtable = DAT_00537e80; }
};
struct RideOn4Vtable { RideOn4Vtable(int **slot) { *slot = DAT_0053ac90; } };
struct RideOn4View : RideOnView, RideOn4Vtable {
    float oldPlayerPos[3];                  /* +84 */
    float vector[3];                        /* +96 */
    float scalar, limitter;                 /* +108 */
    int isFirst;                            /* +116 */
    RideOn4View() : RideOn4Vtable(&vtable) { }
    ~RideOn4View() { vtable = DAT_0053ac90; }
};
struct igMetaObject_3515d0;
extern "C" igMetaObject_3515d0 * beModelCtrlInfoRideOn_GetPublishedMetaObject(...);
struct T_351670 { int w0; int refs; char pad[20]; int *f1c; };
extern "C" igMetaObject *g_beModelCtrlInfoRideOn3_metaObject;
extern "C" int DAT_0053acf0[4];
struct RideOn3Vtable { RideOn3Vtable(int **slot) { *slot = DAT_0053acf0; } };
struct RideOn3View : RideOnView, RideOn3Vtable {
    float worldPosition[3];                 /* +84 */
    float minSpeed, maxSpeed;               /* +96 */
    float minKyori, maxKyori;               /* +104 */
    RideOn3View() : RideOn3Vtable(&vtable) { }
    ~RideOn3View() { vtable = DAT_0053acf0; }
};
struct T_3519c0 { int w0; int refs; char pad[20]; int *f1c; };
extern "C" igMetaObject *g_beModelCtrlInfoRideOn2_metaObject;
extern "C" int DAT_0053ad50[4];
struct RideOn2Vtable { RideOn2Vtable(int **slot) { *slot = DAT_0053ad50; } };
struct RideOn2View : RideOnView, RideOn2Vtable {
    float vector[3];                        /* +84 */
    RideOn2View() : RideOn2Vtable(&vtable) { }
    ~RideOn2View() { vtable = DAT_0053ad50; }
};
struct T_351d10 { int word0; int references; int pad[5]; int f28; };
extern "C" igMetaObject *g_beModelCtrlInfoRideOn_metaObject;
extern "C" igMetaObject *g_beModelCtrlInfoAI_metaObject;
struct F_352220 { int *vt; int pad[1]; int *ref; int pad2[9]; };
extern "C" int DAT_00537e20[4];
extern "C" igMetaObject *g_beModelCtrlInfoHitBody_metaObject;
extern "C" int DAT_00537dc0[4];
extern "C" igMetaObject *g_beModelCtrlMoveObjectList_metaObject;
extern "C" igMetaObject *FUN_00352800(void);
struct Obj_352850 { int *vt; char pad[28]; };
extern "C" int DAT_00537d50[4];
extern "C" igMetaObject *g_beModelCtrlMoveObject_metaObject;
extern "C" igMetaObject *FUN_00352980(void);
struct Obj_3529d0 { int *vt; char pad[44]; };
extern "C" int DAT_00537cf0[4];
extern "C" igMetaObject *g_beModelCtrlInfoList_metaObject;
extern "C" igMetaObject *FUN_00352b90(void);
struct Obj_352be0 { int *vt; char pad[28]; };
extern "C" int DAT_00537c80[4];
extern "C" igMetaObject *g_beModelCtrlInfo_metaObject;
extern "C" igMetaObject *FUN_00352cd0(void);
union U_352d20 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int DAT_00537c10[4];
extern "C" igMetaObject *g_beModelCtrlInfoRamData_metaObject;
struct Obj_352f30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_00537bb0[4];
extern "C" ObjectRefWord *FUN_00352fc0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beModelCtrlInfoDataTrc_metaObject;
union U_3532e0 { int vt; char b[32]; };
extern "C" int DAT_00537b50[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataSeq_metaObject;
union U_353600 { int vt; char b[32]; };
extern "C" int DAT_00537af0[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataHit_metaObject;
union U_353920 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int DAT_00537a90[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataAIH_metaObject;
extern "C" int DAT_00537a30[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataAIM_metaObject;
union U_353ee0 { int vt; char b[32]; };
extern "C" int DAT_005379d0[4];
struct T_temp_v0_2 { int word0; int references; char pad8[20]; int f28; };
extern "C" igMetaObject *g_beModelCtrlAIMapList_metaObject;
struct Obj_354250 { int *vt; char pad[28]; };
extern "C" int DAT_00537960[4];
extern "C" igMetaObject *g_beModelCtrlAIMap_metaObject;
union U_354390 { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" int DAT_00537900[4];
extern "C" struct R **FUN_00354490(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beModelCtrlAIDataList_metaObject;
union U_354770 { int vt; char b[32]; };
extern "C" int DAT_00537890[4];
extern "C" igMetaObject *g_beModelCtrlAIData_metaObject;
union U_3548b0 { int vt; char b[32]; };
extern "C" int DAT_00537830[4];
extern "C" igMetaObject *g_beModelCtrlHITBOX_metaObject;
extern "C" igMetaObject *FUN_00354aa0(void);
extern "C" int DAT_005377d0[4];
extern "C" igMetaObject *g_beModelCtrlMUTEKI_metaObject;
extern "C" igMetaObject *FUN_00354ca0(void);
union U_354cf0 { int vt; char b[16]; };
extern "C" int DAT_00537770[4];
extern "C" igMetaObject *g_beModelCtrlAIMAP_metaObject;
extern "C" igMetaObject *FUN_00354ea0(void);
union U_354ef0 { int vt; char b[16]; };
extern "C" int DAT_00537710[4];
extern "C" igMetaObject *g_beModelCtrlWCHECK_metaObject;
extern "C" igMetaObject *FUN_00355030(void);
union U_355080 { int vt; char b[16]; };
extern "C" int DAT_005376b0[4];
extern "C" igMetaObject *g_beModelCtrlPDMOVE_metaObject;
union U_355210 { int vt; char b[32]; };
extern "C" int DAT_00537650[4];
extern "C" igMetaObject *g_beModelCtrlMOVERL_metaObject;
union U_355410 { int vt; char b[32]; };
extern "C" int DAT_005375f0[4];
extern "C" igMetaObject *g_beModelCtrlMOVEEX_metaObject;
extern "C" int DAT_00537590[4];
extern "C" igMetaObject *g_beModelCtrlMOVE_metaObject;
union U_355890 { int vt; char b[32]; };
extern "C" int DAT_00537530[4];
extern "C" igMetaObject *g_beModelCtrlMSGBOX_metaObject;
union U_355a90 { int vt; int w[4]; char b[16]; };
extern "C" int DAT_005374d0[4];
extern "C" igMetaObject *g_beModelCtrlCTRL_metaObject;
union U_355c20 { int vt; char b[16]; };
extern "C" int DAT_00537470[4];
extern "C" igMetaObject *g_beModelCtrlJUMP_metaObject;
union U_355db0 { int vt; char b[16]; };
extern "C" int DAT_00537410[4];
extern "C" igMetaObject *g_beModelCtrlACTION_metaObject;
union U_355f40 { int vt; char b[16]; };
extern "C" int DAT_005373b0[4];
extern "C" igMetaObject *g_beModelCtrlLABELCTRL_metaObject;
union U_3560d0 { int vt; char b[16]; };
extern "C" int DAT_00537350[4];
extern "C" igMetaObject *g_beModelCtrlLABEL_metaObject;
union U_356310 { int vt; char b[16]; };
extern "C" int DAT_005372f0[4];
extern "C" igMetaObject *g_beModelCtrlLUACALL_metaObject;
extern "C" igMetaObject *FUN_00356450(void);
struct T_3564a0 { int word0; int references; };
extern "C" int DAT_00537290[4];
struct Obj_3564a0 {
    int *vt; char p4[4]; char *m8; char *m12; 
    inline void rel8() {
        char **self = &m8;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void rel12() {
        char **self = &m12;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" igMetaObject *g_beModelCtrlDataList_metaObject;
extern "C" igMetaObject *FUN_00356690(void);
extern "C" int DAT_00537220[4];
extern "C" igMetaObject *g_beModelCtrlData_metaObject;
extern "C" igMetaObject *FUN_00356820(void);
struct T_356870 { int word0; int references; };
extern "C" int DAT_005371c0[4];
struct Obj_356870 {
    int *vt; int w0[1]; char *s; T_356870 *ref;
    inline void releaseRef() {
        T_356870 **self = &ref;
        if (self) {
            T_356870 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void releaseStr() {
        char **self = &s;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" igMetaObject *g_beModelCtrl_metaObject;
extern "C" igMetaObject *FUN_00356b10(void);
extern "C" igMetaObject *g_beMeterCtrlNode_metaObject;
struct Obj_356d60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int DAT_00537120[4];
extern "C" igMetaObject *g_beMeterCtrlInfoList_metaObject;
extern "C" int DAT_005370b0[4];
extern "C" igMetaObject *g_beMeterCtrlInfo_metaObject;
typedef struct { int *vt; int w[6]; int s; } Obj_3570f0;
extern "C" int DAT_00537040[4];
extern "C" igMetaObject *g_beMeterCtrlOneData_metaObject;
struct Obj_357320 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int DAT_00536fe0[4];
extern "C" igMetaObject *g_beMeterCtrl_metaObject;
struct T_357740 { int word0; int references; };
extern "C" int DAT_0053abf0[4];
struct Obj_357740 {
    int *vt; int w0; int *r1; int w1[3]; T_357740 *r2; int pad;
    inline void rel1() {
        int **self = &r1;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    inline void rel2() {
        T_357740 **self = &r2;
        if (self) {
            T_357740 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beMessenger_metaObject;
union U_3579b0 { int vt; char b[64]; };
extern "C" int DAT_0053ab70[4];
extern "C" void *g_stringPool[4];
/* The insight object's clock (+80, 64 bits). */
struct Insight {
    static long long Get(igInsightCore *i) { return i->_worldTime; }
};
/* Loop helpers: the list base and the element access are separate calls. */
struct ListOps {
    static igObject **Data(igObjectList *l) { return (igObject **)l->_data; }
    static igObject *At(igObject **b, int k) { return b[k]; }
};
/* Owning reference to the delay record. */
struct RowRef {
    igObject *p;
    RowRef(igObject *o) { p = o; if (p) ++p->_refCount; }
    ~RowRef() { igObject *o = p; RELEASE_OBJ(o) }
};
/* Owning reference to the old argument object. */
struct SavedRef {
    igObject *p;
    SavedRef(igObject *o) { p = o; }
    void operator=(igObject *in) {
        igObject *old;
        if (in) ++in->_refCount;
        old = p;
        RELEASE_OBJ(old)
        p = in;
    }
    ~SavedRef() { igObject *o = p; RELEASE_OBJ(o) }
};
struct RowOps {
    static void SetArg(beMessengerDelay *r, igObject *in) {
        igObject *old;
        if (in) ++in->_refCount;
        old = (igObject *)r->_argData;
        RELEASE_OBJ(old)
        r->_argData = (int)in;
    }
};
/* Reference stored through a pointer (the messenger's own argument slot) and the temporary handed
 * to the list insert. Its constructor reads its stored word back through a laundered pointer and
 * fetches the delay-stack handle between that read and the null test. */
struct Ref_357a90 {
    igObject * value;
    Ref_357a90(igObject *p, beMessenger *m, int &out) : value(p) {
        Ref_357a90 *s = (Ref_357a90 *)(int)this;
        igObject *v = s->value;
        out = m->_delayStack;
        if (v) ++v->_refCount;
        Ref_357a90 *r = s;
        (void)r;
    }
    static void release(igObject *o) { RELEASE_OBJ(o) }
    static void assign(igObject **dest, igObject *incoming) {
        igObject *outgoing;
        if (incoming) ++incoming->_refCount;
        outgoing = *dest;
        release(outgoing);
        *dest = incoming;
    }
};
extern "C" void **FUN_00357c10(struct Ref **self, short flag);
extern "C" igMetaObject *g_beMessengerWorkList_metaObject;
struct Obj_357f80 { int *vt; char pad[28]; };
extern "C" int DAT_00536f70[4];
/* Messenger class factories and their lazy-registration wrappers. Each factory makes sure the
 * class is registered, reloads the class handle and creates an instance from the caller's
 * allocator. */

/* Structural ABI view of the static-init callback list the registrars return; never defined here. */
struct StaticInitCallbacks;
extern "C" igMetaObject *g_beMessengerWork_metaObject;
extern "C" int DAT_00536f10[4];
extern "C" igMetaObject *g_beMessengerGroupList_metaObject;
struct Obj_3583f0 { int *vt; char pad[28]; };
extern "C" int DAT_00536ea0[4];
extern "C" igMetaObject *g_beMessengerGroup_metaObject;
struct Obj_358570 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_00536e40[4];
extern "C" igMetaObject *g_beMessengerDelayList_metaObject;
extern "C" igMetaObject *FUN_00358810(void);
struct Obj_358860 { int *vt; char pad[28]; };
extern "C" int DAT_00536dd0[4];
extern "C" igMetaObject *g_beMessengerDelay_metaObject;
extern "C" igMetaObject *FUN_00358990(void);
union U_3589e0 { int vt; int w[12]; char b[48]; };
extern "C" int DAT_00536d70[4];
extern "C" igMetaObject *g_beMessengerArgDataList_metaObject;
extern "C" igMetaObject *FUN_00358c40(void);
struct Obj_358c90 { int *vt; char pad[28]; };
extern "C" int DAT_00536d00[4];
extern "C" igMetaObject *g_beMessengerArgData_metaObject;
extern "C" igMetaObject *FUN_00358e10(void);
struct Obj_358e60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_00536ca0[4];
extern "C" igMetaObject *g_beMemory_metaObject;
extern "C" int DAT_0053c1e0[4];
extern "C" igMetaObject *g_beMatCtrlInfoWork_metaObject;
struct T_359560 { int word0; int references; };
extern "C" int DAT_00536c40[4];
struct Obj_359560 {
    int *vt; char p4[4]; T_359560 *m8; T_359560 *m12; 
    inline void rel8() {
        T_359560 **self = &m8;
        if (self) {
            T_359560 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel12() {
        T_359560 **self = &m12;
        if (self) {
            T_359560 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beMatCtrlInfoRam_metaObject;
struct T_359810 { int word0; int references; };
extern "C" int DAT_00536be0[4];
struct Obj_359810 {
    int *vt; int w0; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; T_359810 *r9; T_359810 *r10;
    inline void rel9() {
        T_359810 **self = &r9;
        if (self) {
            T_359810 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel10() {
        T_359810 **self = &r10;
        if (self) {
            T_359810 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" O *FUN_00359900(O *arg0, short arg1);
extern "C" igMetaObject *g_beMatCtrlInfo_metaObject;
struct Obj_359b20 { int *vt; int w[11]; };
extern "C" int DAT_00536b70[4];
typedef struct S_temp_a0_359c50 { char pad4[4]; int f4; } S_temp_a0_359c50;
extern "C" igMetaObject *g_beMatCtrlSearchList_metaObject;
struct Obj_359f00 { int *vt; char pad[28]; };
extern "C" int DAT_00536b00[4];
extern "C" igMetaObject *g_beMatCtrlSearch_metaObject;
struct Obj_35a090 { int *vt; char pad[20]; char *m; char pad2[4]; };
extern "C" int DAT_00536aa0[4];
extern "C" igMetaObject *g_beMatCtrlDataList_metaObject;
struct Obj_35a340 { int *vt; char pad[28]; };
extern "C" int DAT_00536a30[4];
extern "C" igMetaObject *g_beMatCtrlData_metaObject;
union U_35a480 { int vt; char b[16]; };
extern "C" int DAT_005369d0[4];
extern "C" igMetaObject *g_beMatCtrl_metaObject;
struct Obj_35a7f0 { int *vt; int w[19]; };
extern "C" int DAT_0053aad0[4];
struct F_35a940 { char pad[52]; int f52; int f56; char f60; };
extern "C" igMetaObject *g_beLuaState_metaObject;
struct T_35ab00 { int word0; int references; };
extern "C" int DAT_0053aa60[4];
extern "C" int g_igLuaState_vtable[4];
struct Obj_35ab00 {
    int *vt; int w0; int *r1; int w1; T_35ab00 *r2;
    inline void rel1() {
        int **self = &r1;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    inline void rel2() {
        T_35ab00 **self = &r2;
        if (self) {
            T_35ab00 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
struct igMetaObject_35ac00;
extern "C" igMetaObject_35ac00 *igLuaState_GetPublishedMetaObject(void);
extern "C" int g_igLuaState_metaObject[4];
extern "C" igMetaObject *g_beLuaInfo_metaObject;
extern "C" igMetaObject *FUN_0035ad10(void);
struct Obj_35ad60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_00536960[4];
extern "C" ObjectRefWord *FUN_0035ade0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beLuaDataList_metaObject;
extern "C" igMetaObject *FUN_0035b010(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_35b060;
extern "C" int DAT_005368f0[4];
extern "C" igMetaObject *g_beLuaData_metaObject;
extern "C" igMetaObject *FUN_0035b150(void);
struct Obj_35b1a0 { int *vt; int w1; char *w2; igObject *w3; };
extern "C" int DAT_00536890[4];
extern "C" igMetaObject *g_beLuaDataObjectist_metaObject;
extern "C" igMetaObject *FUN_0035b3d0(void);
struct Obj_35b420 { int *vt; char pad[28]; };
extern "C" int DAT_00536820[4];
extern "C" igMetaObject *g_beLuaDataObject_metaObject;
struct Obj_35b5b0 { int *vt; char pad[12]; };
extern "C" int DAT_005367c0[4];
extern "C" igMetaObject *g_beLua_metaObject;
struct Obj_35b810 { int *vt; int w[7]; };
extern "C" int DAT_0053a9e0[4];
extern "C" ObjectRefWord *FUN_0035b940(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_igLightSetList_metaObject;
struct Obj_35bc10 { int *vt; char pad[28]; };
extern "C" int DAT_00536750[4];
extern "C" igMetaObject *g_beLightCtrlInfo_metaObject;
struct W_35bd50 { int *vt; int f[7]; };
extern "C" int DAT_005366e0[4];
extern "C" struct R **FUN_0035bdd0(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beLightCtrl_metaObject;
union U_35c0f0 { int vt; int w[5]; char b[20]; };
extern "C" int DAT_0053c260[4];
extern "C" igMetaObject *g_beLayerInfoRam_metaObject;
extern "C" int DAT_00536680[4];
extern "C" igMetaObject *g_beLayerInfo_metaObject;
union U_35c470 { int vt; char b[32]; };
extern "C" int DAT_00536610[4];
extern "C" ObjectRefWord *FUN_0035c4f0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beLayerGroupList_metaObject;
struct Obj_35c760 { int *vt; char pad[28]; };
extern "C" int DAT_005365a0[4];
extern "C" igMetaObject *g_beLayerGroup_metaObject;
union U_35c8a0 { int vt; char b[16]; };
extern "C" int DAT_00536540[4];
extern "C" igMetaObject *g_beLayerCtl_metaObject;
extern "C" int DAT_0053a940[4];
extern "C" igMetaObject *g_beLOA_metaObject;
extern "C" igMetaObject *FUN_0035cd40(void);
struct W_35cd90 { int *vt; int f[23]; };
extern "C" int DAT_005364a0[4];
extern "C" igMetaObject *g_beKeyboardReceiver_metaObject;
extern "C" igMetaObject *FUN_0035d0c0(void);
struct W_35d110 { int *vt; int f[3]; };
extern "C" int DAT_0053a8b0[4];
struct igMetaObject_35d1c0;
extern "C" igMetaObject_35d1c0 *igEventReceiver_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beHitLandModelInfoRam_metaObject;
extern "C" igMetaObject *FUN_0035d300(void);
struct T_35d350 { int word0; int references; };
extern "C" int DAT_00536440[4];
struct Obj_35d350 {
    int *vt; int w0[9]; T_35d350 *ref; char pad[4];
    inline void releaseRef() {
        T_35d350 **self = &ref;
        if (self) {
            T_35d350 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beHitLandModelInfo_metaObject;
extern "C" igMetaObject *FUN_0035d4a0(void);
struct Obj_35d4f0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_005363d0[4];
extern "C" igMetaObject *g_beHitLandModel_metaObject;
extern "C" int DAT_0053a810[4];
struct HitLandOrderField { int *p; HitLandOrderField() { p = 0; } ~HitLandOrderField(); };
struct HitTraversalField { int *p; HitTraversalField() { p = 0; } ~HitTraversalField(); };
struct HitLandProbeField { int *p; HitLandProbeField() { p = 0; } ~HitLandProbeField(); };
struct ControllerBaseView : igObjectView {
    int name, insight, system, messenger, infoList;
    unsigned char isUpdateRun;
    ControllerBaseView() { name = 0; infoList = 0; }
    ~ControllerBaseView();
};
struct HitLandModelVtable { HitLandModelVtable(int **slot) { *slot = DAT_0053a810; } };
struct HitLandModelView : ControllerBaseView, HitLandModelVtable {
    HitLandOrderField order;                /* +32 _order */
    HitTraversalField hitTraversal;         /* +36 _hitTraversal */
    HitLandProbeField probe;                /* +40 _probe */
    unsigned char isHitWall;                /* +44 */
    igMatrix44fView mat90;                  /* +48 _mat90 */
    HitLandModelView() : HitLandModelVtable(&vtable) { }
    ~HitLandModelView() { vtable = DAT_0053a810; }
};
extern "C" igMetaObject *g_beHitLandModelTraversal_metaObject;
union U_35dcb0 { int vt; char b[80]; };
extern "C" int DAT_00536360[4];
struct igMetaObject_35dd50;
extern "C" igMetaObject_35dd50 *igIntersectTraversal_GetPublishedMetaObject(void);
extern "C" int g_igIntersectTraversal_metaObject[4];
extern "C" igMetaObject *g_beHitLandModelOrder_metaObject;
union U_35df70 { int vt; char b[64]; };
extern "C" int DAT_0053a7a0[4];
extern "C" igMetaObject *g_beHitLandResultDataList_metaObject;
extern "C" int DAT_005362f0[4];
extern "C" igMetaObject *g_beHitLandResultData_metaObject;
union U_35e490 { int vt; char b[96]; };
extern "C" int DAT_00536290[4];
extern "C" igMetaObject *g_beHitLandDelivInfoRam_metaObject;
union U_35e6b0 { int vt; char b[112]; };
extern "C" int DAT_00536230[4];
extern "C" igMetaObject *g_beHitLandDelivInfo_metaObject;
extern "C" int DAT_005361c0[4];
struct Obj_35ea10 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" igMetaObject *g_beHitLandDeliv_metaObject;
union U_35ec70 { int vt; char b[32]; };
extern "C" int DAT_0053a700[4];
extern "C" igMetaObject *g_beGroupKeepList_metaObject;
struct Obj_35eea0 { int *vt; char pad[28]; };
extern "C" int DAT_00536150[4];
extern "C" igMetaObject *g_beGroupKeep_metaObject;
struct Obj_35efe0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_005360b0[4];
extern "C" igMetaObject *g_beGeneraterInfoWork_metaObject;
extern "C" igMetaObject *FUN_0035f190(void);
extern "C" int DAT_00536050[4];
extern "C" igMetaObject *g_beGeneraterInfoRam_metaObject;
extern "C" igMetaObject *FUN_0035f410(void);
struct T_35f460 { int word0; int references; };
extern "C" int DAT_00535ff0[4];
struct Obj_35f460 {
    int *vt; char p4[36]; T_35f460 *m40; T_35f460 *m44; 
    inline void rel40() {
        T_35f460 **self = &m40;
        if (self) {
            T_35f460 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel44() {
        T_35f460 **self = &m44;
        if (self) {
            T_35f460 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" void **FUN_0035f550(struct Ref **self, short flag);
extern "C" igMetaObject *g_beGeneraterInfo_metaObject;
extern "C" igMetaObject *FUN_0035f720(void);
extern "C" int DAT_00535f80[4];
extern "C" igMetaObject *g_beGeneraterDataList_metaObject;
extern "C" igMetaObject *FUN_0035fa20(void);
struct Obj_35fa70 { int *vt; char pad[28]; };
extern "C" int DAT_00535f10[4];
extern "C" igMetaObject *g_beGeneraterData_metaObject;
struct Obj_35fbb0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int DAT_00535eb0[4];
extern "C" O *FUN_0035fcd0(O *arg0, short arg1);
extern "C" igMetaObject *g_beGeneraterPlayerDataList_metaObject;
union U_35ffc0 { int vt; char b[32]; };
extern "C" int DAT_00535e40[4];
extern "C" igMetaObject *g_beGeneraterPlayerData_metaObject;
struct T_360100 { int word0; int references; };
extern "C" int DAT_00535de0[4];
struct Obj_360100 {
    int *vt; int w0; int w1; int w2; T_360100 *r3; T_360100 *r4; int w5; int w6;
    inline void rel3() {
        T_360100 **self = &r3;
        if (self) {
            T_360100 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel4() {
        T_360100 **self = &r4;
        if (self) {
            T_360100 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beGeneraterItemDataList_metaObject;
struct Obj_360400 { int *vt; char pad[28]; };
extern "C" int DAT_00535d70[4];
extern "C" igMetaObject *g_beGeneraterItemData_metaObject;
union U_360540 { int vt; char b[16]; };
extern "C" int DAT_00535d10[4];
extern "C" igMetaObject *g_beGeneraterItemDataOneList_metaObject;
extern "C" int DAT_00535ca0[4];
extern "C" igMetaObject *g_beGeneraterItemDataOne_metaObject;
union U_360960 { int vt; char b[32]; };
extern "C" int DAT_00535c40[4];
extern "C" igMetaObject *g_beGenerater_metaObject;
extern "C" int DAT_0053a660[4];
extern "C" igMetaObject *g_beFontInfo_metaObject;
union U_360ee0 { int vt; char b[32]; };
extern "C" int DAT_00535bd0[4];
extern "C" ObjectRefWord *FUN_00360f60(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beFontInfoData_metaObject;
struct F_361180 { int *vt; int w[11]; };
extern "C" int DAT_00535b70[4];
extern "C" igMetaObject *g_beUnicodeObjList_metaObject;
extern "C" igMetaObject *FUN_003613b0(void);
struct Obj_361400 { int *vt; char pad[28]; };
extern "C" int DAT_00535b00[4];
extern "C" igMetaObject *g_beUnicodeObj_metaObject;
extern "C" igMetaObject *FUN_00361530(void);
union U_361580 { int vt; char b[16]; };
extern "C" int DAT_0053a560[4];
extern "C" igMetaObject *g_beFontImageList_metaObject;
extern "C" igMetaObject *FUN_003617a0(void);
struct Obj_3617f0 { int *vt; char pad[28]; };
extern "C" int DAT_00535a90[4];
extern "C" igMetaObject *g_beFontImage_metaObject;
extern "C" igMetaObject *FUN_003618e0(void);
struct Obj_361930 { int *vt; int w[11]; };
extern "C" int DAT_005359b0[4];
typedef struct S_temp_a0_3619a0 { char pad4[4]; int f4; } S_temp_a0_3619a0;
extern "C" int DAT_00535a20[4];
typedef struct R_361a20 { int w0; int refs; } R_361a20;
typedef struct O_361a20 { int *vt; int f4; int *str; int f12; int f16; R_361a20 *ref; } O_361a20;
extern "C" O_361a20 *FUN_00361a20(O_361a20 *arg0, short arg1);
extern "C" int DAT_00541610[4];
typedef struct R_361b00 { int w0; int refs; } R_361b00;
typedef struct O_361b00 { int *vt; int f4; int *str; int f12; int f16; R_361b00 *ref20; int f24; R_361b00 *ref28; R_361b00 *ref32; } O_361b00;
extern "C" O_361b00 *FUN_00361b00(O_361b00 *arg0, short arg1);
struct igMetaObject_361c90;
extern "C" igMetaObject_361c90 *igBitmapFont_GetPublishedMetaObject(void);
extern "C" int g_igBitmapFont_metaObject[4];
extern "C" igMetaObject *g_beFont_metaObject;
struct Obj_361f30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int DAT_0053a5c0[4];
extern "C" ObjectRefWord *FUN_00362070(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beFontGeomAttrPairList_metaObject;
struct Obj_362400 { int *vt; char pad[28]; };
extern "C" int DAT_00535940[4];
extern "C" igMetaObject *g_beFontGeomAttrPair_metaObject;
union U_362580 { int vt; char b[32]; };
extern "C" int DAT_005358e0[4];
extern "C" igMetaObject *g_beFileListInfoManager_metaObject;
struct Obj_3628d0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int DAT_0053a4e0[4];
extern "C" igMetaObject *g_beFileListInfo_metaObject;
union U_362c50 { int vt; char b[32]; };
extern "C" int DAT_00535870[4];
extern "C" igMetaObject *g_beFile_metaObject;
struct Obj_362ea0 { int *vt; char pad[4]; };
extern "C" int DAT_00535810[4];
extern "C" igMetaObject *g_beFileChkObj_metaObject;
struct F_363020 { int *vt; int pad[1]; int *ref; int pad2[1]; };
extern "C" int DAT_005357b0[4];
extern "C" igMetaObject *g_beDemoManager_metaObject;
extern "C" int DAT_0053a460[4];
struct Obj_3632f0 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char t[4]; };
extern "C" ObjectRefWord *FUN_00363380(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_00363400(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beDemoManagerWorkList_metaObject;
struct Obj_3636d0 { int *vt; char pad[28]; };
extern "C" int DAT_00535740[4];
extern "C" igMetaObject *g_beDemoManagerWork_metaObject;
union U_3638a0 { int vt; char b[16]; };
extern "C" int DAT_005356e0[4];
extern "C" igMetaObject *g_beDemoKeepMesList_metaObject;
extern "C" igMetaObject *FUN_00363ae0(void);
struct Obj_363b30 { int *vt; char pad[28]; };
extern "C" int DAT_00535670[4];
extern "C" igMetaObject *g_beDemoKeepMes_metaObject;
extern "C" igMetaObject *FUN_00363c60(void);
extern "C" int DAT_00535610[4];
extern "C" igMetaObject *g_beDataObjListList_metaObject;
extern "C" igMetaObject *FUN_00363f10(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_363f60;
extern "C" int DAT_005355a0[4];
extern "C" igMetaObject *g_beDataObjList_metaObject;
extern "C" igMetaObject *FUN_003640e0(void);
struct Obj_364130 { int *vt; char pad[28]; };
extern "C" int DAT_00535530[4];
extern "C" igMetaObject *g_beDataObjFloatList_metaObject;
union U_3642b0 { int vt; int w[4]; void *p[4]; char b[16]; };
struct Rc { int vt; int rc; };
extern "C" int DAT_005354d0[4];
extern "C" igMetaObject *g_beDataObjObjectList_metaObject;
struct T_364580 { int word0; int references; };
extern "C" int DAT_00535470[4];
struct Obj_364580 {
    int *vt; int w0; int *r1; T_364580 *r2;
    inline void rel1() {
        int **self = &r1;
        if (self) {
            int *p = *self;
            if (p) {
                int *a1 = p - 2;
                int v0 = p[-1] - 1;
                p[-1] = v0;
                if (v0 == 0)
                    StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    inline void rel2() {
        T_364580 **self = &r2;
        if (self) {
            T_364580 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beDataObjStringList_metaObject;
struct T_364850 { int word0; int references; };
extern "C" int DAT_00535410[4];
struct Obj_364850 {
    int *vt; char p4[4]; char *m8; T_364850 *m12; 
    inline void rel8() {
        char **self = &m8;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void rel12() {
        T_364850 **self = &m12;
        if (self) {
            T_364850 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beDataObjString_metaObject;
extern "C" int DAT_005353b0[4];
extern "C" igMetaObject *g_beDataObjBoolList_metaObject;
union U_364dc0 { int vt; char b[16]; };
extern "C" int DAT_00535350[4];
extern "C" igMetaObject *g_beDataObjBool_metaObject;
struct F_365090 { int *vt; char pad[4]; int *str; char pad2[4]; };
extern "C" int DAT_005352f0[4];
extern "C" igMetaObject *g_beDataObjIntList_metaObject;
struct T_3652d0 { int word0; int references; };
extern "C" int DAT_00535290[4];
struct Obj_3652d0 {
    int *vt; char p4[4]; char *m8; T_3652d0 *m12; 
    inline void rel8() {
        char **self = &m8;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void rel12() {
        T_3652d0 **self = &m12;
        if (self) {
            T_3652d0 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beDataObjInt_metaObject;
union U_3655f0 { int vt; char b[16]; };
extern "C" int DAT_00535230[4];
extern "C" igMetaObject *g_beDataBaseList_metaObject;
struct Obj_3657f0 { int *vt; char pad[28]; };
extern "C" int DAT_005351c0[4];
extern "C" igMetaObject *g_beDataBase_metaObject;
union U_365980 { int vt; int w[13]; char b[52]; };
extern "C" int DAT_00535160[4];
extern "C" igMetaObject *g_beDBManagerInfo_metaObject;
extern "C" igMetaObject *FUN_00365dc0(void);
extern "C" int DAT_005350f0[4];
struct Obj_365e10 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" igMetaObject *g_beDBManager_metaObject;
extern "C" igMetaObject *FUN_00366160(void);
union U_3661b0 { int vt; char b[32]; };
extern "C" int DAT_0053bb70[4];
extern "C" igMetaObject *g_beCriVolume_metaObject;
extern "C" igMetaObject *FUN_00366390(void);
struct Obj_3663e0 { int *vt; char pad[28]; };
extern "C" int DAT_00535090[4];
extern "C" igMetaObject *g_beCriSfpData_metaObject;
extern "C" igMetaObject *FUN_00366540(void);
extern "C" int DAT_00535030[4];
struct igMetaObject_366640;
extern "C" igMetaObject_366640 * beBinDataObject_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beCriHandleList_metaObject;
struct Obj_366820 { int *vt; char pad[28]; };
extern "C" int DAT_00534fc0[4];
extern "C" igMetaObject *g_beCriHandle_metaObject;
extern "C" int DAT_00534f60[4];
extern "C" igMetaObject *g_beCriFxInfo_metaObject;
extern "C" int DAT_00534ef0[4];
extern "C" igMetaObject *g_beCriFxXbData_metaObject;
union U_367040 { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" int DAT_00534e90[4];
extern "C" igMetaObject *g_beCriAudio_metaObject;
union U_367240 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int DAT_00534e30[4];
extern "C" igMetaObject *g_beCriSndf_metaObject;
extern "C" int DAT_00534dd0[4];
extern "C" igMetaObject *g_beCriAcxData_metaObject;
union U_367720 { int vt; char b[32]; };
extern "C" int DAT_00534d70[4];
extern "C" igMetaObject *g_beCri_metaObject;
struct Obj_367940 { int *vt; int w[19]; };
extern "C" int DAT_0053a3e0[4];
extern "C" void **FUN_00367aa0(struct Ref **self, short flag);
extern "C" igMetaObject *g_beCountry_metaObject;
struct Obj_367d60 { int *vt; char pad[4]; };
extern "C" int DAT_00534d10[4];
extern "C" igMetaObject *g_beCopyTransform_metaObject;
extern "C" int DAT_00534c70[4];
/* _srcTransform (igObjectRefMetaField). */
struct SrcTransformField { int *p; SrcTransformField() { p = 0; } ~SrcTransformField(); };
struct CopyTransformVtable { CopyTransformVtable(int **slot) { *slot = DAT_00534c70; } };
struct CopyTransformView : igTransformView, CopyTransformVtable {
    SrcTransformField srcTransform;         /* +108 _srcTransform */
    CopyTransformView() : CopyTransformVtable(&vtable) { }
    ~CopyTransformView() { vtable = DAT_00534c70; }
};
extern "C" igMetaObject *g_beCopyModelCtrl2_metaObject;
extern "C" igMetaObject *FUN_003680b0(void);
extern "C" int DAT_00534bd0[4];
/* _srcNode (igObjectRefMetaField). */
struct SrcNodeField { int *p; SrcNodeField() { p = 0; } ~SrcNodeField(); };
struct CopyModelCtrl2Vtable { CopyModelCtrl2Vtable(int **slot) { *slot = DAT_00534bd0; } };
struct CopyModelCtrl2View : igTransformView, CopyModelCtrl2Vtable {
    SrcNodeField srcNode;         /* +108 _srcNode */
    CopyModelCtrl2View() : CopyModelCtrl2Vtable(&vtable) { }
    ~CopyModelCtrl2View() { vtable = DAT_00534bd0; }
};
extern "C" igMetaObject *g_beChangePosTransformInfoRam_metaObject;
extern "C" igMetaObject *FUN_00368310(void);
struct T_368360 { int word0; int references; };
extern "C" int DAT_00534b70[4];
struct Obj_368360 {
    int *vt; char p4[36]; T_368360 *m40; T_368360 *m44; 
    inline void rel40() {
        T_368360 **self = &m40;
        if (self) {
            T_368360 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel44() {
        T_368360 **self = &m44;
        if (self) {
            T_368360 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beChangePosTransformInfo_metaObject;
extern "C" igMetaObject *FUN_003685a0(void);
struct Obj_3685f0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int DAT_00534b00[4];
extern "C" igMetaObject *g_beChangePosTransform_metaObject;
extern "C" igMetaObject *FUN_003687a0(void);
extern "C" int DAT_0053a340[4];
extern "C" igMetaObject *g_beCameraMode_metaObject;
struct Obj_368ad0 { int *vt; char p4[8]; int sub[4]; char pad[48]; int *r1; int *r2; char pe[44]; };
extern "C" int DAT_0053a2b0[4];
extern "C" int DAT_00542960[4];
struct igMetaObject_368be0;
extern "C" igMetaObject_368be0 *igViewMode_GetPublishedMetaObject(void);
extern "C" int g_igViewMode_metaObject[4];
extern "C" igMetaObject *g_beCameraCtrlInfo_metaObject;
struct Obj_368db0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int DAT_00534a90[4];
extern "C" int g_igObject_metaObject[4];
extern "C" igMetaObject *g_beCameraDemoData_metaObject;
struct T_368fd0 { int word0; int references; };
extern "C" int DAT_00534a30[4];
struct Obj_368fd0 {
    int *vt; int pad4; T_368fd0 *ref; int w[5];
    inline void release() {
        T_368fd0 **self = &ref;
        if (self) {
            T_368fd0 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beCameraBoxData_metaObject;
struct Obj_369200 { int *vt; int w[7]; };
extern "C" int DAT_005349d0[4];
extern "C" igMetaObject *g_beCameraCtrlInfoRamShake_metaObject;
union U_369530 { int vt; char b[64]; };
extern "C" int DAT_00534970[4];
extern "C" igMetaObject *g_beCameraCtrl_metaObject;
extern "C" int DAT_0053a210[4];
/* _cameraMode (igObjectRefMetaField). */
struct CameraModeField { int *p; CameraModeField() { p = 0; } ~CameraModeField(); };
/* Stores the derived vtable before the first member constructor runs. */
struct CameraCtrlVtable { CameraCtrlVtable(int **slot) { *slot = DAT_0053a210; } };
/* matching construct: hand-written view of beCameraCtrl (see beNDMWMdlPlayerInfoWork_GetVTable) */
struct CameraCtrlView : ControllerBaseView, CameraCtrlVtable {
    int viewerMang, viewerPara;             /* +32 */
    CameraModeField cameraMode;             /* +40 _cameraMode */
    float avgPos[3], savePos[3];            /* +44 */
    unsigned char isPosChange;              /* +68 */
    float cameraNowFrame;                   /* +72 */
    int cameraNow, cameraOld;               /* +76 */
    igMatrix44fView eyeMatrix;              /* +84 _eyeMatrix */
    igMatrix44fView intMatrix;              /* +148 _intMatrix */
    float debugZoom;                        /* +212 */
    unsigned char isFirst;                  /* +216 */
    CameraCtrlView() : CameraCtrlVtable(&vtable) { }
    ~CameraCtrlView() { vtable = DAT_0053a210; }
};
extern "C" igMetaObject *g_beBkColorInfo_metaObject;
struct Obj_369c30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_00534900[4];
extern "C" igMetaObject *g_beBkColor_metaObject;
union U_369ea0 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int DAT_0053a170[4];
extern "C" igMetaObject *g_beBaseInfoRamList_metaObject;
union U_36a140 { int vt; char b[32]; };
extern "C" int DAT_00534890[4];
extern "C" igMetaObject *g_beBaseInfoRam_metaObject;
extern "C" igMetaObject *g_beBaseInfoRamTimer_metaObject;
struct Obj_36a5a0 { int *vt; char pad4[4]; void *s; char pad12[52]; };
extern "C" int DAT_00534830[4];
extern "C" igMetaObject *g_beBaseInfoManagerList_metaObject;
extern "C" igMetaObject *FUN_0036a790(void);
extern "C" int DAT_005347c0[4];
extern "C" igMetaObject *g_beBaseInfoManager_metaObject;
extern "C" igMetaObject *FUN_0036a920(void);
extern "C" igMetaObject *g_beBaseInfoList_metaObject;
extern "C" igMetaObject *FUN_0036ab40(void);
struct Obj_36ab90 { int *vt; char pad[28]; };
extern "C" int DAT_00534750[4];
extern "C" igMetaObject *g_beBaseInfo_metaObject;
extern "C" igMetaObject *FUN_0036acd0(void);
extern "C" igMetaObject *g_beBaseInfoDataList_metaObject;
struct Obj_36af60 { int *vt; char pad[28]; };
extern "C" int DAT_005346e0[4];
extern "C" igMetaObject *g_beBaseInfoData_metaObject;
extern "C" igMetaObject *g_beActionStarterInfoRam_metaObject;
struct T_36b210 { int word0; int references; };
extern "C" int DAT_00534680[4];
struct Obj_36b210 {
    int *vt; int w0[9]; T_36b210 *ref; char pad[4];
    inline void releaseRef() {
        T_36b210 **self = &ref;
        if (self) {
            T_36b210 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_beActionStarterInfo_metaObject;
struct Obj_36b3b0 { int *vt; int p4; int f8; int pc; int p10; int f14; int f18; int f1c; };
extern "C" int DAT_00534610[4];
extern "C" O *FUN_0036b430(O *arg0, short arg1);
extern "C" igMetaObject *g_beAsTargetModelDataList_metaObject;
struct Obj_36b6a0 { int *vt; char pad[28]; };
extern "C" int DAT_005345a0[4];
extern "C" igMetaObject *g_beAsTargetModelData_metaObject;
union U_36b7e0 { int vt; char b[16]; };
extern "C" int DAT_00534540[4];
extern "C" igMetaObject *g_beActionStarterData2_metaObject;
union U_36ba60 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int DAT_00534480[4];
extern "C" int DAT_005344e0[4];
struct igMetaObject_36bb50;
extern "C" igMetaObject_36bb50 *beActionStarterData_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beActionStarterDataList_metaObject;
struct Obj_36bd00 { int *vt; char pad[28]; };
extern "C" int DAT_00534410[4];
extern "C" igMetaObject *g_beActionStarterData_metaObject;
struct Obj_36be40 : beActionStarterData {
    inline void rel8() {
        char **self = (char **)&_name;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void rel12() {
        char **self = (char **)&_message;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" igMetaObject *g_beActionStarter_metaObject;
union U_36c110 { int vt; char b[32]; };
extern "C" int DAT_0053a030[4];
extern "C" igMetaObject *g_beAction2InfoWork_metaObject;
extern "C" igMetaObject *FUN_0036c330(void);
union U_36c380 { int vt; char b[96]; };
extern "C" int DAT_005343b0[4];
typedef struct S_temp_a0_36c450 { char pad4[4]; int f4; } S_temp_a0_36c450;
extern "C" igMetaObject *g_beAction2InfoRam_metaObject;
extern "C" igMetaObject *FUN_0036c680(void);
union U_36c6d0 { int vt; char b[64]; };
extern "C" int DAT_00534350[4];
typedef struct S_temp_a0_36c790 { char pad4[4]; int f4; } S_temp_a0_36c790;
extern "C" igMetaObject *g_beAction2InfoList_metaObject;
extern "C" igMetaObject *FUN_0036c9c0(void);
struct Obj_36ca10 { int *vt; char pad[28]; };
extern "C" int DAT_005342e0[4];
extern "C" igMetaObject *g_beAction2Info_metaObject;
extern "C" igMetaObject *FUN_0036cb00(void);
extern "C" int DAT_00534270[4];
extern "C" ObjectRefWord *FUN_0036cc00(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beAction2FLASHSET_metaObject;
union U_36ce60 { int vt; char b[16]; };
extern "C" int DAT_00534210[4];
extern "C" igMetaObject *g_beAction2WAITCHECK_metaObject;
union U_36cff0 { int vt; char b[16]; };
extern "C" int DAT_005341b0[4];
extern "C" igMetaObject *g_beAction2FADESET_metaObject;
union U_36d1f0 { int vt; char b[32]; };
extern "C" int DAT_00534150[4];
extern "C" igMetaObject *g_beAction2JOINTSET_metaObject;
union U_36d3f0 { int vt; char b[32]; };
extern "C" int DAT_005340f0[4];
extern "C" igMetaObject *g_beAction2MOTIONSET_metaObject;
union U_36d630 { int vt; char b[32]; };
extern "C" int DAT_00534090[4];
extern "C" igMetaObject *g_beAction2DataList_metaObject;
struct Obj_36d900 { int *vt; char pad[28]; };
extern "C" int DAT_00534020[4];
extern "C" igMetaObject *g_beAction2Data_metaObject;
union U_36da90 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" int DAT_00533fc0[4];
extern "C" igMetaObject *g_beAction2_metaObject;
union U_36de10 { int vt; char b[32]; };
extern "C" int DAT_00539f90[4];
extern "C" igMetaObject *g_be_metaObject;
struct T_36e080 { int word0; int references; };
extern "C" int DAT_00539f10[4];
struct Obj_36e080 {
    int *vt; int w0[1]; char *s; int w3; T_36e080 *ref; char tail[12];
    inline void releaseRef() {
        T_36e080 **self = &ref;
        if (self) {
            T_36e080 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void releaseStr() {
        char **self = &s;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" igMetaObject *g_ParticleArray_metaObject;
struct Obj_36e310 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; int w28; int w29; int w30; int w31; };
extern "C" int FUN_0014caf0(struct Obj_36e310 *, int);
extern "C" int DAT_0053b740[4];
struct igMetaObject_36e3d0;
extern "C" igMetaObject_36e3d0 *igParticleArray_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_ParticleTimer_metaObject;
extern "C" igMetaObject *FUN_0036e610(void);
struct Obj_36e660 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int FUN_0019d120(struct Obj_36e660 *, int);
extern "C" int DAT_0053b7f0[4];
struct igMetaObject_36e6f0;
extern "C" igMetaObject_36e6f0 *igGeometry_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_ParticleInfo_metaObject;
extern "C" igMetaObject *FUN_0036ea00(void);
struct Obj_36ea50 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; int w28; int w29; int w30; int w31; int w32; int w33; int w34; int w35; int w36; int w37; int w38; int w39; int w40; int w41; int w42; int w43; int w44; int w45; int w46; int w47; int w48; int w49; int w50; int w51; int w52; int w53; int w54; int w55; int w56; int w57; int w58; int w59; int w60; int w61; int w62; int w63; int w64; int w65; int w66; int w67; int w68; int w69; int w70; int w71; int w72; int w73; int w74; int w75; int w76; int w77; int w78; int w79; int w80; int w81; int w82; int w83; int w84; int w85; int w86; int w87; int w88; int w89; int w90; int w91; int w92; int w93; int w94; int w95; int w96; int w97; int w98; int w99; int w100; int w101; int w102; int w103; int w104; int w105; int w106; int w107; int w108; int w109; int w110; int w111; int w112; int w113; int w114; int w115; int w116; int w117; int w118; int w119; int w120; int w121; int w122; int w123; int w124; int w125; int w126; int w127; int w128; int w129; int w130; int w131; int w132; int w133; int w134; int w135; int w136; int w137; int w138; int w139; int w140; int w141; int w142; int w143; int w144; int w145; int w146; int w147; int w148; int w149; int w150; int w151; int w152; int w153; int w154; int w155; int w156; int w157; int w158; int w159; int w160; int w161; int w162; int w163; int w164; int w165; int w166; int w167; int w168; int w169; int w170; int w171; int w172; int w173; int w174; int w175; int w176; int w177; int w178; int w179; int w180; int w181; int w182; int w183; int w184; int w185; int w186; int w187; int w188; int w189; int w190; int w191; int w192; int w193; int w194; int w195; int w196; int w197; int w198; int w199; int w200; int w201; int w202; int w203; int w204; int w205; int w206; int w207; int w208; int w209; int w210; int w211; int w212; int w213; int w214; int w215; int w216; int w217; int w218; int w219; int w220; int w221; int w222; int w223; int w224; int w225; int w226; int w227; int w228; int w229; int w230; int w231; int w232; int w233; int w234; int w235; int w236; int w237; int w238; int w239; int w240; int w241; int w242; int w243; int w244; int w245; int w246; int w247; int w248; int w249; int w250; int w251; int w252; int w253; int w254; int w255; };
extern "C" int FUN_0019b040(struct Obj_36ea50 *, int);
extern "C" int DAT_00533f50[4];
struct igMetaObject_36eb10;
extern "C" igMetaObject_36eb10 *igSceneInfo_GetPublishedMetaObject(void);
extern "C" int g_igSceneInfo_metaObject[4];
extern "C" void Gap__Bec__ParticleInfo__vfunc_11(ParticleInfo *self, int clearControls);
extern "C" void Gap__Bec__beBinDataObject__vfunc_8(beBinDataObject *arg0);
// clang-format off
/* beDataBase record lookup and row count, 0x003a93a0..0x003a9708. A beDataBase is a table of
 * records (rows). Its cells are split by type into six data lists (char, short, int, float, bool,
 * string); each data list is paired with an "offset list" that names the table's columns for that
 * type. A cell of record R and column C is stored row-major at index (columnCount * R + C) of the
 * matching data list (the Junk Shop table is 9 rows x 36 columns; the enemy
 * table keys MODEL, HPMAX, ... by column name). The lists are reached through the reflected
 * object-reference fields and viewed here as the igDataList count/data prefix. */


/* Index returned by beDataBase_FindRecordValueIndex when the key has no column. */


struct igProperty;
typedef igTDataList<igProperty *> ColumnList;
extern "C" int g_propertyNameField[4];
extern "C" char emptyString[];
extern "C" int beDataBase_FindRecordValueIndex(beDataBase *, int, const char *, ColumnList *);
extern "C" long long beDataBase_GetRecordInt(beDataBase *, int, const char *);
extern "C" unsigned long long beDataBase_GetRecordBool(beDataBase *, int, const char *);
extern "C" char *beDataBase_GetRecordString(beDataBase *, int, const char *);
extern "C" int beDataBase_GetRecordCount(beDataBase *);
extern "C" int g_igFont_metaObject[4];
extern "C" int g_igLightSet_metaObject[4];
extern "C" void Gap__Bec__beLuaDataObject__vfunc_08(beLuaDataObject *arg0);
struct T_36f970 { int word0; int references; };
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int kIGMemoryPoolHandleUser1[4];
struct Rel { static inline void go(T_36f970 *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Ref_36f970 { T_36f970 *p; Ref_36f970(T_36f970 *x) : p(x) {} ~Ref_36f970() { Rel::go(p); } };
struct Obj_36f970 {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual void a6();
    virtual void a7();
    virtual void a8();
    virtual void a9();
    virtual void a10();
    virtual void a11();
    virtual void a12();
    virtual void a13();
    virtual void a14();
    virtual void a15();
    virtual void a16();
    virtual void a17();
    virtual void a18();
    virtual void a19();
    virtual int v88();
    int f4; int f8; void *list;
};
extern "C" void Gap__Bec__beNumVerData__vfunc_07(Obj_36f970 *arg0, int arg1);
/* matching construct: inlined release helper reproducing the retail refcount decrement */
struct Rel_36fae0 { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* matching construct: dummy-virtual receiver so arg0->v88() dispatches through vtable offset 88 */
struct Obj_36fae0 {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual void a6();
    virtual void a7();
    virtual void a8();
    virtual void a9();
    virtual void a10();
    virtual void a11();
    virtual void a12();
    virtual void a13();
    virtual void a14();
    virtual void a15();
    virtual void a16();
    virtual void a17();
    virtual void a18();
    virtual void a19();
    virtual int v88();
};
extern "C" void Gap__Bec__beNumVerData__vfunc_08(Obj_36fae0 *arg0);
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_88_0_36fd80 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad4; int f8; int f12; };
extern "C" void Gap__Bec__beSaveDataDeliver__vfunc_08(DW4VC_88_0_36fd80 *arg0);
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class SvPlatDataGCVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
extern "C" void Gap__Bec__beSvPlatDataGC__vfunc_08(beSvPlatDataGC *arg0);
extern "C" void Gap__Bec__beSvPs2McImage128k__vfunc_07(beSvPs2McImage128k *arg0, int arg1);
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class SvPs2McImageVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" void Gap__Bec__beXboxImage24k__vfunc_07(beXboxImage24k *arg0, int arg1);
class DW4VC_88_0_370070 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad4; int f8; };
extern "C" void Gap__Bec__beXboxImage24k__vfunc_08(DW4VC_88_0_370070 *arg0);
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class TransformSyncChildVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();  virtual int vX(int); };
extern "C" void Gap__Bec__beTransformSync__vfunc_35(beTransformSync *arg0, int arg1);
extern "C" int g_igAppearanceList_metaObject[4];

#endif
