int FUN_001506b0(void) {
    if (DAT_0055ff78[0] == 0) {
        DAT_0055ff78[0] = igMetaEnum_Create(&IG_GFX_CLEARRENDERDESTINATION_TY[0], &DAT_00489230[0], &DAT_00489238[0], 2);
    }
    return DAT_0055ff78[0];
}

int FUN_00150710(void) {
    if (DAT_0055ff80[0] == 0) {
        DAT_0055ff80[0] = igMetaEnum_Create(&IG_GFX_CLIPPING_TYPE_PSX2[0], &DAT_00489240[0], &DAT_00489248[0], 2);
    }
    return DAT_0055ff80[0];
}

igMetaObject *FUN_00150770(void) {
    if (g_igPsx2VisualContext_metaObject[0] == 0) {
        g_igPsx2VisualContext_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igPsx2VisualContext_metaObject[0];
}

igMetaObject *igPsx2VisualContext_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VisualContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001511a0();
    return g_igPsx2VisualContext_metaObject[0];
}

int igPsx2VisualContext_GetVTable(void) {
    struct VTableProbe s;
    char *p;
    char *q;
    int r;
    p = (char *)&s;
    FUN_001510e0((igVisualContext *)p);
    s.vt = &DAT_00525870[0];
    q = (char *)&s + 332;
    FUN_001510d0((int *)q);
    FUN_001510a0((int)((char *)&s + 772));
    FUN_00151090((int)(p + 876));
    FUN_00151080((int *)(p + 940));
    FUN_00151070((int *)(p + 944));
    FUN_00151060((int *)(p + 948));
    FUN_00151050((int *)(p + 972));
    FUN_00151050((int *)(p + 976));
    FUN_00151050((int *)(p + 980));
    FUN_00151050((int *)(p + 984));
    FUN_00151050((int *)(p + 988));
    FUN_00151050((int *)(p + 992));
    FUN_00151050((int *)(p + 996));
    FUN_00151050((int *)(p + 1000));
    FUN_00151050((int *)(p + 1004));
    FUN_00151050((int *)(p + 1008));
    FUN_00151050((int *)(p + 1012));
    FUN_00151050((int *)(p + 1016));
    FUN_00151090((int)(p + 1312));
    FUN_00151030(p + 1348);
    FUN_00151090((int)(p + 1432));
    r = *(int *)((char *)&s + *(int *)((char *)(g_objectSystem[0]) + 916));
    s.vt = &DAT_00525870[0];
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1016), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1012), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1008), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1004), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 1000), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 996), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 992), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 988), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 984), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 980), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 976), -1);
    FUN_00150fb0((ObjectRefWord *)((char *)&s + 972), -1);
    FUN_00137260((char *)&s + 948, -1);
    FUN_001372e0((char *)&s + 944, -1);
    FUN_00150f30((O_1506b0 *)((char *)&s + 940), -1);
    ObjectRef_Destruct_00150eb0((ObjectRefWord *)q, -1);
    FUN_00150af0((Obj_1506b0 *)&s, 0);
    return r;
}

void **FUN_001509f0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_00150a70(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

Obj_1506b0 *FUN_00150af0(Obj_1506b0 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_00525e50;
        arg0->rel(&arg0->m308);
        arg0->rel(&arg0->m304);
        __destroy_arr((char *)arg0 + 240, (void *)&FUN_00137360, 4, 16);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m48);
        arg0->rel(&arg0->m44);
        arg0->rel(&arg0->m40);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        arg0->rel(&arg0->m28);
        arg0->rel(&arg0->m24);
        if (arg0) {
            arg0->vt = DAT_00530a10;
            arg0->rel(&arg0->m16);
            arg0->rel(&arg0->m8);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *ObjectRef_Destruct_00150eb0(ObjectRefWord *self,int delete_storage) {
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

O_1506b0 *FUN_00150f30(O_1506b0 *arg0, short arg1) {
    if (arg0) {
        S_temp_a0_1506b0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00150fb0(ObjectRefWord *self,int delete_storage) {
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

void *FUN_00151030(void *arg0) {
    *(int *)((char *)(arg0) + 20) = 0;
    *(char *)((char *)(arg0) + 0) = 0;
    *(char *)((char *)(arg0) + 1) = 0;
    *(int *)((char *)(arg0) + 12) = 0;
    *(int *)((char *)(arg0) + 16) = 0;
    return arg0;
}

int *FUN_00151050(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00151060(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00151070(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00151080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int FUN_00151090(int a) { return a; }

int FUN_001510a0(int arg0) {
    igMatrix44f_SetIdentity((float *)arg0);
    return arg0;
}

int *FUN_001510d0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_001510e0(igVisualContext *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_00530a10[0]);
    arg0->_pExtList = 0;
    arg0->_pExtInstances = 0;
    arg0->_vtable = (int)(&DAT_00525e50[0]);
    arg0->_driverDataMemoryPool = 0;
    arg0->_vertexMemoryPool = 0;
    arg0->_internalMemoryPool = 0;
    arg0->_temporaryMemoryPool = 0;
    arg0->_imageMemoryPool = 0;
    arg0->_textureMemoryPool = 0;
    arg0->_statisticsMemoryPool = 0;
    arg0->_listMemoryPool = 0;
    arg0->_timer = 0;
    igMatrix44f_SetIdentity(&arg0->_viewMatrixHint[0]);
    igMatrix44f_SetIdentity(&arg0->_viewMatrixInverse[0]);
    __construct_array(&arg0->_vertexArray2[0], FUN_00151190, &FUN_00137360, 4, 0x10);
    arg0->_customStates = 0;
    arg0->_customFields = 0;
    return arg0;
}

int *FUN_00151190(int *arg0) {
    *arg0 = 0;
    return arg0;
}

void FUN_001511a0(void)
{
    igMetaObject_RunStaticInit(igPsx2VisualContext_Register);
}

void igPsx2VisualContext_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2VisualContext_metaObject,
        igVisualContext_Register,
        FUN_00151230,
        thunk_igPsx2VisualContext_GetMetaObject,
        igPsx2VisualContext_className,
        0x618, /* instance size */
        igPsx2VisualContext_GetVTable,
        &igPsx2VisualContext_InitFields,
        0, /* extra callback item */
        g_igPsx2VisualContext_callbackList /* callback list */
    );
}

igMetaObject *FUN_00151230(void) {
    return g_igVisualContext_metaObject[0];
}

void igPsx2VisualContext_InitFields(void) {
    igMetaField *temp_a0;
    igMetaField *temp_a0_2;
    igMetaField *temp_a0_3;
    igMetaField *temp_s2;
    igMetaField *temp_s2_10;
    igMetaField *temp_s2_11;
    igMetaField *temp_s2_12;
    igMetaField *temp_s2_13;
    igMetaField *temp_s2_14;
    igMetaField *temp_s2_15;
    igMetaField *temp_s2_16;
    igMetaField *temp_s2_17;
    igMetaField *temp_s2_18;
    igMetaField *temp_s2_19;
    igMetaField *temp_s2_20;
    igMetaField *temp_s2_21;
    igMetaField *temp_s2_2;
    igMetaField *temp_s2_3;
    igMetaField *temp_s2_4;
    igMetaField *temp_s2_5;
    igMetaField *temp_s2_6;
    igMetaField *temp_s2_7;
    igMetaField *temp_s2_8;
    igMetaField *temp_s2_9;
    igMetaField *temp_v0;
    igMetaField *temp_v0_10;
    igMetaField *temp_v0_11;
    igMetaField *temp_v0_12;
    igMetaField *temp_v0_13;
    igMetaField *temp_v0_14;
    igMetaField *temp_v0_15;
    igMetaField *temp_v0_16;
    igMetaField *temp_v0_17;
    igMetaField *temp_v0_18;
    igMetaField *temp_v0_19;
    igMetaField *temp_v0_20;
    igMetaField *temp_v0_21;
    igMetaField *temp_v0_22;
    igMetaField *temp_v0_23;
    igMetaField *temp_v0_24;
    igMetaField *temp_v0_25;
    igMetaField *temp_v0_26;
    igMetaField *temp_v0_27;
    igMetaField *temp_v0_28;
    igMetaField *temp_v0_29;
    igMetaField *temp_v0_2;
    igMetaField *temp_v0_30;
    igMetaField *temp_v0_31;
    igMetaField *temp_v0_32;
    igMetaField *temp_v0_33;
    igMetaField *temp_v0_34;
    igMetaField *temp_v0_35;
    igMetaField *temp_v0_36;
    igMetaField *temp_v0_3;
    igMetaField *temp_v0_4;
    igMetaField *temp_v0_5;
    igMetaField *temp_v0_6;
    igMetaField *temp_v0_7;
    igMetaField *temp_v0_8;
    igMetaField *temp_v0_9;
    int sp60[4];
    int sp50[4];
    float sp40[4];
    int base;
    void *meta;

    meta = (void *)(g_igPsx2VisualContext_metaObject[0]);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, &g_igPsx2VisualContext_ctorTable[0], 0x92);
    temp_s2 = igMetaObject_GetFieldAt(meta, base + 4);
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 5), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 7), -1);
    temp_v0 = igMetaObject_GetFieldAt(meta, base + 8);
    ((igIntArrayMetaField *)temp_v0)->_num = 0x10;
    FUN_002ea290(temp_v0, -1);
    temp_v0_2 = igMetaObject_GetFieldAt(meta, base + 9);
    ((igIntArrayMetaField *)temp_v0_2)->_num = 0x10;
    FUN_002ea290(temp_v0_2, -1);
    temp_v0_3 = igMetaObject_GetFieldAt(meta, base + 0xA);
    ((igIntArrayMetaField *)temp_v0_3)->_num = 0x10;
    FUN_002ea290(temp_v0_3, -1);
    temp_v0_4 = igMetaObject_GetFieldAt(meta, base + 0xB);
    ((igBoolArrayMetaField *)temp_v0_4)->_num = 0x10;
    FUN_002d35d0(temp_v0_4, 1);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0xC), 1);
    { igMetaField *q = igMetaObject_GetFieldAt(meta, base + 0xE); ((igBoolArrayMetaField *)q)->_num = 0x10; }
    temp_v0_5 = igMetaObject_GetFieldAt(meta, base + 0xF);
    ((igEnumArrayMetaField *)temp_v0_5)->_num = 0x10;
    FUN_002dc730(temp_v0_5, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_5)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_6 = igMetaObject_GetFieldAt(meta, base + 0x10);
    ((igEnumArrayMetaField *)temp_v0_6)->_num = 0x10;
    FUN_002dc730(temp_v0_6, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_6)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    { igMetaField *q = igMetaObject_GetFieldAt(meta, base + 0x11); ((igIntArrayMetaField *)q)->_num = 0x10; }
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x13), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x14), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x15), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x16), -1);
    temp_s2_2 = igMetaObject_GetFieldAt(meta, base + 0x17);
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = igIntMetaField_GetDefaultDescriptor();
    temp_s2_3 = igMetaObject_GetFieldAt(meta, base + 0x18);
    ((igMemoryRefMetaField *)temp_s2_3)->_memType = igIntMetaField_GetDefaultDescriptor();
    temp_s2_4 = igMetaObject_GetFieldAt(meta, base + 0x19);
    ((igMemoryRefMetaField *)temp_s2_4)->_memType = igIntMetaField_GetDefaultDescriptor();
    temp_s2_5 = igMetaObject_GetFieldAt(meta, base + 0x1A);
    ((igMemoryRefMetaField *)temp_s2_5)->_memType = igIntMetaField_GetDefaultDescriptor();
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x1C), -1);
    temp_a0 = igMetaObject_GetFieldAt(meta, base + 0x1D);
    sp60[0] = 0;
    sp60[1] = 0;
    sp60[2] = 0;
    sp60[3] = 0;
    FUN_0018e670(temp_a0, sp60);
    FUN_002e3810(igMetaObject_GetFieldAt(meta, base + 0x1E), 1.0f);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x26), 0x280);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x27), 0x1C0);
    FUN_002e3810(igMetaObject_GetFieldAt(meta, base + 0x28), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(meta, base + 0x29), 1.0f);
    temp_s2_6 = igMetaObject_GetFieldAt(meta, base + 0x2A);
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_00152370();
    temp_s2_7 = igMetaObject_GetFieldAt(meta, base + 0x2B);
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_0014d7f0();
    temp_s2_8 = igMetaObject_GetFieldAt(meta, base + 0x2C);
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)FUN_0014c030();
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x30), -1);
    temp_s2_9 = igMetaObject_GetFieldAt(meta, base + 0x32);
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = igMetaObject_GetFieldAt(meta, base + 0x33);
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = igMetaObject_GetFieldAt(meta, base + 0x34);
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = igMetaObject_GetFieldAt(meta, base + 0x35);
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = igMetaObject_GetFieldAt(meta, base + 0x36);
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = igMetaObject_GetFieldAt(meta, base + 0x37);
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = igMetaObject_GetFieldAt(meta, base + 0x38);
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = igMetaObject_GetFieldAt(meta, base + 0x39);
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_16)->_construct = 1;
    temp_s2_17 = igMetaObject_GetFieldAt(meta, base + 0x3A);
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_17)->_construct = 1;
    temp_s2_18 = igMetaObject_GetFieldAt(meta, base + 0x3B);
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_18)->_construct = 1;
    temp_s2_19 = igMetaObject_GetFieldAt(meta, base + 0x3C);
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_19)->_construct = 1;
    temp_s2_20 = igMetaObject_GetFieldAt(meta, base + 0x3D);
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2_20)->_construct = 1;
    temp_v0_7 = igMetaObject_GetFieldAt(meta, base + 0x41);
    FUN_002dc7a0(temp_v0_7, &DAT_00489ba8[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_7)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_8 = igMetaObject_GetFieldAt(meta, base + 0x44);
    ((igEnumArrayMetaField *)temp_v0_8)->_num = 0x10;
    FUN_002dc730(temp_v0_8, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_8)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_9 = igMetaObject_GetFieldAt(meta, base + 0x45);
    ((igEnumArrayMetaField *)temp_v0_9)->_num = 0x10;
    FUN_002dc730(temp_v0_9, 0);
    *(int (**)())&((igEnumArrayMetaField *)temp_v0_9)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    { igMetaField *q = igMetaObject_GetFieldAt(meta, base + 0x46); ((igIntArrayMetaField *)q)->_num = 0x10; }
    temp_s2_21 = igMetaObject_GetFieldAt(meta, base + 0x48);
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = (int)FUN_00152e80();
    ((igObjectRefMetaField *)temp_s2_21)->_refCounted = 0;
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x4B), 0x280);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 0x4C), 0x1C0);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x4D), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x4E), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x4F), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x50), 1);
    temp_v0_10 = igMetaObject_GetFieldAt(meta, base + 0x51);
    FUN_002dc7a0(temp_v0_10, &DAT_00489bb0[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_10)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_11 = igMetaObject_GetFieldAt(meta, base + 0x52);
    FUN_002dc7a0(temp_v0_11, &DAT_00489bb8[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_11)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_12 = igMetaObject_GetFieldAt(meta, base + 0x55);
    FUN_002dc7a0(temp_v0_12, &DAT_00489bc0[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_12)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x56), 1);
    temp_v0_13 = igMetaObject_GetFieldAt(meta, base + 0x58);
    FUN_002dc7a0(temp_v0_13, &DAT_00489bc8[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_13)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_14 = igMetaObject_GetFieldAt(meta, base + 0x5A);
    FUN_002dc7a0(temp_v0_14, &DAT_00489bd0[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_14)->_getMetaEnumFunction = FUN_00149500;
    temp_v0_15 = igMetaObject_GetFieldAt(meta, base + 0x5B);
    FUN_002dc7a0(temp_v0_15, &DAT_00489bd8[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_15)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_16 = igMetaObject_GetFieldAt(meta, base + 0x5C);
    FUN_002dc7a0(temp_v0_16, &DAT_00489be0[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_16)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_17 = igMetaObject_GetFieldAt(meta, base + 0x5F);
    FUN_002dc7a0(temp_v0_17, &DAT_00489be8[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_17)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_a0_2 = igMetaObject_GetFieldAt(meta, base + 0x60);
    sp50[0] = 0;
    sp50[1] = 0;
    sp50[2] = 0;
    sp50[3] = 0;
    FUN_0018e670(temp_a0_2, sp50);
    FUN_002e3810(igMetaObject_GetFieldAt(meta, base + 0x61), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(meta, base + 0x62), 10000.0f);
    { igMetaField *q = igMetaObject_GetFieldAt(meta, base + 0x66); ((igMetaField *)q)->_size = 0x18; }
    temp_v0_18 = igMetaObject_GetFieldAt(meta, base + 0x69);
    FUN_002dc7a0(temp_v0_18, &DAT_00489bf0[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_18)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x6A), 1);
    temp_v0_19 = igMetaObject_GetFieldAt(meta, base + 0x6B);
    FUN_002dc7a0(temp_v0_19, &DAT_00489bf8[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_19)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_20 = igMetaObject_GetFieldAt(meta, base + 0x6C);
    FUN_002dc7a0(temp_v0_20, &DAT_00489c00[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_20)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_21 = igMetaObject_GetFieldAt(meta, base + 0x6F);
    FUN_002dc7a0(temp_v0_21, &DAT_00489c08[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_21)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_22 = igMetaObject_GetFieldAt(meta, base + 0x72);
    FUN_002dc7a0(temp_v0_22, &DAT_00489c10[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_22)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_23 = igMetaObject_GetFieldAt(meta, base + 0x76);
    FUN_002dc7a0(temp_v0_23, &DAT_00489c18[0]);
    *(int (**)())&((igEnumMetaField *)temp_v0_23)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_a0_3 = igMetaObject_GetFieldAt(meta, base + 0x77);
    sp40[3] = 1.0f;
    sp40[0] = 0.501960754f;
    sp40[1] = 0.501960754f;
    sp40[2] = 0.501960754f;
    FUN_0018e670(temp_a0_3, sp40);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x79), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 0x7A), 1);
    temp_v0_24 = igMetaObject_GetFieldAt(meta, base + 0x7B);
    FUN_002d3890(temp_v0_24, 1);
    ((igMetaField *)temp_v0_24)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x7C))->_persistent = 0;
    temp_v0_25 = igMetaObject_GetFieldAt(meta, base + 0x7D);
    FUN_002d3890(temp_v0_25, 1);
    ((igMetaField *)temp_v0_25)->_persistent = 0;
    temp_v0_26 = igMetaObject_GetFieldAt(meta, base + 0x7E);
    FUN_002dc7a0(temp_v0_26, &DAT_00489c20[0]);
    ((igMetaField *)temp_v0_26)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_26)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_27 = igMetaObject_GetFieldAt(meta, base + 0x7F);
    FUN_002dc7a0(temp_v0_27, &DAT_00489c28[0]);
    ((igMetaField *)temp_v0_27)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_27)->_getMetaEnumFunction = (int (*)())FUN_002d1870;
    temp_v0_28 = igMetaObject_GetFieldAt(meta, base + 0x80);
    FUN_002d3890(temp_v0_28, 1);
    ((igMetaField *)temp_v0_28)->_persistent = 0;
    temp_v0_29 = igMetaObject_GetFieldAt(meta, base + 0x81);
    FUN_002ea4b0(temp_v0_29, 0x10);
    ((igMetaField *)temp_v0_29)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x82))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x83))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x84))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x85))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x86))->_persistent = 0;
    temp_v0_30 = igMetaObject_GetFieldAt(meta, base + 0x87);
    FUN_002dc7a0(temp_v0_30, &DAT_00489c30[0]);
    ((igMetaField *)temp_v0_30)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_30)->_getMetaEnumFunction = FUN_00149920;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x88))->_persistent = 0;
    temp_v0_31 = igMetaObject_GetFieldAt(meta, base + 0x89);
    FUN_002dc7a0(temp_v0_31, &DAT_00489c38[0]);
    ((igMetaField *)temp_v0_31)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_31)->_getMetaEnumFunction = FUN_00149980;
    temp_v0_32 = igMetaObject_GetFieldAt(meta, base + 0x8A);
    FUN_002dc7a0(temp_v0_32, &DAT_00489c40[0]);
    ((igMetaField *)temp_v0_32)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_32)->_getMetaEnumFunction = FUN_00149980;
    temp_v0_33 = igMetaObject_GetFieldAt(meta, base + 0x8B);
    FUN_002dc7a0(temp_v0_33, &DAT_00489c48[0]);
    ((igMetaField *)temp_v0_33)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_33)->_getMetaEnumFunction = FUN_00149800;
    temp_v0_34 = igMetaObject_GetFieldAt(meta, base + 0x8C);
    FUN_002dc7a0(temp_v0_34, &DAT_00489c50[0]);
    ((igMetaField *)temp_v0_34)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_34)->_getMetaEnumFunction = FUN_00150710;
    temp_v0_35 = igMetaObject_GetFieldAt(meta, base + 0x8D);
    FUN_002dc7a0(temp_v0_35, &DAT_00489c58[0]);
    ((igMetaField *)temp_v0_35)->_persistent = 0;
    *(int (**)())&((igEnumMetaField *)temp_v0_35)->_getMetaEnumFunction = FUN_001506b0;
    temp_v0_36 = igMetaObject_GetFieldAt(meta, base + 0x8E);
    ((igUnsignedIntArrayMetaField *)temp_v0_36)->_num = 3;
    ((igMetaField *)temp_v0_36)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x8F))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x90))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 0x91))->_persistent = 0;
    igMetaObject_NameFields(meta, &g_igPsx2VisualContext_fieldTable[0], &DAT_00489710[0], &DAT_00489960[0], base);
    *(int *)((char *)(g_igPsx2VisualContext_metaObject[0]) + 64) = (int)(&thunk_igVisualContext_GetMetaObject);
}

