igMetaObject *g_beFileChkObj_metaObject;
igMetaField *g_beFileChkObj_fdMetaField;

void beFileChkObj_Create(int allocator) {
    beFileChkObj_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589780, allocator);
}

void *beFileChkObj_GetMetaObject(void) {
    igMetaObject *g = g_beFileChkObj_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFileChkObj_EnsureRegistered();
    }
    return g_beFileChkObj_metaObject;
}

int beFileChkObj_GetVTable(void) {
    struct F_363020 f;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader(&f);
    f.vt = &g_beFileChkObj_vtable[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &g_beFileChkObj_vtable[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return temp_s0;
}

void beFileChkObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFileChkObj_Register);
}

static igMetaObjectCallback g_beFileChkObj_callbackList[] = { igFile_EnsureRegistered, 0 };

void *beFileChkObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFileChkObj_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFileChkObj_GetMetaObjectFunction,
        "beFileChkObj",
        0xc, /* instance size */
        beFileChkObj_GetVTable,
        beFileChkObj_InitFields,
        0, /* extra callback item */
        g_beFileChkObj_callbackList /* callback list */
    );
}

void beFileChkObj_GetMetaObjectFunction(void)
{
    beFileChkObj_GetMetaObject();
}

static FieldFactory g_beFileChkObj_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beFileChkObj_fieldTable[] = {
    "_fd",
};
static igMetaField **g_beFileChkObj_fieldHandles[] = {
    &g_beFileChkObj_fdMetaField,
};
static int g_beFileChkObj_fieldOffsets[] = {
    8,
};

void beFileChkObj_InitFields(void) {
    int base;
    void *fd;
    void *meta;

    meta = (void *)g_beFileChkObj_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFileChkObj_ctorTable, 1);
    fd = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)fd)->_metaObject = igFile_GetOrCreateMetaObject();
    ((igRefMetaField *)fd)->_construct = 1;
    igMetaObject_NameFields(meta, g_beFileChkObj_fieldTable, g_beFileChkObj_fieldHandles, g_beFileChkObj_fieldOffsets, base);
}

