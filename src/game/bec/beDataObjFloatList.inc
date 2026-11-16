igMetaObject *g_beDataObjFloatList_metaObject;
igMetaField *g_beDataObjFloatList_dataMetaField;

void beDataObjFloatList_Create(int allocator) {
    beDataObjFloatList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589848, allocator);
}

void *beDataObjFloatList_GetMetaObject(void) {
    igMetaObject *g = g_beDataObjFloatList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataObjFloatList_EnsureRegistered();
    }
    return g_beDataObjFloatList_metaObject;
}

int beDataObjFloatList_GetVTable(void) {
    union U_3642b0 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q38;
    void **q3c;

    igObject_InitHeader(u.b);
    q38 = &u.p[2];
    *q38 = 0;
    u.w[0] = (int)(&g_beDataObjFloatList_vtable[0]);
    q3c = &u.p[3];
    *q3c = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beDataObjFloatList_vtable[0]);
    if (q3c != 0) {
        a = (struct Rc *)*q3c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q38 != 0) {
        c = (char *)*q38;
        if (c != 0) {
            a1 = (int *)(c - 8);
            v0 = *(int *)(c - 4) - 1;
            *(int *)(c - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void beDataObjFloatList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjFloatList_Register);
}

static igMetaObjectCallback g_beDataObjFloatList_callbackList[] = { igFloatList_EnsureRegistered, 0 };

void *beDataObjFloatList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjFloatList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjFloatList_GetMetaObjectFunction,
        "beDataObjFloatList",
        0x10, /* instance size */
        beDataObjFloatList_GetVTable,
        beDataObjFloatList_InitFields,
        0, /* extra callback item */
        g_beDataObjFloatList_callbackList /* callback list */
    );
}

void beDataObjFloatList_GetMetaObjectFunction(void)
{
    beDataObjFloatList_GetMetaObject();
}

static FieldFactory g_beDataObjFloatList_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beDataObjFloatList_fieldTable[] = {
    "_data",
};
static igMetaField **g_beDataObjFloatList_fieldHandles[] = {
    &g_beDataObjFloatList_dataMetaField,
};
static int g_beDataObjFloatList_fieldOffsets[] = {
    12,
};

void beDataObjFloatList_InitFields(void) {
    int base;
    void *data;
    void *meta;

    meta = (void *)g_beDataObjFloatList_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataObjFloatList_ctorTable, 1);
    data = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)data)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)data)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataObjFloatList_fieldTable, g_beDataObjFloatList_fieldHandles, g_beDataObjFloatList_fieldOffsets, base);
}

