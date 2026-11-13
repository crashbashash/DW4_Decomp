void FUN_0034c040(int arg0) {
    FUN_0034c230();
    igMetaObject_CreateInstance(*(int *)0x5884C8, arg0);
}

igMetaObject *FUN_0034c080(void) {
    if (g_beParticleCtrl2InfoWork_metaObject[0] == 0) {
        g_beParticleCtrl2InfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beParticleCtrl2InfoWork_metaObject[0];
}

void *FUN_0034c0d0(void) {
    unsigned char b;
    if (((void * *)g_beParticleCtrl2InfoWork_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)g_beParticleCtrl2InfoWork_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0034c230();
done:
    return ((void * *)g_beParticleCtrl2InfoWork_metaObject)[0];
}

int beParticleCtrl2InfoWork_GetVTable(void) {
    union U_34c120 u;
    int temp_s0;
    char *ps;
    int *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005386e0[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005386e0[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_0034c230(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2InfoWork_Register);
}

void *beParticleCtrl2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beParticleCtrl2InfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beParticleCtrl2InfoWork_GetMetaObject,
        beParticleCtrl2InfoWork_className,
        0x18, /* instance size */
        beParticleCtrl2InfoWork_GetVTable,
        beParticleCtrl2InfoWork_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoWork_callbackList /* callback list */
    );
}

void beParticleCtrl2InfoWork_GetMetaObject(void)
{
    FUN_0034c0d0();
}

void beParticleCtrl2InfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beParticleCtrl2InfoWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beParticleCtrl2InfoWork_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034fd40();
    igMetaObject_NameFields(temp_s0, &g_beParticleCtrl2InfoWork_fieldTable[0], &DAT_004c4618[0], &DAT_004c4620[0], temp_s2);
}

