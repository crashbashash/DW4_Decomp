igMetaObject *g_beCriHandle_metaObject;
igMetaField *g_beCriHandle_audioMetaField;
igMetaField *g_beCriHandle_volumeMetaField;
igMetaField *g_beCriHandle_playIDMetaField;
igMetaField *g_beCriHandle_typeMetaField;
igMetaField *g_beCriHandle_priorityMetaField;

void beCriHandle_Create(int allocator) {
    beCriHandle_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5899C8, allocator);
}

igMetaObject *beCriHandle_GetOrCreateMetaObject(void) {
    if (g_beCriHandle_metaObject == 0) {
        g_beCriHandle_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCriHandle_metaObject;
}

void *beCriHandle_GetMetaObject(void) {
    igMetaObject *g = g_beCriHandle_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCriHandle_EnsureRegistered();
    }
    return g_beCriHandle_metaObject;
}

int beCriHandle_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;

    igObject_InitHeader(u.b);
    p48 = &u.b[8];
    *(int *)p48 = 0;
    u.vt = (int)&g_beCriHandle_vtable[0];
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beCriHandle_vtable[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p48 != 0) {
        v1 = *(int **)p48;
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

void beCriHandle_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriHandle_Register);
}

static igMetaObjectCallback g_beCriHandle_callbackList[] = { beCriAudio_EnsureRegistered, beCriVolume_EnsureRegistered, 0 };

void *beCriHandle_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriHandle_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beCriHandle_GetMetaObjectFunction,
        "beCriHandle",
        0x28, /* instance size */
        beCriHandle_GetVTable,
        beCriHandle_InitFields,
        0, /* extra callback item */
        g_beCriHandle_callbackList /* callback list */
    );
}

void beCriHandle_GetMetaObjectFunction(void)
{
    beCriHandle_GetMetaObject();
}

static FieldFactory g_beCriHandle_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igLongMetaField_Create,
    igShortMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_beCriHandle_fieldTable[] = {
    "_audio",
    "_volume",
    "_playID",
    "_type",
    "_priority",
};
static igMetaField **g_beCriHandle_fieldHandles[] = {
    &g_beCriHandle_audioMetaField,
    &g_beCriHandle_volumeMetaField,
    &g_beCriHandle_playIDMetaField,
    &g_beCriHandle_typeMetaField,
    &g_beCriHandle_priorityMetaField,
};
static int g_beCriHandle_fieldOffsets[] = {
    12,
    16,
    24,
    32,
    34,
};

void beCriHandle_InitFields(void) {
    int base;
    void *volume;
    void *audio;
    void *meta;

    meta = (void *)g_beCriHandle_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCriHandle_ctorTable, 5);
    audio = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)audio)->_metaObject = (int)beCriAudio_GetOrCreateMetaObject();
    ((igRefMetaField *)audio)->_construct = 1;
    volume = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)volume)->_metaObject = (int)beCriVolume_GetOrCreateMetaObject();
    ((igRefMetaField *)volume)->_construct = 1;
    igMetaObject_NameFields(meta, g_beCriHandle_fieldTable, g_beCriHandle_fieldHandles, g_beCriHandle_fieldOffsets, base);
}

