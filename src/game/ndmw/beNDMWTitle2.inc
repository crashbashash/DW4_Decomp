igMetaObject *g_beNDMWTitle2_metaObject;
igMetaField *g_beNDMWTitle2_padManagerMetaField;
igMetaField *g_beNDMWTitle2_mcUtilCtrlMetaField;
igMetaField *g_beNDMWTitle2_isMakeFileOKMetaField;
igMetaField *g_beNDMWTitle2_selectMetaField;

void beNDMWTitle2_CreateInstance(int arg0) {
    FUN_003b2a90();
    igMetaObject_CreateInstance(g_beNDMWTitle2_metaObject, arg0);
}

igMetaObject *FUN_003b28e0(void) {
    if (g_beNDMWTitle2_metaObject == 0) {
        g_beNDMWTitle2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWTitle2_metaObject;
}

void *FUN_003b2930(void) {
    unsigned char b;
    if (g_beNDMWTitle2_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWTitle2_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b2a90();
done:
    return g_beNDMWTitle2_metaObject;
}

int beNDMWTitle2_GetVTable(void) {
    struct Obj_3b2980 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053e9a0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053e9a0[0];
    FUN_003b2a10((ObjectRefWord *)&obj.w9, -1);
    FUN_0033dda0(&obj.w8, -1);
    FUN_0033f5e0(&obj, 0);
    return t;
}

ObjectRefWord *FUN_003b2a10(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_003b2a90(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2_Register);
}

static igMetaObjectCallback g_beNDMWTitle2_callbackList[] = { FUN_0034cb30, FUN_003c5380, 0 };

void *beNDMWTitle2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWTitle2_GetMetaObject,
        "beNDMWTitle2",
        0x34, /* instance size */
        beNDMWTitle2_GetVTable,
        beNDMWTitle2_InitFields,
        0, /* extra callback item */
        g_beNDMWTitle2_callbackList /* callback list */
    );
}

void beNDMWTitle2_GetMetaObject(void)
{
    FUN_003b2930();
}

static FieldFactory g_beNDMWTitle2_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWTitle2_fieldTable[] = {
    "_padManager",
    "_mcUtilCtrl",
    "_isMakeFileOK",
    "_select",
};
static igMetaField **g_beNDMWTitle2_fieldHandles[] = {
    &g_beNDMWTitle2_padManagerMetaField,
    &g_beNDMWTitle2_mcUtilCtrlMetaField,
    &g_beNDMWTitle2_isMakeFileOKMetaField,
    &g_beNDMWTitle2_selectMetaField,
};
static int g_beNDMWTitle2_fieldOffsets[] = {
    32,
    36,
    40,
    44,
};

void beNDMWTitle2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWTitle2_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWTitle2_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003c5200();
    igMetaObject_NameFields(temp_s0, g_beNDMWTitle2_fieldTable, g_beNDMWTitle2_fieldHandles, g_beNDMWTitle2_fieldOffsets, temp_s2);
}

