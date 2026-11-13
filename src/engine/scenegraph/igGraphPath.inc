int FUN_0019f630(int arg0) {
    FUN_0019f7a0();
    return igMetaObject_CreateInstance(*(int *)0x561A10, arg0);
}

igMetaObject *FUN_0019f670(void) {
    if (g_igGraphPath_metaObject[0] == 0) {
        g_igGraphPath_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGraphPath_metaObject[0];
}

igMetaObject *igGraphPath_GetMetaObject(void)
{
    igMetaObject *g = g_igGraphPath_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019f7a0();
    return g_igGraphPath_metaObject[0];
}

int igGraphPath_GetVTable(void) {
    Obj_19f710 o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader(&o);
    ps = &o.ref;
    o.vt = &DAT_0052a810[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0052a810[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_0019f7a0(void)
{
    igMetaObject_RunStaticInit(igGraphPath_Register);
}

void igGraphPath_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igGraphPath_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGraphPath_GetMetaObject,
        igGraphPath_className,
        0x1C, /* instance size */
        igGraphPath_GetVTable,
        &igGraphPath_InitFields,
        0, /* extra callback item */
        g_igGraphPath_callbackList /* callback list */
    );
}

void thunk_igGraphPath_GetMetaObject(void) {
    igGraphPath_GetMetaObject();
}

void igGraphPath_InitFields(void) {
    int temp_s2;
    void *temp_a0;
    void *temp_s1;
    void *temp_s0;
    struct { int a; int b; int c; } z;

    temp_s0 = (void *)g_igGraphPath_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igGraphPath_ctorTable[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_0019cbe0();
    *(char *)((char *)(temp_s1) + 36) = 3;
    *(char *)((char *)(temp_s1) + 52) = 1;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    z.a = 0;
    z.b = 0;
    z.c = 0;
    FUN_0018e470(temp_a0, &z);
    FUN_002e3810(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)), 1.0f);
    igMetaObject_NameFields(temp_s0, &g_igGraphPath_fieldTable[0], &DAT_0048c030[0], &DAT_0048c040[0], temp_s2);
}

