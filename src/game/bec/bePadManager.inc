void bePadManager_CreateInstance(int arg0) {
    FUN_0034cb30();
    igMetaObject_CreateInstance(*(int *)0x588518, arg0);
}

igMetaObject *FUN_0034c8e0(void) {
    if (g_bePadManager_metaObject[0] == 0) {
        g_bePadManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_bePadManager_metaObject[0];
}

void *FUN_0034c930(void) {
    igMetaObject *g = g_bePadManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034cb30();
    }
    return g_bePadManager_metaObject[0];
}

int bePadManager_GetVTable(void) {
    struct Obj_34c980 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053b030[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053b030[0];
    FUN_0034cab0((struct R **)&obj.w6, (short)(-1));
    FUN_0034ca30((ObjectRefWord *)&obj.w5, -1);
    FUN_0033dc20((void **)&obj.w4, (short)(-1));
    FUN_00231030(&obj, 0);
    return t;
}

ObjectRefWord *FUN_0034ca30(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_0034cab0(struct R **arg0, short arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0034cb30(void)
{
    igMetaObject_RunStaticInit(bePadManager_Register);
}

void *bePadManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePadManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        bePadManager_GetMetaObject,
        bePadManager_className,
        0x20, /* instance size */
        bePadManager_GetVTable,
        bePadManager_InitFields,
        0, /* extra callback item */
        g_bePadManager_callbackList /* callback list */
    );
}

void bePadManager_GetMetaObject(void)
{
    FUN_0034c930();
}

void bePadManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_bePadManager_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c46c0[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00342ce0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0034ccc0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0035d070();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c46e0[0], &DAT_004c4700[0], &DAT_004c4720[0], temp_s2);
}

