igMetaObject *g_igAppearance_metaObject;
igMetaField *g_igAppearance_skinMetaField;
igMetaField *g_igAppearance_attachedSkinsMetaField;
igMetaField *g_igAppearance_attachedGraphsMetaField;
igMetaField *g_igAppearance_segmentOverrideNameListMetaField;
igMetaField *g_igAppearance_segmentOverrideGraphListMetaField;

igMetaObject *FUN_001a6150(void) {
    if (g_igAppearance_metaObject == 0) {
        g_igAppearance_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAppearance_metaObject;
}

igMetaObject *igAppearance_GetMetaObject(void)
{
    igMetaObject *g = g_igAppearance_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a6450();
    return g_igAppearance_metaObject;
}

int igAppearance_GetVTable(void) {
    struct Obj_1a61f0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0052a090[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052a090[0];
    FUN_001958f0((void * *)&obj.w7, -1);
    igSmartPointer_igStringObjList_Destruct((void * *)&obj.w6, -1);
    FUN_001a63d0((void * *)&obj.w5, -1);
    FUN_001a6350((struct Ref * *)&obj.w4, -1);
    FUN_001a62d0((void * *)&obj.w3, -1);
    FUN_00131bc0(&obj, 0);
    return t;
}

void **FUN_001a62d0(void **arg0, short arg1) {
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

void **FUN_001a6350(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_001a63d0(void **arg0, long long arg1) {
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

void FUN_001a6450(void)
{
    igMetaObject_RunStaticInit(igAppearance_Register);
}

static igMetaObjectCallback g_igAppearance_callbackList[] = { FUN_00198290, FUN_00197f40, FUN_0019d360, igStringObjList_EnsureRegistered, FUN_0019ccc0, 0 };

void igAppearance_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAppearance_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAppearance_GetMetaObject,
        "igAppearance",
        0x20, /* instance size */
        igAppearance_GetVTable,
        &igAppearance_InitFields,
        0, /* extra callback item */
        g_igAppearance_callbackList /* callback list */
    );
}

void thunk_igAppearance_GetMetaObject(void) {
    igAppearance_GetMetaObject();
}

static FieldFactory g_igAppearance_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igAppearance_fieldTable[] = {
    "_skin",
    "_attachedSkins",
    "_attachedGraphs",
    "_segmentOverrideNameList",
    "_segmentOverrideGraphList",
};
static igMetaField **g_igAppearance_fieldHandles[] = {
    &g_igAppearance_skinMetaField,
    &g_igAppearance_attachedSkinsMetaField,
    &g_igAppearance_attachedGraphsMetaField,
    &g_igAppearance_segmentOverrideNameListMetaField,
    &g_igAppearance_segmentOverrideGraphListMetaField,
};
static int g_igAppearance_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
};

void igAppearance_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;

    temp_s1 = (void *)g_igAppearance_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igAppearance_ctorTable, 5);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00197fd0();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00197e60();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0019d280();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igStringObjList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_0019cbe0();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igAppearance_fieldTable, g_igAppearance_fieldHandles, g_igAppearance_fieldOffsets, temp_s0);
}

