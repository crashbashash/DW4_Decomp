igMetaObject *g_beLuaData_metaObject;
igMetaField *g_beLuaData_dataObjectMetaField;

igMetaObject *beLuaData_GetMetaObject(void) {
    igMetaObject *g = g_beLuaData_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beLuaData_EnsureRegistered();
done:
    return g_beLuaData_metaObject;
}

int beLuaData_GetVTable(void) {
    struct Obj_35b1a0 obj;
    char *o;
    igObject *io;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_beLuaData_vtable[0];
    obj.w3 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beLuaData_vtable[0];
    if (&obj.w3 != 0) {
        io = obj.w3;
        if (io != 0) {
            io->_refCount = io->_refCount - 1;
            if ((io->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(io);
            }
        }
    }
    obj.vt = &g_igNamedObject_vtable[0];
    if (&obj.w2 != 0) {
        o = obj.w2;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void beLuaData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaData_Register);
}

static igMetaObjectCallback g_beLuaData_callbackList[] = { beLuaDataObject_EnsureRegistered, 0 };

void *beLuaData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beLuaData_GetMetaObjectFunction,
        "beLuaData",
        0x10, /* instance size */
        beLuaData_GetVTable,
        beLuaData_InitFields,
        0, /* extra callback item */
        g_beLuaData_callbackList /* callback list */
    );
}

void beLuaData_GetMetaObjectFunction(void)
{
    beLuaData_GetMetaObject();
}

static FieldFactory g_beLuaData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beLuaData_fieldTable[] = {
    "_dataObject",
};
static igMetaField **g_beLuaData_fieldHandles[] = {
    &g_beLuaData_dataObjectMetaField,
};
static int g_beLuaData_fieldOffsets[] = {
    12,
};

void beLuaData_InitFields(void) {
    int base;
    void *dataObject;
    void *meta;

    meta = (void *)g_beLuaData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLuaData_ctorTable, 1);
    dataObject = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataObject)->_metaObject = (int)beLuaDataObject_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beLuaData_fieldTable, g_beLuaData_fieldHandles, g_beLuaData_fieldOffsets, base);
}

