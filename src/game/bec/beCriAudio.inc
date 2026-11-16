igMetaObject *g_beCriAudio_metaObject;
igMetaField *g_beCriAudio_adxtMetaField;
igMetaField *g_beCriAudio_sndfMetaField;
igMetaField *g_beCriAudio_audioTypeMetaField;
igMetaField *g_beCriAudio_errVolumeMetaField;

igMetaObject *beCriAudio_GetOrCreateMetaObject(void) {
    if (g_beCriAudio_metaObject == 0) {
        g_beCriAudio_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCriAudio_metaObject;
}

void *beCriAudio_GetMetaObject(void) {
    unsigned char b;
    if (g_beCriAudio_metaObject != 0) {
        b = (g_beCriAudio_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beCriAudio_EnsureRegistered();
done:
    return g_beCriAudio_metaObject;
}

int beCriAudio_GetVTable(void) {
    union U_367240 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q38;
    void **q3c;

    igObject_InitHeader(u.b);
    q38 = &u.p[2];
    q3c = &u.p[3];
    u.w[0] = (int)(&g_beCriAudio_vtable[0]);
    *q38 = 0;
    *q3c = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beCriAudio_vtable[0]);
    if (q3c != 0) {
        a = (struct Rc *)*q3c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q38 != 0) {
        a = (struct Rc *)*q38;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}

void beCriAudio_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriAudio_Register);
}

static igMetaObjectCallback g_beCriAudio_callbackList[] = { igAdxAudio_EnsureRegistered, beCriSndf_EnsureRegistered, 0 };

void *beCriAudio_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriAudio_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriAudio_GetMetaObjectFunction,
        "beCriAudio",
        0x18, /* instance size */
        beCriAudio_GetVTable,
        beCriAudio_InitFields,
        0, /* extra callback item */
        g_beCriAudio_callbackList /* callback list */
    );
}

void beCriAudio_GetMetaObjectFunction(void)
{
    beCriAudio_GetMetaObject();
}

static FieldFactory g_beCriAudio_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beCriAudio_fieldTable[] = {
    "_adxt",
    "_sndf",
    "_audioType",
    "_errVolume",
};
static igMetaField **g_beCriAudio_fieldHandles[] = {
    &g_beCriAudio_adxtMetaField,
    &g_beCriAudio_sndfMetaField,
    &g_beCriAudio_audioTypeMetaField,
    &g_beCriAudio_errVolumeMetaField,
};
static int g_beCriAudio_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void beCriAudio_InitFields(void) {
    int base;
    void *sndf;
    void *adxt;
    void *meta;

    meta = (void *)g_beCriAudio_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCriAudio_ctorTable, 4);
    adxt = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)adxt)->_metaObject = igAdxAudio_GetOrCreateMetaObject();
    sndf = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)sndf)->_metaObject = (int)beCriSndf_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beCriAudio_fieldTable, g_beCriAudio_fieldHandles, g_beCriAudio_fieldOffsets, base);
}

