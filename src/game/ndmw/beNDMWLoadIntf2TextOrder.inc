igMetaObject *g_beNDMWLoadIntf2TextOrder_metaObject;
int g_beNDMWLoadIntf2TextOrder_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2TextOrder_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2TextOrder_luaMetaField;

void beNDMWLoadIntf2TextOrder_Create(int arg0) {
    beNDMWLoadIntf2TextOrder_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2TextOrder_metaObject, arg0);
}

igMetaObject *beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2TextOrder_metaObject == 0) {
        g_beNDMWLoadIntf2TextOrder_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadIntf2TextOrder_metaObject;
}

void *beNDMWLoadIntf2TextOrder_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2TextOrder_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadIntf2TextOrder_EnsureRegistered();
    }
    return g_beNDMWLoadIntf2TextOrder_metaObject;
}

int beNDMWLoadIntf2TextOrder_GetVTable(void) {
    union U_3c77a0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWLoadIntf2TextOrder_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
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

void beNDMWLoadIntf2TextOrder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2TextOrder_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2TextOrder_callbackList[] = { beMessenger_EnsureRegistered, beLua_EnsureRegistered, 0 };

void *beNDMWLoadIntf2TextOrder_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2TextOrder_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2TextOrder_GetMetaObject,
        "beNDMWLoadIntf2TextOrder",
        0x18, /* instance size */
        beNDMWLoadIntf2TextOrder_GetVTable,
        beNDMWLoadIntf2TextOrder_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2TextOrder_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2TextOrder_GetMetaObject(void)
{
    beNDMWLoadIntf2TextOrder_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2TextOrder_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWLoadIntf2TextOrder_fieldTable[] = {
    "_messenger",
    "_lua",
};
static igMetaField **g_beNDMWLoadIntf2TextOrder_fieldHandles[] = {
    &g_beNDMWLoadIntf2TextOrder_messengerMetaField,
    &g_beNDMWLoadIntf2TextOrder_luaMetaField,
};
static int g_beNDMWLoadIntf2TextOrder_fieldOffsets[] = {
    16,
    20,
};

void beNDMWLoadIntf2TextOrder_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    igStringMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWLoadIntf2TextOrder_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2TextOrder_ctorTable, 2);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "TEXTORDER");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2TextOrder_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2TextOrder_fieldTable, g_beNDMWLoadIntf2TextOrder_fieldHandles, g_beNDMWLoadIntf2TextOrder_fieldOffsets, temp_s2);
}

