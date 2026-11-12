void *FUN_0033eb00(void) {
    igMetaObject *g = g_beWeaponInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0033ee30();
    }
    return g_beWeaponInfo_metaObject[0];
}

int beWeaponInfo_GetVTable(void) {
    struct Obj obj;
    int temp_s2;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_00539d50[0]);
    obj.f1C = 0;
    obj.f20 = 0;
    obj.f24 = 0;
    temp_s2 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_00539d50[0]);
    FUN_0033edb0((struct T **)&obj.f24, (short)(-1));
    FUN_00199450(&obj.f20, -1);
    FUN_001958f0(&obj.f1C, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s2;
}

igObject **FUN_0033ec00(igObject **arg0, short arg1) {
    igObject *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void *FUN_0033ec80(struct S_33ec80 *arg0, short arg1) {
    struct R_33ec80 *p;
    int *h;
    int *a1;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00539dc0[0];
        if (&arg0->f24) {
            p = arg0->f24;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f20) {
            p = arg0->f20;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_0052fde0[0];
            if (arg0 != 0) {
                arg0->f0 = &DAT_00524950[0];
                if (&arg0->f8) {
                    h = arg0->f8;
                    if (h != 0) {
                        a1 = h - 2;
                        rc = h[-1] - 1;
                        h[-1] = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*a1, a1);
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

struct T **FUN_0033edb0(struct T **arg0, short arg1) {
    struct T *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0033ee30(void)
{
    igMetaObject_RunStaticInit(beWeaponInfo_Register);
}

void *beWeaponInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beWeaponInfo_GetMetaObject,
        beWeaponInfo_className,
        0x28, /* instance size */
        beWeaponInfo_GetVTable,
        beWeaponInfo_InitFields,
        0, /* extra callback item */
        g_beWeaponInfo_callbackList /* callback list */
    );
}

void beWeaponInfo_GetMetaObject(void)
{
    FUN_0033eb00();
}

igMetaObject *FUN_0033eef0(void) {
    return g_beBaseInfo_metaObject[0];
}

void beWeaponInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beWeaponInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c2f90[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019cbe0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002be100();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0033efe0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c2fa0[0], &DAT_004c2fb0[0], &DAT_004c2fc0[0], temp_s2);
}

