igMetaObject *g_igSorter_metaObject;
igMetaField *g_igSorter_dlistMetaField;
igMetaField *g_igSorter_modeMetaField;
igMetaField *g_igSorter_renderPackagePoolMetaField;
igMetaField *g_igSorter_tmpAttrsMetaField;
igMetaField *g_igSorter_transpPackagesMetaField;
igMetaField *g_igSorter_opaquePackagesMetaField;
igMetaField *g_igSorter_firstPackagesMetaField;
igMetaField *g_igSorter_lightAttrsMetaField;
igMetaField *g_igSorter_firstAttrsMetaField;
igMetaField *g_igSorter_transpAttrsMetaField;
igMetaField *g_igSorter_opaqueAttrsMetaField;
igMetaField *g_igSorter_firstPackageIndicesMetaField;
igMetaField *g_igSorter_transpPackageIndicesMetaField;
igMetaField *g_igSorter_opaquePackageIndicesMetaField;
igMetaField *g_igSorter_depthWriteDisableMetaField;
igMetaField *g_igSorter_cullFaceFrontMetaField;
igMetaField *g_igSorter_cullFaceBackMetaField;
igMetaField *g_igSorter_transparencyDrawModeMetaField;
igMetaField *g_igSorter_emptyRenderPackageMetaField;
igMetaField *g_igSorter_emptyRenderPackageListMetaField;
igMetaField *g_igSorter_emptyRenderPackageIndicesMetaField;
igMetaField *g_igSorter_lastEmptyRenderPackageAttrsMetaField;
igMetaField *g_igSorter_firstEmptyRenderPackageAttrsMetaField;
igMetaField *g_igSorter_emptyGeometryMetaField;
igMetaField *g_igSorter_curListMetaField;
igMetaField *g_igSorter_prevListMetaField;
igMetaField *g_igSorter_isCompoundPackageOpenMetaField;
igMetaField *g_igSorter_isCompoundPackageTransparentMetaField;
igMetaField *g_igSorter_isCompoundPackageFirstMetaField;
igMetaField *g_igSorter_compoundPackageMetaField;
igMetaField *g_igSorter_compoundPackageNestCountMetaField;
igMetaField *g_igSorter_cachedPackageMetaField;
igMetaField *g_igSorter_outputCreatedMetaField;
igMetaField *g_igSorter_useZSortMetaField;
igMetaField *g_igSorter_forceNoSeparateMetaField;
igMetaField *g_igSorter_printOutputStateMetaField;

igMetaObject *FUN_00196c10(void) {
    if (g_igSorter_metaObject == 0) {
        g_igSorter_metaObject = ((igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0])));
    }
    return g_igSorter_metaObject;
}

igMetaObject *igSorter_GetMetaObject(void)
{
    igMetaObject *g = g_igSorter_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00197360();
    return g_igSorter_metaObject;
}

int igSorter_GetVTable(void) {
    union U_196c10 u;
    int temp_s5;
    char *p276, *p268, *p264, *p260, *p256, *p252, *p248, *p244, *p240;
    igObject_InitHeader(u.b);
    u.vt = (int)&g_igSorter_vtable[0];
    FUN_00197350((int *)&u.b[8]);
    FUN_00197340((int *)&u.b[16]);
    FUN_00197330((int *)&u.b[20]);
    FUN_00197320((int *)&u.b[24]);
    FUN_00197320((int *)&u.b[28]);
    FUN_00197320((int *)&u.b[32]);
    FUN_00197350((int *)&u.b[36]);
    FUN_00197350((int *)&u.b[40]);
    FUN_00197350((int *)&u.b[44]);
    FUN_00197350((int *)&u.b[48]);
    igSmartPointer_igIntList_Construct(&u.b[52]);
    igSmartPointer_igIntList_Construct(&u.b[56]);
    igSmartPointer_igIntList_Construct(&u.b[60]);
    FUN_00197310((int *)&u.b[64]);
    FUN_00197300((int *)&u.b[68]);
    FUN_00197300((int *)&u.b[72]);
    p240 = &u.b[80];
    FUN_001972f0((int *)p240);
    p244 = &u.b[84];
    FUN_00197320((int *)p244);
    p248 = &u.b[88];
    igSmartPointer_igIntList_Construct(p248);
    p252 = &u.b[92];
    FUN_00197350((int *)p252);
    p256 = &u.b[96];
    FUN_00197350((int *)p256);
    p260 = &u.b[100];
    FUN_001972e0((int *)p260);
    p264 = &u.b[104];
    igSmartPointer_igIntList_Construct(p264);
    p268 = &u.b[108];
    igSmartPointer_igIntList_Construct(p268);
    p276 = &u.b[116];
    FUN_001972f0((int *)p276);
    temp_s5 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00528620[4];
    FUN_00197260((void **)p276, -1);
    igSmartPointer_igIntList_Destruct(p268, -1);
    igSmartPointer_igIntList_Destruct(p264, -1);
    FUN_001971e0((O *)p260, -1);
    FUN_00197160((void **)p256, -1);
    FUN_00197160((void **)p252, -1);
    igSmartPointer_igIntList_Destruct(p248, -1);
    FUN_001970e0((struct Ref **)p244, -1);
    FUN_00197260((void **)p240, -1);
    FUN_00197060((void **)&u.b[72], -1);
    FUN_00197060((void **)&u.b[68], -1);
    FUN_00196fe0((void **)&u.b[64], -1);
    igSmartPointer_igIntList_Destruct(&u.b[60], -1);
    igSmartPointer_igIntList_Destruct(&u.b[56], -1);
    igSmartPointer_igIntList_Destruct(&u.b[52], -1);
    FUN_00197160((void **)&u.b[48], -1);
    FUN_00197160((void **)&u.b[44], -1);
    FUN_00197160((void **)&u.b[40], -1);
    FUN_00197160((void **)&u.b[36], -1);
    FUN_001970e0((struct Ref **)&u.b[32], -1);
    FUN_001970e0((struct Ref **)&u.b[28], -1);
    FUN_001970e0((struct Ref **)&u.b[24], -1);
    FUN_001380e0(&u.b[20], -1);
    FUN_00196f60((void **)&u.b[16], -1);
    FUN_00197160((void **)&u.b[8], -1);
    return temp_s5;
}

void **FUN_00196f60(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00196fe0(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00197060(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001970e0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy((void *)p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_00197160(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_001971e0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((void *)t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void **FUN_00197260(void **arg0, long long arg1) {
    char *o;
    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

int *FUN_001972e0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_001972f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00197300(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00197310(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00197320(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00197330(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00197340(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00197350(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_00197360(void)
{
    igMetaObject_RunStaticInit(igSorter_Register);
}

static igMetaObjectCallback g_igSorter_callbackList[] = { FUN_00138160, FUN_00197a10, igNonRefCountedAttrList_EnsureRegistered, FUN_001978a0, igIntList_EnsureRegistered, igDepthWriteStateAttr_EnsureRegistered, igCullFaceAttr_EnsureRegistered, FUN_00197cc0, igGeometry_EnsureRegistered, 0 };

void igSorter_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSorter_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igSorter_GetMetaObject,
        "igSorter",
        0x84, /* instance size */
        igSorter_GetVTable,
        &igSorter_InitFields,
        0, /* extra callback item */
        g_igSorter_callbackList /* callback list */
    );
}

void thunk_igSorter_GetMetaObject(void) {
    igSorter_GetMetaObject();
}

static FieldFactory g_igSorter_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igSorter_fieldTable[] = {
    "_dlist",
    "_mode",
    "_renderPackagePool",
    "_tmpAttrs",
    "_transpPackages",
    "_opaquePackages",
    "_firstPackages",
    "_lightAttrs",
    "_firstAttrs",
    "_transpAttrs",
    "_opaqueAttrs",
    "_firstPackageIndices",
    "_transpPackageIndices",
    "_opaquePackageIndices",
    "_depthWriteDisable",
    "_cullFaceFront",
    "_cullFaceBack",
    "_transparencyDrawMode",
    "_emptyRenderPackage",
    "_emptyRenderPackageList",
    "_emptyRenderPackageIndices",
    "_lastEmptyRenderPackageAttrs",
    "_firstEmptyRenderPackageAttrs",
    "_emptyGeometry",
    "_curList",
    "_prevList",
    "_isCompoundPackageOpen",
    "_isCompoundPackageTransparent",
    "_isCompoundPackageFirst",
    "_compoundPackage",
    "_compoundPackageNestCount",
    "_cachedPackage",
    "_outputCreated",
    "_useZSort",
    "_forceNoSeparate",
    "_printOutputState",
};
static igMetaField **g_igSorter_fieldHandles[] = {
    &g_igSorter_dlistMetaField,
    &g_igSorter_modeMetaField,
    &g_igSorter_renderPackagePoolMetaField,
    &g_igSorter_tmpAttrsMetaField,
    &g_igSorter_transpPackagesMetaField,
    &g_igSorter_opaquePackagesMetaField,
    &g_igSorter_firstPackagesMetaField,
    &g_igSorter_lightAttrsMetaField,
    &g_igSorter_firstAttrsMetaField,
    &g_igSorter_transpAttrsMetaField,
    &g_igSorter_opaqueAttrsMetaField,
    &g_igSorter_firstPackageIndicesMetaField,
    &g_igSorter_transpPackageIndicesMetaField,
    &g_igSorter_opaquePackageIndicesMetaField,
    &g_igSorter_depthWriteDisableMetaField,
    &g_igSorter_cullFaceFrontMetaField,
    &g_igSorter_cullFaceBackMetaField,
    &g_igSorter_transparencyDrawModeMetaField,
    &g_igSorter_emptyRenderPackageMetaField,
    &g_igSorter_emptyRenderPackageListMetaField,
    &g_igSorter_emptyRenderPackageIndicesMetaField,
    &g_igSorter_lastEmptyRenderPackageAttrsMetaField,
    &g_igSorter_firstEmptyRenderPackageAttrsMetaField,
    &g_igSorter_emptyGeometryMetaField,
    &g_igSorter_curListMetaField,
    &g_igSorter_prevListMetaField,
    &g_igSorter_isCompoundPackageOpenMetaField,
    &g_igSorter_isCompoundPackageTransparentMetaField,
    &g_igSorter_isCompoundPackageFirstMetaField,
    &g_igSorter_compoundPackageMetaField,
    &g_igSorter_compoundPackageNestCountMetaField,
    &g_igSorter_cachedPackageMetaField,
    &g_igSorter_outputCreatedMetaField,
    &g_igSorter_useZSortMetaField,
    &g_igSorter_forceNoSeparateMetaField,
    &g_igSorter_printOutputStateMetaField,
};
static int g_igSorter_fieldOffsets[] = {
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
    84,
    88,
    92,
    96,
    100,
    104,
    108,
    112,
    113,
    114,
    116,
    120,
    124,
    128,
    129,
    130,
    131,
};

void igSorter_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_14;
    void *temp_s2_15;
    void *temp_s2_16;
    void *temp_s2_17;
    void *temp_s2_18;
    void *temp_s2_19;
    void *temp_s2_20;
    void *temp_s2_21;
    void *temp_s2_22;
    void *temp_s2_23;
    void *temp_s2_24;
    void *temp_s2_25;
    void *temp_s2_26;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = (void *)g_igSorter_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSorter_ctorTable, 0x24);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00137fb0();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00197930();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013ad40();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_001977c0();
    ((igObjectRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_001977c0();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_001977c0();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00137fb0();
    ((igObjectRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_00137fb0();
    ((igObjectRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_00137fb0();
    ((igObjectRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA)));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_00137fb0();
    ((igObjectRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE)));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_001382a0();
    ((igObjectRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF)));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = FUN_001386d0();
    ((igObjectRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10)));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_001386d0();
    ((igObjectRefMetaField *)temp_s2_16)->_construct = 1;
    temp_s2_17 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = (int)FUN_00197af0();
    ((igObjectRefMetaField *)temp_s2_17)->_construct = 1;
    temp_s2_18 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13)));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = (int)FUN_001977c0();
    ((igObjectRefMetaField *)temp_s2_18)->_construct = 1;
    temp_s2_19 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14)));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_19)->_construct = 1;
    temp_s2_20 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15)));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = FUN_00137fb0();
    ((igObjectRefMetaField *)temp_s2_20)->_construct = 1;
    temp_s2_21 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x16)));
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = FUN_00137fb0();
    ((igObjectRefMetaField *)temp_s2_21)->_construct = 1;
    temp_s2_22 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x17)));
    ((igObjectRefMetaField *)temp_s2_22)->_metaObject = (int)igGeometry_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_22)->_construct = 1;
    temp_s2_23 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x18)));
    ((igObjectRefMetaField *)temp_s2_23)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_23)->_construct = 1;
    temp_s2_24 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19)));
    ((igObjectRefMetaField *)temp_s2_24)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_24)->_construct = 1;
    temp_s2_25 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1D)));
    ((igObjectRefMetaField *)temp_s2_25)->_metaObject = (int)FUN_00197af0();
    temp_s2_26 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1F)));
    ((igObjectRefMetaField *)temp_s2_26)->_metaObject = (int)FUN_00197af0();
    ((igObjectRefMetaField *)temp_s2_26)->_refCounted = 0;
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x23))) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSorter_fieldTable, g_igSorter_fieldHandles, g_igSorter_fieldOffsets, temp_s1);
}

