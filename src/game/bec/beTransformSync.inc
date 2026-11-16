igMetaObject *g_beTransformSync_metaObject;
igMetaField *g_beTransformSync_syncTransformListMetaField;

void *beTransformSync_GetMetaObject(void) {
    igMetaObject *g = g_beTransformSync_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTransformSync_EnsureRegistered();
    }
    return g_beTransformSync_metaObject;
}

int beTransformSync_GetVTable(void) {
    TransformSyncView transform;
    return *(int *)((char *)&transform + *(int *)((char *)g_objectSystem[0] + 916));
}

O *FUN_00341160(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void beTransformSync_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTransformSync_Register);
}

static igMetaObjectCallback g_beTransformSync_callbackList[] = { igTransformList_EnsureRegistered, 0 };

void *beTransformSync_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTransformSync_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beTransformSync_GetMetaObjectFunction,
        "beTransformSync",
        0x70, /* instance size */
        beTransformSync_GetVTable,
        beTransformSync_InitFields,
        0, /* extra callback item */
        g_beTransformSync_callbackList /* callback list */
    );
}

void beTransformSync_GetMetaObjectFunction(void)
{
    beTransformSync_GetMetaObject();
}

static FieldFactory g_beTransformSync_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beTransformSync_fieldTable[] = {
    "_syncTransformList",
};
static igMetaField **g_beTransformSync_fieldHandles[] = {
    &g_beTransformSync_syncTransformListMetaField,
};
static int g_beTransformSync_fieldOffsets[] = {
    108,
};

void beTransformSync_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beTransformSync_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beTransformSync_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beTransformSync_fieldTable, g_beTransformSync_fieldHandles, g_beTransformSync_fieldOffsets, temp_s2);
}

