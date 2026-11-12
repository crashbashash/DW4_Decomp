igMetaObject *FUN_0034d540(void) {
    igMetaObject *g = g_beNumberCtrlInfoRam_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0034d740();
done:
    return g_beNumberCtrlInfoRam_metaObject[0];
}

int beNumberCtrlInfoRam_GetVTable(void) {
    struct W_34d590 o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[9] = 0;
    o.vt = &DAT_005384d0[0];
    p16 = &o.f[10];
    *p16 = 0;
    p17 = &o.f[14];
    *p17 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_005384d0[0];
    FUN_0034d6c0((void **)(&o.f[15]), -1);
    FUN_0034d640((void **)p17, (long long)(-1));
    FUN_001971e0(p16, -1);
    FUN_0033e920((S *)&o, (long long)0);
    return r;
}

void **FUN_0034d640(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_0034d6c0(void **arg0, int arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0034d740(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoRam_Register);
}

void *beNumberCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNumberCtrlInfoRam_GetMetaObject,
        beNumberCtrlInfoRam_className,
        0x44, /* instance size */
        beNumberCtrlInfoRam_GetVTable,
        beNumberCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beNumberCtrlInfoRam_callbackList /* callback list */
    );
}

void beNumberCtrlInfoRam_GetMetaObject(void)
{
    FUN_0034d540();
}

void beNumberCtrlInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beNumberCtrlInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4950[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_0019fae0();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0.09375f);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_0034d8f0();
    *(char *)((char *)(temp_s1_2) + 52) = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    *(int *)((char *)(temp_s1_3) + 56) = (int)FUN_0034d2f0();
    igMetaObject_NameFields(temp_s0, &DAT_004c4970[0], &DAT_004c4990[0], &DAT_004c49b0[0], temp_s2);
}

