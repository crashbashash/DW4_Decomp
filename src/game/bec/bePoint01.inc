void FUN_0034b9e0(int arg0) {
    FUN_0034bba0();
    igMetaObject_CreateInstance(*(int *)0x588498, arg0);
}

int FUN_0034ba20(void) {
    if (((int *)DAT_00588498)[0] == 0) {
        ((int *)DAT_00588498)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588498)[0];
}

void *FUN_0034ba70(void) {
    bool ok;
    if (DAT_00588498[0] == 0) goto make;
    ok = !!(DAT_00588498[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0034bba0();
done:;
    return DAT_00588498[0];
}

int bePoint01_GetVTable(void) {
    union U u;
    int r;

    int *v1; int *a1; int v0; int *a0;
    char *pr; char *ps;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053a0d0[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    pr = &u.b[24];
    *(int *)pr = 0;
    u.vt = (int)&DAT_0053b150[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053a0d0[0];
    if (pr != 0) {
        a0 = *(int **)pr;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}

void FUN_0034bba0(void)
{
    igMetaObject_RunStaticInit(bePoint01_Register);
}

void *bePoint01_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePoint01_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        bePoint01_GetMetaObject,
        bePoint01_className,
        0x24, /* instance size */
        bePoint01_GetVTable,
        bePoint01_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void bePoint01_GetMetaObject(void)
{
    FUN_0034ba70();
}

void bePoint01_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588498)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4590[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c4598[0], &DAT_004c45a0[0], &DAT_004c45a8[0], temp_s1);
}

