igMetaObject *g_igViewMode_metaObject;
igMetaField *g_igViewMode_inverseMatrixMetaField;

igMetaObject *igViewMode_GetOrCreateMetaObject(void) {
    if (g_igViewMode_metaObject == 0) {
        g_igViewMode_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewMode_metaObject;
}

void *igViewMode_GetMetaObject(void) {
    igMetaObject *g = g_igViewMode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igViewMode_EnsureRegistered();
    }
    return g_igViewMode_metaObject;
}

int igViewMode_GetVTable(void) {
    struct W o;
    igObject_InitHeader((igObject *)&o);
    o.vt = g_igViewMode_vtable;
    igMatrix44f_SetIdentity((float *)&o.f[2]);
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igViewMode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewMode_Register);
}

CallbackArray *igViewMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewMode_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        igViewMode_GetMetaObjectFunction,
        "igViewMode",
        0x4C, /* instance size */
        igViewMode_GetVTable,
        &igViewMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igViewMode_GetMetaObjectFunction(void) {
    igViewMode_GetMetaObject();
}

static FieldFactory g_igViewMode_ctorTable[] = {
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
};
static const char *g_igViewMode_fieldTable[] = {
    "_inverseMatrix",
};
static igMetaField **g_igViewMode_fieldHandles[] = {
    &g_igViewMode_inverseMatrixMetaField,
};
static int g_igViewMode_fieldOffsets[] = {
    12,
};

void igViewMode_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = g_igViewMode_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewMode_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewMode_fieldTable, g_igViewMode_fieldHandles, g_igViewMode_fieldOffsets, temp_s1);
}

