igMetaObject *igIniShaderFactory_GetMetaObject(void)
{
    igMetaObject *g = g_igIniShaderFactory_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019efb0();
    return g_igIniShaderFactory_metaObject[0];
}

int igIniShaderFactory_GetVTable(void) {
    struct Obj_19ed70 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.vt = &DAT_00528d60[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00528d60[0];
    FUN_0014dd40(&obj.w14, -1);
    FUN_0014dd40(&obj.w13, -1);
    FUN_0019ef30((ObjectRefWord *)&obj.w12, -1);
    FUN_001509f0(&obj.w11, -1);
    StringRef_Destruct_00130720(&obj.w9, -1);
    FUN_0019eeb0((void * *)&obj.w8, -1);
    FUN_0019eeb0((void * *)&obj.w7, -1);
    StringRef_Destruct_00130720(&obj.w6, -1);
    FUN_00199330((struct T_199330 *)&obj, 0);
    return t;
}

void **FUN_0019eeb0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((void *)r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0019ef30(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_0019efb0(void)
{
    igMetaObject_RunStaticInit(igIniShaderFactory_Register);
}

void igIniShaderFactory_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIniShaderFactory_metaObject),
        igShaderFactory_Register,
        igShaderFactory_GetPublishedMetaObject,
        thunk_igIniShaderFactory_GetMetaObject,
        igIniShaderFactory_className,
        0x3C, /* instance size */
        igIniShaderFactory_GetVTable,
        &igIniShaderFactory_InitFields,
        0, /* extra callback item */
        g_igIniShaderFactory_callbackList /* callback list */
    );
}

void thunk_igIniShaderFactory_GetMetaObject(void) {
    igIniShaderFactory_GetMetaObject();
}

int FUN_0019f050(void) {
    return DAT_00561528[0];
}

void igIniShaderFactory_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_s1;

    temp_s1 = (void *)DAT_005619a8[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048bf20[0], 9);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002bcbb0();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002bb030();
    ((igObjectRefMetaField *)temp_s2_2)->_persistent = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002bb030();
    ((igObjectRefMetaField *)temp_s2_3)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4)));
    igStringMetaField_SetDefaultText(temp_v0, 0);
    ((igStringMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5)));
    FUN_002ea4b0(temp_v0_2, -1);
    ((igIntMetaField *)temp_v0_2)->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002c04a0();
    ((igObjectRefMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0019ea00();
    ((igObjectRefMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002bcbb0();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_6)->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &DAT_0048bf50[0], &DAT_0048bf80[0], &DAT_0048bfb0[0], temp_s0);
}

