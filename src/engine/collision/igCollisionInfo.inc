igMetaObject *g_igCollisionInfo_metaObject;
igMetaField *g_igCollisionInfo_gridMetaField;

Rc *igCollisionInfo_Create(int arg0) {
    igCollisionInfo_EnsureRegistered();
    return (Rc *)igMetaObject_CreateInstance(g_igCollisionInfo_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igCollisionInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCollisionInfo_EnsureRegistered();
    return g_igCollisionInfo_metaObject;
}

int igCollisionInfo_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_igCollisionInfo_vtable[0];
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igCollisionInfo_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igCollisionInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCollisionInfo_Register);
}

static igMetaObjectCallback g_igCollisionInfo_callbackList[] = { igCollisionGrid_EnsureRegistered, 0 };

CallbackArray *igCollisionInfo_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        igCollisionInfo_GetMetaObjectFunction,
        "igCollisionInfo",
        0x18, /* instance size */
        igCollisionInfo_GetVTable,
        &igCollisionInfo_InitFields,
        0, /* extra callback item */
        g_igCollisionInfo_callbackList /* callback list */
    );
}

void igCollisionInfo_GetMetaObjectFunction(void) {
    igCollisionInfo_GetMetaObject();
}

static FieldFactory g_igCollisionInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igCollisionInfo_fieldTable[] = {
    "_grid",
};
static igMetaField **g_igCollisionInfo_fieldHandles[] = {
    &g_igCollisionInfo_gridMetaField,
};
static int g_igCollisionInfo_fieldOffsets[] = {
    20,
};

void igCollisionInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCollisionInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCollisionInfo_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igCollisionGrid_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCollisionInfo_fieldTable, g_igCollisionInfo_fieldHandles, g_igCollisionInfo_fieldOffsets, temp_s2);
}

