igMetaObject *g_beNDMWMdlPlayer_metaObject;
igMetaField *g_beNDMWMdlPlayer_viewerSIManagerMetaField;
igMetaField *g_beNDMWMdlPlayer_padManagerMetaField;
igMetaField *g_beNDMWMdlPlayer_gameRamMetaField;

void beNDMWMdlPlayer_CreateInstance(int allocator) {
    beNDMWMdlPlayer_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlPlayer_metaObject, allocator);
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
    struct W_3bf970 o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = g_beNDMWMdlPlayer_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWMdlPlayer_vtable;
    FUN_003bf9d0((O_3bf9d0 *)&o, (short)0);
    return r;
}

O_3bf9d0 *FUN_003bf9d0(O_3bf9d0 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R_3bf9d0 *temp_a0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &g_beNDMWMdlPEBase_vtable[0];
        if (arg0 != 0) {
            arg0->vt = &g_beModelCtrl_vtable[0];
            if (arg0 != 0) {
                arg0->vt = &g_beBaseInfoManager_vtable[0];
                if (&arg0->ref != 0) {
                    temp_a0 = arg0->ref;
                    if (temp_a0 != 0) {
                        temp_a0->refs = temp_a0->refs - 1;
                        if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(temp_a0);
                        }
                    }
                }
                if (arg0 != 0) {
                    arg0->vt = &DAT_0052cf80[0];
                    if (arg0 != 0) {
                        arg0->vt = &g_igNamedObject_vtable[0];
                        if (&arg0->str != 0) {
                            temp_v1 = arg0->str;
                            if (temp_v1 != 0) {
                                temp_a1 = temp_v1 - 2;
                                temp_v0 = temp_v1[-1] - 1;
                                temp_v1[-1] = temp_v0;
                                if (temp_v0 == 0) {
                                    StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                                }
                            }
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
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

