void *FUN_00356080(void) {
    igMetaObject *g = g_beModelCtrlLABELCTRL_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003561a0();
    }
    return g_beModelCtrlLABELCTRL_metaObject[0];
}

int beModelCtrlLABELCTRL_GetVTable(void) {
    union U_3560d0 u;
    int temp_s0;
    char *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00537350[0];
    q0 = &u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00537350[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003561a0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLABELCTRL_Register);
}

void *beModelCtrlLABELCTRL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlLABELCTRL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLABELCTRL_GetMetaObject,
        beModelCtrlLABELCTRL_className,
        0x10, /* instance size */
        beModelCtrlLABELCTRL_GetVTable,
        beModelCtrlLABELCTRL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlLABELCTRL_GetMetaObject(void)
{
    FUN_00356080();
}

void beModelCtrlLABELCTRL_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlLABELCTRL_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5878[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c5880[0], &DAT_004c5888[0], &DAT_004c5890[0], temp_s1);
}

