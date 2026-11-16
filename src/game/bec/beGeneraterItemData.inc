igMetaObject *g_beGeneraterItemData_metaObject;
igMetaField *g_beGeneraterItemData_dataListMetaField;

void *beGeneraterItemData_GetMetaObject(void) {
    unsigned char b;
    if (g_beGeneraterItemData_metaObject != 0) {
        b = (g_beGeneraterItemData_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beGeneraterItemData_EnsureRegistered();
done:
    return g_beGeneraterItemData_metaObject;
}

int beGeneraterItemData_GetVTable(void) {
    union U_360540 u;
    int temp_s0;
    igObject *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_beGeneraterItemData_vtable[0];
    q0 = (igObject *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beGeneraterItemData_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beGeneraterItemData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemData_Register);
}

static igMetaObjectCallback g_beGeneraterItemData_callbackList[] = { beGeneraterItemDataOneList_EnsureRegistered, 0 };

void *beGeneraterItemData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterItemData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemData_GetMetaObjectFunction,
        "beGeneraterItemData",
        0x10, /* instance size */
        beGeneraterItemData_GetVTable,
        beGeneraterItemData_InitFields,
        0, /* extra callback item */
        g_beGeneraterItemData_callbackList /* callback list */
    );
}

void beGeneraterItemData_GetMetaObjectFunction(void)
{
    beGeneraterItemData_GetMetaObject();
}

static FieldFactory g_beGeneraterItemData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterItemData_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beGeneraterItemData_fieldHandles[] = {
    &g_beGeneraterItemData_dataListMetaField,
};
static int g_beGeneraterItemData_fieldOffsets[] = {
    12,
};

void beGeneraterItemData_InitFields(void) {
    int base;
    void *dataList;
    void *meta;

    meta = (void *)g_beGeneraterItemData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterItemData_ctorTable, 1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beGeneraterItemDataOneList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterItemData_fieldTable, g_beGeneraterItemData_fieldHandles, g_beGeneraterItemData_fieldOffsets, base);
}

