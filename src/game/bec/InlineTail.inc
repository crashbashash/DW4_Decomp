igMetaObject *ParticleInfo_GetMeta(void)
{
    return g_ParticleInfo_metaObject;
}

/* Runs the igObject base step, then (when `clearControls` is set) zeroes the particle control
 * data: `_points` (192 words) and `_numControls` (32 words). */
void ParticleInfo_resetFields(ParticleInfo *self, int clearControls) {
    Gap__Core__igObject__resetFields();
    if (clearControls != 0) {
        memset((int)self->_points, 0, sizeof(self->_points));
        memset((int)self->_numControls, 0, sizeof(self->_numControls));
    }
}

igMetaObject *beAction2Data_GetMeta(void)
{
    return g_beAction2Data_metaObject;
}

igMetaObject *beAction2DataList_GetMeta(void)
{
    return g_beAction2DataList_metaObject;
}

igMetaObject *beAction2MOTIONSET_GetMeta(void)
{
    return g_beAction2MOTIONSET_metaObject;
}

igMetaObject *beAction2JOINTSET_GetMeta(void)
{
    return g_beAction2JOINTSET_metaObject;
}

igMetaObject *beAction2FADESET_GetMeta(void)
{
    return g_beAction2FADESET_metaObject;
}

igMetaObject *beAction2WAITCHECK_GetMeta(void)
{
    return g_beAction2WAITCHECK_metaObject;
}

igMetaObject *beAction2FLASHSET_GetMeta(void)
{
    return g_beAction2FLASHSET_metaObject;
}

igMetaObject *beAction2Info_GetMeta(void)
{
    return g_beAction2Info_metaObject;
}

igMetaObject *beAction2InfoList_GetMeta(void)
{
    return g_beAction2InfoList_metaObject;
}

igMetaObject *beAction2InfoRam_GetMeta(void)
{
    return g_beAction2InfoRam_metaObject;
}

igMetaObject *beAction2InfoWork_GetMeta(void)
{
    return g_beAction2InfoWork_metaObject;
}

igMetaObject *beActionStarterDataList_GetMeta(void)
{
    return g_beActionStarterDataList_metaObject;
}

igMetaObject *beActionStarterData2_GetMeta(void)
{
    return g_beActionStarterData2_metaObject;
}

igMetaObject *beActionStarterData_GetMeta(void)
{
    return g_beActionStarterData_metaObject;
}

igMetaObject *beAsTargetModelData_GetMeta(void)
{
    return g_beAsTargetModelData_metaObject;
}

igMetaObject *beAsTargetModelDataList_GetMeta(void)
{
    return g_beAsTargetModelDataList_metaObject;
}

igMetaObject *beActionStarterInfo_GetMeta(void)
{
    return g_beActionStarterInfo_metaObject;
}

igMetaObject *beActionStarterInfoRam_GetMeta(void)
{
    return g_beActionStarterInfoRam_metaObject;
}

igMetaObject *beBaseInfoDataList_GetMeta(void)
{
    return g_beBaseInfoDataList_metaObject;
}

igMetaObject *beBaseInfoList_GetMeta(void)
{
    return g_beBaseInfoList_metaObject;
}

igMetaObject *beBaseInfoManagerList_GetMeta(void)
{
    return g_beBaseInfoManagerList_metaObject;
}

igMetaObject *beBaseInfoRamTimer_GetMeta(void)
{
    return g_beBaseInfoRamTimer_metaObject;
}

igMetaObject *beBaseInfoRamList_GetMetaObject_Virtual(void)
{
    return g_beBaseInfoRamList_metaObject;
}

igMetaObject *beBkColorInfo_GetMeta(void)
{
    return g_beBkColorInfo_metaObject;
}

igMetaObject *beCameraCtrlInfoRamShake_GetMeta(void)
{
    return g_beCameraCtrlInfoRamShake_metaObject;
}

igMetaObject *beCameraBoxData_GetMeta(void)
{
    return g_beCameraBoxData_metaObject;
}

igMetaObject *beCameraDemoData_GetMeta(void)
{
    return g_beCameraDemoData_metaObject;
}

igMetaObject *beCameraCtrlInfo_GetMeta(void)
{
    return g_beCameraCtrlInfo_metaObject;
}

igMetaObject *beChangePosTransformInfo_GetMeta(void)
{
    return g_beChangePosTransformInfo_metaObject;
}

igMetaObject *beChangePosTransformInfoRam_GetMeta(void)
{
    return g_beChangePosTransformInfoRam_metaObject;
}

igMetaObject *beCopyModelCtrl2_GetMeta(void)
{
    return g_beCopyModelCtrl2_metaObject;
}

igMetaObject *beCopyTransform_GetMeta(void)
{
    return g_beCopyTransform_metaObject;
}

igMetaObject *beCountry_GetMeta(void)
{
    return g_beCountry_metaObject;
}

igMetaObject *beCriAcxData_GetMeta(void)
{
    return g_beCriAcxData_metaObject;
}

void beBinDataObject_userDestruct(beBinDataObject *self) {
    if (self->_dataBuffer != 0) {
        Memory_FreeBuffer((void *)self->_dataBuffer);
        self->_dataBuffer = 0;
    }
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beCriSndf_GetMeta(void)
{
    return g_beCriSndf_metaObject;
}

igMetaObject *beCriAudio_GetMeta(void)
{
    return g_beCriAudio_metaObject;
}

igMetaObject *beCriFxXbData_GetMeta(void)
{
    return g_beCriFxXbData_metaObject;
}

igMetaObject *beCriFxInfo_GetMeta(void)
{
    return g_beCriFxInfo_metaObject;
}

igMetaObject *beCriHandle_GetMeta(void)
{
    return g_beCriHandle_metaObject;
}

igMetaObject *beCriHandleList_GetMeta(void)
{
    return g_beCriHandleList_metaObject;
}

igMetaObject *beCriSfpData_GetMeta(void)
{
    return g_beCriSfpData_metaObject;
}

igMetaObject *beCriVolume_GetMeta(void)
{
    return g_beCriVolume_metaObject;
}

igMetaObject *beDBManagerInfo_GetMeta(void)
{
    return g_beDBManagerInfo_metaObject;
}

igMetaObject *beDataBase_GetMeta(void) { return g_beDataBase_metaObject; }

igMetaObject *beDataBaseList_GetMeta(void)
{
    return g_beDataBaseList_metaObject;
}

igMetaObject *beDataObjInt_GetMeta(void)
{
    return g_beDataObjInt_metaObject;
}

igMetaObject *beDataObjIntList_GetMeta(void)
{
    return g_beDataObjIntList_metaObject;
}

igMetaObject *beDataObjBool_GetMeta(void)
{
    return g_beDataObjBool_metaObject;
}

igMetaObject *beDataObjBoolList_GetMeta(void)
{
    return g_beDataObjBoolList_metaObject;
}

igMetaObject *beDataObjString_GetMeta(void)
{
    return g_beDataObjString_metaObject;
}

igMetaObject *beDataObjStringList_GetMeta(void)
{
    return g_beDataObjStringList_metaObject;
}

igMetaObject *beDataObjObjectList_GetMeta(void)
{
    return g_beDataObjObjectList_metaObject;
}

igMetaObject *beDataObjFloatList_GetMeta(void)
{
    return g_beDataObjFloatList_metaObject;
}

igMetaObject *beDataObjList_GetMeta(void)
{
    return g_beDataObjList_metaObject;
}

igMetaObject *beDataObjListList_GetMeta(void)
{
    return g_beDataObjListList_metaObject;
}

igMetaObject *beDemoKeepMes_GetMeta(void)
{
    return g_beDemoKeepMes_metaObject;
}

igMetaObject *beDemoKeepMesList_GetMeta(void)
{
    return g_beDemoKeepMesList_metaObject;
}

igMetaObject *beDemoManagerWork_GetMeta(void)
{
    return g_beDemoManagerWork_metaObject;
}

igMetaObject *beDemoManagerWorkList_GetMeta(void)
{
    return g_beDemoManagerWorkList_metaObject;
}

igMetaObject *beFileChkObj_GetMeta(void)
{
    return g_beFileChkObj_metaObject;
}

igMetaObject *beFile_GetMeta(void)
{
    return g_beFile_metaObject;
}

igMetaObject *beFileListInfo_GetMeta(void)
{
    return g_beFileListInfo_metaObject;
}

igMetaObject *beFontGeomAttrPair_GetMeta(void)
{
    return g_beFontGeomAttrPair_metaObject;
}

igMetaObject *beFontGeomAttrPairList_GetMeta(void)
{
    return g_beFontGeomAttrPairList_metaObject;
}

igMetaObject *beFontImage_GetMeta(void)
{
    return g_beFontImage_metaObject;
}

int igFont_GetMeta(void)
{
    return g_igFont_metaObject[0];
}

igMetaObject *beFontImageList_GetMeta(void)
{
    return g_beFontImageList_metaObject;
}

igMetaObject *beUnicodeObjList_GetMeta(void)
{
    return g_beUnicodeObjList_metaObject;
}

igMetaObject *beFontInfoData_GetMeta(void)
{
    return g_beFontInfoData_metaObject;
}

igMetaObject *beFontInfo_GetMeta(void)
{
    return g_beFontInfo_metaObject;
}

igMetaObject *beGeneraterItemDataOne_GetMeta(void)
{
    return g_beGeneraterItemDataOne_metaObject;
}

igMetaObject *beGeneraterItemDataOneList_GetMeta(void)
{
    return g_beGeneraterItemDataOneList_metaObject;
}

igMetaObject *beGeneraterItemData_GetMeta(void)
{
    return g_beGeneraterItemData_metaObject;
}

igMetaObject *beGeneraterItemDataList_GetMeta(void)
{
    return g_beGeneraterItemDataList_metaObject;
}

igMetaObject *beGeneraterPlayerData_GetMeta(void)
{
    return g_beGeneraterPlayerData_metaObject;
}

igMetaObject *beGeneraterPlayerDataList_GetMeta(void)
{
    return g_beGeneraterPlayerDataList_metaObject;
}

igMetaObject *beGeneraterData_GetMeta(void)
{
    return g_beGeneraterData_metaObject;
}

igMetaObject *beGeneraterDataList_GetMeta(void)
{
    return g_beGeneraterDataList_metaObject;
}

igMetaObject *beGeneraterInfo_GetMeta(void)
{
    return g_beGeneraterInfo_metaObject;
}

igMetaObject *beGeneraterInfoRam_GetMeta(void)
{
    return g_beGeneraterInfoRam_metaObject;
}

igMetaObject *beGeneraterInfoWork_GetMeta(void)
{
    return g_beGeneraterInfoWork_metaObject;
}

igMetaObject *beGroupKeep_GetMeta(void)
{
    return g_beGroupKeep_metaObject;
}

igMetaObject *beGroupKeepList_GetMeta(void)
{
    return g_beGroupKeepList_metaObject;
}

igMetaObject *beHitLandDelivInfo_GetMeta(void)
{
    return g_beHitLandDelivInfo_metaObject;
}

igMetaObject *beHitLandDelivInfoRam_GetMeta(void)
{
    return g_beHitLandDelivInfoRam_metaObject;
}

igMetaObject *beHitLandResultData_GetMeta(void)
{
    return g_beHitLandResultData_metaObject;
}

igMetaObject *beHitLandResultDataList_GetMeta(void)
{
    return g_beHitLandResultDataList_metaObject;
}

igMetaObject *beHitLandModelTraversal_GetMeta(void)
{
    return g_beHitLandModelTraversal_metaObject;
}

igMetaObject *beHitLandModelInfo_GetMeta(void)
{
    return g_beHitLandModelInfo_metaObject;
}

igMetaObject *beHitLandModelInfoRam_GetMeta(void)
{
    return g_beHitLandModelInfoRam_metaObject;
}

igMetaObject *beLOA_GetMeta(void)
{
    return g_beLOA_metaObject;
}

igMetaObject *beLayerGroup_GetMeta(void)
{
    return g_beLayerGroup_metaObject;
}

igMetaObject *beLayerGroupList_GetMeta(void)
{
    return g_beLayerGroupList_metaObject;
}

igMetaObject *beLayerInfo_GetMeta(void)
{
    return g_beLayerInfo_metaObject;
}

igMetaObject *beLayerInfoRam_GetMeta(void)
{
    return g_beLayerInfoRam_metaObject;
}

igMetaObject *beLightCtrlInfo_GetMeta(void)
{
    return g_beLightCtrlInfo_metaObject;
}

igMetaObject *igLightSetList_GetMeta(void)
{
    return g_igLightSetList_metaObject;
}

igMetaObject *beLuaDataObject_GetMeta(void)
{
    return g_beLuaDataObject_metaObject;
}

void beLuaDataObject_userDestruct(beLuaDataObject *self) {
    int buffer;

    buffer = self->_data;
    if (buffer != 0) {
        Memory_FreeBuffer(buffer);
    }
    self->_data = 0;
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beLuaDataObjectist_GetMeta(void)
{
    return g_beLuaDataObjectist_metaObject;
}

igMetaObject *beLuaData_GetMeta(void)
{
    return g_beLuaData_metaObject;
}

igMetaObject *beLuaDataList_GetMeta(void)
{
    return g_beLuaDataList_metaObject;
}

igMetaObject *beLuaInfo_GetMeta(void)
{
    return g_beLuaInfo_metaObject;
}

igMetaObject *beMatCtrlData_GetMeta(void)
{
    return g_beMatCtrlData_metaObject;
}

igMetaObject *beMatCtrlDataList_GetMeta(void)
{
    return g_beMatCtrlDataList_metaObject;
}

igMetaObject *beMatCtrlSearch_GetMeta(void)
{
    return g_beMatCtrlSearch_metaObject;
}

igMetaObject *beMatCtrlSearchList_GetMeta(void)
{
    return g_beMatCtrlSearchList_metaObject;
}

igMetaObject *beMatCtrlInfo_GetMeta(void)
{
    return g_beMatCtrlInfo_metaObject;
}

igMetaObject *beMatCtrlInfoRam_GetMeta(void)
{
    return g_beMatCtrlInfoRam_metaObject;
}

igMetaObject *beMatCtrlInfoWork_GetMeta(void)
{
    return g_beMatCtrlInfoWork_metaObject;
}

igMetaObject *beMessengerArgData_GetMeta(void)
{
    return g_beMessengerArgData_metaObject;
}

igMetaObject *beMessengerArgDataList_GetMeta(void)
{
    return g_beMessengerArgDataList_metaObject;
}

igMetaObject *beMessengerDelay_GetMeta(void)
{
    return g_beMessengerDelay_metaObject;
}

igMetaObject *beMessengerDelayList_GetMeta(void)
{
    return g_beMessengerDelayList_metaObject;
}

igMetaObject *beMessengerGroup_GetMeta(void)
{
    return g_beMessengerGroup_metaObject;
}

igMetaObject *beMessengerGroupList_GetMeta(void)
{
    return g_beMessengerGroupList_metaObject;
}

igMetaObject *beMessengerWork_GetMetaObject_Virtual(void)
{
    return g_beMessengerWork_metaObject;
}

igMetaObject *beMessengerWorkList_GetMeta(void)
{
    return g_beMessengerWorkList_metaObject;
}

igMetaObject *beMeterCtrlOneData_GetMeta(void)
{
    return g_beMeterCtrlOneData_metaObject;
}

igMetaObject *beMeterCtrlInfo_GetMeta(void)
{
    return g_beMeterCtrlInfo_metaObject;
}

igMetaObject *beMeterCtrlInfoList_GetMeta(void)
{
    return g_beMeterCtrlInfoList_metaObject;
}

igMetaObject *beMeterCtrlNode_GetMeta(void)
{
    return g_beMeterCtrlNode_metaObject;
}

igMetaObject *beModelCtrlData_GetMeta(void)
{
    return g_beModelCtrlData_metaObject;
}

igMetaObject *beModelCtrlDataList_GetMeta(void)
{
    return g_beModelCtrlDataList_metaObject;
}

igMetaObject *beModelCtrlLUACALL_GetMeta(void)
{
    return g_beModelCtrlLUACALL_metaObject;
}

igMetaObject *beModelCtrlLABEL_GetMeta(void)
{
    return g_beModelCtrlLABEL_metaObject;
}

igMetaObject *beModelCtrlLABELCTRL_GetMeta(void)
{
    return g_beModelCtrlLABELCTRL_metaObject;
}

igMetaObject *beModelCtrlACTION_GetMeta(void)
{
    return g_beModelCtrlACTION_metaObject;
}

igMetaObject *beModelCtrlJUMP_GetMeta(void)
{
    return g_beModelCtrlJUMP_metaObject;
}

igMetaObject *beModelCtrlCTRL_GetMeta(void)
{
    return g_beModelCtrlCTRL_metaObject;
}

igMetaObject *beModelCtrlMSGBOX_GetMeta(void)
{
    return g_beModelCtrlMSGBOX_metaObject;
}

igMetaObject *beModelCtrlMOVE_GetMeta(void)
{
    return g_beModelCtrlMOVE_metaObject;
}

igMetaObject *beModelCtrlMOVEEX_GetMeta(void)
{
    return g_beModelCtrlMOVEEX_metaObject;
}

igMetaObject *beModelCtrlMOVERL_GetMeta(void)
{
    return g_beModelCtrlMOVERL_metaObject;
}

igMetaObject *beModelCtrlPDMOVE_GetMeta(void)
{
    return g_beModelCtrlPDMOVE_metaObject;
}

igMetaObject *beModelCtrlWCHECK_GetMeta(void)
{
    return g_beModelCtrlWCHECK_metaObject;
}

igMetaObject *beModelCtrlAIMAP_GetMeta(void)
{
    return g_beModelCtrlAIMAP_metaObject;
}

igMetaObject *beModelCtrlMUTEKI_GetMeta(void)
{
    return g_beModelCtrlMUTEKI_metaObject;
}

igMetaObject *beModelCtrlHITBOX_GetMeta(void)
{
    return g_beModelCtrlHITBOX_metaObject;
}

igMetaObject *beModelCtrlAIData_GetMeta(void)
{
    return g_beModelCtrlAIData_metaObject;
}

igMetaObject *beModelCtrlAIDataList_GetMeta(void)
{
    return g_beModelCtrlAIDataList_metaObject;
}

igMetaObject *beModelCtrlAIMap_GetMeta(void)
{
    return g_beModelCtrlAIMap_metaObject;
}

igMetaObject *beModelCtrlAIMapList_GetMeta(void)
{
    return g_beModelCtrlAIMapList_metaObject;
}

igMetaObject *beModelCtrlInfoDataAIM_GetMeta(void)
{
    return g_beModelCtrlInfoDataAIM_metaObject;
}

igMetaObject *beModelCtrlInfoDataAIH_GetMeta(void)
{
    return g_beModelCtrlInfoDataAIH_metaObject;
}

igMetaObject *beModelCtrlInfoDataHit_GetMeta(void)
{
    return g_beModelCtrlInfoDataHit_metaObject;
}

igMetaObject *beModelCtrlInfoDataSeq_GetMeta(void)
{
    return g_beModelCtrlInfoDataSeq_metaObject;
}

igMetaObject *beModelCtrlInfoDataTrc_GetMeta(void)
{
    return g_beModelCtrlInfoDataTrc_metaObject;
}

igMetaObject *beModelCtrlInfoRamData_GetMeta(void)
{
    return g_beModelCtrlInfoRamData_metaObject;
}

igMetaObject *beModelCtrlInfo_GetMeta(void)
{
    return g_beModelCtrlInfo_metaObject;
}

igMetaObject *beModelCtrlInfoList_GetMeta(void)
{
    return g_beModelCtrlInfoList_metaObject;
}

igMetaObject *beModelCtrlMoveObject_GetMeta(void)
{
    return g_beModelCtrlMoveObject_metaObject;
}

igMetaObject *beModelCtrlMoveObjectList_GetMeta(void)
{
    return g_beModelCtrlMoveObjectList_metaObject;
}

igMetaObject *beModelCtrlInfoHitBody_GetMeta(void)
{
    return g_beModelCtrlInfoHitBody_metaObject;
}

igMetaObject *beModelCtrlInfoAI_GetMeta(void)
{
    return g_beModelCtrlInfoAI_metaObject;
}

igMetaObject *beModelCtrlInfoRideOn_GetMeta(void)
{
    return g_beModelCtrlInfoRideOn_metaObject;
}

void beModelCtrlInfoRideOn_Move(void)
{
}

igMetaObject *beModelCtrlInfoWork_GetMeta(void)
{
    return g_beModelCtrlInfoWork_metaObject;
}

igMetaObject *beModelCtrlNode2_GetMeta(void)
{
    return g_beModelCtrlNode2_metaObject;
}

int beModelCtrlSubComBase_Update(void)
{
    return 1;
}

void beModelCtrlSCHitBox_Stop(void)
{
}

igMetaObject *beModelCtrlSubCom_GetMeta(void)
{
    return g_beModelCtrlSubCom_metaObject;
}

igMetaObject *beMovieInfoData_GetMeta(void)
{
    return g_beMovieInfoData_metaObject;
}

igMetaObject *beMovieInfo_GetMeta(void)
{
    return g_beMovieInfo_metaObject;
}

igMetaObject *beLoadingNode_GetMeta(void)
{
    return g_beLoadingNode_metaObject;
}

igMetaObject *beNodeAnim_GetMeta(void)
{
    return g_beNodeAnim_metaObject;
}

igMetaObject *beNumberCtrlInfo_GetMeta(void)
{
    return g_beNumberCtrlInfo_metaObject;
}

igMetaObject *beNumberCtrlInfoList_GetMeta(void)
{
    return g_beNumberCtrlInfoList_metaObject;
}

igMetaObject *beNumVerInsideData_GetMeta(void)
{
    return g_beNumVerInsideData_metaObject;
}

igMetaObject *beNumVerInsideDataList_GetMeta(void)
{
    return g_beNumVerInsideDataList_metaObject;
}

igMetaObject *beNumVerData_GetMeta(void)
{
    return g_beNumVerData_metaObject;
}

void beNumVerData_userConstruct(beNumVerData *self, int flag) {
    int i;
    void *allocator;
    Gap__Core__igObject__userConstruct(self, flag);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    if (!(flag & 0xFF)) {
        i = 0;
        do {
            allocator = igObject_GetAllocator(self);
            allocator = (g_useOwnerAllocator != 0) ? allocator : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]));
            {
                igSmartPointer<beNumVerInsideData> item((beNumVerInsideData *)beNumVerInsideData_Create((int)allocator));
                ObjectList_AppendRetained((void *)self->_verDataList, item.p);
            }
            i += 1;
        } while (i < 6);
    }
}

static inline int beNumVerDataList_GetCount(const beNumVerDataList *list) { return list->_count; }

void beNumVerData_userDestruct(beNumVerData *self) {
    beNumVerDataList *list = (beNumVerDataList *)self->_verDataList;
    int releaseCount;
    int releaseIndex;
    int clearCount;
    int clearIndex;

    if (beNumVerDataList_GetCount(list) > 0) {
        releaseCount = list->_count;
        for (releaseIndex = 0; releaseIndex < releaseCount; releaseIndex++) {
            igRelease(((igObject **)list->_data)[releaseIndex]);
        }
        clearCount = list->_count;
        for (clearIndex = 0; clearIndex < clearCount; clearIndex++) {
            ((int *)list->_data)[clearIndex] = 0;
        }
        list->_count = 0;
    }
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beNumVerDataList_GetMeta(void)
{
    return g_beNumVerDataList_metaObject;
}

igMetaObject *beNumberCtrlInfoRam_GetMeta(void)
{
    return g_beNumberCtrlInfoRam_metaObject;
}

igMetaObject *beNumberCtrlInfoWork_GetMeta(void)
{
    return g_beNumberCtrlInfoWork_metaObject;
}

igMetaObject *beOptInfo_GetMeta(void)
{
    return g_beOptInfo_metaObject;
}

igMetaObject *bePadDataList_GetMeta(void)
{
    return g_bePadDataList_metaObject;
}

igMetaObject *beParticleCtrl2Info_GetMeta(void)
{
    return g_beParticleCtrl2Info_metaObject;
}

igMetaObject *beParticleCtrl2InfoWork_GetMeta(void)
{
    return g_beParticleCtrl2InfoWork_metaObject;
}

igMetaObject *beParticleCtrl2InfoRam_GetMeta(void)
{
    return g_beParticleCtrl2InfoRam_metaObject;
}

igMetaObject *bePoint01Info_GetMeta(void)
{
    return g_bePoint01Info_metaObject;
}

igMetaObject *beResetNode_GetMeta(void)
{
    return g_beResetNode_metaObject;
}

igMetaObject *beSvDeliver_GetMeta(void)
{
    return g_beSvDeliver_metaObject;
}

igMetaObject *beSaveDataDeliver_GetMeta(void)
{
    return g_beSaveDataDeliver_metaObject;
}

void beSaveDataDeliver_userConstruct(beSaveDataDeliver *self) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
}

void beSaveDataDeliver_userDestruct(beSaveDataDeliver *self) {
    int data;

    data = self->_data;
    if (data != 0) {
        Memory_FreeBuffer(data);
    }
    self->_data = 0;
    self->_size = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beSvSlotXbox_GetMeta(void)
{
    return g_beSvSlotXbox_metaObject;
}

igMetaObject *beSvSlotGC_GetMeta(void)
{
    return g_beSvSlotGC_metaObject;
}

igMetaObject *beSvSlotPS2_GetMeta(void)
{
    return g_beSvSlotPS2_metaObject;
}

igMetaObject *beSvSlotDataList_GetMeta(void)
{
    return g_beSvSlotDataList_metaObject;
}

igMetaObject *beSvPlatDataGC_GetMeta(void)
{
    return g_beSvPlatDataGC_metaObject;
}

void beSvPlatDataGC_userConstruct(beSvPlatDataGC *self) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
}

void beSvPlatDataGC_userDestruct(beSvPlatDataGC *self) {
    if (self->_banTplData != 0) {
        Memory_FreeBuffer(self->_banTplData);
    }
    if (self->_iconTplData != 0) {
        Memory_FreeBuffer(self->_iconTplData);
    }
    self->_banTplData = 0;
    self->_iconTplData = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beSvPs2McImage128k_GetMeta(void)
{
    return g_beSvPs2McImage128k_metaObject;
}

void beSvPs2McImage128k_userConstruct(beSvPs2McImage128k *self, int flag) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    if (!(flag & 0xFF)) {
        self->_data = Memory_AllocateDefaultBuffer(0x20000);
    }
}

void beSvPs2McImage128k_userDestruct(beSvPs2McImage128k *self) {
    if (self->_data != 0) {
        Memory_FreeBuffer(self->_data);
    }
    self->_data = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beSvPlatDataPS2_GetMeta(void)
{
    return g_beSvPlatDataPS2_metaObject;
}

igMetaObject *beXboxImage24k_GetMeta(void)
{
    return g_beXboxImage24k_metaObject;
}

void beXboxImage24k_userConstruct(beXboxImage24k *self, int flag) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    if (!(flag & 0xFF)) {
        self->_data = Memory_AllocateDefaultBuffer(0x6000);
        self->_dataSize = 0x6000;
    }
}

void beXboxImage24k_userDestruct(beXboxImage24k *self) {
    int data;

    data = self->_data;
    if (data != 0) {
        Memory_FreeBuffer(data);
    }
    self->_data = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beSvPlatDataXbox_GetMeta(void)
{
    return g_beSvPlatDataXbox_metaObject;
}

igMetaObject *beSvPlatDataPC_GetMeta(void)
{
    return g_beSvPlatDataPC_metaObject;
}

igMetaObject *beSvPlatBaseData_GetMeta(void)
{
    return g_beSvPlatBaseData_metaObject;
}

igMetaObject *beSaveUtilInfo_GetMeta(void)
{
    return g_beSaveUtilInfo_metaObject;
}

igMetaObject *beSaveUtilInfoRam_GetMeta(void)
{
    return g_beSaveUtilInfoRam_metaObject;
}

igMetaObject *beSeData_GetMeta(void)
{
    return g_beSeData_metaObject;
}

igMetaObject *beSeDataList_GetMeta(void)
{
    return g_beSeDataList_metaObject;
}

igMetaObject *beSeInfoData_GetMeta(void)
{
    return g_beSeInfoData_metaObject;
}

igMetaObject *beSeInfo_GetMeta(void)
{
    return g_beSeInfo_metaObject;
}

igMetaObject *beSelectCtrlInfoWork_GetMeta(void)
{
    return g_beSelectCtrlInfoWork_metaObject;
}

igMetaObject *beSelectCtrlInfoRamData_GetMeta(void)
{
    return g_beSelectCtrlInfoRamData_metaObject;
}

igMetaObject *beSelectCtrlInfo_GetMeta(void)
{
    return g_beSelectCtrlInfo_metaObject;
}

igMetaObject *beShadow01Info_GetMeta(void)
{
    return g_beShadow01Info_metaObject;
}

igMetaObject *beShadow01InfoList_GetMeta(void)
{
    return g_beShadow01InfoList_metaObject;
}

igMetaObject *bePlaySE_GetMeta(void)
{
    return g_bePlaySE_metaObject;
}

igMetaObject *bePlaySEList_GetMeta(void)
{
    return g_bePlaySEList_metaObject;
}

igMetaObject *beSoundData_GetMeta(void)
{
    return g_beSoundData_metaObject;
}

igMetaObject *beBaseInfoData_GetMeta(void)
{
    return g_beBaseInfoData_metaObject;
}

igMetaObject *beSoundInfo_GetMeta(void)
{
    return g_beSoundInfo_metaObject;
}

igMetaObject *beStaticInfo_GetMeta(void)
{
    return g_beStaticInfo_metaObject;
}

igMetaObject *beSwitchCtrlInfo_GetMeta(void)
{
    return g_beSwitchCtrlInfo_metaObject;
}

igMetaObject *beTextureCtrlWork_GetMeta(void)
{
    return g_beTextureCtrlWork_metaObject;
}

igMetaObject *beTextureCtrlData_GetMeta(void)
{
    return g_beTextureCtrlData_metaObject;
}

igMetaObject *beTextureCtrlAttr_GetMeta(void)
{
    return g_beTextureCtrlAttr_metaObject;
}

igMetaObject *beTextureCtrlInfo_GetMeta(void)
{
    return g_beTextureCtrlInfo_metaObject;
}

igMetaObject *beTextureCtrlInfoList_GetMeta(void)
{
    return g_beTextureCtrlInfoList_metaObject;
}

igMetaObject *beTimerData_GetMeta(void)
{
    return g_beTimerData_metaObject;
}

igMetaObject *beTimerDataList_GetMeta(void)
{
    return g_beTimerDataList_metaObject;
}

igMetaObject *beTransformSync_GetMeta(void)
{
    return g_beTransformSync_metaObject;
}

void beTransformSync_SetMatrix(beTransformSync *self, const float *matrix) {
    int count;
    int index;
    int offset;

    igMatrix44f_Copy(self->_m, matrix);
    count = ((igObjectList *)self->_syncTransformList)->_count;
    index = 0;
    if (0 < count) {
        offset = 0;
        do {
            igTransformDispatchView *child = *(igTransformDispatchView **)((char *)((igObjectList *)self->_syncTransformList)->_data + offset);
            child->SetMatrix(matrix);
            index += 1;
            offset += 4;
        } while (index < count);
    }
}

igMetaObject *beUnicode_GetMeta(void)
{
    return g_beUnicode_metaObject;
}

igMetaObject *beWaterPlainInfo_GetMeta(void)
{
    return g_beWaterPlainInfo_metaObject;
}

igMetaObject *beWaterMoveData_GetMeta(void)
{
    return g_beWaterMoveData_metaObject;
}

igMetaObject *beWaterMoveDataList_GetMeta(void)
{
    return g_beWaterMoveDataList_metaObject;
}

igMetaObject *beWaterMove_GetMeta(void)
{
    return g_beWaterMove_metaObject;
}

igMetaObject *beWaterPlainInfoRam_GetMeta(void)
{
    return g_beWaterPlainInfoRam_metaObject;
}

igMetaObject *igModelViewMatrixBoneSelectList_GetMeta(void)
{
    return g_igModelViewMatrixBoneSelectListBec_metaObject;
}

igMetaObject *igAppearanceListList_GetMeta(void)
{
    return g_igAppearanceListList_metaObject;
}

igMetaObject *beWeaponAttachData_GetMeta(void)
{
    return g_beWeaponAttachData_metaObject;
}

igMetaObject *beWeaponAttachDataList_GetMeta(void)
{
    return g_beWeaponAttachDataList_metaObject;
}

igMetaObject *beWeaponSeqData_GetMeta(void)
{
    return g_beWeaponSeqData_metaObject;
}

igMetaObject *beWeaponSeqDataList_GetMeta(void)
{
    return g_beWeaponSeqDataList_metaObject;
}

igMetaObject *beWeaponInfo_GetMeta(void)
{
    return g_beWeaponInfo_metaObject;
}

igMetaObject *beBaseInfo_GetMeta(void)
{
    return g_beBaseInfo_metaObject;
}

igMetaObject *beWeaponInfoRam_GetMeta(void)
{
    return g_beWeaponInfoRam_metaObject;
}

igMetaObject *beBaseInfoRam_GetMeta(void)
{
    return g_beBaseInfoRam_metaObject;
}

igMetaObject *beAction2InfoList_GetElementMeta(void)
{
    return g_beAction2Info_metaObject;
}

igMetaObject *beAction2DataList_GetElementMeta(void)
{
    return g_beAction2Data_metaObject;
}

igMetaObject *beAsTargetModelDataList_GetElementMeta(void)
{
    return g_beAsTargetModelData_metaObject;
}

igMetaObject *beActionStarterDataList_GetElementMeta(void)
{
    return g_beActionStarterData_metaObject;
}

igMetaObject *beCriHandleList_GetElementMeta(void)
{
    return g_beCriHandle_metaObject;
}

igMetaObject *beDataBaseList_GetElementMeta(void)
{
    return g_beDataBase_metaObject;
}

igMetaObject *beDataObjListList_GetElementMeta(void)
{
    return g_beDataObjList_metaObject;
}

igMetaObject *beDemoManagerWorkList_GetElementMeta(void)
{
    return g_beDemoManagerWork_metaObject;
}

igMetaObject *beDemoKeepMesList_GetElementMeta(void)
{
    return g_beDemoKeepMes_metaObject;
}

igMetaObject *beFontGeomAttrPairList_GetElementMeta(void)
{
    return g_beFontGeomAttrPair_metaObject;
}

igMetaObject *beUnicodeObjList_GetElementMeta(void)
{
    return g_beUnicodeObj_metaObject;
}

igMetaObject *beFontImageList_GetElementMeta(void)
{
    return g_beFontImage_metaObject;
}

igMetaObject *beGeneraterDataList_GetElementMeta(void)
{
    return g_beGeneraterData_metaObject;
}

igMetaObject *beGeneraterPlayerDataList_GetElementMeta(void)
{
    return g_beGeneraterPlayerData_metaObject;
}

igMetaObject *beGeneraterItemDataList_GetElementMeta(void)
{
    return g_beGeneraterItemData_metaObject;
}

igMetaObject *beGeneraterItemDataOneList_GetElementMeta(void)
{
    return g_beGeneraterItemDataOne_metaObject;
}

igMetaObject *beGroupKeepList_GetElementMeta(void)
{
    return g_beGroupKeep_metaObject;
}

igMetaObject *beHitLandResultDataList_GetElementMeta(void)
{
    return g_beHitLandResultData_metaObject;
}

igMetaObject *beLayerGroupList_GetElementMeta(void)
{
    return g_beLayerGroup_metaObject;
}

int igLightSetList_GetElementMeta(void)
{
    return g_igLightSet_metaObject[0];
}

igMetaObject *beLuaDataList_GetElementMeta(void)
{
    return g_beLuaData_metaObject;
}

igMetaObject *beLuaDataObjectist_GetElementMeta(void)
{
    return g_beLuaDataObject_metaObject;
}

igMetaObject *beMatCtrlSearchList_GetElementMeta(void)
{
    return g_beMatCtrlSearch_metaObject;
}

igMetaObject *beMatCtrlDataList_GetElementMeta(void)
{
    return g_beMatCtrlData_metaObject;
}

igMetaObject *beMeterCtrlInfoList_GetElementMeta(void)
{
    return g_beMeterCtrlInfo_metaObject;
}

igMetaObject *beModelCtrlInfoList_GetElementMeta(void)
{
    return g_beModelCtrlInfo_metaObject;
}

igMetaObject *beModelCtrlAIMapList_GetElementMeta(void)
{
    return g_beModelCtrlAIMap_metaObject;
}

igMetaObject *beModelCtrlAIDataList_GetElementMeta(void)
{
    return g_beModelCtrlAIData_metaObject;
}

igMetaObject *beModelCtrlDataList_GetElementMeta(void)
{
    return g_beModelCtrlData_metaObject;
}

igMetaObject *beModelCtrlMoveObjectList_GetElementMeta(void)
{
    return g_beModelCtrlMoveObject_metaObject;
}

igMetaObject *beNumberCtrlInfoList_GetElementMeta(void)
{
    return g_beNumberCtrlInfo_metaObject;
}

igMetaObject *beNumVerDataList_GetElementMeta(void)
{
    return g_beNumVerData_metaObject;
}

igMetaObject *beNumVerInsideDataList_GetElementMeta(void)
{
    return g_beNumVerInsideData_metaObject;
}

igMetaObject *beSvSlotDataList_GetElementMeta(void)
{
    return g_beSvSlotData_metaObject;
}

igMetaObject *bePadDataList_GetElementMeta(void)
{
    return g_bePadData_metaObject;
}

igMetaObject *beSeDataList_GetElementMeta(void)
{
    return g_beSeData_metaObject;
}

igMetaObject *beShadow01InfoList_GetElementMeta(void)
{
    return g_beShadow01Info_metaObject;
}

igMetaObject *bePlaySEList_GetElementMeta(void)
{
    return g_bePlaySE_metaObject;
}

igMetaObject *beTextureCtrlInfoList_GetElementMeta(void)
{
    return g_beTextureCtrlInfo_metaObject;
}

igMetaObject *beTimerDataList_GetElementMeta(void)
{
    return g_beTimerData_metaObject;
}

igMetaObject *beWaterMoveDataList_GetElementMeta(void)
{
    return g_beWaterMoveData_metaObject;
}

igMetaObject *beWeaponAttachDataList_GetElementMeta(void)
{
    return g_beWeaponAttachData_metaObject;
}

int igAppearanceListList_GetElementMeta(void)
{
    return g_igAppearanceList_metaObject[0];
}

igMetaObject *beBaseInfoManagerList_GetElementMeta(void)
{
    return g_beBaseInfoManager_metaObject;
}

igMetaObject *beMessengerWorkList_GetElementMeta(void)
{
    return g_beMessengerWork_metaObject;
}

igMetaObject *beMessengerGroupList_GetElementMeta(void)
{
    return g_beMessengerGroup_metaObject;
}

igMetaObject *beMessengerDelayList_GetElementMeta(void)
{
    return g_beMessengerDelay_metaObject;
}

igMetaObject *beMessengerArgDataList_GetElementMeta(void)
{
    return g_beMessengerArgData_metaObject;
}

igMetaObject *beWeaponSeqDataList_GetElementMeta(void)
{
    return g_beWeaponSeqData_metaObject;
}

igMetaObject *beBaseInfoRamList_GetElementMeta(void)
{
    return g_beBaseInfoRam_metaObject;
}

igMetaObject *beBaseInfoList_GetElementMeta(void)
{
    return g_beBaseInfo_metaObject;
}

igMetaObject *beBaseInfoDataList_GetElementMeta(void)
{
    return g_beBaseInfoData_metaObject;
}

