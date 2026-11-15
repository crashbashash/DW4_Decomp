igMetaObject *g_beNDMWStatusCtrlDisk_metaObject;
igMetaField *g_beNDMWStatusCtrlDisk_cursorMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_playerNoListMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_receiptMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_diskListMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_sendDiskMetaField;
igMetaField *g_beNDMWStatusCtrlDisk_sendMaxMetaField;

void beNDMWStatusCtrlDisk_Create(int arg0) {
    FUN_003b9c20();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlDisk_metaObject, arg0);
}

igMetaObject *FUN_003b9a90(void)
{
    igMetaObject *g = g_beNDMWStatusCtrlDisk_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b9c20();
    return g_beNDMWStatusCtrlDisk_metaObject;
}

int beNDMWStatusCtrlDisk_GetVTable(void) {
    struct Obj_3b9ae0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.vt = &DAT_0053edb0[0];
    obj.w[21] = 0;
    obj.w[23] = 0;
    obj.w[24] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053edb0[0];
    FUN_003b9ba0((ObjectRefWord *)(&obj.w[24]), -1);
    FUN_003b6090((void **)(&obj.w[23]), (long long)(-1));
    igSmartPointer_igIntList_Destruct(&obj.w[21], -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)((int *)&obj), (long long)0);
    return t;
}

ObjectRefWord *FUN_003b9ba0(ObjectRefWord *self,int delete_storage) {
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

void FUN_003b9c20(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlDisk_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlDisk_callbackList[] = { igIntList_EnsureRegistered, FUN_003c9210, FUN_003c86d0, 0 };

void *beNDMWStatusCtrlDisk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlDisk_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlDisk_GetMetaObject,
        "beNDMWStatusCtrlDisk",
        0x6c, /* instance size */
        beNDMWStatusCtrlDisk_GetVTable,
        beNDMWStatusCtrlDisk_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlDisk_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlDisk_GetMetaObject(void)
{
    FUN_003b9a90();
}

static FieldFactory g_beNDMWStatusCtrlDisk_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWStatusCtrlDisk_fieldTable[] = {
    "_cursor",
    "_playerNoList",
    "_receipt",
    "_diskList",
    "_sendDisk",
    "_sendMax",
};
static igMetaField **g_beNDMWStatusCtrlDisk_fieldHandles[] = {
    &g_beNDMWStatusCtrlDisk_cursorMetaField,
    &g_beNDMWStatusCtrlDisk_playerNoListMetaField,
    &g_beNDMWStatusCtrlDisk_receiptMetaField,
    &g_beNDMWStatusCtrlDisk_diskListMetaField,
    &g_beNDMWStatusCtrlDisk_sendDiskMetaField,
    &g_beNDMWStatusCtrlDisk_sendMaxMetaField,
};
static int g_beNDMWStatusCtrlDisk_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
    104,
};

void beNDMWStatusCtrlDisk_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWStatusCtrlDisk_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWStatusCtrlDisk_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003c9130();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_003c85f0();
    igMetaObject_NameFields(temp_s0, g_beNDMWStatusCtrlDisk_fieldTable, g_beNDMWStatusCtrlDisk_fieldHandles, g_beNDMWStatusCtrlDisk_fieldOffsets, temp_s2);
}

