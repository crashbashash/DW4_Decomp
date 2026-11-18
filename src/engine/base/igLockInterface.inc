igMetaObject *g_igLockInterface_metaObject;
igMetaField *g_igLockInterface_objectCacheNamesMetaField;
igMetaField *g_igLockInterface_objectCacheValidsMetaField;
igMetaField *g_igLockInterface_objectCacheListsMetaField;

igMetaObject *FUN_002267c0(void) {
    if (g_igLockInterface_metaObject == 0) {
        g_igLockInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLockInterface_metaObject;
}

igMetaObject *igLockInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igLockInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226a10();
    return g_igLockInterface_metaObject;
}

int igLockInterface_GetVTable(void) {
    union U_3 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igLockInterface_vtable[0];
    q2 = (S_ref *)&u.b[32];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[36];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[40];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igLockInterface_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
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
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
            }
        }
    }
    return temp_s0;
}

igSmartPointer<igObject> *igSmartPointer_igBoolList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void FUN_00226a10(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igLockInterface_Register);
}

static igMetaObjectCallback g_igLockInterface_callbackList[] = { igStringRefList_EnsureRegistered, igBoolList_EnsureRegistered, igObjectListList_EnsureRegistered, 0 };

CallbackArray *igLockInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLockInterface_metaObject,
        (igMetaObjectRegisterFunction)igInterface_Register,
        (igMetaObjectGetFunction)igInterface_GetPublishedMetaObject,
        thunk_igLockInterface_GetMetaObject,
        "igLockInterface",
        0x2C, /* instance size */
        igLockInterface_GetVTable,
        &igLockInterface_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igLockInterface_callbackList /* callback list */
    );
}

void thunk_igLockInterface_GetMetaObject(void) {
    igLockInterface_GetMetaObject();
}

static FieldFactory g_igLockInterface_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLockInterface_fieldTable[] = {
    "_objectCacheNames",
    "_objectCacheValids",
    "_objectCacheLists",
};
static igMetaField **g_igLockInterface_fieldHandles[] = {
    &g_igLockInterface_objectCacheNamesMetaField,
    &g_igLockInterface_objectCacheValidsMetaField,
    &g_igLockInterface_objectCacheListsMetaField,
};
static int g_igLockInterface_fieldOffsets[] = {
    32,
    36,
    40,
};

void igLockInterface_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igLockInterface_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igLockInterface_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)igObjectListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_igLockInterface_fieldTable, g_igLockInterface_fieldHandles, g_igLockInterface_fieldOffsets, temp_s2);
}

