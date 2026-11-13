void *FUN_00227780(int arg0) {
    FUN_002278a0();
    return igMetaObject_CreateInstance(*(int *)0x56D968, arg0);
}

igMetaObject *igIterateField_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002278a0();
    return g_igIterateField_metaObject[0];
}

int igIterateField_GetVTable(void) {
    union U_4 u;
    int t;
    char *ps;
    int *p;
    int *q;
    int v;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052c400[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0052c400[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return t;
}

void FUN_002278a0(void)
{
    igMetaObject_RunStaticInit(igIterateField_Register);
}

void igIterateField_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIterateField_metaObject,
        igIterator_Register,
        igIterator_GetPublishedMetaObject,
        thunk_igIterateField_GetMetaObject,
        igIterateField_className,
        0x10, /* instance size */
        igIterateField_GetVTable,
        &igIterateField_InitFields,
        0, /* extra callback item */
        g_igIterateField_callbackList /* callback list */
    );
}

void thunk_igIterateField_GetMetaObject(void) {
    igIterateField_GetMetaObject();
}

void igIterateField_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igIterateField_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igIterateField_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    igMetaObject_NameFields(temp_s0, &g_igIterateField_fieldTable[0], &DAT_00497d98[0], &DAT_00497da0[0], temp_s2);
}

