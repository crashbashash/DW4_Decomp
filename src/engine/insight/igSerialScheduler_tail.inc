static inline void setRetained(SchedulerManager *manager, ManagerArray *list, int index) {
    igObject *previous;

    if (manager != 0) {
        ((igObject *)manager)->_refCount = ((igObject *)manager)->_refCount + 1;
    }
    previous = (igObject *)list->_data[index];
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        list->_data[index] = manager;
    }
}

/* matching construct: 4 variants, the inline parameter order */
void Gap__Insight__igSerialScheduler__vfunc_23(igSerialScheduler *scheduler) {
    unsigned int count = ((ManagerListView *)scheduler->_managerList)->_list->_count;
    int i;

    ObjectList_ResizeRetained((ManagerArray *)scheduler->_cachedManagerList, count);
    for (i = 0; i < count; i++) {
        setRetained(((ManagerListView *)scheduler->_managerList)->_list->_data[i], (ManagerArray *)scheduler->_cachedManagerList, i);
    }
    for (i = 0; i < count; i++) {
        ((ManagerArray *)scheduler->_cachedManagerList)->_data[i]->update();
    }
    ObjectList_ResizeRetained((ManagerArray *)scheduler->_cachedManagerList, 0);
}

void Gap__Insight__igSerialScheduler__vfunc_24(void *arg0, int arg1) {
    FUN_002d6f50(*(int *)((char *)(arg0) + 8), arg1, 1);
}

void Gap__Insight__igSerialScheduler__vfunc_25(Obj_238020 *arg0, int arg1) {
    int sp1C;
    FUN_002d7750(&sp1C, arg0->f8, arg1);
}

void Gap__Insight__igSerialScheduler__vfunc_27(int a0) {
    FUN_002d7090(*(int *)((char *)a0 + 8));
}

void Gap__Insight__igSerialScheduler__vfunc_28(S0 *arg0, int arg1, int arg2) {
    int sp1C;

    FUN_002d7760(&sp1C, arg0->f8, arg1, arg2);
}

void Gap__Insight__igSerialScheduler__vfunc_29(int a0) {
    FUN_002d7840(*(int *)((char *)a0 + 8));
}

void *FUN_00238110(void *arg0) {
    *(int *)((char *)(arg0) + 0) = 0;
    *(char *)((char *)(arg0) + 4) = 1;
    *(char *)((char *)(arg0) + 5) = 0;
    *(int *)((char *)(arg0) + 8) = 0;
    *(int *)((char *)(arg0) + 12) = 0x3F800000;
    *(int *)((char *)(arg0) + 16) = 0;
    *(int *)((char *)(arg0) + 20) = 0x3F800000;
    *(int *)((char *)(arg0) + 24) = 0x3F800000;
    *(int *)((char *)(arg0) + 28) = 0x3F000000;
    *(int *)((char *)(arg0) + 32) = 0;
    *(int *)((char *)(arg0) + 36) = 0x3F800000;
    *(int *)((char *)(arg0) + 40) = 0x3F800000;
    *(int *)((char *)(arg0) + 44) = 0;
    *(int *)((char *)(arg0) + 48) = 0;
    *(int *)((char *)(arg0) + 52) = 0x3F800000;
    *(float *)((char *)(arg0) + 56) = (float) 0.00100000005f;
    *(char *)((char *)(arg0) + 60) = 1;
    *(int *)((char *)(arg0) + 64) = 0x42340000;
    *(char *)((char *)(arg0) + 68) = 1;
    *(float *)((char *)(arg0) + 72) = (float) 0.100000001f;
    *(int *)((char *)(arg0) + 76) = 0x447A0000;
    *(float *)((char *)(arg0) + 80) = (float) DAT_004e1058[0];
    *(float *)((char *)(arg0) + 84) = (float) DAT_004e105c[0];
    *(float *)((char *)(arg0) + 88) = (float) DAT_004e1060[0];
    *(char *)((char *)(arg0) + 92) = 1;
    *(char *)((char *)(arg0) + 93) = 0;
    *(char *)((char *)(arg0) + 94) = 0;
    *(char *)((char *)(arg0) + 95) = 0;
    *(char *)((char *)(arg0) + 96) = 0;
    *(int *)((char *)(arg0) + 100) = 0x3F800000;
    *(int *)((char *)(arg0) + 104) = 0x3F800000;
    *(int *)((char *)(arg0) + 108) = 0x3F800000;
    *(int *)((char *)(arg0) + 112) = 0x3F800000;
    *(int *)((char *)(arg0) + 116) = 0x3F800000;
    *(int *)((char *)(arg0) + 120) = 0x3F800000;
    *(int *)((char *)(arg0) + 124) = 0x3F800000;
    *(int *)((char *)(arg0) + 128) = 0x3F800000;
    *(float *)((char *)(arg0) + 132) = (float) DAT_004e1170[0];
    *(float *)((char *)(arg0) + 136) = (float) DAT_004e1174[0];
    *(float *)((char *)(arg0) + 140) = (float) DAT_004e1178[0];
    *(float *)((char *)(arg0) + 144) = (float) DAT_004e117c[0];
    *(float *)((char *)(arg0) + 148) = (float) 0.200000003f;
    *(float *)((char *)(arg0) + 152) = (float) 0.200000003f;
    *(float *)((char *)(arg0) + 156) = (float) 0.200000003f;
    *(int *)((char *)(arg0) + 160) = 0x3F800000;
    *(char *)((char *)(arg0) + 164) = 0;
    *(char *)((char *)(arg0) + 165) = 0;
    *(char *)((char *)(arg0) + 166) = 0;
    *(char *)((char *)(arg0) + 167) = 0;
    *(char *)((char *)(arg0) + 168) = 0;
    *(char *)((char *)(arg0) + 169) = 0;
    *(float *)((char *)(arg0) + 172) = (float) 0.100000001f;
    *(int *)((char *)(arg0) + 176) = 0;
    *(char *)((char *)(arg0) + 180) = 1;
    *(char *)((char *)(arg0) + 181) = 0;
    *(char *)((char *)(arg0) + 182) = 0;
    *(int *)((char *)(arg0) + 184) = 0x280;
    *(int *)((char *)(arg0) + 188) = 0x1C0;
    *(int *)((char *)(arg0) + 192) = 0;
    *(int *)((char *)(arg0) + 196) = -1;
    *(int *)((char *)(arg0) + 200) = -1;
    *(int *)((char *)(arg0) + 204) = -1;
    *(int *)((char *)(arg0) + 208) = -1;
    *(char *)((char *)(arg0) + 212) = 1;
    *(char *)((char *)(arg0) + 213) = 1;
    *(char *)((char *)(arg0) + 214) = 1;
    *(char *)((char *)(arg0) + 215) = 0;
    *(char *)((char *)(arg0) + 216) = 0;
    *(int *)((char *)(arg0) + 220) = 5;
    *(int *)((char *)(arg0) + 224) = 0x1E;
    *(char *)((char *)(arg0) + 228) = 0;
    *(char *)((char *)(arg0) + 229) = 0;
    *(int *)((char *)(arg0) + 232) = 0;
    *(int *)((char *)(arg0) + 236) = 0;
    FUN_002382e0((ViewerOptions_2382e0 *)arg0, -1, 0x1C0, 0x280, 0x447A0000, 0x42340000, 0x3F800000, 1);
    return arg0;
}

/* Matching construct: `group` is declared apart from `props` so the property set lands in the first saved register. */
void FUN_002382e0(ViewerOptions_2382e0 *opt, int, int, int, int, int, int, int) {
  int group;
  int props = ((PropertySet *)DAT_00586dc8[0])->props;
  group = FUN_00306360(props, DAT_004e9870, 0);
  if (group < 0) {
    group = FUN_00306360(props, DAT_004e9878, 0);
    if (group < 0) return;
  }
  if (DAT_004e9880) thunk_FUN_00306910(props, group, DAT_004e9880, &opt->extraCommandLine, opt->extraCommandLine, 0);
  if (DAT_004e9898) thunk_FUN_00306e50(props, group, DAT_004e9898, &opt->showBBox, opt->showBBox, 0);
  if (DAT_004e98a8) thunk_FUN_00306e50(props, group, DAT_004e98a8, &opt->showNormals, opt->showNormals, 0);
  if (DAT_004e98b8) FUN_001e71f0(props, group, DAT_004e98b8, &opt->normalsColor, &opt->normalsColor, 0);
  if (DAT_004e98d0) FUN_001e71f0(props, group, DAT_004e98d0, &opt->invalidStoredNormalsColor, &opt->invalidStoredNormalsColor, 0);
  if (DAT_004e98f0) FUN_001e71f0(props, group, DAT_004e98f0, &opt->scaledNormalsColor, &opt->scaledNormalsColor, 0);
  if (DAT_004e9910) thunk_FUN_003066b0(props, group, DAT_004e9910, &opt->invalidNormalsPrecision, 0, opt->invalidNormalsPrecision);
  if (DAT_004e9930) thunk_FUN_00306e50(props, group, DAT_004e9930, &opt->autoSelectCamera, opt->autoSelectCamera, 0);
  if (DAT_004e9950) thunk_FUN_003066b0(props, group, DAT_004e9950, &opt->horizontalFieldOfView, 0, opt->horizontalFieldOfView);
  if (DAT_004e9968) thunk_FUN_00306e50(props, group, DAT_004e9968, &opt->autoPlanes, opt->autoPlanes, 0);
  if (DAT_004e9980) thunk_FUN_003066b0(props, group, DAT_004e9980, &opt->defaultNearPlane, 0, opt->defaultNearPlane);
  if (DAT_004e99a0) thunk_FUN_003066b0(props, group, DAT_004e99a0, &opt->defaultFarPlane, 0, opt->defaultFarPlane);
  if (DAT_004e99b0) FUN_001e70a0(props, group, DAT_004e99b0, &opt->upVector, &opt->upVector, 0);
  if (DAT_004e99c0) thunk_FUN_00306e50(props, group, DAT_004e99c0, &opt->autoSceneLights, opt->autoSceneLights, 0);
  if (DAT_004e99d0) thunk_FUN_00306e50(props, group, DAT_004e99d0, &opt->autoHeadLight, opt->autoHeadLight, 0);
  if (DAT_004e99e0) thunk_FUN_00306e50(props, group, DAT_004e99e0, &opt->useSceneLights, opt->useSceneLights, 0);
  if (DAT_004e99f0) thunk_FUN_00306e50(props, group, DAT_004e99f0, &opt->useHeadLight, opt->useHeadLight, 0);
  if (DAT_004e9a00) thunk_FUN_00306e50(props, group, DAT_004e9a00, &opt->useHeadLightSpecular, opt->useHeadLightSpecular, 0);
  if (DAT_004e9a20) FUN_001e71f0(props, group, DAT_004e9a20, &opt->headLightDiffuse, &opt->headLightDiffuse, 0);
  if (DAT_004e9a40) FUN_001e71f0(props, group, DAT_004e9a40, &opt->headLightSpecular, &opt->headLightSpecular, 0);
  if (DAT_004e9a60) FUN_001e71f0(props, group, DAT_004e9a60, &opt->headLightAmbient, &opt->headLightAmbient, 0);
  if (DAT_004e9a78) FUN_001e71f0(props, group, DAT_004e9a78, &opt->clearColor, &opt->clearColor, 0);
  if (DAT_004e9a88) thunk_FUN_00306e50(props, group, DAT_004e9a88, &opt->wireframeMode, opt->wireframeMode, 0);
  if (DAT_004e9a98) thunk_FUN_00306e50(props, group, DAT_004e9a98, &opt->forceWireframe, opt->forceWireframe, 0);
  if (DAT_004e9ab0) thunk_FUN_00306e50(props, group, DAT_004e9ab0, &opt->backFaceCullingMode, opt->backFaceCullingMode, 0);
  if (DAT_004e9ad0) thunk_FUN_00306e50(props, group, DAT_004e9ad0, &opt->forceBackFaceCulling, opt->forceBackFaceCulling, 0);
  if (DAT_004e9ae8) thunk_FUN_00306e50(props, group, DAT_004e9ae8, &opt->alphaTest, opt->alphaTest, 0);
  if (DAT_004e9af8) thunk_FUN_00306e50(props, group, DAT_004e9af8, &opt->forceAlphaTest, opt->forceAlphaTest, 0);
  if (DAT_004e9b10) thunk_FUN_003066b0(props, group, DAT_004e9b10, &opt->alphaTestReference, 0, opt->alphaTestReference);
  if (DAT_004e9b28) thunk_FUN_003066b0(props, group, DAT_004e9b28, &opt->maxFrameRate, 0, opt->maxFrameRate);
  if (DAT_004e9b40) thunk_FUN_00306e50(props, group, DAT_004e9b40, &opt->optimizeTextures, opt->optimizeTextures, 0);
  if (DAT_004e9b58) thunk_FUN_00306e50(props, group, DAT_004e9b58, &opt->halfBuffer, opt->halfBuffer, 0);
  if (DAT_004e9b68) thunk_FUN_00306e50(props, group, DAT_004e9b68, &opt->palVideoMode, opt->palVideoMode, 0);
  if (DAT_004e9b78) thunk_FUN_003065f0(props, group, DAT_004e9b78, &opt->width, opt->width, 0);
  if (DAT_004e9b80) thunk_FUN_003065f0(props, group, DAT_004e9b80, &opt->height, opt->height, 0);
  if (DAT_004e9b88) thunk_FUN_003065f0(props, group, DAT_004e9b88, &opt->swapInterval, opt->swapInterval, 0);
  if (DAT_004e9b98) thunk_FUN_003065f0(props, group, DAT_004e9b98, &opt->colorBits, opt->colorBits, 0);
  if (DAT_004e9ba8) thunk_FUN_003065f0(props, group, DAT_004e9ba8, &opt->alphaBits, opt->alphaBits, 0);
  if (DAT_004e9bb8) thunk_FUN_003065f0(props, group, DAT_004e9bb8, &opt->depthBits, opt->depthBits, 0);
  if (DAT_004e9bc8) thunk_FUN_003065f0(props, group, DAT_004e9bc8, &opt->stencilBits, opt->stencilBits, 0);
  if (DAT_004e9be0) thunk_FUN_00306e50(props, group, DAT_004e9be0, &opt->reportVideoFormat, opt->reportVideoFormat, 0);
  if (DAT_004e9bf8) thunk_FUN_00306e50(props, group, DAT_004e9bf8, &opt->showLogo, opt->showLogo, 0);
  if (DAT_004e9c08) thunk_FUN_00306e50(props, group, DAT_004e9c08, &opt->showUI, opt->showUI, 0);
  if (DAT_004e9c10) thunk_FUN_00306e50(props, group, DAT_004e9c10, &opt->enableMayaControls, opt->enableMayaControls, 0);
  if (DAT_004e9c28) thunk_FUN_00306e50(props, group, DAT_004e9c28, &opt->benchmark, opt->benchmark, 0);
  if (DAT_004e9c40) thunk_FUN_003065f0(props, group, DAT_004e9c40, &opt->benchmarkSkipFrames, opt->benchmarkSkipFrames, 0);
  if (DAT_004e9c60) thunk_FUN_003065f0(props, group, DAT_004e9c60, &opt->benchmarkFrames, opt->benchmarkFrames, 0);
  if (DAT_004e9c70) thunk_FUN_00306e50(props, group, DAT_004e9c70, &opt->columnStatistics, opt->columnStatistics, 0);
  if (DAT_004e9c90) thunk_FUN_00306e50(props, group, DAT_004e9c90, &opt->allocateVisualContextInScratchPad, opt->allocateVisualContextInScratchPad, 0);
}

