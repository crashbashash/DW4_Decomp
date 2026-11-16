igMetaObject *g_beNDMWMdlPlayer_metaObject;
igMetaField *g_beNDMWMdlPlayer_viewerSIManagerMetaField;
igMetaField *g_beNDMWMdlPlayer_padManagerMetaField;
igMetaField *g_beNDMWMdlPlayer_gameRamMetaField;

beNDMWMdlPlayer *beNDMWMdlPlayer_CreateInstance(int allocator) {
    beNDMWMdlPlayer_EnsureRegistered();
    return (beNDMWMdlPlayer *)igMetaObject_CreateInstance(g_beNDMWMdlPlayer_metaObject, allocator);
}

igMetaObject *beNDMWMdlPlayer_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlPlayer_metaObject == 0) {
        g_beNDMWMdlPlayer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlPlayer_metaObject;
}

void *beNDMWMdlPlayer_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPlayer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlPlayer_EnsureRegistered();
    }
    return g_beNDMWMdlPlayer_metaObject;
}

int beNDMWMdlPlayer_GetVTable(void) {
    beNDMWMdlPlayer obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlPlayer_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWMdlPlayer_vtable[0];
    beNDMWMdlPEBase_Destroy((beNDMWMdlPEBase *)&obj, 0);
    return vtable;
}

beNDMWMdlPEBase *beNDMWMdlPEBase_Destroy(beNDMWMdlPEBase *self, short flags) {
    if (self != 0) {
        *(int **)&self->_vtable = &g_beNDMWMdlPEBase_vtable[0];
        if (self != 0) {
            *(int **)&self->_vtable = &g_beModelCtrl_vtable[0];
            if (self != 0) {
                *(int **)&self->_vtable = &g_beBaseInfoManager_vtable[0];
                if (&self->_infoList != 0) {
                    igRelease((igObject *)self->_infoList);
                }
                if (self != 0) {
                    *(int **)&self->_vtable = &g_igInfoManager_vtable[0];
                    if (self != 0) {
                        *(int **)&self->_vtable = &g_igNamedObject_vtable[0];
                        if (&self->_name != 0) {
                            releaseString((const char *)self->_name);
                        }
                    }
                }
            }
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beNDMWMdlPlayer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer_Register);
}

static igMetaObjectCallback g_beNDMWMdlPlayer_callbackList[] = { igViewerSceneInfoManager_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWGameRam_EnsureRegistered, 0 };

void *beNDMWMdlPlayer_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPlayer_metaObject,
        beNDMWMdlPEBase_Register,
        beNDMWMdlPEBase_GetPublishedMetaObject,
        beNDMWMdlPlayer_GetMetaObject,
        "beNDMWMdlPlayer",
        0x38, /* instance size */
        beNDMWMdlPlayer_GetVTable,
        beNDMWMdlPlayer_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayer_callbackList /* callback list */
    );
}

void beNDMWMdlPlayer_GetMetaObject(void)
{
    beNDMWMdlPlayer_ResolveMetaObject();
}

igMetaObject *beNDMWMdlPEBase_GetPublishedMetaObject(void) {
    return g_beNDMWMdlPEBase_metaObject;
}

static FieldFactory g_beNDMWMdlPlayer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWMdlPlayer_fieldTable[] = {
    "_viewerSIManager",
    "_padManager",
    "_gameRam",
};
static igMetaField **g_beNDMWMdlPlayer_fieldHandles[] = {
    &g_beNDMWMdlPlayer_viewerSIManagerMetaField,
    &g_beNDMWMdlPlayer_padManagerMetaField,
    &g_beNDMWMdlPlayer_gameRamMetaField,
};
static int g_beNDMWMdlPlayer_fieldOffsets[] = {
    44,
    48,
    52,
};

void beNDMWMdlPlayer_InitFields(void) {
    int base;
    void *gameRam;
    void *padManager;
    void *viewerSIManager;
    igMetaObject *meta;

    meta = g_beNDMWMdlPlayer_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMdlPlayer_ctorTable, 3);
    viewerSIManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)viewerSIManager)->_metaObject = igViewerSceneInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)viewerSIManager)->_refCounted = 0;
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)padManager)->_metaObject = bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    gameRam = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)gameRam)->_metaObject = (int)beNDMWGameRam_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)gameRam)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beNDMWMdlPlayer_fieldTable, g_beNDMWMdlPlayer_fieldHandles, g_beNDMWMdlPlayer_fieldOffsets, base);
}

