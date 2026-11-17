igMetaObject *g_igPsx2Window_metaObject;
igMetaField *g_igPsx2Window_widthMetaField;
igMetaField *g_igPsx2Window_heightMetaField;
igMetaField *g_igPsx2Window_originXMetaField;
igMetaField *g_igPsx2Window_originYMetaField;
igMetaField *g_igPsx2Window_vcMetaField;
igMetaField *g_igPsx2Window_controllerEnabledMetaField;
igMetaField *g_igPsx2Window_winNameMetaField;
igMetaField *g_igPsx2Window_renderDestinationHandleMetaField;
igMetaField *g_igPsx2Window_openMetaField;
igMetaField *g_igPsx2Window_bppMetaField;
igMetaField *g_igPsx2Window_alphaMetaField;
igMetaField *g_igPsx2Window_bppDepthMetaField;

igMetaObject *FUN_00146a60(void)
{
    igMetaObject *meta = g_igPsx2Window_metaObject;
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_00146b80();
end:
    return g_igPsx2Window_metaObject;
}

int igPsx2Window_GetVTable(void) {
    union U_146ab0 u;
    int temp_s0;
    char *q0;
    S_ref *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igPsx2Window_vtable[0];
    q1 = (S_ref *)&u.b[24];
    *(int *)q1 = 0;
    q0 = &u.b[32];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.vt = (int)&g_igPsx2Window_vtable[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (StringTokenHeader *)temp_a1);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    return temp_s0;
}

void FUN_00146b80(void)
{
    igMetaObject_RunStaticInit(igPsx2Window_Register);
}

static igMetaObjectCallback g_igPsx2Window_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igPsx2Window_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2Window_metaObject,
        igWindow_Register,
        igWindow_GetPublishedMetaObject,
        thunk_FUN_00146a60,
        "igPsx2Window",
        sizeof(igPsx2Window),                     /* Instance size. */
        igPsx2Window_GetVTable,
        &igPsx2Window_InitFields,
        0, /* extra callback item */
        g_igPsx2Window_callbackList /* callback list */
    );
}

igMetaObject *FUN_00146c10(void) {
    return g_igWindow_metaObject;
}

static FieldFactory g_igPsx2Window_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igPsx2Window_fieldTable[] = {
    "_width",
    "_height",
    "_originX",
    "_originY",
    "_vc",
    "_controllerEnabled",
    "_winName",
    "_renderDestinationHandle",
    "_open",
    "_bpp",
    "_alpha",
    "_bppDepth",
};
static igMetaField **g_igPsx2Window_fieldHandles[] = {
    &g_igPsx2Window_widthMetaField,
    &g_igPsx2Window_heightMetaField,
    &g_igPsx2Window_originXMetaField,
    &g_igPsx2Window_originYMetaField,
    &g_igPsx2Window_vcMetaField,
    &g_igPsx2Window_controllerEnabledMetaField,
    &g_igPsx2Window_winNameMetaField,
    &g_igPsx2Window_renderDestinationHandleMetaField,
    &g_igPsx2Window_openMetaField,
    &g_igPsx2Window_bppMetaField,
    &g_igPsx2Window_alphaMetaField,
    &g_igPsx2Window_bppDepthMetaField,
};
static int g_igPsx2Window_fieldOffsets[] = {
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
};

void igPsx2Window_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igPsx2Window_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igPsx2Window_ctorTable, 0xC);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2), 0x280);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1), 0x1C0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1) + 56) = (int)igVisualContext_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 5), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6), 0);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 9), 0x18);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 0xA), 8);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 0xB), 0x20);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igPsx2Window_fieldTable, g_igPsx2Window_fieldHandles, g_igPsx2Window_fieldOffsets, temp_s2);
    *(int *)((char *)(g_igPsx2Window_metaObject) + 64) = (int)thunk_igWindow_GetMetaObject;
}

