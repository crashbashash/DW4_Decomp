igMetaObject *g_igTextureMatrixAttr_metaObject;
igMetaField *g_igTextureMatrixAttr_mMetaField;
igMetaField *g_igTextureMatrixAttr_unitIDMetaField;
igMetaField *g_igTextureMatrixAttr_outputElementCountMetaField;
igMetaField *g_igTextureMatrixAttr_isProjectiveMetaField;

igTextureMatrixAttr *igTextureMatrixAttr_Create(igMemoryPoolView *pool) {
    igTextureMatrixAttr_EnsureRegistered();
    return (igTextureMatrixAttr *)igMetaObject_CreateInstance(g_igTextureMatrixAttr_metaObject, pool);
}

igMetaObject *igTextureMatrixAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureMatrixAttr_metaObject == 0) {
        g_igTextureMatrixAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureMatrixAttr_metaObject;
}

igMetaObject *igTextureMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureMatrixAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextureMatrixAttr_EnsureRegistered();
    return g_igTextureMatrixAttr_metaObject;
}

int igTextureMatrixAttr_GetVTable(void) {
    struct F_1318a0 f;

    igObject_InitHeader((igObject *)&f);
    f.vt = &g_igTextureMatrixAttr_vtable[0];
    igMatrix44f_SetIdentity((float *)&f.w[2]);
    return *(int *)((char *)&f + g_objectSystem->vtableProbeOffset);
}

void igTextureMatrixAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureMatrixAttr_Register);
}

CallbackArray *igTextureMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igTextureMatrixAttr_GetMetaObjectFunction,
        "igTextureMatrixAttr",
        0x54, /* instance size */
        igTextureMatrixAttr_GetVTable,
        &igTextureMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTextureMatrixAttr_GetMetaObjectFunction(void) {
    igTextureMatrixAttr_GetMetaObject();
}

static FieldFactory g_igTextureMatrixAttr_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igShortMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igTextureMatrixAttr_fieldTable[] = {
    "_m",
    "_unitID",
    "_outputElementCount",
    "_isProjective",
};
static igMetaField **g_igTextureMatrixAttr_fieldHandles[] = {
    &g_igTextureMatrixAttr_mMetaField,
    &g_igTextureMatrixAttr_unitIDMetaField,
    &g_igTextureMatrixAttr_outputElementCountMetaField,
    &g_igTextureMatrixAttr_isProjectiveMetaField,
};
static int g_igTextureMatrixAttr_fieldOffsets[] = {
    12,
    76,
    80,
    82,
};

void igTextureMatrixAttr_InitFields(void) {
    struct M o1;
    int base;
    struct V o2;
    struct V o3;
    struct Fld *fld;
    void *field;
    struct V o4;
    struct V o5;
    igMetaObject *meta;

    meta = g_igTextureMatrixAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureMatrixAttr_ctorTable, 4);
    field = igMetaObject_GetFieldAt(meta, base);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    igMatrix44f_FromRows((float *)&o1, (igVec4f *)&o2, (igVec4f *)&o3, (igVec4f *)&o4, (igVec4f *)&o5);
    FUN_0018c640((igMetaField *)field, (const float *)&o1);
    fld = (Fld *)igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)fld)->_invarianceFunction = (int)igTextureMatrixAttr_SynchronizeCachedUnitID;
    ((Gap::Core::igShortMetaField *)(igMetaObject_GetFieldAt(meta, base + 2)))->setDefault(-1);
    igMetaObject_NameFields(meta, g_igTextureMatrixAttr_fieldTable, g_igTextureMatrixAttr_fieldHandles, g_igTextureMatrixAttr_fieldOffsets, base);
}

igSmartPointer<igObject> *igSmartPointer_igTextureList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

igInfo *igInfo_Destroy(igInfo *self, short deleteFlag) {
    char *p;
    int *h;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igInfo_vtable[0];
        if (self != 0) {
            self->_vtable = (int)&g_igNamedObject_vtable[0];
            if (&self->_name) {
                p = (char *)self->_name;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
                    }
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igNamedObject *igNamedObject_Destroy(igNamedObject *self, short deleteFlag) {
    char *p;
    int *h;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igNamedObject_vtable[0];
        if (&self->_name) {
            p = (char *)self->_name;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

int FUN_00131c50(void) {
    return (int)g_igInfo_metaObject;
}

