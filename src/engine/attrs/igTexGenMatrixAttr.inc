igMetaObject *g_igTexGenMatrixAttr_metaObject;
igMetaField *g_igTexGenMatrixAttr_mMetaField;
igMetaField *g_igTexGenMatrixAttr_unitIDMetaField;

void FUN_00133160(int arg0) {
    FUN_00133290();
    igMetaObject_CreateInstance(*(int *)0x55EE28, arg0);
}

igMetaObject *FUN_001331a0(void) {
    if (g_igTexGenMatrixAttr_metaObject == 0) {
        g_igTexGenMatrixAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTexGenMatrixAttr_metaObject;
}

igMetaObject *igTexGenMatrixAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTexGenMatrixAttr_metaObject != 0) {
        ready = (g_igTexGenMatrixAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00133290();
done:
    return g_igTexGenMatrixAttr_metaObject;
}

int igTexGenMatrixAttr_GetVTable(void) {
    union U_133240 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&g_igTexGenMatrixAttr_vtable[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00133290(void)
{
    igMetaObject_RunStaticInit(igTexGenMatrixAttr_Register);
}

void igTexGenMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTexGenMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTexGenMatrixAttr_GetMetaObject,
        "igTexGenMatrixAttr",
        0x50, /* instance size */
        igTexGenMatrixAttr_GetVTable,
        &igTexGenMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTexGenMatrixAttr_GetMetaObject(void) {
    igTexGenMatrixAttr_GetMetaObject();
}

static FieldFactory g_igTexGenMatrixAttr_ctorTable[] = {
    igMatrix44fMetaField_CreateInstance,
    igIntMetaField_Create,
};
static const char *g_igTexGenMatrixAttr_fieldTable[] = {
    "m",
    "_unitID",
};
static igMetaField **g_igTexGenMatrixAttr_fieldHandles[] = {
    &g_igTexGenMatrixAttr_mMetaField,
    &g_igTexGenMatrixAttr_unitIDMetaField,
};
static int g_igTexGenMatrixAttr_fieldOffsets[] = {
    12,
    76,
};

void igTexGenMatrixAttr_InitFields(void) {
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;
    struct Fld *fld;

    temp_s0 = g_igTexGenMatrixAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTexGenMatrixAttr_ctorTable, 2);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    igMatrix44f_FromRows(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s1, &o1);
    fld = (Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    fld->f48 = (int)FUN_001404f0;
    igMetaObject_NameFields(temp_s0, g_igTexGenMatrixAttr_fieldTable, g_igTexGenMatrixAttr_fieldHandles, g_igTexGenMatrixAttr_fieldOffsets, temp_s2);
}

