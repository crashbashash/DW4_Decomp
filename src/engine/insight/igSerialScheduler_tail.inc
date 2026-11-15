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
    igRendererOrderedList_Append(*(int *)((char *)(arg0) + 8), arg1, 1);
}

void Gap__Insight__igSerialScheduler__vfunc_25(Obj_238020 *arg0, int arg1) {
    int sp1C;
    igObjectList_RemoveRetained(&sp1C, arg0->f8, arg1);
}

void Gap__Insight__igSerialScheduler__vfunc_27(int a0) {
    igDependencyOrderedList_AddDependency(*(int *)((char *)a0 + 8));
}

void Gap__Insight__igSerialScheduler__vfunc_28(S0 *arg0, int arg1, int arg2) {
    int sp1C;

    igDependencyOrderedList_RemoveDependency(&sp1C, arg0->f8, arg1, arg2);
}

void Gap__Insight__igSerialScheduler__vfunc_29(int a0) {
    igDependencyOrderedList_RemoveDependencies(*(int *)((char *)a0 + 8));
}

void *ViewerOptions_Construct(void *arg0) {
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
    *(float *)((char *)(arg0) + 80) = (float) g_vec3Zero[0];
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
    *(float *)((char *)(arg0) + 132) = (float) g_vec4Zero[0];
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
  int props = ((PropertySet *)g_objectSystem[0])->props;
  group = igRegistry_GetSectionIndex(props, "INSIGHT", 0);
  if (group < 0) {
    group = igRegistry_GetSectionIndex(props, "Viewer", 0);
    if (group < 0) return;
  }
  { const char *key = "extraCommandLine"; if (key) thunk_igRegistry_GetValueString(props, group, key, &opt->extraCommandLine, opt->extraCommandLine, 0); }
  { const char *key = "showBBox"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->showBBox, opt->showBBox, 0); }
  { const char *key = "showNormals"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->showNormals, opt->showNormals, 0); }
  { const char *key = "normalsColor"; if (key) FUN_001e71f0(props, group, key, &opt->normalsColor, &opt->normalsColor, 0); }
  { const char *key = "invalidStoredNormalsColor"; if (key) FUN_001e71f0(props, group, key, &opt->invalidStoredNormalsColor, &opt->invalidStoredNormalsColor, 0); }
  { const char *key = "scaledNormalsColor"; if (key) FUN_001e71f0(props, group, key, &opt->scaledNormalsColor, &opt->scaledNormalsColor, 0); }
  { const char *key = "invalidNormalsPrecision"; if (key) thunk_igRegistry_GetValueFloat(props, group, key, &opt->invalidNormalsPrecision, 0, opt->invalidNormalsPrecision); }
  { const char *key = "autoSelectCamera"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->autoSelectCamera, opt->autoSelectCamera, 0); }
  { const char *key = "horizontalFieldOfView"; if (key) thunk_igRegistry_GetValueFloat(props, group, key, &opt->horizontalFieldOfView, 0, opt->horizontalFieldOfView); }
  { const char *key = "autoPlanes"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->autoPlanes, opt->autoPlanes, 0); }
  { const char *key = "defaultNearPlane"; if (key) thunk_igRegistry_GetValueFloat(props, group, key, &opt->defaultNearPlane, 0, opt->defaultNearPlane); }
  { const char *key = "defaultFarPlane"; if (key) thunk_igRegistry_GetValueFloat(props, group, key, &opt->defaultFarPlane, 0, opt->defaultFarPlane); }
  { const char *key = "upVector"; if (key) FUN_001e70a0(props, group, key, &opt->upVector, &opt->upVector, 0); }
  { const char *key = "autoSceneLights"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->autoSceneLights, opt->autoSceneLights, 0); }
  { const char *key = "autoHeadLight"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->autoHeadLight, opt->autoHeadLight, 0); }
  { const char *key = "useSceneLights"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->useSceneLights, opt->useSceneLights, 0); }
  { const char *key = "useHeadLight"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->useHeadLight, opt->useHeadLight, 0); }
  { const char *key = "useHeadLightSpecular"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->useHeadLightSpecular, opt->useHeadLightSpecular, 0); }
  { const char *key = "headLightDiffuse"; if (key) FUN_001e71f0(props, group, key, &opt->headLightDiffuse, &opt->headLightDiffuse, 0); }
  { const char *key = "headLightSpecular"; if (key) FUN_001e71f0(props, group, key, &opt->headLightSpecular, &opt->headLightSpecular, 0); }
  { const char *key = "headLightAmbient"; if (key) FUN_001e71f0(props, group, key, &opt->headLightAmbient, &opt->headLightAmbient, 0); }
  { const char *key = "clearColor"; if (key) FUN_001e71f0(props, group, key, &opt->clearColor, &opt->clearColor, 0); }
  { const char *key = "wireframeMode"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->wireframeMode, opt->wireframeMode, 0); }
  { const char *key = "forceWireframe"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->forceWireframe, opt->forceWireframe, 0); }
  { const char *key = "backFaceCullingMode"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->backFaceCullingMode, opt->backFaceCullingMode, 0); }
  { const char *key = "forceBackFaceCulling"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->forceBackFaceCulling, opt->forceBackFaceCulling, 0); }
  { const char *key = "alphaTest"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->alphaTest, opt->alphaTest, 0); }
  { const char *key = "forceAlphaTest"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->forceAlphaTest, opt->forceAlphaTest, 0); }
  { const char *key = "alphaTestReference"; if (key) thunk_igRegistry_GetValueFloat(props, group, key, &opt->alphaTestReference, 0, opt->alphaTestReference); }
  { const char *key = "maxFrameRate"; if (key) thunk_igRegistry_GetValueFloat(props, group, key, &opt->maxFrameRate, 0, opt->maxFrameRate); }
  { const char *key = "optimizeTextures"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->optimizeTextures, opt->optimizeTextures, 0); }
  { const char *key = "halfBuffer"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->halfBuffer, opt->halfBuffer, 0); }
  { const char *key = "palVideoMode"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->palVideoMode, opt->palVideoMode, 0); }
  { const char *key = "width"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->width, opt->width, 0); }
  { const char *key = "height"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->height, opt->height, 0); }
  { const char *key = "swapInterval"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->swapInterval, opt->swapInterval, 0); }
  { const char *key = "colorBits"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->colorBits, opt->colorBits, 0); }
  { const char *key = "alphaBits"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->alphaBits, opt->alphaBits, 0); }
  { const char *key = "depthBits"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->depthBits, opt->depthBits, 0); }
  { const char *key = "stencilBits"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->stencilBits, opt->stencilBits, 0); }
  { const char *key = "reportVideoFormat"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->reportVideoFormat, opt->reportVideoFormat, 0); }
  { const char *key = "showLogo"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->showLogo, opt->showLogo, 0); }
  { const char *key = "showUI"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->showUI, opt->showUI, 0); }
  { const char *key = "enableMayaControls"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->enableMayaControls, opt->enableMayaControls, 0); }
  { const char *key = "benchmark"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->benchmark, opt->benchmark, 0); }
  { const char *key = "benchmarkSkipFrames"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->benchmarkSkipFrames, opt->benchmarkSkipFrames, 0); }
  { const char *key = "benchmarkFrames"; if (key) thunk_igRegistry_GetValueInt(props, group, key, &opt->benchmarkFrames, opt->benchmarkFrames, 0); }
  { const char *key = "columnStatistics"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->columnStatistics, opt->columnStatistics, 0); }
  { const char *key = "allocateVisualContextInScratchPad"; if (key) thunk_igRegistry_GetValueBool(props, group, key, &opt->allocateVisualContextInScratchPad, opt->allocateVisualContextInScratchPad, 0); }
}

