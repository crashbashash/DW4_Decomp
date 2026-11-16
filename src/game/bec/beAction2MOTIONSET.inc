igMetaObject *g_beAction2MOTIONSET_metaObject;
igMetaField *g_beAction2MOTIONSET_hokanModeMetaField;
igMetaField *g_beAction2MOTIONSET_hokanTimeMetaField;
igMetaField *g_beAction2MOTIONSET_loopModeMetaField;

void *beAction2MOTIONSET_GetMetaObject(void) {
    unsigned char b;
    if (g_beAction2MOTIONSET_metaObject != 0) {
        b = (g_beAction2MOTIONSET_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beAction2MOTIONSET_EnsureRegistered();
done:
    return g_beAction2MOTIONSET_metaObject;
}

int beAction2MOTIONSET_GetVTable(void) {
    union U_36d630 u;
    int temp_s0;
    char *q0;
    char *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q2 = &u.b[8];
    *(int *)q2 = 0;
    u.vt = (int)&g_beAction2MOTIONSET_vtable[0];
    q1 = &u.b[12];
    *(int *)q1 = 0;
    q0 = &u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beAction2MOTIONSET_vtable[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q2 != 0) {
        temp_v1 = *(int **)q2;
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

void beAction2MOTIONSET_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2MOTIONSET_Register);
}

void *beAction2MOTIONSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2MOTIONSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2MOTIONSET_GetMetaObjectFunction,
        "beAction2MOTIONSET",
        0x18, /* instance size */
        beAction2MOTIONSET_GetVTable,
        beAction2MOTIONSET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2MOTIONSET_GetMetaObjectFunction(void)
{
    beAction2MOTIONSET_GetMetaObject();
}

static FieldFactory g_beAction2MOTIONSET_ctorTable[] = {
    igStringMetaField_Create,
    igFloatMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beAction2MOTIONSET_fieldTable[] = {
    "_hokanMode",
    "_hokanTime",
    "_loopMode",
};
static igMetaField **g_beAction2MOTIONSET_fieldHandles[] = {
    &g_beAction2MOTIONSET_hokanModeMetaField,
    &g_beAction2MOTIONSET_hokanTimeMetaField,
    &g_beAction2MOTIONSET_loopModeMetaField,
};
static int g_beAction2MOTIONSET_fieldOffsets[] = {
    12,
    16,
    20,
};

void beAction2MOTIONSET_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beAction2MOTIONSET_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAction2MOTIONSET_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beAction2MOTIONSET_fieldTable, g_beAction2MOTIONSET_fieldHandles, g_beAction2MOTIONSET_fieldOffsets, base);
}

