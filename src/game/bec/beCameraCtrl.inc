igMetaObject *g_beCameraCtrl_metaObject;
igMetaField *g_beCameraCtrl_viewerMangMetaField;
igMetaField *g_beCameraCtrl_viewerParaMetaField;
igMetaField *g_beCameraCtrl_cameraModeMetaField;
igMetaField *g_beCameraCtrl_avgPosMetaField;
igMetaField *g_beCameraCtrl_savePosMetaField;
igMetaField *g_beCameraCtrl_isPosChangeMetaField;
igMetaField *g_beCameraCtrl_cameraNowFrameMetaField;
igMetaField *g_beCameraCtrl_cameraNowMetaField;
igMetaField *g_beCameraCtrl_cameraOldMetaField;
igMetaField *g_beCameraCtrl_eyeMatrixMetaField;
igMetaField *g_beCameraCtrl_intMatrixMetaField;
igMetaField *g_beCameraCtrl_debugZoomMetaField;
igMetaField *g_beCameraCtrl_isFirstMetaField;

beCameraCtrl *beCameraCtrl_CreateInstance(int allocator) {
    beCameraCtrl_EnsureRegistered();
    return (beCameraCtrl *)igMetaObject_CreateInstance(g_beCameraCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beCameraCtrl_GetOrCreateMetaObject(void) {
    if (g_beCameraCtrl_metaObject == 0) {
        g_beCameraCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beCameraCtrl_metaObject;
}

void *beCameraCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beCameraCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCameraCtrl_EnsureRegistered();
    }
    return g_beCameraCtrl_metaObject;
}

int beCameraCtrl_GetVTable(void) {
    CameraCtrlView camera;
    return *(int *)((char *)&camera + *(int *)((char *)g_objectSystem + 916));
}

igSmartPointer<igObject> *igSmartPointer_beCameraMode_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beCameraCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCameraCtrl_Register);
}

static igMetaObjectCallback g_beCameraCtrl_callbackList[] = { igViewerSceneInfoManager_EnsureRegistered, igViewerParameters_EnsureRegistered, beCameraMode_EnsureRegistered, 0 };

CallbackArray *beCameraCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beCameraCtrl_GetMetaObjectFunction,
        "beCameraCtrl",
        0xdc, /* instance size */
        beCameraCtrl_GetVTable,
        beCameraCtrl_InitFields,
        0, /* extra callback item */
        g_beCameraCtrl_callbackList /* callback list */
    );
}

void beCameraCtrl_GetMetaObjectFunction(void)
{
    beCameraCtrl_GetMetaObject();
}

static FieldFactory g_beCameraCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igVec3fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igMatrix44fMetaField_CreateInstance,
    igMatrix44fMetaField_CreateInstance,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beCameraCtrl_fieldTable[] = {
    "_viewerMang",
    "_viewerPara",
    "_cameraMode",
    "_avgPos",
    "_savePos",
    "_isPosChange",
    "_cameraNowFrame",
    "_cameraNow",
    "_cameraOld",
    "_eyeMatrix",
    "_intMatrix",
    "_debugZoom",
    "_isFirst",
};
static igMetaField **g_beCameraCtrl_fieldHandles[] = {
    &g_beCameraCtrl_viewerMangMetaField,
    &g_beCameraCtrl_viewerParaMetaField,
    &g_beCameraCtrl_cameraModeMetaField,
    &g_beCameraCtrl_avgPosMetaField,
    &g_beCameraCtrl_savePosMetaField,
    &g_beCameraCtrl_isPosChangeMetaField,
    &g_beCameraCtrl_cameraNowFrameMetaField,
    &g_beCameraCtrl_cameraNowMetaField,
    &g_beCameraCtrl_cameraOldMetaField,
    &g_beCameraCtrl_eyeMatrixMetaField,
    &g_beCameraCtrl_intMatrixMetaField,
    &g_beCameraCtrl_debugZoomMetaField,
    &g_beCameraCtrl_isFirstMetaField,
};
static int g_beCameraCtrl_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    56,
    68,
    72,
    76,
    80,
    84,
    148,
    212,
    216,
};

void beCameraCtrl_InitFields(void) {
    int base;
    void *viewerMang;
    void *viewerPara;
    void *cameraMode;
    igMetaObject *meta;

    meta = g_beCameraCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCameraCtrl_ctorTable, 0xD);
    viewerMang = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)viewerMang)->_metaObject = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)viewerMang)->_refCounted = 0;
    viewerPara = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)viewerPara)->_metaObject = (int)igViewerParameters_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)viewerPara)->_refCounted = 0;
    cameraMode = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)cameraMode)->_metaObject = (int)beCameraMode_GetOrCreateMetaObject();
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 0xB), 1.0f);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 0xC), 1);
    igMetaObject_NameFields(meta, g_beCameraCtrl_fieldTable, g_beCameraCtrl_fieldHandles, g_beCameraCtrl_fieldOffsets, base);
}

