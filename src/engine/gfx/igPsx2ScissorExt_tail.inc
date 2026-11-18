igMetaObject *igPsx2ScissorExt_GetOrCreateMetaObject(void) {
    if (g_igPsx2ScissorExt_metaObject == 0) {
        g_igPsx2ScissorExt_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPsx2ScissorExt_metaObject;
}

igMetaObject *igPsx2ScissorExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ScissorExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2ScissorExt_EnsureRegistered();
    return g_igPsx2ScissorExt_metaObject;
}

int igPsx2ScissorExt_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    char *q2;
    igObject *a;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&DAT_00530a10[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    q2 = &u.b[16];
    *(int *)q2 = 0;
    u.vt = (int)&g_igPsx2ScissorExt_vtable[0];
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&DAT_00530a10[0];
    if (q2 != 0) {
        a = *(igObject **)q2;
        if (a != 0) {
            a->_refCount = (int)((int) ((int)a->_refCount - 1));
            if (((unsigned long long) ((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q1 != 0) {
        a = *(igObject **)q1;
        if (a != 0) {
            a->_refCount = (int)((int) ((int)a->_refCount - 1));
            if (((unsigned long long) ((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return temp_s0;
}

void igPsx2ScissorExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2ScissorExt_Register);
}

static igMetaObjectCallback g_igPsx2ScissorExt_callbackList[] = { igPsx2VisualContext_EnsureRegistered, 0 };

CallbackArray *igPsx2ScissorExt_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2ScissorExt_metaObject,
        igScissorExt_Register,
        igScissorExt_GetPublishedMetaObject,
        igPsx2ScissorExt_GetMetaObjectFunction,
        "igPsx2ScissorExt",
        0x2C, /* instance size */
        igPsx2ScissorExt_GetVTable,
        &igPsx2ScissorExt_InitFields,
        0, /* extra callback item */
        g_igPsx2ScissorExt_callbackList /* callback list */
    );
}

igMetaObject *igScissorExt_GetPublishedMetaObject(void) {
    return g_igScissorExt_metaObject;
}

static FieldFactory g_igPsx2ScissorExt_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igPsx2ScissorExt_fieldTable[] = {
    "_context",
    "_scissorEnable",
    "_scissorOrgX",
    "_scissorOrgY",
    "_scissorWidth",
    "_scissorHeight",
};
static igMetaField **g_igPsx2ScissorExt_fieldHandles[] = {
    &g_igPsx2ScissorExt_contextMetaField,
    &g_igPsx2ScissorExt_scissorEnableMetaField,
    &g_igPsx2ScissorExt_scissorOrgXMetaField,
    &g_igPsx2ScissorExt_scissorOrgYMetaField,
    &g_igPsx2ScissorExt_scissorWidthMetaField,
    &g_igPsx2ScissorExt_scissorHeightMetaField,
};
static int g_igPsx2ScissorExt_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
    40,
};

void igPsx2ScissorExt_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igPsx2ScissorExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2ScissorExt_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igPsx2VisualContext_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 4), 0x280);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 5), 0x1C0);
    igMetaObject_NameFields(meta, g_igPsx2ScissorExt_fieldTable, g_igPsx2ScissorExt_fieldHandles, g_igPsx2ScissorExt_fieldOffsets, fieldStart);
}

