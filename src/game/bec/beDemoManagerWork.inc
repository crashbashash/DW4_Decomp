igMetaObject *g_beDemoManagerWork_metaObject;
igMetaField *g_beDemoManagerWork_advancecMetaField;
igMetaField *g_beDemoManagerWork_keepMesListMetaField;

void beDemoManagerWork_CreateInstance(int arg0) {
    beDemoManagerWork_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5897D8, arg0);
}

igMetaObject *beDemoManagerWork_GetOrCreateMetaObject(void) {
    if (g_beDemoManagerWork_metaObject == 0) {
        g_beDemoManagerWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDemoManagerWork_metaObject;
}

void *beDemoManagerWork_GetMetaObject(void) {
    igMetaObject *g = g_beDemoManagerWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDemoManagerWork_EnsureRegistered();
    }
    return g_beDemoManagerWork_metaObject;
}

int beDemoManagerWork_GetVTable(void) {
    union U_3638a0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beDemoManagerWork_vtable[0];
    ps = &u.b[12];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beDemoManagerWork_vtable[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void beDemoManagerWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDemoManagerWork_Register);
}

static igMetaObjectCallback g_beDemoManagerWork_callbackList[] = { beDemoKeepMesList_EnsureRegistered, 0 };

void *beDemoManagerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoManagerWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoManagerWork_GetMetaObjectFunction,
        "beDemoManagerWork",
        0x10, /* instance size */
        beDemoManagerWork_GetVTable,
        beDemoManagerWork_InitFields,
        0, /* extra callback item */
        g_beDemoManagerWork_callbackList /* callback list */
    );
}

void beDemoManagerWork_GetMetaObjectFunction(void)
{
    beDemoManagerWork_GetMetaObject();
}

static FieldFactory g_beDemoManagerWork_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beDemoManagerWork_fieldTable[] = {
    "_advancec",
    "_keepMesList",
};
static igMetaField **g_beDemoManagerWork_fieldHandles[] = {
    &g_beDemoManagerWork_advancecMetaField,
    &g_beDemoManagerWork_keepMesListMetaField,
};
static int g_beDemoManagerWork_fieldOffsets[] = {
    8,
    12,
};

void beDemoManagerWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDemoManagerWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beDemoManagerWork_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beDemoKeepMesList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beDemoManagerWork_fieldTable, g_beDemoManagerWork_fieldHandles, g_beDemoManagerWork_fieldOffsets, temp_s2);
}

