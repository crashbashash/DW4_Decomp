igMetaObject *g_beNDMWShinkaObject_metaObject;
igMetaField *g_beNDMWShinkaObject_idMetaField;
igMetaField *g_beNDMWShinkaObject_nameMetaField;
igMetaField *g_beNDMWShinkaObject_levelMetaField;
igMetaField *g_beNDMWShinkaObject_hpMaxMetaField;
igMetaField *g_beNDMWShinkaObject_mpMaxMetaField;
igMetaField *g_beNDMWShinkaObject_tsuyosaMetaField;
igMetaField *g_beNDMWShinkaObject_mamoriMetaField;
igMetaField *g_beNDMWShinkaObject_kashikosaMetaField;
igMetaField *g_beNDMWShinkaObject_seishinMetaField;
igMetaField *g_beNDMWShinkaObject_subayasaMetaField;
igMetaField *g_beNDMWShinkaObject_bluntMetaField;
igMetaField *g_beNDMWShinkaObject_slashMetaField;
igMetaField *g_beNDMWShinkaObject_stabMetaField;
igMetaField *g_beNDMWShinkaObject_bashMetaField;
igMetaField *g_beNDMWShinkaObject_shotMetaField;
igMetaField *g_beNDMWShinkaObject_crushMetaField;
igMetaField *g_beNDMWShinkaObject_blastMetaField;
igMetaField *g_beNDMWShinkaObject_healMetaField;
igMetaField *g_beNDMWShinkaObject_forceMetaField;

void beNDMWShinkaObject_CreateInstance(int arg0) {
    beNDMWShinkaObject_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShinkaObject_metaObject, arg0);
}

igMetaObject *beNDMWShinkaObject_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWShinkaObject_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWShinkaObject_EnsureRegistered();
    return g_beNDMWShinkaObject_metaObject;
}

int beNDMWShinkaObject_GetVTable(void) {
    struct Obj_3c9a30 obj;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWShinkaObject_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShinkaObject_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void beNDMWShinkaObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaObject_Register);
}

void *beNDMWShinkaObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShinkaObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWShinkaObject_GetMetaObject,
        "beNDMWShinkaObject",
        0x54, /* instance size */
        beNDMWShinkaObject_GetVTable,
        beNDMWShinkaObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShinkaObject_GetMetaObject(void)
{
    beNDMWShinkaObject_ResolveMetaObject();
}

static FieldFactory g_beNDMWShinkaObject_ctorTable[] = {
    igIntMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWShinkaObject_fieldTable[] = {
    "_id",
    "_name",
    "_level",
    "_hpMax",
    "_mpMax",
    "_tsuyosa",
    "_mamori",
    "_kashikosa",
    "_seishin",
    "_subayasa",
    "_blunt",
    "_slash",
    "_stab",
    "_bash",
    "_shot",
    "_crush",
    "_blast",
    "_heal",
    "_force",
};
static igMetaField **g_beNDMWShinkaObject_fieldHandles[] = {
    &g_beNDMWShinkaObject_idMetaField,
    &g_beNDMWShinkaObject_nameMetaField,
    &g_beNDMWShinkaObject_levelMetaField,
    &g_beNDMWShinkaObject_hpMaxMetaField,
    &g_beNDMWShinkaObject_mpMaxMetaField,
    &g_beNDMWShinkaObject_tsuyosaMetaField,
    &g_beNDMWShinkaObject_mamoriMetaField,
    &g_beNDMWShinkaObject_kashikosaMetaField,
    &g_beNDMWShinkaObject_seishinMetaField,
    &g_beNDMWShinkaObject_subayasaMetaField,
    &g_beNDMWShinkaObject_bluntMetaField,
    &g_beNDMWShinkaObject_slashMetaField,
    &g_beNDMWShinkaObject_stabMetaField,
    &g_beNDMWShinkaObject_bashMetaField,
    &g_beNDMWShinkaObject_shotMetaField,
    &g_beNDMWShinkaObject_crushMetaField,
    &g_beNDMWShinkaObject_blastMetaField,
    &g_beNDMWShinkaObject_healMetaField,
    &g_beNDMWShinkaObject_forceMetaField,
};
static int g_beNDMWShinkaObject_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
};

void beNDMWShinkaObject_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShinkaObject_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShinkaObject_ctorTable, 0x13);
    igMetaObject_NameFields(temp_s0, g_beNDMWShinkaObject_fieldTable, g_beNDMWShinkaObject_fieldHandles, g_beNDMWShinkaObject_fieldOffsets, temp_s1);
}

