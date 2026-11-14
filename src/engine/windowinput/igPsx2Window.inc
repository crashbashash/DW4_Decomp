igMetaObject *FUN_00146a60(void)
{
    igMetaObject *meta = g_igPsx2Window_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_00146b80();
end:
    return g_igPsx2Window_metaObject[0];
}

int igPsx2Window_GetVTable(void) {
    union U_146ab0 u;
    int temp_s0;
    char *q0;
    S_ref *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524be0[0];
    q1 = (S_ref *)&u.b[24];
    *(int *)q1 = 0;
    q0 = &u.b[32];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00524be0[0];
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

void FUN_00146b80(void)
{
    igMetaObject_RunStaticInit(igPsx2Window_Register);
}

void igPsx2Window_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Window_metaObject,
        igWindow_Register,
        igWindow_GetPublishedMetaObject,
        thunk_FUN_00146a60,
        igPsx2Window_className,
        sizeof(igPsx2Window),                     /* Instance size. */
        igPsx2Window_GetVTable,
        &igPsx2Window_InitFields,
        0, /* extra callback item */
        g_igPsx2Window_callbackList /* callback list */
    );
}

igMetaObject *FUN_00146c10(void) {
    return g_igWindow_metaObject[0];
}

void igPsx2Window_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igPsx2Window_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPsx2Window_ctorTable[0], 0xC);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2), 0x280);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0x1C0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1) + 56) = FUN_0014a040();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 0);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7), -1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), 0x18);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA), 8);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 0x20);
    igMetaObject_NameFields(temp_s0, &g_igPsx2Window_fieldTable[0], &DAT_004874b0[0], &DAT_004874e0[0], temp_s2);
    *(int *)((char *)(g_igPsx2Window_metaObject[0]) + 64) = (int)thunk_igWindow_GetMetaObject;
}

