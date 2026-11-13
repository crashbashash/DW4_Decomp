void *FUN_00344b40(void) {
    bool ok;
    if (g_beShadow01Info_metaObject[0] == 0) goto make;
    ok = !!(g_beShadow01Info_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00344cc0();
done:;
    return g_beShadow01Info_metaObject[0];
}

int beShadow01Info_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_00539140[0];
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[36] = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00539140[0];
    FUN_00344c40((ObjectRefWord *)(&u.b[36]), -1);
    FUN_00198210(&u.b[32], -1);
    FUN_00198210(&u.b[28], -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return t;
}

ObjectRefWord *FUN_00344c40(ObjectRefWord *self,int delete_storage) {
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

void FUN_00344cc0(void)
{
    igMetaObject_RunStaticInit(beShadow01Info_Register);
}

void *beShadow01Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beShadow01Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beShadow01Info_GetMetaObject,
        beShadow01Info_className,
        0x28, /* instance size */
        beShadow01Info_GetVTable,
        beShadow01Info_InitFields,
        0, /* extra callback item */
        g_beShadow01Info_callbackList /* callback list */
    );
}

void beShadow01Info_GetMetaObject(void)
{
    FUN_00344b40();
}

void beShadow01Info_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beShadow01Info_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beShadow01Info_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019cd50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0019cd50();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0019b440();
    igMetaObject_NameFields(temp_s0, &g_beShadow01Info_fieldTable[0], &DAT_004c3a20[0], &DAT_004c3a30[0], temp_s2);
}

