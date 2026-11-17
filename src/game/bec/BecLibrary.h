#ifndef DW4_BEC_LIBRARY_H
#define DW4_BEC_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igObjectDispatchView.h"
#include "dw4/igTransformDispatchView.h"
#include "dw4/ClassRegistration.h"
#include "dw4/beSystem.h"
#include "dw4/be.h"
#include "dw4/beAction2.h"
#include "dw4/beAction2FADESET.h"
#include "dw4/beAction2FLASHSET.h"
#include "dw4/beAction2Info.h"
#include "dw4/beAction2InfoWork.h"
#include "dw4/beAction2JOINTSET.h"
#include "dw4/beAction2MOTIONSET.h"
#include "dw4/beAction2WAITCHECK.h"
#include "dw4/beActionStarter.h"
#include "dw4/beActionStarterData2.h"
#include "dw4/beActionStarterInfo.h"
#include "dw4/beBaseInfo.h"
#include "dw4/beBaseInfoData.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beBaseInfoManager.h"
#include "dw4/beBaseInfoRam.h"
#include "dw4/beBaseInfoRamTimer.h"
#include "dw4/beBkColor.h"
#include "dw4/beBkColorInfo.h"
#include "dw4/beCameraBoxData.h"
#include "dw4/beCameraCtrl.h"
#include "dw4/beCameraCtrlInfo.h"
#include "dw4/beCameraCtrlInfoRamShake.h"
#include "dw4/beCameraDemoData.h"
#include "dw4/beCameraMode.h"
#include "dw4/beChangePosTransform.h"
#include "dw4/beChangePosTransformInfo.h"
#include "dw4/beCopyModelCtrl2.h"
#include "dw4/beCopyTransform.h"
#include "dw4/beCri.h"
#include "dw4/beCriAcxData.h"
#include "dw4/beCriFxInfo.h"
#include "dw4/beCriHandle.h"
#include "dw4/beCriSfpData.h"
#include "dw4/beCriSndf.h"
#include "dw4/beDataBase.h"
#include "dw4/beDataObjBool.h"
#include "dw4/beDataObjBoolList.h"
#include "dw4/beDataObjFloatList.h"
#include "dw4/beDataObjInt.h"
#include "dw4/beDataObjIntList.h"
#include "dw4/beDataObjList.h"
#include "dw4/beDataObjListList.h"
#include "dw4/beDataObjObjectList.h"
#include "dw4/beDataObjString.h"
#include "dw4/beDataObjStringList.h"
#include "dw4/beDBManager.h"
#include "dw4/beDBManagerInfo.h"
#include "dw4/beDemoKeepMes.h"
#include "dw4/beDemoManager.h"
#include "dw4/beDemoManagerWork.h"
#include "dw4/beFileChkObj.h"
#include "dw4/beFileListInfo.h"
#include "dw4/beFileListInfoManager.h"
#include "dw4/beFont.h"
#include "dw4/beFontGeomAttrPair.h"
#include "dw4/beFontInfo.h"
#include "dw4/beGenerater.h"
#include "dw4/beGeneraterInfo.h"
#include "dw4/beGeneraterInfoWork.h"
#include "dw4/beHitLandDeliv.h"
#include "dw4/beHitLandDelivInfo.h"
#include "dw4/beHitLandModel.h"
#include "dw4/beHitLandModelInfo.h"
#include "dw4/beHitLandModelOrder.h"
#include "dw4/beHitLandModelTraversal.h"
#include "dw4/beHitLandResultData.h"
#include "dw4/beKeyboardReceiver.h"
#include "dw4/beLayerCtl.h"
#include "dw4/beLayerInfo.h"
#include "dw4/beLightCtrl.h"
#include "dw4/beLightCtrlInfo.h"
#include "dw4/beLOA.h"
#include "dw4/beLoadingNode.h"
#include "dw4/beLua.h"
#include "dw4/beLuaInfo.h"
#include "dw4/beLuaState.h"
#include "dw4/beMatCtrl.h"
#include "dw4/beMatCtrlInfo.h"
#include "dw4/beMatCtrlInfoWork.h"
#include "dw4/beMemory.h"
#include "dw4/beMessenger.h"
#include "dw4/beMessengerArgData.h"
#include "dw4/beMessengerDelay.h"
#include "dw4/beMessengerGroup.h"
#include "dw4/beMessengerWork.h"
#include "dw4/beMeterCtrl.h"
#include "dw4/beMeterCtrlInfo.h"
#include "dw4/beMeterCtrlNode.h"
#include "dw4/beModelCtrl.h"
#include "dw4/beModelCtrlACTION.h"
#include "dw4/beModelCtrlAIMAP.h"
#include "dw4/beModelCtrlCTRL.h"
#include "dw4/beModelCtrlHITBOX.h"
#include "dw4/beModelCtrlInfo.h"
#include "dw4/beModelCtrlInfoAI.h"
#include "dw4/beModelCtrlInfoHitBody.h"
#include "dw4/beModelCtrlInfoRideOn.h"
#include "dw4/beModelCtrlInfoRideOn2.h"
#include "dw4/beModelCtrlInfoRideOn3.h"
#include "dw4/beModelCtrlInfoRideOn4.h"
#include "dw4/beModelCtrlInfoWork.h"
#include "dw4/beModelCtrlJUMP.h"
#include "dw4/beModelCtrlLABEL.h"
#include "dw4/beModelCtrlLABELCTRL.h"
#include "dw4/beModelCtrlLUACALL.h"
#include "dw4/beModelCtrlMOVE.h"
#include "dw4/beModelCtrlMOVEEX.h"
#include "dw4/beModelCtrlMoveObject.h"
#include "dw4/beModelCtrlMOVERL.h"
#include "dw4/beModelCtrlMSGBOX.h"
#include "dw4/beModelCtrlMUTEKI.h"
#include "dw4/beModelCtrlNode2.h"
#include "dw4/beModelCtrlPDMOVE.h"
#include "dw4/beModelCtrlSCEffect.h"
#include "dw4/beModelCtrlSCHitBox.h"
#include "dw4/beModelCtrlSCSound.h"
#include "dw4/beModelCtrlWCHECK.h"
#include "dw4/beMovie.h"
#include "dw4/beMovieInfo.h"
#include "dw4/beMovieInfoData.h"
#include "dw4/beNodeAnim.h"
#include "dw4/beNumberCtrl.h"
#include "dw4/beNumberCtrlInfo.h"
#include "dw4/beNumberCtrlInfoWork.h"
#include "dw4/bePadData.h"
#include "dw4/bePadManager.h"
#include "dw4/beParticleCtrl2.h"
#include "dw4/beParticleCtrl2Info.h"
#include "dw4/beParticleCtrl2InfoWork.h"
#include "dw4/bePlaySE.h"
#include "dw4/bePoint01.h"
#include "dw4/bePoint01Info.h"
#include "dw4/beResetNode.h"
#include "dw4/beSaveApi.h"
#include "dw4/beSaveDataDeliver.h"
#include "dw4/beSaveMemoryObj.h"
#include "dw4/beSaveUtil.h"
#include "dw4/beSaveUtilInfo.h"
#include "dw4/beSeCtl.h"
#include "dw4/beSeInfo.h"
#include "dw4/beSelectCtrl.h"
#include "dw4/beSelectCtrlInfo.h"
#include "dw4/beSelectCtrlInfoWork.h"
#include "dw4/beShadow01.h"
#include "dw4/beShadow01Info.h"
#include "dw4/beSound.h"
#include "dw4/beSoundInfo.h"
#include "dw4/beStaticInfo.h"
#include "dw4/beStaticInfoCtl.h"
#include "dw4/beSvConnectCheck.h"
#include "dw4/beSvEndApi.h"
#include "dw4/beSvFileFindApi.h"
#include "dw4/beSvFileMakeApi.h"
#include "dw4/beSvFormatApi.h"
#include "dw4/beSvGetFreeSizeApi.h"
#include "dw4/beSvReadMediaApi.h"
#include "dw4/beSvStartApi.h"
#include "dw4/beSvUseCheckApi.h"
#include "dw4/beSvWriteMediaApi.h"
#include "dw4/beSwitchCtrl.h"
#include "dw4/beSwitchCtrlInfo.h"
#include "dw4/beTargetObj.h"
#include "dw4/beTextureCtrl.h"
#include "dw4/beTextureCtrlInfo.h"
#include "dw4/beTextureCtrlWork.h"
#include "dw4/beTimer.h"
#include "dw4/beUnicodeObj.h"
#include "dw4/beWaterPlain.h"
#include "dw4/beWaterPlainInfo.h"
#include "dw4/beWeapon.h"
#include "dw4/beWeaponAttachData.h"
#include "dw4/beWeaponAttachDataList.h"
#include "dw4/beWeaponInfo.h"
#include "dw4/beWeaponSeqData.h"
#include "dw4/igFont.h"
#include "dw4/libBecRuntimePlugin.h"
#include "dw4/ParticleArray.h"
#include "dw4/ParticleInfo.h"
#include "dw4/ParticleTimer.h"
#include "dw4/StringPool.h"
#include "dw4/igActorList.h"
#include "dw4/igAdxAudio.h"
#include "dw4/igAnimationDatabase.h"
#include "dw4/igAppearanceList.h"
#include "dw4/igAttrList.h"
#include "dw4/igAttrSet.h"
#include "dw4/igBitmapFont.h"
#include "dw4/igBlendFunctionAttr.h"
#include "dw4/igBlendStateAttr.h"
#include "dw4/igBoolList.h"
#include "dw4/igCamera.h"
#include "dw4/igColorAttr.h"
#include "dw4/igDataLists.h"
#include "dw4/igDirectory.h"
#include "dw4/igEventReceiver.h"
#include "dw4/igGeometry.h"
#include "dw4/igGeometryAttrList.h"
#include "dw4/igGeometryList.h"
#include "dw4/igGraphPath.h"
#include "dw4/igGroup.h"
#include "dw4/igImage.h"
#include "dw4/igInfo.h"
#include "dw4/igInfoList.h"
#include "dw4/igInfoManager.h"
#include "dw4/igInsightCore.h"
#include "dw4/igInsightPlugin.h"
#include "dw4/igIntList.h"
#include "dw4/igIntersectTraversal.h"
#include "dw4/igLightSet.h"
#include "dw4/igLightingStateAttr.h"
#include "dw4/igLuaGlue.h"
#include "dw4/igLuaState.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igMemory.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igMetaObject.h"
#include "dw4/igMovieManager.h"
#include "dw4/igNamedObject.h"
#include "dw4/igNode.h"
#include "dw4/igNodeList.h"
#include "dw4/igObject.h"
#include "dw4/igObjectList.h"
#include "dw4/igObjectSystem.h"
#include "dw4/igParticleArray.h"
#include "dw4/igProbe.h"
#include "dw4/igProjectiveShadowShader.h"
#include "dw4/igRandomNumber.h"
#include "dw4/igSceneInfo.h"
#include "dw4/igStringObj.h"
#include "dw4/igStringRefList.h"
#include "dw4/igSwitch.h"
#include "dw4/igTextureAttr.h"
#include "dw4/igTextureStateAttr.h"
#include "dw4/igTransform.h"
#include "dw4/igTransformList.h"
#include "dw4/igTransformRecorder.h"
#include "dw4/igVertexArray.h"
#include "dw4/igViewMode.h"
#include "dw4/igViewerParameters.h"
#include "dw4/igViewerSceneInfoManager.h"
#include <string.h>
static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }
#define RELEASE_OBJ(o) { \
    if (o) { \
        --(o)->_refCount; \
        if (((unsigned long long)(long long)(o)->_refCount & 0x7fffffULL) == 0) \
            igObject_Destroy(o); \
    } }
#define BEDATABASE_NO_INDEX (-1)
#include "dw4/igTDataList.h"
#include "dw4/igBoolArrayMetaField.h"
#include "dw4/igBoolMetaField.h"
#include "dw4/igCharArrayMetaField.h"
#include "dw4/igCharMetaField.h"
#include "dw4/igEnumMetaField.h"
#include "dw4/igFloatArrayMetaField.h"
#include "dw4/igFloatMetaField.h"
#include "dw4/igIntArrayMetaField.h"
#include "dw4/igIntMetaField.h"
#include "dw4/igLongMetaField.h"
#include "dw4/igMatrix44fMetaField.h"
#include "dw4/igMemoryRefMetaField.h"
#include "dw4/igMetaEnum.h"
#include "dw4/igObjectRefMetaField.h"
#include "dw4/igRawRefMetaField.h"
#include "dw4/igShortArrayMetaField.h"
#include "dw4/igShortMetaField.h"
#include "dw4/igStringMetaField.h"
#include "dw4/igUnsignedIntMetaField.h"
#include "dw4/igUnsignedLongMetaField.h"
#include "dw4/igUnsignedShortMetaField.h"
#include "dw4/igVec2fMetaField.h"
#include "dw4/igVec3fMetaField.h"
#include "dw4/igVec4fMetaField.h"
#include "dw4/emptyString.h"
#include "dw4/internalNonRefCountedObjectList.h"
#include "dw4/igAABox.h"
#include "dw4/igAABoxList.h"
#include "dw4/igMatrix44fList.h"
#include "dw4/igRayList.h"
#include "dw4/igVec3fList.h"
extern "C" void igIntListList_EnsureRegistered(void);
extern "C" void igDirectoryList_EnsureRegistered(void);
extern "C" void igFile_EnsureRegistered(void);
extern "C" void igCharList_EnsureRegistered(void);
extern "C" void igShortList_EnsureRegistered(void);

extern "C" void BecLibrary_MarkRegistered(void);
extern "C" void *libBecRuntimePlugin_GetMetaObject(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beLua_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beWaterPlain_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beAction2_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMeterCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beWeapon_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_bePoint01_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beBkColor_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beShadow01_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSound_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSeCtl_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beLayerCtl_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beLightCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beStaticInfoCtl_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beTextureCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSystem_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beFileListInfoManager_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beCri_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_be_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beTimer_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMemory_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beTimer_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beDemoManager_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_be_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beCri_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_bePadManager_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beFileListInfoManager_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMessenger_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSystem_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beTextureCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSaveUtil_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beDBManager_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMovie_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beStaticInfoCtl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNumberCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beLightCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSwitchCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beFont_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beLayerCtl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beActionStarter_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSeCtl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSound_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beHitLandDeliv_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beHitLandModel_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beGenerater_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beShadow01_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beChangePosTransform_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beBkColor_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_bePoint01_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beCameraCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beWeapon_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beTargetObj_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMeterCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beAction2_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beWaterPlain_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSelectCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMatCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beLua_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beParticleCtrl2_Construct(igSmartPointer<igObject> *self);
extern "C" igObject *igInsightPlugin_Construct(igObject *self);
extern "C" void libBecRuntimePlugin_EnsureRegistered(void);
extern "C" int libBecRuntimePlugin_GetVTable(void);
extern "C" CallbackArray *libBecRuntimePlugin_Register(void);
extern "C" void libBecRuntimePlugin_GetMetaObjectFunction(void);
extern "C" void libBecRuntimePlugin_InitFields(void);
extern "C" void *beWeaponInfoRam_GetMetaObject(void);
extern "C" int beWeaponInfoRam_GetVTable(void);
extern "C" void beWeaponInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beWeaponInfoRam_Register(void);
extern "C" void beWeaponInfoRam_GetMetaObjectFunction(void);
extern "C" void *beWeaponInfo_GetMetaObject(void);
extern "C" int beWeaponInfo_GetVTable(void);
/* The destructor inlined for an object reference field: releases what the field points at. */
static inline void igObjectRef_Release(igObject **slot) {
    if (slot) {
        igObject *object = *slot;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
}
/* The destructor inlined for a string field: drops the reference and frees the chunk with the last one. */
static inline void igStringRef_Release(char **slot) {
    if (slot) {
        char *text = *slot;
        if (text) {
            int *header = (int *)(text - 8);
            int refCount = *(int *)(text - 4) - 1;
            *(int *)(text - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
            }
        }
    }
}
extern "C" void beWeaponInfo_EnsureRegistered(void);
extern "C" CallbackArray *beWeaponInfo_Register(void);
extern "C" void beWeaponInfo_GetMetaObjectFunction(void);
extern "C" int igNamedObjectList_GetOrCreateMetaObject(...);
extern "C" void beWeaponInfo_InitFields(void);
extern "C" igMetaObject *beWeaponSeqDataList_GetOrCreateMetaObject(void);
extern "C" void *beWeaponSeqDataList_GetMetaObject(void);
extern "C" int beWeaponSeqDataList_GetVTable(void);
extern "C" void beWeaponSeqDataList_EnsureRegistered(void);
extern "C" CallbackArray *beWeaponSeqDataList_Register(void);
extern "C" void beWeaponSeqDataList_GetMetaObjectFunction(void);
extern "C" void *beWeaponSeqData_GetMetaObject(void);
extern "C" int beWeaponSeqData_GetVTable(void);
extern "C" void beWeaponSeqData_EnsureRegistered(void);
extern "C" CallbackArray *beWeaponSeqData_Register(void);
extern "C" void beWeaponSeqData_GetMetaObjectFunction(void);
extern "C" void beWeaponSeqData_InitFields(void);
extern "C" igMetaObject *beWeapon_GetOrCreateMetaObject(void);
extern "C" void *beWeapon_GetMetaObject(void);
extern "C" int beWeapon_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beBaseInfoList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *beBaseInfoManager_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beWeapon_EnsureRegistered(void);
extern "C" CallbackArray *beWeapon_Register(void);
extern "C" void beWeapon_GetMetaObjectFunction(void);
extern "C" void beWeapon_InitFields(void);
extern "C" igMetaObject *beWeaponAttachDataList_GetOrCreateMetaObject(void);
extern "C" int beWeaponAttachDataList_GetVTable(void);
extern "C" void beWeaponAttachDataList_EnsureRegistered(void);
extern "C" CallbackArray *beWeaponAttachDataList_Register(void);
extern "C" void beWeaponAttachDataList_GetMetaObjectFunction(void);
extern "C" int beWeaponAttachData_GetVTable(void);
extern "C" void beWeaponAttachData_EnsureRegistered(void);
extern "C" CallbackArray *beWeaponAttachData_Register(void);
extern "C" void beWeaponAttachData_GetMetaObjectFunction(void);
extern "C" void beWeaponAttachData_InitFields(void);
extern "C" igMetaObject *igAppearanceListList_GetOrCreateMetaObject(void);
extern "C" int igAppearanceListList_GetVTable(void);
extern "C" void igAppearanceListList_EnsureRegistered(void);
extern "C" CallbackArray *igAppearanceListList_Register(void);
extern "C" void igAppearanceListList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelectListBec_GetOrCreateMetaObject(void);
extern "C" int igModelViewMatrixBoneSelectListBec_GetVTable(void);
extern "C" void igModelViewMatrixBoneSelectListBec_EnsureRegistered(void);
extern "C" CallbackArray *igModelViewMatrixBoneSelectListBec_Register(void);
extern "C" void igModelViewMatrixBoneSelectListBec_GetMetaObjectFunction(void);
extern "C" void *beWaterPlainInfoRam_GetMetaObject(void);
extern "C" int beWaterPlainInfoRam_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beWaterMove_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" void beWaterPlainInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beWaterPlainInfoRam_Register(void);
extern "C" void beWaterPlainInfoRam_GetMetaObjectFunction(void);
extern "C" int igFloatListList_GetOrCreateMetaObject(void);
extern "C" int igFloatList_GetOrCreateMetaObject(void);
extern "C" void beWaterPlainInfoRam_InitFields(void);
extern "C" igMetaObject *beWaterMove_GetOrCreateMetaObject(void);
extern "C" void *beWaterMove_GetMetaObject(void);
extern "C" int beWaterMove_GetVTable(void);
extern "C" void beWaterMove_EnsureRegistered(void);
extern "C" CallbackArray *beWaterMove_Register(void);
extern "C" void beWaterMove_GetMetaObjectFunction(void);
extern "C" void beWaterMove_InitFields(void);
extern "C" igMetaObject *beWaterMoveDataList_GetOrCreateMetaObject(void);
extern "C" void *beWaterMoveDataList_GetMetaObject(void);
extern "C" int beWaterMoveDataList_GetVTable(void);
extern "C" void beWaterMoveDataList_EnsureRegistered(void);
extern "C" CallbackArray *beWaterMoveDataList_Register(void);
extern "C" void beWaterMoveDataList_GetMetaObjectFunction(void);
extern "C" void *beWaterMoveData_GetMetaObject(void);
extern "C" int beWaterMoveData_GetVTable(void);
extern "C" void beWaterMoveData_EnsureRegistered(void);
extern "C" CallbackArray *beWaterMoveData_Register(void);
extern "C" void beWaterMoveData_GetMetaObjectFunction(void);
extern "C" void beWaterMoveData_InitFields(void);
extern "C" void *beWaterPlainInfo_GetMetaObject(void);
extern "C" int beWaterPlainInfo_GetVTable(void);
extern "C" void beWaterPlainInfo_EnsureRegistered(void);
extern "C" CallbackArray *beWaterPlainInfo_Register(void);
extern "C" void beWaterPlainInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *beWaterPlain_GetOrCreateMetaObject(void);
extern "C" void *beWaterPlain_GetMetaObject(void);
extern "C" int beWaterPlain_GetVTable(void);
extern "C" void beWaterPlain_EnsureRegistered(void);
extern "C" CallbackArray *beWaterPlain_Register(void);
extern "C" void beWaterPlain_GetMetaObjectFunction(void);
extern "C" void *beUnicode_GetMetaObject(void);
extern "C" int beUnicode_GetVTable(void);
extern "C" void beUnicode_EnsureRegistered(void);
extern "C" CallbackArray *beUnicode_Register(void);
extern "C" void beUnicode_GetMetaObjectFunction(void);
extern "C" void *beTransformSync_GetMetaObject(void);
extern "C" int beTransformSync_GetVTable(void);
extern "C" void beTransformSync_EnsureRegistered(void);
extern "C" CallbackArray *beTransformSync_Register(void);
extern "C" void beTransformSync_GetMetaObjectFunction(void);
extern "C" void beTransformSync_InitFields(void);
extern "C" igMetaObject *beTimer_GetOrCreateMetaObject(void);
extern "C" void *beTimer_GetMetaObject(void);
extern "C" int beTimer_GetVTable(void);
extern "C" void beTimer_EnsureRegistered(void);
extern "C" CallbackArray *beTimer_Register(void);
extern "C" void beTimer_GetMetaObjectFunction(void);
extern "C" void beTimer_InitFields(void);
extern "C" igMetaObject *beTimerDataList_GetOrCreateMetaObject(void);
extern "C" void *beTimerDataList_GetMetaObject(void);
extern "C" int beTimerDataList_GetVTable(void);
extern "C" void beTimerDataList_EnsureRegistered(void);
extern "C" CallbackArray *beTimerDataList_Register(void);
extern "C" void beTimerDataList_GetMetaObjectFunction(void);
extern "C" int beTimerData_GetVTable(void);
extern "C" void beTimerData_EnsureRegistered(void);
extern "C" CallbackArray *beTimerData_Register(void);
extern "C" void beTimerData_GetMetaObjectFunction(void);
extern "C" void beTimerData_InitFields(void);
extern "C" int beTextureCtrlInfoList_GetVTable(void);
extern "C" void beTextureCtrlInfoList_EnsureRegistered(void);
extern "C" CallbackArray *beTextureCtrlInfoList_Register(void);
extern "C" void beTextureCtrlInfoList_GetMetaObjectFunction(void);
extern "C" int beTextureCtrlInfo_GetVTable(void);
extern "C" void beTextureCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beTextureCtrlInfo_Register(void);
extern "C" void beTextureCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beTextureCtrlInfo_InitFields(void);
extern "C" int beTextureCtrlAttr_GetVTable(void);
extern "C" void beTextureCtrlAttr_EnsureRegistered(void);
extern "C" CallbackArray *beTextureCtrlAttr_Register(void);
extern "C" void beTextureCtrlAttr_GetMetaObjectFunction(void);
extern "C" void beTextureCtrlAttr_InitFields(void);
extern "C" void *beTextureCtrlData_GetMetaObject(void);
extern "C" int beTextureCtrlData_GetVTable(void);
extern "C" void beTextureCtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beTextureCtrlData_Register(void);
extern "C" void beTextureCtrlData_GetMetaObjectFunction(void);
extern "C" void beTextureCtrlData_InitFields(void);
extern "C" igMetaObject *beTextureCtrl_GetOrCreateMetaObject(void);
extern "C" void *beTextureCtrl_GetMetaObject(void);
extern "C" int beTextureCtrl_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beTextureCtrlWork_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beTextureCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beTextureCtrl_Register(void);
extern "C" void beTextureCtrl_GetMetaObjectFunction(void);
extern "C" void beTextureCtrl_InitFields(void);
extern "C" igMetaObject *beTextureCtrlWork_GetOrCreateMetaObject(void);
extern "C" void *beTextureCtrlWork_GetMetaObject(void);
extern "C" int beTextureCtrlWork_GetVTable(void);
extern "C" void beTextureCtrlWork_EnsureRegistered(void);
extern "C" CallbackArray *beTextureCtrlWork_Register(void);
extern "C" void beTextureCtrlWork_GetMetaObjectFunction(void);
extern "C" void beTextureCtrlWork_InitFields(void);
extern "C" igMetaObject *beTargetObj_GetOrCreateMetaObject(void);
extern "C" void *beTargetObj_GetMetaObject(void);
extern "C" int beTargetObj_GetVTable(void);
extern "C" void beTargetObj_EnsureRegistered(void);
extern "C" CallbackArray *beTargetObj_Register(void);
extern "C" void beTargetObj_GetMetaObjectFunction(void);
extern "C" void beTargetObj_InitFields(void);
extern "C" void *beSystem_GetMetaObject(void);
extern "C" int beSystem_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igRandomNumber_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" CallbackArray *beSystem_Register(void);
extern "C" void beSystem_GetMetaObjectFunction(void);
extern "C" void beSystem_InitFields(void);
extern "C" void *beSwitchCtrlInfo_GetMetaObject(void);
extern "C" int beSwitchCtrlInfo_GetVTable(void);
extern "C" void beSwitchCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beSwitchCtrlInfo_Register(void);
extern "C" void beSwitchCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beSwitchCtrlInfo_InitFields(void);
extern "C" igMetaObject *beSwitchCtrl_GetOrCreateMetaObject(void);
extern "C" void *beSwitchCtrl_GetMetaObject(void);
extern "C" int beSwitchCtrl_GetVTable(void);
extern "C" void beSwitchCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beSwitchCtrl_Register(void);
extern "C" void beSwitchCtrl_GetMetaObjectFunction(void);
extern "C" igMetaObject *beStaticInfoCtl_GetOrCreateMetaObject(void);
extern "C" void *beStaticInfoCtl_GetMetaObject(void);
extern "C" int beStaticInfoCtl_GetVTable(void);
extern "C" void beStaticInfoCtl_EnsureRegistered(void);
extern "C" CallbackArray *beStaticInfoCtl_Register(void);
extern "C" void beStaticInfoCtl_GetMetaObjectFunction(void);
extern "C" void beStaticInfoCtl_InitFields(void);
extern "C" void *beStaticInfo_GetMetaObject(void);
extern "C" int beStaticInfo_GetVTable(void);
extern "C" void beStaticInfo_EnsureRegistered(void);
extern "C" CallbackArray *beStaticInfo_Register(void);
extern "C" void beStaticInfo_GetMetaObjectFunction(void);
extern "C" void *beBinDataObject_GetMetaObject(void);
extern "C" void beBinDataObject_EnsureRegistered(void);
extern "C" CallbackArray *beBinDataObject_Register(void);
extern "C" void beBinDataObject_GetMetaObjectFunction(void);
extern "C" void beBinDataObject_InitFields(void);
extern "C" int beSoundInfo_GetVTable(void);
extern "C" void beSoundInfo_EnsureRegistered(void);
extern "C" CallbackArray *beSoundInfo_Register(void);
extern "C" void beSoundInfo_GetMetaObjectFunction(void);
extern "C" void beSoundInfo_InitFields(void);
extern "C" int beSoundData_GetVTable(void);
extern "C" void beSoundData_EnsureRegistered(void);
extern "C" CallbackArray *beSoundData_Register(void);
extern "C" void beSoundData_GetMetaObjectFunction(void);
extern "C" void beSoundData_InitFields(void);
extern "C" igMetaObject *beSound_GetOrCreateMetaObject(void);
extern "C" int beSound_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_bePlaySEList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beSound_EnsureRegistered(void);
extern "C" CallbackArray *beSound_Register(void);
extern "C" void beSound_GetMetaObjectFunction(void);
extern "C" void beSound_InitFields(void);
extern "C" igMetaObject *bePlaySEList_GetOrCreateMetaObject(void);
extern "C" int bePlaySEList_GetVTable(void);
extern "C" void bePlaySEList_EnsureRegistered(void);
extern "C" CallbackArray *bePlaySEList_Register(void);
extern "C" void bePlaySEList_GetMetaObjectFunction(void);
extern "C" void *bePlaySE_GetMetaObject(void);
extern "C" int bePlaySE_GetVTable(void);
extern "C" void bePlaySE_EnsureRegistered(void);
extern "C" CallbackArray *bePlaySE_Register(void);
extern "C" void bePlaySE_GetMetaObjectFunction(void);
extern "C" void bePlaySE_InitFields(void);
extern "C" igMetaObject *beShadow01InfoList_GetOrCreateMetaObject(void);
extern "C" void *beShadow01InfoList_GetMetaObject(void);
extern "C" int beShadow01InfoList_GetVTable(void);
extern "C" void beShadow01InfoList_EnsureRegistered(void);
extern "C" CallbackArray *beShadow01InfoList_Register(void);
extern "C" void beShadow01InfoList_GetMetaObjectFunction(void);
extern "C" void *beShadow01Info_GetMetaObject(void);
extern "C" int beShadow01Info_GetVTable(void);
extern "C" void beShadow01Info_EnsureRegistered(void);
extern "C" CallbackArray *beShadow01Info_Register(void);
extern "C" void beShadow01Info_GetMetaObjectFunction(void);
extern "C" void beShadow01Info_InitFields(void);
extern "C" igMetaObject *beShadow01_GetOrCreateMetaObject(void);
extern "C" void *beShadow01_GetMetaObject(void);
extern "C" int beShadow01_GetVTable(void);
extern "C" void beShadow01_EnsureRegistered(void);
extern "C" CallbackArray *beShadow01_Register(void);
extern "C" void beShadow01_GetMetaObjectFunction(void);
extern "C" void beShadow01_InitFields(void);
extern "C" void *beSelectCtrlInfo_GetMetaObject(void);
extern "C" int beSelectCtrlInfo_GetVTable(void);
extern "C" void beSelectCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beSelectCtrlInfo_Register(void);
extern "C" void beSelectCtrlInfo_GetMetaObjectFunction(void);
extern "C" void *beSelectCtrlInfoRamData_GetMetaObject(void);
extern "C" int beSelectCtrlInfoRamData_GetVTable(void);
extern "C" void beSelectCtrlInfoRamData_EnsureRegistered(void);
extern "C" CallbackArray *beSelectCtrlInfoRamData_Register(void);
extern "C" void beSelectCtrlInfoRamData_GetMetaObjectFunction(void);
extern "C" void beSelectCtrlInfoRamData_InitFields(void);
extern "C" igMetaObject *beSelectCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" void *beSelectCtrlInfoWork_GetMetaObject(void);
extern "C" int beSelectCtrlInfoWork_GetVTable(void);
extern "C" void beSelectCtrlInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beSelectCtrlInfoWork_Register(void);
extern "C" void beSelectCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" void beSelectCtrlInfoWork_InitFields(void);
extern "C" igMetaObject *beSelectCtrl_GetOrCreateMetaObject(void);
extern "C" void *beSelectCtrl_GetMetaObject(void);
extern "C" int beSelectCtrl_GetVTable(void);
extern "C" void beSelectCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beSelectCtrl_Register(void);
extern "C" void beSelectCtrl_GetMetaObjectFunction(void);
extern "C" void beSelectCtrl_InitFields(void);
extern "C" void *beSeInfo_GetMetaObject(void);
extern "C" int beSeInfo_GetVTable(void);
extern "C" void beSeInfo_EnsureRegistered(void);
extern "C" CallbackArray *beSeInfo_Register(void);
extern "C" void beSeInfo_GetMetaObjectFunction(void);
extern "C" void *beSeInfoData_GetMetaObject(void);
extern "C" int beSeInfoData_GetVTable(void);
extern "C" void beSeInfoData_EnsureRegistered(void);
extern "C" CallbackArray *beSeInfoData_Register(void);
extern "C" void beSeInfoData_GetMetaObjectFunction(void);
extern "C" void beSeInfoData_InitFields(void);
extern "C" igMetaObject *beSeDataList_GetOrCreateMetaObject(void);
extern "C" int beSeDataList_GetVTable(void);
extern "C" void beSeDataList_EnsureRegistered(void);
extern "C" CallbackArray *beSeDataList_Register(void);
extern "C" void beSeDataList_GetMetaObjectFunction(void);
extern "C" int beSeData_GetVTable(void);
extern "C" void beSeData_EnsureRegistered(void);
extern "C" CallbackArray *beSeData_Register(void);
extern "C" void beSeData_GetMetaObjectFunction(void);
extern "C" void beSeData_InitFields(void);
extern "C" igMetaObject *beSeCtl_GetOrCreateMetaObject(void);
extern "C" int beSeCtl_GetVTable(void);
extern "C" void beSeCtl_EnsureRegistered(void);
extern "C" CallbackArray *beSeCtl_Register(void);
extern "C" void beSeCtl_GetMetaObjectFunction(void);
extern "C" void beSeCtl_InitFields(void);
extern "C" int beSaveUtilInfoRam_GetVTable(void);
extern "C" void beSaveUtilInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beSaveUtilInfoRam_Register(void);
extern "C" void beSaveUtilInfoRam_GetMetaObjectFunction(void);
extern "C" void beSaveUtilInfoRam_InitFields(void);
extern "C" void *beSaveUtilInfo_GetMetaObject(void);
extern "C" int beSaveUtilInfo_GetVTable(void);
extern "C" void beSaveUtilInfo_EnsureRegistered(void);
extern "C" CallbackArray *beSaveUtilInfo_Register(void);
extern "C" void beSaveUtilInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *beSaveUtil_GetOrCreateMetaObject(void);
extern "C" void *beSaveUtil_GetMetaObject(void);
extern "C" int beSaveUtil_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSaveApi_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSvConnectCheck_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beSaveUtil_EnsureRegistered(void);
extern "C" CallbackArray *beSaveUtil_Register(void);
extern "C" void beSaveUtil_GetMetaObjectFunction(void);
extern "C" void beSaveUtil_InitFields(void);
extern "C" void *beSvPlatDataPC_GetMetaObject(void);
extern "C" int beSvPlatDataPC_GetVTable(void);
extern "C" void beSvPlatDataPC_EnsureRegistered(void);
extern "C" CallbackArray *beSvPlatDataPC_Register(void);
extern "C" void beSvPlatDataPC_GetMetaObjectFunction(void);
extern "C" igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void);
extern "C" void *beSvPlatDataXbox_GetMetaObject(void);
extern "C" int beSvPlatDataXbox_GetVTable(void);
extern "C" void beSvPlatDataXbox_EnsureRegistered(void);
extern "C" CallbackArray *beSvPlatDataXbox_Register(void);
extern "C" void beSvPlatDataXbox_GetMetaObjectFunction(void);
extern "C" void beSvPlatDataXbox_InitFields(void);
extern "C" igMetaObject *beXboxImage24k_GetOrCreateMetaObject(void);
extern "C" void *beXboxImage24k_GetMetaObject(void);
extern "C" int beXboxImage24k_GetVTable(void);
extern "C" void beXboxImage24k_EnsureRegistered(void);
extern "C" CallbackArray *beXboxImage24k_Register(void);
extern "C" void beXboxImage24k_GetMetaObjectFunction(void);
extern "C" void beXboxImage24k_InitFields(void);
extern "C" void *beSvPlatDataPS2_GetMetaObject(void);
extern "C" int beSvPlatDataPS2_GetVTable(void);
extern "C" void beSvPlatDataPS2_EnsureRegistered(void);
extern "C" CallbackArray *beSvPlatDataPS2_Register(void);
extern "C" void beSvPlatDataPS2_GetMetaObjectFunction(void);
extern "C" void beSvPlatDataPS2_InitFields(void);
extern "C" void *beSvPs2McImage128k_GetMetaObject(void);
extern "C" int beSvPs2McImage128k_GetVTable(void);
extern "C" void beSvPs2McImage128k_EnsureRegistered(void);
extern "C" CallbackArray *beSvPs2McImage128k_Register(void);
extern "C" void beSvPs2McImage128k_GetMetaObjectFunction(void);
extern "C" void beSvPs2McImage128k_InitFields(void);
extern "C" void *beSvPlatDataGC_GetMetaObject(void);
extern "C" int beSvPlatDataGC_GetVTable(void);
extern "C" void beSvPlatDataGC_EnsureRegistered(void);
extern "C" CallbackArray *beSvPlatDataGC_Register(void);
extern "C" void beSvPlatDataGC_GetMetaObjectFunction(void);
extern "C" void beSvPlatDataGC_InitFields(void);
extern "C" igMetaObject *beSvConnectCheck_GetOrCreateMetaObject(void);
extern "C" void *beSvConnectCheck_GetMetaObject(void);
extern "C" int beSvConnectCheck_GetVTable(void);
extern "C" void beSvConnectCheck_EnsureRegistered(void);
extern "C" CallbackArray *beSvConnectCheck_Register(void);
extern "C" void beSvConnectCheck_GetMetaObjectFunction(void);
extern "C" igMetaObject *beSaveApi_GetPublishedMetaObject(void);
extern "C" void *beSvEndApi_GetMetaObject(void);
extern "C" int beSvEndApi_GetVTable(void);
extern "C" void beSvEndApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvEndApi_Register(void);
extern "C" void beSvEndApi_GetMetaObjectFunction(void);
extern "C" void beSvEndApi_InitFields(void);
extern "C" int beSvStartApi_GetVTable(void);
extern "C" void beSvStartApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvStartApi_Register(void);
extern "C" void beSvStartApi_GetMetaObjectFunction(void);
extern "C" void beSvStartApi_InitFields(void);
extern "C" int beSvGetFreeSizeApi_GetVTable(void);
extern "C" void beSvGetFreeSizeApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvGetFreeSizeApi_Register(void);
extern "C" void beSvGetFreeSizeApi_GetMetaObjectFunction(void);
extern "C" void beSvGetFreeSizeApi_InitFields(void);
extern "C" int beSvWriteMediaApi_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSvPlatBaseData_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" void beSvWriteMediaApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvWriteMediaApi_Register(void);
extern "C" void beSvWriteMediaApi_GetMetaObjectFunction(void);
extern "C" void beSvWriteMediaApi_InitFields(void);
extern "C" int beSvReadMediaApi_GetVTable(void);
extern "C" void beSvReadMediaApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvReadMediaApi_Register(void);
extern "C" void beSvReadMediaApi_GetMetaObjectFunction(void);
extern "C" void beSvReadMediaApi_InitFields(void);
extern "C" void *beSvUseCheckApi_GetMetaObject(void);
extern "C" int beSvUseCheckApi_GetVTable(void);
extern "C" void beSvUseCheckApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvUseCheckApi_Register(void);
extern "C" void beSvUseCheckApi_GetMetaObjectFunction(void);
extern "C" void *beSvFormatApi_GetMetaObject(void);
extern "C" int beSvFormatApi_GetVTable(void);
extern "C" void beSvFormatApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvFormatApi_Register(void);
extern "C" void beSvFormatApi_GetMetaObjectFunction(void);
extern "C" void *beSvFileFindApi_GetMetaObject(void);
extern "C" int beSvFileFindApi_GetVTable(void);
extern "C" void beSvFileFindApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvFileFindApi_Register(void);
extern "C" void beSvFileFindApi_GetMetaObjectFunction(void);
extern "C" void *beSvFileMakeApi_GetMetaObject(void);
extern "C" int beSvFileMakeApi_GetVTable(void);
extern "C" void beSvFileMakeApi_EnsureRegistered(void);
extern "C" CallbackArray *beSvFileMakeApi_Register(void);
extern "C" void beSvFileMakeApi_GetMetaObjectFunction(void);
extern "C" void beSvFileMakeApi_InitFields(void);
extern "C" igMetaObject *beSaveApi_GetOrCreateMetaObject(void);
extern "C" void *beSaveApi_GetMetaObject(void);
extern "C" void beSaveApi_EnsureRegistered(void);
extern "C" CallbackArray *beSaveApi_Register(void);
extern "C" void beSaveApi_GetMetaObjectFunction(void);
extern "C" void beSaveApi_InitFields(void);
extern "C" igMetaObject *beSvPlatBaseData_GetOrCreateMetaObject(void);
extern "C" void *beSvPlatBaseData_GetMetaObject(void);
extern "C" int beSvPlatBaseData_GetVTable(void);
extern "C" void beSvPlatBaseData_EnsureRegistered(void);
extern "C" CallbackArray *beSvPlatBaseData_Register(void);
extern "C" void beSvPlatBaseData_GetMetaObjectFunction(void);
extern "C" void beSvPlatBaseData_InitFields(void);
extern "C" igMetaObject *beSvSlotDataList_GetOrCreateMetaObject(void);
extern "C" void *beSvSlotDataList_GetMetaObject(void);
extern "C" int beSvSlotDataList_GetVTable(void);
extern "C" void beSvSlotDataList_EnsureRegistered(void);
extern "C" CallbackArray *beSvSlotDataList_Register(void);
extern "C" void beSvSlotDataList_GetMetaObjectFunction(void);
extern "C" void *beSvSlotPS2_GetMetaObject(void);
extern "C" int beSvSlotPS2_GetVTable(void);
extern "C" void beSvSlotPS2_EnsureRegistered(void);
extern "C" CallbackArray *beSvSlotPS2_Register(void);
extern "C" void beSvSlotPS2_GetMetaObjectFunction(void);
extern "C" igMetaObject *beSvSlotData_GetPublishedMetaObject(void);
extern "C" void *beSvSlotGC_GetMetaObject(void);
extern "C" int beSvSlotGC_GetVTable(void);
extern "C" void beSvSlotGC_EnsureRegistered(void);
extern "C" CallbackArray *beSvSlotGC_Register(void);
extern "C" void beSvSlotGC_GetMetaObjectFunction(void);
extern "C" void *beSvSlotXbox_GetMetaObject(void);
extern "C" int beSvSlotXbox_GetVTable(void);
extern "C" void beSvSlotXbox_EnsureRegistered(void);
extern "C" CallbackArray *beSvSlotXbox_Register(void);
extern "C" void beSvSlotXbox_GetMetaObjectFunction(void);
extern "C" void beSvSlotXbox_InitFields(void);
extern "C" void beSvSlotData_EnsureRegistered(void);
extern "C" CallbackArray *beSvSlotData_Register(void);
extern "C" void beSvSlotData_GetMetaObjectFunction(void);
extern "C" void beSvSlotData_InitFields(void);
extern "C" igMetaObject *beSaveMemoryObj_GetOrCreateMetaObject(void);
extern "C" int beSaveMemoryObj_GetVTable(void);
extern "C" void beSaveMemoryObj_EnsureRegistered(void);
extern "C" CallbackArray *beSaveMemoryObj_Register(void);
extern "C" void beSaveMemoryObj_GetMetaObjectFunction(void);
extern "C" void beSaveMemoryObj_InitFields(void);
extern "C" int beSaveDataDeliver_GetVTable(void);
extern "C" CallbackArray *beSaveDataDeliver_Register(void);
extern "C" void beSaveDataDeliver_GetMetaObjectFunction(void);
extern "C" void beSaveDataDeliver_InitFields(void);
extern "C" igMetaObject *beSvDeliver_GetOrCreateMetaObject(void);
extern "C" int beSvDeliver_GetVTable(void);
extern "C" void beSvDeliver_EnsureRegistered(void);
extern "C" CallbackArray *beSvDeliver_Register(void);
extern "C" void beSvDeliver_GetMetaObjectFunction(void);
extern "C" void beSvDeliver_InitFields(void);
extern "C" int beResetNode_GetVTable(void);
extern "C" void beResetNode_EnsureRegistered(void);
extern "C" CallbackArray *beResetNode_Register(void);
extern "C" void beResetNode_GetMetaObjectFunction(void);
extern "C" void beResetNode_InitFields(void);
extern "C" void beResetNode_StaticInitCallback(void);
extern "C" void *bePoint01Info_GetMetaObject(void);
extern "C" int bePoint01Info_GetVTable(void);
extern "C" void bePoint01Info_EnsureRegistered(void);
extern "C" CallbackArray *bePoint01Info_Register(void);
extern "C" void bePoint01Info_GetMetaObjectFunction(void);
extern "C" void bePoint01Info_InitFields(void);
extern "C" igMetaObject *bePoint01_GetOrCreateMetaObject(void);
extern "C" void *bePoint01_GetMetaObject(void);
extern "C" int bePoint01_GetVTable(void);
extern "C" void bePoint01_EnsureRegistered(void);
extern "C" CallbackArray *bePoint01_Register(void);
extern "C" void bePoint01_GetMetaObjectFunction(void);
extern "C" void bePoint01_InitFields(void);
extern "C" void *beParticleCtrl2InfoRam_GetMetaObject(void);
extern "C" int beParticleCtrl2InfoRam_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_ParticleTimer_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beParticleCtrl2InfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beParticleCtrl2InfoRam_Register(void);
extern "C" void beParticleCtrl2InfoRam_GetMetaObjectFunction(void);
extern "C" void beParticleCtrl2InfoRam_InitFields(void);
extern "C" igMetaObject *beParticleCtrl2InfoWork_GetOrCreateMetaObject(void);
extern "C" void *beParticleCtrl2InfoWork_GetMetaObject(void);
extern "C" int beParticleCtrl2InfoWork_GetVTable(void);
extern "C" void beParticleCtrl2InfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beParticleCtrl2InfoWork_Register(void);
extern "C" void beParticleCtrl2InfoWork_GetMetaObjectFunction(void);
extern "C" void beParticleCtrl2InfoWork_InitFields(void);
extern "C" void *beParticleCtrl2Info_GetMetaObject(void);
extern "C" int beParticleCtrl2Info_GetVTable(void);
extern "C" void beParticleCtrl2Info_EnsureRegistered(void);
extern "C" CallbackArray *beParticleCtrl2Info_Register(void);
extern "C" void beParticleCtrl2Info_GetMetaObjectFunction(void);
extern "C" void beParticleCtrl2Info_InitFields(void);
extern "C" igMetaObject *beParticleCtrl2_GetOrCreateMetaObject(void);
extern "C" void *beParticleCtrl2_GetMetaObject(void);
extern "C" int beParticleCtrl2_GetVTable(void);
extern "C" void beParticleCtrl2_EnsureRegistered(void);
extern "C" CallbackArray *beParticleCtrl2_Register(void);
extern "C" void beParticleCtrl2_GetMetaObjectFunction(void);
extern "C" void *bePadManager_GetMetaObject(void);
extern "C" int bePadManager_GetVTable(void);
extern "C" CallbackArray *bePadManager_Register(void);
extern "C" void bePadManager_GetMetaObjectFunction(void);
extern "C" void bePadManager_InitFields(void);
extern "C" igMetaObject *bePadDataList_GetOrCreateMetaObject(void);
extern "C" void *bePadDataList_GetMetaObject(void);
extern "C" int bePadDataList_GetVTable(void);
extern "C" void bePadDataList_EnsureRegistered(void);
extern "C" CallbackArray *bePadDataList_Register(void);
extern "C" void bePadDataList_GetMetaObjectFunction(void);
extern "C" void *bePadData_GetMetaObject(void);
extern "C" int bePadData_GetVTable(void);
extern "C" void bePadData_EnsureRegistered(void);
extern "C" CallbackArray *bePadData_Register(void);
extern "C" void bePadData_GetMetaObjectFunction(void);
extern "C" void bePadData_InitFields(void);
extern "C" int beOptInfo_GetVTable(void);
extern "C" void beOptInfo_EnsureRegistered(void);
extern "C" CallbackArray *igInfo_Register(void);
extern "C" CallbackArray *beOptInfo_Register(void);
extern "C" void beOptInfo_GetMetaObjectFunction(void);
extern "C" void beOptInfo_InitFields(void);
extern "C" igMetaObject *beNumberCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" int beNumberCtrlInfoWork_GetVTable(void);
extern "C" void beNumberCtrlInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNumberCtrlInfoWork_Register(void);
extern "C" void beNumberCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" void beNumberCtrlInfoWork_InitFields(void);
extern "C" int beNumberCtrlInfoRam_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNumVerDataList_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNumberCtrlInfoWork_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" void beNumberCtrlInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beNumberCtrlInfoRam_Register(void);
extern "C" void beNumberCtrlInfoRam_GetMetaObjectFunction(void);
extern "C" void beNumberCtrlInfoRam_InitFields(void);
extern "C" igMetaObject *beNumVerDataList_GetOrCreateMetaObject(void);
extern "C" int beNumVerDataList_GetVTable(void);
extern "C" void beNumVerDataList_EnsureRegistered(void);
extern "C" CallbackArray *beNumVerDataList_Register(void);
extern "C" void beNumVerDataList_GetMetaObjectFunction(void);
extern "C" void *beNumVerData_GetMetaObject(void);
extern "C" int beNumVerData_GetVTable(void);
extern "C" void beNumVerData_EnsureRegistered(void);
extern "C" CallbackArray *beNumVerData_Register(void);
extern "C" void beNumVerData_GetMetaObjectFunction(void);
extern "C" void beNumVerData_InitFields(void);
extern "C" igMetaObject *beNumVerInsideDataList_GetOrCreateMetaObject(void);
extern "C" void *beNumVerInsideDataList_GetMetaObject(void);
extern "C" int beNumVerInsideDataList_GetVTable(void);
extern "C" void beNumVerInsideDataList_EnsureRegistered(void);
extern "C" CallbackArray *beNumVerInsideDataList_Register(void);
extern "C" void beNumVerInsideDataList_GetMetaObjectFunction(void);
extern "C" int beNumVerInsideData_Create(int allocator);
extern "C" void *beNumVerInsideData_GetMetaObject(void);
extern "C" int beNumVerInsideData_GetVTable(void);
extern "C" void beNumVerInsideData_EnsureRegistered(void);
extern "C" CallbackArray *beNumVerInsideData_Register(void);
extern "C" void beNumVerInsideData_GetMetaObjectFunction(void);
extern "C" void beNumVerInsideData_InitFields(void);
extern "C" void *beNumberCtrlInfoList_GetMetaObject(void);
extern "C" int beNumberCtrlInfoList_GetVTable(void);
extern "C" void beNumberCtrlInfoList_EnsureRegistered(void);
extern "C" CallbackArray *beNumberCtrlInfoList_Register(void);
extern "C" void beNumberCtrlInfoList_GetMetaObjectFunction(void);
extern "C" void *beNumberCtrlInfo_GetMetaObject(void);
extern "C" int beNumberCtrlInfo_GetVTable(void);
extern "C" void beNumberCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNumberCtrlInfo_Register(void);
extern "C" void beNumberCtrlInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNumberCtrl_GetOrCreateMetaObject(void);
extern "C" void *beNumberCtrl_GetMetaObject(void);
extern "C" int beNumberCtrl_GetVTable(void);
extern "C" void beNumberCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNumberCtrl_Register(void);
extern "C" void beNumberCtrl_GetMetaObjectFunction(void);
extern "C" int beLoadingNode_GetVTable(void);
extern "C" beNodeAnim *beNodeAnim_Destroy(beNodeAnim *self, long long delete_storage);
extern "C" void beLoadingNode_EnsureRegistered(void);
extern "C" CallbackArray *beLoadingNode_Register(void);
extern "C" void beLoadingNode_GetMetaObject(void);
extern "C" igMetaObject *beNodeAnim_GetPublishedMetaObject(void);
extern "C" void beLoadingNode_InitFields(void);
extern "C" void beLoadingNode_StaticInitCallback(void);
extern "C" int beNodeAnim_GetVTable(void);
extern "C" void beNodeAnim_EnsureRegistered(void);
extern "C" CallbackArray *beNodeAnim_Register(void);
extern "C" void beNodeAnim_GetMetaObject(void);
extern "C" void beNodeAnim_InitFields(void);
extern "C" void beNodeAnim_StaticInitCallback(void);
extern "C" void *beMovieInfo_GetMetaObject(void);
extern "C" int beMovieInfo_GetVTable(void);
extern "C" void beMovieInfo_EnsureRegistered(void);
extern "C" CallbackArray *beMovieInfo_Register(void);
extern "C" void beMovieInfo_GetMetaObjectFunction(void);
extern "C" void *beMovieInfoData_GetMetaObject(void);
extern "C" int beMovieInfoData_GetVTable(void);
extern "C" void beMovieInfoData_EnsureRegistered(void);
extern "C" CallbackArray *beMovieInfoData_Register(void);
extern "C" void beMovieInfoData_GetMetaObjectFunction(void);
extern "C" void beMovieInfoData_InitFields(void);
extern "C" igMetaObject *beMovie_GetOrCreateMetaObject(void);
extern "C" int beMovie_GetVTable(void);
extern "C" void beMovie_EnsureRegistered(void);
extern "C" CallbackArray *beMovie_Register(void);
extern "C" void beMovie_GetMetaObjectFunction(void);
extern "C" void beMovie_InitFields(void);
extern "C" igMetaObject *beModelCtrlSubCom_GetOrCreateMetaObject(void);
extern "C" int beModelCtrlSubCom_GetVTable(void);
extern "C" void beModelCtrlSubCom_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlSubCom_Register(void);
extern "C" void beModelCtrlSubCom_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSubCom_InitFields(void);
extern "C" int beModelCtrlSCSound_GetVTable(void);
extern "C" void beModelCtrlSCSound_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlSCSound_Register(void);
extern "C" void beModelCtrlSCSound_GetMetaObjectFunction(void);
extern "C" igMetaObject *beModelCtrlSubComBase_GetPublishedMetaObject(void);
extern "C" void beModelCtrlSCSound_InitFields(void);
extern "C" int beModelCtrlSCHitBox_GetVTable(void);
extern "C" void beModelCtrlSCHitBox_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlSCHitBox_Register(void);
extern "C" void beModelCtrlSCHitBox_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSCHitBox_InitFields(void);
extern "C" void *beModelCtrlSCEffect_GetMetaObject(void);
extern "C" int beModelCtrlSCEffect_GetVTable(void);
extern "C" void beModelCtrlSCEffect_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlSCEffect_Register(void);
extern "C" void beModelCtrlSCEffect_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSCEffect_InitFields(void);
extern "C" void *beModelCtrlSubComBase_GetMetaObject(void);
extern "C" void beModelCtrlSubComBase_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlSubComBase_Register(void);
extern "C" void beModelCtrlSubComBase_GetMetaObjectFunction(void);
extern "C" void beModelCtrlSubComBase_InitFields(void);
extern "C" igMetaObject *beModelCtrlNode2_GetOrCreateMetaObject(void);
extern "C" int beModelCtrlNode2_GetVTable(void);
extern "C" void beModelCtrlNode2_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlNode2_Register(void);
extern "C" void beModelCtrlNode2_GetMetaObject(void);
extern "C" void beModelCtrlNode2_InitFields(void);
extern "C" void beModelCtrlNode2_StaticInitCallback(void);
extern "C" igMetaObject *beModelCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoWork_GetMetaObject(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlSubCom_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoHitBody_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_igGroup_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoRideOn_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlMoveObjectList_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoDataTrc_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlNode2_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoAI_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlData_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beDataObjInt_Construct(igSmartPointer<igObject> *self);
extern "C" void beModelCtrlInfoWork_EnsureRegistered(void);
extern "C" int beModelCtrlInfoWork_GetVTable(void);
extern "C" void beModelCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoWork_InitFields(void);
extern "C" void *beModelCtrlInfoRideOn4_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn4_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn4_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoRideOn4_Register(void);
extern "C" void beModelCtrlInfoRideOn4_GetMetaObjectFunction(void);
extern "C" igMetaObject *beModelCtrlInfoRideOn_GetPublishedMetaObject(void);
extern "C" void beModelCtrlInfoRideOn4_InitFields(void);
extern "C" void *beModelCtrlInfoRideOn3_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn3_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn3_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoRideOn3_Register(void);
extern "C" void beModelCtrlInfoRideOn3_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRideOn3_InitFields(void);
extern "C" void *beModelCtrlInfoRideOn2_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn2_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn2_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoRideOn2_Register(void);
extern "C" void beModelCtrlInfoRideOn2_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRideOn2_InitFields(void);
extern "C" igMetaObject *beModelCtrlInfoRideOn_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoRideOn_GetMetaObject(void);
extern "C" int beModelCtrlInfoRideOn_GetVTable(void);
extern "C" void beModelCtrlInfoRideOn_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoRideOn_Register(void);
extern "C" void beModelCtrlInfoRideOn_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRideOn_InitFields(void);
extern "C" igMetaObject *beModelCtrlInfoAI_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoAI_GetMetaObject(void);
extern "C" int beModelCtrlInfoAI_GetVTable(void);
extern "C" void beModelCtrlInfoAI_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoAI_Register(void);
extern "C" void beModelCtrlInfoAI_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoAI_InitFields(void);
extern "C" igMetaObject *beModelCtrlInfoHitBody_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoHitBody_GetMetaObject(void);
extern "C" int beModelCtrlInfoHitBody_GetVTable(void);
extern "C" void beModelCtrlInfoHitBody_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoHitBody_Register(void);
extern "C" void beModelCtrlInfoHitBody_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoHitBody_InitFields(void);
extern "C" igMetaObject *beModelCtrlMoveObjectList_GetOrCreateMetaObject(void);
extern "C" int beModelCtrlMoveObjectList_GetVTable(void);
extern "C" void beModelCtrlMoveObjectList_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlMoveObjectList_Register(void);
extern "C" void beModelCtrlMoveObjectList_GetMetaObjectFunction(void);
extern "C" int beModelCtrlMoveObject_GetVTable(void);
extern "C" void beModelCtrlMoveObject_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlMoveObject_Register(void);
extern "C" void beModelCtrlMoveObject_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMoveObject_InitFields(void);
extern "C" int beModelCtrlInfoList_GetVTable(void);
extern "C" void beModelCtrlInfoList_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoList_Register(void);
extern "C" void beModelCtrlInfoList_GetMetaObjectFunction(void);
extern "C" int beModelCtrlInfo_GetVTable(void);
extern "C" void beModelCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfo_Register(void);
extern "C" void beModelCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfo_InitFields(void);
extern "C" void *beModelCtrlInfoRamData_GetMetaObject(void);
extern "C" int beModelCtrlInfoRamData_GetVTable(void);
extern "C" void beModelCtrlInfoRamData_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoRamData_Register(void);
extern "C" void beModelCtrlInfoRamData_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoRamData_InitFields(void);
extern "C" igMetaObject *beModelCtrlInfoDataTrc_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlInfoDataTrc_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataTrc_GetVTable(void);
extern "C" void beModelCtrlInfoDataTrc_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoDataTrc_Register(void);
extern "C" void beModelCtrlInfoDataTrc_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataTrc_InitFields(void);
extern "C" void *beModelCtrlInfoDataSeq_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataSeq_GetVTable(void);
extern "C" void beModelCtrlInfoDataSeq_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoDataSeq_Register(void);
extern "C" void beModelCtrlInfoDataSeq_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataSeq_InitFields(void);
extern "C" void *beModelCtrlInfoDataHit_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataHit_GetVTable(void);
extern "C" void beModelCtrlInfoDataHit_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoDataHit_Register(void);
extern "C" void beModelCtrlInfoDataHit_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataHit_InitFields(void);
extern "C" void *beModelCtrlInfoDataAIH_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataAIH_GetVTable(void);
extern "C" void beModelCtrlInfoDataAIH_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoDataAIH_Register(void);
extern "C" void beModelCtrlInfoDataAIH_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataAIH_InitFields(void);
extern "C" void *beModelCtrlInfoDataAIM_GetMetaObject(void);
extern "C" int beModelCtrlInfoDataAIM_GetVTable(void);
extern "C" void beModelCtrlInfoDataAIM_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlInfoDataAIM_Register(void);
extern "C" void beModelCtrlInfoDataAIM_GetMetaObjectFunction(void);
extern "C" void beModelCtrlInfoDataAIM_InitFields(void);
extern "C" igMetaObject *beModelCtrlAIMapList_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlAIMapList_GetMetaObject(void);
extern "C" int beModelCtrlAIMapList_GetVTable(void);
extern "C" void beModelCtrlAIMapList_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlAIMapList_Register(void);
extern "C" void beModelCtrlAIMapList_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlAIMap_GetMetaObject(void);
extern "C" int beModelCtrlAIMap_GetVTable(void);
extern "C" void beModelCtrlAIMap_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlAIMap_Register(void);
extern "C" void beModelCtrlAIMap_GetMetaObjectFunction(void);
extern "C" void beModelCtrlAIMap_InitFields(void);
extern "C" igMetaObject *beModelCtrlAIDataList_GetOrCreateMetaObject(void);
extern "C" void *beModelCtrlAIDataList_GetMetaObject(void);
extern "C" int beModelCtrlAIDataList_GetVTable(void);
extern "C" void beModelCtrlAIDataList_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlAIDataList_Register(void);
extern "C" void beModelCtrlAIDataList_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlAIData_GetMetaObject(void);
extern "C" int beModelCtrlAIData_GetVTable(void);
extern "C" void beModelCtrlAIData_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlAIData_Register(void);
extern "C" void beModelCtrlAIData_GetMetaObjectFunction(void);
extern "C" void beModelCtrlAIData_InitFields(void);
extern "C" int beModelCtrlHITBOX_GetVTable(void);
extern "C" void beModelCtrlHITBOX_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlHITBOX_Register(void);
extern "C" void beModelCtrlHITBOX_GetMetaObjectFunction(void);
extern "C" void beModelCtrlHITBOX_InitFields(void);
extern "C" int beModelCtrlMUTEKI_GetVTable(void);
extern "C" void beModelCtrlMUTEKI_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlMUTEKI_Register(void);
extern "C" void beModelCtrlMUTEKI_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMUTEKI_InitFields(void);
extern "C" int beModelCtrlAIMAP_GetVTable(void);
extern "C" void beModelCtrlAIMAP_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlAIMAP_Register(void);
extern "C" void beModelCtrlAIMAP_GetMetaObjectFunction(void);
extern "C" int beModelCtrlWCHECK_GetVTable(void);
extern "C" void beModelCtrlWCHECK_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlWCHECK_Register(void);
extern "C" void beModelCtrlWCHECK_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlPDMOVE_GetMetaObject(void);
extern "C" int beModelCtrlPDMOVE_GetVTable(void);
extern "C" void beModelCtrlPDMOVE_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlPDMOVE_Register(void);
extern "C" void beModelCtrlPDMOVE_GetMetaObjectFunction(void);
extern "C" void beModelCtrlPDMOVE_InitFields(void);
extern "C" void *beModelCtrlMOVERL_GetMetaObject(void);
extern "C" int beModelCtrlMOVERL_GetVTable(void);
extern "C" void beModelCtrlMOVERL_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlMOVERL_Register(void);
extern "C" void beModelCtrlMOVERL_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMOVERL_InitFields(void);
extern "C" void *beModelCtrlMOVEEX_GetMetaObject(void);
extern "C" int beModelCtrlMOVEEX_GetVTable(void);
extern "C" void beModelCtrlMOVEEX_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlMOVEEX_Register(void);
extern "C" void beModelCtrlMOVEEX_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMOVEEX_InitFields(void);
extern "C" void *beModelCtrlMOVE_GetMetaObject(void);
extern "C" int beModelCtrlMOVE_GetVTable(void);
extern "C" void beModelCtrlMOVE_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlMOVE_Register(void);
extern "C" void beModelCtrlMOVE_GetMetaObjectFunction(void);
extern "C" void beModelCtrlMOVE_InitFields(void);
extern "C" void *beModelCtrlMSGBOX_GetMetaObject(void);
extern "C" int beModelCtrlMSGBOX_GetVTable(void);
extern "C" void beModelCtrlMSGBOX_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlMSGBOX_Register(void);
extern "C" void beModelCtrlMSGBOX_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlCTRL_GetMetaObject(void);
extern "C" int beModelCtrlCTRL_GetVTable(void);
extern "C" void beModelCtrlCTRL_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlCTRL_Register(void);
extern "C" void beModelCtrlCTRL_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlJUMP_GetMetaObject(void);
extern "C" int beModelCtrlJUMP_GetVTable(void);
extern "C" void beModelCtrlJUMP_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlJUMP_Register(void);
extern "C" void beModelCtrlJUMP_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlACTION_GetMetaObject(void);
extern "C" int beModelCtrlACTION_GetVTable(void);
extern "C" void beModelCtrlACTION_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlACTION_Register(void);
extern "C" void beModelCtrlACTION_GetMetaObjectFunction(void);
extern "C" void *beModelCtrlLABELCTRL_GetMetaObject(void);
extern "C" int beModelCtrlLABELCTRL_GetVTable(void);
extern "C" void beModelCtrlLABELCTRL_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlLABELCTRL_Register(void);
extern "C" void beModelCtrlLABELCTRL_GetMetaObjectFunction(void);
extern "C" void beModelCtrlLABELCTRL_InitFields(void);
extern "C" void *beModelCtrlLABEL_GetMetaObject(void);
extern "C" int beModelCtrlLABEL_GetVTable(void);
extern "C" void beModelCtrlLABEL_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlLABEL_Register(void);
extern "C" void beModelCtrlLABEL_GetMetaObjectFunction(void);
extern "C" int beModelCtrlLUACALL_GetVTable(void);
extern "C" void beModelCtrlLUACALL_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlLUACALL_Register(void);
extern "C" void beModelCtrlLUACALL_GetMetaObjectFunction(void);
extern "C" void beModelCtrlLUACALL_InitFields(void);
extern "C" int beModelCtrlDataList_GetVTable(void);
extern "C" void beModelCtrlDataList_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlDataList_Register(void);
extern "C" void beModelCtrlDataList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beModelCtrlData_GetOrCreateMetaObject(void);
extern "C" int beModelCtrlData_GetVTable(void);
extern "C" void beModelCtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beModelCtrlData_Register(void);
extern "C" void beModelCtrlData_GetMetaObjectFunction(void);
extern "C" void beModelCtrlData_InitFields(void);
extern "C" void beModelCtrl_EnsureRegistered(void);
extern "C" void beModelCtrl_GetMetaObjectFunction(void);
extern "C" void beModelCtrl_InitFields(void);
extern "C" igMetaObject *beMeterCtrlNode_GetOrCreateMetaObject(void);
extern "C" int beMeterCtrlNode_GetVTable(void);
extern "C" void beMeterCtrlNode_EnsureRegistered(void);
extern "C" CallbackArray *beMeterCtrlNode_Register(void);
extern "C" void beMeterCtrlNode_GetMetaObject(void);
extern "C" int igLongList_GetOrCreateMetaObject(void);
extern "C" void beMeterCtrlNode_InitFields(void);
extern "C" void beMeterCtrlNode_StaticInitCallback(void);
extern "C" void *beMeterCtrlInfoList_GetMetaObject(void);
extern "C" int beMeterCtrlInfoList_GetVTable(void);
extern "C" void beMeterCtrlInfoList_EnsureRegistered(void);
extern "C" CallbackArray *beMeterCtrlInfoList_Register(void);
extern "C" void beMeterCtrlInfoList_GetMetaObjectFunction(void);
extern "C" void *beMeterCtrlInfo_GetMetaObject(void);
extern "C" int beMeterCtrlInfo_GetVTable(void);
extern "C" void beMeterCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beMeterCtrlInfo_Register(void);
extern "C" void beMeterCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beMeterCtrlInfo_InitFields(void);
extern "C" void *beMeterCtrlOneData_GetMetaObject(void);
extern "C" int beMeterCtrlOneData_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMeterCtrlNode_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" void beMeterCtrlOneData_EnsureRegistered(void);
extern "C" CallbackArray *beMeterCtrlOneData_Register(void);
extern "C" void beMeterCtrlOneData_GetMetaObjectFunction(void);
extern "C" void beMeterCtrlOneData_InitFields(void);
extern "C" igMetaObject *beMeterCtrl_GetOrCreateMetaObject(void);
extern "C" void *beMeterCtrl_GetMetaObject(void);
extern "C" int beMeterCtrl_GetVTable(void);
extern "C" void beMeterCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beMeterCtrl_Register(void);
extern "C" void beMeterCtrl_GetMetaObjectFunction(void);
extern "C" void *beMessenger_GetMetaObject(void);
extern "C" int beMessenger_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMessengerGroupList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMessengerWorkList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMessengerArgDataList_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" CallbackArray *beMessenger_Register(void);
extern "C" void beMessenger_GetMetaObjectFunction(void);
extern "C" void beMessenger_InitFields(void);
extern "C" igMetaObject *beMessengerWorkList_GetOrCreateMetaObject(void);
extern "C" void *beMessengerWorkList_GetMetaObject(void);
extern "C" int beMessengerWorkList_GetVTable(void);
extern "C" void beMessengerWorkList_EnsureRegistered(void);
extern "C" CallbackArray *beMessengerWorkList_Register(void);
extern "C" void beMessengerWorkList_GetMetaObjectFunction(void);
extern "C" void beMessengerWork_EnsureRegistered();
extern "C" void beMessengerGroup_EnsureRegistered();
extern "C" void beMessengerDelay_EnsureRegistered();
extern "C" void beMessengerArgData_EnsureRegistered();
extern "C" void *beMessengerWork_GetMetaObject(void);
extern "C" int beMessengerWork_GetVTable(void);
extern "C" CallbackArray *beMessengerWork_Register(void);
extern "C" void beMessengerWork_GetMetaObjectFunction(void);
extern "C" void beMessengerWork_InitFields(void);
extern "C" igMetaObject *beMessengerGroupList_GetOrCreateMetaObject(void);
extern "C" void *beMessengerGroupList_GetMetaObject(void);
extern "C" int beMessengerGroupList_GetVTable(void);
extern "C" void beMessengerGroupList_EnsureRegistered(void);
extern "C" CallbackArray *beMessengerGroupList_Register(void);
extern "C" void beMessengerGroupList_GetMetaObjectFunction(void);
extern "C" void *beMessengerGroup_GetMetaObject(void);
extern "C" int beMessengerGroup_GetVTable(void);
extern "C" CallbackArray *beMessengerGroup_Register(void);
extern "C" void beMessengerGroup_GetMetaObjectFunction(void);
extern "C" void beMessengerGroup_InitFields(void);
extern "C" igMetaObject *beMessengerDelayList_GetOrCreateMetaObject(void);
extern "C" int beMessengerDelayList_GetVTable(void);
extern "C" void beMessengerDelayList_EnsureRegistered(void);
extern "C" CallbackArray *beMessengerDelayList_Register(void);
extern "C" void beMessengerDelayList_GetMetaObjectFunction(void);
extern "C" int beMessengerDelay_GetVTable(void);
extern "C" CallbackArray *beMessengerDelay_Register(void);
extern "C" void beMessengerDelay_GetMetaObjectFunction(void);
extern "C" void beMessengerDelay_InitFields(void);
extern "C" igMetaObject *beMessengerArgDataList_GetOrCreateMetaObject(void);
extern "C" int beMessengerArgDataList_GetVTable(void);
extern "C" void beMessengerArgDataList_EnsureRegistered(void);
extern "C" CallbackArray *beMessengerArgDataList_Register(void);
extern "C" void beMessengerArgDataList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beMessengerArgData_GetOrCreateMetaObject(void);
extern "C" int beMessengerArgData_GetVTable(void);
extern "C" CallbackArray *beMessengerArgData_Register(void);
extern "C" void beMessengerArgData_GetMetaObjectFunction(void);
extern "C" void beMessengerArgData_InitFields(void);
extern "C" igMetaObject *beMemory_GetOrCreateMetaObject(void);
extern "C" void *beMemory_GetMetaObject(void);
extern "C" int beMemory_GetVTable(void);
extern "C" void beMemory_EnsureRegistered(void);
extern "C" CallbackArray *beMemory_Register(void);
extern "C" void beMemory_GetMetaObjectFunction(void);
extern "C" void beMemory_InitFields(void);
extern "C" igMetaObject *beMatCtrlInfoWork_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlInfoWork_GetMetaObject(void);
extern "C" int beMatCtrlInfoWork_GetVTable(void);
extern "C" void beMatCtrlInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrlInfoWork_Register(void);
extern "C" void beMatCtrlInfoWork_GetMetaObjectFunction(void);
extern "C" int igIntListList_GetOrCreateMetaObject(void);
extern "C" void beMatCtrlInfoWork_InitFields(void);
extern "C" void *beMatCtrlInfoRam_GetMetaObject(void);
extern "C" int beMatCtrlInfoRam_GetVTable(void);
extern "C" void beMatCtrlInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrlInfoRam_Register(void);
extern "C" void beMatCtrlInfoRam_GetMetaObjectFunction(void);
extern "C" void beMatCtrlInfoRam_InitFields(void);
extern "C" void *beMatCtrlInfo_GetMetaObject(void);
extern "C" int beMatCtrlInfo_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMatCtrlDataList_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMatCtrlSearchList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beMatCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrlInfo_Register(void);
extern "C" void beMatCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beMatCtrlInfo_InitFields(void);
extern "C" igMetaObject *beMatCtrlSearchList_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlSearchList_GetMetaObject(void);
extern "C" int beMatCtrlSearchList_GetVTable(void);
extern "C" void beMatCtrlSearchList_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrlSearchList_Register(void);
extern "C" void beMatCtrlSearchList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beMatCtrlSearch_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlSearch_GetMetaObject(void);
extern "C" int beMatCtrlSearch_GetVTable(void);
extern "C" void beMatCtrlSearch_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrlSearch_Register(void);
extern "C" void beMatCtrlSearch_GetMetaObjectFunction(void);
extern "C" void beMatCtrlSearch_InitFields(void);
extern "C" igMetaObject *beMatCtrlDataList_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrlDataList_GetMetaObject(void);
extern "C" int beMatCtrlDataList_GetVTable(void);
extern "C" void beMatCtrlDataList_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrlDataList_Register(void);
extern "C" void beMatCtrlDataList_GetMetaObjectFunction(void);
extern "C" void *beMatCtrlData_GetMetaObject(void);
extern "C" int beMatCtrlData_GetVTable(void);
extern "C" void beMatCtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrlData_Register(void);
extern "C" void beMatCtrlData_GetMetaObjectFunction(void);
extern "C" void beMatCtrlData_InitFields(void);
extern "C" igMetaObject *beMatCtrl_GetOrCreateMetaObject(void);
extern "C" void *beMatCtrl_GetMetaObject(void);
extern "C" int beMatCtrl_GetVTable(void);
extern "C" void beMatCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beMatCtrl_Register(void);
extern "C" void beMatCtrl_GetMetaObjectFunction(void);
extern "C" void beMatCtrl_InitFields(void);
extern "C" igMetaObject *beLuaState_GetOrCreateMetaObject(void);
extern "C" void *beLuaState_GetMetaObject(void);
extern "C" int beLuaState_GetVTable(void);
extern "C" void beLuaState_EnsureRegistered(void);
extern "C" CallbackArray *beLuaState_Register(void);
extern "C" void beLuaState_GetMetaObjectFunction(void);
extern "C" igMetaObject *igLuaState_GetPublishedMetaObject(void);
extern "C" void beLuaState_InitFields(void);
extern "C" int beLuaInfo_GetVTable(void);
extern "C" void beLuaInfo_EnsureRegistered(void);
extern "C" CallbackArray *beLuaInfo_Register(void);
extern "C" void beLuaInfo_GetMetaObjectFunction(void);
extern "C" void beLuaInfo_InitFields(void);
extern "C" igMetaObject *beLuaDataList_GetOrCreateMetaObject(void);
extern "C" int beLuaDataList_GetVTable(void);
extern "C" void beLuaDataList_EnsureRegistered(void);
extern "C" CallbackArray *beLuaDataList_Register(void);
extern "C" void beLuaDataList_GetMetaObjectFunction(void);
extern "C" int beLuaData_GetVTable(void);
extern "C" void beLuaData_EnsureRegistered(void);
extern "C" CallbackArray *beLuaData_Register(void);
extern "C" void beLuaData_GetMetaObjectFunction(void);
extern "C" void beLuaData_InitFields(void);
extern "C" int beLuaDataObjectist_GetVTable(void);
extern "C" void beLuaDataObjectist_EnsureRegistered(void);
extern "C" CallbackArray *beLuaDataObjectist_Register(void);
extern "C" void beLuaDataObjectist_GetMetaObjectFunction(void);
extern "C" igMetaObject *beLuaDataObject_GetOrCreateMetaObject(void);
extern "C" void *beLuaDataObject_GetMetaObject(void);
extern "C" int beLuaDataObject_GetVTable(void);
extern "C" void beLuaDataObject_EnsureRegistered(void);
extern "C" CallbackArray *beLuaDataObject_Register(void);
extern "C" void beLuaDataObject_GetMetaObjectFunction(void);
extern "C" void beLuaDataObject_InitFields(void);
extern "C" void *beLua_GetMetaObject(void);
extern "C" int beLua_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beLuaState_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" CallbackArray *beLua_Register(void);
extern "C" void beLua_GetMetaObjectFunction(void);
extern "C" void beLua_InitFields(void);
extern "C" igMetaObject *igLightSetList_GetOrCreateMetaObject(void);
extern "C" void *igLightSetList_GetMetaObject(void);
extern "C" int igLightSetList_GetVTable(void);
extern "C" void igLightSetList_EnsureRegistered(void);
extern "C" CallbackArray *igLightSetList_Register(void);
extern "C" void igLightSetList_GetMetaObjectFunction(void);
extern "C" void *beLightCtrlInfo_GetMetaObject(void);
extern "C" int beLightCtrlInfo_GetVTable(void);
extern "C" void beLightCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beLightCtrlInfo_Register(void);
extern "C" void beLightCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beLightCtrlInfo_InitFields(void);
extern "C" igMetaObject *beLightCtrl_GetOrCreateMetaObject(void);
extern "C" void *beLightCtrl_GetMetaObject(void);
extern "C" int beLightCtrl_GetVTable(void);
extern "C" void beLightCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beLightCtrl_Register(void);
extern "C" void beLightCtrl_GetMetaObjectFunction(void);
extern "C" void *beLayerInfoRam_GetMetaObject(void);
extern "C" int beLayerInfoRam_GetVTable(void);
extern "C" void beLayerInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beLayerInfoRam_Register(void);
extern "C" void beLayerInfoRam_GetMetaObjectFunction(void);
extern "C" void *beLayerInfo_GetMetaObject(void);
extern "C" int beLayerInfo_GetVTable(void);
extern "C" void beLayerInfo_EnsureRegistered(void);
extern "C" CallbackArray *beLayerInfo_Register(void);
extern "C" void beLayerInfo_GetMetaObjectFunction(void);
extern "C" void beLayerInfo_InitFields(void);
extern "C" igMetaObject *beLayerGroupList_GetOrCreateMetaObject(void);
extern "C" void *beLayerGroupList_GetMetaObject(void);
extern "C" int beLayerGroupList_GetVTable(void);
extern "C" void beLayerGroupList_EnsureRegistered(void);
extern "C" CallbackArray *beLayerGroupList_Register(void);
extern "C" void beLayerGroupList_GetMetaObjectFunction(void);
extern "C" void *beLayerGroup_GetMetaObject(void);
extern "C" int beLayerGroup_GetVTable(void);
extern "C" void beLayerGroup_EnsureRegistered(void);
extern "C" CallbackArray *beLayerGroup_Register(void);
extern "C" void beLayerGroup_GetMetaObjectFunction(void);
extern "C" igMetaObject *beLayerCtl_GetOrCreateMetaObject(void);
extern "C" void *beLayerCtl_GetMetaObject(void);
extern "C" int beLayerCtl_GetVTable(void);
extern "C" void beLayerCtl_EnsureRegistered(void);
extern "C" CallbackArray *beLayerCtl_Register(void);
extern "C" void beLayerCtl_GetMetaObjectFunction(void);
extern "C" void beLayerCtl_InitFields(void);
extern "C" int beLOA_GetVTable(void);
extern "C" void beLOA_EnsureRegistered(void);
extern "C" CallbackArray *beLOA_Register(void);
extern "C" void beLOA_GetMetaObjectFunction(void);
extern "C" void beLOA_InitFields(void);
extern "C" void beLOA_StaticInitCallback(void);
extern "C" igMetaObject *beKeyboardReceiver_GetOrCreateMetaObject(void);
extern "C" int beKeyboardReceiver_GetVTable(void);
extern "C" void beKeyboardReceiver_EnsureRegistered(void);
extern "C" CallbackArray *beKeyboardReceiver_Register(void);
extern "C" void beKeyboardReceiver_GetMetaObjectFunction(void);
extern "C" void beKeyboardReceiver_InitFields(void);
extern "C" int beHitLandModelInfoRam_GetVTable(void);
extern "C" void beHitLandModelInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandModelInfoRam_Register(void);
extern "C" void beHitLandModelInfoRam_GetMetaObjectFunction(void);
extern "C" int beHitLandModelInfo_GetVTable(void);
extern "C" void beHitLandModelInfo_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandModelInfo_Register(void);
extern "C" void beHitLandModelInfo_GetMetaObjectFunction(void);
extern "C" void beHitLandModelInfo_InitFields(void);
extern "C" igMetaObject *beHitLandModel_GetOrCreateMetaObject(void);
extern "C" void *beHitLandModel_GetMetaObject(void);
extern "C" int beHitLandModel_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beHitLandModelOrder_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beHitLandModelTraversal_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beHitLandModel_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandModel_Register(void);
extern "C" void beHitLandModel_GetMetaObjectFunction(void);
extern "C" void beHitLandModel_InitFields(void);
extern "C" igMetaObject *beHitLandModelTraversal_GetOrCreateMetaObject(void);
extern "C" void *beHitLandModelTraversal_GetMetaObject(void);
extern "C" int beHitLandModelTraversal_GetVTable(void);
extern "C" void beHitLandModelTraversal_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandModelTraversal_Register(void);
extern "C" void beHitLandModelTraversal_GetMetaObjectFunction(void);
extern "C" igMetaObject *igIntersectTraversal_GetPublishedMetaObject(void);
extern "C" void beHitLandModelTraversal_InitFields(void);
extern "C" igMetaObject *beHitLandModelOrder_GetOrCreateMetaObject(void);
extern "C" void *beHitLandModelOrder_GetMetaObject(void);
extern "C" int beHitLandModelOrder_GetVTable(void);
extern "C" void beHitLandModelOrder_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandModelOrder_Register(void);
extern "C" void beHitLandModelOrder_GetMetaObjectFunction(void);
extern "C" void beHitLandModelOrder_InitFields(void);
extern "C" igMetaObject *beHitLandResultDataList_GetOrCreateMetaObject(void);
extern "C" void *beHitLandResultDataList_GetMetaObject(void);
extern "C" int beHitLandResultDataList_GetVTable(void);
extern "C" void beHitLandResultDataList_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandResultDataList_Register(void);
extern "C" void beHitLandResultDataList_GetMetaObjectFunction(void);
extern "C" void *beHitLandResultData_GetMetaObject(void);
extern "C" int beHitLandResultData_GetVTable(void);
extern "C" void beHitLandResultData_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandResultData_Register(void);
extern "C" void beHitLandResultData_GetMetaObjectFunction(void);
extern "C" void beHitLandResultData_InitFields(void);
extern "C" void *beHitLandDelivInfoRam_GetMetaObject(void);
extern "C" int beHitLandDelivInfoRam_GetVTable(void);
extern "C" void beHitLandDelivInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandDelivInfoRam_Register(void);
extern "C" void beHitLandDelivInfoRam_GetMetaObjectFunction(void);
extern "C" void beHitLandDelivInfoRam_InitFields(void);
extern "C" void *beHitLandDelivInfo_GetMetaObject(void);
extern "C" int beHitLandDelivInfo_GetVTable(void);
extern "C" void beHitLandDelivInfo_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandDelivInfo_Register(void);
extern "C" void beHitLandDelivInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *beHitLandDeliv_GetOrCreateMetaObject(void);
extern "C" void *beHitLandDeliv_GetMetaObject(void);
extern "C" int beHitLandDeliv_GetVTable(void);
extern "C" void beHitLandDeliv_EnsureRegistered(void);
extern "C" CallbackArray *beHitLandDeliv_Register(void);
extern "C" void beHitLandDeliv_GetMetaObjectFunction(void);
extern "C" igMetaObject *beGroupKeepList_GetOrCreateMetaObject(void);
extern "C" void *beGroupKeepList_GetMetaObject(void);
extern "C" int beGroupKeepList_GetVTable(void);
extern "C" void beGroupKeepList_EnsureRegistered(void);
extern "C" CallbackArray *beGroupKeepList_Register(void);
extern "C" void beGroupKeepList_GetMetaObjectFunction(void);
extern "C" void *beGroupKeep_GetMetaObject(void);
extern "C" int beGroupKeep_GetVTable(void);
extern "C" void beGroupKeep_EnsureRegistered(void);
extern "C" CallbackArray *beGroupKeep_Register(void);
extern "C" void beGroupKeep_GetMetaObjectFunction(void);
extern "C" igMetaObject *beGeneraterInfoWork_GetOrCreateMetaObject(void);
extern "C" int beGeneraterInfoWork_GetVTable(void);
extern "C" void beGeneraterInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterInfoWork_Register(void);
extern "C" void beGeneraterInfoWork_GetMetaObjectFunction(void);
extern "C" void beGeneraterInfoWork_InitFields(void);
extern "C" int beGeneraterInfoRam_GetVTable(void);
extern "C" void beGeneraterInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterInfoRam_Register(void);
extern "C" void beGeneraterInfoRam_GetMetaObjectFunction(void);
extern "C" void beGeneraterInfoRam_InitFields(void);
extern "C" int beGeneraterInfo_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beGeneraterDataList_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" void beGeneraterInfo_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterInfo_Register(void);
extern "C" void beGeneraterInfo_GetMetaObjectFunction(void);
extern "C" void beGeneraterInfo_InitFields(void);
extern "C" igMetaObject *beGeneraterDataList_GetOrCreateMetaObject(void);
extern "C" int beGeneraterDataList_GetVTable(void);
extern "C" void beGeneraterDataList_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterDataList_Register(void);
extern "C" void beGeneraterDataList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterData_GetMetaObject(void);
extern "C" int beGeneraterData_GetVTable(void);
extern "C" void beGeneraterData_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterData_Register(void);
extern "C" void beGeneraterData_GetMetaObjectFunction(void);
extern "C" void beGeneraterData_InitFields(void);
extern "C" igMetaObject *beGeneraterPlayerDataList_GetOrCreateMetaObject(void);
extern "C" void *beGeneraterPlayerDataList_GetMetaObject(void);
extern "C" int beGeneraterPlayerDataList_GetVTable(void);
extern "C" void beGeneraterPlayerDataList_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterPlayerDataList_Register(void);
extern "C" void beGeneraterPlayerDataList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterPlayerData_GetMetaObject(void);
extern "C" int beGeneraterPlayerData_GetVTable(void);
extern "C" void beGeneraterPlayerData_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterPlayerData_Register(void);
extern "C" void beGeneraterPlayerData_GetMetaObjectFunction(void);
extern "C" void beGeneraterPlayerData_InitFields(void);
extern "C" igMetaObject *beGeneraterItemDataList_GetOrCreateMetaObject(void);
extern "C" void *beGeneraterItemDataList_GetMetaObject(void);
extern "C" int beGeneraterItemDataList_GetVTable(void);
extern "C" void beGeneraterItemDataList_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterItemDataList_Register(void);
extern "C" void beGeneraterItemDataList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterItemData_GetMetaObject(void);
extern "C" int beGeneraterItemData_GetVTable(void);
extern "C" void beGeneraterItemData_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterItemData_Register(void);
extern "C" void beGeneraterItemData_GetMetaObjectFunction(void);
extern "C" void beGeneraterItemData_InitFields(void);
extern "C" igMetaObject *beGeneraterItemDataOneList_GetOrCreateMetaObject(void);
extern "C" void *beGeneraterItemDataOneList_GetMetaObject(void);
extern "C" int beGeneraterItemDataOneList_GetVTable(void);
extern "C" void beGeneraterItemDataOneList_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterItemDataOneList_Register(void);
extern "C" void beGeneraterItemDataOneList_GetMetaObjectFunction(void);
extern "C" void *beGeneraterItemDataOne_GetMetaObject(void);
extern "C" int beGeneraterItemDataOne_GetVTable(void);
extern "C" void beGeneraterItemDataOne_EnsureRegistered(void);
extern "C" CallbackArray *beGeneraterItemDataOne_Register(void);
extern "C" void beGeneraterItemDataOne_GetMetaObjectFunction(void);
extern "C" void beGeneraterItemDataOne_InitFields(void);
extern "C" igMetaObject *beGenerater_GetOrCreateMetaObject(void);
extern "C" void *beGenerater_GetMetaObject(void);
extern "C" int beGenerater_GetVTable(void);
extern "C" void beGenerater_EnsureRegistered(void);
extern "C" CallbackArray *beGenerater_Register(void);
extern "C" void beGenerater_GetMetaObjectFunction(void);
extern "C" void beGenerater_InitFields(void);
extern "C" void *beFontInfo_GetMetaObject(void);
extern "C" int beFontInfo_GetVTable(void);
extern "C" void beFontInfo_EnsureRegistered(void);
extern "C" CallbackArray *beFontInfo_Register(void);
extern "C" void beFontInfo_GetMetaObjectFunction(void);
extern "C" void beFontInfo_InitFields(void);
extern "C" void *beFontInfoData_GetMetaObject(void);
extern "C" int beFontInfoData_GetVTable(void);
extern "C" void beFontInfoData_EnsureRegistered(void);
extern "C" CallbackArray *beFontInfoData_Register(void);
extern "C" void beFontInfoData_GetMetaObjectFunction(void);
extern "C" void beFontInfoData_InitFields(void);
extern "C" igMetaObject *beUnicodeObjList_GetOrCreateMetaObject(void);
extern "C" int beUnicodeObjList_GetVTable(void);
extern "C" void beUnicodeObjList_EnsureRegistered(void);
extern "C" CallbackArray *beUnicodeObjList_Register(void);
extern "C" void beUnicodeObjList_GetMetaObjectFunction(void);
extern "C" int beUnicodeObj_GetVTable(void);
extern "C" void beUnicodeObj_EnsureRegistered(void);
extern "C" CallbackArray *beUnicodeObj_Register(void);
extern "C" void beUnicodeObj_GetMetaObjectFunction(void);
extern "C" int igUnsignedShortMetaField_GetDefaultDescriptor(void);
extern "C" void beUnicodeObj_InitFields(void);
extern "C" igMetaObject *beFontImageList_GetOrCreateMetaObject(void);
extern "C" int beFontImageList_GetVTable(void);
extern "C" void beFontImageList_EnsureRegistered(void);
extern "C" CallbackArray *beFontImageList_Register(void);
extern "C" void beFontImageList_GetMetaObjectFunction(void);
extern "C" int beFontImage_GetVTable(void);
extern "C" void beFontImage_EnsureRegistered(void);
extern "C" CallbackArray *beFontImage_Register(void);
extern "C" void beFontImage_GetMetaObjectFunction(void);
extern "C" igMetaObject *igBitmapFont_GetPublishedMetaObject(void);
extern "C" igMetaObject *beFont_GetOrCreateMetaObject(void);
extern "C" void *beFont_GetMetaObject(void);
extern "C" int beFont_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beFontGeomAttrPairList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beFont_EnsureRegistered(void);
extern "C" CallbackArray *beFont_Register(void);
extern "C" void beFont_GetMetaObjectFunction(void);
extern "C" void beFont_InitFields(void);
extern "C" igMetaObject *beFontGeomAttrPairList_GetOrCreateMetaObject(void);
extern "C" void *beFontGeomAttrPairList_GetMetaObject(void);
extern "C" int beFontGeomAttrPairList_GetVTable(void);
extern "C" void beFontGeomAttrPairList_EnsureRegistered(void);
extern "C" CallbackArray *beFontGeomAttrPairList_Register(void);
extern "C" void beFontGeomAttrPairList_GetMetaObjectFunction(void);
extern "C" void *beFontGeomAttrPair_GetMetaObject(void);
extern "C" int beFontGeomAttrPair_GetVTable(void);
extern "C" void beFontGeomAttrPair_EnsureRegistered(void);
extern "C" CallbackArray *beFontGeomAttrPair_Register(void);
extern "C" void beFontGeomAttrPair_GetMetaObjectFunction(void);
extern "C" void beFontGeomAttrPair_InitFields(void);
extern "C" igMetaObject *beFileListInfoManager_GetOrCreateMetaObject(void);
extern "C" void *beFileListInfoManager_GetMetaObject(void);
extern "C" int beFileListInfoManager_GetVTable(void);
extern "C" void beFileListInfoManager_EnsureRegistered(void);
extern "C" CallbackArray *beFileListInfoManager_Register(void);
extern "C" void beFileListInfoManager_GetMetaObjectFunction(void);
extern "C" int igDirectoryList_GetOrCreateMetaObject(void);
extern "C" void beFileListInfoManager_InitFields(void);
extern "C" void *beFileListInfo_GetMetaObject(void);
extern "C" int beFileListInfo_GetVTable(void);
extern "C" void beFileListInfo_EnsureRegistered(void);
extern "C" CallbackArray *beFileListInfo_Register(void);
extern "C" void beFileListInfo_GetMetaObjectFunction(void);
extern "C" void beFileListInfo_InitFields(void);
extern "C" void *beFile_GetMetaObject(void);
extern "C" int beFile_GetVTable(void);
extern "C" void beFile_EnsureRegistered(void);
extern "C" CallbackArray *beFile_Register(void);
extern "C" void beFile_GetMetaObjectFunction(void);
extern "C" void *beFileChkObj_GetMetaObject(void);
extern "C" int beFileChkObj_GetVTable(void);
extern "C" void beFileChkObj_EnsureRegistered(void);
extern "C" CallbackArray *beFileChkObj_Register(void);
extern "C" void beFileChkObj_GetMetaObjectFunction(void);
extern "C" int igFile_GetOrCreateMetaObject(void);
extern "C" void beFileChkObj_InitFields(void);
extern "C" igMetaObject *beDemoManager_GetOrCreateMetaObject(void);
extern "C" void *beDemoManager_GetMetaObject(void);
extern "C" int beDemoManager_GetVTable(void);
extern "C" void beDemoManager_EnsureRegistered(void);
extern "C" CallbackArray *beDemoManager_Register(void);
extern "C" void beDemoManager_GetMetaObjectFunction(void);
extern "C" void beDemoManager_InitFields(void);
extern "C" igMetaObject *beDemoManagerWorkList_GetOrCreateMetaObject(void);
extern "C" void *beDemoManagerWorkList_GetMetaObject(void);
extern "C" int beDemoManagerWorkList_GetVTable(void);
extern "C" void beDemoManagerWorkList_EnsureRegistered(void);
extern "C" CallbackArray *beDemoManagerWorkList_Register(void);
extern "C" void beDemoManagerWorkList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beDemoManagerWork_GetOrCreateMetaObject(void);
extern "C" void *beDemoManagerWork_GetMetaObject(void);
extern "C" int beDemoManagerWork_GetVTable(void);
extern "C" void beDemoManagerWork_EnsureRegistered(void);
extern "C" CallbackArray *beDemoManagerWork_Register(void);
extern "C" void beDemoManagerWork_GetMetaObjectFunction(void);
extern "C" void beDemoManagerWork_InitFields(void);
extern "C" igMetaObject *beDemoKeepMesList_GetOrCreateMetaObject(void);
extern "C" int beDemoKeepMesList_GetVTable(void);
extern "C" void beDemoKeepMesList_EnsureRegistered(void);
extern "C" CallbackArray *beDemoKeepMesList_Register(void);
extern "C" void beDemoKeepMesList_GetMetaObjectFunction(void);
extern "C" int beDemoKeepMes_GetVTable(void);
extern "C" void beDemoKeepMes_EnsureRegistered(void);
extern "C" CallbackArray *beDemoKeepMes_Register(void);
extern "C" void beDemoKeepMes_GetMetaObjectFunction(void);
extern "C" void beDemoKeepMes_InitFields(void);
extern "C" int beDataObjListList_GetVTable(void);
extern "C" CallbackArray *beDataObjListList_Register(void);
extern "C" void beDataObjListList_GetMetaObjectFunction(void);
extern "C" int beDataObjList_GetVTable(void);
extern "C" CallbackArray *beDataObjList_Register(void);
extern "C" void beDataObjList_GetMetaObjectFunction(void);
extern "C" void *beDataObjFloatList_GetMetaObject(void);
extern "C" int beDataObjFloatList_GetVTable(void);
extern "C" void beDataObjFloatList_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjFloatList_Register(void);
extern "C" void beDataObjFloatList_GetMetaObjectFunction(void);
extern "C" void beDataObjFloatList_InitFields(void);
extern "C" void *beDataObjObjectList_GetMetaObject(void);
extern "C" int beDataObjObjectList_GetVTable(void);
extern "C" void beDataObjObjectList_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjObjectList_Register(void);
extern "C" void beDataObjObjectList_GetMetaObjectFunction(void);
extern "C" void beDataObjObjectList_InitFields(void);
extern "C" void *beDataObjStringList_GetMetaObject(void);
extern "C" int beDataObjStringList_GetVTable(void);
extern "C" void beDataObjStringList_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjStringList_Register(void);
extern "C" void beDataObjStringList_GetMetaObjectFunction(void);
extern "C" void beDataObjStringList_InitFields(void);
extern "C" void *beDataObjString_GetMetaObject(void);
extern "C" int beDataObjString_GetVTable(void);
extern "C" void beDataObjString_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjString_Register(void);
extern "C" void beDataObjString_GetMetaObjectFunction(void);
extern "C" void beDataObjString_InitFields(void);
extern "C" void *beDataObjBoolList_GetMetaObject(void);
extern "C" int beDataObjBoolList_GetVTable(void);
extern "C" void beDataObjBoolList_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjBoolList_Register(void);
extern "C" void beDataObjBoolList_GetMetaObjectFunction(void);
extern "C" void beDataObjBoolList_InitFields(void);
extern "C" void *beDataObjBool_GetMetaObject(void);
extern "C" int beDataObjBool_GetVTable(void);
extern "C" void beDataObjBool_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjBool_Register(void);
extern "C" void beDataObjBool_GetMetaObjectFunction(void);
extern "C" void beDataObjBool_InitFields(void);
extern "C" void *beDataObjIntList_GetMetaObject(void);
extern "C" int beDataObjIntList_GetVTable(void);
extern "C" void beDataObjIntList_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjIntList_Register(void);
extern "C" void beDataObjIntList_GetMetaObjectFunction(void);
extern "C" void beDataObjIntList_InitFields(void);
extern "C" igMetaObject *beDataObjInt_GetOrCreateMetaObject(void);
extern "C" void *beDataObjInt_GetMetaObject(void);
extern "C" int beDataObjInt_GetVTable(void);
extern "C" void beDataObjInt_EnsureRegistered(void);
extern "C" CallbackArray *beDataObjInt_Register(void);
extern "C" void beDataObjInt_GetMetaObjectFunction(void);
extern "C" void beDataObjInt_InitFields(void);
extern "C" void *beDataBaseList_GetMetaObject(void);
extern "C" int beDataBaseList_GetVTable(void);
extern "C" void beDataBaseList_EnsureRegistered(void);
extern "C" CallbackArray *beDataBaseList_Register(void);
extern "C" void beDataBaseList_GetMetaObjectFunction(void);
extern "C" void *beDataBase_GetMetaObject(void);
extern "C" int beDataBase_GetVTable(void);
extern "C" CallbackArray *beDataBase_Register(void);
extern "C" void beDataBase_GetMetaObjectFunction(void);
extern "C" int igShortList_GetOrCreateMetaObject(void);
extern "C" int igCharList_GetOrCreateMetaObject(void);
extern "C" void beDataBase_InitFields(void);
extern "C" int beDBManagerInfo_GetVTable(void);
extern "C" void beDBManagerInfo_EnsureRegistered(void);
extern "C" CallbackArray *beDBManagerInfo_Register(void);
extern "C" void beDBManagerInfo_GetMetaObjectFunction(void);
extern "C" void beDBManagerInfo_InitFields(void);
extern "C" igMetaObject *beDBManager_GetOrCreateMetaObject(void);
extern "C" int beDBManager_GetVTable(void);
extern "C" void beDBManager_EnsureRegistered(void);
extern "C" CallbackArray *beDBManager_Register(void);
extern "C" void beDBManager_GetMetaObjectFunction(void);
extern "C" igMetaObject *beCriVolume_GetOrCreateMetaObject(void);
extern "C" int beCriVolume_GetVTable(void);
extern "C" void beCriVolume_EnsureRegistered(void);
extern "C" CallbackArray *beCriVolume_Register(void);
extern "C" void beCriVolume_GetMetaObjectFunction(void);
extern "C" void beCriVolume_InitFields(void);
extern "C" int beCriSfpData_GetVTable(void);
extern "C" void beCriSfpData_EnsureRegistered(void);
extern "C" CallbackArray *beCriSfpData_Register(void);
extern "C" void beCriSfpData_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBinDataObject_GetPublishedMetaObject(void);
extern "C" void beCriSfpData_InitFields(void);
extern "C" void beCriSfpData_StaticInitCallback(void);
extern "C" igMetaObject *beCriHandleList_GetOrCreateMetaObject(void);
extern "C" void *beCriHandleList_GetMetaObject(void);
extern "C" int beCriHandleList_GetVTable(void);
extern "C" void beCriHandleList_EnsureRegistered(void);
extern "C" CallbackArray *beCriHandleList_Register(void);
extern "C" void beCriHandleList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beCriHandle_GetOrCreateMetaObject(void);
extern "C" void *beCriHandle_GetMetaObject(void);
extern "C" int beCriHandle_GetVTable(void);
extern "C" void beCriHandle_EnsureRegistered(void);
extern "C" CallbackArray *beCriHandle_Register(void);
extern "C" void beCriHandle_GetMetaObjectFunction(void);
extern "C" void beCriHandle_InitFields(void);
extern "C" void *beCriFxInfo_GetMetaObject(void);
extern "C" int beCriFxInfo_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beCriFxXbData_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" void beCriFxInfo_EnsureRegistered(void);
extern "C" CallbackArray *beCriFxInfo_Register(void);
extern "C" void beCriFxInfo_GetMetaObjectFunction(void);
extern "C" void beCriFxInfo_InitFields(void);
extern "C" igMetaObject *beCriFxXbData_GetOrCreateMetaObject(void);
extern "C" void *beCriFxXbData_GetMetaObject(void);
extern "C" int beCriFxXbData_GetVTable(void);
extern "C" void beCriFxXbData_EnsureRegistered(void);
extern "C" CallbackArray *beCriFxXbData_Register(void);
extern "C" void beCriFxXbData_GetMetaObjectFunction(void);
extern "C" void beCriFxXbData_InitFields(void);
extern "C" igMetaObject *beCriAudio_GetOrCreateMetaObject(void);
extern "C" void *beCriAudio_GetMetaObject(void);
extern "C" int beCriAudio_GetVTable(void);
extern "C" void beCriAudio_EnsureRegistered(void);
extern "C" CallbackArray *beCriAudio_Register(void);
extern "C" void beCriAudio_GetMetaObjectFunction(void);
extern "C" void beCriAudio_InitFields(void);
extern "C" igMetaObject *beCriSndf_GetOrCreateMetaObject(void);
extern "C" void *beCriSndf_GetMetaObject(void);
extern "C" int beCriSndf_GetVTable(void);
extern "C" void beCriSndf_EnsureRegistered(void);
extern "C" CallbackArray *beCriSndf_Register(void);
extern "C" void beCriSndf_GetMetaObjectFunction(void);
extern "C" void beCriSndf_InitFields(void);
extern "C" void *beCriAcxData_GetMetaObject(void);
extern "C" int beCriAcxData_GetVTable(void);
extern "C" void beCriAcxData_EnsureRegistered(void);
extern "C" CallbackArray *beCriAcxData_Register(void);
extern "C" void beCriAcxData_GetMetaObjectFunction(void);
extern "C" igMetaObject *beCri_GetOrCreateMetaObject(void);
extern "C" void *beCri_GetMetaObject(void);
extern "C" int beCri_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beCriHandle_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beCri_EnsureRegistered(void);
extern "C" CallbackArray *beCri_Register(void);
extern "C" void beCri_GetMetaObjectFunction(void);
extern "C" void beCri_InitFields(void);
extern "C" void *beCountry_GetMetaObject(void);
extern "C" int beCountry_GetVTable(void);
extern "C" void beCountry_EnsureRegistered(void);
extern "C" CallbackArray *beCountry_Register(void);
extern "C" void beCountry_GetMetaObjectFunction(void);
extern "C" int beCopyTransform_GetVTable(void);
extern "C" void beCopyTransform_EnsureRegistered(void);
extern "C" CallbackArray *beCopyTransform_Register(void);
extern "C" void beCopyTransform_GetMetaObjectFunction(void);
extern "C" void beCopyTransform_InitFields(void);
extern "C" void beCopyTransform_StaticInitCallback(void);
extern "C" int beCopyModelCtrl2_GetVTable(void);
extern "C" void beCopyModelCtrl2_EnsureRegistered(void);
extern "C" CallbackArray *beCopyModelCtrl2_Register(void);
extern "C" void beCopyModelCtrl2_GetMetaObjectFunction(void);
extern "C" void beCopyModelCtrl2_InitFields(void);
extern "C" void beCopyModelCtrl2_StaticInitCallback(void);
extern "C" int beChangePosTransformInfoRam_GetVTable(void);
extern "C" void beChangePosTransformInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beChangePosTransformInfoRam_Register(void);
extern "C" void beChangePosTransformInfoRam_GetMetaObjectFunction(void);
extern "C" void beChangePosTransformInfoRam_InitFields(void);
extern "C" int beChangePosTransformInfo_GetVTable(void);
extern "C" void beChangePosTransformInfo_EnsureRegistered(void);
extern "C" CallbackArray *beChangePosTransformInfo_Register(void);
extern "C" void beChangePosTransformInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *beChangePosTransform_GetOrCreateMetaObject(void);
extern "C" int beChangePosTransform_GetVTable(void);
extern "C" void beChangePosTransform_EnsureRegistered(void);
extern "C" CallbackArray *beChangePosTransform_Register(void);
extern "C" void beChangePosTransform_GetMetaObjectFunction(void);
extern "C" void beChangePosTransform_InitFields(void);
extern "C" igMetaObject *beCameraMode_GetOrCreateMetaObject(void);
extern "C" void *beCameraMode_GetMetaObject(void);
extern "C" int beCameraMode_GetVTable(void);
extern "C" void beCameraMode_EnsureRegistered(void);
extern "C" CallbackArray *beCameraMode_Register(void);
extern "C" void beCameraMode_GetMetaObjectFunction(void);
extern "C" void beCameraMode_InitFields(void);
extern "C" void *beCameraCtrlInfo_GetMetaObject(void);
extern "C" int beCameraCtrlInfo_GetVTable(void);
extern "C" void beCameraCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beCameraCtrlInfo_Register(void);
extern "C" void beCameraCtrlInfo_GetMetaObjectFunction(void);
extern "C" void beCameraCtrlInfo_InitFields(void);
extern "C" void *beCameraDemoData_GetMetaObject(void);
extern "C" int beCameraDemoData_GetVTable(void);
extern "C" void beCameraDemoData_EnsureRegistered(void);
extern "C" CallbackArray *beCameraDemoData_Register(void);
extern "C" void beCameraDemoData_GetMetaObjectFunction(void);
extern "C" void beCameraDemoData_InitFields(void);
extern "C" void *beCameraBoxData_GetMetaObject(void);
extern "C" int beCameraBoxData_GetVTable(void);
extern "C" void beCameraBoxData_EnsureRegistered(void);
extern "C" CallbackArray *beCameraBoxData_Register(void);
extern "C" void beCameraBoxData_GetMetaObjectFunction(void);
extern "C" void beCameraBoxData_InitFields(void);
extern "C" void *beCameraCtrlInfoRamShake_GetMetaObject(void);
extern "C" int beCameraCtrlInfoRamShake_GetVTable(void);
extern "C" void beCameraCtrlInfoRamShake_EnsureRegistered(void);
extern "C" CallbackArray *beCameraCtrlInfoRamShake_Register(void);
extern "C" void beCameraCtrlInfoRamShake_GetMetaObjectFunction(void);
extern "C" void beCameraCtrlInfoRamShake_InitFields(void);
extern "C" igMetaObject *beCameraCtrl_GetOrCreateMetaObject(void);
extern "C" void *beCameraCtrl_GetMetaObject(void);
extern "C" int beCameraCtrl_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beCameraMode_Destruct(igSmartPointer<igObject> *self, long long delete_storage);
extern "C" void beCameraCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beCameraCtrl_Register(void);
extern "C" void beCameraCtrl_GetMetaObjectFunction(void);
extern "C" void beCameraCtrl_InitFields(void);
extern "C" void *beBkColorInfo_GetMetaObject(void);
extern "C" int beBkColorInfo_GetVTable(void);
extern "C" void beBkColorInfo_EnsureRegistered(void);
extern "C" CallbackArray *beBkColorInfo_Register(void);
extern "C" void beBkColorInfo_GetMetaObjectFunction(void);
extern "C" void beBkColorInfo_InitFields(void);
extern "C" igMetaObject *beBkColor_GetOrCreateMetaObject(void);
extern "C" void *beBkColor_GetMetaObject(void);
extern "C" int beBkColor_GetVTable(void);
extern "C" void beBkColor_EnsureRegistered(void);
extern "C" CallbackArray *beBkColor_Register(void);
extern "C" void beBkColor_GetMetaObjectFunction(void);
extern "C" void beBkColor_InitFields(void);
extern "C" igMetaObject *beBaseInfoRamList_GetOrCreateMetaObject(void);
extern "C" void *beBaseInfoRamList_GetReadyMetaObject(void);
extern "C" int beBaseInfoRamList_GetVTable(void);
extern "C" void beBaseInfoRamList_EnsureRegistered(void);
extern "C" CallbackArray *beBaseInfoRamList_Register(void);
extern "C" void *beBaseInfoRamList_GetMetaObject(void);
extern "C" void *beBaseInfoRam_GetMetaObject(void);
extern "C" int beBaseInfoRam_GetVTable(void);
extern "C" void beBaseInfoRam_GetMetaObjectFunction(void);
extern "C" void beBaseInfoRam_InitFields(void);
extern "C" void *beBaseInfoRamTimer_GetMetaObject(void);
extern "C" int beBaseInfoRamTimer_GetVTable(void);
extern "C" void beBaseInfoRamTimer_EnsureRegistered(void);
extern "C" CallbackArray *beBaseInfoRamTimer_Register(void);
extern "C" void beBaseInfoRamTimer_GetMetaObjectFunction(void);
extern "C" void beBaseInfoRamTimer_InitFields(void);
extern "C" int beBaseInfoManagerList_GetVTable(void);
extern "C" void beBaseInfoManagerList_EnsureRegistered(void);
extern "C" CallbackArray *beBaseInfoManagerList_Register(void);
extern "C" void beBaseInfoManagerList_GetMetaObjectFunction(void);
extern "C" void beBaseInfoManager_GetMetaObjectFunction(void);
extern "C" void beBaseInfoManager_InitFields(void);
extern "C" igMetaObject *beBaseInfoList_GetOrCreateMetaObject(void);
extern "C" int beBaseInfoList_GetVTable(void);
extern "C" void beBaseInfoList_EnsureRegistered(void);
extern "C" CallbackArray *beBaseInfoList_Register(void);
extern "C" void beBaseInfoList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beBaseInfo_GetOrCreateMetaObject(void);
extern "C" void beBaseInfo_EnsureRegistered(void);
extern "C" void beBaseInfo_GetMetaObjectFunction(void);
extern "C" void beBaseInfo_InitFields(void);
extern "C" igMetaObject *beBaseInfoDataList_GetOrCreateMetaObject(void);
extern "C" void *beBaseInfoDataList_GetMetaObject(void);
extern "C" int beBaseInfoDataList_GetVTable(void);
extern "C" void beBaseInfoDataList_EnsureRegistered(void);
extern "C" CallbackArray *beBaseInfoDataList_Register(void);
extern "C" void beBaseInfoDataList_GetMetaObjectFunction(void);
extern "C" void *beBaseInfoData_GetMetaObject(void);
extern "C" void beBaseInfoData_EnsureRegistered(void);
extern "C" void beBaseInfoData_GetMetaObjectFunction(void);
extern "C" void beBaseInfoData_InitFields(void);
extern "C" void *beActionStarterInfoRam_GetMetaObject(void);
extern "C" int beActionStarterInfoRam_GetVTable(void);
extern "C" void beActionStarterInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beActionStarterInfoRam_Register(void);
extern "C" void beActionStarterInfoRam_GetMetaObjectFunction(void);
extern "C" void *beActionStarterInfo_GetMetaObject(void);
extern "C" int beActionStarterInfo_GetVTable(void);
extern "C" void beActionStarterInfo_EnsureRegistered(void);
extern "C" CallbackArray *beActionStarterInfo_Register(void);
extern "C" void beActionStarterInfo_GetMetaObjectFunction(void);
extern "C" void beActionStarterInfo_InitFields(void);
extern "C" igMetaObject *beAsTargetModelDataList_GetOrCreateMetaObject(void);
extern "C" void *beAsTargetModelDataList_GetMetaObject(void);
extern "C" int beAsTargetModelDataList_GetVTable(void);
extern "C" void beAsTargetModelDataList_EnsureRegistered(void);
extern "C" CallbackArray *beAsTargetModelDataList_Register(void);
extern "C" void beAsTargetModelDataList_GetMetaObjectFunction(void);
extern "C" void *beAsTargetModelData_GetMetaObject(void);
extern "C" int beAsTargetModelData_GetVTable(void);
extern "C" void beAsTargetModelData_EnsureRegistered(void);
extern "C" CallbackArray *beAsTargetModelData_Register(void);
extern "C" void beAsTargetModelData_GetMetaObjectFunction(void);
extern "C" void beAsTargetModelData_InitFields(void);
extern "C" void *beActionStarterData2_GetMetaObject(void);
extern "C" int beActionStarterData2_GetVTable(void);
extern "C" void beActionStarterData2_EnsureRegistered(void);
extern "C" CallbackArray *beActionStarterData2_Register(void);
extern "C" void beActionStarterData2_GetMetaObjectFunction(void);
extern "C" igMetaObject *beActionStarterData_GetPublishedMetaObject(void);
extern "C" void beActionStarterData2_InitFields(void);
extern "C" igMetaObject *beActionStarterDataList_GetOrCreateMetaObject(void);
extern "C" void *beActionStarterDataList_GetMetaObject(void);
extern "C" int beActionStarterDataList_GetVTable(void);
extern "C" void beActionStarterDataList_EnsureRegistered(void);
extern "C" CallbackArray *beActionStarterDataList_Register(void);
extern "C" void beActionStarterDataList_GetMetaObjectFunction(void);
extern "C" void *beActionStarterData_GetMetaObject(void);
extern "C" int beActionStarterData_GetVTable(void);
extern "C" void beActionStarterData_EnsureRegistered(void);
extern "C" CallbackArray *beActionStarterData_Register(void);
extern "C" void beActionStarterData_GetMetaObjectFunction(void);
extern "C" void beActionStarterData_InitFields(void);
extern "C" igMetaObject *beActionStarter_GetOrCreateMetaObject(void);
extern "C" void *beActionStarter_GetMetaObject(void);
extern "C" int beActionStarter_GetVTable(void);
extern "C" void beActionStarter_EnsureRegistered(void);
extern "C" CallbackArray *beActionStarter_Register(void);
extern "C" void beActionStarter_GetMetaObjectFunction(void);
extern "C" igMetaObject *beAction2InfoWork_GetOrCreateMetaObject(void);
extern "C" int igSmartPointer_igTextureStateAttr_Destruct(char *, int);
extern "C" int beAction2InfoWork_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beAction2Data_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beAction2InfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beAction2InfoWork_Register(void);
extern "C" void beAction2InfoWork_GetMetaObjectFunction(void);
extern "C" void beAction2InfoWork_InitFields(void);
extern "C" int beAction2InfoRam_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beAction2InfoWork_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" void beAction2InfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beAction2InfoRam_Register(void);
extern "C" void beAction2InfoRam_GetMetaObjectFunction(void);
extern "C" void beAction2InfoRam_InitFields(void);
extern "C" int beAction2InfoList_GetVTable(void);
extern "C" void beAction2InfoList_EnsureRegistered(void);
extern "C" CallbackArray *beAction2InfoList_Register(void);
extern "C" void beAction2InfoList_GetMetaObjectFunction(void);
extern "C" int beAction2Info_GetVTable(void);
extern "C" void beAction2Info_EnsureRegistered(void);
extern "C" CallbackArray *beAction2Info_Register(void);
extern "C" void beAction2Info_GetMetaObjectFunction(void);
extern "C" void beAction2Info_InitFields(void);
extern "C" void *beAction2FLASHSET_GetMetaObject(void);
extern "C" int beAction2FLASHSET_GetVTable(void);
extern "C" void beAction2FLASHSET_EnsureRegistered(void);
extern "C" CallbackArray *beAction2FLASHSET_Register(void);
extern "C" void beAction2FLASHSET_GetMetaObjectFunction(void);
extern "C" void *beAction2WAITCHECK_GetMetaObject(void);
extern "C" int beAction2WAITCHECK_GetVTable(void);
extern "C" void beAction2WAITCHECK_EnsureRegistered(void);
extern "C" CallbackArray *beAction2WAITCHECK_Register(void);
extern "C" void beAction2WAITCHECK_GetMetaObjectFunction(void);
extern "C" void beAction2WAITCHECK_InitFields(void);
extern "C" void *beAction2FADESET_GetMetaObject(void);
extern "C" int beAction2FADESET_GetVTable(void);
extern "C" void beAction2FADESET_EnsureRegistered(void);
extern "C" CallbackArray *beAction2FADESET_Register(void);
extern "C" void beAction2FADESET_GetMetaObjectFunction(void);
extern "C" void beAction2FADESET_InitFields(void);
extern "C" void *beAction2JOINTSET_GetMetaObject(void);
extern "C" int beAction2JOINTSET_GetVTable(void);
extern "C" void beAction2JOINTSET_EnsureRegistered(void);
extern "C" CallbackArray *beAction2JOINTSET_Register(void);
extern "C" void beAction2JOINTSET_GetMetaObjectFunction(void);
extern "C" void beAction2JOINTSET_InitFields(void);
extern "C" void *beAction2MOTIONSET_GetMetaObject(void);
extern "C" int beAction2MOTIONSET_GetVTable(void);
extern "C" void beAction2MOTIONSET_EnsureRegistered(void);
extern "C" CallbackArray *beAction2MOTIONSET_Register(void);
extern "C" void beAction2MOTIONSET_GetMetaObjectFunction(void);
extern "C" void beAction2MOTIONSET_InitFields(void);
extern "C" igMetaObject *beAction2DataList_GetOrCreateMetaObject(void);
extern "C" void *beAction2DataList_GetMetaObject(void);
extern "C" int beAction2DataList_GetVTable(void);
extern "C" void beAction2DataList_EnsureRegistered(void);
extern "C" CallbackArray *beAction2DataList_Register(void);
extern "C" void beAction2DataList_GetMetaObjectFunction(void);
extern "C" igMetaObject *beAction2Data_GetOrCreateMetaObject(void);
extern "C" void *beAction2Data_GetMetaObject(void);
extern "C" int beAction2Data_GetVTable(void);
extern "C" void beAction2Data_EnsureRegistered(void);
extern "C" CallbackArray *beAction2Data_Register(void);
extern "C" void beAction2Data_GetMetaObjectFunction(void);
extern "C" void beAction2Data_InitFields(void);
extern "C" igMetaObject *beAction2_GetOrCreateMetaObject(void);
extern "C" void *beAction2_GetMetaObject(void);
extern "C" int beAction2_GetVTable(void);
extern "C" void beAction2_EnsureRegistered(void);
extern "C" CallbackArray *beAction2_Register(void);
extern "C" void beAction2_GetMetaObjectFunction(void);
extern "C" igMetaObject *be_GetOrCreateMetaObject(void);
extern "C" void *be_GetMetaObject(void);
extern "C" int be_GetVTable(void);
extern "C" CallbackArray *be_Register(void);
extern "C" void be_GetMetaObjectFunction(void);
extern "C" void be_InitFields(void);
extern "C" void *ParticleArray_GetMetaObject(void);
extern "C" int ParticleArray_GetVTable(void);
extern "C" void ParticleArray_EnsureRegistered(void);
extern "C" CallbackArray *ParticleArray_Register(void);
extern "C" void ParticleArray_GetMetaObjectFunction(void);
extern "C" void ParticleArray_InitFields(void);
extern "C" igMetaObject *ParticleTimer_GetOrCreateMetaObject(void);
extern "C" int ParticleTimer_GetVTable(void);
extern "C" void ParticleTimer_EnsureRegistered(void);
extern "C" CallbackArray *ParticleTimer_Register(void);
extern "C" void ParticleTimer_GetMetaObjectFunction(void);
extern "C" void ParticleTimer_InitFields(void);
extern "C" void ParticleTimer_StaticInitCallback(void);
extern "C" igMetaEnum *ParticleInfo_GetParticleTimeTypeMetaEnum(void);
extern "C" igMetaEnum *ParticleInfo_GetParticleAlphaFunctionMetaEnum(void);
extern "C" igMetaEnum *ParticleInfo_GetParticleAlphaTypeMetaEnum(void);
extern "C" igMetaEnum *ParticleInfo_GetParticleEmitterTypeMetaEnum(void);
extern "C" int ParticleInfo_GetVTable(void);
extern "C" void ParticleInfo_EnsureRegistered(void);
extern "C" CallbackArray *ParticleInfo_Register(void);
extern "C" void ParticleInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *igSceneInfo_GetPublishedMetaObject(void);
extern "C" void ParticleInfo_InitFields(void);
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
extern "C" igMetaObject *igFont_GetMeta(void);
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
extern "C" igMetaObject *igLightSetList_GetElementMeta(void);
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
extern "C" void **igSmartPointer_beNumVerInsideData_Destruct(void **arg0, short arg1);
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
extern "C" void beSaveDataDeliver_userConstruct(beSaveDataDeliver *self);
extern "C" igMetaObject *beSvSlotXbox_GetMeta(void);
extern "C" igMetaObject *beSvSlotGC_GetMeta(void);
extern "C" igMetaObject *beSvSlotPS2_GetMeta(void);
extern "C" igMetaObject *beSvSlotDataList_GetMeta(void);
extern "C" igMetaObject *beSvSlotDataList_GetElementMeta(void);
extern "C" igMetaObject *beSvPlatDataGC_GetMeta(void);
extern "C" void beSvPlatDataGC_userConstruct(beSvPlatDataGC *self);
extern "C" igMetaObject *beSvPs2McImage128k_GetMeta(void);
extern "C" void beSvPs2McImage128k_userDestruct(beSvPs2McImage128k *self);
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
extern "C" igMetaObject *beUnicode_GetMeta(void);
extern "C" igMetaObject *beWaterPlainInfo_GetMeta(void);
extern "C" igMetaObject *beWaterMoveData_GetMeta(void);
extern "C" igMetaObject *beWaterMoveDataList_GetMeta(void);
extern "C" igMetaObject *beWaterMoveDataList_GetElementMeta(void);
extern "C" igMetaObject *beWaterMove_GetMeta(void);
extern "C" igMetaObject *beWaterPlainInfoRam_GetMeta(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelectList_GetMeta(void);
extern "C" igMetaObject *igAppearanceListList_GetMeta(void);
extern "C" igMetaObject *igAppearanceListList_GetElementMeta(void);
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
extern "C" igSmartPointer<igObject> *igSmartPointer_beMessengerArgData_Destruct(igSmartPointer<igObject> *self, int delete_storage);
/* Deleting destructor; the deletion flag is a signed short. */
extern "C" igSmartPointer<igObject> *igSmartPointer_beParticleCtrl2_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMatCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage);
struct R { int vt; unsigned int rc; };
extern "C" igSmartPointer<igObject> *igSmartPointer_beSelectCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beTargetObj_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beCameraCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beChangePosTransform_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beGenerater_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beHitLandModel_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beHitLandDeliv_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beActionStarter_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beFont_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSwitchCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNumberCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMovie_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beDBManager_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSaveUtil_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMessenger_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beDemoManager_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beMemory_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" int g_igInsightPlugin_vtable[4];
extern "C" igMetaObject *g_beWeaponInfoRam_metaObject;
extern "C" int g_beWeaponInfoRam_vtable[4];
extern "C" void *beBaseInfoRam_Destroy(beBaseInfoRam *self, long long delete_storage);
extern "C" igSmartPointer<igObject> *beWeaponInfoRam_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" int g_beWeaponInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beBaseInfoRamList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" int g_beBaseInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beWeaponSeqDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beWeaponSeqDataList_metaObject;
extern "C" int g_beWeaponSeqDataList_vtable[4];
extern "C" igMetaObject *g_beWeaponSeqData_metaObject;
extern "C" int g_beWeaponSeqData_vtable[4];
extern "C" int g_beWeapon_vtable[4];
extern "C" int g_igInfoManager_vtable[4];
extern "C" igMetaObject *g_beWeaponAttachDataList_metaObject;
extern "C" igMetaObject *beWeaponAttachDataList_GetMetaObject(void);
extern "C" int g_beWeaponAttachDataList_vtable[4];
extern "C" igMetaObject *g_beWeaponAttachData_metaObject;
extern "C" igMetaObject *beWeaponAttachData_GetMetaObject(void);
extern "C" int g_beWeaponAttachData_vtable[4];
extern "C" igMetaObject *g_igAppearanceListList_metaObject;
extern "C" igMetaObject *igAppearanceListList_GetMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
extern "C" int g_igAppearanceListList_vtable[4];
extern "C" igMetaObject *igModelViewMatrixBoneSelectListBec_GetMetaObject(void);
extern "C" int g_igModelViewMatrixBoneSelectListBec_vtable[4];
extern "C" igMetaObject *g_beWaterPlainInfoRam_metaObject;
extern "C" int g_beWaterPlainInfoRam_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igFloatListList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beWaterMove_metaObject;
extern "C" int g_beWaterMove_vtable[4];
extern "C" igMetaObject *g_beWaterMoveDataList_metaObject;
extern "C" int g_beWaterMoveDataList_vtable[4];
extern "C" igMetaObject *g_beWaterMoveData_metaObject;
extern "C" int g_beWaterMoveData_vtable[4];
extern "C" int g_beWaterPlainInfo_vtable[4];
extern "C" int g_beWaterPlain_vtable[4];
extern "C" igMetaObject *g_beUnicode_metaObject;
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
extern "C" igSmartPointer<igObject> *igSmartPointer_igTransformList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *igTransform_GetPublishedMetaObject(void);
extern "C" int g_beTimer_vtable[4];
extern "C" igMetaObject *igInfoManager_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beTimerDataList_metaObject;
extern "C" int g_beTimerDataList_vtable[4];
extern "C" igMetaObject *g_beTimerData_metaObject;
extern "C" igMetaObject *beTimerData_GetMetaObject(void);
extern "C" int g_beTimerData_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlInfoList_metaObject;
extern "C" igMetaObject *beTextureCtrlInfoList_GetMetaObject(void);
extern "C" int g_beTextureCtrlInfoList_vtable[4];
extern "C" igMetaObject *beTextureCtrlInfo_GetMetaObject(void);
extern "C" int g_beTextureCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlAttr_metaObject;
extern "C" igMetaObject *beTextureCtrlAttr_GetMetaObject(void);
extern "C" int g_beTextureCtrlAttr_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlData_metaObject;
extern "C" int g_beTextureCtrlData_vtable[4];
extern "C" int g_beTextureCtrl_vtable[4];
extern "C" igMetaObject *g_beTextureCtrlWork_metaObject;
extern "C" int g_beTextureCtrlWork_vtable[4];
extern "C" int g_beTargetObj_vtable[4];
extern "C" int g_beSystem_vtable[4];
extern "C" int g_beSwitchCtrlInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igSwitch_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" int g_beSwitchCtrl_vtable[4];
extern "C" int g_beStaticInfoCtl_vtable[4];
extern "C" int g_beStaticInfo_vtable[4];
extern "C" igMetaObject *g_beBinDataObject_metaObject;
extern "C" igMetaObject *beSoundInfo_GetMetaObject(void);
extern "C" int g_beSoundInfo_vtable[4];
extern "C" igMetaObject *g_beSoundData_metaObject;
extern "C" igMetaObject *beSoundData_GetMetaObject(void);
extern "C" int g_beSoundData_vtable[4];
extern "C" int g_beBaseInfoData_vtable[4];
extern "C" igMetaObject *beSound_GetMetaObject(void);
extern "C" int g_beSound_vtable[4];
extern "C" igMetaObject *g_bePlaySEList_metaObject;
extern "C" igMetaObject *bePlaySEList_GetMetaObject(void);
extern "C" int g_bePlaySEList_vtable[4];
extern "C" igMetaObject *g_bePlaySE_metaObject;
extern "C" int g_bePlaySE_vtable[4];
extern "C" igMetaObject *g_beShadow01InfoList_metaObject;
/* Stack object, vtable slot read through the object plus a runtime offset. */
extern "C" int g_beShadow01InfoList_vtable[4];
extern "C" int g_beShadow01Info_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igProjectiveShadowShader_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" int g_beShadow01_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beShadow01InfoList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" int g_beSelectCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beSelectCtrlInfoRamData_metaObject;
extern "C" int g_beSelectCtrlInfoRamData_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beSelectCtrlInfoWork_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_beSelectCtrlInfoWork_metaObject;
extern "C" int g_beSelectCtrlInfoWork_vtable[4];
extern "C" int g_beSelectCtrl_vtable[4];
extern "C" int g_beSeInfo_vtable[4];
extern "C" igMetaObject *g_beSeInfoData_metaObject;
extern "C" int g_beSeInfoData_vtable[4];
extern "C" igMetaObject *g_beSeDataList_metaObject;
extern "C" igMetaObject *beSeDataList_GetMetaObject(void);
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
                    StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
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
                    StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
                }
            }
        }
    }
};
extern "C" igMetaObject *beSeCtl_GetMetaObject(void);
extern "C" int g_beSeCtl_vtable[4];
extern "C" igMetaObject *g_beSaveUtilInfoRam_metaObject;
extern "C" igMetaObject *beSaveUtilInfoRam_GetMetaObject(void);
extern "C" int g_beSaveUtilInfoRam_vtable[4];
extern "C" int g_beSaveUtilInfo_vtable[4];
extern "C" int g_beSaveUtil_vtable[4];
extern "C" igMetaObject *g_beSvPlatDataPC_metaObject;
extern "C" int g_beSvPlatDataPC_vtable[4];
extern "C" int g_beSvPlatBaseData_vtable[4];
extern "C" beSvPlatBaseData *beSvPlatBaseData_Destroy(beSvPlatBaseData *self, short delete_storage);
extern "C" igMetaObject *g_beSvPlatDataXbox_metaObject;
extern "C" int g_beSvPlatDataXbox_vtable[4];
extern "C" igMetaObject *g_beXboxImage24k_metaObject;
extern "C" int g_beXboxImage24k_vtable[4];
extern "C" igMetaObject *g_beSvPlatDataPS2_metaObject;
extern "C" int g_beSvPlatDataPS2_vtable[4];
extern "C" igMetaObject *g_beSvPs2McImage128k_metaObject;
extern "C" int g_beSvPs2McImage128k_vtable[4];
extern "C" igMetaObject *g_beSvPlatDataGC_metaObject;
extern "C" int g_beSvPlatDataGC_vtable[4];
extern "C" int g_beSvConnectCheck_vtable[4];
extern "C" int g_beSaveApi_vtable[4];
extern "C" void *beSaveApi_Destroy(beSaveApi *self, short delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beSaveMemoryObj_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" int g_beSvEndApi_vtable[4];
extern "C" igMetaObject *beSvStartApi_GetMetaObject(void);
extern "C" int g_beSvStartApi_vtable[4];
extern "C" igMetaObject *beSvGetFreeSizeApi_GetMetaObject(void);
extern "C" int g_beSvGetFreeSizeApi_vtable[4];
extern "C" igMetaObject *beSvWriteMediaApi_GetMetaObject(void);
extern "C" int g_beSvWriteMediaApi_vtable[4];
extern "C" igMetaObject *beSvReadMediaApi_GetMetaObject(void);
extern "C" int g_beSvReadMediaApi_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beSaveDataDeliver_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" int g_beSvUseCheckApi_vtable[4];
extern "C" int g_beSvFormatApi_vtable[4];
extern "C" int g_beSvFileFindApi_vtable[4];
extern "C" int g_beSvFileMakeApi_vtable[4];
extern "C" igMetaObject *g_beSvPlatBaseData_metaObject;
extern "C" igMetaObject *g_beSvSlotDataList_metaObject;
extern "C" int g_beSvSlotDataList_vtable[4];
extern "C" igMetaObject *g_beSvSlotPS2_metaObject;
extern "C" int g_beSvSlotPS2_vtable[4];
extern "C" igMetaObject *g_beSvSlotGC_metaObject;
extern "C" int g_beSvSlotGC_vtable[4];
extern "C" igMetaObject *g_beSvSlotXbox_metaObject;
extern "C" int g_beSvSlotXbox_vtable[4];
extern "C" igMetaObject *g_beSvSlotData_metaObject;
extern "C" igMetaObject *beSvSlotData_GetMetaObject(void);
extern "C" igMetaObject *beSaveMemoryObj_GetMetaObject(void);
extern "C" int g_beSaveMemoryObj_vtable[4];
extern "C" igMetaObject *g_beSaveDataDeliver_metaObject;
extern "C" igMetaObject *beSaveDataDeliver_GetMetaObject(void);
extern "C" int g_beSaveDataDeliver_vtable[4];
extern "C" igMetaObject *g_beSvDeliver_metaObject;
extern "C" igMetaObject *beSvDeliver_GetMetaObject(void);
extern "C" int g_beSvDeliver_vtable[4];
extern "C" igMetaObject *g_beResetNode_metaObject;
extern "C" int g_beResetNode_vtable[4];
extern "C" igMetaObject *igGroup_GetPublishedMetaObject(void);
extern "C" int g_bePoint01Info_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beGroupKeepList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" int g_bePoint01_vtable[4];
extern "C" igMetaObject *g_beParticleCtrl2InfoRam_metaObject;
extern "C" int g_beParticleCtrl2InfoRam_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beParticleCtrl2InfoWork_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_beParticleCtrl2InfoWork_metaObject;
extern "C" int g_beParticleCtrl2InfoWork_vtable[4];
extern "C" int g_beParticleCtrl2Info_vtable[4];
extern "C" int g_beParticleCtrl2_vtable[4];
extern "C" int g_bePadManager_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_bePadDataList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beKeyboardReceiver_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_bePadDataList_metaObject;
extern "C" int g_bePadDataList_vtable[4];
extern "C" int g_bePadData_vtable[4];
extern "C" igMetaObject *g_beOptInfo_metaObject;
extern "C" igMetaObject *beOptInfo_GetMetaObject(void);
extern "C" int g_beOptInfo_vtable[4];
extern "C" igMetaObject *g_beNumberCtrlInfoWork_metaObject;
extern "C" igMetaObject *beNumberCtrlInfoWork_GetMetaObject(void);
extern "C" int g_beNumberCtrlInfoWork_vtable[4];
extern "C" igMetaObject *g_beNumberCtrlInfoRam_metaObject;
extern "C" igMetaObject *beNumberCtrlInfoRam_GetMetaObject(void);
extern "C" int g_beNumberCtrlInfoRam_vtable[4];
extern "C" igMetaObject *g_beNumVerDataList_metaObject;
extern "C" igMetaObject *beNumVerDataList_GetMetaObject(void);
extern "C" int g_beNumVerDataList_vtable[4];
extern "C" igMetaObject *g_beNumVerData_metaObject;
extern "C" int g_beNumVerData_vtable[4];
extern "C" igMetaObject *g_beNumVerInsideDataList_metaObject;
extern "C" int g_beNumVerInsideDataList_vtable[4];
extern "C" igMetaObject *g_beNumVerInsideData_metaObject;
extern "C" int g_beNumVerInsideData_vtable[4];
extern "C" igMetaObject *g_beNumberCtrlInfoList_metaObject;
extern "C" int g_beNumberCtrlInfoList_vtable[4];
extern "C" int g_beNumberCtrlInfo_vtable[4];
extern "C" int g_beNumberCtrl_vtable[4];
extern "C" int g_beLoadingNode_vtable[4];
extern "C" int g_igGroup_vtable[4];
extern "C" int g_beNodeAnim_vtable[4];
extern "C" igMetaObject *g_beNodeAnim_metaObject;
extern "C" int g_beMovieInfo_vtable[4];
extern "C" int g_beMovieInfoData_vtable[4];
extern "C" igMetaObject *beMovie_GetMetaObject(void);
extern "C" int g_beMovie_vtable[4];
extern "C" igMetaObject *g_beModelCtrlSubCom_metaObject;
extern "C" igMetaObject *beModelCtrlSubCom_GetMetaObject(void);
extern "C" int g_beModelCtrlSubCom_vtable[4];
extern "C" igMetaObject *beModelCtrlSCSound_GetMetaObject(void);
extern "C" int g_beModelCtrlSCSound_vtable[4];
extern "C" igMetaObject *beModelCtrlSCHitBox_GetMetaObject(void);
extern "C" int g_beModelCtrlSCHitBox_vtable[4];
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
            if (count == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
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
extern "C" int g_beModelCtrlInfoRideOn3_vtable[4];
struct RideOn3Vtable { RideOn3Vtable(int **slot) { *slot = g_beModelCtrlInfoRideOn3_vtable; } };
struct RideOn3View : RideOnView, RideOn3Vtable {
    float worldPosition[3];                 /* +84 */
    float minSpeed, maxSpeed;               /* +96 */
    float minKyori, maxKyori;               /* +104 */
    RideOn3View() : RideOn3Vtable(&vtable) { }
    ~RideOn3View() { vtable = g_beModelCtrlInfoRideOn3_vtable; }
};
extern "C" int g_beModelCtrlInfoRideOn2_vtable[4];
struct RideOn2Vtable { RideOn2Vtable(int **slot) { *slot = g_beModelCtrlInfoRideOn2_vtable; } };
struct RideOn2View : RideOnView, RideOn2Vtable {
    float vector[3];                        /* +84 */
    RideOn2View() : RideOn2Vtable(&vtable) { }
    ~RideOn2View() { vtable = g_beModelCtrlInfoRideOn2_vtable; }
};
extern "C" igMetaObject *g_beModelCtrlInfoRideOn_metaObject;
extern "C" igMetaObject *g_beModelCtrlInfoAI_metaObject;
extern "C" int g_beModelCtrlInfoAI_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoHitBody_metaObject;
extern "C" int g_beModelCtrlInfoHitBody_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMoveObjectList_metaObject;
extern "C" igMetaObject *beModelCtrlMoveObjectList_GetMetaObject(void);
extern "C" int g_beModelCtrlMoveObjectList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlMoveObject_metaObject;
extern "C" igMetaObject *beModelCtrlMoveObject_GetMetaObject(void);
extern "C" int g_beModelCtrlMoveObject_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoList_metaObject;
extern "C" igMetaObject *beModelCtrlInfoList_GetMetaObject(void);
extern "C" int g_beModelCtrlInfoList_vtable[4];
extern "C" igMetaObject *beModelCtrlInfo_GetMetaObject(void);
extern "C" int g_beModelCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoRamData_metaObject;
extern "C" int g_beModelCtrlInfoRamData_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoWork_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_beModelCtrlInfoDataTrc_metaObject;
extern "C" int g_beModelCtrlInfoDataTrc_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataSeq_metaObject;
extern "C" int g_beModelCtrlInfoDataSeq_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataHit_metaObject;
extern "C" int g_beModelCtrlInfoDataHit_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataAIH_metaObject;
extern "C" int g_beModelCtrlInfoDataAIH_vtable[4];
extern "C" igMetaObject *g_beModelCtrlInfoDataAIM_metaObject;
extern "C" int g_beModelCtrlInfoDataAIM_vtable[4];
extern "C" igMetaObject *g_beModelCtrlAIMapList_metaObject;
extern "C" int g_beModelCtrlAIMapList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlAIMap_metaObject;
extern "C" int g_beModelCtrlAIMap_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beModelCtrlAIDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beModelCtrlAIDataList_metaObject;
extern "C" int g_beModelCtrlAIDataList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlAIData_metaObject;
extern "C" int g_beModelCtrlAIData_vtable[4];
extern "C" igMetaObject *beModelCtrlHITBOX_GetMetaObject(void);
extern "C" int g_beModelCtrlHITBOX_vtable[4];
extern "C" igMetaObject *beModelCtrlMUTEKI_GetMetaObject(void);
extern "C" int g_beModelCtrlMUTEKI_vtable[4];
extern "C" igMetaObject *beModelCtrlAIMAP_GetMetaObject(void);
extern "C" int g_beModelCtrlAIMAP_vtable[4];
extern "C" igMetaObject *beModelCtrlWCHECK_GetMetaObject(void);
extern "C" int g_beModelCtrlWCHECK_vtable[4];
extern "C" int g_beModelCtrlPDMOVE_vtable[4];
extern "C" int g_beModelCtrlMOVERL_vtable[4];
extern "C" int g_beModelCtrlMOVEEX_vtable[4];
extern "C" int g_beModelCtrlMOVE_vtable[4];
extern "C" int g_beModelCtrlMSGBOX_vtable[4];
extern "C" int g_beModelCtrlCTRL_vtable[4];
extern "C" int g_beModelCtrlJUMP_vtable[4];
extern "C" int g_beModelCtrlACTION_vtable[4];
extern "C" int g_beModelCtrlLABELCTRL_vtable[4];
extern "C" int g_beModelCtrlLABEL_vtable[4];
extern "C" igMetaObject *beModelCtrlLUACALL_GetMetaObject(void);
extern "C" int g_beModelCtrlLUACALL_vtable[4];
extern "C" igMetaObject *g_beModelCtrlDataList_metaObject;
extern "C" igMetaObject *beModelCtrlDataList_GetMetaObject(void);
extern "C" int g_beModelCtrlDataList_vtable[4];
extern "C" igMetaObject *g_beModelCtrlData_metaObject;
extern "C" igMetaObject *beModelCtrlData_GetMetaObject(void);
extern "C" int g_beModelCtrlData_vtable[4];
extern "C" igMetaObject *beModelCtrl_GetMetaObject(void);
extern "C" igMetaObject *g_beMeterCtrlNode_metaObject;
extern "C" int g_beMeterCtrlNode_vtable[4];
extern "C" igMetaObject *g_beMeterCtrlInfoList_metaObject;
extern "C" int g_beMeterCtrlInfoList_vtable[4];
extern "C" int g_beMeterCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beMeterCtrlOneData_metaObject;
extern "C" int g_beMeterCtrlOneData_vtable[4];
extern "C" int g_beMeterCtrl_vtable[4];
extern "C" int g_beMessenger_vtable[4];
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
extern "C" igSmartPointer<igObject> *igSmartPointer_beMessengerDelayList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beMessengerWorkList_metaObject;
extern "C" int g_beMessengerWorkList_vtable[4];
/* Messenger class factories and their lazy-registration wrappers. Each factory makes sure the
 * class is registered, reloads the class handle and creates an instance from the caller's
 * allocator. */

/* Structural ABI view of the static-init callback list the registrars return; never defined here. */
struct StaticInitCallbacks;
extern "C" igMetaObject *g_beMessengerWork_metaObject;
extern "C" int g_beMessengerWork_vtable[4];
extern "C" igMetaObject *g_beMessengerGroupList_metaObject;
extern "C" int g_beMessengerGroupList_vtable[4];
extern "C" igMetaObject *g_beMessengerGroup_metaObject;
extern "C" int g_beMessengerGroup_vtable[4];
extern "C" igMetaObject *g_beMessengerDelayList_metaObject;
extern "C" igMetaObject *beMessengerDelayList_GetMetaObject(void);
extern "C" int g_beMessengerDelayList_vtable[4];
extern "C" igMetaObject *g_beMessengerDelay_metaObject;
extern "C" igMetaObject *beMessengerDelay_GetMetaObject(void);
extern "C" int g_beMessengerDelay_vtable[4];
extern "C" igMetaObject *g_beMessengerArgDataList_metaObject;
extern "C" igMetaObject *beMessengerArgDataList_GetMetaObject(void);
extern "C" int g_beMessengerArgDataList_vtable[4];
extern "C" igMetaObject *g_beMessengerArgData_metaObject;
extern "C" igMetaObject *beMessengerArgData_GetMetaObject(void);
extern "C" int g_beMessengerArgData_vtable[4];
extern "C" int g_beMemory_vtable[4];
extern "C" igMetaObject *g_beMatCtrlInfoWork_metaObject;
extern "C" int g_beMatCtrlInfoWork_vtable[4];
extern "C" igMetaObject *g_beMatCtrlInfoRam_metaObject;
extern "C" int g_beMatCtrlInfoRam_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beMatCtrlInfoWork_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" int g_beMatCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beMatCtrlSearchList_metaObject;
extern "C" int g_beMatCtrlSearchList_vtable[4];
extern "C" igMetaObject *g_beMatCtrlSearch_metaObject;
extern "C" int g_beMatCtrlSearch_vtable[4];
extern "C" igMetaObject *g_beMatCtrlDataList_metaObject;
extern "C" int g_beMatCtrlDataList_vtable[4];
extern "C" igMetaObject *g_beMatCtrlData_metaObject;
extern "C" int g_beMatCtrlData_vtable[4];
extern "C" int g_beMatCtrl_vtable[4];
extern "C" int g_beLuaState_vtable[4];
extern "C" int g_igLuaState_vtable[4];
extern "C" igMetaObject *beLuaInfo_GetMetaObject(void);
extern "C" int g_beLuaInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beLuaDataList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_beLuaDataList_metaObject;
extern "C" igMetaObject *beLuaDataList_GetMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
extern "C" int g_beLuaDataList_vtable[4];
extern "C" igMetaObject *g_beLuaData_metaObject;
extern "C" igMetaObject *beLuaData_GetMetaObject(void);
extern "C" int g_beLuaData_vtable[4];
extern "C" igMetaObject *g_beLuaDataObjectist_metaObject;
extern "C" igMetaObject *beLuaDataObjectist_GetMetaObject(void);
extern "C" int g_beLuaDataObjectist_vtable[4];
extern "C" igMetaObject *g_beLuaDataObject_metaObject;
extern "C" int g_beLuaDataObject_vtable[4];
extern "C" int g_beLua_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igLuaGlue_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_igLightSetList_metaObject;
extern "C" int g_igLightSetList_vtable[4];
extern "C" int g_beLightCtrlInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igLightSetList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" int g_beLightCtrl_vtable[4];
extern "C" igMetaObject *g_beLayerInfoRam_metaObject;
extern "C" int g_beLayerInfoRam_vtable[4];
extern "C" int g_beLayerInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beLayerGroupList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_beLayerGroupList_metaObject;
extern "C" int g_beLayerGroupList_vtable[4];
extern "C" igMetaObject *g_beLayerGroup_metaObject;
extern "C" int g_beLayerGroup_vtable[4];
extern "C" int g_beLayerCtl_vtable[4];
extern "C" igMetaObject *g_beLOA_metaObject;
extern "C" int g_beLOA_vtable[4];
extern "C" igMetaObject *beKeyboardReceiver_GetMetaObject(void);
extern "C" int g_beKeyboardReceiver_vtable[4];
extern "C" igMetaObject *igEventReceiver_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_beHitLandModelInfoRam_metaObject;
extern "C" igMetaObject *beHitLandModelInfoRam_GetMetaObject(void);
extern "C" int g_beHitLandModelInfoRam_vtable[4];
extern "C" igMetaObject *beHitLandModelInfo_GetMetaObject(void);
extern "C" int g_beHitLandModelInfo_vtable[4];
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
extern "C" int g_beHitLandModelTraversal_vtable[4];
extern "C" int g_beHitLandModelOrder_vtable[4];
extern "C" igMetaObject *g_beHitLandResultDataList_metaObject;
extern "C" int g_beHitLandResultDataList_vtable[4];
extern "C" igMetaObject *g_beHitLandResultData_metaObject;
extern "C" int g_beHitLandResultData_vtable[4];
extern "C" igMetaObject *g_beHitLandDelivInfoRam_metaObject;
extern "C" int g_beHitLandDelivInfoRam_vtable[4];
extern "C" int g_beHitLandDelivInfo_vtable[4];
extern "C" int g_beHitLandDeliv_vtable[4];
extern "C" igMetaObject *g_beGroupKeepList_metaObject;
extern "C" int g_beGroupKeepList_vtable[4];
extern "C" igMetaObject *g_beGroupKeep_metaObject;
extern "C" int g_beGroupKeep_vtable[4];
extern "C" igMetaObject *g_beGeneraterInfoWork_metaObject;
extern "C" igMetaObject *beGeneraterInfoWork_GetMetaObject(void);
extern "C" int g_beGeneraterInfoWork_vtable[4];
extern "C" igMetaObject *g_beGeneraterInfoRam_metaObject;
extern "C" igMetaObject *beGeneraterInfoRam_GetMetaObject(void);
extern "C" int g_beGeneraterInfoRam_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beGeneraterInfoWork_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *beGeneraterInfo_GetMetaObject(void);
extern "C" int g_beGeneraterInfo_vtable[4];
extern "C" igMetaObject *g_beGeneraterDataList_metaObject;
extern "C" igMetaObject *beGeneraterDataList_GetMetaObject(void);
extern "C" int g_beGeneraterDataList_vtable[4];
extern "C" igMetaObject *g_beGeneraterData_metaObject;
extern "C" int g_beGeneraterData_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beGeneraterPlayerDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beGeneraterPlayerDataList_metaObject;
extern "C" int g_beGeneraterPlayerDataList_vtable[4];
extern "C" igMetaObject *g_beGeneraterPlayerData_metaObject;
extern "C" int g_beGeneraterPlayerData_vtable[4];
extern "C" igMetaObject *g_beGeneraterItemDataList_metaObject;
extern "C" int g_beGeneraterItemDataList_vtable[4];
extern "C" igMetaObject *g_beGeneraterItemData_metaObject;
extern "C" int g_beGeneraterItemData_vtable[4];
extern "C" igMetaObject *g_beGeneraterItemDataOneList_metaObject;
extern "C" int g_beGeneraterItemDataOneList_vtable[4];
extern "C" igMetaObject *g_beGeneraterItemDataOne_metaObject;
extern "C" int g_beGeneraterItemDataOne_vtable[4];
extern "C" int g_beGenerater_vtable[4];
extern "C" int g_beFontInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beUnicodeObjList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_beFontInfoData_metaObject;
extern "C" int g_beFontInfoData_vtable[4];
extern "C" igMetaObject *g_beUnicodeObjList_metaObject;
extern "C" igMetaObject *beUnicodeObjList_GetMetaObject(void);
extern "C" int g_beUnicodeObjList_vtable[4];
extern "C" igMetaObject *beUnicodeObj_GetMetaObject(void);
extern "C" int g_beUnicodeObj_vtable[4];
extern "C" igMetaObject *g_beFontImageList_metaObject;
extern "C" igMetaObject *beFontImageList_GetMetaObject(void);
extern "C" int g_beFontImageList_vtable[4];
extern "C" igMetaObject *g_beFontImage_metaObject;
extern "C" igMetaObject *beFontImage_GetMetaObject(void);
extern "C" int g_beFontImage_vtable[4];
extern "C" int g_igFont_vtable[4];
extern "C" int g_igBitmapFont_vtable[4];
extern "C" igBitmapFont *igBitmapFont_Destroy(igBitmapFont *self, short delete_storage);
extern "C" int g_beFont_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beFontImageList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igMetaObject *g_beFontGeomAttrPairList_metaObject;
extern "C" int g_beFontGeomAttrPairList_vtable[4];
extern "C" igMetaObject *g_beFontGeomAttrPair_metaObject;
extern "C" int g_beFontGeomAttrPair_vtable[4];
extern "C" int g_beFileListInfoManager_vtable[4];
extern "C" int g_beFileListInfo_vtable[4];
extern "C" igMetaObject *g_beFile_metaObject;
extern "C" int g_beFile_vtable[4];
extern "C" igMetaObject *g_beFileChkObj_metaObject;
extern "C" int g_beFileChkObj_vtable[4];
extern "C" int g_beDemoManager_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beDemoManagerWork_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beDemoManagerWorkList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beDemoManagerWorkList_metaObject;
extern "C" int g_beDemoManagerWorkList_vtable[4];
extern "C" igMetaObject *g_beDemoManagerWork_metaObject;
extern "C" int g_beDemoManagerWork_vtable[4];
extern "C" igMetaObject *g_beDemoKeepMesList_metaObject;
extern "C" igMetaObject *beDemoKeepMesList_GetMetaObject(void);
extern "C" int g_beDemoKeepMesList_vtable[4];
extern "C" igMetaObject *g_beDemoKeepMes_metaObject;
extern "C" igMetaObject *beDemoKeepMes_GetMetaObject(void);
extern "C" int g_beDemoKeepMes_vtable[4];
extern "C" igMetaObject *g_beDataObjListList_metaObject;
extern "C" igMetaObject *beDataObjListList_GetMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
extern "C" int g_beDataObjListList_vtable[4];
extern "C" igMetaObject *beDataObjList_GetMetaObject(void);
extern "C" int g_beDataObjList_vtable[4];
extern "C" igMetaObject *g_beDataObjFloatList_metaObject;
extern "C" int g_beDataObjFloatList_vtable[4];
extern "C" igMetaObject *g_beDataObjObjectList_metaObject;
extern "C" int g_beDataObjObjectList_vtable[4];
extern "C" igMetaObject *g_beDataObjStringList_metaObject;
extern "C" int g_beDataObjStringList_vtable[4];
extern "C" igMetaObject *g_beDataObjString_metaObject;
extern "C" int g_beDataObjString_vtable[4];
extern "C" igMetaObject *g_beDataObjBoolList_metaObject;
extern "C" int g_beDataObjBoolList_vtable[4];
extern "C" igMetaObject *g_beDataObjBool_metaObject;
extern "C" int g_beDataObjBool_vtable[4];
extern "C" igMetaObject *g_beDataObjIntList_metaObject;
extern "C" int g_beDataObjIntList_vtable[4];
extern "C" igMetaObject *g_beDataObjInt_metaObject;
extern "C" int g_beDataObjInt_vtable[4];
extern "C" igMetaObject *g_beDataBaseList_metaObject;
extern "C" int g_beDataBaseList_vtable[4];
extern "C" igMetaObject *g_beDataBase_metaObject;
extern "C" int g_beDataBase_vtable[4];
extern "C" igMetaObject *beDBManagerInfo_GetMetaObject(void);
extern "C" int g_beDBManagerInfo_vtable[4];
extern "C" igMetaObject *beDBManager_GetMetaObject(void);
extern "C" int g_beDBManager_vtable[4];
extern "C" igMetaObject *g_beCriVolume_metaObject;
extern "C" igMetaObject *beCriVolume_GetMetaObject(void);
extern "C" int g_beCriVolume_vtable[4];
extern "C" igMetaObject *beCriSfpData_GetMetaObject(void);
extern "C" int g_beCriSfpData_vtable[4];
extern "C" igMetaObject *g_beCriHandleList_metaObject;
extern "C" int g_beCriHandleList_vtable[4];
extern "C" igMetaObject *g_beCriHandle_metaObject;
extern "C" int g_beCriHandle_vtable[4];
extern "C" int g_beCriFxInfo_vtable[4];
extern "C" igMetaObject *g_beCriFxXbData_metaObject;
extern "C" int g_beCriFxXbData_vtable[4];
extern "C" igMetaObject *g_beCriAudio_metaObject;
extern "C" int g_beCriAudio_vtable[4];
extern "C" igMetaObject *g_beCriSndf_metaObject;
extern "C" int g_beCriSndf_vtable[4];
extern "C" int g_beCriAcxData_vtable[4];
extern "C" int g_beCri_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beCriHandleList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beCountry_metaObject;
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
extern "C" int g_beChangePosTransformInfoRam_vtable[4];
extern "C" igMetaObject *beChangePosTransformInfo_GetMetaObject(void);
extern "C" int g_beChangePosTransformInfo_vtable[4];
extern "C" igMetaObject *beChangePosTransform_GetMetaObject(void);
extern "C" int g_beChangePosTransform_vtable[4];
extern "C" int g_beCameraMode_vtable[4];
extern "C" int g_igViewMode_vtable[4];
extern "C" int g_beCameraCtrlInfo_vtable[4];
extern "C" int g_igObject_metaObject[4];
extern "C" int g_beCameraDemoData_vtable[4];
extern "C" int g_beCameraBoxData_vtable[4];
extern "C" igMetaObject *g_beCameraCtrlInfoRamShake_metaObject;
extern "C" int g_beCameraCtrlInfoRamShake_vtable[4];
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
extern "C" int g_beBkColorInfo_vtable[4];
extern "C" int g_beBkColor_vtable[4];
extern "C" igMetaObject *g_beBaseInfoRamList_metaObject;
extern "C" int g_beBaseInfoRamList_vtable[4];
extern "C" igMetaObject *g_beBaseInfoRam_metaObject;
extern "C" int g_beBaseInfoRamTimer_vtable[4];
extern "C" igMetaObject *g_beBaseInfoManagerList_metaObject;
extern "C" igMetaObject *beBaseInfoManagerList_GetMetaObject(void);
extern "C" int g_beBaseInfoManagerList_vtable[4];
extern "C" igMetaObject *beBaseInfoManager_GetMetaObject(void);
extern "C" igMetaObject *g_beBaseInfoList_metaObject;
extern "C" igMetaObject *beBaseInfoList_GetMetaObject(void);
extern "C" int g_beBaseInfoList_vtable[4];
extern "C" igMetaObject *g_beBaseInfo_metaObject;
extern "C" igMetaObject *beBaseInfo_GetMetaObject(void);
extern "C" igMetaObject *g_beBaseInfoDataList_metaObject;
extern "C" int g_beBaseInfoDataList_vtable[4];
extern "C" igMetaObject *g_beBaseInfoData_metaObject;
extern "C" igMetaObject *g_beActionStarterInfoRam_metaObject;
extern "C" int g_beActionStarterInfoRam_vtable[4];
extern "C" int g_beActionStarterInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beAsTargetModelDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage);
extern "C" igMetaObject *g_beAsTargetModelDataList_metaObject;
extern "C" int g_beAsTargetModelDataList_vtable[4];
extern "C" igMetaObject *g_beAsTargetModelData_metaObject;
extern "C" int g_beAsTargetModelData_vtable[4];
extern "C" int g_beActionStarterData2_vtable[4];
extern "C" int g_beActionStarterData_vtable[4];
extern "C" igMetaObject *g_beActionStarterDataList_metaObject;
extern "C" int g_beActionStarterDataList_vtable[4];
extern "C" igMetaObject *g_beActionStarterData_metaObject;
extern "C" int g_beActionStarter_vtable[4];
extern "C" igMetaObject *g_beAction2InfoWork_metaObject;
extern "C" igMetaObject *beAction2InfoWork_GetMetaObject(void);
extern "C" int g_beAction2InfoWork_vtable[4];
extern "C" igMetaObject *g_beAction2InfoRam_metaObject;
extern "C" igMetaObject *beAction2InfoRam_GetMetaObject(void);
extern "C" int g_beAction2InfoRam_vtable[4];
extern "C" igMetaObject *g_beAction2InfoList_metaObject;
extern "C" igMetaObject *beAction2InfoList_GetMetaObject(void);
extern "C" int g_beAction2InfoList_vtable[4];
extern "C" igMetaObject *beAction2Info_GetMetaObject(void);
extern "C" int g_beAction2Info_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beAction2DataList_Destruct(igSmartPointer<igObject> *self, int delete_storage);
extern "C" int g_beAction2FLASHSET_vtable[4];
extern "C" int g_beAction2WAITCHECK_vtable[4];
extern "C" int g_beAction2FADESET_vtable[4];
extern "C" int g_beAction2JOINTSET_vtable[4];
extern "C" int g_beAction2MOTIONSET_vtable[4];
extern "C" igMetaObject *g_beAction2DataList_metaObject;
extern "C" int g_beAction2DataList_vtable[4];
extern "C" igMetaObject *g_beAction2Data_metaObject;
extern "C" int g_beAction2Data_vtable[4];
extern "C" int g_beAction2_vtable[4];
extern "C" int g_be_vtable[4];
extern "C" int g_ParticleArray_vtable[4];
extern "C" igMetaObject *igParticleArray_GetPublishedMetaObject(void);
extern "C" int g_ParticleTimer_vtable[4];
extern "C" igMetaObject *igGeometry_GetPublishedMetaObject(void);
extern "C" igMetaObject *ParticleInfo_GetMetaObject(void);
extern "C" int g_ParticleInfo_vtable[4];
extern "C" void beBinDataObject_userDestruct(beBinDataObject *self);
// clang-format off
extern "C" void beLuaDataObject_userDestruct(beLuaDataObject *self);
extern "C" void beNumVerData_userConstruct(beNumVerData *self, int flag);
extern "C" void beNumVerData_userDestruct(beNumVerData *self);
extern "C" void beSaveDataDeliver_userDestruct(beSaveDataDeliver *self);
extern "C" void beSvPlatDataGC_userDestruct(beSvPlatDataGC *self);
extern "C" void beSvPs2McImage128k_userConstruct(beSvPs2McImage128k *self, int flag);
extern "C" void beXboxImage24k_userConstruct(beXboxImage24k *self, int flag);
extern "C" void beXboxImage24k_userDestruct(beXboxImage24k *self);
extern "C" void beTransformSync_SetMatrix(beTransformSync *self, const float *matrix);

#endif
