igMetaObject *g_beNDMWPanelObjectWaza_metaObject;
int g_beNDMWPanelObjectWaza_nameExternalEnumStorage;
igMetaField *g_beNDMWPanelObjectWaza_listFolderMetaField;
igMetaField *g_beNDMWPanelObjectWaza_listColorMetaField;

igMetaObject *FUN_003be8e0(void) {
    if (g_beNDMWPanelObjectWaza_metaObject == 0) {
        g_beNDMWPanelObjectWaza_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWPanelObjectWaza_metaObject;
}

igMetaObject *beNDMWPanelObjectWaza_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelObjectWaza_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003bea10();
done:
    return g_beNDMWPanelObjectWaza_metaObject;
}

int beNDMWPanelObjectWaza_GetVTable(void) {
    struct Obj_3be980 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.vt = &DAT_0053e1a0[0];
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053e1a0[0];
    igSmartPointer_igIntList_Destruct(&obj.w16, -1);
    igSmartPointer_igObjectList_Destruct(&obj.w15, -1);
    FUN_003be240((Obj_3be240 *)&obj, (short)0);
    return t;
}

void FUN_003bea10(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectWaza_Register);
}

static igMetaObjectCallback g_beNDMWPanelObjectWaza_callbackList[] = { igObjectList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWPanelObjectWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelObjectWaza_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectWaza_GetMetaObject,
        "beNDMWPanelObjectWaza",
        0x44, /* instance size */
        beNDMWPanelObjectWaza_GetVTable,
        beNDMWPanelObjectWaza_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectWaza_callbackList /* callback list */
    );
}

void beNDMWPanelObjectWaza_GetMetaObject(void)
{
    beNDMWPanelObjectWaza_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelObjectWaza_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelObjectWaza_fieldTable[] = {
    "_listFolder",
    "_listColor",
};
static igMetaField **g_beNDMWPanelObjectWaza_fieldHandles[] = {
    &g_beNDMWPanelObjectWaza_listFolderMetaField,
    &g_beNDMWPanelObjectWaza_listColorMetaField,
};
static int g_beNDMWPanelObjectWaza_fieldOffsets[] = {
    60,
    64,
};

void beNDMWPanelObjectWaza_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    igMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWPanelObjectWaza_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWPanelObjectWaza_ctorTable, 2);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_page"));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 0);
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWPanelObjectWaza_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0)->_construct = 1;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWPanelObjectWaza_fieldTable, g_beNDMWPanelObjectWaza_fieldHandles, g_beNDMWPanelObjectWaza_fieldOffsets, temp_s2);
}

