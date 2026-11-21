igMetaObject *g_igCustomStateCollection_metaObject;
igMetaField *g_igCustomStateCollection_nameMetaField;
igMetaField *g_igCustomStateCollection_flagsMetaField;

igCustomStateCollectionView *igCustomStateCollection_Create(int arg0) {
    igCustomStateCollection_EnsureRegistered();
    return (igCustomStateCollectionView *)igMetaObject_CreateInstance(g_igCustomStateCollection_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igCustomStateCollection_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateCollection_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCustomStateCollection_EnsureRegistered();
    return g_igCustomStateCollection_metaObject;
}

int igCustomStateCollection_GetVTable(void) {
    struct W o;
    int r;
    int *p; int *a1; int t;
    igObject_InitHeader((igObject *)&o);
    o.vt = g_igCustomStateCollection_vtable;
    *(int *)((char *)&o + 20) = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = g_igCustomStateCollection_vtable;
    if (&*(int *)((char *)&o + 20) != 0) { p = *(int **)((char *)&o + 20); if (p != 0) { a1 = p - 2; t = p[-1] - 1; p[-1] = t; if (t == 0) StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1); } }
    return r;
}

void igCustomStateCollection_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCustomStateCollection_Register);
}

static igMetaObjectCallback g_igCustomStateCollection_callbackList[] = { igCustomState_EnsureRegistered, 0 };

CallbackArray *igCustomStateCollection_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCustomStateCollection_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igCustomStateCollection_GetMetaObjectFunction,
        "igCustomStateCollection",
        0x1C, /* instance size */
        igCustomStateCollection_GetVTable,
        &igCustomStateCollection_InitFields,
        0, /* extra callback item */
        g_igCustomStateCollection_callbackList /* callback list */
    );
}

void igCustomStateCollection_GetMetaObjectFunction(void) {
    igCustomStateCollection_GetMetaObject();
}

static FieldFactory g_igCustomStateCollection_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igCustomStateCollection_fieldTable[] = {
    "_name",
    "_flags",
};
static igMetaField **g_igCustomStateCollection_fieldHandles[] = {
    &g_igCustomStateCollection_nameMetaField,
    &g_igCustomStateCollection_flagsMetaField,
};
static int g_igCustomStateCollection_fieldOffsets[] = {
    20,
    24,
};

void igCustomStateCollection_InitFields(void) {
    int fieldStart;
    igMetaObject *meta;

    meta = g_igCustomStateCollection_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igCustomStateCollection_ctorTable, 2);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart)))->setDefault("");
    igMetaObject_NameFields(meta, g_igCustomStateCollection_fieldTable, g_igCustomStateCollection_fieldHandles, g_igCustomStateCollection_fieldOffsets, fieldStart);
}

