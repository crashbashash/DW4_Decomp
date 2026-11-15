igMetaObject *g_igModel_metaObject;
igMetaField *g_igModel_viewsMetaField;

igMetaObject *FUN_0044d5d0(void) {
    if (g_igModel_metaObject == 0) {
        g_igModel_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igModel_metaObject;
}

igMetaObject *igModel_GetMetaObject(void)
{
    igMetaObject *g = g_igModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igModel_RunStaticInit();
    return g_igModel_metaObject;
}

int igModel_GetVTable(void) {
    struct Obj_44d670 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540e30[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00540e30[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void igModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igModel_Register);
}

static igMetaObjectCallback g_igModel_callbackList[] = { igNonRefCountedViewList_EnsureRegistered, 0 };

void igModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModel_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igModel_GetMetaObject,
        "igModel",
        0xC, /* instance size */
        igModel_GetVTable,
        &igModel_InitFields,
        0, /* extra callback item */
        g_igModel_callbackList /* callback list */
    );
}

void thunk_igModel_GetMetaObject(void) {
    igModel_GetMetaObject();
}

static FieldFactory g_igModel_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igModel_fieldTable[] = {
    "_views",
};
static igMetaField **g_igModel_fieldHandles[] = {
    &g_igModel_viewsMetaField,
};
static int g_igModel_fieldOffsets[] = {
    8,
};

void igModel_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igModel_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igModel_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0044b880();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_igModel_fieldTable, g_igModel_fieldHandles, g_igModel_fieldOffsets, temp_s2);
}

