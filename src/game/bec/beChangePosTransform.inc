void FUN_00368710(int arg0) {
    FUN_003688d0();
    igMetaObject_CreateInstance(*(int *)0x589B80, arg0);
}

igMetaObject *FUN_00368750(void) {
    if (g_beChangePosTransform_metaObject[0] == 0) {
        g_beChangePosTransform_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beChangePosTransform_metaObject[0];
}

igMetaObject *FUN_003687a0(void) {
    if (g_beChangePosTransform_metaObject[0] == 0 || !isValid(g_beChangePosTransform_metaObject[0])) FUN_003688d0();
    return g_beChangePosTransform_metaObject[0];
}

int beChangePosTransform_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0053a0d0[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0053a340[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053a0d0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
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

void FUN_003688d0(void)
{
    igMetaObject_RunStaticInit(beChangePosTransform_Register);
}

void *beChangePosTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beChangePosTransform_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beChangePosTransform_GetMetaObject,
        beChangePosTransform_className,
        0x2c, /* instance size */
        beChangePosTransform_GetVTable,
        beChangePosTransform_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beChangePosTransform_GetMetaObject(void)
{
    FUN_003687a0();
}

void beChangePosTransform_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beChangePosTransform_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7798[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c77a0[0], &DAT_004c77a8[0], &DAT_004c77b0[0], temp_s1);
}

