igMetaObject *g_beModelCtrlSCSound_metaObject;
igMetaField *g_beModelCtrlSCSound_sndNameMetaField;
igMetaField *g_beModelCtrlSCSound_sndHandleMetaField;

void beModelCtrlSCSound_Create(int arg0) {
    beModelCtrlSCSound_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5887B0, arg0);
}

igMetaObject *beModelCtrlSCSound_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlSCSound_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beModelCtrlSCSound_EnsureRegistered();
done:
    return g_beModelCtrlSCSound_metaObject;
}

int beModelCtrlSCSound_GetVTable(void) {
    union U_34f530 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beModelCtrlSCSound_vtable[0];
    ps = &u.b[20];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beModelCtrlSCSound_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beModelCtrlSCSound_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCSound_Register);
}

void *beModelCtrlSCSound_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlSCSound_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCSound_GetMetaObjectFunction,
        "beModelCtrlSCSound",
        0x20, /* instance size */
        beModelCtrlSCSound_GetVTable,
        beModelCtrlSCSound_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCSound_GetMetaObjectFunction(void)
{
    beModelCtrlSCSound_GetMetaObject();
}

igMetaObject *beModelCtrlSubComBase_GetPublishedMetaObject(void) {
    return g_beModelCtrlSubComBase_metaObject;
}

static FieldFactory g_beModelCtrlSCSound_ctorTable[] = {
    igStringMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beModelCtrlSCSound_fieldTable[] = {
    "_sndName",
    "_sndHandle",
};
static igMetaField **g_beModelCtrlSCSound_fieldHandles[] = {
    &g_beModelCtrlSCSound_sndNameMetaField,
    &g_beModelCtrlSCSound_sndHandleMetaField,
};
static int g_beModelCtrlSCSound_fieldOffsets[] = {
    20,
    24,
};

void beModelCtrlSCSound_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlSCSound_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlSCSound_ctorTable, 2);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlSCSound_fieldTable, g_beModelCtrlSCSound_fieldHandles, g_beModelCtrlSCSound_fieldOffsets, temp_s1);
}

