igMetaObject *g_beMatCtrlSearch_metaObject;
igMetaField *g_beMatCtrlSearch_minXMetaField;
igMetaField *g_beMatCtrlSearch_maxXMetaField;
igMetaField *g_beMatCtrlSearch_matNOMetaField;
igMetaField *g_beMatCtrlSearch_parentMetaField;
igMetaField *g_beMatCtrlSearch_memberListMetaField;

igMetaObject *beMatCtrlSearch_GetOrCreateMetaObject(void) {
    if (g_beMatCtrlSearch_metaObject == 0) {
        g_beMatCtrlSearch_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMatCtrlSearch_metaObject;
}

void *beMatCtrlSearch_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlSearch_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlSearch_EnsureRegistered();
    }
    return g_beMatCtrlSearch_metaObject;
}

int beMatCtrlSearch_GetVTable(void) {
    struct Obj_35a090 obj;
    char *o;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &g_beMatCtrlSearch_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beMatCtrlSearch_vtable[0];
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

void beMatCtrlSearch_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearch_Register);
}

static igMetaObjectCallback g_beMatCtrlSearch_callbackList[] = { beMatCtrlSearchList_EnsureRegistered, 0 };

void *beMatCtrlSearch_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlSearch_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMatCtrlSearch_GetMetaObjectFunction,
        "beMatCtrlSearch",
        0x1c, /* instance size */
        beMatCtrlSearch_GetVTable,
        beMatCtrlSearch_InitFields,
        0, /* extra callback item */
        g_beMatCtrlSearch_callbackList /* callback list */
    );
}

void beMatCtrlSearch_GetMetaObjectFunction(void)
{
    beMatCtrlSearch_GetMetaObject();
}

static FieldFactory g_beMatCtrlSearch_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlSearch_fieldTable[] = {
    "_minX",
    "_maxX",
    "_matNO",
    "_parent",
    "_memberList",
};
static igMetaField **g_beMatCtrlSearch_fieldHandles[] = {
    &g_beMatCtrlSearch_minXMetaField,
    &g_beMatCtrlSearch_maxXMetaField,
    &g_beMatCtrlSearch_matNOMetaField,
    &g_beMatCtrlSearch_parentMetaField,
    &g_beMatCtrlSearch_memberListMetaField,
};
static int g_beMatCtrlSearch_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void beMatCtrlSearch_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMatCtrlSearch_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMatCtrlSearch_ctorTable, 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beMatCtrlSearch_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beMatCtrlSearchList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beMatCtrlSearch_fieldTable, g_beMatCtrlSearch_fieldHandles, g_beMatCtrlSearch_fieldOffsets, temp_s2);
}

