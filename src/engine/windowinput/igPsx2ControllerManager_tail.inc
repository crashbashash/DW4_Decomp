static const char *g_igPsx2ControllerManager_multitapPortNames[] = {
    "NONE", "PORT0", "PORT1", "ALL",
};
static int g_igPsx2ControllerManager_multitapPortValues[] = {
    0, 1, 2, 0xffff,
};
igMetaEnum *g_igPsx2ControllerManager_multitapPortMetaEnum;

igMetaEnum *FUN_00146d90(void) {
    if (g_igPsx2ControllerManager_multitapPortMetaEnum == 0) {
        g_igPsx2ControllerManager_multitapPortMetaEnum = igMetaEnum_Create("MultitapPort", g_igPsx2ControllerManager_multitapPortNames, g_igPsx2ControllerManager_multitapPortValues, 4);
    }
    return g_igPsx2ControllerManager_multitapPortMetaEnum;
}

igMetaObject *g_igPsx2ControllerManager_metaObject;
igMetaField *g_igPsx2ControllerManager_multitapMetaField;
igMetaField *g_igPsx2ControllerManager_validControllerManagerMetaField;
igMetaField *g_igPsx2ControllerManager_loadIRXsMetaField;

igMetaObject *igPsx2ControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ControllerManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146ee0();
    return g_igPsx2ControllerManager_metaObject;
}

int igPsx2ControllerManager_GetVTable(void) {
    union U_146e40 u;
    int temp_s0;
    S_ref *q1;
    
    
    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&DAT_00524f00[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&g_igPsx2ControllerManager_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.w[0] = (int)(&DAT_00524f00[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_00146ee0(void)
{
    igMetaObject_RunStaticInit(igPsx2ControllerManager_Register);
}

CallbackArray *igPsx2ControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2ControllerManager_metaObject,
        igControllerManager_Register,
        igControllerManager_GetPublishedMetaObject,
        thunk_igPsx2ControllerManager_GetMetaObject,
        "igPsx2ControllerManager",
        0x14, /* instance size */
        igPsx2ControllerManager_GetVTable,
        &igPsx2ControllerManager_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_00146f60(void) {
    return g_igControllerManager_metaObject;
}

static FieldFactory g_igPsx2ControllerManager_ctorTable[] = {
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igPsx2ControllerManager_fieldTable[] = {
    "_multitap",
    "_validControllerManager",
    "_loadIRXs",
};
static igMetaField **g_igPsx2ControllerManager_fieldHandles[] = {
    &g_igPsx2ControllerManager_multitapMetaField,
    &g_igPsx2ControllerManager_validControllerManagerMetaField,
    &g_igPsx2ControllerManager_loadIRXsMetaField,
};
static int g_igPsx2ControllerManager_fieldOffsets[] = {
    12,
    16,
    17,
};

void igPsx2ControllerManager_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    igMetaObject *temp_s0;

    temp_s0 = g_igPsx2ControllerManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igPsx2ControllerManager_ctorTable, 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00146d90);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igPsx2ControllerManager_fieldTable, g_igPsx2ControllerManager_fieldHandles, g_igPsx2ControllerManager_fieldOffsets, temp_s2);
}

