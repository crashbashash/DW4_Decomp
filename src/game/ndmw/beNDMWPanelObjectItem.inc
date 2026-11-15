igMetaObject *g_beNDMWPanelObjectItem_metaObject;
int g_beNDMWPanelObjectItem_nameExternalEnumStorage;
igMetaField *g_beNDMWPanelObjectItem_listFolderMetaField;
igMetaField *g_beNDMWPanelObjectItem_listColorMetaField;

igMetaObject *FUN_003be5a0(void) {
    if (g_beNDMWPanelObjectItem_metaObject == 0) {
        g_beNDMWPanelObjectItem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWPanelObjectItem_metaObject;
}

igMetaObject *beNDMWPanelObjectItem_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelObjectItem_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003be6d0();
    return g_beNDMWPanelObjectItem_metaObject;
}

int beNDMWPanelObjectItem_GetVTable(void) {
    struct Obj_3be640 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.vt = &DAT_0053e130[0];
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053e130[0];
    igSmartPointer_igIntList_Destruct(&obj.w16, -1);
    igSmartPointer_igObjectList_Destruct(&obj.w15, -1);
    FUN_003be240((Obj_3be240 *)&obj, (short)0);
    return t;
}

void FUN_003be6d0(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectItem_Register);
}

static igMetaObjectCallback g_beNDMWPanelObjectItem_callbackList[] = { igObjectList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWPanelObjectItem_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelObjectItem_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectItem_GetMetaObject,
        "beNDMWPanelObjectItem",
        0x44, /* instance size */
        beNDMWPanelObjectItem_GetVTable,
        beNDMWPanelObjectItem_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectItem_callbackList /* callback list */
    );
}

void beNDMWPanelObjectItem_GetMetaObject(void)
{
    beNDMWPanelObjectItem_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelObjectItem_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelObjectItem_fieldTable[] = {
    "_listFolder",
    "_listColor",
};
static igMetaField **g_beNDMWPanelObjectItem_fieldHandles[] = {
    &g_beNDMWPanelObjectItem_listFolderMetaField,
    &g_beNDMWPanelObjectItem_listColorMetaField,
};
static int g_beNDMWPanelObjectItem_fieldOffsets[] = {
    60,
    64,
};

void beNDMWPanelObjectItem_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWPanelObjectItem_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWPanelObjectItem_ctorTable, 2);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_page"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 1);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beNDMWPanelObjectItem_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((RT *)temp_v0_2)->references = ((RT *)temp_v0_2)->references - 1;
    if (((unsigned long long)(long long)((RT *)temp_v0_2)->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((FT *)temp_s0)->meta = igObjectList_GetOrCreateMetaObject();
    ((FT *)temp_s0)->flag = 1;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((FT *)temp_s0_2)->meta = igIntList_GetOrCreateMetaObject();
    ((FT *)temp_s0_2)->flag = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWPanelObjectItem_fieldTable, g_beNDMWPanelObjectItem_fieldHandles, g_beNDMWPanelObjectItem_fieldOffsets, temp_s2);
}

