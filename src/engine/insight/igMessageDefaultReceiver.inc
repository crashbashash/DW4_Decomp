void FUN_00232200(int arg0) {
    FUN_00232320();
    igMetaObject_CreateInstance(*(int *)0x56DB30, arg0);
}

igMetaObject *igMessageDefaultReceiver_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMessageDefaultReceiver_metaObject[0] != 0) {
        ready = (g_igMessageDefaultReceiver_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00232320();
done:
    return g_igMessageDefaultReceiver_metaObject[0];
}

int igMessageDefaultReceiver_GetVTable(void) {
    union U_232290 u;
    int temp_s0;
    char *ps;
    int *p;
    int v;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052c930[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0052c930[0];
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
    return temp_s0;
}

void FUN_00232320(void)
{
    igMetaObject_RunStaticInit(igMessageDefaultReceiver_Register);
}

void igMessageDefaultReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageDefaultReceiver_metaObject,
        igMessageReceiver_Register,
        igMessageReceiver_GetPublishedMetaObject,
        thunk_igMessageDefaultReceiver_GetMetaObject,
        igMessageDefaultReceiver_className,
        0x18, /* instance size */
        igMessageDefaultReceiver_GetVTable,
        &igMessageDefaultReceiver_InitFields,
        0, /* extra callback item */
        g_igMessageDefaultReceiver_callbackList /* callback list */
    );
}

void thunk_igMessageDefaultReceiver_GetMetaObject(void) {
    igMessageDefaultReceiver_GetMetaObject();
}

igMetaObject *FUN_002323c0(void) {
    return g_igMessageReceiver_metaObject[0];
}

void igMessageDefaultReceiver_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s1;
    char *p;

    temp_s0 = g_igMessageDefaultReceiver_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498048[0], 2);
    p = (char *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)(p + 56) = (int)g_igObject_metaObject[0];
    p = (char *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    *(short *)(p + 20) = 0xC;
    igMetaObject_NameFields(temp_s0, &DAT_00498050[0], &DAT_00498058[0], &DAT_00498060[0], temp_s1);
}

