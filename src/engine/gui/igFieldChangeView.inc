igMetaObject *g_igFieldChangeView_metaObject;
igMetaField *g_igFieldChangeView_synchronizerMetaField;
igMetaField *g_igFieldChangeView_fieldMetaField;

int FUN_00450de0(int arg0) {
    igFieldChangeView_EnsureRegistered();
    return igMetaObject_CreateInstance((int)g_igFieldChangeView_metaObject, arg0);
}

igMetaObject *igFieldChangeView_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeView_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeView_EnsureRegistered();
    return g_igFieldChangeView_metaObject;
}

int igFieldChangeView_GetVTable(void) {
    struct Obj_450e70 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541360[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00541360[0];
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

void igFieldChangeView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeView_Register);
}

static igMetaObjectCallback g_igFieldChangeView_callbackList[] = { igFieldSynchronizer_EnsureRegistered, igMetaField_EnsureRegistered, 0 };

void igFieldChangeView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFieldChangeView_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igFieldChangeView_GetMetaObject,
        "igFieldChangeView",
        0x14, /* instance size */
        igFieldChangeView_GetVTable,
        &igFieldChangeView_InitFields,
        0, /* extra callback item */
        g_igFieldChangeView_callbackList /* callback list */
    );
}

void thunk_igFieldChangeView_GetMetaObject(void) {
    igFieldChangeView_GetMetaObject();
}

static FieldFactory g_igFieldChangeView_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igFieldChangeView_fieldTable[] = {
    "_synchronizer",
    "_field",
};
static igMetaField **g_igFieldChangeView_fieldHandles[] = {
    &g_igFieldChangeView_synchronizerMetaField,
    &g_igFieldChangeView_fieldMetaField,
};
static int g_igFieldChangeView_fieldOffsets[] = {
    12,
    16,
};

void igFieldChangeView_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFieldChangeView_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igFieldChangeView_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00450a00();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igMetaField_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_igFieldChangeView_fieldTable, g_igFieldChangeView_fieldHandles, g_igFieldChangeView_fieldOffsets, temp_s2);
}

