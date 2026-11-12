void FUN_0034c630(int arg0) {
    FUN_0034c7f0();
    igMetaObject_CreateInstance(*(int *)0x588510, arg0);
}

igMetaObject *FUN_0034c670(void) {
    if (g_beParticleCtrl2_metaObject[0] == 0) {
        g_beParticleCtrl2_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beParticleCtrl2_metaObject[0];
}

void *FUN_0034c6c0(void) {
    igMetaObject *g = g_beParticleCtrl2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034c7f0();
    }
    return g_beParticleCtrl2_metaObject[0];
}

int beParticleCtrl2_GetVTable(void) {
    union U_34c710 u;
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
    u.vt = (int)&DAT_0053b0b0[0];
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

void FUN_0034c7f0(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2_Register);
}

void *beParticleCtrl2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beParticleCtrl2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beParticleCtrl2_GetMetaObject,
        beParticleCtrl2_className,
        0x20, /* instance size */
        beParticleCtrl2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beParticleCtrl2_GetMetaObject(void)
{
    FUN_0034c6c0();
}

