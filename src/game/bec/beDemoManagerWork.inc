void beDemoManagerWork_CreateInstance(int arg0) {
    FUN_00363930();
    igMetaObject_CreateInstance(*(int *)0x5897D8, arg0);
}

igMetaObject *FUN_00363800(void) {
    if (g_beDemoManagerWork_metaObject[0] == 0) {
        g_beDemoManagerWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beDemoManagerWork_metaObject[0];
}

void *FUN_00363850(void) {
    igMetaObject *g = g_beDemoManagerWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00363930();
    }
    return g_beDemoManagerWork_metaObject[0];
}

int beDemoManagerWork_GetVTable(void) {
    union U_3638a0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005356e0[0];
    ps = &u.b[12];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005356e0[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_00363930(void)
{
    igMetaObject_RunStaticInit(beDemoManagerWork_Register);
}

void *beDemoManagerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoManagerWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beDemoManagerWork_GetMetaObject,
        beDemoManagerWork_className,
        0x10, /* instance size */
        beDemoManagerWork_GetVTable,
        beDemoManagerWork_InitFields,
        0, /* extra callback item */
        g_beDemoManagerWork_callbackList /* callback list */
    );
}

void beDemoManagerWork_GetMetaObject(void)
{
    FUN_00363850();
}

void beDemoManagerWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDemoManagerWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beDemoManagerWork_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00363a90();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beDemoManagerWork_fieldTable[0], &DAT_004c7060[0], &DAT_004c7068[0], temp_s2);
}

