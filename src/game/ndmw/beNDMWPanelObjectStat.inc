igMetaObject *g_beNDMWPanelObjectStat_metaObject;
int g_beNDMWPanelObjectStat_nameExternalEnumStorage;
igMetaField *g_beNDMWPanelObjectStat_listFolderMetaField;
igMetaField *g_beNDMWPanelObjectStat_listColorMetaField;
igMetaField *g_beNDMWPanelObjectStat_playerWorkMetaField;

igMetaObject *beNDMWPanelObjectStat_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelObjectStat_metaObject == 0) {
        g_beNDMWPanelObjectStat_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWPanelObjectStat_metaObject;
}

igMetaObject *beNDMWPanelObjectStat_ResolveMetaObject(void)
{
    igMetaObject *g = g_beNDMWPanelObjectStat_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWPanelObjectStat_EnsureRegistered();
    return g_beNDMWPanelObjectStat_metaObject;
}

int beNDMWPanelObjectStat_GetVTable(void) {
    union U_3be190 u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[9] = 0;
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[0] = (int)(&g_beNDMWPanelObjectStat_vtable[0]);
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beNDMWPanelObjectStat_vtable[0]);
    FUN_003bde80((struct Ref **)(&u.w[17]), (short)(-1));
    igSmartPointer_igIntList_Destruct(&u.w[16], -1);
    igSmartPointer_igStringRefList_Destruct(&u.w[15], -1);
    FUN_003be240((Obj_3be240 *)u.b, (short)0);
    return temp_s2;
}

Obj_3be240 *FUN_003be240(Obj_3be240 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &g_beNDMWPanelObject_vtable[0];
        arg0->rel(&arg0->m48);
        arg0->rel(&arg0->m44);
        arg0->rel(&arg0->m36);
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void beNDMWPanelObjectStat_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObjectStat_Register);
}

static igMetaObjectCallback g_beNDMWPanelObjectStat_callbackList[] = { igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, beNDMWMdlPlayerInfoWork_EnsureRegistered, 0 };

void *beNDMWPanelObjectStat_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelObjectStat_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectStat_GetMetaObject,
        "beNDMWPanelObjectStat",
        0x48, /* instance size */
        beNDMWPanelObjectStat_GetVTable,
        beNDMWPanelObjectStat_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectStat_callbackList /* callback list */
    );
}

void beNDMWPanelObjectStat_GetMetaObject(void)
{
    beNDMWPanelObjectStat_ResolveMetaObject();
}

igMetaObject *beNDMWPanelObject_GetPublishedMetaObject(void) {
    return g_beNDMWPanelObject_metaObject;
}

static FieldFactory g_beNDMWPanelObjectStat_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelObjectStat_fieldTable[] = {
    "_listFolder",
    "_listColor",
    "_playerWork",
};
static igMetaField **g_beNDMWPanelObjectStat_fieldHandles[] = {
    &g_beNDMWPanelObjectStat_listFolderMetaField,
    &g_beNDMWPanelObjectStat_listColorMetaField,
    &g_beNDMWPanelObjectStat_playerWorkMetaField,
};
static int g_beNDMWPanelObjectStat_fieldOffsets[] = {
    60,
    64,
    68,
};

void beNDMWPanelObjectStat_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igMetaObject *temp_s1;
    igMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (igMetaObject *)(g_beNDMWPanelObjectStat_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWPanelObjectStat_ctorTable, 3);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_page"));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 2);
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWPanelObjectStat_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)&temp_v0_2->_refCount = (int)((int) (*(int *)&temp_v0_2->_refCount - 1));
    if (((unsigned long long) ((long long) *(int *)&temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = igStringRefList_GetOrCreateMetaObject();
    temp_s0->_construct = 1;
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0_2->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s0_2->_construct = 1;
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0_3->_metaObject = (int)beNDMWMdlPlayerInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWPanelObjectStat_fieldTable, g_beNDMWPanelObjectStat_fieldHandles, g_beNDMWPanelObjectStat_fieldOffsets, temp_s2);
}

