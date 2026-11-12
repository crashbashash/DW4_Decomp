void FUN_003660d0(int arg0) {
    FUN_00366290();
    igMetaObject_CreateInstance(*(int *)0x589958, arg0);
}

int FUN_00366110(void) {
    if (((int *)DAT_00589958)[0] == 0) {
        ((int *)DAT_00589958)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589958)[0];
}

G_366160 *FUN_00366160(void) {
    G_366160 *g = DAT_00589958[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00366290();
    return DAT_00589958[0];
}

int beDBManager_GetVTable(void) {
    union U_3661b0 u;
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
    u.vt = (int)&DAT_0053bb70[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
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
    u.vt = (int)&DAT_00524950[0];
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

void FUN_00366290(void)
{
    igMetaObject_RunStaticInit(beDBManager_Register);
}

void *beDBManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDBManager_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beDBManager_GetMetaObject,
        beDBManager_className,
        0x20, /* instance size */
        beDBManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDBManager_GetMetaObject(void)
{
    FUN_00366160();
}

