igMetaObject *g_igAnimationTrack_metaObject;
igMetaField *g_igAnimationTrack_sourceMetaField;
igMetaField *g_igAnimationTrack_constantQuaternionMetaField;
igMetaField *g_igAnimationTrack_constantTranslationMetaField;

igMetaObject *igAnimationTrack_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTrack_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationTrack_EnsureRegistered();
    return g_igAnimationTrack_metaObject;
}

int igAnimationTrack_GetVTable(void) {
    union U_1a9f50 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_igAnimationTrack_vtable[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igAnimationTrack_vtable[0];
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
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igAnimationTrack_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationTrack_Register);
}

static igMetaObjectCallback g_igAnimationTrack_callbackList[] = { igTransformSource_EnsureRegistered, 0 };

CallbackArray *igAnimationTrack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTrack_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igAnimationTrack_GetMetaObjectFunction,
        "igAnimationTrack",
        0x2C, /* instance size */
        igAnimationTrack_GetVTable,
        &igAnimationTrack_InitFields,
        0, /* extra callback item */
        g_igAnimationTrack_callbackList /* callback list */
    );
}

void igAnimationTrack_GetMetaObjectFunction(void) {
    igAnimationTrack_GetMetaObject();
}

static FieldFactory g_igAnimationTrack_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec3fMetaField_CreateInstance,
};
static const char *g_igAnimationTrack_fieldTable[] = {
    "_source",
    "_constantQuaternion",
    "_constantTranslation",
};
static igMetaField **g_igAnimationTrack_fieldHandles[] = {
    &g_igAnimationTrack_sourceMetaField,
    &g_igAnimationTrack_constantQuaternionMetaField,
    &g_igAnimationTrack_constantTranslationMetaField,
};
static int g_igAnimationTrack_fieldOffsets[] = {
    12,
    16,
    32,
};

void igAnimationTrack_InitFields(void) {
    int base;
    void *sourceField;
    void *meta;

    meta = (void *)g_igAnimationTrack_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAnimationTrack_ctorTable, 3);
    sourceField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)sourceField)->_metaObject = (int)igTransformSource_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igAnimationTrack_fieldTable, g_igAnimationTrack_fieldHandles, g_igAnimationTrack_fieldOffsets, base);
}

