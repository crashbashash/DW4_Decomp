igMetaObject *g_bePoint01_metaObject;
igMetaField *g_bePoint01_pointNoMetaField;

void bePoint01_CreateInstance(int allocator) {
    bePoint01_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588498, allocator);
}

igMetaObject *bePoint01_GetOrCreateMetaObject(void) {
    if (g_bePoint01_metaObject == 0) {
        g_bePoint01_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_bePoint01_metaObject;
}

void *bePoint01_GetMetaObject(void) {
    bool ok;
    if (g_bePoint01_metaObject == 0) goto make;
    ok = !!(g_bePoint01_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    bePoint01_EnsureRegistered();
done:;
    return g_bePoint01_metaObject;
}

int bePoint01_GetVTable(void) {
    union U u;
    int r;

    int *v1; int *a1; int v0; int *a0;
    char *pr; char *ps;
    igObject_InitHeader(u.b);
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    pr = &u.b[24];
    *(int *)pr = 0;
    u.vt = (int)&g_bePoint01_vtable[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beBaseInfoManager_vtable[0];
    if (pr != 0) {
        a0 = *(int **)pr;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}

void bePoint01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePoint01_Register);
}

void *bePoint01_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePoint01_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        bePoint01_GetMetaObjectFunction,
        "bePoint01",
        0x24, /* instance size */
        bePoint01_GetVTable,
        bePoint01_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void bePoint01_GetMetaObjectFunction(void)
{
    bePoint01_GetMetaObject();
}

static FieldFactory g_bePoint01_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_bePoint01_fieldTable[] = {
    "_pointNo",
};
static igMetaField **g_bePoint01_fieldHandles[] = {
    &g_bePoint01_pointNoMetaField,
};
static int g_bePoint01_fieldOffsets[] = {
    32,
};

void bePoint01_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_bePoint01_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_bePoint01_ctorTable, 1);
    igMetaObject_NameFields(meta, g_bePoint01_fieldTable, g_bePoint01_fieldHandles, g_bePoint01_fieldOffsets, base);
}

