igMetaObject *g_beModelCtrlSCEffect_metaObject;
igMetaField *g_beModelCtrlSCEffect_geneRamNoMetaField;
igMetaField *g_beModelCtrlSCEffect_modelNameMetaField;
igMetaField *g_beModelCtrlSCEffect_seqNameMetaField;
igMetaField *g_beModelCtrlSCEffect_offsetMetaField;
igMetaField *g_beModelCtrlSCEffect_rotationMetaField;
igMetaField *g_beModelCtrlSCEffect_isSeqDeadMetaField;
igMetaField *g_beModelCtrlSCEffect_isPositionLockMetaField;

void beModelCtrlSCEffect_Create(int arg0) {
    beModelCtrlSCEffect_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588800, arg0);
}

void *beModelCtrlSCEffect_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlSCEffect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlSCEffect_EnsureRegistered();
    }
    return g_beModelCtrlSCEffect_metaObject;
}

int beModelCtrlSCEffect_GetVTable(void) {
    beModelCtrlSCEffect obj;
    char *o;
    int *a1;
    int v0;
    int t;
    int *p0, *p1;

    igObject_InitHeader(&obj);
    p0 = &obj._modelName;
    p1 = &obj._seqName;
    obj._vtable = (int)&g_beModelCtrlSCEffect_vtable[0];
    *p0 = 0;
    *p1 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beModelCtrlSCEffect_vtable[0];
    if (p1 != 0) {
        o = (char *)*p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p0 != 0) {
        o = (char *)*p0;
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

void beModelCtrlSCEffect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCEffect_Register);
}

void *beModelCtrlSCEffect_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlSCEffect_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCEffect_GetMetaObjectFunction,
        "beModelCtrlSCEffect",
        0x3c, /* instance size */
        beModelCtrlSCEffect_GetVTable,
        beModelCtrlSCEffect_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCEffect_GetMetaObjectFunction(void)
{
    beModelCtrlSCEffect_GetMetaObject();
}

static FieldFactory g_beModelCtrlSCEffect_ctorTable[] = {
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    FUN_00187890,
    FUN_00187890,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beModelCtrlSCEffect_fieldTable[] = {
    "_geneRamNo",
    "_modelName",
    "_seqName",
    "_offset",
    "_rotation",
    "_isSeqDead",
    "_isPositionLock",
};
static igMetaField **g_beModelCtrlSCEffect_fieldHandles[] = {
    &g_beModelCtrlSCEffect_geneRamNoMetaField,
    &g_beModelCtrlSCEffect_modelNameMetaField,
    &g_beModelCtrlSCEffect_seqNameMetaField,
    &g_beModelCtrlSCEffect_offsetMetaField,
    &g_beModelCtrlSCEffect_rotationMetaField,
    &g_beModelCtrlSCEffect_isSeqDeadMetaField,
    &g_beModelCtrlSCEffect_isPositionLockMetaField,
};
static int g_beModelCtrlSCEffect_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    44,
    56,
    57,
};

void beModelCtrlSCEffect_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlSCEffect_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlSCEffect_ctorTable, 7);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), -1);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlSCEffect_fieldTable, g_beModelCtrlSCEffect_fieldHandles, g_beModelCtrlSCEffect_fieldOffsets, temp_s1);
}

