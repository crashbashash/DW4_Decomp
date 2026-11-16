igMetaObject *g_igVisualContextAttrDefaultManager_metaObject;
igMetaField *g_igVisualContextAttrDefaultManager_visualContextMetaField;

void FUN_00130020(int arg0) {
    FUN_001301c0();
    igMetaObject_CreateInstance(*(int *)0x55EBC0, arg0);
}

igMetaObject *igVisualContextAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextAttrDefaultManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001301c0();
    return g_igVisualContextAttrDefaultManager_metaObject;
}

int igVisualContextAttrDefaultManager_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[8];
    u.vt = (int)&g_igVisualContextAttrDefaultManager_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igVisualContextAttrDefaultManager_vtable[0];
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

void **FUN_00130140(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_001301c0(void)
{
    igMetaObject_RunStaticInit(igVisualContextAttrDefaultManager_Register);
}

static igMetaObjectCallback g_igVisualContextAttrDefaultManager_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

void igVisualContextAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVisualContextAttrDefaultManager_metaObject,
        igAttrDefaultManager_Register,
        igAttrDefaultManager_GetPublishedMetaObject,
        thunk_igVisualContextAttrDefaultManager_GetMetaObject,
        "igVisualContextAttrDefaultManager",
        0xC, /* instance size */
        igVisualContextAttrDefaultManager_GetVTable,
        &igVisualContextAttrDefaultManager_InitFields,
        0, /* extra callback item */
        g_igVisualContextAttrDefaultManager_callbackList /* callback list */
    );
}

void thunk_igVisualContextAttrDefaultManager_GetMetaObject(void) {
    igVisualContextAttrDefaultManager_GetMetaObject();
}

igMetaObject *FUN_00130260(void) {
    return g_igAttrDefaultManager_metaObject;
}

static FieldFactory g_igVisualContextAttrDefaultManager_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igVisualContextAttrDefaultManager_fieldTable[] = {
    "_visualContext",
};
static igMetaField **g_igVisualContextAttrDefaultManager_fieldHandles[] = {
    &g_igVisualContextAttrDefaultManager_visualContextMetaField,
};
static int g_igVisualContextAttrDefaultManager_fieldOffsets[] = {
    8,
};

void igVisualContextAttrDefaultManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igVisualContextAttrDefaultManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igVisualContextAttrDefaultManager_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igVisualContext_GetOrCreateMetaObject();
    ((igMetaField *)temp_s1)->_persistent = 0;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 1;
    igMetaObject_NameFields(temp_s0, g_igVisualContextAttrDefaultManager_fieldTable, g_igVisualContextAttrDefaultManager_fieldHandles, g_igVisualContextAttrDefaultManager_fieldOffsets, temp_s2);
}

