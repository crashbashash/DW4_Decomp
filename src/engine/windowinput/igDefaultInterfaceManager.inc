igMetaObject *FUN_00146470(void)
{
    unsigned char ready;
    if (g_igDefaultInterfaceManager_metaObject[0] != 0) {
        ready = (g_igDefaultInterfaceManager_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00146560();
done:
    return g_igDefaultInterfaceManager_metaObject[0];
}

int igDefaultInterfaceManager_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00524da0[0];
    u.vt = (int)&DAT_00524e50[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524da0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void FUN_00146560(void)
{
    igMetaObject_RunStaticInit(igDefaultInterfaceManager_Register);
}

void igDefaultInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultInterfaceManager_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        thunk_FUN_00146470,
        igDefaultInterfaceManager_className,
        0x4C, /* instance size */
        igDefaultInterfaceManager_GetVTable,
        &igDefaultInterfaceManager_InitFields,              /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_001465e0(void) {
    return DAT_0055f5e8[0];
}

void igDefaultInterfaceManager_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f610[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487160[0], 0x10);
    igMetaObject_NameFields(temp_s0, &DAT_004871a0[0], &DAT_004871e0[0], &DAT_00487220[0], temp_s1);
}

