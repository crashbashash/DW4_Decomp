igMetaObject *ParticleInfo_GetMeta(void)
{
    return g_ParticleInfo_metaObject;
}

/* Runs the igObject base step, then (when `clearControls` is set) zeroes the particle control
 * data: `_points` (192 words) and `_numControls` (32 words). */
void ParticleInfo_resetFields(ParticleInfo *self, int clearControls) {
    Gap__Core__igObject__resetFields((igObject *)self, clearControls);
    if (clearControls != 0) {
        memset(self->_points, 0, sizeof(self->_points));
        memset(self->_numControls, 0, sizeof(self->_numControls));
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

igMetaObject *beActionStarterData2_GetMeta(void)
{
    return g_beActionStarterData2_metaObject;
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

igMetaObject *beCriAudio_GetMeta(void)
{
    return g_beCriAudio_metaObject;
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

igMetaObject *beDBManagerInfo_GetMeta(void)
{
    return g_beDBManagerInfo_metaObject;
}

igMetaObject *beDataObjIntList_GetMeta(void)
{
    return g_beDataObjIntList_metaObject;
}

igMetaObject *beDataObjBoolList_GetMeta(void)
{
    return g_beDataObjBoolList_metaObject;
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

igMetaObject *beFileListInfo_GetMeta(void)
{
    return g_beFileListInfo_metaObject;
}

igMetaObject *beFontImage_GetMeta(void)
{
    return g_beFontImage_metaObject;
}

igMetaObject *igFont_GetMeta(void)
{
    return g_igFont_metaObject;
}

igMetaObject *beFontImageList_GetMeta(void)
{
    return g_beFontImageList_metaObject;
}

igMetaObject *beFontInfoData_GetMeta(void)
{
    return g_beFontInfoData_metaObject;
}

igMetaObject *beFontInfo_GetMeta(void)
{
    return g_beFontInfo_metaObject;
}

igMetaObject *beGeneraterItemData_GetMeta(void)
{
    return g_beGeneraterItemData_metaObject;
}

igMetaObject *beGeneraterItemDataList_GetMeta(void)
{
    return g_beGeneraterItemDataList_metaObject;
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

namespace Gap {
namespace Bec {

void beLuaDataObject::userDestruct() {
    int buffer;

    buffer = _data;
    if (buffer != 0) {
        Memory_FreeBuffer((void *)buffer);
    }
    _data = 0;
    Gap__Core__igObject__userDestruct((::beLuaDataObject *)this);
}
}
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

igMetaObject *beMatCtrlInfo_GetMeta(void)
{
    return g_beMatCtrlInfo_metaObject;
}

igMetaObject *beMatCtrlInfoRam_GetMeta(void)
{
    return g_beMatCtrlInfoRam_metaObject;
}

igMetaObject *beMessengerGroup_GetMeta(void)
{
    return g_beMessengerGroup_metaObject;
}

igMetaObject *beMessengerGroupList_GetMeta(void)
{
    return g_beMessengerGroupList_metaObject;
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

igMetaObject *beModelCtrlAIMAP_GetMeta(void)
{
    return g_beModelCtrlAIMAP_metaObject;
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

namespace Gap {
namespace Bec {

void beNumVerData::userConstruct(int flag) {
    int i;
    void *allocator;
    Gap__Core__igObject__userConstruct((::igObject *)this);
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    if (!(flag & 0xFF)) {
        i = 0;
        do {
            allocator = ((Gap::Core::igObject *)this)->getMemoryPool();
            allocator = (g_useOwnerAllocator != 0) ? allocator : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
            {
                igSmartPointer< ::beNumVerInsideData> item((::beNumVerInsideData *)Gap::Bec::beNumVerInsideData::_instantiateFromPool((igMemoryPoolView *)allocator));
                ((Gap::Core::igObjectList *)_verDataList)->append((Gap::Core::igObject *)item.p);
            }
            i += 1;
        } while (i < 6);
    }
}
}
}

namespace Gap {
namespace Bec {

void beNumVerData::userDestruct() {
    igObjectList *list = (igObjectList *)(beNumVerInsideDataList *)_verDataList;

    if (list->getCount() > 0) {
        list->removeAll();
    }
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct((::beNumVerData *)this);
}
}
}

igMetaObject *beNumberCtrlInfoRam_GetMeta(void)
{
    return g_beNumberCtrlInfoRam_metaObject;
}

igMetaObject *beOptInfo_GetMeta(void)
{
    return g_beOptInfo_metaObject;
}

igMetaObject *beParticleCtrl2Info_GetMeta(void)
{
    return g_beParticleCtrl2Info_metaObject;
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

namespace Gap {
namespace Bec {

void beSaveDataDeliver::userConstruct(int flag) {
    Gap__Core__igObject__userConstruct((::igObject *)this);
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
}

void beSaveDataDeliver::userDestruct() {
    int data;

    data = _data;
    if (data != 0) {
        Memory_FreeBuffer((void *)data);
    }
    _data = 0;
    _size = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct((::beSaveDataDeliver *)this);
}

void beSvPlatDataGC::userConstruct(int flag) {
    Gap__Core__igObject__userConstruct((::igObject *)this);
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
}

void beSvPlatDataGC::userDestruct() {
    if (_banTplData != 0) {
        Memory_FreeBuffer((void *)_banTplData);
    }
    if (_iconTplData != 0) {
        Memory_FreeBuffer((void *)_iconTplData);
    }
    _banTplData = 0;
    _iconTplData = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct((::beSvPlatDataGC *)this);
}

void beSvPs2McImage128k::userConstruct(int flag) {
    Gap__Core__igObject__userConstruct((::igObject *)this);
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    if (!(flag & 0xFF)) {
        _data = (int)Memory_AllocateDefaultBuffer(0x20000);
    }
}

void beSvPs2McImage128k::userDestruct() {
    if (_data != 0) {
        Memory_FreeBuffer((void *)_data);
    }
    _data = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct((::beSvPs2McImage128k *)this);
}

void beXboxImage24k::userConstruct(int flag) {
    Gap__Core__igObject__userConstruct((::igObject *)this);
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    if (!(flag & 0xFF)) {
        _data = (int)Memory_AllocateDefaultBuffer(0x6000);
        _dataSize = 0x6000;
    }
}

void beXboxImage24k::userDestruct() {
    int data;

    data = _data;
    if (data != 0) {
        Memory_FreeBuffer((void *)data);
    }
    _data = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)this)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct((::beXboxImage24k *)this);
}
}
}

igMetaObject *beSvPlatDataXbox_GetMeta(void)
{
    return g_beSvPlatDataXbox_metaObject;
}

igMetaObject *beSaveUtilInfo_GetMeta(void)
{
    return g_beSaveUtilInfo_metaObject;
}

igMetaObject *beSaveUtilInfoRam_GetMeta(void)
{
    return g_beSaveUtilInfoRam_metaObject;
}

igMetaObject *beSeInfo_GetMeta(void)
{
    return g_beSeInfo_metaObject;
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

igMetaObject *beSoundData_GetMeta(void)
{
    return g_beSoundData_metaObject;
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

igMetaObject *beWaterPlainInfo_GetMeta(void)
{
    return g_beWaterPlainInfo_metaObject;
}

igMetaObject *beWaterPlainInfoRam_GetMeta(void)
{
    return g_beWaterPlainInfoRam_metaObject;
}

igMetaObject *igModelViewMatrixBoneSelectList_GetMeta(void)
{
    return g_igModelViewMatrixBoneSelectListBec_metaObject;
}

igMetaObject *beWeaponAttachData_GetMeta(void)
{
    return g_beWeaponAttachData_metaObject;
}

igMetaObject *beWeaponAttachDataList_GetMeta(void)
{
    return g_beWeaponAttachDataList_metaObject;
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

igMetaObject *beCriHandleList_GetElementMeta(void)
{
    return g_beCriHandle_metaObject;
}

igMetaObject *beDataObjListList_GetElementMeta(void)
{
    return g_beDataObjList_metaObject;
}

igMetaObject *beFontImageList_GetElementMeta(void)
{
    return g_beFontImage_metaObject;
}

igMetaObject *beGeneraterDataList_GetElementMeta(void)
{
    return g_beGeneraterData_metaObject;
}

igMetaObject *beGeneraterItemDataList_GetElementMeta(void)
{
    return g_beGeneraterItemData_metaObject;
}

igMetaObject *beGroupKeepList_GetElementMeta(void)
{
    return g_beGroupKeep_metaObject;
}

igMetaObject *beLuaDataList_GetElementMeta(void)
{
    return g_beLuaData_metaObject;
}

igMetaObject *beLuaDataObjectist_GetElementMeta(void)
{
    return Gap::Bec::beLuaDataObject::getClassMeta();
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

igMetaObject *beModelCtrlDataList_GetElementMeta(void)
{
    return g_beModelCtrlData_metaObject;
}

igMetaObject *beNumberCtrlInfoList_GetElementMeta(void)
{
    return g_beNumberCtrlInfo_metaObject;
}

igMetaObject *beShadow01InfoList_GetElementMeta(void)
{
    return g_beShadow01Info_metaObject;
}

igMetaObject *beTextureCtrlInfoList_GetElementMeta(void)
{
    return g_beTextureCtrlInfo_metaObject;
}

igMetaObject *beWeaponAttachDataList_GetElementMeta(void)
{
    return g_beWeaponAttachData_metaObject;
}

igMetaObject *beBaseInfoManagerList_GetElementMeta(void)
{
    return g_beBaseInfoManager_metaObject;
}

igMetaObject *beMessengerGroupList_GetElementMeta(void)
{
    return g_beMessengerGroup_metaObject;
}

igMetaObject *beBaseInfoRamList_GetElementMeta(void)
{
    return g_beBaseInfoRam_metaObject;
}

igMetaObject *beBaseInfoList_GetElementMeta(void)
{
    return g_beBaseInfo_metaObject;
}
