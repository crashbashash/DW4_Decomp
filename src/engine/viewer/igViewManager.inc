igMetaObject *g_igViewManager_metaObject;
igMetaField *g_igViewManager_viewModeMetaField;
igMetaField *g_igViewManager_viewModelMetaField;
igMetaField *g_igViewManager_synchronizersMetaField;
igMetaField *g_igViewManager_homeMatrixMetaField;

igMetaObject *FUN_0045d100(void) {
    if (g_igViewManager_metaObject == 0) {
        g_igViewManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewManager_metaObject;
}

void *igViewManager_GetMetaObject(void) {
    igMetaObject *g = g_igViewManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045d2f0();
    }
    return g_igViewManager_metaObject;
}

int igViewManager_GetVTable(void) {
    union U_45d1a0 u;
    int temp_s3;
    S_ref *q3;
    S_ref *q2;
    S_ref *q1;
    
    
    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&g_igViewManager_vtable[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    igMatrix44f_SetIdentity((float *)&u.w[5]);
    temp_s3 = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem)) + 916)];
    u.w[0] = (int)(&DAT_00542680[4]);
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
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    return temp_s3;
}

void FUN_0045d2f0(void)
{
    igMetaObject_RunStaticInit(igViewManager_Register);
}

static igMetaObjectCallback g_igViewManager_callbackList[] = { FUN_0045d000, FUN_0045d5c0, igObjectList_EnsureRegistered, 0 };

CallbackArray *igViewManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewManager_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igViewManager_GetMetaObject,
        "igViewManager",
        0x54, /* instance size */
        igViewManager_GetVTable,
        &igViewManager_InitFields,
        0, /* extra callback item */
        g_igViewManager_callbackList /* callback list */
    );
}

void thunk_igViewManager_GetMetaObject(void) {
    igViewManager_GetMetaObject();
}

static FieldFactory g_igViewManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
};
static const char *g_igViewManager_fieldTable[] = {
    "_viewMode",
    "_viewModel",
    "_synchronizers",
    "_homeMatrix",
};
static igMetaField **g_igViewManager_fieldHandles[] = {
    &g_igViewManager_viewModeMetaField,
    &g_igViewManager_viewModelMetaField,
    &g_igViewManager_synchronizersMetaField,
    &g_igViewManager_homeMatrixMetaField,
};
static int g_igViewManager_fieldOffsets[] = {
    8,
    12,
    16,
    20,
};

void igViewManager_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = g_igViewManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewManager_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0045cf10();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0045d470();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewManager_fieldTable, g_igViewManager_fieldHandles, g_igViewManager_fieldOffsets, temp_s2);
}

