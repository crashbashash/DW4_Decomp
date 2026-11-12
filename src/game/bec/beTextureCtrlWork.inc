void FUN_00342630(int arg0) {
    FUN_003427f0();
    igMetaObject_CreateInstance(*(int *)0x587CD0, arg0);
}

int FUN_00342670(void) {
    if (((int *)DAT_00587cd0)[0] == 0) {
        ((int *)DAT_00587cd0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587cd0)[0];
}

void *FUN_003426c0(void) {
    bool ok;
    if (DAT_00587cd0[0] == 0) goto make;
    ok = !!(DAT_00587cd0[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003427f0();
done:;
    return DAT_00587cd0[0];
}

int beTextureCtrlWork_GetVTable(void) {
    union U_342710 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539500[0];
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539500[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
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

void FUN_003427f0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlWork_Register);
}

void *beTextureCtrlWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beTextureCtrlWork_GetMetaObject,
        beTextureCtrlWork_className,
        0x10, /* instance size */
        beTextureCtrlWork_GetVTable,
        beTextureCtrlWork_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlWork_callbackList /* callback list */
    );
}

void beTextureCtrlWork_GetMetaObject(void)
{
    FUN_003426c0();
}

void beTextureCtrlWork_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587cd0)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3510[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c3518[0], &DAT_004c3520[0], &DAT_004c3528[0], temp_s2);
}

