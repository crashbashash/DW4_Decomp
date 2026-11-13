void beWeapon_CreateInstance(int arg0) {
    FUN_0033f750();
    igMetaObject_CreateInstance(*(int *)0x587A68, arg0);
}

igMetaObject *FUN_0033f450(void) {
    if (g_beWeapon_metaObject[0] == 0) {
        g_beWeapon_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beWeapon_metaObject[0];
}

void *FUN_0033f4a0(void) {
    igMetaObject *g = g_beWeapon_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0033f750();
    }
    return g_beWeapon_metaObject[0];
}

int beWeapon_GetVTable(void) {
    union U_33f4f0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&DAT_0053b630[0]);
    u.w[8] = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0053b630[0]);
    FUN_0033f6d0((void **)(&u.w[8]), (short)(-1));
    FUN_0033f5e0((O_33f5e0 *)(&u.w[0]), (short)0);
    return temp_s0;
}

void **FUN_0033f560(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O_33f5e0 *FUN_0033f5e0(O_33f5e0 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R_33f5e0 *temp_a0;
    int *temp_v1;

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
                arg0->vt = &g_igNamedObject_vtable[0];
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
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_0033f6d0(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0033f750(void)
{
    igMetaObject_RunStaticInit(beWeapon_Register);
}

void *beWeapon_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeapon_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beWeapon_GetMetaObject,
        beWeapon_className,
        0x24, /* instance size */
        beWeapon_GetVTable,
        beWeapon_InitFields,
        0, /* extra callback item */
        g_beWeapon_callbackList /* callback list */
    );
}

void beWeapon_GetMetaObject(void)
{
    FUN_0033f4a0();
}

igMetaObject *FUN_0033f810(void) {
    return g_beBaseInfoManager_metaObject[0];
}

void beWeapon_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beWeapon_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3020[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0033f8f0();
    igMetaObject_NameFields(temp_s0, &DAT_004c3028[0], &DAT_004c3030[0], &DAT_004c3038[0], temp_s2);
}

