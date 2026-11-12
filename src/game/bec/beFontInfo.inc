void *FUN_00360e90(void) {
    struct G *g = DAT_005895e8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00360fe0();
    }
    return DAT_005895e8[0];
}

int beFontInfo_GetVTable(void) {
    union U_360ee0 u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_00535bd0[0];
    ps = &u.b[28];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00535bd0[0];
    FUN_00360f60((ObjectRefWord *)ps, -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return temp_s0;
}

ObjectRefWord *FUN_00360f60(ObjectRefWord *self,int delete_storage) {
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

void FUN_00360fe0(void)
{
    igMetaObject_RunStaticInit(beFontInfo_Register);
}

void *beFontInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beFontInfo_GetMetaObject,
        beFontInfo_className,
        0x20, /* instance size */
        beFontInfo_GetVTable,
        beFontInfo_InitFields,
        0, /* extra callback item */
        g_beFontInfo_callbackList /* callback list */
    );
}

void beFontInfo_GetMetaObject(void)
{
    FUN_00360e90();
}

void beFontInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005895e8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6bc0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00361360();
    igMetaObject_NameFields(temp_s0, &DAT_004c6bc8[0], &DAT_004c6bd0[0], &DAT_004c6bd8[0], temp_s2);
}

