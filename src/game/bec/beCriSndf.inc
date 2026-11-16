igMetaObject *g_beCriSndf_metaObject;
igMetaField *g_beCriSndf_reqMetaField;
igMetaField *g_beCriSndf_seqMetaField;
igMetaField *g_beCriSndf_isPlayingMetaField;

void beCriSndf_Create(int arg0) {
    beCriSndf_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589AB0, arg0);
}

igMetaObject *beCriSndf_GetOrCreateMetaObject(void) {
    if (g_beCriSndf_metaObject == 0) {
        g_beCriSndf_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCriSndf_metaObject;
}

void *beCriSndf_GetMetaObject(void) {
    igMetaObject *g = g_beCriSndf_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCriSndf_EnsureRegistered();
    }
    return g_beCriSndf_metaObject;
}

int beCriSndf_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&g_beCriSndf_vtable[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void beCriSndf_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriSndf_Register);
}

void *beCriSndf_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriSndf_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriSndf_GetMetaObjectFunction,
        "beCriSndf",
        0x20, /* instance size */
        beCriSndf_GetVTable,
        beCriSndf_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriSndf_GetMetaObjectFunction(void)
{
    beCriSndf_GetMetaObject();
}

static FieldFactory g_beCriSndf_ctorTable[] = {
    igIntMetaField_Create,
    igLongMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beCriSndf_fieldTable[] = {
    "_req",
    "_seq",
    "_isPlaying",
};
static igMetaField **g_beCriSndf_fieldHandles[] = {
    &g_beCriSndf_reqMetaField,
    &g_beCriSndf_seqMetaField,
    &g_beCriSndf_isPlayingMetaField,
};
static int g_beCriSndf_fieldOffsets[] = {
    8,
    16,
    24,
};

void beCriSndf_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriSndf_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCriSndf_ctorTable, 3);
    igMetaObject_NameFields(temp_s0, g_beCriSndf_fieldTable, g_beCriSndf_fieldHandles, g_beCriSndf_fieldOffsets, temp_s1);
}

