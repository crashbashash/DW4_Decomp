void FUN_003bf1b0(int arg0) {
    FUN_003bf3f0();
    igMetaObject_CreateInstance(*(int *)0x58B368, arg0);
}

igMetaObject *FUN_003bf1f0(void) {
    if (g_beNDMWMdlPlayer2_metaObject[0] == 0) {
        g_beNDMWMdlPlayer2_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWMdlPlayer2_metaObject[0];
}

void *beNDMWMdlPlayer2_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPlayer2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bf3f0();
    }
    return g_beNDMWMdlPlayer2_metaObject[0];
}

int beNDMWMdlPlayer2_GetVTable(void) {
    union U_3bf290 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&DAT_0053e6f0[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053e6f0[0];
    FUN_003bf2f0((struct NamedRefObject *)u.b, (long long)0);
    return t;
}

struct NamedRefObject *FUN_003bf2f0(struct NamedRefObject *arg0, long long arg1) {
    int *temp_a1;
    int temp_v0;
    int *temp_v1;
    RefCountedHeader *temp_a0;

    if (arg0 != 0) {
        arg0->vt = &DAT_0053adb0[0];
        if (arg0 != 0) {
            arg0->vt = &DAT_0053a0d0[0];
            if (&arg0->ref != 0) {
                temp_a0 = arg0->ref;
                if (temp_a0 != 0) {
                    temp_a0->refs = temp_a0->refs - 1;
                    if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(temp_a0);
                    }
                }
            }
            if (arg0 != 0) {
                arg0->vt = &DAT_0052cf80[0];
                if (arg0 != 0) {
                    arg0->vt = &DAT_00524950[0];
                    if (&arg0->str != 0) {
                        temp_v1 = (int *)arg0->str;
                        if (temp_v1 != 0) {
                            temp_a1 = temp_v1 - 2;
                            temp_v0 = temp_v1[-1] - 1;
                            temp_v1[-1] = temp_v0;
                            if (temp_v0 == 0) {
                                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                            }
                        }
                    }
                }
            }
        }
        if ((short)arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_003bf3f0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer2_Register);
}

void *beNDMWMdlPlayer2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPlayer2_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPlayer2_GetMetaObject,
        beNDMWMdlPlayer2_className,
        0x30, /* instance size */
        beNDMWMdlPlayer2_GetVTable,
        beNDMWMdlPlayer2_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayer2_callbackList /* callback list */
    );
}

void beNDMWMdlPlayer2_GetMetaObject(void)
{
    beNDMWMdlPlayer2_ResolveMetaObject();
}

int FUN_003bf4b0(void) {
    return g_beModelCtrl_metaObject[0];
}

void beNDMWMdlPlayer2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWMdlPlayer2_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca7c0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004ca7c8[0], &DAT_004ca7d0[0], &DAT_004ca7d8[0], temp_s2);
}

