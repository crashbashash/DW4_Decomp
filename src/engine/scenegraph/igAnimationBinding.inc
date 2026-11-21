int FUN_001a8c30(int arg0) {
    igAnimationBinding_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igAnimationBinding_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igAnimationBinding_metaObject;
igMetaField *g_igAnimationBinding_hierarchyMetaField;
igMetaField *g_igAnimationBinding_boneTrackIdxArrayMetaField;
igMetaField *g_igAnimationBinding_bindCountMetaField;
igMetaField *g_igAnimationBinding_chainSwapListMetaField;
igMetaField *g_igAnimationBinding_reflectTrackMetaField;

igMetaObject *igAnimationBinding_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationBinding_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationBinding_EnsureRegistered();
    return g_igAnimationBinding_metaObject;
}

int igAnimationBinding_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igAnimationBinding_vtable[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[20];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igAnimationBinding_vtable[0];
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

void igAnimationBinding_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationBinding_Register);
}

static igMetaObjectCallback g_igAnimationBinding_callbackList[] = { igAnimationHierarchy_EnsureRegistered, Gap::Core::igIntList::arkRegister, igBitMask_EnsureRegistered, 0 };

CallbackArray *igAnimationBinding_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationBinding_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igAnimationBinding_GetMetaObjectFunction,
        "igAnimationBinding",
        0x1C, /* instance size */
        igAnimationBinding_GetVTable,
        &igAnimationBinding_InitFields,
        0, /* extra callback item */
        g_igAnimationBinding_callbackList /* callback list */
    );
}

void igAnimationBinding_GetMetaObjectFunction(void) {
    igAnimationBinding_GetMetaObject();
}

static FieldFactory g_igAnimationBinding_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAnimationBinding_fieldTable[] = {
    "_hierarchy",
    "_boneTrackIdxArray",
    "_bindCount",
    "_chainSwapList",
    "_reflectTrack",
};
static igMetaField **g_igAnimationBinding_fieldHandles[] = {
    &g_igAnimationBinding_hierarchyMetaField,
    &g_igAnimationBinding_boneTrackIdxArrayMetaField,
    &g_igAnimationBinding_bindCountMetaField,
    &g_igAnimationBinding_chainSwapListMetaField,
    &g_igAnimationBinding_reflectTrackMetaField,
};
static int g_igAnimationBinding_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void igAnimationBinding_InitFields(void) {
    int base;
    void *reflectTrackField;
    void *chainSwapListField;
    void *boneTrackIdxArrayField;
    void *hierarchyField;
    void *meta;

    meta = (void *)g_igAnimationBinding_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAnimationBinding_ctorTable, 5);
    hierarchyField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)hierarchyField)->_metaObject = (int)igAnimationHierarchy_GetOrCreateMetaObject();
    boneTrackIdxArrayField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igMemoryRefMetaField *)boneTrackIdxArrayField)->_memType = (int)Gap::Core::igIntMetaField::getMetaField();
    ((igRefMetaField *)boneTrackIdxArrayField)->_destruct = 1;
    ((igMemoryRefMetaField *)boneTrackIdxArrayField)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)boneTrackIdxArrayField)->_releaseOnReset = 1;
    chainSwapListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)chainSwapListField)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    reflectTrackField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igObjectRefMetaField *)reflectTrackField)->_metaObject = (int)igBitMask_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igAnimationBinding_fieldTable, g_igAnimationBinding_fieldHandles, g_igAnimationBinding_fieldOffsets, base);
}

