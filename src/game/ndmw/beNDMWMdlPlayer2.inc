igMetaObject *g_beNDMWMdlPlayer2_metaObject;
igMetaField *g_beNDMWMdlPlayer2_padManagerMetaField;

beNDMWMdlPlayer2 *beNDMWMdlPlayer2_CreateInstance(int allocator) {
    beNDMWMdlPlayer2_EnsureRegistered();
    return (beNDMWMdlPlayer2 *)igMetaObject_CreateInstance(g_beNDMWMdlPlayer2_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWMdlPlayer2_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlPlayer2_metaObject == 0) {
        g_beNDMWMdlPlayer2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWMdlPlayer2_metaObject;
}

void *beNDMWMdlPlayer2_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPlayer2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlPlayer2_EnsureRegistered();
    }
    return g_beNDMWMdlPlayer2_metaObject;
}

int beNDMWMdlPlayer2_GetVTable(void) {
    beNDMWMdlPlayer2 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlPlayer2_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWMdlPlayer2_vtable[0];
    beModelCtrl_Destroy((beModelCtrl *)&obj, 0);
    return vtable;
}

beModelCtrl *beModelCtrl_Destroy(beModelCtrl *self, short flags) {
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
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beNDMWMdlPlayer2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer2_Register);
}

static igMetaObjectCallback g_beNDMWMdlPlayer2_callbackList[] = { bePadManager_EnsureRegistered, 0 };

CallbackArray *beNDMWMdlPlayer2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPlayer2_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPlayer2_GetMetaObject,
        "beNDMWMdlPlayer2",
        0x30, /* instance size */
        beNDMWMdlPlayer2_GetVTable,
        beNDMWMdlPlayer2_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayer2_callbackList /* callback list */
    );
}

void beNDMWMdlPlayer2_GetMetaObject(void)
{
    beNDMWMdlPlayer2_ResolveMetaObject();
}

igMetaObject *beModelCtrl_GetPublishedMetaObject(void) {
    return g_beModelCtrl_metaObject;
}

static FieldFactory g_beNDMWMdlPlayer2_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWMdlPlayer2_fieldTable[] = {
    "_padManager",
};
static igMetaField **g_beNDMWMdlPlayer2_fieldHandles[] = {
    &g_beNDMWMdlPlayer2_padManagerMetaField,
};
static int g_beNDMWMdlPlayer2_fieldOffsets[] = {
    44,
};

void beNDMWMdlPlayer2_InitFields(void) {
    int base;
    void *padManager;
    igMetaObject *meta;

    meta = g_beNDMWMdlPlayer2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMdlPlayer2_ctorTable, 1);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beNDMWMdlPlayer2_fieldTable, g_beNDMWMdlPlayer2_fieldHandles, g_beNDMWMdlPlayer2_fieldOffsets, base);
}

