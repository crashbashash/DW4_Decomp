void FUN_00363210(int arg0) {
    FUN_00363480();
    igMetaObject_CreateInstance(*(int *)0x589790, arg0);
}

int FUN_00363250(void) {
    if (((int *)DAT_00589790)[0] == 0) {
        ((int *)DAT_00589790)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589790)[0];
}

void *FUN_003632a0(void) {
    struct G *g = DAT_00589790[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00363480();
    }
    return DAT_00589790[0];
}

int beDemoManager_GetVTable(void) {
    struct Obj_3632f0 o;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_0053a460[0];
    o.f8 = 0;
    o.f24 = 0;
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053a460[0];
    FUN_00363400((struct R **)&o.f28, (short)(-1));
    FUN_00363380((ObjectRefWord *)&o.f24, -1);
    FUN_00231030(&o, 0);
    return r;
}

ObjectRefWord *FUN_00363380(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_00363400(struct R **arg0, short arg1) {
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

void FUN_00363480(void)
{
    igMetaObject_RunStaticInit(beDemoManager_Register);
}

void *beDemoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beDemoManager_GetMetaObject,
        beDemoManager_className,
        0x24, /* instance size */
        beDemoManager_GetVTable,
        beDemoManager_InitFields,
        0, /* extra callback item */
        g_beDemoManager_callbackList /* callback list */
    );
}

void beDemoManager_GetMetaObject(void)
{
    FUN_003632a0();
}

void beDemoManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589790)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6fc0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0035b770();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00363800();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_00363630();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6fe0[0], &DAT_004c7000[0], &DAT_004c7020[0], temp_s2);
}

