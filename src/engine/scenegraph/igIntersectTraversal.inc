igMetaObject *g_igIntersectTraversal_metaObject;
igMetaField *g_igIntersectTraversal_matStackMetaField;
igMetaField *g_igIntersectTraversal_nodeStackMetaField;
igMetaField *g_igIntersectTraversal_probeMetaField;
igMetaField *g_igIntersectTraversal_modeMetaField;
igMetaField *g_igIntersectTraversal_hitProcMetaField;
igMetaField *g_igIntersectTraversal_volumesMetaField;
igMetaField *g_igIntersectTraversal_rayMetaField;

igMetaObject *FUN_0019dfd0(void) {
    if (g_igIntersectTraversal_metaObject == 0) {
        g_igIntersectTraversal_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igIntersectTraversal_metaObject;
}

igMetaObject *igIntersectTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igIntersectTraversal_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019e440();
    return g_igIntersectTraversal_metaObject;
}

int igIntersectTraversal_GetVTable(void) {
    struct Obj_19e070 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w[6] = 0;
    obj.vt = &g_igIntersectTraversal_vtable[0];
    obj.w[7] = 0;
    obj.w[8] = 0;
    obj.w[9] = 0;
    obj.w[12] = 0;
    obj.w[13] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igIntersectTraversal_vtable[0];
    FUN_0019e3c0((void * *)&obj.w[13], -1);
    FUN_0018fa00(&obj.w[12], -1);
    FUN_0019e340((void * *)&obj.w[9], -1);
    igSmartPointer_igNodeList_Destruct((void * *)&obj.w[8], -1);
    FUN_00150fb0(&obj.w[7], -1);
    FUN_00194490((struct S *)((int *)&obj), 0);
    return t;
}

igIntersectTraversal *igIntersectTraversal_Destroy(igIntersectTraversal *self, short deleteFlag) {
    if (self) {
        self->_vtable = (int)&g_igIntersectTraversal_vtable[0];
        if (&self->_ray) {
            S1 *t = (S1 *)self->_ray;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&self->_volumes) {
            S1 *t = (S1 *)self->_volumes;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&self->_probe) {
            S1 *t = (S1 *)self->_probe;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&self->_nodeStack) {
            S1 *t = (S1 *)self->_nodeStack;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&self->_matStack) {
            S1 *t = (S1 *)self->_matStack;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (self) {
            self->_vtable = (int)&g_igTraversal_vtable[0];
            if (&self->_travProcs) {
                S1 *t = (S1 *)self->_travProcs;
                if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
            }
        }
        if (deleteFlag > 0) Memory_FreeBufferAliasC(self);
    }
    return self;
}

void **FUN_0019e340(void **arg0, short arg1) {
    S_temp_a0_19e340 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_19e340 *)(*arg0);
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

void **FUN_0019e3c0(void **arg0, short arg1) {
    S_temp_a0_19e3c0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_19e3c0 *)(*arg0);
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

void FUN_0019e440(void)
{
    igMetaObject_RunStaticInit((CallbackArray * (*)())igIntersectTraversal_Register);
}

static igMetaObjectCallback g_igIntersectTraversal_callbackList[] = { FUN_001e4820, igNodeList_EnsureRegistered, igProbe_EnsureRegistered, FUN_00186d20, igRay_EnsureRegistered, 0 };

CallbackArray *igIntersectTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIntersectTraversal_metaObject,
        igTraversal_Register,
        igTraversal_GetPublishedMetaObject,
        thunk_igIntersectTraversal_GetMetaObject,
        "igIntersectTraversal",
        0x40, /* instance size */
        igIntersectTraversal_GetVTable,
        &igIntersectTraversal_InitFields,
        &FUN_0019e640, /* extra callback item */
        g_igIntersectTraversal_callbackList /* callback list */
    );
}

void thunk_igIntersectTraversal_GetMetaObject(void) {
    igIntersectTraversal_GetMetaObject();
}

igMetaObject *FUN_0019e4e0(void) {
    return g_igTraversal_metaObject;
}

static FieldFactory g_igIntersectTraversal_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igIntersectTraversal_fieldTable[] = {
    "_matStack",
    "_nodeStack",
    "_probe",
    "_mode",
    "_hitProc",
    "_volumes",
    "_ray",
};
static igMetaField **g_igIntersectTraversal_fieldHandles[] = {
    &g_igIntersectTraversal_matStackMetaField,
    &g_igIntersectTraversal_nodeStackMetaField,
    &g_igIntersectTraversal_probeMetaField,
    &g_igIntersectTraversal_modeMetaField,
    &g_igIntersectTraversal_hitProcMetaField,
    &g_igIntersectTraversal_volumesMetaField,
    &g_igIntersectTraversal_rayMetaField,
};
static int g_igIntersectTraversal_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
    52,
    56,
};

void igIntersectTraversal_InitFields(void) {
    void *temp_s1;
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;

    temp_s1 = (void *)g_igIntersectTraversal_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igIntersectTraversal_ctorTable, 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igNodeList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igProbe_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igIntMetaField_SetDefault(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)), 5);
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, 4 + temp_s0))))->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00186c40();
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00188260();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igIntersectTraversal_fieldTable, g_igIntersectTraversal_fieldHandles, g_igIntersectTraversal_fieldOffsets, temp_s0);
    igMetaObject_AddExitCallback((int)&thunk_FUN_001ce740);
}

void FUN_0019e640(void) {
    FUN_001ce710();
    igMetaObject_AddRegistrationCallback((int)FUN_001ce660);
}

void thunk_FUN_001ce740(void) {
    FUN_001ce740();
}

