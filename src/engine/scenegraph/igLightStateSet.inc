igMetaObject *igLightStateSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateSet_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019da60();
    return g_igLightStateSet_metaObject[0];
}

int igLightStateSet_GetVTable(void) {
    struct Obj_19d960 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[6] = 0;
    obj.vt = &DAT_00528bc0[0];
    obj.w[7] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00528bc0[0];
    FUN_0019d9e0((void * *)&obj.w[7], -1);
    FUN_00195a90((struct T_195a90 *)&obj, 0);
    return r;
}

void **FUN_0019d9e0(void **arg0, short arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0019da60(void)
{
    igMetaObject_RunStaticInit(igLightStateSet_Register);
}

void igLightStateSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLightStateSet_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igLightStateSet_GetMetaObject,
        igLightStateSet_className,
        0x24, /* instance size */
        igLightStateSet_GetVTable,
        &igLightStateSet_InitFields,
        0, /* extra callback item */
        g_igLightStateSet_callbackList /* callback list */
    );
}

void thunk_igLightStateSet_GetMetaObject(void) {
    igLightStateSet_GetMetaObject();
}

void igLightStateSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightStateSet_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048bd98[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00136040();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields(temp_s0, &DAT_0048bda0[0], &DAT_0048bda8[0], &DAT_0048bdb0[0], temp_s2);
}

