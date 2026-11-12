int FUN_0044e990(int arg0) {
    igActiveComponentsObserver_RunStaticInit();
    return igMetaObject_CreateInstance(*(int *)0x58C360, arg0);
}

igMetaObject *igActiveComponentsObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igActiveComponentsObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igActiveComponentsObserver_RunStaticInit();
    return g_igActiveComponentsObserver_metaObject[0];
}

int igActiveComponentsObserver_GetVTable(void) {
    union U_44ea20 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00541020[0];
    p48 = &u.b[12];
    *(int *)p48 = 0;
    p4C = &u.b[16];
    *(int *)p4C = 0;
    p50 = &u.b[20];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00541020[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void igActiveComponentsObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igActiveComponentsObserver_Register);
}

void igActiveComponentsObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActiveComponentsObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igActiveComponentsObserver_GetMetaObject,
        igActiveComponentsObserver_className,
        0x18, /* instance size */
        igActiveComponentsObserver_GetVTable,
        &igActiveComponentsObserver_InitFields,
        0, /* extra callback item */
        g_igActiveComponentsObserver_callbackList /* callback list */
    );
}

void thunk_igActiveComponentsObserver_GetMetaObject(void) {
    igActiveComponentsObserver_GetMetaObject();
}

void igActiveComponentsObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igActiveComponentsObserver_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d02c8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0044ff40();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0044ff40();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0044ff40();
    igMetaObject_NameFields(temp_s0, &DAT_004d02d8[0], &DAT_004d02e8[0], &DAT_004d02f8[0], temp_s2);
}

