igMetaObject *g_beSvConnectCheck_metaObject;

void beSvConnectCheck_Create(int allocator) {
    beSvConnectCheck_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5881D8, allocator);
}

igMetaObject *beSvConnectCheck_GetOrCreateMetaObject(void) {
    if (g_beSvConnectCheck_metaObject == 0) {
        g_beSvConnectCheck_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
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
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beSvConnectCheck_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvConnectCheck_Register);
}

void *beSvConnectCheck_Register(void) {
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

