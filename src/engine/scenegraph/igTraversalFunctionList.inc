int igTraversalFunctionList_CreateInstance(int arg0) {
    igTraversalFunctionList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igTraversalFunctionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igTraversalFunctionList_metaObject;

igMetaObject *igTraversalFunctionList_GetOrCreateMetaObject(void) {
    if (g_igTraversalFunctionList_metaObject == 0) {
        g_igTraversalFunctionList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTraversalFunctionList_metaObject;
}

igMetaObject *igTraversalFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversalFunctionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTraversalFunctionList_EnsureRegistered();
    return g_igTraversalFunctionList_metaObject;
}

int igTraversalFunctionList_GetVTable(void) {
    struct Obj_19a7c0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTraversalFunctionList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTraversalFunctionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTraversalFunctionList_Register);
}

CallbackArray *igTraversalFunctionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTraversalFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igTraversalFunctionList_GetMetaObjectFunction,
        "igTraversalFunctionList",
        0x14, /* instance size */
        igTraversalFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTraversalFunctionList_GetMetaObjectFunction(void) {
    igTraversalFunctionList_GetMetaObject();
}

igSmartPointer<igObject> *igSmartPointer_igProjectionMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igSetRenderDestinationAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igCopyRenderDestinationAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igTextureBindAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igTexGenMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igColorAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igViewportAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

int *igSmartPointer_igColorAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTexGenMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igLightAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igViewportAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igCopyRenderDestinationAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTextureBindAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTextureAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igSetRenderDestinationAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igRenderDestinationAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igTextureMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igProjectionMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igModelViewMatrixAttr_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igNodeList_Construct(int *p)
{
    *p = 0;
    return p;
}

int FUN_0019ace0(int a0)
{
    return a0;
}

void *FUN_0019acf0(igGroup *arg0) {
    igObject_InitHeader((igObject *)arg0);
    arg0->_vtable = (int)(&g_igNamedObject_vtable[0]);
    arg0->_name = 0;
    arg0->_vtable = (int)(&g_igNode_vtable[0]);
    arg0->_bound = 0;
    arg0->_parentList = 0;
    arg0->_vtable = (int)(&g_igGroup_vtable[0]);
    arg0->_childList = 0;
    return arg0;
}

