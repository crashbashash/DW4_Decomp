igMetaObject *g_beModelCtrlInfoDataTrc_metaObject;
int g_beModelCtrlInfoDataTrc_nameStorage;
igMetaField *g_beModelCtrlInfoDataTrc_recorderNodeMetaField;

igMetaObject *beModelCtrlInfoDataTrc_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoDataTrc_metaObject == 0) {
        g_beModelCtrlInfoDataTrc_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlInfoDataTrc_metaObject;
}

void *beModelCtrlInfoDataTrc_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoDataTrc_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoDataTrc_EnsureRegistered();
    }
    return g_beModelCtrlInfoDataTrc_metaObject;
}

int beModelCtrlInfoDataTrc_GetVTable(void) {
    union U_3532e0 u;
    int temp_s1;
    void ** q0;
    igObject * q1;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q0 = (void **)&u.b[8];
    *q0 = 0;
    u.vt = (int)(&g_beModelCtrlInfoDataTrc_vtable[0]);
    q1 = (igObject *)&u.b[16];
    *(int *)q1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&g_beModelCtrlInfoDataTrc_vtable[0]);
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)q1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    u.vt = (int)(&g_igNamedObject_vtable[0]);
    if (q0 != 0) {
        temp_v1 = *q0;
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

void beModelCtrlInfoDataTrc_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataTrc_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoDataTrc_callbackList[] = { igTransformRecorder_EnsureRegistered, 0 };

void *beModelCtrlInfoDataTrc_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataTrc_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataTrc_GetMetaObjectFunction,
        "beModelCtrlInfoDataTrc",
        0x14, /* instance size */
        beModelCtrlInfoDataTrc_GetVTable,
        beModelCtrlInfoDataTrc_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataTrc_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataTrc_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataTrc_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataTrc_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoDataTrc_fieldTable[] = {
    "_recorderNode",
};
static igMetaField **g_beModelCtrlInfoDataTrc_fieldHandles[] = {
    &g_beModelCtrlInfoDataTrc_recorderNodeMetaField,
};
static int g_beModelCtrlInfoDataTrc_fieldOffsets[] = {
    16,
};

void beModelCtrlInfoDataTrc_InitFields(void) {
    int base;
    int index;
    void **found;
    void *recorderNode;
    void *meta;
    igStringMetaField *clone;

    meta = (igMetaObject *)(((void * *)&g_beModelCtrlInfoDataTrc_metaObject)[0]);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoDataTrc_ctorTable, 1);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igStringMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igStringMetaField_SetDefaultText(clone, "TRC");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoDataTrc_nameStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    recorderNode = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)recorderNode)->_metaObject = igTransformRecorder_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beModelCtrlInfoDataTrc_fieldTable, g_beModelCtrlInfoDataTrc_fieldHandles, g_beModelCtrlInfoDataTrc_fieldOffsets, base);
}

