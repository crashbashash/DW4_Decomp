igMetaObject *FUN_0044d840(void) {
    if (g_igHotKeyEventReceiver_metaObject[0] == 0) {
        g_igHotKeyEventReceiver_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igHotKeyEventReceiver_metaObject[0];
}

igMetaObject *igHotKeyEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyEventReceiver_RunStaticInit();
    return g_igHotKeyEventReceiver_metaObject[0];
}

int igHotKeyEventReceiver_GetVTable(void) {
    union U_44d8e0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540e90[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00540e90[0];
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

void igHotKeyEventReceiver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyEventReceiver_Register);
}

void igHotKeyEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igHotKeyEventReceiver_GetMetaObject,
        igHotKeyEventReceiver_className,
        0xC, /* instance size */
        igHotKeyEventReceiver_GetVTable,
        &igHotKeyEventReceiver_InitFields,
        0, /* extra callback item */
        g_igHotKeyEventReceiver_callbackList /* callback list */
    );
}

void thunk_igHotKeyEventReceiver_GetMetaObject(void) {
    igHotKeyEventReceiver_GetMetaObject();
}

void igHotKeyEventReceiver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igHotKeyEventReceiver_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igHotKeyEventReceiver_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0044dab0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igHotKeyEventReceiver_fieldTable[0], &DAT_004d0118[0], &DAT_004d0120[0], temp_s2);
}

