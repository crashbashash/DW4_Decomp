igMetaObject *igActorInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igActorInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001aa410();
    return g_igActorInfo_metaObject[0];
}

int igActorInfo_GetVTable(void) {
    struct Obj_1aa1b0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_005297c0[0];
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005297c0[0];
    FUN_001a7a00((ObjectRefWord *)&obj.w9, -1);
    FUN_001a7a80((void * *)&obj.w8, -1);
    FUN_001aa390((void * *)&obj.w7, -1);
    FUN_001aa310((void * *)&obj.w6, -1);
    FUN_001aa290((void * *)&obj.w5, -1);
    FUN_00131b20(&obj, 0);
    return t;
}

void **FUN_001aa290(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001aa310(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001aa390(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_001aa410(void)
{
    igMetaObject_RunStaticInit(igActorInfo_Register);
}

void igActorInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igActorInfo_metaObject),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igActorInfo_GetMetaObject,
        igActorInfo_className,
        0x28, /* instance size */
        igActorInfo_GetVTable,
        &igActorInfo_InitFields,
        0, /* extra callback item */
        g_igActorInfo_callbackList /* callback list */
    );
}

void thunk_igActorInfo_GetMetaObject(void) {
    igActorInfo_GetMetaObject();
}

void igActorInfo_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;

    temp_s1 = (void *)DAT_00562450[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048d6d0[0], 5);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001aa730();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_001aa5c0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_001a7780();
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001a83b0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_001a5fe0();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_0048d6f0[0], &DAT_0048d710[0], &DAT_0048d730[0], temp_s0);
}

