void beFont_CreateInstance(int arg0) {
    FUN_00362170();
    igMetaObject_CreateInstance(*(int *)0x589678, arg0);
}

igMetaObject *FUN_00361e90(void) {
    if (g_beFont_metaObject[0] == 0) {
        g_beFont_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beFont_metaObject[0];
}

void *FUN_00361ee0(void) {
    igMetaObject *g = g_beFont_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00362170();
    }
    return g_beFont_metaObject[0];
}

int beFont_GetVTable(void) {
    struct Obj_361f30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053a5c0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053a5c0[0];
    StringRef_Destruct_00130720(&obj.w16, -1);
    StringRef_Destruct_00130720(&obj.w15, -1);
    FUN_001489a0(&obj.w14, -1);
    FUN_001354b0(&obj.w13, -1);
    ObjectRef_Destruct_00150eb0(&obj.w12, -1);
    FUN_003620f0((void **)&obj.w11, (short)(-1));
    FUN_00362070((ObjectRefWord *)&obj.w9, -1);
    FUN_001d97f0(&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

ObjectRefWord *FUN_00362070(ObjectRefWord *self,int delete_storage) {
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

void **FUN_003620f0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00362170(void)
{
    igMetaObject_RunStaticInit(beFont_Register);
}

void *beFont_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFont_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beFont_GetMetaObject,
        beFont_className,
        0x48, /* instance size */
        beFont_GetVTable,
        beFont_InitFields,
        0, /* extra callback item */
        g_beFont_callbackList /* callback list */
    );
}

void beFont_GetMetaObject(void)
{
    FUN_00361ee0();
}

void beFont_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beFont_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c6d60[0], 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001a5d70();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00361750();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00362360();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002b9540();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c6d90[0], &DAT_004c6dc0[0], &DAT_004c6df0[0], temp_s0);
}

