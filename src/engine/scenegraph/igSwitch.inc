void igSwitch_CreateInstance(int arg0) {
    FUN_00196ad0();
    igMetaObject_CreateInstance(*(int *)0x561308, arg0);
}

igMetaObject *FUN_00196930(void) {
    if (g_igSwitch_metaObject[0] == 0) {
        g_igSwitch_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igSwitch_metaObject[0];
}

igMetaObject *igSwitch_GetMetaObject(void)
{
    igMetaObject *g = g_igSwitch_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00196ad0();
    return g_igSwitch_metaObject[0];
}

int igSwitch_GetVTable(void) {
    union U_1969d0 u;
    int temp_s0;
    char *ps;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&DAT_00528590[0];
    ps = &u.b[32];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00528590[0];
    FUN_00196a50((struct R * *)ps, -1);
    FUN_00195a90((struct T_195a90 *)u.b, 0);
    return temp_s0;
}

struct R **FUN_00196a50(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00196ad0(void)
{
    igMetaObject_RunStaticInit(igSwitch_Register);
}

void igSwitch_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSwitch_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igSwitch_GetMetaObject,
        igSwitch_className,
        0x24, /* instance size */
        igSwitch_GetVTable,
        &igSwitch_InitFields,
        0, /* extra callback item */
        g_igSwitch_callbackList /* callback list */
    );
}

void thunk_igSwitch_GetMetaObject(void) {
    igSwitch_GetMetaObject();
}

void igSwitch_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSwitch_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igSwitch_ctorTable[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a4d90();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igSwitch_fieldTable[0], &DAT_0048b228[0], &DAT_0048b230[0], temp_s2);
}

