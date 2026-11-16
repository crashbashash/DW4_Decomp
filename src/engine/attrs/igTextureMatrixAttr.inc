igMetaObject *g_igTextureMatrixAttr_metaObject;
igMetaField *g_igTextureMatrixAttr_mMetaField;
igMetaField *g_igTextureMatrixAttr_unitIDMetaField;
igMetaField *g_igTextureMatrixAttr_outputElementCountMetaField;
igMetaField *g_igTextureMatrixAttr_isProjectiveMetaField;

void FUN_001317c0(int arg0) {
    igTextureMatrixAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x55ECD8, arg0);
}

igMetaObject *FUN_00131800(void) {
    if (g_igTextureMatrixAttr_metaObject == 0) {
        g_igTextureMatrixAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureMatrixAttr_metaObject;
}

igMetaObject *igTextureMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureMatrixAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextureMatrixAttr_EnsureRegistered();
    return g_igTextureMatrixAttr_metaObject;
}

int igTextureMatrixAttr_GetVTable(void) {
    struct F_1318a0 f;

    igObject_InitHeader(&f);
    f.vt = &g_igTextureMatrixAttr_vtable[0];
    igMatrix44f_SetIdentity(&f.w[2]);
    return *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igTextureMatrixAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureMatrixAttr_Register);
}

void igTextureMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureMatrixAttr_GetMetaObject,
        "igTextureMatrixAttr",
        0x54, /* instance size */
        igTextureMatrixAttr_GetVTable,
        &igTextureMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureMatrixAttr_GetMetaObject(void) {
    igTextureMatrixAttr_GetMetaObject();
}

static FieldFactory g_igTextureMatrixAttr_ctorTable[] = {
    FUN_00188660,
    igIntMetaField_Create,
    igShortMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igTextureMatrixAttr_fieldTable[] = {
    "_m",
    "_unitID",
    "_outputElementCount",
    "_isProjective",
};
static igMetaField **g_igTextureMatrixAttr_fieldHandles[] = {
    &g_igTextureMatrixAttr_mMetaField,
    &g_igTextureMatrixAttr_unitIDMetaField,
    &g_igTextureMatrixAttr_outputElementCountMetaField,
    &g_igTextureMatrixAttr_isProjectiveMetaField,
};
static int g_igTextureMatrixAttr_fieldOffsets[] = {
    12,
    76,
    80,
    82,
};

void igTextureMatrixAttr_InitFields(void) {
    struct M o1;
    int temp_s2;
    struct V o2;
    struct V o3;
    struct Fld *fld;
    void *temp_s1;
    struct V o4;
    struct V o5;
    igMetaObject *temp_s0;

    temp_s0 = g_igTextureMatrixAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igTextureMatrixAttr_ctorTable, 4);
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
    FUN_00130e90(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s1, &o1);
    fld = (Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    fld->f48 = (int)FUN_00141520;
    igShortMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), -1);
    igMetaObject_NameFields(temp_s0, g_igTextureMatrixAttr_fieldTable, g_igTextureMatrixAttr_fieldHandles, g_igTextureMatrixAttr_fieldOffsets, temp_s2);
}

void **FUN_00131aa0(void **arg0, short arg1) {
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

void *igInfo_Destroy(struct S *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_igInfo_vtable[0];
        if (arg0 != 0) {
            arg0->f0 = &g_igNamedObject_vtable[0];
            if (&arg0->f8) {
                p = arg0->f8;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void *FUN_00131bc0(struct S_131bc0 *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_igNamedObject_vtable[0];
        if (&arg0->f8) {
            p = arg0->f8;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

int FUN_00131c50(void) {
    return g_igInfo_metaObject[0];
}

