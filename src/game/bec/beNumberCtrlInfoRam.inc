igMetaObject *g_beNumberCtrlInfoRam_metaObject;
igMetaField *g_beNumberCtrlInfoRam_geometryMetaField;
igMetaField *g_beNumberCtrlInfoRam_offsetNextMetaField;
igMetaField *g_beNumberCtrlInfoRam_maxValueMetaField;
igMetaField *g_beNumberCtrlInfoRam_modeMetaField;
igMetaField *g_beNumberCtrlInfoRam_numListMetaField;
igMetaField *g_beNumberCtrlInfoRam_workMetaField;

igMetaObject *beNumberCtrlInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beNumberCtrlInfoRam_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNumberCtrlInfoRam_EnsureRegistered();
done:
    return g_beNumberCtrlInfoRam_metaObject;
}

int beNumberCtrlInfoRam_GetVTable(void) {
    struct W_34d590 o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[9] = 0;
    o.vt = &g_beNumberCtrlInfoRam_vtable[0];
    p16 = &o.f[10];
    *p16 = 0;
    p17 = &o.f[14];
    *p17 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNumberCtrlInfoRam_vtable[0];
    igSmartPointer_beNumberCtrlInfoWork_Destruct((void **)(&o.f[15]), -1);
    FUN_0034d640((void **)p17, (long long)(-1));
    FUN_001971e0(p16, -1);
    FUN_0033e920((S *)&o, (long long)0);
    return r;
}

void **FUN_0034d640(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_beNumberCtrlInfoWork_Destruct(void **arg0, int arg1) {
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

void beNumberCtrlInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoRam_Register);
}

static igMetaObjectCallback g_beNumberCtrlInfoRam_callbackList[] = { igGeometry_EnsureRegistered, beNumVerDataList_EnsureRegistered, beNumberCtrlInfoWork_EnsureRegistered, 0 };

void *beNumberCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNumberCtrlInfoRam_GetMetaObjectFunction,
        "beNumberCtrlInfoRam",
        0x44, /* instance size */
        beNumberCtrlInfoRam_GetVTable,
        beNumberCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beNumberCtrlInfoRam_callbackList /* callback list */
    );
}

void beNumberCtrlInfoRam_GetMetaObjectFunction(void)
{
    beNumberCtrlInfoRam_GetMetaObject();
}

static FieldFactory g_beNumberCtrlInfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNumberCtrlInfoRam_fieldTable[] = {
    "_geometry",
    "_offsetNext",
    "_maxValue",
    "_mode",
    "_numList",
    "_work",
};
static igMetaField **g_beNumberCtrlInfoRam_fieldHandles[] = {
    &g_beNumberCtrlInfoRam_geometryMetaField,
    &g_beNumberCtrlInfoRam_offsetNextMetaField,
    &g_beNumberCtrlInfoRam_maxValueMetaField,
    &g_beNumberCtrlInfoRam_modeMetaField,
    &g_beNumberCtrlInfoRam_numListMetaField,
    &g_beNumberCtrlInfoRam_workMetaField,
};
static int g_beNumberCtrlInfoRam_fieldOffsets[] = {
    44,
    48,
    52,
    56,
    60,
    64,
};

void beNumberCtrlInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beNumberCtrlInfoRam_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNumberCtrlInfoRam_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = igGeometry_GetOrCreateMetaObject();
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0.09375f);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1_2) + 56) = (int)beNumVerDataList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1_2) + 52) = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    *(int *)((char *)(temp_s1_3) + 56) = (int)beNumberCtrlInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNumberCtrlInfoRam_fieldTable, g_beNumberCtrlInfoRam_fieldHandles, g_beNumberCtrlInfoRam_fieldOffsets, temp_s2);
}

