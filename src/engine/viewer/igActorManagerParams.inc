igMetaObject *g_igActorManagerParams_metaObject;
igMetaField *g_igActorManagerParams_skelOnlyMetaField;
igMetaField *g_igActorManagerParams_skelAndSkinMetaField;

igMetaObject *FUN_0045e6f0(void) {
    if (g_igActorManagerParams_metaObject == 0) {
        g_igActorManagerParams_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igActorManagerParams_metaObject;
}

void *igActorManagerParams_GetMetaObject(void) {
    igMetaObject *g = g_igActorManagerParams_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045e830();
    }
    return g_igActorManagerParams_metaObject;
}

int igActorManagerParams_GetVTable(void) {
    union U_45e790 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((igObject *)u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igModel_vtable[0];
    u.vt = (int)&g_igActorManagerParams_vtable[0];
    s0 = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem)) + 916)];
    u.vt = (int)&g_igModel_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)v1);
            }
        }
    }
    return s0;
}

void FUN_0045e830(void)
{
    igMetaObject_RunStaticInit(igActorManagerParams_Register);
}

CallbackArray *igActorManagerParams_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igActorManagerParams_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igActorManagerParams_GetMetaObject,
        "igActorManagerParams",
        0x10, /* instance size */
        igActorManagerParams_GetVTable,
        &igActorManagerParams_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igActorManagerParams_GetMetaObject(void) {
    igActorManagerParams_GetMetaObject();
}

static FieldFactory g_igActorManagerParams_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igActorManagerParams_fieldTable[] = {
    "_skelOnly",
    "_skelAndSkin",
};
static igMetaField **g_igActorManagerParams_fieldHandles[] = {
    &g_igActorManagerParams_skelOnlyMetaField,
    &g_igActorManagerParams_skelAndSkinMetaField,
};
static int g_igActorManagerParams_fieldOffsets[] = {
    12,
    13,
};

void igActorManagerParams_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = g_igActorManagerParams_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igActorManagerParams_ctorTable, 2);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igActorManagerParams_fieldTable, g_igActorManagerParams_fieldHandles, g_igActorManagerParams_fieldOffsets, temp_s1);
}

igMetaObject *Gap__Viewer__igActorManagerParams__vfunc_22(void) {
    return g_igActorManagerParams_metaObject;
}

