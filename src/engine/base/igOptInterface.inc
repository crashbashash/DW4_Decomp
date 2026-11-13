igMetaObject *FUN_00225a40(void) {
    if (g_igOptInterface_metaObject[0] == 0) {
        g_igOptInterface_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igOptInterface_metaObject[0];
}

igMetaObject *igOptInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igOptInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225c10();
    return g_igOptInterface_metaObject[0];
}

int igOptInterface_GetVTable(void) {
    struct Obj_2 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052be10[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052be10[0];
    FUN_001d35d0(&obj.w11, -1);
    FUN_00225b90((void **)&obj.w10, -1);
    StringRef_Destruct_00130720(&obj.w9, -1);
    FUN_0013a880(&obj.w8, -1);
    return t;
}

void **FUN_00225b90(void **arg0, long long arg1) {
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

void FUN_00225c10(void)
{
    igMetaObject_RunStaticInit(igOptInterface_Register);
}

void igOptInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOptInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igOptInterface_GetMetaObject,
        igOptInterface_className,
        0x30, /* instance size */
        igOptInterface_GetVTable,
        &igOptInterface_InitFields,
        0, /* extra callback item */
        g_igOptInterface_callbackList /* callback list */
    );
}

void thunk_igOptInterface_GetMetaObject(void) {
    igOptInterface_GetMetaObject();
}

igMetaObject *FUN_00225cb0(void) {
    return g_igInterface_metaObject[0];
}

void igOptInterface_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_v0;
    void *temp_s1;

    temp_s1 = (void *)g_igOptInterface_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igOptInterface_ctorTable[0], 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_002c8e50();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    igStringMetaField_SetDefaultText(temp_v0, &DAT_004e79b0[0]);
    ((igStringMetaField *)temp_v0)->_destruct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00228e60();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_igOptInterface_fieldTable[0], &DAT_00497be0[0], &DAT_00497bf0[0], temp_s0);
}

