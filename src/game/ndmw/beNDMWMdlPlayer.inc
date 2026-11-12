void FUN_003bf890(int arg0) {
    FUN_003bfae0();
    igMetaObject_CreateInstance(*(int *)0x58B3A8, arg0);
}

int FUN_003bf8d0(void) {
    if (((int *)DAT_0058b3a8)[0] == 0) {
        ((int *)DAT_0058b3a8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b3a8)[0];
}

void *beNDMWMdlPlayer_ResolveMetaObject(void) {
    struct MetaObjectValidityView *g = DAT_0058b3a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bfae0();
    }
    return DAT_0058b3a8[0];
}

int beNDMWMdlPlayer_GetVTable(void) {
    struct W_3bf970 o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = DAT_0053e620;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_0053e620;
    FUN_003bf9d0((O_3bf9d0 *)&o, (short)0);
    return r;
}

O_3bf9d0 *FUN_003bf9d0(O_3bf9d0 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R_3bf9d0 *temp_a0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &DAT_00540580[0];
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
                            temp_v1 = arg0->str;
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
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_003bfae0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer_Register);
}

void *beNDMWMdlPlayer_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPlayer_metaObject,
        beNDMWMdlPEBase_Register,
        beNDMWMdlPEBase_GetPublishedMetaObject,
        beNDMWMdlPlayer_GetMetaObject,
        beNDMWMdlPlayer_className,
        0x38, /* instance size */
        beNDMWMdlPlayer_GetVTable,
        beNDMWMdlPlayer_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayer_callbackList /* callback list */
    );
}

void beNDMWMdlPlayer_GetMetaObject(void)
{
    beNDMWMdlPlayer_ResolveMetaObject();
}

int FUN_003bfba0(void) {
    return ((int *)DAT_0058b428)[0];
}

void beNDMWMdlPlayer_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058b3a8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca870[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00459380();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_003c9ce0();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004ca880[0], &DAT_004ca890[0], &DAT_004ca8a0[0], temp_s2);
}

