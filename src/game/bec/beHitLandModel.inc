igMetaObject *g_beHitLandModel_metaObject;
igMetaField *g_beHitLandModel_orderMetaField;
igMetaField *g_beHitLandModel_hitTraversalMetaField;
igMetaField *g_beHitLandModel_probeMetaField;
igMetaField *g_beHitLandModel_isHitWallMetaField;
igMetaField *g_beHitLandModel_mat90MetaField;

void beHitLandModel_CreateInstance(int arg0) {
    FUN_0035da30();
    igMetaObject_CreateInstance(*(int *)0x589350, arg0);
}

igMetaObject *FUN_0035d7c0(void) {
    if (g_beHitLandModel_metaObject == 0) {
        g_beHitLandModel_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beHitLandModel_metaObject;
}

void *FUN_0035d810(void) {
    igMetaObject *g = g_beHitLandModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035da30();
    }
    return g_beHitLandModel_metaObject;
}

int beHitLandModel_GetVTable(void) {
    HitLandModelView model;
    return *(int *)((char *)&model + *(int *)((char *)g_objectSystem[0] + 916));
}

void **FUN_0035d930(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0035d9b0(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0035da30(void)
{
    igMetaObject_RunStaticInit(beHitLandModel_Register);
}

static igMetaObjectCallback g_beHitLandModel_callbackList[] = { FUN_0035e090, FUN_0035dd30, FUN_0019e890, 0 };

void *beHitLandModel_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModel_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beHitLandModel_GetMetaObject,
        "beHitLandModel",
        0x70, /* instance size */
        beHitLandModel_GetVTable,
        beHitLandModel_InitFields,
        0, /* extra callback item */
        g_beHitLandModel_callbackList /* callback list */
    );
}

void beHitLandModel_GetMetaObject(void)
{
    FUN_0035d810();
}

static FieldFactory g_beHitLandModel_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    FUN_00188660,
};
static const char *g_beHitLandModel_fieldTable[] = {
    "_order",
    "_hitTraversal",
    "_probe",
    "_isHitWall",
    "_mat90",
};
static igMetaField **g_beHitLandModel_fieldHandles[] = {
    &g_beHitLandModel_orderMetaField,
    &g_beHitLandModel_hitTraversalMetaField,
    &g_beHitLandModel_probeMetaField,
    &g_beHitLandModel_isHitWallMetaField,
    &g_beHitLandModel_mat90MetaField,
};
static int g_beHitLandModel_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
};

void beHitLandModel_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beHitLandModel_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beHitLandModel_ctorTable, 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0035ded0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0035dc10();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0019e6c0();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    igMetaObject_NameFields(temp_s0, g_beHitLandModel_fieldTable, g_beHitLandModel_fieldHandles, g_beHitLandModel_fieldOffsets, temp_s2);
}

