igMetaObject *g_igClearRenderer_metaObject;
igMetaField *g_igClearRenderer_buffersToClearMetaField;

igMetaObject *igClearRenderer_GetOrCreateMetaObject(void) {
    if (g_igClearRenderer_metaObject == 0) {
        g_igClearRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igClearRenderer_metaObject;
}

igMetaObject *igClearRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igClearRenderer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igClearRenderer_EnsureRegistered();
    return g_igClearRenderer_metaObject;
}

int igClearRenderer_GetVTable(void) {
    union U_44c2f0 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader((igObject *)u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&g_igRenderer_vtable[0];
    u.vt = (int)&g_igClearRenderer_vtable[0];
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igRenderer_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    return temp_s0;
}

void igClearRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igClearRenderer_Register);
}

CallbackArray *igClearRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igClearRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        igClearRenderer_GetMetaObjectFunction,
        "igClearRenderer",
        0x10, /* instance size */
        igClearRenderer_GetVTable,
        &igClearRenderer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igClearRenderer_GetMetaObjectFunction(void) {
    igClearRenderer_GetMetaObject();
}

static FieldFactory g_igClearRenderer_ctorTable[] = {
    igUnsignedIntMetaField_Create,
};
static const char *g_igClearRenderer_fieldTable[] = {
    "_buffersToClear",
};
static igMetaField **g_igClearRenderer_fieldHandles[] = {
    &g_igClearRenderer_buffersToClearMetaField,
};
static int g_igClearRenderer_fieldOffsets[] = {
    12,
};

void igClearRenderer_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igClearRenderer_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igClearRenderer_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igClearRenderer_fieldTable, g_igClearRenderer_fieldHandles, g_igClearRenderer_fieldOffsets, temp_s1);
}

