igMetaObject *g_igHotKeyEventReceiver_metaObject;
igMetaField *g_igHotKeyEventReceiver_hotKeyListMetaField;

igMetaObject *igHotKeyEventReceiver_GetOrCreateMetaObject(void) {
    if (g_igHotKeyEventReceiver_metaObject == 0) {
        g_igHotKeyEventReceiver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igHotKeyEventReceiver_metaObject;
}

igMetaObject *igHotKeyEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyEventReceiver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyEventReceiver_RunStaticInit();
    return g_igHotKeyEventReceiver_metaObject;
}

int igHotKeyEventReceiver_GetVTable(void) {
    union U_44d8e0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igHotKeyEventReceiver_vtable[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igHotKeyEventReceiver_vtable[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igHotKeyEventReceiver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyEventReceiver_Register);
}

static igMetaObjectCallback g_igHotKeyEventReceiver_callbackList[] = { igHotKeyBindingList_RunStaticInit, 0 };

CallbackArray *igHotKeyEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igHotKeyEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igHotKeyEventReceiver_GetMetaObject,
        "igHotKeyEventReceiver",
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

static FieldFactory g_igHotKeyEventReceiver_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igHotKeyEventReceiver_fieldTable[] = {
    "_hotKeyList",
};
static igMetaField **g_igHotKeyEventReceiver_fieldHandles[] = {
    &g_igHotKeyEventReceiver_hotKeyListMetaField,
};
static int g_igHotKeyEventReceiver_fieldOffsets[] = {
    8,
};

void igHotKeyEventReceiver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igHotKeyEventReceiver_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igHotKeyEventReceiver_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igHotKeyBindingList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igHotKeyEventReceiver_fieldTable, g_igHotKeyEventReceiver_fieldHandles, g_igHotKeyEventReceiver_fieldOffsets, temp_s2);
}

