void beNDMWTitle2_CreateInstance(int arg0) {
    FUN_003b2a90();
    igMetaObject_CreateInstance(*(int *)0x58AB10, arg0);
}

igMetaObject *FUN_003b28e0(void) {
    if (g_beNDMWTitle2_metaObject[0] == 0) {
        g_beNDMWTitle2_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWTitle2_metaObject[0];
}

void *FUN_003b2930(void) {
    unsigned char b;
    if (((void * *)g_beNDMWTitle2_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)g_beNDMWTitle2_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b2a90();
done:
    return ((void * *)g_beNDMWTitle2_metaObject)[0];
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

void *beNDMWTitle2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWTitle2_GetMetaObject,
        beNDMWTitle2_className,
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

void beNDMWTitle2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWTitle2_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9730[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003c5200();
    igMetaObject_NameFields(temp_s0, &DAT_004c9740[0], &DAT_004c9750[0], &DAT_004c9760[0], temp_s2);
}

