igMetaObject *g_igTraversal_metaObject;
igMetaField *g_igTraversal_nodeSelectProcEnabledMetaField;
igMetaField *g_igTraversal_nodeSelectProcMetaField;
igMetaField *g_igTraversal_timeLongMetaField;
igMetaField *g_igTraversal_userTimeStateMetaField;
igMetaField *g_igTraversal_travProcsMetaField;

igMetaObject *igTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversal_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00194530();
    return g_igTraversal_metaObject;
}

int igTraversal_GetVTable(void) {
    struct Obj o;
    struct R *t;
    int r;
    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igTraversal_vtable[0];
    o.p = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igTraversal_vtable[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
    }
    return r;
}

void *FUN_00194490(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_igTraversal_vtable[0];
        if (&arg0->f1c) {
            p = arg0->f1c;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void FUN_00194530(void)
{
    igMetaObject_RunStaticInit(igTraversal_Register);
}

static igMetaObjectCallback g_igTraversal_callbackList[] = { igTraversalFunctionList_EnsureRegistered, 0 };

CallbackArray *igTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTraversal_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igTraversal_GetMetaObject,
        "igTraversal",
        0x20, /* instance size */
        igTraversal_GetVTable,
        &igTraversal_InitFields,
        &FUN_00194690, /* extra callback item */
        g_igTraversal_callbackList /* callback list */
    );
}

void thunk_igTraversal_GetMetaObject(void) {
    igTraversal_GetMetaObject();
}

static FieldFactory g_igTraversal_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igTraversal_fieldTable[] = {
    "_nodeSelectProcEnabled",
    "_nodeSelectProc",
    "_timeLong",
    "_userTimeState",
    "_travProcs",
};
static igMetaField **g_igTraversal_fieldHandles[] = {
    &g_igTraversal_nodeSelectProcEnabledMetaField,
    &g_igTraversal_nodeSelectProcMetaField,
    &g_igTraversal_timeLongMetaField,
    &g_igTraversal_userTimeStateMetaField,
    &g_igTraversal_travProcsMetaField,
};
static int g_igTraversal_fieldOffsets[] = {
    8,
    12,
    16,
    24,
    28,
};

void igTraversal_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTraversal_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igTraversal_ctorTable, 5);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_0019a720();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igTraversal_fieldTable, g_igTraversal_fieldHandles, g_igTraversal_fieldOffsets, temp_s2);
    igMetaObject_AddExitCallback((int)&thunk_FUN_001e0470);
}

void FUN_00194690(void) {
    FUN_001e0410();
    igMetaObject_AddRegistrationCallback((int)((int *)FUN_001e02e0));
}

void thunk_FUN_001e0470(void) {
    FUN_001e0470();
}

