igMetaObject *Gap__Bec__ParticleInfo__vfunc_20(void)
{
    return g_ParticleInfo_metaObject;
}

/* Runs the igObject base step, then (when `clearControls` is set) zeroes the particle control
 * data: `_points` (192 words) and `_numControls` (32 words). */
void Gap__Bec__ParticleInfo__vfunc_11(ParticleInfo *self, int clearControls) {
    Gap__Core__igObject__resetFields();
    if (clearControls != 0) {
        memset((int)self->_points, 0, sizeof(self->_points));
        memset((int)self->_numControls, 0, sizeof(self->_numControls));
    }
}

igMetaObject *Gap__Bec__beAction2Data__vfunc_20(void)
{
    return g_beAction2Data_metaObject;
}

igMetaObject *Gap__Bec__beAction2DataList__vfunc_20(void)
{
    return g_beAction2DataList_metaObject;
}

igMetaObject *Gap__Bec__beAction2MOTIONSET__vfunc_20(void)
{
    return g_beAction2MOTIONSET_metaObject;
}

igMetaObject *Gap__Bec__beAction2JOINTSET__vfunc_20(void)
{
    return g_beAction2JOINTSET_metaObject;
}

igMetaObject *Gap__Bec__beAction2FADESET__vfunc_20(void)
{
    return g_beAction2FADESET_metaObject;
}

igMetaObject *Gap__Bec__beAction2WAITCHECK__vfunc_20(void)
{
    return g_beAction2WAITCHECK_metaObject;
}

igMetaObject *Gap__Bec__beAction2FLASHSET__vfunc_20(void)
{
    return g_beAction2FLASHSET_metaObject;
}

igMetaObject *Gap__Bec__beAction2Info__vfunc_20(void)
{
    return g_beAction2Info_metaObject;
}

igMetaObject *Gap__Bec__beAction2InfoList__vfunc_20(void)
{
    return g_beAction2InfoList_metaObject;
}

igMetaObject *Gap__Bec__beAction2InfoRam__vfunc_20(void)
{
    return g_beAction2InfoRam_metaObject;
}

igMetaObject *Gap__Bec__beAction2InfoWork__vfunc_20(void)
{
    return g_beAction2InfoWork_metaObject;
}

igMetaObject *Gap__Bec__beActionStarterDataList__vfunc_20(void)
{
    return g_beActionStarterDataList_metaObject;
}

igMetaObject *Gap__Bec__beActionStarterData2__vfunc_20(void)
{
    return g_beActionStarterData2_metaObject;
}

igMetaObject *Gap__Bec__beActionStarterData__vfunc_20(void)
{
    return g_beActionStarterData_metaObject;
}

igMetaObject *Gap__Bec__beAsTargetModelData__vfunc_20(void)
{
    return g_beAsTargetModelData_metaObject;
}

igMetaObject *Gap__Bec__beAsTargetModelDataList__vfunc_20(void)
{
    return g_beAsTargetModelDataList_metaObject;
}

igMetaObject *Gap__Bec__beActionStarterInfo__vfunc_20(void)
{
    return g_beActionStarterInfo_metaObject;
}

igMetaObject *Gap__Bec__beActionStarterInfoRam__vfunc_20(void)
{
    return g_beActionStarterInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoDataList__vfunc_20(void)
{
    return g_beBaseInfoDataList_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoList__vfunc_20(void)
{
    return g_beBaseInfoList_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoManagerList__vfunc_20(void)
{
    return g_beBaseInfoManagerList_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoRamTimer__vfunc_20(void)
{
    return g_beBaseInfoRamTimer_metaObject;
}

igMetaObject *beBaseInfoRamList_GetMetaObject_Virtual(void)
{
    return g_beBaseInfoRamList_metaObject;
}

igMetaObject *Gap__Bec__beBkColorInfo__vfunc_20(void)
{
    return g_beBkColorInfo_metaObject;
}

igMetaObject *Gap__Bec__beCameraCtrlInfoRamShake__vfunc_20(void)
{
    return g_beCameraCtrlInfoRamShake_metaObject;
}

igMetaObject *Gap__Bec__beCameraBoxData__vfunc_20(void)
{
    return g_beCameraBoxData_metaObject;
}

igMetaObject *Gap__Bec__beCameraDemoData__vfunc_20(void)
{
    return g_beCameraDemoData_metaObject;
}

igMetaObject *Gap__Bec__beCameraCtrlInfo__vfunc_20(void)
{
    return g_beCameraCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beChangePosTransformInfo__vfunc_20(void)
{
    return g_beChangePosTransformInfo_metaObject;
}

igMetaObject *Gap__Bec__beChangePosTransformInfoRam__vfunc_20(void)
{
    return g_beChangePosTransformInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beCopyModelCtrl2__vfunc_20(void)
{
    return g_beCopyModelCtrl2_metaObject;
}

igMetaObject *Gap__Bec__beCopyTransform__vfunc_20(void)
{
    return g_beCopyTransform_metaObject;
}

igMetaObject *Gap__Bec__beCountry__vfunc_20(void)
{
    return g_beCountry_metaObject;
}

igMetaObject *Gap__Bec__beCriAcxData__vfunc_20(void)
{
    return g_beCriAcxData_metaObject;
}

void Gap__Bec__beBinDataObject__vfunc_8(beBinDataObject *arg0) {
    if (arg0->_dataBuffer != 0) {
        Memory_FreeBuffer((void *)arg0->_dataBuffer);
        arg0->_dataBuffer = 0;
    }
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *Gap__Bec__beCriSndf__vfunc_20(void)
{
    return g_beCriSndf_metaObject;
}

igMetaObject *Gap__Bec__beCriAudio__vfunc_20(void)
{
    return g_beCriAudio_metaObject;
}

igMetaObject *Gap__Bec__beCriFxXbData__vfunc_20(void)
{
    return g_beCriFxXbData_metaObject;
}

igMetaObject *Gap__Bec__beCriFxInfo__vfunc_20(void)
{
    return g_beCriFxInfo_metaObject;
}

igMetaObject *Gap__Bec__beCriHandle__vfunc_20(void)
{
    return g_beCriHandle_metaObject;
}

igMetaObject *Gap__Bec__beCriHandleList__vfunc_20(void)
{
    return g_beCriHandleList_metaObject;
}

igMetaObject *Gap__Bec__beCriSfpData__vfunc_20(void)
{
    return g_beCriSfpData_metaObject;
}

igMetaObject *Gap__Bec__beCriVolume__vfunc_20(void)
{
    return g_beCriVolume_metaObject;
}

igMetaObject *Gap__Bec__beDBManagerInfo__vfunc_20(void)
{
    return g_beDBManagerInfo_metaObject;
}

igMetaObject *Gap__Bec__beDataBase__vfunc_20(void) { return g_beDataBase_metaObject; }

igMetaObject *Gap__Bec__beDataBaseList__vfunc_20(void)
{
    return g_beDataBaseList_metaObject;
}

igMetaObject *Gap__Bec__beDataObjInt__vfunc_20(void)
{
    return g_beDataObjInt_metaObject;
}

igMetaObject *Gap__Bec__beDataObjIntList__vfunc_20(void)
{
    return g_beDataObjIntList_metaObject;
}

igMetaObject *Gap__Bec__beDataObjBool__vfunc_20(void)
{
    return g_beDataObjBool_metaObject;
}

igMetaObject *Gap__Bec__beDataObjBoolList__vfunc_20(void)
{
    return g_beDataObjBoolList_metaObject;
}

igMetaObject *Gap__Bec__beDataObjString__vfunc_20(void)
{
    return g_beDataObjString_metaObject;
}

igMetaObject *Gap__Bec__beDataObjStringList__vfunc_20(void)
{
    return g_beDataObjStringList_metaObject;
}

igMetaObject *Gap__Bec__beDataObjObjectList__vfunc_20(void)
{
    return g_beDataObjObjectList_metaObject;
}

igMetaObject *Gap__Bec__beDataObjFloatList__vfunc_20(void)
{
    return g_beDataObjFloatList_metaObject;
}

igMetaObject *Gap__Bec__beDataObjList__vfunc_20(void)
{
    return g_beDataObjList_metaObject;
}

igMetaObject *Gap__Bec__beDataObjListList__vfunc_20(void)
{
    return g_beDataObjListList_metaObject;
}

igMetaObject *Gap__Bec__beDemoKeepMes__vfunc_20(void)
{
    return g_beDemoKeepMes_metaObject;
}

igMetaObject *Gap__Bec__beDemoKeepMesList__vfunc_20(void)
{
    return g_beDemoKeepMesList_metaObject;
}

igMetaObject *Gap__Bec__beDemoManagerWork__vfunc_20(void)
{
    return g_beDemoManagerWork_metaObject;
}

igMetaObject *Gap__Bec__beDemoManagerWorkList__vfunc_20(void)
{
    return g_beDemoManagerWorkList_metaObject;
}

igMetaObject *Gap__Bec__beFileChkObj__vfunc_20(void)
{
    return g_beFileChkObj_metaObject;
}

igMetaObject *Gap__Bec__beFile__vfunc_20(void)
{
    return g_beFile_metaObject;
}

igMetaObject *Gap__Bec__beFileListInfo__vfunc_20(void)
{
    return g_beFileListInfo_metaObject;
}

igMetaObject *Gap__Bec__beFontGeomAttrPair__vfunc_20(void)
{
    return g_beFontGeomAttrPair_metaObject;
}

igMetaObject *Gap__Bec__beFontGeomAttrPairList__vfunc_20(void)
{
    return g_beFontGeomAttrPairList_metaObject;
}

igMetaObject *Gap__Bec__beFontImage__vfunc_20(void)
{
    return g_beFontImage_metaObject;
}

int Gap__Gui__igFont__vfunc_20(void)
{
    return g_igFont_metaObject[0];
}

igMetaObject *Gap__Bec__beFontImageList__vfunc_20(void)
{
    return g_beFontImageList_metaObject;
}

igMetaObject *Gap__Bec__beUnicodeObjList__vfunc_20(void)
{
    return g_beUnicodeObjList_metaObject;
}

igMetaObject *Gap__Bec__beFontInfoData__vfunc_20(void)
{
    return g_beFontInfoData_metaObject;
}

igMetaObject *Gap__Bec__beFontInfo__vfunc_20(void)
{
    return g_beFontInfo_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterItemDataOne__vfunc_20(void)
{
    return g_beGeneraterItemDataOne_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterItemDataOneList__vfunc_20(void)
{
    return g_beGeneraterItemDataOneList_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterItemData__vfunc_20(void)
{
    return g_beGeneraterItemData_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterItemDataList__vfunc_20(void)
{
    return g_beGeneraterItemDataList_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterPlayerData__vfunc_20(void)
{
    return g_beGeneraterPlayerData_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterPlayerDataList__vfunc_20(void)
{
    return g_beGeneraterPlayerDataList_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterData__vfunc_20(void)
{
    return g_beGeneraterData_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterDataList__vfunc_20(void)
{
    return g_beGeneraterDataList_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterInfo__vfunc_20(void)
{
    return g_beGeneraterInfo_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterInfoRam__vfunc_20(void)
{
    return g_beGeneraterInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterInfoWork__vfunc_20(void)
{
    return g_beGeneraterInfoWork_metaObject;
}

igMetaObject *Gap__Bec__beGroupKeep__vfunc_20(void)
{
    return g_beGroupKeep_metaObject;
}

igMetaObject *Gap__Bec__beGroupKeepList__vfunc_20(void)
{
    return g_beGroupKeepList_metaObject;
}

igMetaObject *Gap__Bec__beHitLandDelivInfo__vfunc_20(void)
{
    return g_beHitLandDelivInfo_metaObject;
}

igMetaObject *Gap__Bec__beHitLandDelivInfoRam__vfunc_20(void)
{
    return g_beHitLandDelivInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beHitLandResultData__vfunc_20(void)
{
    return g_beHitLandResultData_metaObject;
}

igMetaObject *Gap__Bec__beHitLandResultDataList__vfunc_20(void)
{
    return g_beHitLandResultDataList_metaObject;
}

igMetaObject *Gap__Bec__beHitLandModelTraversal__vfunc_20(void)
{
    return g_beHitLandModelTraversal_metaObject;
}

igMetaObject *Gap__Bec__beHitLandModelInfo__vfunc_20(void)
{
    return g_beHitLandModelInfo_metaObject;
}

igMetaObject *Gap__Bec__beHitLandModelInfoRam__vfunc_20(void)
{
    return g_beHitLandModelInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beLOA__vfunc_20(void)
{
    return g_beLOA_metaObject;
}

igMetaObject *Gap__Bec__beLayerGroup__vfunc_20(void)
{
    return g_beLayerGroup_metaObject;
}

igMetaObject *Gap__Bec__beLayerGroupList__vfunc_20(void)
{
    return g_beLayerGroupList_metaObject;
}

igMetaObject *Gap__Bec__beLayerInfo__vfunc_20(void)
{
    return g_beLayerInfo_metaObject;
}

igMetaObject *Gap__Bec__beLayerInfoRam__vfunc_20(void)
{
    return g_beLayerInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beLightCtrlInfo__vfunc_20(void)
{
    return g_beLightCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__igLightSetList__vfunc_20(void)
{
    return g_igLightSetList_metaObject;
}

igMetaObject *Gap__Bec__beLuaDataObject__vfunc_20(void)
{
    return g_beLuaDataObject_metaObject;
}

void Gap__Bec__beLuaDataObject__vfunc_08(beLuaDataObject *arg0) {
    int temp_a0;

    temp_a0 = arg0->_data;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->_data = 0;
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *Gap__Bec__beLuaDataObjectist__vfunc_20(void)
{
    return g_beLuaDataObjectist_metaObject;
}

igMetaObject *Gap__Bec__beLuaData__vfunc_20(void)
{
    return g_beLuaData_metaObject;
}

igMetaObject *Gap__Bec__beLuaDataList__vfunc_20(void)
{
    return g_beLuaDataList_metaObject;
}

igMetaObject *Gap__Bec__beLuaInfo__vfunc_20(void)
{
    return g_beLuaInfo_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlData__vfunc_20(void)
{
    return g_beMatCtrlData_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlDataList__vfunc_20(void)
{
    return g_beMatCtrlDataList_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlSearch__vfunc_20(void)
{
    return g_beMatCtrlSearch_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlSearchList__vfunc_20(void)
{
    return g_beMatCtrlSearchList_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlInfo__vfunc_20(void)
{
    return g_beMatCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlInfoRam__vfunc_20(void)
{
    return g_beMatCtrlInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlInfoWork__vfunc_20(void)
{
    return g_beMatCtrlInfoWork_metaObject;
}

igMetaObject *Gap__Bec__beMessengerArgData__vfunc_20(void)
{
    return g_beMessengerArgData_metaObject;
}

igMetaObject *Gap__Bec__beMessengerArgDataList__vfunc_20(void)
{
    return g_beMessengerArgDataList_metaObject;
}

igMetaObject *Gap__Bec__beMessengerDelay__vfunc_20(void)
{
    return g_beMessengerDelay_metaObject;
}

igMetaObject *Gap__Bec__beMessengerDelayList__vfunc_20(void)
{
    return g_beMessengerDelayList_metaObject;
}

igMetaObject *Gap__Bec__beMessengerGroup__vfunc_20(void)
{
    return g_beMessengerGroup_metaObject;
}

igMetaObject *Gap__Bec__beMessengerGroupList__vfunc_20(void)
{
    return g_beMessengerGroupList_metaObject;
}

igMetaObject *beMessengerWork_GetMetaObject_Virtual(void)
{
    return g_beMessengerWork_metaObject;
}

igMetaObject *Gap__Bec__beMessengerWorkList__vfunc_20(void)
{
    return g_beMessengerWorkList_metaObject;
}

igMetaObject *Gap__Bec__beMeterCtrlOneData__vfunc_20(void)
{
    return g_beMeterCtrlOneData_metaObject;
}

igMetaObject *Gap__Bec__beMeterCtrlInfo__vfunc_20(void)
{
    return g_beMeterCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beMeterCtrlInfoList__vfunc_20(void)
{
    return g_beMeterCtrlInfoList_metaObject;
}

igMetaObject *Gap__Bec__beMeterCtrlNode__vfunc_20(void)
{
    return g_beMeterCtrlNode_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlData__vfunc_20(void)
{
    return g_beModelCtrlData_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlDataList__vfunc_20(void)
{
    return g_beModelCtrlDataList_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlLUACALL__vfunc_20(void)
{
    return g_beModelCtrlLUACALL_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlLABEL__vfunc_20(void)
{
    return g_beModelCtrlLABEL_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlLABELCTRL__vfunc_20(void)
{
    return g_beModelCtrlLABELCTRL_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlACTION__vfunc_20(void)
{
    return g_beModelCtrlACTION_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlJUMP__vfunc_20(void)
{
    return g_beModelCtrlJUMP_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlCTRL__vfunc_20(void)
{
    return g_beModelCtrlCTRL_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMSGBOX__vfunc_20(void)
{
    return g_beModelCtrlMSGBOX_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMOVE__vfunc_20(void)
{
    return g_beModelCtrlMOVE_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMOVEEX__vfunc_20(void)
{
    return g_beModelCtrlMOVEEX_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMOVERL__vfunc_20(void)
{
    return g_beModelCtrlMOVERL_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlPDMOVE__vfunc_20(void)
{
    return g_beModelCtrlPDMOVE_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlWCHECK__vfunc_20(void)
{
    return g_beModelCtrlWCHECK_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlAIMAP__vfunc_20(void)
{
    return g_beModelCtrlAIMAP_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMUTEKI__vfunc_20(void)
{
    return g_beModelCtrlMUTEKI_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlHITBOX__vfunc_20(void)
{
    return g_beModelCtrlHITBOX_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlAIData__vfunc_20(void)
{
    return g_beModelCtrlAIData_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlAIDataList__vfunc_20(void)
{
    return g_beModelCtrlAIDataList_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlAIMap__vfunc_20(void)
{
    return g_beModelCtrlAIMap_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlAIMapList__vfunc_20(void)
{
    return g_beModelCtrlAIMapList_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoDataAIM__vfunc_20(void)
{
    return g_beModelCtrlInfoDataAIM_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoDataAIH__vfunc_20(void)
{
    return g_beModelCtrlInfoDataAIH_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoDataHit__vfunc_20(void)
{
    return g_beModelCtrlInfoDataHit_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoDataSeq__vfunc_20(void)
{
    return g_beModelCtrlInfoDataSeq_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoDataTrc__vfunc_20(void)
{
    return g_beModelCtrlInfoDataTrc_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoRamData__vfunc_20(void)
{
    return g_beModelCtrlInfoRamData_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfo__vfunc_20(void)
{
    return g_beModelCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoList__vfunc_20(void)
{
    return g_beModelCtrlInfoList_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMoveObject__vfunc_20(void)
{
    return g_beModelCtrlMoveObject_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMoveObjectList__vfunc_20(void)
{
    return g_beModelCtrlMoveObjectList_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoHitBody__vfunc_20(void)
{
    return g_beModelCtrlInfoHitBody_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoAI__vfunc_20(void)
{
    return g_beModelCtrlInfoAI_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoRideOn__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn_metaObject;
}

void Gap__Bec__beModelCtrlInfoRideOn__vfunc_21(void)
{
}

igMetaObject *Gap__Bec__beModelCtrlInfoWork__vfunc_20(void)
{
    return g_beModelCtrlInfoWork_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlNode2__vfunc_20(void)
{
    return g_beModelCtrlNode2_metaObject;
}

int Gap__Bec__beModelCtrlSubComBase__vfunc_24(void)
{
    return 1;
}

void Gap__Bec__beModelCtrlSCHitBox__vfunc_23(void)
{
}

igMetaObject *Gap__Bec__beModelCtrlSubCom__vfunc_20(void)
{
    return g_beModelCtrlSubCom_metaObject;
}

igMetaObject *Gap__Bec__beMovieInfoData__vfunc_20(void)
{
    return g_beMovieInfoData_metaObject;
}

igMetaObject *Gap__Bec__beMovieInfo__vfunc_20(void)
{
    return g_beMovieInfo_metaObject;
}

igMetaObject *Gap__Bec__beLoadingNode__vfunc_20(void)
{
    return g_beLoadingNode_metaObject;
}

igMetaObject *Gap__Bec__beNodeAnim__vfunc_20(void)
{
    return g_beNodeAnim_metaObject;
}

igMetaObject *Gap__Bec__beNumberCtrlInfo__vfunc_20(void)
{
    return g_beNumberCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beNumberCtrlInfoList__vfunc_20(void)
{
    return g_beNumberCtrlInfoList_metaObject;
}

igMetaObject *Gap__Bec__beNumVerInsideData__vfunc_20(void)
{
    return g_beNumVerInsideData_metaObject;
}

igMetaObject *Gap__Bec__beNumVerInsideDataList__vfunc_20(void)
{
    return g_beNumVerInsideDataList_metaObject;
}

igMetaObject *Gap__Bec__beNumVerData__vfunc_20(void)
{
    return g_beNumVerData_metaObject;
}

void Gap__Bec__beNumVerData__vfunc_07(Obj_36f970 *arg0, int arg1) {
    int i;
    void *alloc;
    Gap__Core__igObject__userConstruct(arg0, arg1);
    igMetaObject_CountInstances(arg0->v88(), 1);
    if (!(arg1 & 0xFF)) {
        i = 0;
        do {
            alloc = igObject_GetAllocator(arg0);
            alloc = (g_useOwnerAllocator != 0) ? alloc : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]));
            { Ref_36f970 sp3C(((T_36f970 *)FUN_0034de60((int)alloc)));
            ObjectList_AppendRetained(arg0->list, sp3C.p); }
            i += 1;
        } while (i < 6);
    }
}

static inline int count(const beNumVerDataList *list) { return list->_count; }

void Gap__Bec__beNumVerData__vfunc_08(Obj_36fae0 *arg0) {
    beNumVerDataList *l = (beNumVerDataList *)((beNumVerData *)arg0)->_verDataList;
    int n;
    if (count(l) > 0) {
    n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            Rel_36fae0::go(((igObject **)(l->_data + off))[0]);
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                ((int *)(l->_data + off3))[0] = 0;
                ((int *)(l->_data + off3))[1] = 0;
                ((int *)(l->_data + off3))[2] = 0;
                ((int *)(l->_data + off3))[3] = 0;
                ((int *)(l->_data + off3))[4] = 0;
                ((int *)(l->_data + off3))[5] = 0;
                ((int *)(l->_data + off3))[6] = 0;
                ((int *)(l->_data + off3))[7] = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                ((int *)(l->_data + off4))[0] = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    }
    igMetaObject_CountInstances(arg0->v88(), 1);
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *Gap__Bec__beNumVerDataList__vfunc_20(void)
{
    return g_beNumVerDataList_metaObject;
}

igMetaObject *Gap__Bec__beNumberCtrlInfoRam__vfunc_20(void)
{
    return g_beNumberCtrlInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beNumberCtrlInfoWork__vfunc_20(void)
{
    return g_beNumberCtrlInfoWork_metaObject;
}

igMetaObject *Gap__Bec__beOptInfo__vfunc_20(void)
{
    return g_beOptInfo_metaObject;
}

igMetaObject *Gap__Bec__bePadDataList__vfunc_20(void)
{
    return g_bePadDataList_metaObject;
}

igMetaObject *Gap__Bec__beParticleCtrl2Info__vfunc_20(void)
{
    return g_beParticleCtrl2Info_metaObject;
}

igMetaObject *Gap__Bec__beParticleCtrl2InfoWork__vfunc_20(void)
{
    return g_beParticleCtrl2InfoWork_metaObject;
}

igMetaObject *Gap__Bec__beParticleCtrl2InfoRam__vfunc_20(void)
{
    return g_beParticleCtrl2InfoRam_metaObject;
}

igMetaObject *Gap__Bec__bePoint01Info__vfunc_20(void)
{
    return g_bePoint01Info_metaObject;
}

igMetaObject *Gap__Bec__beResetNode__vfunc_20(void)
{
    return g_beResetNode_metaObject;
}

igMetaObject *Gap__Bec__beSvDeliver__vfunc_20(void)
{
    return g_beSvDeliver_metaObject;
}

igMetaObject *Gap__Bec__beSaveDataDeliver__vfunc_20(void)
{
    return g_beSaveDataDeliver_metaObject;
}

void Gap__Bec__beSaveDataDeliver__vfunc_07(void **arg0) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

void Gap__Bec__beSaveDataDeliver__vfunc_08(DW4VC_88_0_36fd80 *arg0) {
    int temp_a0;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->f8 = 0;
    arg0->f12 = 0;
    igMetaObject_CountInstances(arg0->vX(), 1);
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *Gap__Bec__beSvSlotXbox__vfunc_20(void)
{
    return g_beSvSlotXbox_metaObject;
}

igMetaObject *Gap__Bec__beSvSlotGC__vfunc_20(void)
{
    return g_beSvSlotGC_metaObject;
}

igMetaObject *Gap__Bec__beSvSlotPS2__vfunc_20(void)
{
    return g_beSvSlotPS2_metaObject;
}

igMetaObject *Gap__Bec__beSvSlotDataList__vfunc_20(void)
{
    return g_beSvSlotDataList_metaObject;
}

igMetaObject *Gap__Bec__beSvPlatDataGC__vfunc_20(void)
{
    return g_beSvPlatDataGC_metaObject;
}

void Gap__Bec__beSvPlatDataGC__vfunc_07(void **arg0) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

void Gap__Bec__beSvPlatDataGC__vfunc_08(beSvPlatDataGC *arg0) {
    if (arg0->_banTplData != 0) {
        Memory_FreeBuffer(arg0->_banTplData);
    }
    if (arg0->_iconTplData != 0) {
        Memory_FreeBuffer(arg0->_iconTplData);
    }
    arg0->_banTplData = 0;
    arg0->_iconTplData = 0;
    igMetaObject_CountInstances(((SvPlatDataGCVirtualSlots *)arg0)->vX(), 1);
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *Gap__Bec__beSvPs2McImage128k__vfunc_20(void)
{
    return g_beSvPs2McImage128k_metaObject;
}

void Gap__Bec__beSvPs2McImage128k__vfunc_07(beSvPs2McImage128k *arg0, int arg1) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    if (!(arg1 & 0xFF)) {
        arg0->_data = Memory_AllocateDefaultBuffer(0x20000);
    }
}

void Gap__Bec__beSvPs2McImage128k__vfunc_08(void *arg0) {
    beSvPs2McImage128k *o = (beSvPs2McImage128k *)arg0;
    if (o->_data != 0) {
        Memory_FreeBuffer(o->_data);
    }
    o->_data = 0;
    igMetaObject_CountInstances(((SvPs2McImageVirtualSlots *)(((char *)(arg0) + 0)))->vX(), 1);
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *Gap__Bec__beSvPlatDataPS2__vfunc_20(void)
{
    return g_beSvPlatDataPS2_metaObject;
}

igMetaObject *Gap__Bec__beXboxImage24k__vfunc_20(void)
{
    return g_beXboxImage24k_metaObject;
}

void Gap__Bec__beXboxImage24k__vfunc_07(beXboxImage24k *arg0, int arg1) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    if (!(arg1 & 0xFF)) {
        arg0->_data = Memory_AllocateDefaultBuffer(0x6000);
        arg0->_dataSize = 0x6000;
    }
}

void Gap__Bec__beXboxImage24k__vfunc_08(DW4VC_88_0_370070 *arg0) {
    int temp_a0;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->f8 = 0;
    igMetaObject_CountInstances(arg0->vX(), 1);
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *Gap__Bec__beSvPlatDataXbox__vfunc_20(void)
{
    return g_beSvPlatDataXbox_metaObject;
}

igMetaObject *Gap__Bec__beSvPlatDataPC__vfunc_20(void)
{
    return g_beSvPlatDataPC_metaObject;
}

igMetaObject *Gap__Bec__beSvPlatBaseData__vfunc_20(void)
{
    return g_beSvPlatBaseData_metaObject;
}

igMetaObject *Gap__Bec__beSaveUtilInfo__vfunc_20(void)
{
    return g_beSaveUtilInfo_metaObject;
}

igMetaObject *Gap__Bec__beSaveUtilInfoRam__vfunc_20(void)
{
    return g_beSaveUtilInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beSeData__vfunc_20(void)
{
    return g_beSeData_metaObject;
}

igMetaObject *Gap__Bec__beSeDataList__vfunc_20(void)
{
    return g_beSeDataList_metaObject;
}

igMetaObject *Gap__Bec__beSeInfoData__vfunc_20(void)
{
    return g_beSeInfoData_metaObject;
}

igMetaObject *Gap__Bec__beSeInfo__vfunc_20(void)
{
    return g_beSeInfo_metaObject;
}

igMetaObject *Gap__Bec__beSelectCtrlInfoWork__vfunc_20(void)
{
    return g_beSelectCtrlInfoWork_metaObject;
}

igMetaObject *Gap__Bec__beSelectCtrlInfoRamData__vfunc_20(void)
{
    return g_beSelectCtrlInfoRamData_metaObject;
}

igMetaObject *Gap__Bec__beSelectCtrlInfo__vfunc_20(void)
{
    return g_beSelectCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beShadow01Info__vfunc_20(void)
{
    return g_beShadow01Info_metaObject;
}

igMetaObject *Gap__Bec__beShadow01InfoList__vfunc_20(void)
{
    return g_beShadow01InfoList_metaObject;
}

igMetaObject *Gap__Bec__bePlaySE__vfunc_20(void)
{
    return g_bePlaySE_metaObject;
}

igMetaObject *Gap__Bec__bePlaySEList__vfunc_20(void)
{
    return g_bePlaySEList_metaObject;
}

igMetaObject *Gap__Bec__beSoundData__vfunc_20(void)
{
    return g_beSoundData_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoData__vfunc_20(void)
{
    return g_beBaseInfoData_metaObject;
}

igMetaObject *Gap__Bec__beSoundInfo__vfunc_20(void)
{
    return g_beSoundInfo_metaObject;
}

igMetaObject *Gap__Bec__beStaticInfo__vfunc_20(void)
{
    return g_beStaticInfo_metaObject;
}

igMetaObject *Gap__Bec__beSwitchCtrlInfo__vfunc_20(void)
{
    return g_beSwitchCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beTextureCtrlWork__vfunc_20(void)
{
    return g_beTextureCtrlWork_metaObject;
}

igMetaObject *Gap__Bec__beTextureCtrlData__vfunc_20(void)
{
    return g_beTextureCtrlData_metaObject;
}

igMetaObject *Gap__Bec__beTextureCtrlAttr__vfunc_20(void)
{
    return g_beTextureCtrlAttr_metaObject;
}

igMetaObject *Gap__Bec__beTextureCtrlInfo__vfunc_20(void)
{
    return g_beTextureCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beTextureCtrlInfoList__vfunc_20(void)
{
    return g_beTextureCtrlInfoList_metaObject;
}

igMetaObject *Gap__Bec__beTimerData__vfunc_20(void)
{
    return g_beTimerData_metaObject;
}

igMetaObject *Gap__Bec__beTimerDataList__vfunc_20(void)
{
    return g_beTimerDataList_metaObject;
}

igMetaObject *Gap__Bec__beTransformSync__vfunc_20(void)
{
    return g_beTransformSync_metaObject;
}

void Gap__Bec__beTransformSync__vfunc_35(beTransformSync *arg0, int arg1) {
    int temp_s2; int var_s1; int var_s0;

    igMatrix44f_Copy((char *)arg0 + 0x20, arg1);
    temp_s2 = ((igObjectList *)arg0->_syncTransformList)->_count;
    var_s1 = 0;
    if (0 < temp_s2) {
        var_s0 = 0;
        do {
            TransformSyncChildVirtualSlots *o = *(TransformSyncChildVirtualSlots **)((char *)((igObjectList *)arg0->_syncTransformList)->_data + var_s0);
            o->vX(arg1);
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < temp_s2);
    }
}

igMetaObject *Gap__Bec__beUnicode__vfunc_20(void)
{
    return g_beUnicode_metaObject;
}

igMetaObject *Gap__Bec__beWaterPlainInfo__vfunc_20(void)
{
    return g_beWaterPlainInfo_metaObject;
}

igMetaObject *Gap__Bec__beWaterMoveData__vfunc_20(void)
{
    return g_beWaterMoveData_metaObject;
}

igMetaObject *Gap__Bec__beWaterMoveDataList__vfunc_20(void)
{
    return g_beWaterMoveDataList_metaObject;
}

igMetaObject *Gap__Bec__beWaterMove__vfunc_20(void)
{
    return g_beWaterMove_metaObject;
}

igMetaObject *Gap__Bec__beWaterPlainInfoRam__vfunc_20(void)
{
    return g_beWaterPlainInfoRam_metaObject;
}

igMetaObject *Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_20(void)
{
    return g_igModelViewMatrixBoneSelectListBec_metaObject;
}

igMetaObject *Gap__Bec__igAppearanceListList__vfunc_20(void)
{
    return g_igAppearanceListList_metaObject;
}

igMetaObject *Gap__Bec__beWeaponAttachData__vfunc_20(void)
{
    return g_beWeaponAttachData_metaObject;
}

igMetaObject *Gap__Bec__beWeaponAttachDataList__vfunc_20(void)
{
    return g_beWeaponAttachDataList_metaObject;
}

igMetaObject *Gap__Bec__beWeaponSeqData__vfunc_20(void)
{
    return g_beWeaponSeqData_metaObject;
}

igMetaObject *Gap__Bec__beWeaponSeqDataList__vfunc_20(void)
{
    return g_beWeaponSeqDataList_metaObject;
}

igMetaObject *Gap__Bec__beWeaponInfo__vfunc_20(void)
{
    return g_beWeaponInfo_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfo__vfunc_20(void)
{
    return g_beBaseInfo_metaObject;
}

igMetaObject *Gap__Bec__beWeaponInfoRam__vfunc_20(void)
{
    return g_beWeaponInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoRam__vfunc_20(void)
{
    return g_beBaseInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beAction2InfoList__vfunc_22(void)
{
    return g_beAction2Info_metaObject;
}

igMetaObject *Gap__Bec__beAction2DataList__vfunc_22(void)
{
    return g_beAction2Data_metaObject;
}

igMetaObject *Gap__Bec__beAsTargetModelDataList__vfunc_22(void)
{
    return g_beAsTargetModelData_metaObject;
}

igMetaObject *Gap__Bec__beActionStarterDataList__vfunc_22(void)
{
    return g_beActionStarterData_metaObject;
}

igMetaObject *Gap__Bec__beCriHandleList__vfunc_22(void)
{
    return g_beCriHandle_metaObject;
}

igMetaObject *Gap__Bec__beDataBaseList__vfunc_22(void)
{
    return g_beDataBase_metaObject;
}

igMetaObject *Gap__Bec__beDataObjListList__vfunc_22(void)
{
    return g_beDataObjList_metaObject;
}

igMetaObject *Gap__Bec__beDemoManagerWorkList__vfunc_22(void)
{
    return g_beDemoManagerWork_metaObject;
}

igMetaObject *Gap__Bec__beDemoKeepMesList__vfunc_22(void)
{
    return g_beDemoKeepMes_metaObject;
}

igMetaObject *Gap__Bec__beFontGeomAttrPairList__vfunc_22(void)
{
    return g_beFontGeomAttrPair_metaObject;
}

igMetaObject *Gap__Bec__beUnicodeObjList__vfunc_22(void)
{
    return g_beUnicodeObj_metaObject;
}

igMetaObject *Gap__Bec__beFontImageList__vfunc_22(void)
{
    return g_beFontImage_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterDataList__vfunc_22(void)
{
    return g_beGeneraterData_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterPlayerDataList__vfunc_22(void)
{
    return g_beGeneraterPlayerData_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterItemDataList__vfunc_22(void)
{
    return g_beGeneraterItemData_metaObject;
}

igMetaObject *Gap__Bec__beGeneraterItemDataOneList__vfunc_22(void)
{
    return g_beGeneraterItemDataOne_metaObject;
}

igMetaObject *Gap__Bec__beGroupKeepList__vfunc_22(void)
{
    return g_beGroupKeep_metaObject;
}

igMetaObject *Gap__Bec__beHitLandResultDataList__vfunc_22(void)
{
    return g_beHitLandResultData_metaObject;
}

igMetaObject *Gap__Bec__beLayerGroupList__vfunc_22(void)
{
    return g_beLayerGroup_metaObject;
}

int Gap__Bec__igLightSetList__vfunc_22(void)
{
    return g_igLightSet_metaObject[0];
}

igMetaObject *Gap__Bec__beLuaDataList__vfunc_22(void)
{
    return g_beLuaData_metaObject;
}

igMetaObject *Gap__Bec__beLuaDataObjectist__vfunc_22(void)
{
    return g_beLuaDataObject_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlSearchList__vfunc_22(void)
{
    return g_beMatCtrlSearch_metaObject;
}

igMetaObject *Gap__Bec__beMatCtrlDataList__vfunc_22(void)
{
    return g_beMatCtrlData_metaObject;
}

igMetaObject *Gap__Bec__beMeterCtrlInfoList__vfunc_22(void)
{
    return g_beMeterCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlInfoList__vfunc_22(void)
{
    return g_beModelCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlAIMapList__vfunc_22(void)
{
    return g_beModelCtrlAIMap_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlAIDataList__vfunc_22(void)
{
    return g_beModelCtrlAIData_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlDataList__vfunc_22(void)
{
    return g_beModelCtrlData_metaObject;
}

igMetaObject *Gap__Bec__beModelCtrlMoveObjectList__vfunc_22(void)
{
    return g_beModelCtrlMoveObject_metaObject;
}

igMetaObject *Gap__Bec__beNumberCtrlInfoList__vfunc_22(void)
{
    return g_beNumberCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beNumVerDataList__vfunc_22(void)
{
    return g_beNumVerData_metaObject;
}

igMetaObject *Gap__Bec__beNumVerInsideDataList__vfunc_22(void)
{
    return g_beNumVerInsideData_metaObject;
}

igMetaObject *Gap__Bec__beSvSlotDataList__vfunc_22(void)
{
    return g_beSvSlotData_metaObject;
}

igMetaObject *Gap__Bec__bePadDataList__vfunc_22(void)
{
    return g_bePadData_metaObject;
}

igMetaObject *Gap__Bec__beSeDataList__vfunc_22(void)
{
    return g_beSeData_metaObject;
}

igMetaObject *Gap__Bec__beShadow01InfoList__vfunc_22(void)
{
    return g_beShadow01Info_metaObject;
}

igMetaObject *Gap__Bec__bePlaySEList__vfunc_22(void)
{
    return g_bePlaySE_metaObject;
}

igMetaObject *Gap__Bec__beTextureCtrlInfoList__vfunc_22(void)
{
    return g_beTextureCtrlInfo_metaObject;
}

igMetaObject *Gap__Bec__beTimerDataList__vfunc_22(void)
{
    return g_beTimerData_metaObject;
}

igMetaObject *Gap__Bec__beWaterMoveDataList__vfunc_22(void)
{
    return g_beWaterMoveData_metaObject;
}

igMetaObject *Gap__Bec__beWeaponAttachDataList__vfunc_22(void)
{
    return g_beWeaponAttachData_metaObject;
}

int Gap__Bec__igAppearanceListList__vfunc_22(void)
{
    return g_igAppearanceList_metaObject[0];
}

igMetaObject *Gap__Bec__beBaseInfoManagerList__vfunc_22(void)
{
    return g_beBaseInfoManager_metaObject;
}

igMetaObject *Gap__Bec__beMessengerWorkList__vfunc_22(void)
{
    return g_beMessengerWork_metaObject;
}

igMetaObject *Gap__Bec__beMessengerGroupList__vfunc_22(void)
{
    return g_beMessengerGroup_metaObject;
}

igMetaObject *Gap__Bec__beMessengerDelayList__vfunc_22(void)
{
    return g_beMessengerDelay_metaObject;
}

igMetaObject *Gap__Bec__beMessengerArgDataList__vfunc_22(void)
{
    return g_beMessengerArgData_metaObject;
}

igMetaObject *Gap__Bec__beWeaponSeqDataList__vfunc_22(void)
{
    return g_beWeaponSeqData_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoRamList__vfunc_22(void)
{
    return g_beBaseInfoRam_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoList__vfunc_22(void)
{
    return g_beBaseInfo_metaObject;
}

igMetaObject *Gap__Bec__beBaseInfoDataList__vfunc_22(void)
{
    return g_beBaseInfoData_metaObject;
}

