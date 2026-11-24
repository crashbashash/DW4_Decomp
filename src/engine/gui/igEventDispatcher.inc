igMetaObject *g_igEventDispatcher_metaObject;
igMetaField *g_igEventDispatcher_receiversMetaField;
igMetaField *g_igEventDispatcher_controllerManagerMetaField;

igMetaObject *igEventDispatcher_GetOrCreateMetaObject(void) {
    if (g_igEventDispatcher_metaObject == 0) {
        g_igEventDispatcher_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igEventDispatcher_metaObject;
}

igMetaObject *igEventDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igEventDispatcher_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventDispatcher_EnsureRegistered();
    return g_igEventDispatcher_metaObject;
}

int igEventDispatcher_GetVTable(void) {
    union U_451450 u;
    int temp_s2;
    S_ref *q2;
    S_ref *q1;
    S_ref *q3;
    
    
    igObject_InitHeader((igObject *)u.b);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&g_igEventDispatcher_vtable[0]);
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    temp_s2 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igEventDispatcher_vtable[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524da0[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    return temp_s2;
}

void igEventDispatcher_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventDispatcher_Register);
}

static igMetaObjectCallback g_igEventDispatcher_callbackList[] = { Gap::Gui::igEventReceiverOrderedList::arkRegister, igControllerManager_EnsureRegistered, 0 };

CallbackArray *igEventDispatcher_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEventDispatcher_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        igEventDispatcher_GetMetaObjectFunction,
        "igEventDispatcher",
        0x14, /* instance size */
        igEventDispatcher_GetVTable,
        &igEventDispatcher_InitFields,
        0, /* extra callback item */
        g_igEventDispatcher_callbackList /* callback list */
    );
}

void igEventDispatcher_GetMetaObjectFunction(void) {
    igEventDispatcher_GetMetaObject();
}

static FieldFactory g_igEventDispatcher_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igEventDispatcher_fieldTable[] = {
    "_receivers",
    "_controllerManager",
};
static igMetaField **g_igEventDispatcher_fieldHandles[] = {
    &g_igEventDispatcher_receiversMetaField,
    &g_igEventDispatcher_controllerManagerMetaField,
};
static int g_igEventDispatcher_fieldOffsets[] = {
    12,
    16,
};

void igEventDispatcher_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEventDispatcher_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igEventDispatcher_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)Gap::Gui::igEventReceiverOrderedList::getClassTypeLazy();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igControllerManager_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igEventDispatcher_fieldTable, g_igEventDispatcher_fieldHandles, g_igEventDispatcher_fieldOffsets, temp_s2);
}

