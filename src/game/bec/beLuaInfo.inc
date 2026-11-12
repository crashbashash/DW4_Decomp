igMetaObject *FUN_0035ad10(void)
{
    igMetaObject *g = DAT_005891c0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0035ae60();
    return DAT_005891c0[0];
}

int beLuaInfo_GetVTable(void) {
    struct Obj_35ad60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_00536960[0];
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536960[0];
    FUN_0035ade0((ObjectRefWord *)&obj.w7, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

ObjectRefWord *FUN_0035ade0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_0035ae60(void)
{
    igMetaObject_RunStaticInit(beLuaInfo_Register);
}

void *beLuaInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLuaInfo_GetMetaObject,
        beLuaInfo_className,
        0x20, /* instance size */
        beLuaInfo_GetVTable,
        beLuaInfo_InitFields,
        0, /* extra callback item */
        g_beLuaInfo_callbackList /* callback list */
    );
}

void beLuaInfo_GetMetaObject(void)
{
    FUN_0035ad10();
}

void beLuaInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005891c0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6260[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035afc0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6268[0], &DAT_004c6270[0], &DAT_004c6278[0], temp_s2);
}

