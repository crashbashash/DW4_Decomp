igMetaObject *g_igLightStateSet_metaObject;
igMetaField *g_igLightStateSet_lightEnablesMetaField;

igMetaObject *igLightStateSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateSet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightStateSet_EnsureRegistered();
    return g_igLightStateSet_metaObject;
}

int igLightStateSet_GetVTable(void) {
    struct Obj_19d960 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[6] = 0;
    obj.vt = &g_igLightStateSet_vtable[0];
    obj.w[7] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igLightStateSet_vtable[0];
    FUN_0019d9e0((void * *)&obj.w[7], -1);
    igGroup_Destroy((struct T_195a90 *)&obj, 0);
    return r;
}

void **FUN_0019d9e0(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void igLightStateSet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightStateSet_Register);
}

static igMetaObjectCallback g_igLightStateSet_callbackList[] = { igLightStateAttrList_EnsureRegistered, 0 };

void igLightStateSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightStateSet_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igLightStateSet_GetMetaObject,
        "igLightStateSet",
        0x24, /* instance size */
        igLightStateSet_GetVTable,
        &igLightStateSet_InitFields,
        0, /* extra callback item */
        g_igLightStateSet_callbackList /* callback list */
    );
}

void thunk_igLightStateSet_GetMetaObject(void) {
    igLightStateSet_GetMetaObject();
}

static FieldFactory g_igLightStateSet_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igLightStateSet_fieldTable[] = {
    "_lightEnables",
};
static igMetaField **g_igLightStateSet_fieldHandles[] = {
    &g_igLightStateSet_lightEnablesMetaField,
};
static int g_igLightStateSet_fieldOffsets[] = {
    32,
};

void igLightStateSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightStateSet_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igLightStateSet_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00136040();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igLightStateSet_fieldTable, g_igLightStateSet_fieldHandles, g_igLightStateSet_fieldOffsets, temp_s2);
}

