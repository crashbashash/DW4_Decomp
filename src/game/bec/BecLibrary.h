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
extern "C" void igModelViewMatrixBoneSelect_EnsureRegistered(void);
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
extern "C" void igNodeList_EnsureRegistered(void);
extern "C" void igNamedObjectList_EnsureRegistered(void);
extern "C" void igAppearanceList_EnsureRegistered(void);
extern "C" void igVertexArray_EnsureRegistered(void);
extern "C" void igFloatList_EnsureRegistered(void);
extern "C" void igIntList_EnsureRegistered(void);
extern "C" void igFloatListList_EnsureRegistered(void);
extern "C" void igVec3fList_EnsureRegistered(void);
extern "C" void igTransformList_EnsureRegistered(void);
extern "C" void igAttrSet_EnsureRegistered(void);
extern "C" void igTextureAttr_EnsureRegistered(void);
extern "C" void igRandomNumber_EnsureRegistered(void);
extern "C" void igStringRefList_EnsureRegistered(void);
extern "C" void igDirectory_EnsureRegistered(void);
extern "C" void igStringObj_EnsureRegistered(void);
extern "C" void igInfoList_EnsureRegistered(void);
extern "C" void igGroup_EnsureRegistered(void);
extern "C" void igSwitch_EnsureRegistered(void);
extern "C" void igNode_EnsureRegistered(void);
extern "C" void igProjectiveShadowShader_EnsureRegistered(void);
extern "C" void igBoolList_EnsureRegistered(void);
extern "C" void igObjectList_EnsureRegistered(void);
extern "C" void igTransform_EnsureRegistered(void);
extern "C" void igGeometry_EnsureRegistered(void);
extern "C" void igSceneInfo_EnsureRegistered(void);
extern "C" void igMovieManager_EnsureRegistered(void);
extern "C" void igAttrList_EnsureRegistered(void);
extern "C" void igAABox_EnsureRegistered(void);
extern "C" void igAABoxList_EnsureRegistered(void);
extern "C" void igTransformRecorder_EnsureRegistered(void);
extern "C" void igLongList_EnsureRegistered(void);
extern "C" void igMatrix44fList_EnsureRegistered(void);
extern "C" void igIntListList_EnsureRegistered(void);
extern "C" void igLuaGlue_EnsureRegistered(void);
extern "C" void igLightSet_EnsureRegistered(void);
extern "C" void igBlendStateAttr_EnsureRegistered(void);
extern "C" void igBlendFunctionAttr_EnsureRegistered(void);
extern "C" void igColorAttr_EnsureRegistered(void);
extern "C" void igProbe_EnsureRegistered(void);
extern "C" void igRayList_EnsureRegistered(void);
extern "C" void igGeometryAttrList_EnsureRegistered(void);
extern "C" void igViewerSceneInfoManager_EnsureRegistered(void);
extern "C" void igDirectoryList_EnsureRegistered(void);
extern "C" void igFile_EnsureRegistered(void);
extern "C" void igNamedObject_EnsureRegistered(void);
extern "C" void igCharList_EnsureRegistered(void);
extern "C" void igShortList_EnsureRegistered(void);
extern "C" void igAdxAudio_EnsureRegistered(void);
extern "C" void igGraphPath_EnsureRegistered(void);
extern "C" void igCamera_EnsureRegistered(void);
extern "C" void igInsightCore_EnsureRegistered(void);
extern "C" void igObject_EnsureRegistered(void);
extern "C" void igGeometryList_EnsureRegistered(void);
extern "C" void igViewerParameters_EnsureRegistered(void);
extern "C" void igTextureStateAttr_EnsureRegistered(void);
extern "C" void igLightingStateAttr_EnsureRegistered(void);
extern "C" void igActorList_EnsureRegistered(void);
extern "C" void igAnimationDatabase_EnsureRegistered(void);
extern "C" void igImage_EnsureRegistered(void);

extern "C" void FUN_0033bf50(void);
extern "C" void BecLibrary_MarkRegistered(void);
extern "C" void *libBecRuntimePlugin_GetMetaObject(void);
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
extern "C" void libBecRuntimePlugin_EnsureRegistered(void);
extern "C" void * igMetaObject_RegisterClass(...);
extern "C" void *igInsightPlugin_Register(void);
extern "C" int libBecRuntimePlugin_GetVTable(void);
extern "C" void *libBecRuntimePlugin_Register(void);
extern "C" void libBecRuntimePlugin_GetMetaObjectFunction(void);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void * igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" void libBecRuntimePlugin_InitFields(void);
extern "C" void *beWeaponInfoRam_GetMetaObject(void);
extern "C" int beWeaponInfoRam_GetVTable(void);
extern "C" int Memory_FreeBufferAliasC(...);
extern "C" void beWeaponInfoRam_EnsureRegistered(void);
extern "C" void *beWeaponInfoRam_Register(void);
extern "C" void beWeaponInfoRam_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
extern "C" void *beWeaponInfo_GetMetaObject(void);
extern "C" int FUN_001958f0(...);
extern "C" int FUN_00199450(...);
extern "C" int beWeaponInfo_GetVTable(void);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" void beWeaponInfo_EnsureRegistered(void);
extern "C" void *beWeaponInfo_Register(void);
extern "C" void beWeaponInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
extern "C" int igNodeList_GetOrCreateMetaObject(void);
extern "C" int igNamedObjectList_GetOrCreateMetaObject(...);
extern "C" void beWeaponInfo_InitFields(void);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" igMetaObject *igMetaObject_Create(int);
extern "C" igMetaObject *beWeaponSeqDataList_GetOrCreateMetaObject(void);
extern "C" void *beWeaponSeqDataList_GetMetaObject(void);
extern "C" int beWeaponSeqDataList_GetVTable(void);
extern "C" void beWeaponSeqDataList_EnsureRegistered(void);
extern "C" void *igObjectList_Register(void);
extern "C" void *beWeaponSeqDataList_Register(void);
extern "C" void beWeaponSeqDataList_GetMetaObjectFunction(void);
extern "C" void *beWeaponSeqData_GetMetaObject(void);
extern "C" int beWeaponSeqData_GetVTable(void);
extern "C" void beWeaponSeqData_EnsureRegistered(void);
extern "C" void *igNamedObject_Register(void);
extern "C" void *beWeaponSeqData_Register(void);
extern "C" void beWeaponSeqData_GetMetaObjectFunction(void);
extern "C" void beWeaponSeqData_InitFields(void);
extern "C" igMetaEnum *igMetaEnum_Create(const char *name, const char **names, int *values, int count);
extern "C" igMetaEnum *beWeaponSeqData_GetMsgActionEnum(void);
extern "C" int igMetaObject_CreateInstance(...);
extern "C" void beWeapon_CreateInstance(int arg0);
extern "C" igMetaObject *beWeapon_GetOrCreateMetaObject(void);
extern "C" void *beWeapon_GetMetaObject(void);
extern "C" int beWeapon_GetVTable(void);
extern "C" void **FUN_0033f560(void **arg0, int arg1);
extern "C" void **beWeapon_igSmartPointer_igObject_Destruct(void **arg0, short arg1);
extern "C" void beWeapon_EnsureRegistered(void);
extern "C" void *beWeapon_Register(void);
extern "C" void beWeapon_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
extern "C" void beWeapon_InitFields(void);
extern "C" void beWeaponAttachDataList_Create(int arg0);
extern "C" igMetaObject *beWeaponAttachDataList_GetOrCreateMetaObject(void);
extern "C" int beWeaponAttachDataList_GetVTable(void);
extern "C" void beWeaponAttachDataList_EnsureRegistered(void);
extern "C" void *beWeaponAttachDataList_Register(void);
extern "C" void beWeaponAttachDataList_GetMetaObjectFunction(void);
extern "C" void beWeaponAttachData_Create(int arg0);
extern "C" int beWeaponAttachData_GetVTable(void);
extern "C" void beWeaponAttachData_EnsureRegistered(void);
extern "C" void *igObject_Register(void);
extern "C" void *beWeaponAttachData_Register(void);
extern "C" void beWeaponAttachData_GetMetaObjectFunction(void);
extern "C" void beWeaponAttachData_InitFields(void);
extern "C" igMetaObject *igAppearanceListList_GetOrCreateMetaObject(void);
extern "C" int igAppearanceListList_GetVTable(void);
extern "C" void igAppearanceListList_EnsureRegistered(void);
extern "C" void *igAppearanceListList_Register(void);
extern "C" void igAppearanceListList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelectListBec_GetOrCreateMetaObject(void);
extern "C" int igModelViewMatrixBoneSelectListBec_GetVTable(void);
extern "C" void igModelViewMatrixBoneSelectListBec_EnsureRegistered(void);
extern "C" void *igModelViewMatrixBoneSelectListBec_Register(void);
extern "C" void igModelViewMatrixBoneSelectListBec_GetMetaObjectFunction(void);
extern "C" void *beWaterPlainInfoRam_GetMetaObject(void);
extern "C" int FUN_001338d0(int *, int);
extern "C" int FUN_001354b0(int *, int);
extern "C" int igSmartPointer_igIntList_Destruct(int *, int);
extern "C" int beWaterPlainInfoRam_GetVTable(void);
extern "C" void **FUN_00340240(void **arg0, long long arg1);
extern "C" void beWaterPlainInfoRam_EnsureRegistered(void);
extern "C" void *beWaterPlainInfoRam_Register(void);
extern "C" void beWaterPlainInfoRam_GetMetaObjectFunction(void);
extern "C" int igVertexArray_GetOrCreateMetaObject(void);
extern "C" int igFloatListList_GetOrCreateMetaObject(void);
extern "C" int igFloatList_GetOrCreateMetaObject(void);
extern "C" int igIntList_GetOrCreateMetaObject(void);
extern "C" void beWaterPlainInfoRam_InitFields(void);
extern "C" igMetaObject *beWaterMove_GetOrCreateMetaObject(void);
extern "C" void *beWaterMove_GetMetaObject(void);
extern "C" int beWaterMove_GetVTable(void);
extern "C" void beWaterMove_EnsureRegistered(void);
extern "C" void *beWaterMove_Register(void);
extern "C" void beWaterMove_GetMetaObjectFunction(void);
extern "C" void beWaterMove_InitFields(void);
extern "C" igMetaObject *beWaterMoveDataList_GetOrCreateMetaObject(void);
extern "C" void *beWaterMoveDataList_GetMetaObject(void);
extern "C" int beWaterMoveDataList_GetVTable(void);
extern "C" void beWaterMoveDataList_EnsureRegistered(void);
extern "C" void *beWaterMoveDataList_Register(void);
extern "C" void beWaterMoveDataList_GetMetaObjectFunction(void);
extern "C" void *beWaterMoveData_GetMetaObject(void);
extern "C" int beWaterMoveData_GetVTable(void);
extern "C" void beWaterMoveData_EnsureRegistered(void);
extern "C" void *beWaterMoveData_Register(void);
extern "C" void beWaterMoveData_GetMetaObjectFunction(void);
extern "C" int igVec3fList_GetOrCreateMetaObject(void);
extern "C" void beWaterMoveData_InitFields(void);
extern "C" void *beWaterPlainInfo_GetMetaObject(void);
extern "C" int beWaterPlainInfo_GetVTable(void);
extern "C" void beWaterPlainInfo_EnsureRegistered(void);
extern "C" void *beWaterPlainInfo_Register(void);
extern "C" void beWaterPlainInfo_GetMetaObjectFunction(void);
extern "C" igMetaEnum *beWaterPlain_GetMessageEnum(void);
extern "C" void beWaterPlain_CreateInstance(int arg0);
extern "C" igMetaObject *beWaterPlain_GetOrCreateMetaObject(void);
extern "C" void *beWaterPlain_GetMetaObject(void);
extern "C" int beWaterPlain_GetVTable(void);
extern "C" void beWaterPlain_EnsureRegistered(void);
extern "C" void *beWaterPlain_Register(void);
extern "C" void beWaterPlain_GetMetaObjectFunction(void);
extern "C" void *beUnicode_GetMetaObject(void);
extern "C" int beUnicode_GetVTable(void);
extern "C" void beUnicode_EnsureRegistered(void);
extern "C" void *beUnicode_Register(void);
extern "C" void beUnicode_GetMetaObjectFunction(void);
extern "C" void *beTransformSync_GetMetaObject(void);
extern "C" int beTransformSync_GetVTable(void);
extern "C" void beTransformSync_EnsureRegistered(void);
extern "C" void *igTransform_Register(void);
extern "C" void *beTransformSync_Register(void);
extern "C" void beTransformSync_GetMetaObjectFunction(void);
extern "C" int igTransformList_GetOrCreateMetaObject(void);
extern "C" void beTransformSync_InitFields(void);
extern "C" void beTimer_CreateInstance(int arg0);
extern "C" igMetaObject *beTimer_GetOrCreateMetaObject(void);
extern "C" void *beTimer_GetMetaObject(void);
extern "C" int beTimer_GetVTable(void);
extern "C" void beTimer_EnsureRegistered(void);
extern "C" void *igInfoManager_Register(void);
extern "C" void *beTimer_Register(void);
extern "C" void beTimer_GetMetaObjectFunction(void);
extern "C" void beTimer_InitFields(void);
extern "C" igMetaObject *beTimerDataList_GetOrCreateMetaObject(void);
extern "C" void *beTimerDataList_GetMetaObject(void);
extern "C" int beTimerDataList_GetVTable(void);
extern "C" void beTimerDataList_EnsureRegistered(void);
extern "C" void *beTimerDataList_Register(void);
extern "C" void beTimerDataList_GetMetaObjectFunction(void);
extern "C" int beTimerData_GetVTable(void);
extern "C" void beTimerData_EnsureRegistered(void);
extern "C" void *beTimerData_Register(void);
extern "C" void beTimerData_GetMetaObjectFunction(void);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" void beTimerData_InitFields(void);
extern "C" int beTextureCtrlInfoList_GetVTable(void);
extern "C" void beTextureCtrlInfoList_EnsureRegistered(void);
extern "C" void *beTextureCtrlInfoList_Register(void);
extern "C" void beTextureCtrlInfoList_GetMetaObjectFunction(void);
extern "C" int beTextureCtrlInfo_GetVTable(void);
extern "C" void beTextureCtrlInfo_EnsureRegistered(void);
extern "C" void *beTextureCtrlInfo_Register(void);
extern "C" void beTextureCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beTextureCtrlInfo_InitFields(void);
extern "C" int beTextureCtrlAttr_GetVTable(void);
extern "C" void beTextureCtrlAttr_EnsureRegistered(void);
extern "C" void *beTextureCtrlAttr_Register(void);
extern "C" void beTextureCtrlAttr_GetMetaObjectFunction(void);
extern "C" int igAttrSet_GetOrCreateMetaObject(void);
extern "C" void beTextureCtrlAttr_InitFields(void);
extern "C" void *beTextureCtrlData_GetMetaObject(void);
extern "C" int beTextureCtrlData_GetVTable(void);
extern "C" void beTextureCtrlData_EnsureRegistered(void);
extern "C" void *beTextureCtrlData_Register(void);
extern "C" void beTextureCtrlData_GetMetaObjectFunction(void);
extern "C" int igTextureAttr_GetOrCreateMetaObject(void);
extern "C" void beTextureCtrlData_InitFields(void);
extern "C" void beTextureCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beTextureCtrl_GetOrCreateMetaObject(void);
extern "C" void *beTextureCtrl_GetMetaObject(void);
extern "C" int beTextureCtrl_GetVTable(void);
extern "C" void **FUN_00342460(void **arg0, short arg1);
extern "C" void beTextureCtrl_EnsureRegistered(void);
extern "C" void *beTextureCtrl_Register(void);
extern "C" void beTextureCtrl_GetMetaObjectFunction(void);
extern "C" void beTextureCtrl_InitFields(void);
extern "C" void beTextureCtrlWork_Create(int arg0);
extern "C" igMetaObject *beTextureCtrlWork_GetOrCreateMetaObject(void);
extern "C" void *beTextureCtrlWork_GetMetaObject(void);
extern "C" int beTextureCtrlWork_GetVTable(void);
extern "C" void beTextureCtrlWork_EnsureRegistered(void);
extern "C" void *beTextureCtrlWork_Register(void);
extern "C" void beTextureCtrlWork_GetMetaObjectFunction(void);
extern "C" void beTextureCtrlWork_InitFields(void);
extern "C" void beTargetObj_CreateInstance(int arg0);
extern "C" igMetaObject *beTargetObj_GetOrCreateMetaObject(void);
extern "C" void *beTargetObj_GetMetaObject(void);
extern "C" int FUN_001374b0(int *, int);
extern "C" int FUN_00231030(...);
extern "C" int beTargetObj_GetVTable(void);
extern "C" void beTargetObj_EnsureRegistered(void);
extern "C" void *beTargetObj_Register(void);
extern "C" void beTargetObj_GetMetaObjectFunction(void);
extern "C" void beTargetObj_InitFields(void);
extern "C" void beSystem_CreateInstance(int arg0);
extern "C" igMetaObject *beSystem_GetOrCreateMetaObject(void);
extern "C" void *beSystem_GetMetaObject(void);
extern "C" int igSmartPointer_igStringObj_Destruct(int *, int);
extern "C" int igSmartPointer_igStringRefList_Destruct(int *, int);
extern "C" int igSmartPointer_igInfoList_Destruct(int *, int);
extern "C" int igSmartPointer_igDirectory_Destruct(int *, int);
extern "C" int FUN_00229350(int *, int);
extern "C" int igStringRef_Destruct(...);
extern "C" int beSystem_GetVTable(void);
extern "C" void **FUN_00342eb0(void **arg0, short arg1);
extern "C" void beSystem_EnsureRegistered(void);
extern "C" void *beSystem_Register(void);
extern "C" void beSystem_GetMetaObjectFunction(void);
extern "C" int igGroup_GetOrCreateMetaObject(void);
extern "C" int igRandomNumber_GetOrCreateMetaObject(void);
extern "C" int igStringRefList_GetOrCreateMetaObject(void);
extern "C" int igStringObj_GetOrCreateMetaObject(void);
extern "C" int igInfoList_GetOrCreateMetaObject(void);
extern "C" int igDirectory_GetOrCreateMetaObject(void);
extern "C" int igBoolMetaField_SetDefaultValue(void *, int);
extern "C" int igFloatMetaField_SetDefault(void *, float);
extern "C" void beSystem_InitFields(void);
extern "C" void *beSwitchCtrlInfo_GetMetaObject(void);
extern "C" int beSwitchCtrlInfo_GetVTable(void);
extern "C" void beSwitchCtrlInfo_EnsureRegistered(void);
extern "C" void *beSwitchCtrlInfo_Register(void);
extern "C" void beSwitchCtrlInfo_GetMetaObjectFunction(void);
extern "C" int igSwitch_GetOrCreateMetaObject(void);
extern "C" void beSwitchCtrlInfo_InitFields(void);
extern "C" igMetaEnum *beSwitchCtrl_GetMessageEnum(void);
extern "C" void beSwitchCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beSwitchCtrl_GetOrCreateMetaObject(void);
extern "C" void *beSwitchCtrl_GetMetaObject(void);
extern "C" int beSwitchCtrl_GetVTable(void);
extern "C" void beSwitchCtrl_EnsureRegistered(void);
extern "C" void *beSwitchCtrl_Register(void);
extern "C" void beSwitchCtrl_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_00343700(void);
extern "C" void beStaticInfoCtl_CreateInstance(int arg0);
extern "C" igMetaObject *beStaticInfoCtl_GetOrCreateMetaObject(void);
extern "C" void *beStaticInfoCtl_GetMetaObject(void);
extern "C" int beStaticInfoCtl_GetVTable(void);
extern "C" void beStaticInfoCtl_EnsureRegistered(void);
extern "C" void *beStaticInfoCtl_Register(void);
extern "C" void beStaticInfoCtl_GetMetaObjectFunction(void);
extern "C" void beStaticInfoCtl_InitFields(void);
extern "C" void *beStaticInfo_GetMetaObject(void);
extern "C" int beStaticInfo_GetVTable(void);
extern "C" void beStaticInfo_EnsureRegistered(void);
extern "C" void *beStaticInfo_Register(void);
extern "C" void beStaticInfo_GetMetaObjectFunction(void);
extern "C" void *beBinDataObject_GetMetaObject(void);
extern "C" void beBinDataObject_EnsureRegistered(void);
extern "C" void *beBinDataObject_Register(void);
extern "C" void beBinDataObject_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
extern "C" int igCharMetaField_GetDefaultDescriptor(...);
extern "C" void beBinDataObject_InitFields(void);
extern "C" int beSoundInfo_GetVTable(void);
extern "C" void beSoundInfo_EnsureRegistered(void);
extern "C" void *beSoundInfo_Register(void);
extern "C" void beSoundInfo_GetMetaObjectFunction(void);
extern "C" void beSoundInfo_InitFields(void);
extern "C" int beSoundData_GetVTable(void);
extern "C" void beSoundData_EnsureRegistered(void);
extern "C" void *beSoundData_Register(void);
extern "C" void beSoundData_GetMetaObjectFunction(void);
extern "C" int igIntMetaField_SetDefault(...);
extern "C" int igShortMetaField_SetDefault(int, int);
extern "C" void beSoundData_InitFields(void);
extern "C" igMetaEnum *beSound_GetMessageEnum(void);
extern "C" void beSound_CreateInstance(int arg0);
extern "C" igMetaObject *beSound_GetOrCreateMetaObject(void);
extern "C" int beSound_GetVTable(void);
extern "C" void **FUN_00344440(void **arg0, short arg1);
extern "C" void beSound_EnsureRegistered(void);
extern "C" void *beSound_Register(void);
extern "C" void beSound_GetMetaObjectFunction(void);
extern "C" void beSound_InitFields(void);
extern "C" igMetaObject *bePlaySEList_GetOrCreateMetaObject(void);
extern "C" int bePlaySEList_GetVTable(void);
extern "C" void bePlaySEList_EnsureRegistered(void);
extern "C" void *bePlaySEList_Register(void);
extern "C" void bePlaySEList_GetMetaObjectFunction(void);
extern "C" void bePlaySE_CreateInstance(int arg0);
extern "C" void *bePlaySE_GetMetaObject(void);
extern "C" int bePlaySE_GetVTable(void);
extern "C" void bePlaySE_EnsureRegistered(void);
extern "C" void *bePlaySE_Register(void);
extern "C" void bePlaySE_GetMetaObjectFunction(void);
extern "C" void bePlaySE_InitFields(void);
extern "C" igMetaObject *beShadow01InfoList_GetOrCreateMetaObject(void);
extern "C" void *beShadow01InfoList_GetMetaObject(void);
extern "C" int beShadow01InfoList_GetVTable(void);
extern "C" void beShadow01InfoList_EnsureRegistered(void);
extern "C" void *beShadow01InfoList_Register(void);
extern "C" void beShadow01InfoList_GetMetaObjectFunction(void);
extern "C" void *beShadow01Info_GetMetaObject(void);
extern "C" int FUN_00198210(char *, int);
extern "C" int beShadow01Info_GetVTable(void);
extern "C" void beShadow01Info_EnsureRegistered(void);
extern "C" void *beShadow01Info_Register(void);
extern "C" void beShadow01Info_GetMetaObjectFunction(void);
extern "C" int igProjectiveShadowShader_GetOrCreateMetaObject(void);
extern "C" int igNode_GetOrCreateMetaObject(void);
extern "C" void beShadow01Info_InitFields(void);
extern "C" void beShadow01_CreateInstance(int arg0);
extern "C" igMetaObject *beShadow01_GetOrCreateMetaObject(void);
extern "C" void *beShadow01_GetMetaObject(void);
extern "C" int beShadow01_GetVTable(void);
extern "C" void beShadow01_EnsureRegistered(void);
extern "C" void *beShadow01_Register(void);
extern "C" void beShadow01_GetMetaObjectFunction(void);
extern "C" void beShadow01_InitFields(void);
extern "C" void *beSelectCtrlInfo_GetMetaObject(void);
extern "C" int beSelectCtrlInfo_GetVTable(void);
extern "C" void beSelectCtrlInfo_EnsureRegistered(void);
extern "C" void *beSelectCtrlInfo_Register(void);
extern "C" void beSelectCtrlInfo_GetMetaObjectFunction(void);
extern "C" void *beSelectCtrlInfoRamData_GetMetaObject(void);
extern "C" int beSelectCtrlInfoRamData_GetVTable(void);
extern "C" void beSelectCtrlInfoRamData_EnsureRegistered(void);
extern "C" void *beSelectCtrlInfoRamData_Register(void);
extern "C" void beSelectCtrlInfoRamData_GetMetaObjectFunction(void);
extern "C" int ObjectPointerList_FindIndex(...);
extern "C" int igMetaObject_FinalizeAndReplaceField(...);
extern "C" void **igMetaObject_FindFieldByName(...);
extern "C" void beSelectCtrlInfoRamData_InitFields(void);
extern "C" void beSelectCtrlInfoWork_Create(int arg0);
extern "C" igMetaObject *beSelectCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" void *beSelectCtrlInfoWork_GetMetaObject(void);
extern "C" int beSelectCtrlInfoWork_GetVTable(void);
extern "C" void beSelectCtrlInfoWork_EnsureRegistered(void);
extern "C" void *beSelectCtrlInfoWork_Register(void);
extern "C" void beSelectCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" int igBoolList_GetOrCreateMetaObject(void);
extern "C" void beSelectCtrlInfoWork_InitFields(void);
extern "C" igMetaEnum *beSelectCtrl_GetMessageEnum(void);
extern "C" void beSelectCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beSelectCtrl_GetOrCreateMetaObject(void);
extern "C" void *beSelectCtrl_GetMetaObject(void);
extern "C" int beSelectCtrl_GetVTable(void);
extern "C" void beSelectCtrl_EnsureRegistered(void);
extern "C" void *beSelectCtrl_Register(void);
extern "C" void beSelectCtrl_GetMetaObjectFunction(void);
extern "C" void beSelectCtrl_InitFields(void);
extern "C" void *beSeInfo_GetMetaObject(void);
extern "C" int beSeInfo_GetVTable(void);
extern "C" void beSeInfo_EnsureRegistered(void);
extern "C" void *beSeInfo_Register(void);
extern "C" void beSeInfo_GetMetaObjectFunction(void);
extern "C" void *beSeInfoData_GetMetaObject(void);
extern "C" int beSeInfoData_GetVTable(void);
extern "C" void beSeInfoData_EnsureRegistered(void);
extern "C" void *beSeInfoData_Register(void);
extern "C" void beSeInfoData_GetMetaObjectFunction(void);
extern "C" void beSeInfoData_InitFields(void);
extern "C" igMetaObject *beSeDataList_GetOrCreateMetaObject(void);
extern "C" int beSeDataList_GetVTable(void);
extern "C" void beSeDataList_EnsureRegistered(void);
extern "C" void *beSeDataList_Register(void);
extern "C" void beSeDataList_GetMetaObjectFunction(void);
extern "C" int beSeData_GetVTable(void);
extern "C" void beSeData_EnsureRegistered(void);
extern "C" void *beSeData_Register(void);
extern "C" void beSeData_GetMetaObjectFunction(void);
extern "C" void beSeData_InitFields(void);
extern "C" void beSeCtl_CreateInstance(int arg0);
extern "C" igMetaObject *beSeCtl_GetOrCreateMetaObject(void);
extern "C" int beSeCtl_GetVTable(void);
extern "C" void beSeCtl_EnsureRegistered(void);
extern "C" void *beSeCtl_Register(void);
extern "C" void beSeCtl_GetMetaObjectFunction(void);
extern "C" void beSeCtl_InitFields(void);
extern "C" int beSaveUtilInfoRam_GetVTable(void);
extern "C" void beSaveUtilInfoRam_EnsureRegistered(void);
extern "C" void *beSaveUtilInfoRam_Register(void);
extern "C" void beSaveUtilInfoRam_GetMetaObjectFunction(void);
extern "C" void beSaveUtilInfoRam_InitFields(void);
extern "C" void *beSaveUtilInfo_GetMetaObject(void);
extern "C" int beSaveUtilInfo_GetVTable(void);
extern "C" void beSaveUtilInfo_EnsureRegistered(void);
extern "C" void *beSaveUtilInfo_Register(void);
extern "C" void beSaveUtilInfo_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_00346c20(void);
extern "C" void beSaveUtil_CreateInstance(int arg0);
extern "C" igMetaObject *beSaveUtil_GetOrCreateMetaObject(void);
extern "C" void *beSaveUtil_GetMetaObject(void);
extern "C" int beSaveUtil_GetVTable(void);
extern "C" void **FUN_00346df0(void **arg0, int arg1);
extern "C" void **FUN_00346e70(void **arg0, short arg1);
extern "C" void beSaveUtil_EnsureRegistered(void);
extern "C" void *beSaveUtil_Register(void);
extern "C" void beSaveUtil_GetMetaObjectFunction(void);
extern "C" void beSaveUtil_InitFields(void);
extern "C" void *beSvPlatDataPC_GetMetaObject(void);
extern "C" int beSvPlatDataPC_GetVTable(void);
extern "C" void beSvPlatDataPC_EnsureRegistered(void);
extern "C" void *beSvPlatDataPC_Register(void);
extern "C" void beSvPlatDataPC_GetMetaObjectFunction(void);
extern "C" igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void);
extern "C" void *beSvPlatDataXbox_GetMetaObject(void);
extern "C" int beSvPlatDataXbox_GetVTable(void);
extern "C" void beSvPlatDataXbox_EnsureRegistered(void);
extern "C" void *beSvPlatDataXbox_Register(void);
extern "C" void beSvPlatDataXbox_GetMetaObjectFunction(void);
extern "C" void beSvPlatDataXbox_InitFields(void);
extern "C" igMetaObject *beXboxImage24k_GetOrCreateMetaObject(void);
extern "C" void *beXboxImage24k_GetMetaObject(void);
extern "C" int beXboxImage24k_GetVTable(void);
extern "C" void beXboxImage24k_EnsureRegistered(void);
extern "C" void *beXboxImage24k_Register(void);
extern "C" void beXboxImage24k_GetMetaObjectFunction(void);
extern "C" void beXboxImage24k_InitFields(void);
extern "C" void *beSvPlatDataPS2_GetMetaObject(void);
extern "C" int igSmartPointer_igObjectList_Destruct(...);
extern "C" int beSvPlatDataPS2_GetVTable(void);
extern "C" void beSvPlatDataPS2_EnsureRegistered(void);
extern "C" void *beSvPlatDataPS2_Register(void);
extern "C" void beSvPlatDataPS2_GetMetaObjectFunction(void);
extern "C" int igObjectList_GetOrCreateMetaObject(...);
extern "C" void beSvPlatDataPS2_InitFields(void);
extern "C" void *beSvPs2McImage128k_GetMetaObject(void);
extern "C" int beSvPs2McImage128k_GetVTable(void);
extern "C" void beSvPs2McImage128k_EnsureRegistered(void);
extern "C" void *beSvPs2McImage128k_Register(void);
extern "C" void beSvPs2McImage128k_GetMetaObjectFunction(void);
extern "C" void beSvPs2McImage128k_InitFields(void);
extern "C" void *beSvPlatDataGC_GetMetaObject(void);
extern "C" int beSvPlatDataGC_GetVTable(void);
extern "C" void beSvPlatDataGC_EnsureRegistered(void);
extern "C" void *beSvPlatDataGC_Register(void);
extern "C" void beSvPlatDataGC_GetMetaObjectFunction(void);
extern "C" void beSvPlatDataGC_InitFields(void);
extern "C" void beSvConnectCheck_Create(int arg0);
extern "C" igMetaObject *beSvConnectCheck_GetOrCreateMetaObject(void);
extern "C" void *beSvConnectCheck_GetMetaObject(void);
extern "C" int beSvConnectCheck_GetVTable(void);
extern "C" void beSvConnectCheck_EnsureRegistered(void);
extern "C" void *beSvConnectCheck_Register(void);
extern "C" void beSvConnectCheck_GetMetaObjectFunction(void);
extern "C" igMetaObject *beSaveApi_GetPublishedMetaObject(void);
extern "C" void beSvEndApi_Create(int arg0);
extern "C" void *beSvEndApi_GetMetaObject(void);
extern "C" int beSvEndApi_GetVTable(void);
extern "C" void beSvEndApi_EnsureRegistered(void);
extern "C" void *beSvEndApi_Register(void);
extern "C" void beSvEndApi_GetMetaObjectFunction(void);
extern "C" void beSvEndApi_InitFields(void);
extern "C" void beSvStartApi_Create(int arg0);
extern "C" int beSvStartApi_GetVTable(void);
extern "C" void beSvStartApi_EnsureRegistered(void);
extern "C" void *beSvStartApi_Register(void);
extern "C" void beSvStartApi_GetMetaObjectFunction(void);
extern "C" void beSvStartApi_InitFields(void);
extern "C" void beSvGetFreeSizeApi_Create(int arg0);
extern "C" int beSvGetFreeSizeApi_GetVTable(void);
extern "C" void beSvGetFreeSizeApi_EnsureRegistered(void);
extern "C" void *beSvGetFreeSizeApi_Register(void);
extern "C" void beSvGetFreeSizeApi_GetMetaObjectFunction(void);
extern "C" void beSvGetFreeSizeApi_InitFields(void);
extern "C" void beSvWriteMediaApi_Create(int arg0);
extern "C" int beSvWriteMediaApi_GetVTable(void);
extern "C" void **FUN_00349080(void **arg0, long long arg1);
extern "C" void beSvWriteMediaApi_EnsureRegistered(void);
extern "C" void *beSvWriteMediaApi_Register(void);
extern "C" void beSvWriteMediaApi_GetMetaObjectFunction(void);
extern "C" void beSvWriteMediaApi_InitFields(void);
extern "C" void beSvReadMediaApi_Create(int arg0);
extern "C" int beSvReadMediaApi_GetVTable(void);
extern "C" void beSvReadMediaApi_EnsureRegistered(void);
extern "C" void *beSvReadMediaApi_Register(void);
extern "C" void beSvReadMediaApi_GetMetaObjectFunction(void);
extern "C" void beSvReadMediaApi_InitFields(void);
extern "C" void beSvUseCheckApi_Create(int arg0);
extern "C" void *beSvUseCheckApi_GetMetaObject(void);
extern "C" int beSvUseCheckApi_GetVTable(void);
extern "C" void beSvUseCheckApi_EnsureRegistered(void);
extern "C" void *beSvUseCheckApi_Register(void);
extern "C" void beSvUseCheckApi_GetMetaObjectFunction(void);
extern "C" void beSvFormatApi_Create(int arg0);
extern "C" void *beSvFormatApi_GetMetaObject(void);
extern "C" int beSvFormatApi_GetVTable(void);
extern "C" void beSvFormatApi_EnsureRegistered(void);
extern "C" void *beSvFormatApi_Register(void);
extern "C" void beSvFormatApi_GetMetaObjectFunction(void);
extern "C" void beSvFileFindApi_Create(int arg0);
extern "C" void *beSvFileFindApi_GetMetaObject(void);
extern "C" int beSvFileFindApi_GetVTable(void);
extern "C" void beSvFileFindApi_EnsureRegistered(void);
extern "C" void *beSvFileFindApi_Register(void);
extern "C" void beSvFileFindApi_GetMetaObjectFunction(void);
extern "C" void beSvFileMakeApi_Create(int arg0);
extern "C" void *beSvFileMakeApi_GetMetaObject(void);
extern "C" int beSvFileMakeApi_GetVTable(void);
extern "C" void beSvFileMakeApi_EnsureRegistered(void);
extern "C" void *beSvFileMakeApi_Register(void);
extern "C" void beSvFileMakeApi_GetMetaObjectFunction(void);
extern "C" void beSvFileMakeApi_InitFields(void);
extern "C" igMetaObject *beSaveApi_GetOrCreateMetaObject(void);
extern "C" void *beSaveApi_GetMetaObject(void);
extern "C" void beSaveApi_EnsureRegistered(void);
extern "C" void *beSaveApi_Register(void);
extern "C" void beSaveApi_GetMetaObjectFunction(void);
extern "C" void beSaveApi_InitFields(void);
extern "C" igMetaObject *beSvPlatBaseData_GetOrCreateMetaObject(void);
extern "C" void *beSvPlatBaseData_GetMetaObject(void);
extern "C" int beSvPlatBaseData_GetVTable(void);
extern "C" void beSvPlatBaseData_EnsureRegistered(void);
extern "C" void *beSvPlatBaseData_Register(void);
extern "C" void beSvPlatBaseData_GetMetaObjectFunction(void);
extern "C" void beSvPlatBaseData_InitFields(void);
extern "C" igMetaObject *beSvSlotDataList_GetOrCreateMetaObject(void);
extern "C" void *beSvSlotDataList_GetMetaObject(void);
extern "C" int beSvSlotDataList_GetVTable(void);
extern "C" void beSvSlotDataList_EnsureRegistered(void);
extern "C" void *beSvSlotDataList_Register(void);
extern "C" void beSvSlotDataList_GetMetaObjectFunction(void);
extern "C" void *beSvSlotPS2_GetMetaObject(void);
extern "C" int beSvSlotPS2_GetVTable(void);
extern "C" void beSvSlotPS2_EnsureRegistered(void);
extern "C" void *beSvSlotPS2_Register(void);
extern "C" void beSvSlotPS2_GetMetaObjectFunction(void);
extern "C" igMetaObject *beSvSlotData_GetPublishedMetaObject(void);
extern "C" void *beSvSlotGC_GetMetaObject(void);
extern "C" int beSvSlotGC_GetVTable(void);
extern "C" void beSvSlotGC_EnsureRegistered(void);
extern "C" void *beSvSlotGC_Register(void);
extern "C" void beSvSlotGC_GetMetaObjectFunction(void);
extern "C" void *beSvSlotXbox_GetMetaObject(void);
extern "C" int beSvSlotXbox_GetVTable(void);
extern "C" void beSvSlotXbox_EnsureRegistered(void);
extern "C" void *beSvSlotXbox_Register(void);
extern "C" void beSvSlotXbox_GetMetaObjectFunction(void);
extern "C" void beSvSlotXbox_InitFields(void);
extern "C" void beSvSlotData_EnsureRegistered(void);
extern "C" void *beSvSlotData_Register(void);
extern "C" void beSvSlotData_GetMetaObjectFunction(void);
extern "C" void beSvSlotData_InitFields(void);
extern "C" void beSaveMemoryObj_CreateInstance(int arg0);
extern "C" igMetaObject *beSaveMemoryObj_GetOrCreateMetaObject(void);
extern "C" int beSaveMemoryObj_GetVTable(void);
extern "C" void beSaveMemoryObj_EnsureRegistered(void);
extern "C" void *beSaveMemoryObj_Register(void);
extern "C" void beSaveMemoryObj_GetMetaObjectFunction(void);
extern "C" void beSaveMemoryObj_InitFields(void);
extern "C" igMetaObject *beSaveDataDeliver_GetOrCreateMetaObject(void);
extern "C" int beSaveDataDeliver_GetVTable(void);
extern "C" void beSaveDataDeliver_EnsureRegistered(void);
extern "C" void *beSaveDataDeliver_Register(void);
extern "C" void beSaveDataDeliver_GetMetaObjectFunction(void);
extern "C" void beSaveDataDeliver_InitFields(void);
extern "C" igMetaObject *beSvDeliver_GetOrCreateMetaObject(void);
extern "C" int beSvDeliver_GetVTable(void);
extern "C" void beSvDeliver_EnsureRegistered(void);
extern "C" void *beSvDeliver_Register(void);
extern "C" void beSvDeliver_GetMetaObjectFunction(void);
extern "C" int igCharMetaField_SetDefaultValue(void *, int);
extern "C" void beSvDeliver_InitFields(void);
extern "C" void *beResetNode_GetMetaObject(void);
extern "C" int FUN_00195a90(...);
extern "C" int beResetNode_GetVTable(void);
extern "C" void beResetNode_EnsureRegistered(void);
extern "C" void *igGroup_Register(void);
extern "C" void *beResetNode_Register(void);
extern "C" void beResetNode_GetMetaObjectFunction(void);
extern "C" void beResetNode_InitFields(void);
extern "C" void FUN_0039c8c0(void);
extern "C" void FUN_0034b690(void);
extern "C" void *bePoint01Info_GetMetaObject(void);
extern "C" int bePoint01Info_GetVTable(void);
extern "C" void bePoint01Info_EnsureRegistered(void);
extern "C" void *bePoint01Info_Register(void);
extern "C" void bePoint01Info_GetMetaObjectFunction(void);
extern "C" void bePoint01Info_InitFields(void);
extern "C" igMetaEnum *FUN_0034b980(void);
extern "C" void bePoint01_CreateInstance(int arg0);
extern "C" igMetaObject *bePoint01_GetOrCreateMetaObject(void);
extern "C" void *bePoint01_GetMetaObject(void);
extern "C" int bePoint01_GetVTable(void);
extern "C" void bePoint01_EnsureRegistered(void);
extern "C" void *bePoint01_Register(void);
extern "C" void bePoint01_GetMetaObjectFunction(void);
extern "C" void bePoint01_InitFields(void);
extern "C" void *beParticleCtrl2InfoRam_GetMetaObject(void);
extern "C" int FUN_001a7580(int *, int);
extern "C" int beParticleCtrl2InfoRam_GetVTable(void);
extern "C" void **FUN_0034bdc0(void **arg0, short arg1);
extern "C" void beParticleCtrl2InfoRam_EnsureRegistered(void);
extern "C" void *beParticleCtrl2InfoRam_Register(void);
extern "C" void beParticleCtrl2InfoRam_GetMetaObjectFunction(void);
extern "C" int igTransform_GetOrCreateMetaObject(void);
extern "C" void beParticleCtrl2InfoRam_InitFields(void);
extern "C" void beParticleCtrl2InfoWork_Create(int arg0);
extern "C" igMetaObject *beParticleCtrl2InfoWork_GetOrCreateMetaObject(void);
extern "C" void *beParticleCtrl2InfoWork_GetMetaObject(void);
extern "C" int beParticleCtrl2InfoWork_GetVTable(void);
extern "C" void **FUN_0034c1b0(void **arg0, short arg1);
extern "C" void beParticleCtrl2InfoWork_EnsureRegistered(void);
extern "C" void *beParticleCtrl2InfoWork_Register(void);
extern "C" void beParticleCtrl2InfoWork_GetMetaObjectFunction(void);
extern "C" void beParticleCtrl2InfoWork_InitFields(void);
extern "C" void *beParticleCtrl2Info_GetMetaObject(void);
extern "C" int beParticleCtrl2Info_GetVTable(void);
extern "C" void beParticleCtrl2Info_EnsureRegistered(void);
extern "C" void *beParticleCtrl2Info_Register(void);
extern "C" void beParticleCtrl2Info_GetMetaObjectFunction(void);
extern "C" void beParticleCtrl2Info_InitFields(void);
extern "C" igMetaEnum *FUN_0034c5d0(void);
extern "C" void beParticleCtrl2_CreateInstance(int arg0);
extern "C" igMetaObject *beParticleCtrl2_GetOrCreateMetaObject(void);
extern "C" void *beParticleCtrl2_GetMetaObject(void);
extern "C" int beParticleCtrl2_GetVTable(void);
extern "C" void beParticleCtrl2_EnsureRegistered(void);
extern "C" void *beParticleCtrl2_Register(void);
extern "C" void beParticleCtrl2_GetMetaObjectFunction(void);
extern "C" void bePadManager_CreateInstance(int arg0);
extern "C" igMetaObject *bePadManager_GetOrCreateMetaObject(void);
extern "C" void *bePadManager_GetMetaObject(void);
extern "C" int bePadManager_GetVTable(void);
extern "C" void bePadManager_EnsureRegistered(void);
extern "C" void *bePadManager_Register(void);
extern "C" void bePadManager_GetMetaObjectFunction(void);
extern "C" void bePadManager_InitFields(void);
extern "C" igMetaObject *bePadDataList_GetOrCreateMetaObject(void);
extern "C" void *bePadDataList_GetMetaObject(void);
extern "C" int bePadDataList_GetVTable(void);
extern "C" void bePadDataList_EnsureRegistered(void);
extern "C" void *bePadDataList_Register(void);
extern "C" void bePadDataList_GetMetaObjectFunction(void);
extern "C" void bePadData_Create(int arg0);
extern "C" void *bePadData_GetMetaObject(void);
extern "C" int bePadData_GetVTable(void);
extern "C" void bePadData_EnsureRegistered(void);
extern "C" void *bePadData_Register(void);
extern "C" void bePadData_GetMetaObjectFunction(void);
extern "C" int FUN_0018e2f0(int, int *);
extern "C" void bePadData_InitFields(void);
extern "C" int igInfo_Destroy(...);
extern "C" int beOptInfo_GetVTable(void);
extern "C" void beOptInfo_EnsureRegistered(void);
extern "C" void *igInfo_Register(void);
extern "C" void *beOptInfo_Register(void);
extern "C" void beOptInfo_GetMetaObjectFunction(void);
extern "C" void beOptInfo_InitFields(void);
extern "C" void beNumberCtrlInfoWork_Create(int arg0);
extern "C" igMetaObject *beNumberCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" int beNumberCtrlInfoWork_GetVTable(void);
extern "C" void beNumberCtrlInfoWork_EnsureRegistered(void);
extern "C" void *beNumberCtrlInfoWork_Register(void);
extern "C" void beNumberCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" void beNumberCtrlInfoWork_InitFields(void);
extern "C" int FUN_001971e0(int *, int);
extern "C" int beNumberCtrlInfoRam_GetVTable(void);
extern "C" void **FUN_0034d640(void **arg0, long long arg1);
extern "C" void **igSmartPointer_beNumberCtrlInfoWork_Destruct(void **arg0, int arg1);
extern "C" void beNumberCtrlInfoRam_EnsureRegistered(void);
extern "C" void *beNumberCtrlInfoRam_Register(void);
extern "C" void beNumberCtrlInfoRam_GetMetaObjectFunction(void);
extern "C" int igGeometry_GetOrCreateMetaObject(void);
extern "C" void beNumberCtrlInfoRam_InitFields(void);
extern "C" igMetaObject *beNumVerDataList_GetOrCreateMetaObject(void);
extern "C" int beNumVerDataList_GetVTable(void);
extern "C" void beNumVerDataList_EnsureRegistered(void);
extern "C" void *beNumVerDataList_Register(void);
extern "C" void beNumVerDataList_GetMetaObjectFunction(void);
extern "C" void *beNumVerData_GetMetaObject(void);
extern "C" int beNumVerData_GetVTable(void);
extern "C" void beNumVerData_EnsureRegistered(void);
extern "C" void *beNumVerData_Register(void);
extern "C" void beNumVerData_GetMetaObjectFunction(void);
extern "C" void beNumVerData_InitFields(void);
extern "C" igMetaObject *beNumVerInsideDataList_GetOrCreateMetaObject(void);
extern "C" void *beNumVerInsideDataList_GetMetaObject(void);
extern "C" int beNumVerInsideDataList_GetVTable(void);
extern "C" void beNumVerInsideDataList_EnsureRegistered(void);
extern "C" void *beNumVerInsideDataList_Register(void);
extern "C" void beNumVerInsideDataList_GetMetaObjectFunction(void);
extern "C" int beNumVerInsideData_Create(int arg0);
extern "C" void *beNumVerInsideData_GetMetaObject(void);
extern "C" int beNumVerInsideData_GetVTable(void);
extern "C" void beNumVerInsideData_EnsureRegistered(void);
extern "C" void *beNumVerInsideData_Register(void);
extern "C" void beNumVerInsideData_GetMetaObjectFunction(void);
extern "C" void beNumVerInsideData_InitFields(void);
extern "C" void *beNumberCtrlInfoList_GetMetaObject(void);
extern "C" int beNumberCtrlInfoList_GetVTable(void);
extern "C" void beNumberCtrlInfoList_EnsureRegistered(void);
extern "C" void *beNumberCtrlInfoList_Register(void);
extern "C" void beNumberCtrlInfoList_GetMetaObjectFunction(void);
extern "C" void *beNumberCtrlInfo_GetMetaObject(void);
extern "C" int beNumberCtrlInfo_GetVTable(void);
extern "C" void beNumberCtrlInfo_EnsureRegistered(void);
extern "C" void *beNumberCtrlInfo_Register(void);
extern "C" void beNumberCtrlInfo_GetMetaObjectFunction(void);
extern "C" igMetaEnum *beNumberCtrl_GetMessageEnum(void);
extern "C" void beNumberCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beNumberCtrl_GetOrCreateMetaObject(void);
extern "C" void *beNumberCtrl_GetMetaObject(void);
extern "C" int beNumberCtrl_GetVTable(void);
extern "C" void beNumberCtrl_EnsureRegistered(void);
extern "C" void *beNumberCtrl_Register(void);
extern "C" void beNumberCtrl_GetMetaObjectFunction(void);
extern "C" void *beLoadingNode_ResolveMetaObject(void);
extern "C" int beLoadingNode_GetVTable(void);
extern "C" int FUN_00195970(int **, int);
extern "C" int **FUN_0034e690(int **arg0, long long arg1);
extern "C" void beLoadingNode_EnsureRegistered(void);
extern "C" void *beLoadingNode_Register(void);
extern "C" void beLoadingNode_GetMetaObject(void);
extern "C" igMetaObject *beNodeAnim_GetPublishedMetaObject(void);
extern "C" void beLoadingNode_InitFields(void);
extern "C" void beLoadingNode_RegisterTraversalFunction(void);
extern "C" void FUN_0034e850(void);
extern "C" void *beNodeAnim_ResolveMetaObject(void);
extern "C" int beNodeAnim_GetVTable(void);
extern "C" void beNodeAnim_EnsureRegistered(void);
extern "C" void *beNodeAnim_Register(void);
extern "C" void beNodeAnim_GetMetaObject(void);
extern "C" int igLongMetaField_SetDefault(...);
extern "C" void beNodeAnim_InitFields(void);
extern "C" void beNodeAnim_RegisterTraversalFunction(void);
extern "C" void FUN_0034eaf0(void);
extern "C" void *beMovieInfo_GetMetaObject(void);
extern "C" int beMovieInfo_GetVTable(void);
extern "C" void beMovieInfo_EnsureRegistered(void);
extern "C" void *beMovieInfo_Register(void);
extern "C" void beMovieInfo_GetMetaObjectFunction(void);
extern "C" void *beMovieInfoData_GetMetaObject(void);
extern "C" int FUN_001d3650(int *, int);
extern "C" int FUN_00130720(...);
extern "C" int beMovieInfoData_GetVTable(void);
extern "C" void beMovieInfoData_EnsureRegistered(void);
extern "C" void *beMovieInfoData_Register(void);
extern "C" void beMovieInfoData_GetMetaObjectFunction(void);
extern "C" int igSceneInfo_GetOrCreateMetaObject(void);
extern "C" void beMovieInfoData_InitFields(void);
extern "C" igMetaEnum *FUN_0034eed0(void);
extern "C" void beMovie_CreateInstance(int arg0);
extern "C" igMetaObject *beMovie_GetOrCreateMetaObject(void);
extern "C" int FUN_003369f0(int *, int);
extern "C" int beMovie_GetVTable(void);
extern "C" void beMovie_EnsureRegistered(void);
extern "C" void *beMovie_Register(void);
extern "C" void beMovie_GetMetaObjectFunction(void);
extern "C" int igMovieManager_GetOrCreateMetaObject(void);
extern "C" void beMovie_InitFields(void);
extern "C" igMetaObject *beModelCtrlSubCom_GetOrCreateMetaObject(void);
extern "C" int beModelCtrlSubCom_GetVTable(void);
extern "C" void beModelCtrlSubCom_EnsureRegistered(void);
extern "C" void *beModelCtrlSubCom_Register(void);
extern "C" void beModelCtrlSubCom_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSubCom_InitFields(void);
extern "C" void beModelCtrlSCSound_Create(int arg0);
extern "C" int beModelCtrlSCSound_GetVTable(void);
extern "C" void beModelCtrlSCSound_EnsureRegistered(void);
extern "C" void *beModelCtrlSCSound_Register(void);
extern "C" void beModelCtrlSCSound_GetMetaObjectFunction(void);
extern "C" igMetaObject *beModelCtrlSubComBase_GetPublishedMetaObject(void);
extern "C" void beModelCtrlSCSound_InitFields(void);
extern "C" void beModelCtrlSCHitBox_Create(int arg0);
extern "C" int beModelCtrlSCHitBox_GetVTable(void);
extern "C" void beModelCtrlSCHitBox_EnsureRegistered(void);
extern "C" void *beModelCtrlSCHitBox_Register(void);
extern "C" void beModelCtrlSCHitBox_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSCHitBox_InitFields(void);
extern "C" void beModelCtrlSCEffect_Create(int arg0);
extern "C" void *beModelCtrlSCEffect_GetMetaObject(void);
extern "C" int beModelCtrlSCEffect_GetVTable(void);
extern "C" void beModelCtrlSCEffect_EnsureRegistered(void);
extern "C" void *beModelCtrlSCEffect_Register(void);
extern "C" void beModelCtrlSCEffect_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSCEffect_InitFields(void);
extern "C" void *beModelCtrlSubComBase_GetMetaObject(void);
extern "C" void beModelCtrlSubComBase_EnsureRegistered(void);
extern "C" void *beModelCtrlSubComBase_Register(void);
extern "C" void beModelCtrlSubComBase_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSubComBase_InitFields(void);
extern "C" void beModelCtrlNode2_Create(int arg0);
extern "C" igMetaObject *beModelCtrlNode2_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlNode2_ResolveMetaObject(void);
extern "C" int beModelCtrlNode2_GetVTable(void);
extern "C" void beModelCtrlNode2_EnsureRegistered(void);
extern "C" void *beModelCtrlNode2_Register(void);
extern "C" void beModelCtrlNode2_GetMetaObject(void);
extern "C" int igAttrList_GetOrCreateMetaObject(void);
extern "C" void beModelCtrlNode2_InitFields(void);
extern "C" void beModelCtrlNode2_RegisterTraversalFunction(void);
extern "C" void FUN_00350000(void);
extern "C" void beModelCtrlInfoWork_Create(int arg0);
extern "C" igMetaObject *beModelCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoWork_GetMetaObject(void);
extern "C" void **igSmartPointer_beDataObjInt_Destruct(void **arg0, short arg1);
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
extern "C" void beModelCtrlInfoWork_EnsureRegistered(void);
extern "C" int beModelCtrlInfoWork_GetVTable(void);
extern "C" void *beModelCtrlInfoWork_Register(void);
extern "C" void beModelCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" int igAABox_GetOrCreateMetaObject(void);
extern "C" void beModelCtrlInfoWork_InitFields(void);
extern "C" void beModelCtrlInfoRideOn4_Create(int arg0);
extern "C" void *beModelCtrlInfoRideOn4_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn4_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn4_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoRideOn4_Register(void);
extern "C" void beModelCtrlInfoRideOn4_GetMetaObjectFunction(void);
extern "C" igMetaObject *beModelCtrlInfoRideOn_GetPublishedMetaObject(void);
extern "C" void beModelCtrlInfoRideOn4_InitFields(void);
extern "C" void beModelCtrlInfoRideOn3_Create(int arg0);
extern "C" void *beModelCtrlInfoRideOn3_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn3_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn3_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoRideOn3_Register(void);
extern "C" void beModelCtrlInfoRideOn3_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRideOn3_InitFields(void);
extern "C" void beModelCtrlInfoRideOn2_Create(int arg0);
extern "C" void *beModelCtrlInfoRideOn2_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn2_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn2_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoRideOn2_Register(void);
extern "C" void beModelCtrlInfoRideOn2_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRideOn2_InitFields(void);
extern "C" void beModelCtrlInfoRideOn_Create(int arg0);
extern "C" igMetaObject *beModelCtrlInfoRideOn_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoRideOn_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoRideOn_Register(void);
extern "C" void beModelCtrlInfoRideOn_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRideOn_InitFields(void);
extern "C" void beModelCtrlInfoAI_Create(int arg0);
extern "C" igMetaObject *beModelCtrlInfoAI_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoAI_GetMetaObject(void);
extern "C" int beModelCtrlInfoAI_GetVTable(void);
extern "C" void beModelCtrlInfoAI_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoAI_Register(void);
extern "C" void beModelCtrlInfoAI_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoAI_InitFields(void);
extern "C" void beModelCtrlInfoHitBody_Create(int arg0);
extern "C" igMetaObject *beModelCtrlInfoHitBody_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoHitBody_GetMetaObject(void);
extern "C" int beModelCtrlInfoHitBody_GetVTable(void);
extern "C" void beModelCtrlInfoHitBody_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoHitBody_Register(void);
extern "C" void beModelCtrlInfoHitBody_GetMetaObjectFunction(void);
extern "C" int igAABoxList_GetOrCreateMetaObject(...);
extern "C" void beModelCtrlInfoHitBody_InitFields(void);
extern "C" igMetaObject *beModelCtrlMoveObjectList_GetOrCreateMetaObject(void);
extern "C" int beModelCtrlMoveObjectList_GetVTable(void);
extern "C" void beModelCtrlMoveObjectList_EnsureRegistered(void);
extern "C" void *beModelCtrlMoveObjectList_Register(void);
extern "C" void beModelCtrlMoveObjectList_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMoveObject_Create(int arg0);
extern "C" int beModelCtrlMoveObject_GetVTable(void);
extern "C" void beModelCtrlMoveObject_EnsureRegistered(void);
extern "C" void *beModelCtrlMoveObject_Register(void);
extern "C" void beModelCtrlMoveObject_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMoveObject_InitFields(void);
extern "C" int beModelCtrlInfoList_GetVTable(void);
extern "C" void beModelCtrlInfoList_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoList_Register(void);
extern "C" void beModelCtrlInfoList_GetMetaObjectFunction(void);
extern "C" int beModelCtrlInfo_GetVTable(void);
extern "C" void beModelCtrlInfo_EnsureRegistered(void);
extern "C" void *beModelCtrlInfo_Register(void);
extern "C" void beModelCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfo_InitFields(void);
extern "C" void *beModelCtrlInfoRamData_GetMetaObject(void);
extern "C" int beModelCtrlInfoRamData_GetVTable(void);
extern "C" void beModelCtrlInfoRamData_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoRamData_Register(void);
extern "C" void beModelCtrlInfoRamData_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRamData_InitFields(void);
extern "C" igMetaObject *beModelCtrlInfoDataTrc_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoDataTrc_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataTrc_GetVTable(void);
extern "C" void beModelCtrlInfoDataTrc_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoDataTrc_Register(void);
extern "C" void beModelCtrlInfoDataTrc_GetMetaObjectFunction(void);
extern "C" int igTransformRecorder_GetOrCreateMetaObject(...);
extern "C" void beModelCtrlInfoDataTrc_InitFields(void);
extern "C" void *beModelCtrlInfoDataSeq_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataSeq_GetVTable(void);
extern "C" void beModelCtrlInfoDataSeq_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoDataSeq_Register(void);
extern "C" void beModelCtrlInfoDataSeq_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataSeq_InitFields(void);
extern "C" void *beModelCtrlInfoDataHit_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataHit_GetVTable(void);
extern "C" void beModelCtrlInfoDataHit_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoDataHit_Register(void);
extern "C" void beModelCtrlInfoDataHit_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataHit_InitFields(void);
extern "C" void *beModelCtrlInfoDataAIH_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataAIH_GetVTable(void);
extern "C" void beModelCtrlInfoDataAIH_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoDataAIH_Register(void);
extern "C" void beModelCtrlInfoDataAIH_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataAIH_InitFields(void);
extern "C" void *beModelCtrlInfoDataAIM_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataAIM_GetVTable(void);
extern "C" void beModelCtrlInfoDataAIM_EnsureRegistered(void);
extern "C" void *beModelCtrlInfoDataAIM_Register(void);
extern "C" void beModelCtrlInfoDataAIM_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataAIM_InitFields(void);
extern "C" igMetaObject *beModelCtrlAIMapList_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlAIMapList_GetMetaObject(void);
extern "C" int beModelCtrlAIMapList_GetVTable(void);
extern "C" void beModelCtrlAIMapList_EnsureRegistered(void);
extern "C" void *beModelCtrlAIMapList_Register(void);
extern "C" void beModelCtrlAIMapList_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlAIMap_GetMetaObject(void);
extern "C" int FUN_00131bc0(...);
extern "C" int beModelCtrlAIMap_GetVTable(void);
extern "C" void beModelCtrlAIMap_EnsureRegistered(void);
extern "C" void *beModelCtrlAIMap_Register(void);
extern "C" void beModelCtrlAIMap_GetMetaObjectFunction(void);
extern "C" void beModelCtrlAIMap_InitFields(void);
extern "C" igMetaObject *beModelCtrlAIDataList_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlAIDataList_GetMetaObject(void);
extern "C" int beModelCtrlAIDataList_GetVTable(void);
extern "C" void beModelCtrlAIDataList_EnsureRegistered(void);
extern "C" void *beModelCtrlAIDataList_Register(void);
extern "C" void beModelCtrlAIDataList_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlAIData_GetMetaObject(void);
extern "C" int beModelCtrlAIData_GetVTable(void);
extern "C" void beModelCtrlAIData_EnsureRegistered(void);
extern "C" void *beModelCtrlAIData_Register(void);
extern "C" void beModelCtrlAIData_GetMetaObjectFunction(void);
extern "C" void beModelCtrlAIData_InitFields(void);
extern "C" void beModelCtrlHITBOX_Create(int arg0);
extern "C" int beModelCtrlHITBOX_GetVTable(void);
extern "C" void beModelCtrlHITBOX_EnsureRegistered(void);
extern "C" void *beModelCtrlHITBOX_Register(void);
extern "C" void beModelCtrlHITBOX_GetMetaObjectFunction(void);
extern "C" void beModelCtrlHITBOX_InitFields(void);
extern "C" int beModelCtrlMUTEKI_GetVTable(void);
extern "C" void beModelCtrlMUTEKI_EnsureRegistered(void);
extern "C" void *beModelCtrlMUTEKI_Register(void);
extern "C" void beModelCtrlMUTEKI_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMUTEKI_InitFields(void);
extern "C" int beModelCtrlAIMAP_GetVTable(void);
extern "C" void beModelCtrlAIMAP_EnsureRegistered(void);
extern "C" void *beModelCtrlAIMAP_Register(void);
extern "C" void beModelCtrlAIMAP_GetMetaObjectFunction(void);
extern "C" int beModelCtrlWCHECK_GetVTable(void);
extern "C" void beModelCtrlWCHECK_EnsureRegistered(void);
extern "C" void *beModelCtrlWCHECK_Register(void);
extern "C" void beModelCtrlWCHECK_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlPDMOVE_GetMetaObject(void);
extern "C" int beModelCtrlPDMOVE_GetVTable(void);
extern "C" void beModelCtrlPDMOVE_EnsureRegistered(void);
extern "C" void *beModelCtrlPDMOVE_Register(void);
extern "C" void beModelCtrlPDMOVE_GetMetaObjectFunction(void);
extern "C" void beModelCtrlPDMOVE_InitFields(void);
extern "C" void *beModelCtrlMOVERL_GetMetaObject(void);
extern "C" int beModelCtrlMOVERL_GetVTable(void);
extern "C" void beModelCtrlMOVERL_EnsureRegistered(void);
extern "C" void *beModelCtrlMOVERL_Register(void);
extern "C" void beModelCtrlMOVERL_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMOVERL_InitFields(void);
extern "C" void *beModelCtrlMOVEEX_GetMetaObject(void);
extern "C" int beModelCtrlMOVEEX_GetVTable(void);
extern "C" void beModelCtrlMOVEEX_EnsureRegistered(void);
extern "C" void *beModelCtrlMOVEEX_Register(void);
extern "C" void beModelCtrlMOVEEX_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMOVEEX_InitFields(void);
extern "C" void *beModelCtrlMOVE_GetMetaObject(void);
extern "C" int beModelCtrlMOVE_GetVTable(void);
extern "C" void beModelCtrlMOVE_EnsureRegistered(void);
extern "C" void *beModelCtrlMOVE_Register(void);
extern "C" void beModelCtrlMOVE_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMOVE_InitFields(void);
extern "C" void *beModelCtrlMSGBOX_GetMetaObject(void);
extern "C" int beModelCtrlMSGBOX_GetVTable(void);
extern "C" void beModelCtrlMSGBOX_EnsureRegistered(void);
extern "C" void *beModelCtrlMSGBOX_Register(void);
extern "C" void beModelCtrlMSGBOX_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlCTRL_GetMetaObject(void);
extern "C" int beModelCtrlCTRL_GetVTable(void);
extern "C" void beModelCtrlCTRL_EnsureRegistered(void);
extern "C" void *beModelCtrlCTRL_Register(void);
extern "C" void beModelCtrlCTRL_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlJUMP_GetMetaObject(void);
extern "C" int beModelCtrlJUMP_GetVTable(void);
extern "C" void beModelCtrlJUMP_EnsureRegistered(void);
extern "C" void *beModelCtrlJUMP_Register(void);
extern "C" void beModelCtrlJUMP_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlACTION_GetMetaObject(void);
extern "C" int beModelCtrlACTION_GetVTable(void);
extern "C" void beModelCtrlACTION_EnsureRegistered(void);
extern "C" void *beModelCtrlACTION_Register(void);
extern "C" void beModelCtrlACTION_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlLABELCTRL_GetMetaObject(void);
extern "C" int beModelCtrlLABELCTRL_GetVTable(void);
extern "C" void beModelCtrlLABELCTRL_EnsureRegistered(void);
extern "C" void *beModelCtrlLABELCTRL_Register(void);
extern "C" void beModelCtrlLABELCTRL_GetMetaObjectFunction(void);
extern "C" void beModelCtrlLABELCTRL_InitFields(void);
extern "C" void *beModelCtrlLABEL_GetMetaObject(void);
extern "C" int beModelCtrlLABEL_GetVTable(void);
extern "C" void beModelCtrlLABEL_EnsureRegistered(void);
extern "C" void *beModelCtrlLABEL_Register(void);
extern "C" void beModelCtrlLABEL_GetMetaObjectFunction(void);
extern "C" int beModelCtrlLUACALL_GetVTable(void);
extern "C" void beModelCtrlLUACALL_EnsureRegistered(void);
extern "C" void *beModelCtrlLUACALL_Register(void);
extern "C" void beModelCtrlLUACALL_GetMetaObjectFunction(void);
extern "C" void beModelCtrlLUACALL_InitFields(void);
extern "C" int beModelCtrlDataList_GetVTable(void);
extern "C" void beModelCtrlDataList_EnsureRegistered(void);
extern "C" void *beModelCtrlDataList_Register(void);
extern "C" void beModelCtrlDataList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beModelCtrlData_GetOrCreateMetaObject(void);
extern "C" int beModelCtrlData_GetVTable(void);
extern "C" void beModelCtrlData_EnsureRegistered(void);
extern "C" void *beModelCtrlData_Register(void);
extern "C" void beModelCtrlData_GetMetaObjectFunction(void);
extern "C" void beModelCtrlData_InitFields(void);
extern "C" igMetaEnum *beModelCtrl_GetMessageEnum(void);
extern "C" void beModelCtrl_EnsureRegistered(void);
extern "C" void *beModelCtrl_Register(void);
extern "C" void beModelCtrl_GetMetaObjectFunction(void);
extern "C" void beModelCtrl_InitFields(void);
extern "C" igMetaObject *beMeterCtrlNode_GetOrCreateMetaObject(void);
extern "C" void *beMeterCtrlNode_ResolveMetaObject(void);
extern "C" int FUN_00195190(int *, int);
extern "C" int beMeterCtrlNode_GetVTable(void);
extern "C" void beMeterCtrlNode_EnsureRegistered(void);
extern "C" void *beMeterCtrlNode_Register(void);
extern "C" void beMeterCtrlNode_GetMetaObject(void);
extern "C" int igLongList_GetOrCreateMetaObject(void);
extern "C" void beMeterCtrlNode_InitFields(void);
extern "C" void beMeterCtrlNode_RegisterTraversalFunction(void);
extern "C" void FUN_00356f40(void);
extern "C" void *beMeterCtrlInfoList_GetMetaObject(void);
extern "C" int beMeterCtrlInfoList_GetVTable(void);
extern "C" void beMeterCtrlInfoList_EnsureRegistered(void);
extern "C" void *beMeterCtrlInfoList_Register(void);
extern "C" void beMeterCtrlInfoList_GetMetaObjectFunction(void);
extern "C" void *beMeterCtrlInfo_GetMetaObject(void);
extern "C" int beMeterCtrlInfo_GetVTable(void);
extern "C" void beMeterCtrlInfo_EnsureRegistered(void);
extern "C" void *beMeterCtrlInfo_Register(void);
extern "C" void beMeterCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beMeterCtrlInfo_InitFields(void);
extern "C" void *beMeterCtrlOneData_GetMetaObject(void);
extern "C" int beMeterCtrlOneData_GetVTable(void);
extern "C" void **FUN_003573d0(void **arg0, long long arg1);
extern "C" void beMeterCtrlOneData_EnsureRegistered(void);
extern "C" void *beMeterCtrlOneData_Register(void);
extern "C" void beMeterCtrlOneData_GetMetaObjectFunction(void);
extern "C" void beMeterCtrlOneData_InitFields(void);
extern "C" igMetaEnum *FUN_00357600(void);
extern "C" void beMeterCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beMeterCtrl_GetOrCreateMetaObject(void);
extern "C" void *beMeterCtrl_GetMetaObject(void);
extern "C" int beMeterCtrl_GetVTable(void);
extern "C" void beMeterCtrl_EnsureRegistered(void);
extern "C" void *beMeterCtrl_Register(void);
extern "C" void beMeterCtrl_GetMetaObjectFunction(void);
extern "C" void beMessenger_CreateInstance(int arg0);
extern "C" igMetaObject *beMessenger_GetOrCreateMetaObject(void);
extern "C" void *beMessenger_GetMetaObject(void);
extern "C" int beMessenger_GetVTable(void);
extern "C" void List_RemoveWordAt(void *, int);
extern "C" void List_InsertWords(void *, int, int, void *);
extern "C" void *StringPool_Allocate(int);
extern "C" void *StringPool_Construct(void *);
extern "C" const char *StringPool_Intern(void *, const char *);
extern "C" void **FUN_00357b10(void **arg0, int arg1);
extern "C" void **FUN_00357b90(void **arg0, short arg1);
extern "C" void **FUN_00357c90(void **arg0, long long arg1);
extern "C" void beMessenger_EnsureRegistered(void);
extern "C" void *beMessenger_Register(void);
extern "C" void beMessenger_GetMetaObjectFunction(void);
extern "C" void beMessenger_InitFields(void);
extern "C" igMetaObject *beMessengerWorkList_GetOrCreateMetaObject(void);
extern "C" void *beMessengerWorkList_GetMetaObject(void);
extern "C" int beMessengerWorkList_GetVTable(void);
extern "C" void beMessengerWorkList_EnsureRegistered(void);
extern "C" void *beMessengerWorkList_Register(void);
extern "C" void beMessengerWorkList_GetMetaObjectFunction(void);
extern "C" void *beMessengerWork_Create(void *allocator);
extern "C" void beMessengerWork_EnsureRegistered();
extern "C" void *beMessengerGroup_Create(void *allocator);
extern "C" void beMessengerGroup_EnsureRegistered();
extern "C" void *beMessengerDelay_Create(void *allocator);
extern "C" void beMessengerDelay_EnsureRegistered();
extern "C" void *beMessengerArgData_Create(void *allocator);
extern "C" void beMessengerArgData_EnsureRegistered();
extern "C" void *beMessengerWork_GetMetaObject(void);
extern "C" int beMessengerWork_GetVTable(void);
extern "C" void *beMessengerWork_Register(void);
extern "C" void beMessengerWork_GetMetaObjectFunction(void);
extern "C" void beMessengerWork_InitFields(void);
extern "C" igMetaObject *beMessengerGroupList_GetOrCreateMetaObject(void);
extern "C" void *beMessengerGroupList_GetMetaObject(void);
extern "C" int beMessengerGroupList_GetVTable(void);
extern "C" void beMessengerGroupList_EnsureRegistered(void);
extern "C" void *beMessengerGroupList_Register(void);
extern "C" void beMessengerGroupList_GetMetaObjectFunction(void);
extern "C" void *beMessengerGroup_GetMetaObject(void);
extern "C" int beMessengerGroup_GetVTable(void);
extern "C" void *beMessengerGroup_Register(void);
extern "C" void beMessengerGroup_GetMetaObjectFunction(void);
extern "C" void beMessengerGroup_InitFields(void);
extern "C" igMetaObject *beMessengerDelayList_GetOrCreateMetaObject(void);
extern "C" int beMessengerDelayList_GetVTable(void);
extern "C" void beMessengerDelayList_EnsureRegistered(void);
extern "C" void *beMessengerDelayList_Register(void);
extern "C" void beMessengerDelayList_GetMetaObjectFunction(void);
extern "C" int beMessengerDelay_GetVTable(void);
extern "C" void *beMessengerDelay_Register(void);
extern "C" void beMessengerDelay_GetMetaObjectFunction(void);
extern "C" void beMessengerDelay_InitFields(void);
extern "C" igMetaObject *beMessengerArgDataList_GetOrCreateMetaObject(void);
extern "C" int beMessengerArgDataList_GetVTable(void);
extern "C" void beMessengerArgDataList_EnsureRegistered(void);
extern "C" void *beMessengerArgDataList_Register(void);
extern "C" void beMessengerArgDataList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beMessengerArgData_GetOrCreateMetaObject(void);
extern "C" int FUN_001998f0(int *, int);
extern "C" int FUN_00226990(int *, int);
extern "C" int beMessengerArgData_GetVTable(void);
extern "C" void *beMessengerArgData_Register(void);
extern "C" void beMessengerArgData_GetMetaObjectFunction(void);
extern "C" int igMatrix44fList_GetOrCreateMetaObject(void);
extern "C" void beMessengerArgData_InitFields(void);
extern "C" igMetaObject *beMemory_GetOrCreateMetaObject(void);
extern "C" void *beMemory_GetMetaObject(void);
extern "C" int beMemory_GetVTable(void);
extern "C" void beMemory_EnsureRegistered(void);
extern "C" void *beMemory_Register(void);
extern "C" void beMemory_GetMetaObjectFunction(void);
extern "C" void beMemory_InitFields(void);
extern "C" void beMatCtrlInfoWork_Create(int arg0);
extern "C" igMetaObject *beMatCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlInfoWork_GetMetaObject(void);
extern "C" int beMatCtrlInfoWork_GetVTable(void);
extern "C" void beMatCtrlInfoWork_EnsureRegistered(void);
extern "C" void *beMatCtrlInfoWork_Register(void);
extern "C" void beMatCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" int igIntListList_GetOrCreateMetaObject(void);
extern "C" void beMatCtrlInfoWork_InitFields(void);
extern "C" void *beMatCtrlInfoRam_GetMetaObject(void);
extern "C" int beMatCtrlInfoRam_GetVTable(void);
extern "C" void beMatCtrlInfoRam_EnsureRegistered(void);
extern "C" void *beMatCtrlInfoRam_Register(void);
extern "C" void beMatCtrlInfoRam_GetMetaObjectFunction(void);
extern "C" void beMatCtrlInfoRam_InitFields(void);
extern "C" void *beMatCtrlInfo_GetMetaObject(void);
extern "C" int beMatCtrlInfo_GetVTable(void);
extern "C" void **FUN_00359bd0(void **arg0, long long arg1);
extern "C" void **FUN_00359c50(void **arg0, short arg1);
extern "C" void beMatCtrlInfo_EnsureRegistered(void);
extern "C" void *beMatCtrlInfo_Register(void);
extern "C" void beMatCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beMatCtrlInfo_InitFields(void);
extern "C" igMetaObject *beMatCtrlSearchList_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlSearchList_GetMetaObject(void);
extern "C" int beMatCtrlSearchList_GetVTable(void);
extern "C" void beMatCtrlSearchList_EnsureRegistered(void);
extern "C" void *beMatCtrlSearchList_Register(void);
extern "C" void beMatCtrlSearchList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beMatCtrlSearch_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlSearch_GetMetaObject(void);
extern "C" int beMatCtrlSearch_GetVTable(void);
extern "C" void beMatCtrlSearch_EnsureRegistered(void);
extern "C" void *beMatCtrlSearch_Register(void);
extern "C" void beMatCtrlSearch_GetMetaObjectFunction(void);
extern "C" void beMatCtrlSearch_InitFields(void);
extern "C" igMetaObject *beMatCtrlDataList_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlDataList_GetMetaObject(void);
extern "C" int beMatCtrlDataList_GetVTable(void);
extern "C" void beMatCtrlDataList_EnsureRegistered(void);
extern "C" void *beMatCtrlDataList_Register(void);
extern "C" void beMatCtrlDataList_GetMetaObjectFunction(void);
extern "C" void *beMatCtrlData_GetMetaObject(void);
extern "C" int beMatCtrlData_GetVTable(void);
extern "C" void beMatCtrlData_EnsureRegistered(void);
extern "C" void *beMatCtrlData_Register(void);
extern "C" void beMatCtrlData_GetMetaObjectFunction(void);
extern "C" void beMatCtrlData_InitFields(void);
extern "C" igMetaEnum *beMatCtrl_GetMessageEnum(void);
extern "C" void beMatCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beMatCtrl_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrl_GetMetaObject(void);
extern "C" int beMatCtrl_GetVTable(void);
extern "C" void beMatCtrl_EnsureRegistered(void);
extern "C" void *beMatCtrl_Register(void);
extern "C" void beMatCtrl_GetMetaObjectFunction(void);
extern "C" void beMatCtrl_InitFields(void);
extern "C" void beLuaState_Create(int arg0);
extern "C" igMetaObject *beLuaState_GetOrCreateMetaObject(void);
extern "C" void *beLuaState_GetMetaObject(void);
extern "C" int beLuaState_GetVTable(void);
extern "C" void beLuaState_EnsureRegistered(void);
extern "C" void *igLuaState_Register(void);
extern "C" void *beLuaState_Register(void);
extern "C" void beLuaState_GetMetaObjectFunction(void);
extern "C" int igLuaState_GetPublishedMetaObject(void);
extern "C" void beLuaState_InitFields(void);
extern "C" int beLuaInfo_GetVTable(void);
extern "C" void beLuaInfo_EnsureRegistered(void);
extern "C" void *beLuaInfo_Register(void);
extern "C" void beLuaInfo_GetMetaObjectFunction(void);
extern "C" void beLuaInfo_InitFields(void);
extern "C" igMetaObject *beLuaDataList_GetOrCreateMetaObject(void);
extern "C" int beLuaDataList_GetVTable(void);
extern "C" void beLuaDataList_EnsureRegistered(void);
extern "C" void *beLuaDataList_Register(void);
extern "C" void beLuaDataList_GetMetaObjectFunction(void);
extern "C" int beLuaData_GetVTable(void);
extern "C" void beLuaData_EnsureRegistered(void);
extern "C" void *beLuaData_Register(void);
extern "C" void beLuaData_GetMetaObjectFunction(void);
extern "C" void beLuaData_InitFields(void);
extern "C" int beLuaDataObjectist_GetVTable(void);
extern "C" void beLuaDataObjectist_EnsureRegistered(void);
extern "C" void *beLuaDataObjectist_Register(void);
extern "C" void beLuaDataObjectist_GetMetaObjectFunction(void);
extern "C" igMetaObject *beLuaDataObject_GetOrCreateMetaObject(void);
extern "C" void *beLuaDataObject_GetMetaObject(void);
extern "C" int beLuaDataObject_GetVTable(void);
extern "C" void beLuaDataObject_EnsureRegistered(void);
extern "C" void *beLuaDataObject_Register(void);
extern "C" void beLuaDataObject_GetMetaObjectFunction(void);
extern "C" void beLuaDataObject_InitFields(void);
extern "C" void beLua_CreateInstance(int arg0);
extern "C" igMetaObject *beLua_GetOrCreateMetaObject(void);
extern "C" void *beLua_GetMetaObject(void);
extern "C" int beLua_GetVTable(void);
extern "C" void **FUN_0035b8c0(void **arg0, short arg1);
extern "C" void beLua_EnsureRegistered(void);
extern "C" void *beLua_Register(void);
extern "C" void beLua_GetMetaObjectFunction(void);
extern "C" int igLuaGlue_GetOrCreateMetaObject(void);
extern "C" void beLua_InitFields(void);
extern "C" igMetaObject *igLightSetList_GetOrCreateMetaObject(void);
extern "C" void *igLightSetList_GetMetaObject(void);
extern "C" int igLightSetList_GetVTable(void);
extern "C" void igLightSetList_EnsureRegistered(void);
extern "C" void *igLightSetList_Register(void);
extern "C" void igLightSetList_GetMetaObjectFunction(void);
extern "C" void *beLightCtrlInfo_GetMetaObject(void);
extern "C" int beLightCtrlInfo_GetVTable(void);
extern "C" void beLightCtrlInfo_EnsureRegistered(void);
extern "C" void *beLightCtrlInfo_Register(void);
extern "C" void beLightCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beLightCtrlInfo_InitFields(void);
extern "C" igMetaEnum *FUN_0035bfb0(void);
extern "C" void beLightCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beLightCtrl_GetOrCreateMetaObject(void);
extern "C" void *beLightCtrl_GetMetaObject(void);
extern "C" int beLightCtrl_GetVTable(void);
extern "C" void beLightCtrl_EnsureRegistered(void);
extern "C" void *beLightCtrl_Register(void);
extern "C" void beLightCtrl_GetMetaObjectFunction(void);
extern "C" void *beLayerInfoRam_GetMetaObject(void);
extern "C" int beLayerInfoRam_GetVTable(void);
extern "C" void beLayerInfoRam_EnsureRegistered(void);
extern "C" void *beLayerInfoRam_Register(void);
extern "C" void beLayerInfoRam_GetMetaObjectFunction(void);
extern "C" void *beLayerInfo_GetMetaObject(void);
extern "C" int beLayerInfo_GetVTable(void);
extern "C" void beLayerInfo_EnsureRegistered(void);
extern "C" void *beLayerInfo_Register(void);
extern "C" void beLayerInfo_GetMetaObjectFunction(void);
extern "C" void beLayerInfo_InitFields(void);
extern "C" igMetaObject *beLayerGroupList_GetOrCreateMetaObject(void);
extern "C" void *beLayerGroupList_GetMetaObject(void);
extern "C" int beLayerGroupList_GetVTable(void);
extern "C" void beLayerGroupList_EnsureRegistered(void);
extern "C" void *beLayerGroupList_Register(void);
extern "C" void beLayerGroupList_GetMetaObjectFunction(void);
extern "C" void *beLayerGroup_GetMetaObject(void);
extern "C" int beLayerGroup_GetVTable(void);
extern "C" void beLayerGroup_EnsureRegistered(void);
extern "C" void *beLayerGroup_Register(void);
extern "C" void beLayerGroup_GetMetaObjectFunction(void);
extern "C" igMetaEnum *beLayerCtl_GetSwtCtlEnum(void);
extern "C" igMetaEnum *beLayerCtl_GetMessageEnum(void);
extern "C" void beLayerCtl_CreateInstance(int arg0);
extern "C" igMetaObject *beLayerCtl_GetOrCreateMetaObject(void);
extern "C" void *beLayerCtl_GetMetaObject(void);
extern "C" int beLayerCtl_GetVTable(void);
extern "C" void beLayerCtl_EnsureRegistered(void);
extern "C" void *beLayerCtl_Register(void);
extern "C" void beLayerCtl_GetMetaObjectFunction(void);
extern "C" void beLayerCtl_InitFields(void);
extern "C" int FUN_0013bfe0(int *, int);
extern "C" int FUN_0019ab10(...);
extern "C" int FUN_001aaf00(...);
extern "C" int FUN_001ab380(int *, int);
extern "C" int beLOA_GetVTable(void);
extern "C" void beLOA_EnsureRegistered(void);
extern "C" void *beLOA_Register(void);
extern "C" void beLOA_GetMetaObjectFunction(void);
extern "C" int igColorAttr_GetOrCreateMetaObject(void);
extern "C" int igBlendStateAttr_GetOrCreateMetaObject(void);
extern "C" int igBlendFunctionAttr_GetOrCreateMetaObject(void);
extern "C" int FUN_0018e670(void *, int *);
extern "C" void beLOA_InitFields(void);
extern "C" void FUN_00389fb0(void);
extern "C" void FUN_0035d050(void);
extern "C" igMetaObject *beKeyboardReceiver_GetOrCreateMetaObject(void);
extern "C" int beKeyboardReceiver_GetVTable(void);
extern "C" void beKeyboardReceiver_EnsureRegistered(void);
extern "C" void *igEventReceiver_Register(void);
extern "C" void *beKeyboardReceiver_Register(void);
extern "C" void beKeyboardReceiver_GetMetaObjectFunction(void);
extern "C" void beKeyboardReceiver_InitFields(void);
extern "C" int beHitLandModelInfoRam_GetVTable(void);
extern "C" void beHitLandModelInfoRam_EnsureRegistered(void);
extern "C" void *beHitLandModelInfoRam_Register(void);
extern "C" void beHitLandModelInfoRam_GetMetaObjectFunction(void);
extern "C" int beHitLandModelInfo_GetVTable(void);
extern "C" void beHitLandModelInfo_EnsureRegistered(void);
extern "C" void *beHitLandModelInfo_Register(void);
extern "C" void beHitLandModelInfo_GetMetaObjectFunction(void);
extern "C" void beHitLandModelInfo_InitFields(void);
extern "C" igMetaEnum *FUN_0035d720(void);
extern "C" void beHitLandModel_CreateInstance(int arg0);
extern "C" igMetaObject *beHitLandModel_GetOrCreateMetaObject(void);
extern "C" void *beHitLandModel_GetMetaObject(void);
extern "C" int beHitLandModel_GetVTable(void);
extern "C" void **FUN_0035d930(void **arg0, int arg1);
extern "C" void **FUN_0035d9b0(void **arg0, short arg1);
extern "C" void beHitLandModel_EnsureRegistered(void);
extern "C" void *beHitLandModel_Register(void);
extern "C" void beHitLandModel_GetMetaObjectFunction(void);
extern "C" int igProbe_GetOrCreateMetaObject(void);
extern "C" void beHitLandModel_InitFields(void);
extern "C" void beHitLandModelTraversal_Create(int arg0);
extern "C" igMetaObject *beHitLandModelTraversal_GetOrCreateMetaObject(void);
extern "C" void *beHitLandModelTraversal_GetMetaObject(void);
extern "C" int FUN_0019e150(char *, int);
extern "C" int beHitLandModelTraversal_GetVTable(void);
extern "C" void beHitLandModelTraversal_EnsureRegistered(void);
extern "C" void *igIntersectTraversal_Register(void);
extern "C" void *beHitLandModelTraversal_Register(void);
extern "C" void beHitLandModelTraversal_GetMetaObjectFunction(void);
extern "C" int igIntersectTraversal_GetPublishedMetaObject(void);
extern "C" void beHitLandModelTraversal_InitFields(void);
extern "C" void beHitLandModelOrder_Create(int arg0);
extern "C" igMetaObject *beHitLandModelOrder_GetOrCreateMetaObject(void);
extern "C" void *beHitLandModelOrder_GetMetaObject(void);
extern "C" int beHitLandModelOrder_GetVTable(void);
extern "C" void beHitLandModelOrder_EnsureRegistered(void);
extern "C" void *beHitLandModelOrder_Register(void);
extern "C" void beHitLandModelOrder_GetMetaObjectFunction(void);
extern "C" int igRayList_GetOrCreateMetaObject(void);
extern "C" int FUN_0018e470(void *, int *);
extern "C" void beHitLandModelOrder_InitFields(void);
extern "C" igMetaObject *beHitLandResultDataList_GetOrCreateMetaObject(void);
extern "C" void *beHitLandResultDataList_GetMetaObject(void);
extern "C" int beHitLandResultDataList_GetVTable(void);
extern "C" void beHitLandResultDataList_EnsureRegistered(void);
extern "C" void *beHitLandResultDataList_Register(void);
extern "C" void beHitLandResultDataList_GetMetaObjectFunction(void);
extern "C" void beHitLandResultData_Create(int arg0);
extern "C" void *beHitLandResultData_GetMetaObject(void);
extern "C" int beHitLandResultData_GetVTable(void);
extern "C" void beHitLandResultData_EnsureRegistered(void);
extern "C" void *beHitLandResultData_Register(void);
extern "C" void beHitLandResultData_GetMetaObjectFunction(void);
extern "C" void beHitLandResultData_InitFields(void);
extern "C" void *beHitLandDelivInfoRam_GetMetaObject(void);
extern "C" int beHitLandDelivInfoRam_GetVTable(void);
extern "C" void beHitLandDelivInfoRam_EnsureRegistered(void);
extern "C" void *beHitLandDelivInfoRam_Register(void);
extern "C" void beHitLandDelivInfoRam_GetMetaObjectFunction(void);
extern "C" void beHitLandDelivInfoRam_InitFields(void);
extern "C" void *beHitLandDelivInfo_GetMetaObject(void);
extern "C" int beHitLandDelivInfo_GetVTable(void);
extern "C" void beHitLandDelivInfo_EnsureRegistered(void);
extern "C" void *beHitLandDelivInfo_Register(void);
extern "C" void beHitLandDelivInfo_GetMetaObjectFunction(void);
extern "C" igMetaEnum *beHitLandDelivInfo_GetMessageEnum(void);
extern "C" void beHitLandDeliv_CreateInstance(int arg0);
extern "C" igMetaObject *beHitLandDeliv_GetOrCreateMetaObject(void);
extern "C" void *beHitLandDeliv_GetMetaObject(void);
extern "C" int beHitLandDeliv_GetVTable(void);
extern "C" void beHitLandDeliv_EnsureRegistered(void);
extern "C" void *beHitLandDeliv_Register(void);
extern "C" void beHitLandDeliv_GetMetaObjectFunction(void);
extern "C" igMetaObject *beGroupKeepList_GetOrCreateMetaObject(void);
extern "C" void *beGroupKeepList_GetMetaObject(void);
extern "C" int beGroupKeepList_GetVTable(void);
extern "C" void beGroupKeepList_EnsureRegistered(void);
extern "C" void *beGroupKeepList_Register(void);
extern "C" void beGroupKeepList_GetMetaObjectFunction(void);
extern "C" void *beGroupKeep_GetMetaObject(void);
extern "C" int beGroupKeep_GetVTable(void);
extern "C" void beGroupKeep_EnsureRegistered(void);
extern "C" void *beGroupKeep_Register(void);
extern "C" void beGroupKeep_GetMetaObjectFunction(void);
extern "C" void beGeneraterInfoWork_Create(int arg0);
extern "C" igMetaObject *beGeneraterInfoWork_GetOrCreateMetaObject(void);
extern "C" int beGeneraterInfoWork_GetVTable(void);
extern "C" void beGeneraterInfoWork_EnsureRegistered(void);
extern "C" void *beGeneraterInfoWork_Register(void);
extern "C" void beGeneraterInfoWork_GetMetaObjectFunction(void);
extern "C" void beGeneraterInfoWork_InitFields(void);
extern "C" int beGeneraterInfoRam_GetVTable(void);
extern "C" void beGeneraterInfoRam_EnsureRegistered(void);
extern "C" void *beGeneraterInfoRam_Register(void);
extern "C" void beGeneraterInfoRam_GetMetaObjectFunction(void);
extern "C" void beGeneraterInfoRam_InitFields(void);
extern "C" int beGeneraterInfo_GetVTable(void);
extern "C" void **FUN_0035f7f0(void **arg0, long long arg1);
extern "C" void beGeneraterInfo_EnsureRegistered(void);
extern "C" void *beGeneraterInfo_Register(void);
extern "C" void beGeneraterInfo_GetMetaObjectFunction(void);
extern "C" void beGeneraterInfo_InitFields(void);
extern "C" igMetaObject *beGeneraterDataList_GetOrCreateMetaObject(void);
extern "C" int beGeneraterDataList_GetVTable(void);
extern "C" void beGeneraterDataList_EnsureRegistered(void);
extern "C" void *beGeneraterDataList_Register(void);
extern "C" void beGeneraterDataList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterData_GetMetaObject(void);
extern "C" int beGeneraterData_GetVTable(void);
extern "C" void beGeneraterData_EnsureRegistered(void);
extern "C" void *beGeneraterData_Register(void);
extern "C" void beGeneraterData_GetMetaObjectFunction(void);
extern "C" void beGeneraterData_InitFields(void);
extern "C" igMetaObject *beGeneraterPlayerDataList_GetOrCreateMetaObject(void);
extern "C" void *beGeneraterPlayerDataList_GetMetaObject(void);
extern "C" int beGeneraterPlayerDataList_GetVTable(void);
extern "C" void beGeneraterPlayerDataList_EnsureRegistered(void);
extern "C" void *beGeneraterPlayerDataList_Register(void);
extern "C" void beGeneraterPlayerDataList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterPlayerData_GetMetaObject(void);
extern "C" int beGeneraterPlayerData_GetVTable(void);
extern "C" void beGeneraterPlayerData_EnsureRegistered(void);
extern "C" void *beGeneraterPlayerData_Register(void);
extern "C" void beGeneraterPlayerData_GetMetaObjectFunction(void);
extern "C" void beGeneraterPlayerData_InitFields(void);
extern "C" igMetaObject *beGeneraterItemDataList_GetOrCreateMetaObject(void);
extern "C" void *beGeneraterItemDataList_GetMetaObject(void);
extern "C" int beGeneraterItemDataList_GetVTable(void);
extern "C" void beGeneraterItemDataList_EnsureRegistered(void);
extern "C" void *beGeneraterItemDataList_Register(void);
extern "C" void beGeneraterItemDataList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterItemData_GetMetaObject(void);
extern "C" int beGeneraterItemData_GetVTable(void);
extern "C" void beGeneraterItemData_EnsureRegistered(void);
extern "C" void *beGeneraterItemData_Register(void);
extern "C" void beGeneraterItemData_GetMetaObjectFunction(void);
extern "C" void beGeneraterItemData_InitFields(void);
extern "C" igMetaObject *beGeneraterItemDataOneList_GetOrCreateMetaObject(void);
extern "C" void *beGeneraterItemDataOneList_GetMetaObject(void);
extern "C" int beGeneraterItemDataOneList_GetVTable(void);
extern "C" void beGeneraterItemDataOneList_EnsureRegistered(void);
extern "C" void *beGeneraterItemDataOneList_Register(void);
extern "C" void beGeneraterItemDataOneList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterItemDataOne_GetMetaObject(void);
extern "C" int beGeneraterItemDataOne_GetVTable(void);
extern "C" void beGeneraterItemDataOne_EnsureRegistered(void);
extern "C" void *beGeneraterItemDataOne_Register(void);
extern "C" void beGeneraterItemDataOne_GetMetaObjectFunction(void);
extern "C" void beGeneraterItemDataOne_InitFields(void);
extern "C" igMetaEnum *FUN_00360b10(void);
extern "C" void beGenerater_CreateInstance(int arg0);
extern "C" igMetaObject *beGenerater_GetOrCreateMetaObject(void);
extern "C" void *beGenerater_GetMetaObject(void);
extern "C" int beGenerater_GetVTable(void);
extern "C" void beGenerater_EnsureRegistered(void);
extern "C" void *beGenerater_Register(void);
extern "C" void beGenerater_GetMetaObjectFunction(void);
extern "C" void beGenerater_InitFields(void);
extern "C" void *beFontInfo_GetMetaObject(void);
extern "C" int beFontInfo_GetVTable(void);
extern "C" void beFontInfo_EnsureRegistered(void);
extern "C" void *beFontInfo_Register(void);
extern "C" void beFontInfo_GetMetaObjectFunction(void);
extern "C" void beFontInfo_InitFields(void);
extern "C" void *beFontInfoData_GetMetaObject(void);
extern "C" int FUN_001d97f0(...);
extern "C" int beFontInfoData_GetVTable(void);
extern "C" void beFontInfoData_EnsureRegistered(void);
extern "C" void *beFontInfoData_Register(void);
extern "C" void beFontInfoData_GetMetaObjectFunction(void);
extern "C" void beFontInfoData_InitFields(void);
extern "C" igMetaObject *beUnicodeObjList_GetOrCreateMetaObject(void);
extern "C" int beUnicodeObjList_GetVTable(void);
extern "C" void beUnicodeObjList_EnsureRegistered(void);
extern "C" void *beUnicodeObjList_Register(void);
extern "C" void beUnicodeObjList_GetMetaObjectFunction(void);
extern "C" void beUnicodeObj_Create(int arg0);
extern "C" int beUnicodeObj_GetVTable(void);
extern "C" void beUnicodeObj_EnsureRegistered(void);
extern "C" void *beUnicodeObj_Register(void);
extern "C" void beUnicodeObj_GetMetaObjectFunction(void);
extern "C" int igUnsignedShortMetaField_GetDefaultDescriptor(void);
extern "C" void beUnicodeObj_InitFields(void);
extern "C" igMetaObject *beFontImageList_GetOrCreateMetaObject(void);
extern "C" int beFontImageList_GetVTable(void);
extern "C" void beFontImageList_EnsureRegistered(void);
extern "C" void *beFontImageList_Register(void);
extern "C" void beFontImageList_GetMetaObjectFunction(void);
extern "C" int beFontImage_GetVTable(void);
extern "C" void **FUN_003619a0(void **arg0, short arg1);
extern "C" void beFontImage_EnsureRegistered(void);
extern "C" void *igBitmapFont_Register(void);
extern "C" void *beFontImage_Register(void);
extern "C" void beFontImage_GetMetaObjectFunction(void);
extern "C" int igBitmapFont_GetPublishedMetaObject(void);
extern "C" igMetaEnum *beFont_GetAlignEnum(void);
extern "C" igMetaEnum *beFont_GetSwitchEnum(void);
extern "C" igMetaEnum *beFont_GetMessageEnum(void);
extern "C" void beFont_CreateInstance(int arg0);
extern "C" igMetaObject *beFont_GetOrCreateMetaObject(void);
extern "C" void *beFont_GetMetaObject(void);
extern "C" int beFont_GetVTable(void);
extern "C" void **FUN_003620f0(void **arg0, short arg1);
extern "C" void beFont_EnsureRegistered(void);
extern "C" void *beFont_Register(void);
extern "C" void beFont_GetMetaObjectFunction(void);
extern "C" void beFont_InitFields(void);
extern "C" igMetaObject *beFontGeomAttrPairList_GetOrCreateMetaObject(void);
extern "C" void *beFontGeomAttrPairList_GetMetaObject(void);
extern "C" int beFontGeomAttrPairList_GetVTable(void);
extern "C" void beFontGeomAttrPairList_EnsureRegistered(void);
extern "C" void *beFontGeomAttrPairList_Register(void);
extern "C" void beFontGeomAttrPairList_GetMetaObjectFunction(void);
extern "C" void beFontGeomAttrPair_Create(int arg0);
extern "C" void *beFontGeomAttrPair_GetMetaObject(void);
extern "C" int beFontGeomAttrPair_GetVTable(void);
extern "C" void beFontGeomAttrPair_EnsureRegistered(void);
extern "C" void *beFontGeomAttrPair_Register(void);
extern "C" void beFontGeomAttrPair_GetMetaObjectFunction(void);
extern "C" int igGeometryAttrList_GetOrCreateMetaObject(void);
extern "C" void beFontGeomAttrPair_InitFields(void);
extern "C" void beFileListInfoManager_CreateInstance(int arg0);
extern "C" igMetaObject *beFileListInfoManager_GetOrCreateMetaObject(void);
extern "C" void *beFileListInfoManager_GetMetaObject(void);
extern "C" int igSmartPointer_igDirectoryList_Destruct(int *, int);
extern "C" int beFileListInfoManager_GetVTable(void);
extern "C" void beFileListInfoManager_EnsureRegistered(void);
extern "C" void *beFileListInfoManager_Register(void);
extern "C" void beFileListInfoManager_GetMetaObjectFunction(void);
extern "C" int igDirectoryList_GetOrCreateMetaObject(void);
extern "C" int igViewerSceneInfoManager_GetOrCreateMetaObject(void);
extern "C" void beFileListInfoManager_InitFields(void);
extern "C" void *beFileListInfo_GetMetaObject(void);
extern "C" int beFileListInfo_GetVTable(void);
extern "C" void beFileListInfo_EnsureRegistered(void);
extern "C" void *beFileListInfo_Register(void);
extern "C" void beFileListInfo_GetMetaObjectFunction(void);
extern "C" void beFileListInfo_InitFields(void);
extern "C" void *beFile_GetMetaObject(void);
extern "C" int beFile_GetVTable(void);
extern "C" void beFile_EnsureRegistered(void);
extern "C" void *beFile_Register(void);
extern "C" void beFile_GetMetaObjectFunction(void);
extern "C" void beFileChkObj_Create(int arg0);
extern "C" void *beFileChkObj_GetMetaObject(void);
extern "C" int beFileChkObj_GetVTable(void);
extern "C" void beFileChkObj_EnsureRegistered(void);
extern "C" void *beFileChkObj_Register(void);
extern "C" void beFileChkObj_GetMetaObjectFunction(void);
extern "C" int igFile_GetOrCreateMetaObject(void);
extern "C" void beFileChkObj_InitFields(void);
extern "C" void beDemoManager_CreateInstance(int arg0);
extern "C" igMetaObject *beDemoManager_GetOrCreateMetaObject(void);
extern "C" void *beDemoManager_GetMetaObject(void);
extern "C" int beDemoManager_GetVTable(void);
extern "C" void beDemoManager_EnsureRegistered(void);
extern "C" void *beDemoManager_Register(void);
extern "C" void beDemoManager_GetMetaObjectFunction(void);
extern "C" void beDemoManager_InitFields(void);
extern "C" igMetaObject *beDemoManagerWorkList_GetOrCreateMetaObject(void);
extern "C" void *beDemoManagerWorkList_GetMetaObject(void);
extern "C" int beDemoManagerWorkList_GetVTable(void);
extern "C" void beDemoManagerWorkList_EnsureRegistered(void);
extern "C" void *beDemoManagerWorkList_Register(void);
extern "C" void beDemoManagerWorkList_GetMetaObjectFunction(void);
extern "C" void beDemoManagerWork_CreateInstance(int arg0);
extern "C" igMetaObject *beDemoManagerWork_GetOrCreateMetaObject(void);
extern "C" void *beDemoManagerWork_GetMetaObject(void);
extern "C" int beDemoManagerWork_GetVTable(void);
extern "C" void beDemoManagerWork_EnsureRegistered(void);
extern "C" void *beDemoManagerWork_Register(void);
extern "C" void beDemoManagerWork_GetMetaObjectFunction(void);
extern "C" void beDemoManagerWork_InitFields(void);
extern "C" igMetaObject *beDemoKeepMesList_GetOrCreateMetaObject(void);
extern "C" int beDemoKeepMesList_GetVTable(void);
extern "C" void beDemoKeepMesList_EnsureRegistered(void);
extern "C" void *beDemoKeepMesList_Register(void);
extern "C" void beDemoKeepMesList_GetMetaObjectFunction(void);
extern "C" void beDemoKeepMes_CreateInstance(int arg0);
extern "C" int beDemoKeepMes_GetVTable(void);
extern "C" void beDemoKeepMes_EnsureRegistered(void);
extern "C" void *beDemoKeepMes_Register(void);
extern "C" void beDemoKeepMes_GetMetaObjectFunction(void);
extern "C" void beDemoKeepMes_InitFields(void);
extern "C" void beDataObjListList_Create(int arg0);
extern "C" igMetaObject *beDataObjListList_GetOrCreateMetaObject(void);
extern "C" int beDataObjListList_GetVTable(void);
extern "C" void beDataObjListList_EnsureRegistered(void);
extern "C" void *beDataObjListList_Register(void);
extern "C" void beDataObjListList_GetMetaObjectFunction(void);
extern "C" void beDataObjList_Create(int arg0);
extern "C" igMetaObject *beDataObjList_GetOrCreateMetaObject(void);
extern "C" int beDataObjList_GetVTable(void);
extern "C" void beDataObjList_EnsureRegistered(void);
extern "C" void *beDataObjList_Register(void);
extern "C" void beDataObjList_GetMetaObjectFunction(void);
extern "C" void beDataObjFloatList_Create(int arg0);
extern "C" void *beDataObjFloatList_GetMetaObject(void);
extern "C" int beDataObjFloatList_GetVTable(void);
extern "C" void beDataObjFloatList_EnsureRegistered(void);
extern "C" void *beDataObjFloatList_Register(void);
extern "C" void beDataObjFloatList_GetMetaObjectFunction(void);
extern "C" void beDataObjFloatList_InitFields(void);
extern "C" void beDataObjObjectList_Create(int arg0);
extern "C" void *beDataObjObjectList_GetMetaObject(void);
extern "C" int beDataObjObjectList_GetVTable(void);
extern "C" void beDataObjObjectList_EnsureRegistered(void);
extern "C" void *beDataObjObjectList_Register(void);
extern "C" void beDataObjObjectList_GetMetaObjectFunction(void);
extern "C" void beDataObjObjectList_InitFields(void);
extern "C" void beDataObjStringList_Create(int arg0);
extern "C" void *beDataObjStringList_GetMetaObject(void);
extern "C" int beDataObjStringList_GetVTable(void);
extern "C" void beDataObjStringList_EnsureRegistered(void);
extern "C" void *beDataObjStringList_Register(void);
extern "C" void beDataObjStringList_GetMetaObjectFunction(void);
extern "C" void beDataObjStringList_InitFields(void);
extern "C" void beDataObjString_Create(int arg0);
extern "C" void *beDataObjString_GetMetaObject(void);
extern "C" int beDataObjString_GetVTable(void);
extern "C" void beDataObjString_EnsureRegistered(void);
extern "C" void *beDataObjString_Register(void);
extern "C" void beDataObjString_GetMetaObjectFunction(void);
extern "C" void beDataObjString_InitFields(void);
extern "C" void beDataObjBoolList_Create(int arg0);
extern "C" void *beDataObjBoolList_GetMetaObject(void);
extern "C" int beDataObjBoolList_GetVTable(void);
extern "C" void beDataObjBoolList_EnsureRegistered(void);
extern "C" void *beDataObjBoolList_Register(void);
extern "C" void beDataObjBoolList_GetMetaObjectFunction(void);
extern "C" void beDataObjBoolList_InitFields(void);
extern "C" void beDataObjBool_Create(int arg0);
extern "C" void *beDataObjBool_GetMetaObject(void);
extern "C" int beDataObjBool_GetVTable(void);
extern "C" void beDataObjBool_EnsureRegistered(void);
extern "C" void *beDataObjBool_Register(void);
extern "C" void beDataObjBool_GetMetaObjectFunction(void);
extern "C" void beDataObjBool_InitFields(void);
extern "C" void beDataObjIntList_Create(int arg0);
extern "C" void *beDataObjIntList_GetMetaObject(void);
extern "C" int beDataObjIntList_GetVTable(void);
extern "C" void beDataObjIntList_EnsureRegistered(void);
extern "C" void *beDataObjIntList_Register(void);
extern "C" void beDataObjIntList_GetMetaObjectFunction(void);
extern "C" void beDataObjIntList_InitFields(void);
extern "C" void beDataObjInt_Create(int arg0);
extern "C" igMetaObject *beDataObjInt_GetOrCreateMetaObject(void);
extern "C" void *beDataObjInt_GetMetaObject(void);
extern "C" int beDataObjInt_GetVTable(void);
extern "C" void beDataObjInt_EnsureRegistered(void);
extern "C" void *beDataObjInt_Register(void);
extern "C" void beDataObjInt_GetMetaObjectFunction(void);
extern "C" void beDataObjInt_InitFields(void);
extern "C" void *beDataBaseList_GetMetaObject(void);
extern "C" int beDataBaseList_GetVTable(void);
extern "C" void beDataBaseList_EnsureRegistered(void);
extern "C" void *beDataBaseList_Register(void);
extern "C" void beDataBaseList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beDataBase_GetOrCreateMetaObject(void);
extern "C" void *beDataBase_GetMetaObject(void);
extern "C" int FUN_001648f0(int *, int);
extern "C" int FUN_00164970(int *, int);
extern "C" int beDataBase_GetVTable(void);
extern "C" void beDataBase_EnsureRegistered(void);
extern "C" void *beDataBase_Register(void);
extern "C" void beDataBase_GetMetaObjectFunction(void);
extern "C" int igShortList_GetOrCreateMetaObject(void);
extern "C" int igCharList_GetOrCreateMetaObject(void);
extern "C" void beDataBase_InitFields(void);
extern "C" int beDBManagerInfo_GetVTable(void);
extern "C" void **FUN_00365e90(void **arg0, long long arg1);
extern "C" void beDBManagerInfo_EnsureRegistered(void);
extern "C" void *beDBManagerInfo_Register(void);
extern "C" void beDBManagerInfo_GetMetaObjectFunction(void);
extern "C" void beDBManagerInfo_InitFields(void);
extern "C" igMetaEnum *FUN_00366070(void);
extern "C" void beDBManager_CreateInstance(int arg0);
extern "C" igMetaObject *beDBManager_GetOrCreateMetaObject(void);
extern "C" int beDBManager_GetVTable(void);
extern "C" void beDBManager_EnsureRegistered(void);
extern "C" void *beDBManager_Register(void);
extern "C" void beDBManager_GetMetaObjectFunction(void);
extern "C" igMetaObject *beCriVolume_GetOrCreateMetaObject(void);
extern "C" int beCriVolume_GetVTable(void);
extern "C" void beCriVolume_EnsureRegistered(void);
extern "C" void *beCriVolume_Register(void);
extern "C" void beCriVolume_GetMetaObjectFunction(void);
extern "C" void beCriVolume_InitFields(void);
extern "C" int beCriSfpData_GetVTable(void);
extern "C" void beCriSfpData_EnsureRegistered(void);
extern "C" void *beCriSfpData_Register(void);
extern "C" void beCriSfpData_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBinDataObject_GetPublishedMetaObject(void);
extern "C" void beCriSfpData_InitFields(void);
extern "C" void beCriSfpData_SetupBufferAlignment(void);
extern "C" void FUN_00366760(void);
extern "C" igMetaObject *beCriHandleList_GetOrCreateMetaObject(void);
extern "C" void *beCriHandleList_GetMetaObject(void);
extern "C" int beCriHandleList_GetVTable(void);
extern "C" void beCriHandleList_EnsureRegistered(void);
extern "C" void *beCriHandleList_Register(void);
extern "C" void beCriHandleList_GetMetaObjectFunction(void);
extern "C" void beCriHandle_Create(int arg0);
extern "C" igMetaObject *beCriHandle_GetOrCreateMetaObject(void);
extern "C" void *beCriHandle_GetMetaObject(void);
extern "C" int beCriHandle_GetVTable(void);
extern "C" void beCriHandle_EnsureRegistered(void);
extern "C" void *beCriHandle_Register(void);
extern "C" void beCriHandle_GetMetaObjectFunction(void);
extern "C" void beCriHandle_InitFields(void);
extern "C" void *beCriFxInfo_GetMetaObject(void);
extern "C" int beCriFxInfo_GetVTable(void);
extern "C" void **FUN_00366d80(void **arg0, int arg1);
extern "C" void beCriFxInfo_EnsureRegistered(void);
extern "C" void *beCriFxInfo_Register(void);
extern "C" void beCriFxInfo_GetMetaObjectFunction(void);
extern "C" void beCriFxInfo_InitFields(void);
extern "C" igMetaObject *beCriFxXbData_GetOrCreateMetaObject(void);
extern "C" void *beCriFxXbData_GetMetaObject(void);
extern "C" int beCriFxXbData_GetVTable(void);
extern "C" void beCriFxXbData_EnsureRegistered(void);
extern "C" void *beCriFxXbData_Register(void);
extern "C" void beCriFxXbData_GetMetaObjectFunction(void);
extern "C" void beCriFxXbData_InitFields(void);
extern "C" igMetaObject *beCriAudio_GetOrCreateMetaObject(void);
extern "C" void *beCriAudio_GetMetaObject(void);
extern "C" int beCriAudio_GetVTable(void);
extern "C" void beCriAudio_EnsureRegistered(void);
extern "C" void *beCriAudio_Register(void);
extern "C" void beCriAudio_GetMetaObjectFunction(void);
extern "C" int igAdxAudio_GetOrCreateMetaObject(void);
extern "C" void beCriAudio_InitFields(void);
extern "C" void beCriSndf_Create(int arg0);
extern "C" igMetaObject *beCriSndf_GetOrCreateMetaObject(void);
extern "C" void *beCriSndf_GetMetaObject(void);
extern "C" int beCriSndf_GetVTable(void);
extern "C" void beCriSndf_EnsureRegistered(void);
extern "C" void *beCriSndf_Register(void);
extern "C" void beCriSndf_GetMetaObjectFunction(void);
extern "C" void beCriSndf_InitFields(void);
extern "C" void *beCriAcxData_GetMetaObject(void);
extern "C" int beCriAcxData_GetVTable(void);
extern "C" void beCriAcxData_EnsureRegistered(void);
extern "C" void *beCriAcxData_Register(void);
extern "C" void beCriAcxData_GetMetaObjectFunction(void);
extern "C" void beCri_CreateInstance(int arg0);
extern "C" igMetaObject *beCri_GetOrCreateMetaObject(void);
extern "C" void *beCri_GetMetaObject(void);
extern "C" int beCri_GetVTable(void);
extern "C" void **igSmartPointer_beCriHandle_Destruct(void **arg0, short arg1);
extern "C" void beCri_EnsureRegistered(void);
extern "C" void *beCri_Register(void);
extern "C" void beCri_GetMetaObjectFunction(void);
extern "C" void beCri_InitFields(void);
extern "C" void *beCountry_GetMetaObject(void);
extern "C" int beCountry_GetVTable(void);
extern "C" void beCountry_EnsureRegistered(void);
extern "C" void *beCountry_Register(void);
extern "C" void beCountry_GetMetaObjectFunction(void);
extern "C" void *beCopyTransform_GetMetaObject(void);
extern "C" int beCopyTransform_GetVTable(void);
extern "C" void beCopyTransform_EnsureRegistered(void);
extern "C" void *beCopyTransform_Register(void);
extern "C" void beCopyTransform_GetMetaObjectFunction(void);
extern "C" void beCopyTransform_InitFields(void);
extern "C" void beCopyTransform_RegisterTraversal(void);
extern "C" void FUN_00368090(void);
extern "C" int beCopyModelCtrl2_GetVTable(void);
extern "C" void beCopyModelCtrl2_EnsureRegistered(void);
extern "C" void *beCopyModelCtrl2_Register(void);
extern "C" void beCopyModelCtrl2_GetMetaObjectFunction(void);
extern "C" void beCopyModelCtrl2_InitFields(void);
extern "C" void beCopyModelCtrl2_RegisterTraversal(void);
extern "C" void FUN_003682f0(void);
extern "C" int beChangePosTransformInfoRam_GetVTable(void);
extern "C" void beChangePosTransformInfoRam_EnsureRegistered(void);
extern "C" void *beChangePosTransformInfoRam_Register(void);
extern "C" void beChangePosTransformInfoRam_GetMetaObjectFunction(void);
extern "C" void beChangePosTransformInfoRam_InitFields(void);
extern "C" int beChangePosTransformInfo_GetVTable(void);
extern "C" void beChangePosTransformInfo_EnsureRegistered(void);
extern "C" void *beChangePosTransformInfo_Register(void);
extern "C" void beChangePosTransformInfo_GetMetaObjectFunction(void);
extern "C" void beChangePosTransform_CreateInstance(int arg0);
extern "C" igMetaObject *beChangePosTransform_GetOrCreateMetaObject(void);
extern "C" int beChangePosTransform_GetVTable(void);
extern "C" void beChangePosTransform_EnsureRegistered(void);
extern "C" void *beChangePosTransform_Register(void);
extern "C" void beChangePosTransform_GetMetaObjectFunction(void);
extern "C" void beChangePosTransform_InitFields(void);
extern "C" void beCameraMode_Create(int arg0);
extern "C" igMetaObject *beCameraMode_GetOrCreateMetaObject(void);
extern "C" void *beCameraMode_GetMetaObject(void);
extern "C" int igMatrix44f_SetIdentity(int *);
extern "C" int beCameraMode_GetVTable(void);
extern "C" void beCameraMode_EnsureRegistered(void);
extern "C" void *igViewMode_Register(void);
extern "C" void *beCameraMode_Register(void);
extern "C" void beCameraMode_GetMetaObjectFunction(void);
extern "C" int igViewMode_GetPublishedMetaObject(void);
extern "C" int igGraphPath_GetOrCreateMetaObject(void);
extern "C" int igCamera_GetOrCreateMetaObject(void);
extern "C" int igInsightCore_GetOrCreateMetaObject(void);
extern "C" void beCameraMode_InitFields(void);
extern "C" void *beCameraCtrlInfo_GetMetaObject(void);
extern "C" int ObjectRef_Destruct_001363f0(int *, int);
extern "C" int beCameraCtrlInfo_GetVTable(void);
extern "C" void beCameraCtrlInfo_EnsureRegistered(void);
extern "C" void *beCameraCtrlInfo_Register(void);
extern "C" void beCameraCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beCameraCtrlInfo_InitFields(void);
extern "C" void *beCameraDemoData_GetMetaObject(void);
extern "C" int beCameraDemoData_GetVTable(void);
extern "C" void beCameraDemoData_EnsureRegistered(void);
extern "C" void *beCameraDemoData_Register(void);
extern "C" void beCameraDemoData_GetMetaObjectFunction(void);
extern "C" void beCameraDemoData_InitFields(void);
extern "C" void *beCameraBoxData_GetMetaObject(void);
extern "C" int FUN_0019c220(int *, int);
extern "C" int beCameraBoxData_GetVTable(void);
extern "C" void beCameraBoxData_EnsureRegistered(void);
extern "C" void *beCameraBoxData_Register(void);
extern "C" void beCameraBoxData_GetMetaObjectFunction(void);
extern "C" int igGeometryList_GetOrCreateMetaObject(void);
extern "C" void beCameraBoxData_InitFields(void);
extern "C" void beCameraCtrlInfoRamShake_Create(int arg0);
extern "C" void *beCameraCtrlInfoRamShake_GetMetaObject(void);
extern "C" int beCameraCtrlInfoRamShake_GetVTable(void);
extern "C" void beCameraCtrlInfoRamShake_EnsureRegistered(void);
extern "C" void *beCameraCtrlInfoRamShake_Register(void);
extern "C" void beCameraCtrlInfoRamShake_GetMetaObjectFunction(void);
extern "C" void beCameraCtrlInfoRamShake_InitFields(void);
extern "C" igMetaEnum *beCameraCtrl_GetMessageEnum(void);
extern "C" void beCameraCtrl_CreateInstance(int arg0);
extern "C" igMetaObject *beCameraCtrl_GetOrCreateMetaObject(void);
extern "C" void *beCameraCtrl_GetMetaObject(void);
extern "C" int beCameraCtrl_GetVTable(void);
extern "C" void **FUN_003699a0(void **arg0, long long arg1);
extern "C" void beCameraCtrl_EnsureRegistered(void);
extern "C" void *beCameraCtrl_Register(void);
extern "C" void beCameraCtrl_GetMetaObjectFunction(void);
extern "C" int igViewerParameters_GetOrCreateMetaObject(void);
extern "C" void beCameraCtrl_InitFields(void);
extern "C" void *beBkColorInfo_GetMetaObject(void);
extern "C" int beBkColorInfo_GetVTable(void);
extern "C" void beBkColorInfo_EnsureRegistered(void);
extern "C" void *beBkColorInfo_Register(void);
extern "C" void beBkColorInfo_GetMetaObjectFunction(void);
extern "C" void beBkColorInfo_InitFields(void);
extern "C" void beBkColor_CreateInstance(int arg0);
extern "C" igMetaObject *beBkColor_GetOrCreateMetaObject(void);
extern "C" void *beBkColor_GetMetaObject(void);
extern "C" int beBkColor_GetVTable(void);
extern "C" void beBkColor_EnsureRegistered(void);
extern "C" void *beBkColor_Register(void);
extern "C" void beBkColor_GetMetaObjectFunction(void);
extern "C" void beBkColor_InitFields(void);
extern "C" igMetaObject *beBaseInfoRamList_GetOrCreateMetaObject(void);
extern "C" void *beBaseInfoRamList_GetReadyMetaObject(void);
extern "C" int beBaseInfoRamList_GetVTable(void);
extern "C" void beBaseInfoRamList_EnsureRegistered(void);
extern "C" void *beBaseInfoRamList_Register(void);
extern "C" void *beBaseInfoRamList_GetMetaObject(void);
extern "C" igMetaObject *beBaseInfoRam_GetOrCreateMetaObject(void);
extern "C" void *beBaseInfoRam_GetMetaObject(void);
extern "C" int beBaseInfoRam_GetVTable(void);
extern "C" void beBaseInfoRam_EnsureRegistered(void);
extern "C" void *beBaseInfoRam_Register(void);
extern "C" void beBaseInfoRam_GetMetaObjectFunction(void);
extern "C" void beBaseInfoRam_InitFields(void);
extern "C" void beBaseInfoRamTimer_Create(int arg0);
extern "C" void *beBaseInfoRamTimer_GetMetaObject(void);
extern "C" int beBaseInfoRamTimer_GetVTable(void);
extern "C" void beBaseInfoRamTimer_EnsureRegistered(void);
extern "C" void *beBaseInfoRamTimer_Register(void);
extern "C" void beBaseInfoRamTimer_GetMetaObjectFunction(void);
extern "C" void beBaseInfoRamTimer_InitFields(void);
extern "C" int beBaseInfoManagerList_GetVTable(void);
extern "C" void beBaseInfoManagerList_EnsureRegistered(void);
extern "C" void *beBaseInfoManagerList_Register(void);
extern "C" void beBaseInfoManagerList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBaseInfoManager_GetOrCreateMetaObject(void);
extern "C" void beBaseInfoManager_EnsureRegistered(void);
extern "C" void *beBaseInfoManager_Register(void);
extern "C" void beBaseInfoManager_GetMetaObjectFunction(void);
extern "C" void beBaseInfoManager_InitFields(void);
extern "C" igMetaObject *beBaseInfoList_GetOrCreateMetaObject(void);
extern "C" int beBaseInfoList_GetVTable(void);
extern "C" void beBaseInfoList_EnsureRegistered(void);
extern "C" void *beBaseInfoList_Register(void);
extern "C" void beBaseInfoList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBaseInfo_GetOrCreateMetaObject(void);
extern "C" void beBaseInfo_EnsureRegistered(void);
extern "C" void *beBaseInfo_Register(void);
extern "C" void beBaseInfo_GetMetaObjectFunction(void);
extern "C" void beBaseInfo_InitFields(void);
extern "C" void beBaseInfoDataList_Create(int arg0);
extern "C" igMetaObject *beBaseInfoDataList_GetOrCreateMetaObject(void);
extern "C" void *beBaseInfoDataList_GetMetaObject(void);
extern "C" int beBaseInfoDataList_GetVTable(void);
extern "C" void beBaseInfoDataList_EnsureRegistered(void);
extern "C" void *beBaseInfoDataList_Register(void);
extern "C" void beBaseInfoDataList_GetMetaObjectFunction(void);
extern "C" void *beBaseInfoData_GetMetaObject(void);
extern "C" void beBaseInfoData_EnsureRegistered(void);
extern "C" void *beBaseInfoData_Register(void);
extern "C" void beBaseInfoData_GetMetaObjectFunction(void);
extern "C" void beBaseInfoData_InitFields(void);
extern "C" void *beActionStarterInfoRam_GetMetaObject(void);
extern "C" int beActionStarterInfoRam_GetVTable(void);
extern "C" void beActionStarterInfoRam_EnsureRegistered(void);
extern "C" void *beActionStarterInfoRam_Register(void);
extern "C" void beActionStarterInfoRam_GetMetaObjectFunction(void);
extern "C" void *beActionStarterInfo_GetMetaObject(void);
extern "C" int beActionStarterInfo_GetVTable(void);
extern "C" void beActionStarterInfo_EnsureRegistered(void);
extern "C" void *beActionStarterInfo_Register(void);
extern "C" void beActionStarterInfo_GetMetaObjectFunction(void);
extern "C" void beActionStarterInfo_InitFields(void);
extern "C" igMetaObject *beAsTargetModelDataList_GetOrCreateMetaObject(void);
extern "C" void *beAsTargetModelDataList_GetMetaObject(void);
extern "C" int beAsTargetModelDataList_GetVTable(void);
extern "C" void beAsTargetModelDataList_EnsureRegistered(void);
extern "C" void *beAsTargetModelDataList_Register(void);
extern "C" void beAsTargetModelDataList_GetMetaObjectFunction(void);
extern "C" void *beAsTargetModelData_GetMetaObject(void);
extern "C" int beAsTargetModelData_GetVTable(void);
extern "C" void beAsTargetModelData_EnsureRegistered(void);
extern "C" void *beAsTargetModelData_Register(void);
extern "C" void beAsTargetModelData_GetMetaObjectFunction(void);
extern "C" void beAsTargetModelData_InitFields(void);
extern "C" void *beActionStarterData2_GetMetaObject(void);
extern "C" int beActionStarterData2_GetVTable(void);
extern "C" void beActionStarterData2_EnsureRegistered(void);
extern "C" void *beActionStarterData2_Register(void);
extern "C" void beActionStarterData2_GetMetaObjectFunction(void);
extern "C" igMetaObject *beActionStarterData_GetPublishedMetaObject(void);
extern "C" void beActionStarterData2_InitFields(void);
extern "C" igMetaObject *beActionStarterDataList_GetOrCreateMetaObject(void);
extern "C" void *beActionStarterDataList_GetMetaObject(void);
extern "C" int beActionStarterDataList_GetVTable(void);
extern "C" void beActionStarterDataList_EnsureRegistered(void);
extern "C" void *beActionStarterDataList_Register(void);
extern "C" void beActionStarterDataList_GetMetaObjectFunction(void);
extern "C" void *beActionStarterData_GetMetaObject(void);
extern "C" int beActionStarterData_GetVTable(void);
extern "C" void beActionStarterData_EnsureRegistered(void);
extern "C" void *beActionStarterData_Register(void);
extern "C" void beActionStarterData_GetMetaObjectFunction(void);
extern "C" void beActionStarterData_InitFields(void);
extern "C" void beActionStarter_CreateInstance(int arg0);
extern "C" igMetaObject *beActionStarter_GetOrCreateMetaObject(void);
extern "C" void *beActionStarter_GetMetaObject(void);
extern "C" int beActionStarter_GetVTable(void);
extern "C" void beActionStarter_EnsureRegistered(void);
extern "C" void *beActionStarter_Register(void);
extern "C" void beActionStarter_GetMetaObjectFunction(void);
extern "C" void beAction2InfoWork_CreateInstance(int arg0);
extern "C" igMetaObject *beAction2InfoWork_GetOrCreateMetaObject(void);
extern "C" int FUN_001d21b0(char *, int);
extern "C" int FUN_00239200(char *, int);
extern "C" int beAction2InfoWork_GetVTable(void);
extern "C" void **FUN_0036c450(void **arg0, short arg1);
extern "C" void beAction2InfoWork_EnsureRegistered(void);
extern "C" void *beAction2InfoWork_Register(void);
extern "C" void beAction2InfoWork_GetMetaObjectFunction(void);
extern "C" int igTextureStateAttr_GetOrCreateMetaObject(void);
extern "C" int igLightingStateAttr_GetOrCreateMetaObject(void);
extern "C" void beAction2InfoWork_InitFields(void);
extern "C" int FUN_001a7a00(char *, int);
extern "C" int FUN_001aa310(char *, int);
extern "C" int beAction2InfoRam_GetVTable(void);
extern "C" void **FUN_0036c790(void **arg0, short arg1);
extern "C" void beAction2InfoRam_EnsureRegistered(void);
extern "C" void *beAction2InfoRam_Register(void);
extern "C" void beAction2InfoRam_GetMetaObjectFunction(void);
extern "C" int igAppearanceList_GetOrCreateMetaObject(void);
extern "C" int igActorList_GetOrCreateMetaObject(void);
extern "C" void beAction2InfoRam_InitFields(void);
extern "C" int beAction2InfoList_GetVTable(void);
extern "C" void beAction2InfoList_EnsureRegistered(void);
extern "C" void *beAction2InfoList_Register(void);
extern "C" void beAction2InfoList_GetMetaObjectFunction(void);
extern "C" int FUN_001aa390(int *, int);
extern "C" int beAction2Info_GetVTable(void);
extern "C" void beAction2Info_EnsureRegistered(void);
extern "C" void *beAction2Info_Register(void);
extern "C" void beAction2Info_GetMetaObjectFunction(void);
extern "C" int igAnimationDatabase_GetOrCreateMetaObject(void);
extern "C" void beAction2Info_InitFields(void);
extern "C" void *beAction2FLASHSET_GetMetaObject(void);
extern "C" int beAction2FLASHSET_GetVTable(void);
extern "C" void beAction2FLASHSET_EnsureRegistered(void);
extern "C" void *beAction2FLASHSET_Register(void);
extern "C" void beAction2FLASHSET_GetMetaObjectFunction(void);
extern "C" void *beAction2WAITCHECK_GetMetaObject(void);
extern "C" int beAction2WAITCHECK_GetVTable(void);
extern "C" void beAction2WAITCHECK_EnsureRegistered(void);
extern "C" void *beAction2WAITCHECK_Register(void);
extern "C" void beAction2WAITCHECK_GetMetaObjectFunction(void);
extern "C" void beAction2WAITCHECK_InitFields(void);
extern "C" void *beAction2FADESET_GetMetaObject(void);
extern "C" int beAction2FADESET_GetVTable(void);
extern "C" void beAction2FADESET_EnsureRegistered(void);
extern "C" void *beAction2FADESET_Register(void);
extern "C" void beAction2FADESET_GetMetaObjectFunction(void);
extern "C" void beAction2FADESET_InitFields(void);
extern "C" void *beAction2JOINTSET_GetMetaObject(void);
extern "C" int beAction2JOINTSET_GetVTable(void);
extern "C" void beAction2JOINTSET_EnsureRegistered(void);
extern "C" void *beAction2JOINTSET_Register(void);
extern "C" void beAction2JOINTSET_GetMetaObjectFunction(void);
extern "C" void beAction2JOINTSET_InitFields(void);
extern "C" void *beAction2MOTIONSET_GetMetaObject(void);
extern "C" int beAction2MOTIONSET_GetVTable(void);
extern "C" void beAction2MOTIONSET_EnsureRegistered(void);
extern "C" void *beAction2MOTIONSET_Register(void);
extern "C" void beAction2MOTIONSET_GetMetaObjectFunction(void);
extern "C" void beAction2MOTIONSET_InitFields(void);
extern "C" igMetaObject *beAction2DataList_GetOrCreateMetaObject(void);
extern "C" void *beAction2DataList_GetMetaObject(void);
extern "C" int beAction2DataList_GetVTable(void);
extern "C" void beAction2DataList_EnsureRegistered(void);
extern "C" void *beAction2DataList_Register(void);
extern "C" void beAction2DataList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beAction2Data_GetOrCreateMetaObject(void);
extern "C" void *beAction2Data_GetMetaObject(void);
extern "C" int beAction2Data_GetVTable(void);
extern "C" void beAction2Data_EnsureRegistered(void);
extern "C" void *beAction2Data_Register(void);
extern "C" void beAction2Data_GetMetaObjectFunction(void);
extern "C" void beAction2Data_InitFields(void);
extern "C" igMetaEnum *beAction2_GetMessageEnum(void);
extern "C" void beAction2_CreateInstance(int arg0);
extern "C" igMetaObject *beAction2_GetOrCreateMetaObject(void);
extern "C" void *beAction2_GetMetaObject(void);
extern "C" int beAction2_GetVTable(void);
extern "C" void beAction2_EnsureRegistered(void);
extern "C" void *beAction2_Register(void);
extern "C" void beAction2_GetMetaObjectFunction(void);
extern "C" void be_CreateInstance(int arg0);
extern "C" igMetaObject *be_GetOrCreateMetaObject(void);
extern "C" void *be_GetMetaObject(void);
extern "C" int be_GetVTable(void);
extern "C" void be_EnsureRegistered(void);
extern "C" void *be_Register(void);
extern "C" void be_GetMetaObjectFunction(void);
extern "C" void be_InitFields(void);
extern "C" void *ParticleArray_GetMetaObject(void);
extern "C" int ParticleArray_GetVTable(void);
extern "C" void ParticleArray_EnsureRegistered(void);
extern "C" void *igParticleArray_Register(void);
extern "C" void *ParticleArray_Register(void);
extern "C" void ParticleArray_GetMetaObjectFunction(void);
extern "C" void ParticleArray_InitFields(void);
extern "C" igMetaObject *ParticleTimer_GetOrCreateMetaObject(void);
extern "C" int ParticleTimer_GetVTable(void);
extern "C" void ParticleTimer_EnsureRegistered(void);
extern "C" void *igGeometry_Register(void);
extern "C" void *ParticleTimer_Register(void);
extern "C" void ParticleTimer_GetMetaObjectFunction(void);
extern "C" void ParticleTimer_InitFields(void);
extern "C" void FUN_003a3900(void);
extern "C" void FUN_0036e860(void);
extern "C" igMetaEnum *FUN_0036e880(void);
extern "C" igMetaEnum *FUN_0036e8e0(void);
extern "C" igMetaEnum *FUN_0036e940(void);
extern "C" igMetaEnum *FUN_0036e9a0(void);
extern "C" int FUN_00132390(int *, int);
extern "C" int ParticleInfo_GetVTable(void);
extern "C" void ParticleInfo_EnsureRegistered(void);
extern "C" void *igSceneInfo_Register(void);
extern "C" void *ParticleInfo_Register(void);
extern "C" void ParticleInfo_GetMetaObjectFunction(void);
extern "C" int igSceneInfo_GetPublishedMetaObject(void);
extern "C" int igImage_GetOrCreateMetaObject(void);
extern "C" int igEnumMetaField_SetDefaultValue(void *field, const int &value);
extern "C" void ParticleInfo_InitFields(void);
extern "C" int memset(int, int, int);
extern "C" int Gap__Core__igObject__resetFields(...);
extern "C" igMetaObject *ParticleInfo_GetMeta(void);
extern "C" igMetaObject *beAction2Data_GetMeta(void);
extern "C" igMetaObject *beAction2DataList_GetMeta(void);
extern "C" igMetaObject *beAction2DataList_GetElementMeta(void);
extern "C" igMetaObject *beAction2MOTIONSET_GetMeta(void);
extern "C" igMetaObject *beAction2JOINTSET_GetMeta(void);
extern "C" igMetaObject *beAction2FADESET_GetMeta(void);
extern "C" igMetaObject *beAction2WAITCHECK_GetMeta(void);
extern "C" igMetaObject *beAction2FLASHSET_GetMeta(void);
extern "C" igMetaObject *beAction2Info_GetMeta(void);
extern "C" igMetaObject *beAction2InfoList_GetMeta(void);
extern "C" igMetaObject *beAction2InfoList_GetElementMeta(void);
extern "C" igMetaObject *beAction2InfoRam_GetMeta(void);
extern "C" igMetaObject *beAction2InfoWork_GetMeta(void);
extern "C" igMetaObject *beActionStarterDataList_GetMeta(void);
extern "C" igMetaObject *beActionStarterDataList_GetElementMeta(void);
extern "C" igMetaObject *beActionStarterData2_GetMeta(void);
extern "C" igMetaObject *beActionStarterData_GetMeta(void);
extern "C" igMetaObject *beAsTargetModelData_GetMeta(void);
extern "C" igMetaObject *beAsTargetModelDataList_GetMeta(void);
extern "C" igMetaObject *beAsTargetModelDataList_GetElementMeta(void);
extern "C" igMetaObject *beActionStarterInfo_GetMeta(void);
extern "C" igMetaObject *beActionStarterInfoRam_GetMeta(void);
extern "C" igMetaObject *beBaseInfoDataList_GetMeta(void);
extern "C" igMetaObject *beBaseInfoDataList_GetElementMeta(void);
extern "C" igMetaObject *beBaseInfoList_GetMeta(void);
extern "C" igMetaObject *beBaseInfoList_GetElementMeta(void);
extern "C" igMetaObject *beBaseInfoManagerList_GetMeta(void);
extern "C" igMetaObject *beBaseInfoManagerList_GetElementMeta(void);
extern "C" igMetaObject *beBaseInfoRamTimer_GetMeta(void);
extern "C" igMetaObject *beBaseInfoRamList_GetMetaObject_Virtual(void);
extern "C" igMetaObject *beBaseInfoRamList_GetElementMeta(void);
extern "C" igMetaObject *beBkColorInfo_GetMeta(void);
extern "C" igMetaObject *beCameraCtrlInfoRamShake_GetMeta(void);
extern "C" igMetaObject *beCameraBoxData_GetMeta(void);
extern "C" igMetaObject *beCameraDemoData_GetMeta(void);
extern "C" igMetaObject *beCameraCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beChangePosTransformInfo_GetMeta(void);
extern "C" igMetaObject *beChangePosTransformInfoRam_GetMeta(void);
extern "C" igMetaObject *beCopyModelCtrl2_GetMeta(void);
extern "C" igMetaObject *beCopyTransform_GetMeta(void);
extern "C" igMetaObject *beCountry_GetMeta(void);
extern "C" igMetaObject *beCriAcxData_GetMeta(void);
extern "C" int Memory_FreeBuffer(...);
extern "C" int Gap__Core__igObject__userDestruct(...);
extern "C" igMetaObject *beCriSndf_GetMeta(void);
extern "C" igMetaObject *beCriAudio_GetMeta(void);
extern "C" igMetaObject *beCriFxXbData_GetMeta(void);
extern "C" igMetaObject *beCriFxInfo_GetMeta(void);
extern "C" igMetaObject *beCriHandle_GetMeta(void);
extern "C" igMetaObject *beCriHandleList_GetMeta(void);
extern "C" igMetaObject *beCriHandleList_GetElementMeta(void);
extern "C" igMetaObject *beCriSfpData_GetMeta(void);
extern "C" igMetaObject *beCriVolume_GetMeta(void);
extern "C" igMetaObject *beDBManagerInfo_GetMeta(void);
extern "C" int igProperty_FindByName(void *, void *, const char *);
extern "C" igMetaObject *beDataBase_GetMeta(void);
extern "C" igMetaObject *beDataBaseList_GetMeta(void);
extern "C" igMetaObject *beDataBaseList_GetElementMeta(void);
extern "C" igMetaObject *beDataObjInt_GetMeta(void);
extern "C" igMetaObject *beDataObjIntList_GetMeta(void);
extern "C" igMetaObject *beDataObjBool_GetMeta(void);
extern "C" igMetaObject *beDataObjBoolList_GetMeta(void);
extern "C" igMetaObject *beDataObjString_GetMeta(void);
extern "C" igMetaObject *beDataObjStringList_GetMeta(void);
extern "C" igMetaObject *beDataObjObjectList_GetMeta(void);
extern "C" igMetaObject *beDataObjFloatList_GetMeta(void);
extern "C" igMetaObject *beDataObjList_GetMeta(void);
extern "C" igMetaObject *beDataObjListList_GetMeta(void);
extern "C" igMetaObject *beDataObjListList_GetElementMeta(void);
extern "C" igMetaObject *beDemoKeepMes_GetMeta(void);
extern "C" igMetaObject *beDemoKeepMesList_GetMeta(void);
extern "C" igMetaObject *beDemoKeepMesList_GetElementMeta(void);
extern "C" igMetaObject *beDemoManagerWork_GetMeta(void);
extern "C" igMetaObject *beDemoManagerWorkList_GetMeta(void);
extern "C" igMetaObject *beDemoManagerWorkList_GetElementMeta(void);
extern "C" igMetaObject *beFileChkObj_GetMeta(void);
extern "C" igMetaObject *beFile_GetMeta(void);
extern "C" igMetaObject *beFileListInfo_GetMeta(void);
extern "C" igMetaObject *beFontGeomAttrPair_GetMeta(void);
extern "C" igMetaObject *beFontGeomAttrPairList_GetMeta(void);
extern "C" igMetaObject *beFontGeomAttrPairList_GetElementMeta(void);
extern "C" igMetaObject *beFontImage_GetMeta(void);
extern "C" int igFont_GetMeta(void);
extern "C" igMetaObject *beFontImageList_GetMeta(void);
extern "C" igMetaObject *beFontImageList_GetElementMeta(void);
extern "C" igMetaObject *beUnicodeObjList_GetMeta(void);
extern "C" igMetaObject *beUnicodeObjList_GetElementMeta(void);
extern "C" igMetaObject *beFontInfoData_GetMeta(void);
extern "C" igMetaObject *beFontInfo_GetMeta(void);
extern "C" igMetaObject *beGeneraterItemDataOne_GetMeta(void);
extern "C" igMetaObject *beGeneraterItemDataOneList_GetMeta(void);
extern "C" igMetaObject *beGeneraterItemDataOneList_GetElementMeta(void);
extern "C" igMetaObject *beGeneraterItemData_GetMeta(void);
extern "C" igMetaObject *beGeneraterItemDataList_GetMeta(void);
extern "C" igMetaObject *beGeneraterItemDataList_GetElementMeta(void);
extern "C" igMetaObject *beGeneraterPlayerData_GetMeta(void);
extern "C" igMetaObject *beGeneraterPlayerDataList_GetMeta(void);
extern "C" igMetaObject *beGeneraterPlayerDataList_GetElementMeta(void);
extern "C" igMetaObject *beGeneraterData_GetMeta(void);
extern "C" igMetaObject *beGeneraterDataList_GetMeta(void);
extern "C" igMetaObject *beGeneraterDataList_GetElementMeta(void);
extern "C" igMetaObject *beGeneraterInfo_GetMeta(void);
extern "C" igMetaObject *beGeneraterInfoRam_GetMeta(void);
extern "C" igMetaObject *beGeneraterInfoWork_GetMeta(void);
extern "C" igMetaObject *beGroupKeep_GetMeta(void);
extern "C" igMetaObject *beGroupKeepList_GetMeta(void);
extern "C" igMetaObject *beGroupKeepList_GetElementMeta(void);
extern "C" igMetaObject *beHitLandDelivInfo_GetMeta(void);
extern "C" igMetaObject *beHitLandDelivInfoRam_GetMeta(void);
extern "C" igMetaObject *beHitLandResultData_GetMeta(void);
extern "C" igMetaObject *beHitLandResultDataList_GetMeta(void);
extern "C" igMetaObject *beHitLandResultDataList_GetElementMeta(void);
extern "C" igMetaObject *beHitLandModelTraversal_GetMeta(void);
extern "C" igMetaObject *beHitLandModelInfo_GetMeta(void);
extern "C" igMetaObject *beHitLandModelInfoRam_GetMeta(void);
extern "C" igMetaObject *beLOA_GetMeta(void);
extern "C" igMetaObject *beLayerGroup_GetMeta(void);
extern "C" igMetaObject *beLayerGroupList_GetMeta(void);
extern "C" igMetaObject *beLayerGroupList_GetElementMeta(void);
extern "C" igMetaObject *beLayerInfo_GetMeta(void);
extern "C" igMetaObject *beLayerInfoRam_GetMeta(void);
extern "C" igMetaObject *beLightCtrlInfo_GetMeta(void);
extern "C" igMetaObject *igLightSetList_GetMeta(void);
extern "C" int igLightSetList_GetElementMeta(void);
extern "C" igMetaObject *beLuaDataObject_GetMeta(void);
extern "C" igMetaObject *beLuaDataObjectist_GetMeta(void);
extern "C" igMetaObject *beLuaDataObjectist_GetElementMeta(void);
extern "C" igMetaObject *beLuaData_GetMeta(void);
extern "C" igMetaObject *beLuaDataList_GetMeta(void);
extern "C" igMetaObject *beLuaDataList_GetElementMeta(void);
extern "C" igMetaObject *beLuaInfo_GetMeta(void);
extern "C" igMetaObject *beMatCtrlData_GetMeta(void);
extern "C" igMetaObject *beMatCtrlDataList_GetMeta(void);
extern "C" igMetaObject *beMatCtrlDataList_GetElementMeta(void);
extern "C" igMetaObject *beMatCtrlSearch_GetMeta(void);
extern "C" igMetaObject *beMatCtrlSearchList_GetMeta(void);
extern "C" igMetaObject *beMatCtrlSearchList_GetElementMeta(void);
extern "C" igMetaObject *beMatCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beMatCtrlInfoRam_GetMeta(void);
extern "C" igMetaObject *beMatCtrlInfoWork_GetMeta(void);
extern "C" igMetaObject *beMessengerArgData_GetMeta(void);
extern "C" igMetaObject *beMessengerArgDataList_GetMeta(void);
extern "C" igMetaObject *beMessengerArgDataList_GetElementMeta(void);
extern "C" igMetaObject *beMessengerDelay_GetMeta(void);
extern "C" igMetaObject *beMessengerDelayList_GetMeta(void);
extern "C" igMetaObject *beMessengerDelayList_GetElementMeta(void);
extern "C" igMetaObject *beMessengerGroup_GetMeta(void);
extern "C" igMetaObject *beMessengerGroupList_GetMeta(void);
extern "C" igMetaObject *beMessengerGroupList_GetElementMeta(void);
extern "C" igMetaObject *beMessengerWork_GetMetaObject_Virtual(void);
extern "C" igMetaObject *beMessengerWorkList_GetMeta(void);
extern "C" igMetaObject *beMessengerWorkList_GetElementMeta(void);
extern "C" igMetaObject *beMeterCtrlOneData_GetMeta(void);
extern "C" igMetaObject *beMeterCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beMeterCtrlInfoList_GetMeta(void);
extern "C" igMetaObject *beMeterCtrlInfoList_GetElementMeta(void);
extern "C" igMetaObject *beMeterCtrlNode_GetMeta(void);
extern "C" igMetaObject *beModelCtrlData_GetMeta(void);
extern "C" igMetaObject *beModelCtrlDataList_GetMeta(void);
extern "C" igMetaObject *beModelCtrlDataList_GetElementMeta(void);
extern "C" igMetaObject *beModelCtrlLUACALL_GetMeta(void);
extern "C" igMetaObject *beModelCtrlLABEL_GetMeta(void);
extern "C" igMetaObject *beModelCtrlLABELCTRL_GetMeta(void);
extern "C" igMetaObject *beModelCtrlACTION_GetMeta(void);
extern "C" igMetaObject *beModelCtrlJUMP_GetMeta(void);
extern "C" igMetaObject *beModelCtrlCTRL_GetMeta(void);
extern "C" igMetaObject *beModelCtrlMSGBOX_GetMeta(void);
extern "C" igMetaObject *beModelCtrlMOVE_GetMeta(void);
extern "C" igMetaObject *beModelCtrlMOVEEX_GetMeta(void);
extern "C" igMetaObject *beModelCtrlMOVERL_GetMeta(void);
extern "C" igMetaObject *beModelCtrlPDMOVE_GetMeta(void);
extern "C" igMetaObject *beModelCtrlWCHECK_GetMeta(void);
extern "C" igMetaObject *beModelCtrlAIMAP_GetMeta(void);
extern "C" igMetaObject *beModelCtrlMUTEKI_GetMeta(void);
extern "C" igMetaObject *beModelCtrlHITBOX_GetMeta(void);
extern "C" igMetaObject *beModelCtrlAIData_GetMeta(void);
extern "C" igMetaObject *beModelCtrlAIDataList_GetMeta(void);
extern "C" igMetaObject *beModelCtrlAIDataList_GetElementMeta(void);
extern "C" igMetaObject *beModelCtrlAIMap_GetMeta(void);
extern "C" igMetaObject *beModelCtrlAIMapList_GetMeta(void);
extern "C" igMetaObject *beModelCtrlAIMapList_GetElementMeta(void);
extern "C" igMetaObject *beModelCtrlInfoDataAIM_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoDataAIH_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoDataHit_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoDataSeq_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoDataTrc_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoRamData_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoList_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoList_GetElementMeta(void);
extern "C" igMetaObject *beModelCtrlMoveObject_GetMeta(void);
extern "C" igMetaObject *beModelCtrlMoveObjectList_GetMeta(void);
extern "C" igMetaObject *beModelCtrlMoveObjectList_GetElementMeta(void);
extern "C" igMetaObject *beModelCtrlInfoHitBody_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoAI_GetMeta(void);
extern "C" igMetaObject *beModelCtrlInfoRideOn_GetMeta(void);
extern "C" void beModelCtrlInfoRideOn_Move(void);
extern "C" igMetaObject *beModelCtrlInfoWork_GetMeta(void);
extern "C" igMetaObject *beModelCtrlNode2_GetMeta(void);
extern "C" int beModelCtrlSubComBase_Update(void);
extern "C" void beModelCtrlSCHitBox_Stop(void);
extern "C" igMetaObject *beModelCtrlSubCom_GetMeta(void);
extern "C" igMetaObject *beMovieInfoData_GetMeta(void);
extern "C" igMetaObject *beMovieInfo_GetMeta(void);
extern "C" igMetaObject *beLoadingNode_GetMeta(void);
extern "C" igMetaObject *beNodeAnim_GetMeta(void);
extern "C" igMetaObject *beNumberCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beNumberCtrlInfoList_GetMeta(void);
extern "C" igMetaObject *beNumberCtrlInfoList_GetElementMeta(void);
extern "C" igMetaObject *beNumVerInsideData_GetMeta(void);
extern "C" igMetaObject *beNumVerInsideDataList_GetMeta(void);
extern "C" igMetaObject *beNumVerInsideDataList_GetElementMeta(void);
extern "C" igMetaObject *beNumVerData_GetMeta(void);
extern "C" int Gap__Core__igObject__userConstruct(...);
extern "C" int igMetaObject_CountInstances(...);
extern "C" void *igObject_GetAllocator(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void **FUN_0036fa60(void **arg0, short arg1);
extern "C" igMetaObject *beNumVerDataList_GetMeta(void);
extern "C" igMetaObject *beNumVerDataList_GetElementMeta(void);
extern "C" igMetaObject *beNumberCtrlInfoRam_GetMeta(void);
extern "C" igMetaObject *beNumberCtrlInfoWork_GetMeta(void);
extern "C" igMetaObject *beOptInfo_GetMeta(void);
extern "C" igMetaObject *bePadDataList_GetMeta(void);
extern "C" igMetaObject *bePadDataList_GetElementMeta(void);
extern "C" igMetaObject *beParticleCtrl2Info_GetMeta(void);
extern "C" igMetaObject *beParticleCtrl2InfoWork_GetMeta(void);
extern "C" igMetaObject *beParticleCtrl2InfoRam_GetMeta(void);
extern "C" igMetaObject *bePoint01Info_GetMeta(void);
extern "C" igMetaObject *beResetNode_GetMeta(void);
extern "C" igMetaObject *beSvDeliver_GetMeta(void);
extern "C" igMetaObject *beSaveDataDeliver_GetMeta(void);
extern "C" void beSaveDataDeliver_userConstruct(void **arg0);
extern "C" igMetaObject *beSvSlotXbox_GetMeta(void);
extern "C" igMetaObject *beSvSlotGC_GetMeta(void);
extern "C" igMetaObject *beSvSlotPS2_GetMeta(void);
extern "C" igMetaObject *beSvSlotDataList_GetMeta(void);
extern "C" igMetaObject *beSvSlotDataList_GetElementMeta(void);
extern "C" igMetaObject *beSvPlatDataGC_GetMeta(void);
extern "C" void beSvPlatDataGC_userConstruct(void **arg0);
extern "C" igMetaObject *beSvPs2McImage128k_GetMeta(void);
extern "C" int Memory_AllocateDefaultBuffer(...);
extern "C" void beSvPs2McImage128k_userDestruct(void *arg0);
extern "C" igMetaObject *beSvPlatDataPS2_GetMeta(void);
extern "C" igMetaObject *beXboxImage24k_GetMeta(void);
extern "C" igMetaObject *beSvPlatDataXbox_GetMeta(void);
extern "C" igMetaObject *beSvPlatDataPC_GetMeta(void);
extern "C" igMetaObject *beSvPlatBaseData_GetMeta(void);
extern "C" igMetaObject *beSaveUtilInfo_GetMeta(void);
extern "C" igMetaObject *beSaveUtilInfoRam_GetMeta(void);
extern "C" igMetaObject *beSeData_GetMeta(void);
extern "C" igMetaObject *beSeDataList_GetMeta(void);
extern "C" igMetaObject *beSeDataList_GetElementMeta(void);
extern "C" igMetaObject *beSeInfoData_GetMeta(void);
extern "C" igMetaObject *beSeInfo_GetMeta(void);
extern "C" igMetaObject *beSelectCtrlInfoWork_GetMeta(void);
extern "C" igMetaObject *beSelectCtrlInfoRamData_GetMeta(void);
extern "C" igMetaObject *beSelectCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beShadow01Info_GetMeta(void);
extern "C" igMetaObject *beShadow01InfoList_GetMeta(void);
extern "C" igMetaObject *beShadow01InfoList_GetElementMeta(void);
extern "C" igMetaObject *bePlaySE_GetMeta(void);
extern "C" igMetaObject *bePlaySEList_GetMeta(void);
extern "C" igMetaObject *bePlaySEList_GetElementMeta(void);
extern "C" igMetaObject *beSoundData_GetMeta(void);
extern "C" igMetaObject *beBaseInfoData_GetMeta(void);
extern "C" igMetaObject *beSoundInfo_GetMeta(void);
extern "C" igMetaObject *beStaticInfo_GetMeta(void);
extern "C" igMetaObject *beSwitchCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beTextureCtrlWork_GetMeta(void);
extern "C" igMetaObject *beTextureCtrlData_GetMeta(void);
extern "C" igMetaObject *beTextureCtrlAttr_GetMeta(void);
extern "C" igMetaObject *beTextureCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beTextureCtrlInfoList_GetMeta(void);
extern "C" igMetaObject *beTextureCtrlInfoList_GetElementMeta(void);
extern "C" igMetaObject *beTimerData_GetMeta(void);
extern "C" igMetaObject *beTimerDataList_GetMeta(void);
extern "C" igMetaObject *beTimerDataList_GetElementMeta(void);
extern "C" igMetaObject *beTransformSync_GetMeta(void);
extern "C" int igMatrix44f_Copy(...);
extern "C" igMetaObject *beUnicode_GetMeta(void);
extern "C" igMetaObject *beWaterPlainInfo_GetMeta(void);
extern "C" igMetaObject *beWaterMoveData_GetMeta(void);
extern "C" igMetaObject *beWaterMoveDataList_GetMeta(void);
extern "C" igMetaObject *beWaterMoveDataList_GetElementMeta(void);
extern "C" igMetaObject *beWaterMove_GetMeta(void);
extern "C" igMetaObject *beWaterPlainInfoRam_GetMeta(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelectList_GetMeta(void);
extern "C" igMetaObject *igAppearanceListList_GetMeta(void);
extern "C" int igAppearanceListList_GetElementMeta(void);
extern "C" igMetaObject *beWeaponAttachData_GetMeta(void);
extern "C" igMetaObject *beWeaponAttachDataList_GetMeta(void);
extern "C" igMetaObject *beWeaponAttachDataList_GetElementMeta(void);
extern "C" igMetaObject *beWeaponSeqData_GetMeta(void);
extern "C" igMetaObject *beWeaponSeqDataList_GetMeta(void);
extern "C" igMetaObject *beWeaponSeqDataList_GetElementMeta(void);
extern "C" igMetaObject *beWeaponInfo_GetMeta(void);
extern "C" igMetaObject *beBaseInfo_GetMeta(void);
extern "C" igMetaObject *beWeaponInfoRam_GetMeta(void);
extern "C" igMetaObject *beBaseInfoRam_GetMeta(void);
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
extern "C" int g_igInsightPlugin_vtable[4];
struct igMetaObject_33e370;
extern "C" igMetaObject_33e370 *igInsightPlugin_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beWeaponInfoRam_metaObject;
struct G { int pad[9]; int f; };
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[48]; };
extern "C" int g_beWeaponInfoRam_vtable[4];
extern "C" int g_beBaseInfoRam_vtable[4];
extern "C" void * g_objectSystem[4];
typedef struct { int vt; char p[36]; char *m; } S;
extern "C" void *FUN_0033e920(S *arg0, long long arg1);
extern "C" ObjectRefWord *ObjectRef_Destruct_0033e9c0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beWeaponInfo_metaObject;
struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; };
extern "C" int g_beWeaponInfo_vtable[4];
extern "C" igObject **FUN_0033ec00(igObject **arg0, short arg1);
extern "C" int g_igNamedObject_vtable[4];
extern "C" int g_igInfo_vtable[4];
extern "C" int g_beBaseInfo_vtable[4];
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
extern "C" int kIGMemoryPoolHandleMetaData[4];
extern "C" igMetaObject *g_beWeaponSeqDataList_metaObject;
union U_33f080 { int vt; char b[32]; };
extern "C" int g_beWeaponSeqDataList_vtable[4];
struct igMetaObject_33f0e0;
extern "C" igMetaObject_33f0e0 * igObjectList_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beWeaponSeqData_metaObject;
struct T_33f1c0 { int word0; int references; };
extern "C" int g_beWeaponSeqData_vtable[4];
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
extern "C" int g_beWeapon_vtable[4];
extern "C" int DAT_0052cf80[4];
extern "C" int g_beBaseInfoManager_vtable[4];
typedef struct R_33f5e0 { int w0; int refs; } R_33f5e0;
typedef struct O_33f5e0 { int *vt; int f4; int *str; int f12; int f16; int f20; R_33f5e0 *ref; } O_33f5e0;
extern "C" O_33f5e0 *FUN_0033f5e0(O_33f5e0 *arg0, short arg1);
extern "C" igMetaObject *g_beWeaponAttachDataList_metaObject;
extern "C" igMetaObject *beWeaponAttachDataList_GetMetaObject(void);
extern "C" int g_beWeaponAttachDataList_vtable[4];
extern "C" igMetaObject *g_beWeaponAttachData_metaObject;
extern "C" igMetaObject *beWeaponAttachData_GetMetaObject(void);
struct T_33fb10 { int word0; int references; };
extern "C" int g_beWeaponAttachData_vtable[4];
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
extern "C" igMetaObject *igAppearanceListList_GetMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_33fe10;
extern "C" int g_igAppearanceListList_vtable[4];
extern "C" igMetaObject *igModelViewMatrixBoneSelectListBec_GetMetaObject(void);
struct Obj_33ffa0 { int *vt; char pad[28]; };
extern "C" int g_igModelViewMatrixBoneSelectListBec_vtable[4];
extern "C" igMetaObject *g_beWaterPlainInfoRam_metaObject;
struct Obj_3400e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; int w28; int w29; int w30; int w31; int w32; int w33; int w34; int w35; int w36; int w37; int w38; int w39; int w40; int w41; int w42; int w43; int w44; int w45; int w46; int w47; };
extern "C" int g_beWaterPlainInfoRam_vtable[4];
extern "C" void **FUN_003401c0(struct Ref **self, short flag);
extern "C" igMetaObject *g_beWaterMove_metaObject;
struct W { int *vt; int f[11]; };
extern "C" int g_beWaterMove_vtable[4];
extern "C" igMetaObject *g_beWaterMoveDataList_metaObject;
struct Obj_3407c0 { int *vt; char pad[28]; };
extern "C" int g_beWaterMoveDataList_vtable[4];
extern "C" igMetaObject *g_beWaterMoveData_metaObject;
union U_340900 { int vt; char b[32]; };
extern "C" int g_beWaterMoveData_vtable[4];
extern "C" igMetaObject *g_beWaterPlainInfo_metaObject;
struct W_340b40 { int *vt; int f[7]; };
extern "C" int g_beWaterPlainInfo_vtable[4];
extern "C" igMetaObject *g_beWaterPlain_metaObject;
union U_340da0 { int vt; char b[32]; };
extern "C" int g_beWaterPlain_vtable[4];
extern "C" igMetaObject *g_beUnicode_metaObject;
union U_340f80 { int vt; int w[2]; void *p[2]; char b[8]; };
extern "C" int g_beUnicode_vtable[4];
extern "C" igMetaObject *g_beTransformSync_metaObject;
extern "C" int g_igTransform_vtable[4];
extern "C" int g_beTransformSync_vtable[4];
/* igObject, constructed by igObject_InitHeader. */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igInsightPlugin, constructed out of line; its vtable pointer is where igObject keeps _vtable. */
struct InsightPluginView { virtual void firstSlot(); unsigned int refCount; InsightPluginView(); };
/* The object references of libBecRuntimePlugin, one class per referenced type. */
struct ParticleCtrl2Field { int *p; ParticleCtrl2Field() throw(); ~ParticleCtrl2Field(); };
struct LuaManagerField { int *p; LuaManagerField() throw(); ~LuaManagerField(); };
struct MatCtrlField { int *p; MatCtrlField() throw(); ~MatCtrlField(); };
struct SelectCtrlField { int *p; SelectCtrlField() throw(); ~SelectCtrlField(); };
struct WaterPlainField { int *p; WaterPlainField() throw(); ~WaterPlainField(); };
struct Action2Field { int *p; Action2Field() throw(); ~Action2Field(); };
struct MeterCtrlField { int *p; MeterCtrlField() throw(); ~MeterCtrlField(); };
struct TargetObjField { int *p; TargetObjField() throw(); ~TargetObjField(); };
struct WeaponField { int *p; WeaponField() throw(); ~WeaponField(); };
struct CameraCtrlField { int *p; CameraCtrlField() throw(); ~CameraCtrlField(); };
struct Point01Field { int *p; Point01Field() throw(); ~Point01Field(); };
struct BkColorField { int *p; BkColorField() throw(); ~BkColorField(); };
struct CpTransformField { int *p; CpTransformField() throw(); ~CpTransformField(); };
struct Shadow01Field { int *p; Shadow01Field() throw(); ~Shadow01Field(); };
struct GeneraterField { int *p; GeneraterField() throw(); ~GeneraterField(); };
struct HitLandModelField { int *p; HitLandModelField() throw(); ~HitLandModelField(); };
struct HitLandDelivField { int *p; HitLandDelivField() throw(); ~HitLandDelivField(); };
struct SoundField { int *p; SoundField() throw(); ~SoundField(); };
struct SeCtlField { int *p; SeCtlField() throw(); ~SeCtlField(); };
struct ActionStarterField { int *p; ActionStarterField() throw(); ~ActionStarterField(); };
struct LayerCtlField { int *p; LayerCtlField() throw(); ~LayerCtlField(); };
struct FontField { int *p; FontField() throw(); ~FontField(); };
struct SwitchCtrlField { int *p; SwitchCtrlField() throw(); ~SwitchCtrlField(); };
struct LightCtrlField { int *p; LightCtrlField() throw(); ~LightCtrlField(); };
struct NumberCtrlField { int *p; NumberCtrlField() throw(); ~NumberCtrlField(); };
struct StaticInfoCtlField { int *p; StaticInfoCtlField() throw(); ~StaticInfoCtlField(); };
struct MovieField { int *p; MovieField() throw(); ~MovieField(); };
struct DbManagerField { int *p; DbManagerField() throw(); ~DbManagerField(); };
struct SaveUtilField { int *p; SaveUtilField() throw(); ~SaveUtilField(); };
struct TextureCtrlField { int *p; TextureCtrlField() throw(); ~TextureCtrlField(); };
struct SystemField { int *p; SystemField() throw(); ~SystemField(); };
struct MessengerField { int *p; MessengerField() throw(); ~MessengerField(); };
struct FileListField { int *p; FileListField() throw(); ~FileListField(); };
struct PadManagerField { int *p; PadManagerField() throw(); ~PadManagerField(); };
struct CriField { int *p; CriField() throw(); ~CriField(); };
struct LuaInterfaceField { int *p; LuaInterfaceField() throw(); ~LuaInterfaceField(); };
struct DemoManagerField { int *p; DemoManagerField() throw(); ~DemoManagerField(); };
struct TimerField { int *p; TimerField() throw(); ~TimerField(); };
struct MemoryField { int *p; MemoryField() throw(); ~MemoryField(); };
/* libBecRuntimePlugin with the constructors and destructors of its references called out of line. */
struct BecRuntimePluginView : InsightPluginView {
    ParticleCtrl2Field       particleCtrl2;    /* +8   _particleCtrl2 */
    LuaManagerField          luaManager;       /* +12  _luaManager */
    MatCtrlField             matCtrl;          /* +16  _matCtrl */
    SelectCtrlField          selectCtrl;       /* +20  _selectCtrl */
    WaterPlainField          waterPlain;       /* +24  _waterPlain */
    Action2Field             action2;          /* +28  _action2 */
    MeterCtrlField           meterCtrl;        /* +32  _meterCtrl */
    TargetObjField           targetObj;        /* +36  _targetObj */
    WeaponField              weapon;           /* +40  _weapon */
    CameraCtrlField          cameraCtrl;       /* +44  _cameraCtrl */
    Point01Field             point01;          /* +48  _point01 */
    BkColorField             bkColor;          /* +52  _bkColor */
    CpTransformField         cpTransform;      /* +56  _cpTransform */
    Shadow01Field            shadow01;         /* +60  _shadow01 */
    GeneraterField           generater;        /* +64  _generater */
    HitLandModelField        hitLandModel;     /* +68  _hitLandModel */
    HitLandDelivField        hitLandDeliv;     /* +72  _hitLandDeliv */
    SoundField               sound;            /* +76  _sound */
    SeCtlField               seCtl;            /* +80  _seCtl */
    ActionStarterField       actionStarter;    /* +84  _actionStarter */
    LayerCtlField            layerCtl;         /* +88  _layerCtl */
    FontField                font;             /* +92  _font */
    SwitchCtrlField          switchCtrl;       /* +96  _switchCtrl */
    LightCtrlField           lightCtrl;        /* +100 _lightCtrl */
    NumberCtrlField          numberCtrl;       /* +104 _numberCtrl */
    StaticInfoCtlField       staticInfoCtl;    /* +108 _staticInfoCtl */
    MovieField               movie;            /* +112 _movie */
    DbManagerField           dbManager;        /* +116 _dbManager */
    SaveUtilField            saveUtil;         /* +120 _saveUtil */
    TextureCtrlField         textureCtrl;      /* +124 _textureCtrl */
    SystemField              system;           /* +128 _system */
    MessengerField           messenger;        /* +132 _messenger */
    FileListField            fileList;         /* +136 _fileList */
    PadManagerField          padManager;       /* +140 _padManager */
    CriField                 cri;              /* +144 _cri */
    LuaInterfaceField        luaInterface;     /* +148 _luaInterface */
    DemoManagerField         demoManager;      /* +152 _demoManager */
    TimerField               timer;            /* +156 _timer */
    MemoryField              memory;           /* +160 _memory */
    virtual void firstSlot();
};
/* igMatrix44f, constructed by igMatrix44f_SetIdentity. */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _syncTransformList (igObjectRefMetaField). */
struct SyncTransformListField { int *p; SyncTransformListField() { p = 0; } ~SyncTransformListField(); };
/* Stores a derived vtable before the class's first member constructor runs. */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = g_igTransform_vtable; } };
struct TransformSyncVtable { TransformSyncVtable(int **slot) { *slot = g_beTransformSync_vtable; } };
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
    ~TransformSyncView() { vtable = g_beTransformSync_vtable; }
};
extern "C" O *FUN_00341160(O *arg0, short arg1);
struct igMetaObject_341200;
extern "C" igMetaObject_341200 * igTransform_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beTimer_metaObject;
extern "C" int g_beTimer_vtable[4];
struct igMetaObject_341520;
extern "C" igMetaObject_341520 * igInfoManager_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beTimerDataList_metaObject;
struct Obj_341750 { int *vt; char pad[28]; };
extern "C" int g_beTimerDataList_vtable[4];
extern "C" igMetaObject *g_beTimerData_metaObject;
extern "C" igMetaObject *beTimerData_GetMetaObject(void);
extern "C" int g_beTimerData_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlInfoList_metaObject;
extern "C" igMetaObject *beTextureCtrlInfoList_GetMetaObject(void);
struct Obj_341af0 { int *vt; char pad[28]; };
extern "C" int g_beTextureCtrlInfoList_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlInfo_metaObject;
extern "C" igMetaObject *beTextureCtrlInfo_GetMetaObject(void);
extern "C" int g_beTextureCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlAttr_metaObject;
extern "C" igMetaObject *beTextureCtrlAttr_GetMetaObject(void);
union U_341e60 { int vt; char b[16]; };
extern "C" int g_beTextureCtrlAttr_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlData_metaObject;
extern "C" int g_beTextureCtrlData_vtable[4];
extern "C" igMetaObject *g_beTextureCtrl_metaObject;
typedef struct { int *vt; int w[8]; int s; } Obj_3423f0;
extern "C" int g_beTextureCtrl_vtable[4];
typedef struct S_temp_a0_342460 { char pad4[4]; int f4; } S_temp_a0_342460;
extern "C" igMetaObject *g_beTextureCtrlWork_metaObject;
union U_342710 { int vt; char b[16]; };
extern "C" int g_beTextureCtrlWork_vtable[4];
extern "C" igMetaObject *g_beTargetObj_metaObject;
union U_342a50 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int g_beTargetObj_vtable[4];
extern "C" igMetaObject *g_beSystem_metaObject;
struct Obj_342d80 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" int g_beSystem_vtable[4];
typedef struct S_temp_a0_342eb0 { char pad4[4]; int f4; } S_temp_a0_342eb0;
extern "C" igMetaObject *g_beSwitchCtrlInfo_metaObject;
struct Obj_3431e0 { int *vt; int w[7]; };
extern "C" int g_beSwitchCtrlInfo_vtable[4];
extern "C" ObjectRefWord *FUN_00343260(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beSwitchCtrl_metaObject;
union U_343570 { int vt; char b[32]; };
extern "C" int g_beSwitchCtrl_vtable[4];
extern "C" igMetaObject *g_beStaticInfoCtl_metaObject;
struct Obj_343840 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_beStaticInfoCtl_vtable[4];
extern "C" igMetaObject *g_beStaticInfo_metaObject;
union U_343a60 { int vt; char b[32]; };
extern "C" int g_beStaticInfo_vtable[4];
extern "C" igMetaObject *g_beBinDataObject_metaObject;
extern "C" igMetaObject *g_beSoundInfo_metaObject;
extern "C" igMetaObject *beSoundInfo_GetMetaObject(void);
extern "C" int g_beSoundInfo_vtable[4];
extern "C" igMetaObject *g_beSoundData_metaObject;
extern "C" igMetaObject *beSoundData_GetMetaObject(void);
union U_343fa0 { int vt; int w[5]; char b[20]; };
extern "C" int g_beSoundData_vtable[4];
extern "C" int g_beBaseInfoData_vtable[4];
struct W_344030 { int *vt; int pad; int *name; };
extern "C" struct W_344030 *FUN_00344030(struct W_344030 *arg0, short arg1);
extern "C" igMetaObject *g_beSound_metaObject;
extern "C" igMetaObject *beSound_GetMetaObject(void);
extern "C" int g_beSound_vtable[4];
extern "C" igMetaObject *g_bePlaySEList_metaObject;
extern "C" igMetaObject *bePlaySEList_GetMetaObject(void);
struct Obj_3446d0 { int *vt; char pad[28]; };
extern "C" int g_bePlaySEList_vtable[4];
extern "C" igMetaObject *g_bePlaySE_metaObject;
extern "C" int g_bePlaySE_vtable[4];
extern "C" igMetaObject *g_beShadow01InfoList_metaObject;
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_344a50;
extern "C" int g_beShadow01InfoList_vtable[4];
extern "C" igMetaObject *g_beShadow01Info_metaObject;
extern "C" int g_beShadow01Info_vtable[4];
extern "C" ObjectRefWord *FUN_00344c40(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beShadow01_metaObject;
extern "C" int g_beShadow01_vtable[4];
extern "C" struct R **FUN_00344f90(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beSelectCtrlInfo_metaObject;
struct F { int *vt; int w[7]; };
extern "C" int g_beSelectCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beSelectCtrlInfoRamData_metaObject;
struct T_345330 { int word0; int references; };
extern "C" int g_beSelectCtrlInfoRamData_vtable[4];
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
extern "C" int g_beSelectCtrlInfoWork_vtable[4];
extern "C" igMetaObject *g_beSelectCtrl_metaObject;
extern "C" int g_beSelectCtrl_vtable[4];
extern "C" igMetaObject *g_beSeInfo_metaObject;
struct W_345d80 { int *vt; int w[7]; };
extern "C" int g_beSeInfo_vtable[4];
extern "C" igMetaObject *g_beSeInfoData_metaObject;
struct T_345ef0 { int word0; int references; };
extern "C" int g_beSeInfoData_vtable[4];
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
extern "C" igMetaObject *beSeDataList_GetMetaObject(void);
struct Obj_3461c0 { int *vt; char pad[28]; };
extern "C" int g_beSeDataList_vtable[4];
extern "C" igMetaObject *g_beSeData_metaObject;
extern "C" igMetaObject *beSeData_GetMetaObject(void);
extern "C" int g_beSeData_vtable[4];
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
extern "C" igMetaObject *beSeCtl_GetMetaObject(void);
union U_3465d0 { int vt; int w[4]; void *p[4]; char b[48]; };
extern "C" int g_beSeCtl_vtable[4];
extern "C" igMetaObject *g_beSaveUtilInfoRam_metaObject;
extern "C" igMetaObject *beSaveUtilInfoRam_GetMetaObject(void);
struct Obj_346860 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; char *w10; int w11; char *w12; int w13; int w14; int w15; };
extern "C" int g_beSaveUtilInfoRam_vtable[4];
extern "C" igMetaObject *g_beSaveUtilInfo_metaObject;
extern "C" int g_beSaveUtilInfo_vtable[4];
struct Obj_346b00 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" igMetaObject *g_beSaveUtil_metaObject;
struct Obj_346d60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_beSaveUtil_vtable[4];
extern "C" igMetaObject *g_beSvPlatDataPC_metaObject;
union U_3470b0 { int vt; char b[32]; };
extern "C" int g_beSvPlatDataPC_vtable[4];
extern "C" int g_beSvPlatBaseData_vtable[4];
struct Q { char pad4[4]; int f4; };
struct O_347150 { int *vt; int p4; int p8; Q *m; };
extern "C" O_347150 *FUN_00347150(O_347150 *arg0, short arg1);
extern "C" igMetaObject *g_beSvPlatDataXbox_metaObject;
extern "C" int g_beSvPlatDataXbox_vtable[4];
struct T_3474b0 { int w0; int refs; char pad[20]; int *f1c; };
struct F_3474b0 { char pad[52]; unsigned char b52; char pad2[3]; int f56; };
struct G_3474b0 { char pad[52]; int w52; };
extern "C" igMetaObject *g_beXboxImage24k_metaObject;
struct Obj_3476a0 { int *vt; char pad[12]; };
extern "C" int g_beXboxImage24k_vtable[4];
extern "C" igMetaObject *g_beSvPlatDataPS2_metaObject;
union U_347870 { int vt; char b[224]; };
extern "C" int g_beSvPlatDataPS2_vtable[4];
extern "C" igMetaObject *g_beSvPs2McImage128k_metaObject;
struct Obj_347ca0 { int *vt; char pad[8]; };
extern "C" int g_beSvPs2McImage128k_vtable[4];
extern "C" igMetaObject *g_beSvPlatDataGC_metaObject;
union U_347e70 { int vt; char b[144]; };
extern "C" int g_beSvPlatDataGC_vtable[4];
struct T_348000 { int w0; int refs; char pad[20]; int *f1c; };
struct G_348000 { char pad[52]; int w52; };
struct H { char pad[60]; int f60; };
extern "C" igMetaObject *g_beSvConnectCheck_metaObject;
union U_348250 { int vt; char b[144]; };
extern "C" int g_beSvConnectCheck_vtable[4];
extern "C" int g_beSaveApi_vtable[4];
struct R_348390 { int w0; int rc; };
struct S_348390 {
    void *f0;
    char pad[44];
    struct R_348390 *f48;
    struct R_348390 *f52;
    struct R_348390 *f56;
};
extern "C" void *FUN_00348390(struct S_348390 *arg0, short arg1);
extern "C" void **igSmartPointer_beSaveMemoryObj_Destruct(struct Ref **self, short flag);
extern "C" igMetaObject *g_beSaveApi_metaObject;
extern "C" igMetaObject *g_beSvEndApi_metaObject;
struct T_348680 { int word0; int references; };
extern "C" int g_beSvEndApi_vtable[4];
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
extern "C" igMetaObject *beSvStartApi_GetMetaObject(void);
union U_3489c0 { int vt; char b[64]; };
extern "C" int g_beSvStartApi_vtable[4];
struct T_348bb0 { int word0; int references; int pad[5]; int f28; };
extern "C" igMetaObject *g_beSvGetFreeSizeApi_metaObject;
extern "C" igMetaObject *beSvGetFreeSizeApi_GetMetaObject(void);
union U_348d00 { int vt; char b[96]; };
extern "C" int g_beSvGetFreeSizeApi_vtable[4];
extern "C" igMetaObject *g_beSvWriteMediaApi_metaObject;
extern "C" igMetaObject *beSvWriteMediaApi_GetMetaObject(void);
struct Obj_348ff0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int g_beSvWriteMediaApi_vtable[4];
extern "C" igMetaObject *g_beSvReadMediaApi_metaObject;
extern "C" igMetaObject *beSvReadMediaApi_GetMetaObject(void);
struct Obj_349300 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
extern "C" int g_beSvReadMediaApi_vtable[4];
extern "C" O *FUN_003493b0(O *arg0, short arg1);
extern "C" igMetaObject *g_beSvUseCheckApi_metaObject;
union U_349680 { int vt; int w[4]; void *p[4]; char b[80]; };
extern "C" int g_beSvUseCheckApi_vtable[4];
extern "C" igMetaObject *g_beSvFormatApi_metaObject;
union U_349900 { int vt; char b[56]; };
extern "C" int g_beSvFormatApi_vtable[4];
extern "C" igMetaObject *g_beSvFileFindApi_metaObject;
union U_349b80 { beSvFileFindApi o; int w[24]; char b[96]; };
extern "C" int g_beSvFileFindApi_vtable[4];
extern "C" igMetaObject *g_beSvFileMakeApi_metaObject;
struct Obj_349e00 { int *vt; int w[263]; };
extern "C" int g_beSvFileMakeApi_vtable[4];
extern "C" igMetaObject *g_beSvPlatBaseData_metaObject;
struct F_34a2b0 { int *vt; int pad[2]; int *ref; int pad2[4]; };
extern "C" igMetaObject *g_beSvSlotDataList_metaObject;
struct Obj_34a540 { int *vt; char pad[28]; };
extern "C" int g_beSvSlotDataList_vtable[4];
extern "C" igMetaObject *g_beSvSlotPS2_metaObject;
struct Obj_34a680 { int *vt; char pad[28]; };
extern "C" int g_beSvSlotPS2_vtable[4];
extern "C" igMetaObject *g_beSvSlotGC_metaObject;
struct Obj_34a7d0 { int *vt; char pad[28]; };
extern "C" int g_beSvSlotGC_vtable[4];
extern "C" igMetaObject *g_beSvSlotXbox_metaObject;
union U_34a910 { int vt; char b[64]; };
extern "C" int g_beSvSlotXbox_vtable[4];
extern "C" igMetaObject *g_beSvSlotData_metaObject;
extern "C" igMetaObject *beSvSlotData_GetMetaObject(void);
extern "C" igMetaObject *g_beSaveMemoryObj_metaObject;
extern "C" igMetaObject *beSaveMemoryObj_GetMetaObject(void);
struct Obj_34ad30 { int *vt; char pad[12]; };
extern "C" int g_beSaveMemoryObj_vtable[4];
extern "C" igMetaObject *g_beSaveDataDeliver_metaObject;
extern "C" igMetaObject *beSaveDataDeliver_GetMetaObject(void);
struct Obj_34af50 { int *vt; char pad[12]; };
extern "C" int g_beSaveDataDeliver_vtable[4];
extern "C" igMetaObject *g_beSvDeliver_metaObject;
extern "C" igMetaObject *beSvDeliver_GetMetaObject(void);
union U_34b170 { int vt; int w[17]; char b[68]; };
extern "C" int g_beSvDeliver_vtable[4];
extern "C" igMetaObject *g_beResetNode_metaObject;
struct W_34b4f0 { int *vt; int w[11]; };
extern "C" int g_beResetNode_vtable[4];
struct igMetaObject_34b580;
extern "C" igMetaObject_34b580 * igGroup_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_bePoint01Info_metaObject;
extern "C" int g_bePoint01Info_vtable[4];
extern "C" ObjectRefWord *FUN_0034b790(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_bePoint01_metaObject;
extern "C" int g_bePoint01_vtable[4];
extern "C" igMetaObject *g_beParticleCtrl2InfoRam_metaObject;
struct Obj_34bd10 { int *vt; int w[15]; };
extern "C" int g_beParticleCtrl2InfoRam_vtable[4];
typedef struct S_temp_a0_34bdc0 { char pad4[4]; int f4; } S_temp_a0_34bdc0;
extern "C" ObjectRefWord *igSmartPointer_beParticleCtrl2InfoWork_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beParticleCtrl2InfoWork_metaObject;
union U_34c120 { int vt; char b[32]; };
extern "C" int g_beParticleCtrl2InfoWork_vtable[4];
extern "C" igMetaObject *g_beParticleCtrl2Info_metaObject;
struct Obj_34c3d0 { int *vt; char p4[4]; int f8; char pc[8]; int f14; int f18; int f1c; int f20; char pe[12]; };
extern "C" int g_beParticleCtrl2Info_vtable[4];
extern "C" igMetaObject *g_beParticleCtrl2_metaObject;
union U_34c710 { int vt; char b[32]; };
extern "C" int g_beParticleCtrl2_vtable[4];
extern "C" igMetaObject *g_bePadManager_metaObject;
struct Obj_34c980 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_bePadManager_vtable[4];
extern "C" ObjectRefWord *FUN_0034ca30(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_0034cab0(struct R **arg0, short arg1);
extern "C" igMetaObject *g_bePadDataList_metaObject;
union U_34cd60 { int vt; char b[32]; };
extern "C" int g_bePadDataList_vtable[4];
extern "C" igMetaObject *g_bePadData_metaObject;
struct Obj_34cee0 { int *vt; char pad[108]; };
extern "C" int g_bePadData_vtable[4];
extern "C" igMetaObject *g_beOptInfo_metaObject;
extern "C" igMetaObject *beOptInfo_GetMetaObject(void);
typedef struct { int *vt; int p4; int f8; int pad[4]; int a; int b; int tail[3]; } Obj_34d0d0;
extern "C" int g_beOptInfo_vtable[4];
struct igMetaObject_34d180;
extern "C" igMetaObject_34d180 * igInfo_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_beNumberCtrlInfoWork_metaObject;
extern "C" igMetaObject *beNumberCtrlInfoWork_GetMetaObject(void);
extern "C" int g_beNumberCtrlInfoWork_vtable[4];
extern "C" igMetaObject *g_beNumberCtrlInfoRam_metaObject;
extern "C" igMetaObject *beNumberCtrlInfoRam_GetMetaObject(void);
struct W_34d590 { int *vt; int f[19]; };
extern "C" int g_beNumberCtrlInfoRam_vtable[4];
extern "C" igMetaObject *g_beNumVerDataList_metaObject;
extern "C" igMetaObject *beNumVerDataList_GetMetaObject(void);
struct Obj_34d990 { int *vt; char pad[28]; };
extern "C" int g_beNumVerDataList_vtable[4];
extern "C" igMetaObject *g_beNumVerData_metaObject;
struct Obj_34dad0 { int *vt; char pad[8]; char *m; };
extern "C" int g_beNumVerData_vtable[4];
extern "C" igMetaObject *g_beNumVerInsideDataList_metaObject;
struct Obj_34dd70 { int *vt; char pad[28]; };
extern "C" int g_beNumVerInsideDataList_vtable[4];
extern "C" igMetaObject *g_beNumVerInsideData_metaObject;
struct Obj_34def0 { int *vt; char pad[12]; };
extern "C" int g_beNumVerInsideData_vtable[4];
extern "C" igMetaObject *g_beNumberCtrlInfoList_metaObject;
struct Obj_34e0a0 { int *vt; char pad[28]; };
extern "C" int g_beNumberCtrlInfoList_vtable[4];
extern "C" igMetaObject *g_beNumberCtrlInfo_metaObject;
struct Obj_34e1e0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int g_beNumberCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beNumberCtrl_metaObject;
union U_34e440 { int vt; int w[5]; char b[20]; };
extern "C" int g_beNumberCtrl_vtable[4];
extern "C" igMetaObject *g_beLoadingNode_metaObject;
struct Obj_34e620 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; int f30; int f34; int f38; int f3C; int f40; int f44; int f48; int f4C; int f50; int f54; int f58; int f5C; int f60; int f64; int f68; int f6C; int f70; int f74; int f78; int f7C; };
extern "C" int g_beLoadingNode_vtable[4];
extern "C" int g_igGroup_vtable[4];
extern "C" int g_beNodeAnim_vtable[4];
extern "C" igMetaObject *g_beNodeAnim_metaObject;
struct Obj_34e8c0 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; int f56; int f60; int f64; int f68; int f72; int f76; int f80; int f84; int f88; int f92; int f96; int f100; int f104; int f108; };
extern "C" igMetaObject *g_beMovieInfo_metaObject;
struct W_34eb60 { int *vt; int w[7]; };
extern "C" int g_beMovieInfo_vtable[4];
extern "C" igMetaObject *g_beMovieInfoData_metaObject;
struct Obj_34ecd0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; };
extern "C" int g_beMovieInfoData_vtable[4];
extern "C" igMetaObject *g_beMovie_metaObject;
extern "C" igMetaObject *beMovie_GetMetaObject(void);
struct Obj_34f010 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_beMovie_vtable[4];
extern "C" igMetaObject *g_beModelCtrlSubCom_metaObject;
extern "C" igMetaObject *beModelCtrlSubCom_GetMetaObject(void);
extern "C" int g_beModelCtrlSubCom_vtable[4];
struct Obj_34f2b0 { int *vt; char pad[4]; struct R *p; char pad2[4]; };
extern "C" igMetaObject *g_beModelCtrlSCSound_metaObject;
extern "C" igMetaObject *beModelCtrlSCSound_GetMetaObject(void);
union U_34f530 { int vt; char b[32]; };
extern "C" int g_beModelCtrlSCSound_vtable[4];
extern "C" igMetaObject *g_beModelCtrlSCHitBox_metaObject;
extern "C" igMetaObject *beModelCtrlSCHitBox_GetMetaObject(void);
struct Obj_34f780 { int *vt; char pad[60]; };
extern "C" int g_beModelCtrlSCHitBox_vtable[4];
extern "C" igMetaObject *g_beModelCtrlSCEffect_metaObject;
extern "C" int g_beModelCtrlSCEffect_vtable[4];
extern "C" igMetaObject *g_beModelCtrlSubComBase_metaObject;
extern "C" igMetaObject *g_beModelCtrlNode2_metaObject;
extern "C" int g_beModelCtrlNode2_vtable[4];
/* _overrideAttrList (igObjectRefMetaField). */
struct OverrideAttrListField { int *p; OverrideAttrListField() { p = 0; } ~OverrideAttrListField(); };
struct ModelCtrlNode2Vtable { ModelCtrlNode2Vtable(int **slot) { *slot = g_beModelCtrlNode2_vtable; } };
struct ModelCtrlNode2View : igTransformView, ModelCtrlNode2Vtable {
    int pad108;
    long long time;                         /* +112 _time */
    float timeScale;                        /* +120 _timeScale */
    long long timeBias;                     /* +128 _timeBias */
    OverrideAttrListField overrideAttrList;  /* +136 _overrideAttrList */
    ModelCtrlNode2View() : ModelCtrlNode2Vtable(&vtable) { }
    ~ModelCtrlNode2View() { vtable = g_beModelCtrlNode2_vtable; }
};
extern "C" igMetaObject *g_beModelCtrlInfoWork_metaObject;
extern "C" int g_beModelCtrlInfoWork_vtable[4];
/* The members of beModelCtrlInfoWork whose constructors and destructors are called out of line, one
 * class per member type. */
/* An igStringMetaField member. */
struct StringField { int *p; StringField() throw(); ~StringField(); };
/* _labelOffsetList. */
struct LabelOffsetListField { int *p; LabelOffsetListField() throw(); ~LabelOffsetListField(); };
struct HpField { int *p; HpField() throw(); ~HpField(); };
struct ComDataField { int *p; ComDataField() throw(); ~ComDataField(); };
struct LabelListField { int *p; LabelListField() throw(); ~LabelListField(); };
struct MoveDataListField { int *p; MoveDataListField() throw(); ~MoveDataListField(); };
struct AIField { int *p; AIField() throw(); ~AIField(); };
struct PosLockNodeField { int *p; PosLockNodeField() throw(); ~PosLockNodeField(); };
struct PosLockTrcField { int *p; PosLockTrcField() throw(); ~PosLockTrcField(); };
struct MoveObjectListField { int *p; MoveObjectListField() throw(); ~MoveObjectListField(); };
struct RideOnDataField { int *p; RideOnDataField() throw(); ~RideOnDataField(); };
struct DebugHitBoxNodeField { int *p; DebugHitBoxNodeField() throw(); ~DebugHitBoxNodeField(); };
struct HitBodyField { int *p; HitBodyField() throw(); ~HitBodyField(); };
struct SubCommandField { int *p; SubCommandField() throw(); ~SubCommandField(); };
struct BaseAABoxField { int *p; BaseAABoxField() throw(); ~BaseAABoxField(); };
/* An igVec3fMetaField member. */
struct Vec3Field { float v[3]; Vec3Field() throw(); };
/* Stores the beModelCtrlInfoWork vtable before the first member constructor runs. */
struct ModelCtrlInfoWorkVtable { ModelCtrlInfoWorkVtable(int **slot) { *slot = g_beModelCtrlInfoWork_vtable; } };
/* matching construct: hand-written view of beModelCtrlInfoWork (the second empty base places the vtable
 * store before the member constructors run) */
struct ModelCtrlInfoWorkView : igObjectView, ModelCtrlInfoWorkVtable {
    HpField mHp;                                    /* +8   _mHp */
    HpField hp;                                     /* +12  _hp */
    int recNo;                                      /* +16  _recNo */
    StringField seqCodeName;                          /* +20  _seqCodeName */
    ComDataField comData;                           /* +24  _comData */
    int comIndex;                                   /* +28  _comIndex */
    int comLabelCount;                              /* +32  _comLabelCount */
    LabelListField labelSeqList;                    /* +36  _labelSeqList */
    LabelListField labelNameList;                   /* +40  _labelNameList */
    LabelOffsetListField labelOffsetList;           /* +44  _labelOffsetList */
    StringField luaBHit;                              /* +48  _luaBHit */
    StringField luaWHit;                              /* +52  _luaWHit */
    StringField luaFHit;                              /* +56  _luaFHit */
    int ctrlSt0;                                    /* +60  _ctrlSt0 */
    int ctrlSt1;                                    /* +64  _ctrlSt1 */
    unsigned char isOnCtrl;                         /* +68  _isOnCtrl */
    unsigned char isOnFreeze;                       /* +69  _isOnFreeze */
    MoveDataListField pdMoveDataList;               /* +72  _pdMoveDataList */
    StringField wCheckName;                           /* +76  _wCheckName */
    AIField aI;                                     /* +80  _aI */
    float aIHOffsetY;                               /* +84  _aIHOffsetY */
    StringField targetMode;                           /* +88  _targetMode */
    StringField targetKind;                           /* +92  _targetKind */
    StringField targetSpc1;                           /* +96  _targetSpc1 */
    Vec3Field targetPos;                            /* +100 _targetPos */
    unsigned char keyInput;                         /* +112 _keyInput */
    StringField keyEventName;                         /* +116 _keyEventName */
    unsigned char isHitCheck;                       /* +120 _isHitCheck */
    float mutekiCount;                              /* +124 _mutekiCount */
    Vec3Field targetDirection;                      /* +128 _targetDirection */
    Vec3Field directionLimiter;                     /* +140 _directionLimiter */
    Vec3Field direction;                            /* +152 _direction */
    float svLODHighRange;                           /* +164 _svLODHighRange */
    unsigned char isPosLock;                        /* +168 _isPosLock */
    PosLockNodeField posLockNode;                   /* +172 _posLockNode */
    PosLockTrcField posLockTrc;                     /* +176 _posLockTrc */
    StringField posLockModelName;                     /* +180 _posLockModelName */
    StringField posLockBoneName;                      /* +184 _posLockBoneName */
    Vec3Field posLockOffset;                        /* +188 _posLockOffset */
    MoveObjectListField moveObjectList;             /* +200 _moveObjectList */
    RideOnDataField rideOnData;                     /* +204 _rideOnData */
    DebugHitBoxNodeField debugHitBoxNode;           /* +208 _debugHitBoxNode */
    HitBodyField hitBody;                           /* +212 _hitBody */
    unsigned char isWallCheck;                      /* +216 _isWallCheck */
    unsigned char isFloorCheck;                     /* +217 _isFloorCheck */
    unsigned char isFallCheck;                      /* +218 _isFallCheck */
    StringField hitParentName;                        /* +220 _hitParentName */
    int hitParentRamNo;                             /* +224 _hitParentRamNo */
    SubCommandField subCommand;                     /* +228 _subCommand */
    BaseAABoxField baseAABox;                       /* +232 _baseAABox */
    ModelCtrlInfoWorkView() : ModelCtrlInfoWorkVtable(&vtable) { }
    ~ModelCtrlInfoWorkView() { vtable = g_beModelCtrlInfoWork_vtable; }
};
extern "C" void *FUN_00350410(beNDMWMdlPlayer2InfoWork *arg0, long long arg1);
extern "C" void **FUN_00350b90(struct Ref **self, short flag);
extern "C" O *FUN_00350c90(O *arg0, short arg1);
extern "C" ObjectRefWord *FUN_00350d10(ObjectRefWord *self,int delete_storage);
typedef struct S_temp_a0_350d90 { char pad4[4]; int f4; } S_temp_a0_350d90;
extern "C" ObjectRefWord *FUN_00350e10(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beModelCtrlInfoRideOn4_metaObject;
extern "C" int g_beModelCtrlInfoRideOn_vtable[4];
extern "C" int g_beModelCtrlInfoRideOn4_vtable[4];
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
struct RideOnVtable { RideOnVtable(int **slot) { *slot = g_beModelCtrlInfoRideOn_vtable; } };
struct RideOnView : igObjectView, RideOnVtable {
    ModelNameField modelName;               /* +8 _modelName */
    int modelRamNo;                         /* +12 */
    ModelNodeField modelNode;               /* +16 _modelNode */
    igMatrix44fView oldMatrix;              /* +20 _oldMatrix */
    RideOnView() : RideOnVtable(&vtable) { }
    ~RideOnView() { vtable = g_beModelCtrlInfoRideOn_vtable; }
};
struct RideOn4Vtable { RideOn4Vtable(int **slot) { *slot = g_beModelCtrlInfoRideOn4_vtable; } };
struct RideOn4View : RideOnView, RideOn4Vtable {
    float oldPlayerPos[3];                  /* +84 */
    float vector[3];                        /* +96 */
    float scalar, limitter;                 /* +108 */
    int isFirst;                            /* +116 */
    RideOn4View() : RideOn4Vtable(&vtable) { }
    ~RideOn4View() { vtable = g_beModelCtrlInfoRideOn4_vtable; }
};
struct T_351670 { int w0; int refs; char pad[20]; int *f1c; };
extern "C" igMetaObject *g_beModelCtrlInfoRideOn3_metaObject;
extern "C" int g_beModelCtrlInfoRideOn3_vtable[4];
struct RideOn3Vtable { RideOn3Vtable(int **slot) { *slot = g_beModelCtrlInfoRideOn3_vtable; } };
struct RideOn3View : RideOnView, RideOn3Vtable {
    float worldPosition[3];                 /* +84 */
    float minSpeed, maxSpeed;               /* +96 */
    float minKyori, maxKyori;               /* +104 */
    RideOn3View() : RideOn3Vtable(&vtable) { }
    ~RideOn3View() { vtable = g_beModelCtrlInfoRideOn3_vtable; }
};
struct T_3519c0 { int w0; int refs; char pad[20]; int *f1c; };
extern "C" igMetaObject *g_beModelCtrlInfoRideOn2_metaObject;
extern "C" int g_beModelCtrlInfoRideOn2_vtable[4];
struct RideOn2Vtable { RideOn2Vtable(int **slot) { *slot = g_beModelCtrlInfoRideOn2_vtable; } };
struct RideOn2View : RideOnView, RideOn2Vtable {
    float vector[3];                        /* +84 */
    RideOn2View() : RideOn2Vtable(&vtable) { }
    ~RideOn2View() { vtable = g_beModelCtrlInfoRideOn2_vtable; }
};
struct T_351d10 { int word0; int references; int pad[5]; int f28; };
extern "C" igMetaObject *g_beModelCtrlInfoRideOn_metaObject;
extern "C" igMetaObject *g_beModelCtrlInfoAI_metaObject;
struct F_352220 { int *vt; int pad[1]; int *ref; int pad2[9]; };
extern "C" int g_beModelCtrlInfoAI_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoHitBody_metaObject;
extern "C" int g_beModelCtrlInfoHitBody_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMoveObjectList_metaObject;
extern "C" igMetaObject *beModelCtrlMoveObjectList_GetMetaObject(void);
struct Obj_352850 { int *vt; char pad[28]; };
extern "C" int g_beModelCtrlMoveObjectList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMoveObject_metaObject;
extern "C" igMetaObject *beModelCtrlMoveObject_GetMetaObject(void);
struct Obj_3529d0 { int *vt; char pad[44]; };
extern "C" int g_beModelCtrlMoveObject_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoList_metaObject;
extern "C" igMetaObject *beModelCtrlInfoList_GetMetaObject(void);
struct Obj_352be0 { int *vt; char pad[28]; };
extern "C" int g_beModelCtrlInfoList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfo_metaObject;
extern "C" igMetaObject *beModelCtrlInfo_GetMetaObject(void);
union U_352d20 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int g_beModelCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoRamData_metaObject;
struct Obj_352f30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_beModelCtrlInfoRamData_vtable[4];
extern "C" ObjectRefWord *FUN_00352fc0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beModelCtrlInfoDataTrc_metaObject;
union U_3532e0 { int vt; char b[32]; };
extern "C" int g_beModelCtrlInfoDataTrc_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataSeq_metaObject;
union U_353600 { int vt; char b[32]; };
extern "C" int g_beModelCtrlInfoDataSeq_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataHit_metaObject;
union U_353920 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int g_beModelCtrlInfoDataHit_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataAIH_metaObject;
extern "C" int g_beModelCtrlInfoDataAIH_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataAIM_metaObject;
union U_353ee0 { int vt; char b[32]; };
extern "C" int g_beModelCtrlInfoDataAIM_vtable[4];
struct T_temp_v0_2 { int word0; int references; char pad8[20]; int f28; };
extern "C" igMetaObject *g_beModelCtrlAIMapList_metaObject;
struct Obj_354250 { int *vt; char pad[28]; };
extern "C" int g_beModelCtrlAIMapList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlAIMap_metaObject;
union U_354390 { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" int g_beModelCtrlAIMap_vtable[4];
extern "C" struct R **FUN_00354490(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beModelCtrlAIDataList_metaObject;
union U_354770 { int vt; char b[32]; };
extern "C" int g_beModelCtrlAIDataList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlAIData_metaObject;
union U_3548b0 { int vt; char b[32]; };
extern "C" int g_beModelCtrlAIData_vtable[4];
extern "C" igMetaObject *g_beModelCtrlHITBOX_metaObject;
extern "C" igMetaObject *beModelCtrlHITBOX_GetMetaObject(void);
extern "C" int g_beModelCtrlHITBOX_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMUTEKI_metaObject;
extern "C" igMetaObject *beModelCtrlMUTEKI_GetMetaObject(void);
union U_354cf0 { int vt; char b[16]; };
extern "C" int g_beModelCtrlMUTEKI_vtable[4];
extern "C" igMetaObject *g_beModelCtrlAIMAP_metaObject;
extern "C" igMetaObject *beModelCtrlAIMAP_GetMetaObject(void);
union U_354ef0 { int vt; char b[16]; };
extern "C" int g_beModelCtrlAIMAP_vtable[4];
extern "C" igMetaObject *g_beModelCtrlWCHECK_metaObject;
extern "C" igMetaObject *beModelCtrlWCHECK_GetMetaObject(void);
union U_355080 { int vt; char b[16]; };
extern "C" int g_beModelCtrlWCHECK_vtable[4];
extern "C" igMetaObject *g_beModelCtrlPDMOVE_metaObject;
union U_355210 { int vt; char b[32]; };
extern "C" int g_beModelCtrlPDMOVE_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMOVERL_metaObject;
union U_355410 { int vt; char b[32]; };
extern "C" int g_beModelCtrlMOVERL_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMOVEEX_metaObject;
extern "C" int g_beModelCtrlMOVEEX_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMOVE_metaObject;
union U_355890 { int vt; char b[32]; };
extern "C" int g_beModelCtrlMOVE_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMSGBOX_metaObject;
union U_355a90 { int vt; int w[4]; char b[16]; };
extern "C" int g_beModelCtrlMSGBOX_vtable[4];
extern "C" igMetaObject *g_beModelCtrlCTRL_metaObject;
union U_355c20 { int vt; char b[16]; };
extern "C" int g_beModelCtrlCTRL_vtable[4];
extern "C" igMetaObject *g_beModelCtrlJUMP_metaObject;
union U_355db0 { int vt; char b[16]; };
extern "C" int g_beModelCtrlJUMP_vtable[4];
extern "C" igMetaObject *g_beModelCtrlACTION_metaObject;
union U_355f40 { int vt; char b[16]; };
extern "C" int g_beModelCtrlACTION_vtable[4];
extern "C" igMetaObject *g_beModelCtrlLABELCTRL_metaObject;
union U_3560d0 { int vt; char b[16]; };
extern "C" int g_beModelCtrlLABELCTRL_vtable[4];
extern "C" igMetaObject *g_beModelCtrlLABEL_metaObject;
union U_356310 { int vt; char b[16]; };
extern "C" int g_beModelCtrlLABEL_vtable[4];
extern "C" igMetaObject *g_beModelCtrlLUACALL_metaObject;
extern "C" igMetaObject *beModelCtrlLUACALL_GetMetaObject(void);
struct T_3564a0 { int word0; int references; };
extern "C" int g_beModelCtrlLUACALL_vtable[4];
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
extern "C" igMetaObject *beModelCtrlDataList_GetMetaObject(void);
extern "C" int g_beModelCtrlDataList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlData_metaObject;
extern "C" igMetaObject *beModelCtrlData_GetMetaObject(void);
struct T_356870 { int word0; int references; };
extern "C" int g_beModelCtrlData_vtable[4];
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
extern "C" igMetaObject *beModelCtrl_GetMetaObject(void);
extern "C" igMetaObject *g_beMeterCtrlNode_metaObject;
struct Obj_356d60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int g_beMeterCtrlNode_vtable[4];
extern "C" igMetaObject *g_beMeterCtrlInfoList_metaObject;
extern "C" int g_beMeterCtrlInfoList_vtable[4];
extern "C" igMetaObject *g_beMeterCtrlInfo_metaObject;
typedef struct { int *vt; int w[6]; int s; } Obj_3570f0;
extern "C" int g_beMeterCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beMeterCtrlOneData_metaObject;
struct Obj_357320 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int g_beMeterCtrlOneData_vtable[4];
extern "C" igMetaObject *g_beMeterCtrl_metaObject;
struct T_357740 { int word0; int references; };
extern "C" int g_beMeterCtrl_vtable[4];
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
extern "C" int g_beMessenger_vtable[4];
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
extern "C" int g_beMessengerWorkList_vtable[4];
/* Messenger class factories and their lazy-registration wrappers. Each factory makes sure the
 * class is registered, reloads the class handle and creates an instance from the caller's
 * allocator. */

/* Structural ABI view of the static-init callback list the registrars return; never defined here. */
struct StaticInitCallbacks;
extern "C" igMetaObject *g_beMessengerWork_metaObject;
extern "C" int g_beMessengerWork_vtable[4];
extern "C" igMetaObject *g_beMessengerGroupList_metaObject;
struct Obj_3583f0 { int *vt; char pad[28]; };
extern "C" int g_beMessengerGroupList_vtable[4];
extern "C" igMetaObject *g_beMessengerGroup_metaObject;
struct Obj_358570 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_beMessengerGroup_vtable[4];
extern "C" igMetaObject *g_beMessengerDelayList_metaObject;
extern "C" igMetaObject *beMessengerDelayList_GetMetaObject(void);
struct Obj_358860 { int *vt; char pad[28]; };
extern "C" int g_beMessengerDelayList_vtable[4];
extern "C" igMetaObject *g_beMessengerDelay_metaObject;
extern "C" igMetaObject *beMessengerDelay_GetMetaObject(void);
union U_3589e0 { int vt; int w[12]; char b[48]; };
extern "C" int g_beMessengerDelay_vtable[4];
extern "C" igMetaObject *g_beMessengerArgDataList_metaObject;
extern "C" igMetaObject *beMessengerArgDataList_GetMetaObject(void);
struct Obj_358c90 { int *vt; char pad[28]; };
extern "C" int g_beMessengerArgDataList_vtable[4];
extern "C" igMetaObject *g_beMessengerArgData_metaObject;
extern "C" igMetaObject *beMessengerArgData_GetMetaObject(void);
struct Obj_358e60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_beMessengerArgData_vtable[4];
extern "C" igMetaObject *g_beMemory_metaObject;
extern "C" int g_beMemory_vtable[4];
extern "C" igMetaObject *g_beMatCtrlInfoWork_metaObject;
struct T_359560 { int word0; int references; };
extern "C" int g_beMatCtrlInfoWork_vtable[4];
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
extern "C" int g_beMatCtrlInfoRam_vtable[4];
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
extern "C" O *igSmartPointer_beMatCtrlInfoWork_Destruct(O *arg0, short arg1);
extern "C" igMetaObject *g_beMatCtrlInfo_metaObject;
struct Obj_359b20 { int *vt; int w[11]; };
extern "C" int g_beMatCtrlInfo_vtable[4];
typedef struct S_temp_a0_359c50 { char pad4[4]; int f4; } S_temp_a0_359c50;
extern "C" igMetaObject *g_beMatCtrlSearchList_metaObject;
struct Obj_359f00 { int *vt; char pad[28]; };
extern "C" int g_beMatCtrlSearchList_vtable[4];
extern "C" igMetaObject *g_beMatCtrlSearch_metaObject;
struct Obj_35a090 { int *vt; char pad[20]; char *m; char pad2[4]; };
extern "C" int g_beMatCtrlSearch_vtable[4];
extern "C" igMetaObject *g_beMatCtrlDataList_metaObject;
struct Obj_35a340 { int *vt; char pad[28]; };
extern "C" int g_beMatCtrlDataList_vtable[4];
extern "C" igMetaObject *g_beMatCtrlData_metaObject;
union U_35a480 { int vt; char b[16]; };
extern "C" int g_beMatCtrlData_vtable[4];
extern "C" igMetaObject *g_beMatCtrl_metaObject;
struct Obj_35a7f0 { int *vt; int w[19]; };
extern "C" int g_beMatCtrl_vtable[4];
struct F_35a940 { char pad[52]; int f52; int f56; char f60; };
extern "C" igMetaObject *g_beLuaState_metaObject;
struct T_35ab00 { int word0; int references; };
extern "C" int g_beLuaState_vtable[4];
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
extern "C" int g_igLuaState_metaObject[4];
extern "C" igMetaObject *g_beLuaInfo_metaObject;
extern "C" igMetaObject *beLuaInfo_GetMetaObject(void);
struct Obj_35ad60 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_beLuaInfo_vtable[4];
extern "C" ObjectRefWord *FUN_0035ade0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beLuaDataList_metaObject;
extern "C" igMetaObject *beLuaDataList_GetMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_35b060;
extern "C" int g_beLuaDataList_vtable[4];
extern "C" igMetaObject *g_beLuaData_metaObject;
extern "C" igMetaObject *beLuaData_GetMetaObject(void);
struct Obj_35b1a0 { int *vt; int w1; char *w2; igObject *w3; };
extern "C" int g_beLuaData_vtable[4];
extern "C" igMetaObject *g_beLuaDataObjectist_metaObject;
extern "C" igMetaObject *beLuaDataObjectist_GetMetaObject(void);
struct Obj_35b420 { int *vt; char pad[28]; };
extern "C" int g_beLuaDataObjectist_vtable[4];
extern "C" igMetaObject *g_beLuaDataObject_metaObject;
struct Obj_35b5b0 { int *vt; char pad[12]; };
extern "C" int g_beLuaDataObject_vtable[4];
extern "C" igMetaObject *g_beLua_metaObject;
struct Obj_35b810 { int *vt; int w[7]; };
extern "C" int g_beLua_vtable[4];
extern "C" ObjectRefWord *FUN_0035b940(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_igLightSetList_metaObject;
struct Obj_35bc10 { int *vt; char pad[28]; };
extern "C" int g_igLightSetList_vtable[4];
extern "C" igMetaObject *g_beLightCtrlInfo_metaObject;
struct W_35bd50 { int *vt; int f[7]; };
extern "C" int g_beLightCtrlInfo_vtable[4];
extern "C" struct R **FUN_0035bdd0(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beLightCtrl_metaObject;
union U_35c0f0 { int vt; int w[5]; char b[20]; };
extern "C" int g_beLightCtrl_vtable[4];
extern "C" igMetaObject *g_beLayerInfoRam_metaObject;
extern "C" int g_beLayerInfoRam_vtable[4];
extern "C" igMetaObject *g_beLayerInfo_metaObject;
union U_35c470 { int vt; char b[32]; };
extern "C" int g_beLayerInfo_vtable[4];
extern "C" ObjectRefWord *FUN_0035c4f0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beLayerGroupList_metaObject;
struct Obj_35c760 { int *vt; char pad[28]; };
extern "C" int g_beLayerGroupList_vtable[4];
extern "C" igMetaObject *g_beLayerGroup_metaObject;
union U_35c8a0 { int vt; char b[16]; };
extern "C" int g_beLayerGroup_vtable[4];
extern "C" igMetaObject *g_beLayerCtl_metaObject;
extern "C" int g_beLayerCtl_vtable[4];
extern "C" igMetaObject *g_beLOA_metaObject;
extern "C" igMetaObject *beLOA_GetMetaObject(void);
struct W_35cd90 { int *vt; int f[23]; };
extern "C" int g_beLOA_vtable[4];
extern "C" igMetaObject *g_beKeyboardReceiver_metaObject;
extern "C" igMetaObject *beKeyboardReceiver_GetMetaObject(void);
struct W_35d110 { int *vt; int f[3]; };
extern "C" int g_beKeyboardReceiver_vtable[4];
struct igMetaObject_35d1c0;
extern "C" igMetaObject_35d1c0 *igEventReceiver_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beHitLandModelInfoRam_metaObject;
extern "C" igMetaObject *beHitLandModelInfoRam_GetMetaObject(void);
struct T_35d350 { int word0; int references; };
extern "C" int g_beHitLandModelInfoRam_vtable[4];
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
extern "C" igMetaObject *beHitLandModelInfo_GetMetaObject(void);
struct Obj_35d4f0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_beHitLandModelInfo_vtable[4];
extern "C" igMetaObject *g_beHitLandModel_metaObject;
extern "C" int g_beHitLandModel_vtable[4];
struct HitLandOrderField { int *p; HitLandOrderField() { p = 0; } ~HitLandOrderField(); };
struct HitTraversalField { int *p; HitTraversalField() { p = 0; } ~HitTraversalField(); };
struct HitLandProbeField { int *p; HitLandProbeField() { p = 0; } ~HitLandProbeField(); };
struct ControllerBaseView : igObjectView {
    int name, insight, system, messenger, infoList;
    unsigned char isUpdateRun;
    ControllerBaseView() { name = 0; infoList = 0; }
    ~ControllerBaseView();
};
struct HitLandModelVtable { HitLandModelVtable(int **slot) { *slot = g_beHitLandModel_vtable; } };
struct HitLandModelView : ControllerBaseView, HitLandModelVtable {
    HitLandOrderField order;                /* +32 _order */
    HitTraversalField hitTraversal;         /* +36 _hitTraversal */
    HitLandProbeField probe;                /* +40 _probe */
    unsigned char isHitWall;                /* +44 */
    igMatrix44fView mat90;                  /* +48 _mat90 */
    HitLandModelView() : HitLandModelVtable(&vtable) { }
    ~HitLandModelView() { vtable = g_beHitLandModel_vtable; }
};
extern "C" igMetaObject *g_beHitLandModelTraversal_metaObject;
union U_35dcb0 { int vt; char b[80]; };
extern "C" int g_beHitLandModelTraversal_vtable[4];
extern "C" int g_igIntersectTraversal_metaObject[4];
extern "C" igMetaObject *g_beHitLandModelOrder_metaObject;
union U_35df70 { int vt; char b[64]; };
extern "C" int g_beHitLandModelOrder_vtable[4];
extern "C" igMetaObject *g_beHitLandResultDataList_metaObject;
extern "C" int g_beHitLandResultDataList_vtable[4];
extern "C" igMetaObject *g_beHitLandResultData_metaObject;
union U_35e490 { int vt; char b[96]; };
extern "C" int g_beHitLandResultData_vtable[4];
extern "C" igMetaObject *g_beHitLandDelivInfoRam_metaObject;
union U_35e6b0 { int vt; char b[112]; };
extern "C" int g_beHitLandDelivInfoRam_vtable[4];
extern "C" igMetaObject *g_beHitLandDelivInfo_metaObject;
extern "C" int g_beHitLandDelivInfo_vtable[4];
struct Obj_35ea10 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" igMetaObject *g_beHitLandDeliv_metaObject;
union U_35ec70 { int vt; char b[32]; };
extern "C" int g_beHitLandDeliv_vtable[4];
extern "C" igMetaObject *g_beGroupKeepList_metaObject;
struct Obj_35eea0 { int *vt; char pad[28]; };
extern "C" int g_beGroupKeepList_vtable[4];
extern "C" igMetaObject *g_beGroupKeep_metaObject;
struct Obj_35efe0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_beGroupKeep_vtable[4];
extern "C" igMetaObject *g_beGeneraterInfoWork_metaObject;
extern "C" igMetaObject *beGeneraterInfoWork_GetMetaObject(void);
extern "C" int g_beGeneraterInfoWork_vtable[4];
extern "C" igMetaObject *g_beGeneraterInfoRam_metaObject;
extern "C" igMetaObject *beGeneraterInfoRam_GetMetaObject(void);
struct T_35f460 { int word0; int references; };
extern "C" int g_beGeneraterInfoRam_vtable[4];
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
extern "C" igMetaObject *beGeneraterInfo_GetMetaObject(void);
extern "C" int g_beGeneraterInfo_vtable[4];
extern "C" igMetaObject *g_beGeneraterDataList_metaObject;
extern "C" igMetaObject *beGeneraterDataList_GetMetaObject(void);
struct Obj_35fa70 { int *vt; char pad[28]; };
extern "C" int g_beGeneraterDataList_vtable[4];
extern "C" igMetaObject *g_beGeneraterData_metaObject;
struct Obj_35fbb0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int g_beGeneraterData_vtable[4];
extern "C" O *FUN_0035fcd0(O *arg0, short arg1);
extern "C" igMetaObject *g_beGeneraterPlayerDataList_metaObject;
union U_35ffc0 { int vt; char b[32]; };
extern "C" int g_beGeneraterPlayerDataList_vtable[4];
extern "C" igMetaObject *g_beGeneraterPlayerData_metaObject;
struct T_360100 { int word0; int references; };
extern "C" int g_beGeneraterPlayerData_vtable[4];
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
extern "C" int g_beGeneraterItemDataList_vtable[4];
extern "C" igMetaObject *g_beGeneraterItemData_metaObject;
union U_360540 { int vt; char b[16]; };
extern "C" int g_beGeneraterItemData_vtable[4];
extern "C" igMetaObject *g_beGeneraterItemDataOneList_metaObject;
extern "C" int g_beGeneraterItemDataOneList_vtable[4];
extern "C" igMetaObject *g_beGeneraterItemDataOne_metaObject;
union U_360960 { int vt; char b[32]; };
extern "C" int g_beGeneraterItemDataOne_vtable[4];
extern "C" igMetaObject *g_beGenerater_metaObject;
extern "C" int g_beGenerater_vtable[4];
extern "C" igMetaObject *g_beFontInfo_metaObject;
union U_360ee0 { int vt; char b[32]; };
extern "C" int g_beFontInfo_vtable[4];
extern "C" ObjectRefWord *FUN_00360f60(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beFontInfoData_metaObject;
struct F_361180 { int *vt; int w[11]; };
extern "C" int g_beFontInfoData_vtable[4];
extern "C" igMetaObject *g_beUnicodeObjList_metaObject;
extern "C" igMetaObject *beUnicodeObjList_GetMetaObject(void);
struct Obj_361400 { int *vt; char pad[28]; };
extern "C" int g_beUnicodeObjList_vtable[4];
extern "C" igMetaObject *g_beUnicodeObj_metaObject;
extern "C" igMetaObject *beUnicodeObj_GetMetaObject(void);
union U_361580 { int vt; char b[16]; };
extern "C" int g_beUnicodeObj_vtable[4];
extern "C" igMetaObject *g_beFontImageList_metaObject;
extern "C" igMetaObject *beFontImageList_GetMetaObject(void);
struct Obj_3617f0 { int *vt; char pad[28]; };
extern "C" int g_beFontImageList_vtable[4];
extern "C" igMetaObject *g_beFontImage_metaObject;
extern "C" igMetaObject *beFontImage_GetMetaObject(void);
struct Obj_361930 { int *vt; int w[11]; };
extern "C" int g_beFontImage_vtable[4];
typedef struct S_temp_a0_3619a0 { char pad4[4]; int f4; } S_temp_a0_3619a0;
extern "C" int g_igFont_vtable[4];
typedef struct R_361a20 { int w0; int refs; } R_361a20;
typedef struct O_361a20 { int *vt; int f4; int *str; int f12; int f16; R_361a20 *ref; } O_361a20;
extern "C" O_361a20 *FUN_00361a20(O_361a20 *arg0, short arg1);
extern "C" int g_igBitmapFont_vtable[4];
typedef struct R_361b00 { int w0; int refs; } R_361b00;
typedef struct O_361b00 { int *vt; int f4; int *str; int f12; int f16; R_361b00 *ref20; int f24; R_361b00 *ref28; R_361b00 *ref32; } O_361b00;
extern "C" O_361b00 *FUN_00361b00(O_361b00 *arg0, short arg1);
extern "C" int g_igBitmapFont_metaObject[4];
extern "C" igMetaObject *g_beFont_metaObject;
struct Obj_361f30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int g_beFont_vtable[4];
extern "C" ObjectRefWord *FUN_00362070(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beFontGeomAttrPairList_metaObject;
struct Obj_362400 { int *vt; char pad[28]; };
extern "C" int g_beFontGeomAttrPairList_vtable[4];
extern "C" igMetaObject *g_beFontGeomAttrPair_metaObject;
union U_362580 { int vt; char b[32]; };
extern "C" int g_beFontGeomAttrPair_vtable[4];
extern "C" igMetaObject *g_beFileListInfoManager_metaObject;
struct Obj_3628d0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int g_beFileListInfoManager_vtable[4];
extern "C" igMetaObject *g_beFileListInfo_metaObject;
union U_362c50 { int vt; char b[32]; };
extern "C" int g_beFileListInfo_vtable[4];
extern "C" igMetaObject *g_beFile_metaObject;
struct Obj_362ea0 { int *vt; char pad[4]; };
extern "C" int g_beFile_vtable[4];
extern "C" igMetaObject *g_beFileChkObj_metaObject;
struct F_363020 { int *vt; int pad[1]; int *ref; int pad2[1]; };
extern "C" int g_beFileChkObj_vtable[4];
extern "C" igMetaObject *g_beDemoManager_metaObject;
extern "C" int g_beDemoManager_vtable[4];
struct Obj_3632f0 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char t[4]; };
extern "C" ObjectRefWord *FUN_00363380(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_00363400(struct R **arg0, short arg1);
extern "C" igMetaObject *g_beDemoManagerWorkList_metaObject;
struct Obj_3636d0 { int *vt; char pad[28]; };
extern "C" int g_beDemoManagerWorkList_vtable[4];
extern "C" igMetaObject *g_beDemoManagerWork_metaObject;
union U_3638a0 { int vt; char b[16]; };
extern "C" int g_beDemoManagerWork_vtable[4];
extern "C" igMetaObject *g_beDemoKeepMesList_metaObject;
extern "C" igMetaObject *beDemoKeepMesList_GetMetaObject(void);
struct Obj_363b30 { int *vt; char pad[28]; };
extern "C" int g_beDemoKeepMesList_vtable[4];
extern "C" igMetaObject *g_beDemoKeepMes_metaObject;
extern "C" igMetaObject *beDemoKeepMes_GetMetaObject(void);
extern "C" int g_beDemoKeepMes_vtable[4];
extern "C" igMetaObject *g_beDataObjListList_metaObject;
extern "C" igMetaObject *beDataObjListList_GetMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_363f60;
extern "C" int g_beDataObjListList_vtable[4];
extern "C" igMetaObject *g_beDataObjList_metaObject;
extern "C" igMetaObject *beDataObjList_GetMetaObject(void);
struct Obj_364130 { int *vt; char pad[28]; };
extern "C" int g_beDataObjList_vtable[4];
extern "C" igMetaObject *g_beDataObjFloatList_metaObject;
union U_3642b0 { int vt; int w[4]; void *p[4]; char b[16]; };
struct Rc { int vt; int rc; };
extern "C" int g_beDataObjFloatList_vtable[4];
extern "C" igMetaObject *g_beDataObjObjectList_metaObject;
struct T_364580 { int word0; int references; };
extern "C" int g_beDataObjObjectList_vtable[4];
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
extern "C" int g_beDataObjStringList_vtable[4];
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
extern "C" int g_beDataObjString_vtable[4];
extern "C" igMetaObject *g_beDataObjBoolList_metaObject;
union U_364dc0 { int vt; char b[16]; };
extern "C" int g_beDataObjBoolList_vtable[4];
extern "C" igMetaObject *g_beDataObjBool_metaObject;
struct F_365090 { int *vt; char pad[4]; int *str; char pad2[4]; };
extern "C" int g_beDataObjBool_vtable[4];
extern "C" igMetaObject *g_beDataObjIntList_metaObject;
struct T_3652d0 { int word0; int references; };
extern "C" int g_beDataObjIntList_vtable[4];
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
extern "C" int g_beDataObjInt_vtable[4];
extern "C" igMetaObject *g_beDataBaseList_metaObject;
struct Obj_3657f0 { int *vt; char pad[28]; };
extern "C" int g_beDataBaseList_vtable[4];
extern "C" igMetaObject *g_beDataBase_metaObject;
union U_365980 { int vt; int w[13]; char b[52]; };
extern "C" int g_beDataBase_vtable[4];
extern "C" igMetaObject *g_beDBManagerInfo_metaObject;
extern "C" igMetaObject *beDBManagerInfo_GetMetaObject(void);
extern "C" int g_beDBManagerInfo_vtable[4];
struct Obj_365e10 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" igMetaObject *g_beDBManager_metaObject;
extern "C" igMetaObject *beDBManager_GetMetaObject(void);
union U_3661b0 { int vt; char b[32]; };
extern "C" int g_beDBManager_vtable[4];
extern "C" igMetaObject *g_beCriVolume_metaObject;
extern "C" igMetaObject *beCriVolume_GetMetaObject(void);
struct Obj_3663e0 { int *vt; char pad[28]; };
extern "C" int g_beCriVolume_vtable[4];
extern "C" igMetaObject *g_beCriSfpData_metaObject;
extern "C" igMetaObject *beCriSfpData_GetMetaObject(void);
extern "C" int g_beCriSfpData_vtable[4];
extern "C" igMetaObject *g_beCriHandleList_metaObject;
struct Obj_366820 { int *vt; char pad[28]; };
extern "C" int g_beCriHandleList_vtable[4];
extern "C" igMetaObject *g_beCriHandle_metaObject;
extern "C" int g_beCriHandle_vtable[4];
extern "C" igMetaObject *g_beCriFxInfo_metaObject;
extern "C" int g_beCriFxInfo_vtable[4];
extern "C" igMetaObject *g_beCriFxXbData_metaObject;
union U_367040 { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" int g_beCriFxXbData_vtable[4];
extern "C" igMetaObject *g_beCriAudio_metaObject;
union U_367240 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int g_beCriAudio_vtable[4];
extern "C" igMetaObject *g_beCriSndf_metaObject;
extern "C" int g_beCriSndf_vtable[4];
extern "C" igMetaObject *g_beCriAcxData_metaObject;
union U_367720 { int vt; char b[32]; };
extern "C" int g_beCriAcxData_vtable[4];
extern "C" igMetaObject *g_beCri_metaObject;
struct Obj_367940 { int *vt; int w[19]; };
extern "C" int g_beCri_vtable[4];
extern "C" void **FUN_00367aa0(struct Ref **self, short flag);
extern "C" igMetaObject *g_beCountry_metaObject;
struct Obj_367d60 { int *vt; char pad[4]; };
extern "C" int g_beCountry_vtable[4];
extern "C" igMetaObject *g_beCopyTransform_metaObject;
extern "C" int g_beCopyTransform_vtable[4];
/* _srcTransform (igObjectRefMetaField). */
struct SrcTransformField { int *p; SrcTransformField() { p = 0; } ~SrcTransformField(); };
struct CopyTransformVtable { CopyTransformVtable(int **slot) { *slot = g_beCopyTransform_vtable; } };
struct CopyTransformView : igTransformView, CopyTransformVtable {
    SrcTransformField srcTransform;         /* +108 _srcTransform */
    CopyTransformView() : CopyTransformVtable(&vtable) { }
    ~CopyTransformView() { vtable = g_beCopyTransform_vtable; }
};
extern "C" igMetaObject *g_beCopyModelCtrl2_metaObject;
extern "C" igMetaObject *beCopyModelCtrl2_GetMetaObject(void);
extern "C" int g_beCopyModelCtrl2_vtable[4];
/* _srcNode (igObjectRefMetaField). */
struct SrcNodeField { int *p; SrcNodeField() { p = 0; } ~SrcNodeField(); };
struct CopyModelCtrl2Vtable { CopyModelCtrl2Vtable(int **slot) { *slot = g_beCopyModelCtrl2_vtable; } };
struct CopyModelCtrl2View : igTransformView, CopyModelCtrl2Vtable {
    SrcNodeField srcNode;         /* +108 _srcNode */
    CopyModelCtrl2View() : CopyModelCtrl2Vtable(&vtable) { }
    ~CopyModelCtrl2View() { vtable = g_beCopyModelCtrl2_vtable; }
};
extern "C" igMetaObject *g_beChangePosTransformInfoRam_metaObject;
extern "C" igMetaObject *beChangePosTransformInfoRam_GetMetaObject(void);
struct T_368360 { int word0; int references; };
extern "C" int g_beChangePosTransformInfoRam_vtable[4];
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
extern "C" igMetaObject *beChangePosTransformInfo_GetMetaObject(void);
struct Obj_3685f0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int g_beChangePosTransformInfo_vtable[4];
extern "C" igMetaObject *g_beChangePosTransform_metaObject;
extern "C" igMetaObject *beChangePosTransform_GetMetaObject(void);
extern "C" int g_beChangePosTransform_vtable[4];
extern "C" igMetaObject *g_beCameraMode_metaObject;
struct Obj_368ad0 { int *vt; char p4[8]; int sub[4]; char pad[48]; int *r1; int *r2; char pe[44]; };
extern "C" int g_beCameraMode_vtable[4];
extern "C" int g_igViewMode_vtable[4];
extern "C" int g_igViewMode_metaObject[4];
extern "C" igMetaObject *g_beCameraCtrlInfo_metaObject;
struct Obj_368db0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int g_beCameraCtrlInfo_vtable[4];
extern "C" int g_igObject_metaObject[4];
extern "C" igMetaObject *g_beCameraDemoData_metaObject;
struct T_368fd0 { int word0; int references; };
extern "C" int g_beCameraDemoData_vtable[4];
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
extern "C" int g_beCameraBoxData_vtable[4];
extern "C" igMetaObject *g_beCameraCtrlInfoRamShake_metaObject;
union U_369530 { int vt; char b[64]; };
extern "C" int g_beCameraCtrlInfoRamShake_vtable[4];
extern "C" igMetaObject *g_beCameraCtrl_metaObject;
extern "C" int g_beCameraCtrl_vtable[4];
/* _cameraMode (igObjectRefMetaField). */
struct CameraModeField { int *p; CameraModeField() { p = 0; } ~CameraModeField(); };
/* Stores the derived vtable before the first member constructor runs. */
struct CameraCtrlVtable { CameraCtrlVtable(int **slot) { *slot = g_beCameraCtrl_vtable; } };
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
    ~CameraCtrlView() { vtable = g_beCameraCtrl_vtable; }
};
extern "C" igMetaObject *g_beBkColorInfo_metaObject;
struct Obj_369c30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_beBkColorInfo_vtable[4];
extern "C" igMetaObject *g_beBkColor_metaObject;
union U_369ea0 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int g_beBkColor_vtable[4];
extern "C" igMetaObject *g_beBaseInfoRamList_metaObject;
union U_36a140 { int vt; char b[32]; };
extern "C" int g_beBaseInfoRamList_vtable[4];
extern "C" igMetaObject *g_beBaseInfoRam_metaObject;
extern "C" igMetaObject *g_beBaseInfoRamTimer_metaObject;
struct Obj_36a5a0 { int *vt; char pad4[4]; void *s; char pad12[52]; };
extern "C" int g_beBaseInfoRamTimer_vtable[4];
extern "C" igMetaObject *g_beBaseInfoManagerList_metaObject;
extern "C" igMetaObject *beBaseInfoManagerList_GetMetaObject(void);
extern "C" int g_beBaseInfoManagerList_vtable[4];
extern "C" igMetaObject *g_beBaseInfoManager_metaObject;
extern "C" igMetaObject *beBaseInfoManager_GetMetaObject(void);
extern "C" igMetaObject *g_beBaseInfoList_metaObject;
extern "C" igMetaObject *beBaseInfoList_GetMetaObject(void);
struct Obj_36ab90 { int *vt; char pad[28]; };
extern "C" int g_beBaseInfoList_vtable[4];
extern "C" igMetaObject *g_beBaseInfo_metaObject;
extern "C" igMetaObject *beBaseInfo_GetMetaObject(void);
extern "C" igMetaObject *g_beBaseInfoDataList_metaObject;
struct Obj_36af60 { int *vt; char pad[28]; };
extern "C" int g_beBaseInfoDataList_vtable[4];
extern "C" igMetaObject *g_beBaseInfoData_metaObject;
extern "C" igMetaObject *g_beActionStarterInfoRam_metaObject;
struct T_36b210 { int word0; int references; };
extern "C" int g_beActionStarterInfoRam_vtable[4];
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
extern "C" int g_beActionStarterInfo_vtable[4];
extern "C" O *FUN_0036b430(O *arg0, short arg1);
extern "C" igMetaObject *g_beAsTargetModelDataList_metaObject;
struct Obj_36b6a0 { int *vt; char pad[28]; };
extern "C" int g_beAsTargetModelDataList_vtable[4];
extern "C" igMetaObject *g_beAsTargetModelData_metaObject;
union U_36b7e0 { int vt; char b[16]; };
extern "C" int g_beAsTargetModelData_vtable[4];
extern "C" igMetaObject *g_beActionStarterData2_metaObject;
union U_36ba60 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int g_beActionStarterData2_vtable[4];
extern "C" int g_beActionStarterData_vtable[4];
extern "C" igMetaObject *g_beActionStarterDataList_metaObject;
struct Obj_36bd00 { int *vt; char pad[28]; };
extern "C" int g_beActionStarterDataList_vtable[4];
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
extern "C" int g_beActionStarter_vtable[4];
extern "C" igMetaObject *g_beAction2InfoWork_metaObject;
extern "C" igMetaObject *beAction2InfoWork_GetMetaObject(void);
union U_36c380 { int vt; char b[96]; };
extern "C" int g_beAction2InfoWork_vtable[4];
typedef struct S_temp_a0_36c450 { char pad4[4]; int f4; } S_temp_a0_36c450;
extern "C" igMetaObject *g_beAction2InfoRam_metaObject;
extern "C" igMetaObject *beAction2InfoRam_GetMetaObject(void);
union U_36c6d0 { int vt; char b[64]; };
extern "C" int g_beAction2InfoRam_vtable[4];
typedef struct S_temp_a0_36c790 { char pad4[4]; int f4; } S_temp_a0_36c790;
extern "C" igMetaObject *g_beAction2InfoList_metaObject;
extern "C" igMetaObject *beAction2InfoList_GetMetaObject(void);
struct Obj_36ca10 { int *vt; char pad[28]; };
extern "C" int g_beAction2InfoList_vtable[4];
extern "C" igMetaObject *g_beAction2Info_metaObject;
extern "C" igMetaObject *beAction2Info_GetMetaObject(void);
extern "C" int g_beAction2Info_vtable[4];
extern "C" ObjectRefWord *FUN_0036cc00(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *g_beAction2FLASHSET_metaObject;
union U_36ce60 { int vt; char b[16]; };
extern "C" int g_beAction2FLASHSET_vtable[4];
extern "C" igMetaObject *g_beAction2WAITCHECK_metaObject;
union U_36cff0 { int vt; char b[16]; };
extern "C" int g_beAction2WAITCHECK_vtable[4];
extern "C" igMetaObject *g_beAction2FADESET_metaObject;
union U_36d1f0 { int vt; char b[32]; };
extern "C" int g_beAction2FADESET_vtable[4];
extern "C" igMetaObject *g_beAction2JOINTSET_metaObject;
union U_36d3f0 { int vt; char b[32]; };
extern "C" int g_beAction2JOINTSET_vtable[4];
extern "C" igMetaObject *g_beAction2MOTIONSET_metaObject;
union U_36d630 { int vt; char b[32]; };
extern "C" int g_beAction2MOTIONSET_vtable[4];
extern "C" igMetaObject *g_beAction2DataList_metaObject;
struct Obj_36d900 { int *vt; char pad[28]; };
extern "C" int g_beAction2DataList_vtable[4];
extern "C" igMetaObject *g_beAction2Data_metaObject;
union U_36da90 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" int g_beAction2Data_vtable[4];
extern "C" igMetaObject *g_beAction2_metaObject;
union U_36de10 { int vt; char b[32]; };
extern "C" int g_beAction2_vtable[4];
extern "C" igMetaObject *g_be_metaObject;
struct T_36e080 { int word0; int references; };
extern "C" int g_be_vtable[4];
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
extern "C" int g_ParticleArray_vtable[4];
struct igMetaObject_36e3d0;
extern "C" igMetaObject_36e3d0 *igParticleArray_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_ParticleTimer_metaObject;
extern "C" igMetaObject *ParticleTimer_GetMetaObject(void);
struct Obj_36e660 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int FUN_0019d120(struct Obj_36e660 *, int);
extern "C" int g_ParticleTimer_vtable[4];
struct igMetaObject_36e6f0;
extern "C" igMetaObject_36e6f0 *igGeometry_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_ParticleInfo_metaObject;
extern "C" igMetaObject *ParticleInfo_GetMetaObject(void);
struct Obj_36ea50 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; int w28; int w29; int w30; int w31; int w32; int w33; int w34; int w35; int w36; int w37; int w38; int w39; int w40; int w41; int w42; int w43; int w44; int w45; int w46; int w47; int w48; int w49; int w50; int w51; int w52; int w53; int w54; int w55; int w56; int w57; int w58; int w59; int w60; int w61; int w62; int w63; int w64; int w65; int w66; int w67; int w68; int w69; int w70; int w71; int w72; int w73; int w74; int w75; int w76; int w77; int w78; int w79; int w80; int w81; int w82; int w83; int w84; int w85; int w86; int w87; int w88; int w89; int w90; int w91; int w92; int w93; int w94; int w95; int w96; int w97; int w98; int w99; int w100; int w101; int w102; int w103; int w104; int w105; int w106; int w107; int w108; int w109; int w110; int w111; int w112; int w113; int w114; int w115; int w116; int w117; int w118; int w119; int w120; int w121; int w122; int w123; int w124; int w125; int w126; int w127; int w128; int w129; int w130; int w131; int w132; int w133; int w134; int w135; int w136; int w137; int w138; int w139; int w140; int w141; int w142; int w143; int w144; int w145; int w146; int w147; int w148; int w149; int w150; int w151; int w152; int w153; int w154; int w155; int w156; int w157; int w158; int w159; int w160; int w161; int w162; int w163; int w164; int w165; int w166; int w167; int w168; int w169; int w170; int w171; int w172; int w173; int w174; int w175; int w176; int w177; int w178; int w179; int w180; int w181; int w182; int w183; int w184; int w185; int w186; int w187; int w188; int w189; int w190; int w191; int w192; int w193; int w194; int w195; int w196; int w197; int w198; int w199; int w200; int w201; int w202; int w203; int w204; int w205; int w206; int w207; int w208; int w209; int w210; int w211; int w212; int w213; int w214; int w215; int w216; int w217; int w218; int w219; int w220; int w221; int w222; int w223; int w224; int w225; int w226; int w227; int w228; int w229; int w230; int w231; int w232; int w233; int w234; int w235; int w236; int w237; int w238; int w239; int w240; int w241; int w242; int w243; int w244; int w245; int w246; int w247; int w248; int w249; int w250; int w251; int w252; int w253; int w254; int w255; };
extern "C" int FUN_0019b040(struct Obj_36ea50 *, int);
extern "C" int g_ParticleInfo_vtable[4];
extern "C" int g_igSceneInfo_metaObject[4];
extern "C" void ParticleInfo_resetFields(ParticleInfo *self, int clearControls);
extern "C" void beBinDataObject_userDestruct(beBinDataObject *arg0);
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
extern "C" void beLuaDataObject_userDestruct(beLuaDataObject *arg0);
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
extern "C" void beNumVerData_userConstruct(Obj_36f970 *arg0, int arg1);
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
extern "C" void beNumVerData_userDestruct(Obj_36fae0 *arg0);
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_88_0_36fd80 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad4; int f8; int f12; };
extern "C" void beSaveDataDeliver_userDestruct(DW4VC_88_0_36fd80 *arg0);
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class SvPlatDataGCVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
extern "C" void beSvPlatDataGC_userDestruct(beSvPlatDataGC *arg0);
extern "C" void beSvPs2McImage128k_userConstruct(beSvPs2McImage128k *arg0, int arg1);
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class SvPs2McImageVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" void beXboxImage24k_userConstruct(beXboxImage24k *arg0, int arg1);
class DW4VC_88_0_370070 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad4; int f8; };
extern "C" void beXboxImage24k_userDestruct(DW4VC_88_0_370070 *arg0);
/* matching construct: dummy-virtual class: filler virtual slots place vX at the retail vtable offset */
class TransformSyncChildVirtualSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();  virtual int vX(int); };
extern "C" void beTransformSync_SetMatrix(beTransformSync *arg0, int arg1);
extern "C" int g_igAppearanceList_metaObject[4];

#endif
