void *FUN_0035c420(void) {
    igMetaObject *g = g_beLayerInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035c570();
    }
    return g_beLayerInfo_metaObject[0];
}

int beLayerInfo_GetVTable(void) {
    union U_35c470 u;
    int t;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_00536610[0];
    ps = &u.b[28];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00536610[0];
    FUN_0035c4f0((ObjectRefWord *)ps, -1);
    FUN_0033ec80((struct S_33ec80 *)u.b, (short)0);
    return t;
}

ObjectRefWord *FUN_0035c4f0(ObjectRefWord *self,int delete_storage) {
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

void FUN_0035c570(void)
{
    igMetaObject_RunStaticInit(beLayerInfo_Register);
}

void *beLayerInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLayerInfo_GetMetaObject,
        beLayerInfo_className,
        0x20, /* instance size */
        beLayerInfo_GetVTable,
        beLayerInfo_InitFields,
        0, /* extra callback item */
        g_beLayerInfo_callbackList /* callback list */
    );
}

void beLayerInfo_GetMetaObject(void)
{
    FUN_0035c420();
}

void beLayerInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLayerInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6380[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0035c6c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c6388[0], &DAT_004c6390[0], &DAT_004c6398[0], temp_s2);
}

