igMetaObject *g_beSeCtl_metaObject;
igMetaField *g_beSeCtl_sndMngMetaField;

void beSeCtl_CreateInstance(int allocator) {
    beSeCtl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587FE8, allocator);
}

igMetaObject *beSeCtl_GetOrCreateMetaObject(void) {
    if (g_beSeCtl_metaObject == 0) {
        g_beSeCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSeCtl_metaObject;
}

igMetaObject *beSeCtl_GetMetaObject(void) {
    igMetaObject *g = g_beSeCtl_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beSeCtl_EnsureRegistered();
done:
    return g_beSeCtl_metaObject;
}

int beSeCtl_GetVTable(void) {
    union U_3465d0 u;
    int temp_s1;
    void **q2;
    igObject *q3;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    q2 = &u.p[2];
    *q2 = 0;
    q3 = (igObject *)&u.b[24];
    *(int *)q3 = 0;
    u.w[0] = (int)(&g_beSeCtl_vtable[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beBaseInfoManager_vtable[0]);
    if (q3 != 0) {
        q3 = *(igObject **)q3;
        if (q3 != 0) {
            q3->_refCount = (int)q3->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q3->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void beSeCtl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSeCtl_Register);
}

static igMetaObjectCallback g_beSeCtl_callbackList[] = { beSound_EnsureRegistered, 0 };

void *beSeCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSeCtl_GetMetaObjectFunction,
        "beSeCtl",
        0x24, /* instance size */
        beSeCtl_GetVTable,
        beSeCtl_InitFields,
        0, /* extra callback item */
        g_beSeCtl_callbackList /* callback list */
    );
}

void beSeCtl_GetMetaObjectFunction(void)
{
    beSeCtl_GetMetaObject();
}

static FieldFactory g_beSeCtl_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beSeCtl_fieldTable[] = {
    "_sndMng",
};
static igMetaField **g_beSeCtl_fieldHandles[] = {
    &g_beSeCtl_sndMngMetaField,
};
static int g_beSeCtl_fieldOffsets[] = {
    32,
};

void beSeCtl_InitFields(void) {
    int base;
    void *sndMng;
    void *meta;

    meta = (void *)g_beSeCtl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSeCtl_ctorTable, 1);
    sndMng = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)sndMng)->_metaObject = (int)beSound_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)sndMng)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beSeCtl_fieldTable, g_beSeCtl_fieldHandles, g_beSeCtl_fieldOffsets, base);
}

