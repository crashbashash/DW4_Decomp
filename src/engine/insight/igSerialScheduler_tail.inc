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
void igSerialScheduler_Update(igSerialScheduler *scheduler) {
    unsigned int count = ((ManagerListView *)scheduler->_managerList)->_list->_count;
    int i;

    ObjectList_ResizeRetained((igTDataList<igObject *> *)scheduler->_cachedManagerList, count);
    for (i = 0; i < count; i++) {
        setRetained(((ManagerListView *)scheduler->_managerList)->_list->_data[i], (ManagerArray *)scheduler->_cachedManagerList, i);
    }
    for (i = 0; i < count; i++) {
        ((ManagerArray *)scheduler->_cachedManagerList)->_data[i]->update();
    }
    ObjectList_ResizeRetained((igTDataList<igObject *> *)scheduler->_cachedManagerList, 0);
}

void igSerialScheduler_Schedule(void *arg0, int arg1) {
    igRendererOrderedList_Append((igDependencyOrderedList *)(*(int *)((char *)(arg0) + 8)), (igObject *)arg1, 1);
}

void igSerialScheduler_Unschedule(Obj_238020 *arg0, int arg1) {
    igObjectList_RemoveRetained((igDependencyOrderedList *)arg0->f8, (igObject *)arg1);
}

/* Whether the scheduler already holds manager. */
int igSerialScheduler_IsScheduled(igSerialScheduler *scheduler, igObject *manager) {
    igDependencyOrderedList *managers = (igDependencyOrderedList *)scheduler->_managerList;
    /* matching construct: the copy taken by address keeps the manager in the 12(sp) slot, stored after the first list load. */
    igObject *item = manager;
    igObjectList *list = (igObjectList *)managers->_objectList;
    return indexOfItem(list, &item) >= 0;
}

void igSerialScheduler_AppendDependency(S0 *arg0, void *arg1, void *arg2) {
    igDependencyOrderedList_AddDependency((igDependencyOrderedList *)arg0->f8, arg1, arg2);
}

void igSerialScheduler_RemoveDependency(S0 *arg0, void *arg1, void *arg2) {
    igDependencyOrderedList_RemoveDependency((igDependencyOrderedList *)arg0->f8, arg1, arg2);
}

void igSerialScheduler_RemoveAllDependencies(S0 *arg0, void *arg1) {
    igDependencyOrderedList_RemoveDependencies((igDependencyOrderedList *)arg0->f8, arg1);
}

SharedViewerOptions *igViewerDefaults_Construct(SharedViewerOptions *self) {
    self->extraCommandLine = 0;
    self->showBBox = 1;
    self->showNormals = 0;
    self->normalsColor[0] = 0.0f;
    self->normalsColor[1] = 1.0f;
    self->normalsColor[2] = 0.0f;
    self->normalsColor[3] = 1.0f;
    self->invalidStoredNormalsColor[0] = 1.0f;
    self->invalidStoredNormalsColor[1] = 0.5f;
    self->invalidStoredNormalsColor[2] = 0.0f;
    self->invalidStoredNormalsColor[3] = 1.0f;
    self->scaledNormalsColor[0] = 1.0f;
    self->scaledNormalsColor[1] = 0.0f;
    self->scaledNormalsColor[2] = 0.0f;
    self->scaledNormalsColor[3] = 1.0f;
    self->invalidNormalsPrecision = 0.001f;
    self->autoSelectCamera = 1;
    self->horizontalFieldOfView = 45.0f;
    self->autoPlanes = 1;
    self->defaultNearPlane = 0.1f;
    self->defaultFarPlane = 1000.0f;
    self->upVector[0] = g_vec3Zero.x;
    self->upVector[1] = g_vec3Zero.y;
    self->upVector[2] = g_vec3Zero.z;
    self->autoSceneLights = 1;
    self->autoHeadLight = 0;
    self->useSceneLights = 0;
    self->useHeadLight = 0;
    self->useHeadLightSpecular = 0;
    self->headLightDiffuse[0] = 1.0f;
    self->headLightDiffuse[1] = 1.0f;
    self->headLightDiffuse[2] = 1.0f;
    self->headLightDiffuse[3] = 1.0f;
    self->headLightSpecular[0] = 1.0f;
    self->headLightSpecular[1] = 1.0f;
    self->headLightSpecular[2] = 1.0f;
    self->headLightSpecular[3] = 1.0f;
    self->headLightAmbient[0] = g_vec4Zero.x;
    self->headLightAmbient[1] = g_vec4Zero.y;
    self->headLightAmbient[2] = g_vec4Zero.z;
    self->headLightAmbient[3] = g_vec4Zero.w;
    self->clearColor[0] = 0.2f;
    self->clearColor[1] = 0.2f;
    self->clearColor[2] = 0.2f;
    self->clearColor[3] = 1.0f;
    self->wireframeMode = 0;
    self->forceWireframe = 0;
    self->backFaceCullingMode = 0;
    self->forceBackFaceCulling = 0;
    self->alphaTest = 0;
    self->forceAlphaTest = 0;
    self->alphaTestReference = 0.1f;
    self->maxFrameRate = 0.0f;
    self->optimizeTextures = 1;
    self->halfBuffer = 0;
    self->palVideoMode = 0;
    self->width = 640;
    self->height = 448;
    self->swapInterval = 0;
    self->colorBits = -1;
    self->alphaBits = -1;
    self->depthBits = -1;
    self->stencilBits = -1;
    self->reportVideoFormat = 1;
    self->showLogo = 1;
    self->showUI = 1;
    self->enableMayaControls = 0;
    self->benchmark = 0;
    self->benchmarkSkipFrames = 5;
    self->benchmarkFrames = 30;
    self->columnStatistics = 0;
    self->allocateVisualContextInScratchPad = 0;
    self->useCount = 0;
    self->internedString = 0;
    igViewerDefaults_LoadFromRegistry(self);
    return self;
}

/* matching construct: variant search — `section` is declared apart from `registry` so the registry lands in the first saved register */
void igViewerDefaults_LoadFromRegistry(SharedViewerOptions *self) {
    int section;
    igRegistry *registry = g_objectSystem->configRegistry;
    section = igRegistry_GetSectionIndex(registry, (char *)"INSIGHT", 0);
    if (section < 0) {
        section = igRegistry_GetSectionIndex(registry, (char *)"Viewer", 0);
        if (section < 0) return;
    }
    { const char *key = "extraCommandLine"; if (key) igGetRegistryValue_String(registry, section, key, &self->extraCommandLine, self->extraCommandLine, 0); }
    { const char *key = "showBBox"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->showBBox, self->showBBox, 0); }
    { const char *key = "showNormals"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->showNormals, self->showNormals, 0); }
    { const char *key = "normalsColor"; if (key) igGetRegistryValue_Vec4f(registry, section, key, self->normalsColor, self->normalsColor, 0); }
    { const char *key = "invalidStoredNormalsColor"; if (key) igGetRegistryValue_Vec4f(registry, section, key, self->invalidStoredNormalsColor, self->invalidStoredNormalsColor, 0); }
    { const char *key = "scaledNormalsColor"; if (key) igGetRegistryValue_Vec4f(registry, section, key, self->scaledNormalsColor, self->scaledNormalsColor, 0); }
    { const char *key = "invalidNormalsPrecision"; if (key) igGetRegistryValue_Float(registry, section, key, &self->invalidNormalsPrecision, 0, self->invalidNormalsPrecision); }
    { const char *key = "autoSelectCamera"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->autoSelectCamera, self->autoSelectCamera, 0); }
    { const char *key = "horizontalFieldOfView"; if (key) igGetRegistryValue_Float(registry, section, key, &self->horizontalFieldOfView, 0, self->horizontalFieldOfView); }
    { const char *key = "autoPlanes"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->autoPlanes, self->autoPlanes, 0); }
    { const char *key = "defaultNearPlane"; if (key) igGetRegistryValue_Float(registry, section, key, &self->defaultNearPlane, 0, self->defaultNearPlane); }
    { const char *key = "defaultFarPlane"; if (key) igGetRegistryValue_Float(registry, section, key, &self->defaultFarPlane, 0, self->defaultFarPlane); }
    { const char *key = "upVector"; if (key) igGetRegistryValue_Vec3f(registry, section, key, self->upVector, self->upVector, 0); }
    { const char *key = "autoSceneLights"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->autoSceneLights, self->autoSceneLights, 0); }
    { const char *key = "autoHeadLight"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->autoHeadLight, self->autoHeadLight, 0); }
    { const char *key = "useSceneLights"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->useSceneLights, self->useSceneLights, 0); }
    { const char *key = "useHeadLight"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->useHeadLight, self->useHeadLight, 0); }
    { const char *key = "useHeadLightSpecular"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->useHeadLightSpecular, self->useHeadLightSpecular, 0); }
    { const char *key = "headLightDiffuse"; if (key) igGetRegistryValue_Vec4f(registry, section, key, self->headLightDiffuse, self->headLightDiffuse, 0); }
    { const char *key = "headLightSpecular"; if (key) igGetRegistryValue_Vec4f(registry, section, key, self->headLightSpecular, self->headLightSpecular, 0); }
    { const char *key = "headLightAmbient"; if (key) igGetRegistryValue_Vec4f(registry, section, key, self->headLightAmbient, self->headLightAmbient, 0); }
    { const char *key = "clearColor"; if (key) igGetRegistryValue_Vec4f(registry, section, key, self->clearColor, self->clearColor, 0); }
    { const char *key = "wireframeMode"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->wireframeMode, self->wireframeMode, 0); }
    { const char *key = "forceWireframe"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->forceWireframe, self->forceWireframe, 0); }
    { const char *key = "backFaceCullingMode"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->backFaceCullingMode, self->backFaceCullingMode, 0); }
    { const char *key = "forceBackFaceCulling"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->forceBackFaceCulling, self->forceBackFaceCulling, 0); }
    { const char *key = "alphaTest"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->alphaTest, self->alphaTest, 0); }
    { const char *key = "forceAlphaTest"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->forceAlphaTest, self->forceAlphaTest, 0); }
    { const char *key = "alphaTestReference"; if (key) igGetRegistryValue_Float(registry, section, key, &self->alphaTestReference, 0, self->alphaTestReference); }
    { const char *key = "maxFrameRate"; if (key) igGetRegistryValue_Float(registry, section, key, &self->maxFrameRate, 0, self->maxFrameRate); }
    { const char *key = "optimizeTextures"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->optimizeTextures, self->optimizeTextures, 0); }
    { const char *key = "halfBuffer"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->halfBuffer, self->halfBuffer, 0); }
    { const char *key = "palVideoMode"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->palVideoMode, self->palVideoMode, 0); }
    { const char *key = "width"; if (key) igGetRegistryValue_Int(registry, section, key, &self->width, self->width, 0); }
    { const char *key = "height"; if (key) igGetRegistryValue_Int(registry, section, key, &self->height, self->height, 0); }
    { const char *key = "swapInterval"; if (key) igGetRegistryValue_Int(registry, section, key, &self->swapInterval, self->swapInterval, 0); }
    { const char *key = "colorBits"; if (key) igGetRegistryValue_Int(registry, section, key, &self->colorBits, self->colorBits, 0); }
    { const char *key = "alphaBits"; if (key) igGetRegistryValue_Int(registry, section, key, &self->alphaBits, self->alphaBits, 0); }
    { const char *key = "depthBits"; if (key) igGetRegistryValue_Int(registry, section, key, &self->depthBits, self->depthBits, 0); }
    { const char *key = "stencilBits"; if (key) igGetRegistryValue_Int(registry, section, key, &self->stencilBits, self->stencilBits, 0); }
    { const char *key = "reportVideoFormat"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->reportVideoFormat, self->reportVideoFormat, 0); }
    { const char *key = "showLogo"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->showLogo, self->showLogo, 0); }
    { const char *key = "showUI"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->showUI, self->showUI, 0); }
    { const char *key = "enableMayaControls"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->enableMayaControls, self->enableMayaControls, 0); }
    { const char *key = "benchmark"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->benchmark, self->benchmark, 0); }
    { const char *key = "benchmarkSkipFrames"; if (key) igGetRegistryValue_Int(registry, section, key, &self->benchmarkSkipFrames, self->benchmarkSkipFrames, 0); }
    { const char *key = "benchmarkFrames"; if (key) igGetRegistryValue_Int(registry, section, key, &self->benchmarkFrames, self->benchmarkFrames, 0); }
    { const char *key = "columnStatistics"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->columnStatistics, self->columnStatistics, 0); }
    { const char *key = "allocateVisualContextInScratchPad"; if (key) igGetRegistryValue_Bool(registry, section, key, &self->allocateVisualContextInScratchPad, self->allocateVisualContextInScratchPad, 0); }
}

