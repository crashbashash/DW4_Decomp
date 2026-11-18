igMetaObject *g_igFieldChangeView_metaObject;
igMetaField *g_igFieldChangeView_synchronizerMetaField;
igMetaField *g_igFieldChangeView_fieldMetaField;

int igFieldChangeView_Create(int arg0) {
    igFieldChangeView_EnsureRegistered();
    return (int)(igMetaObject_CreateInstance(g_igFieldChangeView_metaObject, (igMemoryPoolView *)arg0));
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
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igFieldChangeView_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igFieldChangeView_vtable[0];
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

void igFieldChangeView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeView_Register);
}

static igMetaObjectCallback g_igFieldChangeView_callbackList[] = { igFieldSynchronizer_EnsureRegistered, igMetaField_EnsureRegistered, 0 };

CallbackArray *igFieldChangeView_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFieldChangeView_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        igFieldChangeView_GetMetaObjectFunction,
        "igFieldChangeView",
        0x14, /* instance size */
        igFieldChangeView_GetVTable,
        &igFieldChangeView_InitFields,
        0, /* extra callback item */
        g_igFieldChangeView_callbackList /* callback list */
    );
}

void igFieldChangeView_GetMetaObjectFunction(void) {
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
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igFieldChangeView_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igFieldSynchronizer_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igFieldChangeView_fieldTable, g_igFieldChangeView_fieldHandles, g_igFieldChangeView_fieldOffsets, temp_s2);
}

