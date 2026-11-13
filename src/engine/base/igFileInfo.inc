igMetaObject *FUN_00228e60(void) {
    if (g_igFileInfo_metaObject[0] == 0) {
        g_igFileInfo_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igFileInfo_metaObject[0];
}

igMetaObject *igFileInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002290c0();
    return g_igFileInfo_metaObject[0];
}

int igFileInfo_GetVTable(void) {
    struct Obj_8 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_0052c170[0];
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052c170[0];
    FUN_00229040((R **)&obj.w[5], -1);
    FUN_00228fc0((ObjectRefWord *)&obj.w[4], -1);
    FUN_001d35d0(&obj.w[3], -1);
    FUN_001d36d0(&obj.w[2], -1);
    FUN_00131bc0(&obj, 0);
    return r;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_00228fc0(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_00229040(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_002290c0(void)
{
    igMetaObject_RunStaticInit(igFileInfo_Register);
}

void igFileInfo_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileInfo_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFileInfo_GetMetaObject,
        igFileInfo_className,
        0x1C, /* instance size */
        igFileInfo_GetVTable,
        &igFileInfo_InitFields,
        0, /* extra callback item */
        g_igFileInfo_callbackList /* callback list */
    );
}

void thunk_igFileInfo_GetMetaObject(void) {
    igFileInfo_GetMetaObject();
}

void igFileInfo_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igFileInfo_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igFileInfo_ctorTable[0], 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002c7300();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00228cf0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002c3820();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_igFileInfo_fieldTable[0], &DAT_00497f50[0], &DAT_00497f60[0], temp_s0);
}

int *FUN_00229260(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00229270(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

