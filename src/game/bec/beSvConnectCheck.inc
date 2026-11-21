igMetaObject *g_beSvConnectCheck_metaObject;

beSvConnectCheck *beSvConnectCheck_Create(int allocator) {
    beSvConnectCheck_EnsureRegistered();
    return (beSvConnectCheck *)igMetaObject_CreateInstance(g_beSvConnectCheck_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beSvConnectCheck_GetOrCreateMetaObject(void) {
    if (g_beSvConnectCheck_metaObject == 0) {
        g_beSvConnectCheck_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSvConnectCheck_metaObject;
}

void *beSvConnectCheck_GetMetaObject(void) {
    igMetaObject *g = g_beSvConnectCheck_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvConnectCheck_EnsureRegistered();
    }
    return g_beSvConnectCheck_metaObject;
}

int beSvConnectCheck_GetVTable(void) {
    beSvConnectCheck obj;
    int vtable;
    igObject **iconWorkSlot;
    igObject **mountWorkSlot;
    igObject **imageWorkSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    imageWorkSlot = (igObject **)&obj._imageWork;
    *imageWorkSlot = 0;
    mountWorkSlot = (igObject **)&obj._mountWork;
    *mountWorkSlot = 0;
    iconWorkSlot = (igObject **)&obj._iconWork;
    *iconWorkSlot = 0;
    obj._vtable = (int)&g_beSvConnectCheck_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    igObjectRef_Release(iconWorkSlot);
    igObjectRef_Release(mountWorkSlot);
    igObjectRef_Release(imageWorkSlot);
    return vtable;
}

void *beSaveApi_Destroy(beSaveApi *self, short delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_beSaveApi_vtable[0];
        igObjectRef_Release((igObject **)&self->_iconWork);
        igObjectRef_Release((igObject **)&self->_mountWork);
        igObjectRef_Release((igObject **)&self->_imageWork);
        if (delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beSaveMemoryObj_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beSvConnectCheck_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvConnectCheck_Register);
}

CallbackArray *beSvConnectCheck_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvConnectCheck_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvConnectCheck_GetMetaObjectFunction,
        "beSvConnectCheck",
        0x90, /* instance size */
        beSvConnectCheck_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvConnectCheck_GetMetaObjectFunction(void)
{
    beSvConnectCheck_GetMetaObject();
}

igMetaObject *beSaveApi_GetPublishedMetaObject(void) {
    return g_beSaveApi_metaObject;
}

