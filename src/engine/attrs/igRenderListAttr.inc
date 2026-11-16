igMetaObject *g_igRenderListAttr_metaObject;
igMetaField *g_igRenderListAttr_handleMetaField;
igMetaField *g_igRenderListAttr_vcMetaField;

igMetaObject *FUN_00133e50(void) {
    if (g_igRenderListAttr_metaObject == 0) {
        g_igRenderListAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRenderListAttr_metaObject;
}

igMetaObject *igRenderListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderListAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00133f80();
    return g_igRenderListAttr_metaObject;
}

int igRenderListAttr_GetVTable(void) {
    union U_133ef0 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader((igObject *)u.b);
    p = (S_ref *)&u.b[16];
    u.vt = (int)&g_igRenderListAttr_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igRenderListAttr_vtable[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_00133f80(void)
{
    igMetaObject_RunStaticInit(igRenderListAttr_Register);
}

static igMetaObjectCallback g_igRenderListAttr_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igRenderListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderListAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igRenderListAttr_GetMetaObject,
        "igRenderListAttr",
        0x14, /* instance size */
        igRenderListAttr_GetVTable,
        &igRenderListAttr_InitFields,
        0, /* extra callback item */
        g_igRenderListAttr_callbackList /* callback list */
    );
}

void thunk_igRenderListAttr_GetMetaObject(void) {
    igRenderListAttr_GetMetaObject();
}

static FieldFactory g_igRenderListAttr_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igRenderListAttr_fieldTable[] = {
    "_handle",
    "_vc",
};
static igMetaField **g_igRenderListAttr_fieldHandles[] = {
    &g_igRenderListAttr_handleMetaField,
    &g_igRenderListAttr_vcMetaField,
};
static int g_igRenderListAttr_fieldOffsets[] = {
    12,
    16,
};

void igRenderListAttr_InitFields(void) {
    int temp_s2;
    struct F_134020 *temp_v0;
    struct F_134020 *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igRenderListAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igRenderListAttr_ctorTable, 2);
    temp_v0 = (struct F_134020 *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igIntMetaField_SetDefault(temp_v0, -1);
    temp_v0->b38 = 0;
    temp_s1 = (struct F_134020 *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    temp_s1->f56 = (int)igVisualContext_GetOrCreateMetaObject();
    temp_s1->b38 = 0;
    temp_s1->b40 = 1;
    temp_s1->b39 = 1;
    temp_s1->b44 = 3;
    igMetaObject_NameFields(temp_s0, g_igRenderListAttr_fieldTable, g_igRenderListAttr_fieldHandles, g_igRenderListAttr_fieldOffsets, temp_s2);
}

