void *FUN_0034b6b0(void) {
    igMetaObject *g = g_bePoint01Info_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034b810();
    }
    return g_bePoint01Info_metaObject[0];
}

int bePoint01Info_GetVTable(void) {
    struct Obj obj;
    int temp_s1;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_005387a0[0]);
    obj.f1C = 0;
    obj.f20 = 0;
    temp_s1 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_005387a0[0]);
    FUN_0034b790((ObjectRefWord *)&obj.f20, -1);
    FUN_00343260((ObjectRefWord *)&obj.f1C, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s1;
}

ObjectRefWord *FUN_0034b790(ObjectRefWord *self,int delete_storage) {
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

void FUN_0034b810(void)
{
    igMetaObject_RunStaticInit(bePoint01Info_Register);
}

void *bePoint01Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePoint01Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        bePoint01Info_GetMetaObject,
        bePoint01Info_className,
        0x24, /* instance size */
        bePoint01Info_GetVTable,
        bePoint01Info_InitFields,
        0, /* extra callback item */
        g_bePoint01Info_callbackList /* callback list */
    );
}

void bePoint01Info_GetMetaObject(void)
{
    FUN_0034b6b0();
}

void bePoint01Info_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_bePoint01Info_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_bePoint01Info_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196930();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0035ee00();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_bePoint01Info_fieldTable[0], &DAT_004c4538[0], &DAT_004c4540[0], temp_s2);
}

int FUN_0034b980(void) {
    if (DAT_00588490[0] == 0) {
        DAT_00588490[0] = igMetaEnum_Create(&text_MsgAction[0], &DAT_004c4550[0], &DAT_004c4570[0], 7);
    }
    return DAT_00588490[0];
}

