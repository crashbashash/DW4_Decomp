void *FUN_00343190(void) {
    igMetaObject *g = g_beSwitchCtrlInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003432e0();
    }
    return g_beSwitchCtrlInfo_metaObject[0];
}

int beSwitchCtrlInfo_GetVTable(void) {
    struct Obj_3431e0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_00539490[0];
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539490[0];
    FUN_00343260((ObjectRefWord *)(&obj.w[6]), -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return r;
}

ObjectRefWord *FUN_00343260(ObjectRefWord *self,int delete_storage) {
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

void FUN_003432e0(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrlInfo_Register);
}

void *beSwitchCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSwitchCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSwitchCtrlInfo_GetMetaObject,
        beSwitchCtrlInfo_className,
        0x20, /* instance size */
        beSwitchCtrlInfo_GetVTable,
        beSwitchCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beSwitchCtrlInfo_callbackList /* callback list */
    );
}

void beSwitchCtrlInfo_GetMetaObject(void)
{
    FUN_00343190();
}

void beSwitchCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSwitchCtrlInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSwitchCtrlInfo_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    igMetaObject_NameFields(temp_s0, &g_beSwitchCtrlInfo_fieldTable[0], &DAT_004c3770[0], &DAT_004c3778[0], temp_s2);
}

int beSwitchCtrl_GetMessageEnum(void) {
    if (DAT_00587df0[0] == 0) {
        DAT_00587df0[0] = igMetaEnum_Create(&MsgAction[0], &DAT_004c3780[0], &DAT_004c3788[0], 2);
    }
    return DAT_00587df0[0];
}

