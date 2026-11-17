igMetaObject *g_igAttrPool_metaObject;
igMetaField *g_igAttrPool_metaListMetaField;
igMetaField *g_igAttrPool_nonSharableMetaListMetaField;
igMetaField *g_igAttrPool_attributeListMetaField;

int FUN_0013a640(int arg0) {
    igAttrPool_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(*(igMetaObject * *)0x55F428, (igMemoryPoolView *)arg0);
}

igMetaObject *igAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttrPool_EnsureRegistered();
    return g_igAttrPool_metaObject;
}

int igAttrPool_GetVTable(void) {
    union U_13a6d0 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igAttrPool_vtable[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igAttrPool_vtable[0];
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

void **FUN_0013a800(void **arg0, short arg1) {
    S_temp_a0_13a800 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_13a800 *)((void *)(*arg0));
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igMetaObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
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

void igAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttrPool_Register);
}

static igMetaObjectCallback g_igAttrPool_callbackList[] = { igMetaObjectList_EnsureRegistered, igAttrListList_EnsureRegistered, 0 };

CallbackArray *igAttrPool_Register(void) {
    AttrsLibrary_MarkRegistered();  /* Set-once latch: writes a gp-relative byte flag only if it is clear. */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrPool_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrPool_GetMetaObject,
        "igAttrPool",
        0x14, /* instance size */
        igAttrPool_GetVTable,
        &igAttrPool_InitFields,
        FUN_0013aa90,                      /* static-initializer callback item (appended on fresh configuration) */
        g_igAttrPool_callbackList     /* 0-terminated dependency-callback list */
    );
}

void thunk_igAttrPool_GetMetaObject(void) {
    igAttrPool_GetMetaObject();
}

static FieldFactory g_igAttrPool_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAttrPool_fieldTable[] = {
    "_metaList",
    "_nonSharableMetaList",
    "_attributeList",
};
static igMetaField **g_igAttrPool_fieldHandles[] = {
    &g_igAttrPool_metaListMetaField,
    &g_igAttrPool_nonSharableMetaListMetaField,
    &g_igAttrPool_attributeListMetaField,
};
static int g_igAttrPool_fieldOffsets[] = {
    8,
    12,
    16,
};

void igAttrPool_InitFields(void) {
    void *temp_s1;
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1_3;
    igMetaObject *temp_s0;

    temp_s0 = g_igAttrPool_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igAttrPool_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0013abd0();
    ((igObjectRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_igAttrPool_fieldTable, g_igAttrPool_fieldHandles, g_igAttrPool_fieldOffsets, temp_s2);
    igMetaObject_AddExitCallback((int)thunk_FUN_0013c110);
}

void FUN_0013aa90(void) {
    FUN_0013c170();
}

void thunk_FUN_0013c110(void) {
    FUN_0013c110();
}

