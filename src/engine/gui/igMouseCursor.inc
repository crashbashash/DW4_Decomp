igMetaObject *g_igMouseCursor_metaObject;
igMetaField *g_igMouseCursor_geometryElementMetaField;
igMetaField *g_igMouseCursor_offsetMetaField;

igMetaObject *igMouseCursor_GetOrCreateMetaObject(void) {
    if (g_igMouseCursor_metaObject == 0) {
        g_igMouseCursor_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMouseCursor_metaObject;
}

igMetaObject *igMouseCursor_GetMetaObject(void)
{
    igMetaObject *g = g_igMouseCursor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMouseCursor_RunStaticInit();
    return g_igMouseCursor_metaObject;
}

int igMouseCursor_GetVTable(void) {
    struct Obj_44e4d0 obj;
    char *o;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMouseCursor_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igMouseCursor_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
    }
    return t;
}

void igMouseCursor_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMouseCursor_Register);
}

static igMetaObjectCallback g_igMouseCursor_callbackList[] = { igGeometryElement_EnsureRegistered, 0 };

CallbackArray *igMouseCursor_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMouseCursor_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMouseCursor_GetMetaObject,
        "igMouseCursor",
        0x14, /* instance size */
        igMouseCursor_GetVTable,
        &igMouseCursor_InitFields,
        0, /* extra callback item */
        g_igMouseCursor_callbackList /* callback list */
    );
}

void thunk_igMouseCursor_GetMetaObject(void) {
    igMouseCursor_GetMetaObject();
}

static FieldFactory g_igMouseCursor_ctorTable[] = {
    igObjectRefMetaField_Create,
    (FieldFactory)igVec2fMetaField_CreateInstance,
};
static const char *g_igMouseCursor_fieldTable[] = {
    "_geometryElement",
    "_offset",
};
static igMetaField **g_igMouseCursor_fieldHandles[] = {
    &g_igMouseCursor_geometryElementMetaField,
    &g_igMouseCursor_offsetMetaField,
};
static int g_igMouseCursor_fieldOffsets[] = {
    8,
    12,
};

void igMouseCursor_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    void *temp_a0;
    int buf[2];

    temp_s0 = (void *)g_igMouseCursor_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igMouseCursor_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)igGeometryElement_GetOrCreateMetaObject();
    temp_a0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    buf[0] = 0;
    buf[1] = 0;
    igVec2fMetaField_SetDefault((igMetaField *)temp_a0, (const float *)buf);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igMouseCursor_fieldTable, g_igMouseCursor_fieldHandles, g_igMouseCursor_fieldOffsets, temp_s2);
}

