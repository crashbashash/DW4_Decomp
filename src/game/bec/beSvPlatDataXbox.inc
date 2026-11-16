igMetaObject *g_beSvPlatDataXbox_metaObject;
int g_beSvPlatDataXbox_connectMaxStorage;
igMetaField *g_beSvPlatDataXbox_imageSizeMetaField;
igMetaField *g_beSvPlatDataXbox_imageMetaField;
igMetaField *g_beSvPlatDataXbox_saveDataSizeMetaField;
igMetaField *g_beSvPlatDataXbox_dataOffSetMetaField;

void *beSvPlatDataXbox_GetMetaObject(void) {
    igMetaObject *g = g_beSvPlatDataXbox_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPlatDataXbox_EnsureRegistered();
    }
    return g_beSvPlatDataXbox_metaObject;
}

int beSvPlatDataXbox_GetVTable(void) {
    union U u;
    int temp_s0;
    igObject *q0;
    igObject *q1;

    igObject_InitHeader(u.b);
    q1 = (igObject *)&u.b[12];
    *(int *)q1 = 0;
    u.vt = (int)&g_beSvPlatDataXbox_vtable[0];
    q0 = (igObject *)&u.b[36];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSvPlatDataXbox_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_beSvPlatBaseData_vtable[0];
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)q1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void beSvPlatDataXbox_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataXbox_Register);
}

static igMetaObjectCallback g_beSvPlatDataXbox_callbackList[] = { beXboxImage24k_EnsureRegistered, 0 };

void *beSvPlatDataXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataXbox_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataXbox_GetMetaObjectFunction,
        "beSvPlatDataXbox",
        0x2c, /* instance size */
        beSvPlatDataXbox_GetVTable,
        beSvPlatDataXbox_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataXbox_callbackList /* callback list */
    );
}

void beSvPlatDataXbox_GetMetaObjectFunction(void)
{
    beSvPlatDataXbox_GetMetaObject();
}

static FieldFactory g_beSvPlatDataXbox_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igIntArrayMetaField_Create,
};
static const char *g_beSvPlatDataXbox_fieldTable[] = {
    "_imageSize",
    "_image",
    "_saveDataSize",
    "_dataOffSet",
};
static igMetaField **g_beSvPlatDataXbox_fieldHandles[] = {
    &g_beSvPlatDataXbox_imageSizeMetaField,
    &g_beSvPlatDataXbox_imageMetaField,
    &g_beSvPlatDataXbox_saveDataSizeMetaField,
    &g_beSvPlatDataXbox_dataOffSetMetaField,
};
static int g_beSvPlatDataXbox_fieldOffsets[] = {
    32,
    36,
    40,
    24,
};

void beSvPlatDataXbox_InitFields(void) {
    int base;
    int index;
    void **found;
    F_3474b0 *image;
    G_3474b0 *tg;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beSvPlatDataXbox_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvPlatDataXbox_ctorTable, 4);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_connectMax"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igIntMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igIntMetaField_SetDefault(clone, 9);
    clone->_externalEnumStorage = (int)(&g_beSvPlatDataXbox_connectMaxStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    image = (F_3474b0 *)(igMetaObject_GetFieldAt(meta, base + 1));
    image->f56 = (int)beXboxImage24k_GetOrCreateMetaObject();
    image->b52 = 1;
    tg = (G_3474b0 *)igMetaObject_GetFieldAt(meta, base + 3);
    tg->w52 = 2;
    igMetaObject_NameFields(meta, g_beSvPlatDataXbox_fieldTable, g_beSvPlatDataXbox_fieldHandles, g_beSvPlatDataXbox_fieldOffsets, base);
}

