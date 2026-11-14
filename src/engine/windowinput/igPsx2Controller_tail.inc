int FUN_00147030(void) {
    if (DAT_0055f758[0] == 0) {
        DAT_0055f758[0] = igMetaEnum_Create(&text_ControllerPhase[0], &DAT_00487580[0], &DAT_004875a0[0], 8);
    }
    return DAT_0055f758[0];
}

int FUN_00147090(int arg0) {
    FUN_001471b0();
    return igMetaObject_CreateInstance(*(int *)0x55F760, arg0);
}

igMetaObject *igPsx2Controller_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Controller_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001471b0();
    return g_igPsx2Controller_metaObject[0];
}

int igPsx2Controller_GetVTable(void) {
    union U_147120 u;
    void **q8;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q8 = &u.p[8];
    u.w[0] = (int)(&DAT_00524d00[0]);
    *q8 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00524d00[0]);
    if (q8 != 0) {
        temp_a0 = *q8;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_001471b0(void)
{
    igMetaObject_RunStaticInit(igPsx2Controller_Register);
}

void igPsx2Controller_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Controller_metaObject,
        igController_Register,
        igController_GetPublishedMetaObject,
        thunk_igPsx2Controller_GetMetaObject,
        igPsx2Controller_className,
        0x70, /* instance size */
        igPsx2Controller_GetVTable,
        &igPsx2Controller_InitFields,
        0, /* extra callback item */
        g_igPsx2Controller_callbackList /* callback list */
    );
}

igMetaObject *FUN_00147240(void) {
    return g_igController_metaObject[0];
}

void igPsx2Controller_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_s0;

    temp_s0 = (void *)g_igPsx2Controller_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2Controller_ctorTable[0], 0x18);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 0x10);
    igUnsignedShortMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 2);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    *(int *)((char *)(temp_s2) + 56) = (int)FUN_00145d40();
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6); q->f52 = 2; }
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7); q->f52 = 2; }
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    igEnumMetaField_SetDefaultValue(temp_v0, &DAT_00487750[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&igMetaEnum_GetEmpty);
    igUnsignedShortMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 0xFFFF);
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE); q->f52 = 2; }
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF); q->f52 = 2; }
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12), 1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14));
    igEnumMetaField_SetDefaultValue(temp_v0_2, &DAT_00487758[0]);
    *(int *)((char *)(temp_v0_2) + 52) = (int)(&FUN_00147030);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15), 1);
    igMetaObject_NameFields(temp_s0, &g_igPsx2Controller_fieldTable[0], &DAT_00487690[0], &DAT_004876f0[0], temp_s1);
}

int FUN_00147430(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)arg0 + 8) + (arg1 * 4));
}

int FUN_00147450(void *arg0, int arg1) {
    int i;
    int *list;

    for (i = 0; i < 0x20; i++) {
        if (arg1 == *(int *)(*(int *)((char *)(arg0) + 8) + (i * 4))) {
            return i;
        }
    }
    return -1;
}

void FUN_001474a0(O *arg0, int arg1) {
    int n;
    int i;
    n = arg0->list->count;
    for (i = 0; i < n; i++) {
        arg0->list->items[i]->vX(arg1);
    }
}

