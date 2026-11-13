void beNDMWStatusCtrlDisk_Create(int arg0) {
    FUN_003b9c20();
    igMetaObject_CreateInstance(*(int *)0x58AEC0, arg0);
}

igMetaObject *FUN_003b9a90(void)
{
    igMetaObject *g = g_beNDMWStatusCtrlDisk_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b9c20();
    return g_beNDMWStatusCtrlDisk_metaObject[0];
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
    ObjectRef_Destruct_00150eb0(&obj.w[21], -1);
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

void *beNDMWStatusCtrlDisk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlDisk_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlDisk_GetMetaObject,
        beNDMWStatusCtrlDisk_className,
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

void beNDMWStatusCtrlDisk_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrlDisk_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9dd0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003c9130();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_003c85f0();
    igMetaObject_NameFields(temp_s0, &DAT_004c9df0[0], &DAT_004c9e10[0], &DAT_004c9e30[0], temp_s2);
}

