igMetaObject *g_igCollisionGridHelper_metaObject;
igMetaField *g_igCollisionGridHelper_gridMetaField;
igMetaField *g_igCollisionGridHelper_staticGroupTypeMetaField;

igMetaObject *igCollisionGridHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGridHelper_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239ee0();
    return g_igCollisionGridHelper_metaObject;
}

int igCollisionGridHelper_GetVTable(void) {
    union U_239e00 u;
    int temp_s1;
    S_ref *q2;
    S_ref *q3;

    void *temp_a0;
    void *temp_a0_2;

    igObject_InitHeader((igObject *)u.b);
    q2 = (S_ref *)&u.p[2];
    q3 = (S_ref *)&u.p[3];
    u.w[0] = (int)(&g_igCollisionGridHelper_vtable[0]);
    *(int *)q2 = 0;
    *(int *)q3 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.w[0] = (int)(&g_igCollisionGridHelper_vtable[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s1;
}

void FUN_00239ee0(void)
{
    igMetaObject_RunStaticInit(igCollisionGridHelper_Register);
}

static igMetaObjectCallback g_igCollisionGridHelper_callbackList[] = { FUN_0023a340, igMetaObject_EnsureRegistered, 0 };

CallbackArray *igCollisionGridHelper_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionGridHelper_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionGridHelper_GetMetaObject,
        "igCollisionGridHelper",
        0x10, /* instance size */
        igCollisionGridHelper_GetVTable,
        &igCollisionGridHelper_InitFields,
        0, /* extra callback item */
        g_igCollisionGridHelper_callbackList /* callback list */
    );
}

void thunk_igCollisionGridHelper_GetMetaObject(void) {
    igCollisionGridHelper_GetMetaObject();
}

static FieldFactory g_igCollisionGridHelper_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igCollisionGridHelper_fieldTable[] = {
    "_grid",
    "_staticGroupType",
};
static igMetaField **g_igCollisionGridHelper_fieldHandles[] = {
    &g_igCollisionGridHelper_gridMetaField,
    &g_igCollisionGridHelper_staticGroupTypeMetaField,
};
static int g_igCollisionGridHelper_fieldOffsets[] = {
    8,
    12,
};

void igCollisionGridHelper_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCollisionGridHelper_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCollisionGridHelper_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0023a080();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)(igMetaObject_GetOrCreateMetaObject());
    igObjectRefMetaField_SetDefault(temp_s1_2, igCollisionGroup_GetMetaObject());
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCollisionGridHelper_fieldTable, g_igCollisionGridHelper_fieldHandles, g_igCollisionGridHelper_fieldOffsets, temp_s2);
}

