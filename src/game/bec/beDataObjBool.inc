igMetaObject *g_beDataObjBool_metaObject;
igMetaField *g_beDataObjBool_dataMetaField;

void beDataObjBool_Create(int arg0) {
    beDataObjBool_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589898, arg0);
}

void *beDataObjBool_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjBool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjBool_EnsureRegistered();
    }
    return g_beDataObjBool_metaObject;
}

int beDataObjBool_GetVTable(void) {
    struct F_365090 o;
    int r;
    int *s;
    int *h;
    int c;

    igObject_InitHeader(&o);
    o.vt = g_igNamedObject_vtable;
    o.str = 0;
    o.vt = g_beDataObjBool_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_igNamedObject_vtable;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
    return r;
}

void beDataObjBool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjBool_Register);
}

void *beDataObjBool_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjBool_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjBool_GetMetaObjectFunction,
        "beDataObjBool",
        0x10, /* instance size */
        beDataObjBool_GetVTable,
        beDataObjBool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDataObjBool_GetMetaObjectFunction(void)
{
    beDataObjBool_GetMetaObject();
}

static FieldFactory g_beDataObjBool_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_beDataObjBool_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjBool_fieldHandles[] = {
    &g_beDataObjBool_dataMetaField,
};
static int g_beDataObjBool_fieldOffsets[] = {
    12,
};

void beDataObjBool_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjBool_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beDataObjBool_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beDataObjBool_fieldTable, g_beDataObjBool_fieldHandles, g_beDataObjBool_fieldOffsets, temp_s1);
}

