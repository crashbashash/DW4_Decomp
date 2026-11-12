S_35f720 *FUN_0035f720(void) {
    S_35f720 *g = DAT_005894d8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0035f870();
done:
    return DAT_005894d8[0];
}

int beGeneraterInfo_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[4] = 0;
    f.w[5] = 0;
    f.vt = &DAT_00535f80[0];
    f.w[6] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_00535f80[0];
    FUN_0035f7f0((void **)(&f.w[6]), (long long)(-1));
    FUN_0033ec80((struct S_33ec80 *)&f, (short)0);
    return temp_s0;
}

void **FUN_0035f7f0(void **arg0, long long arg1) {
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

void FUN_0035f870(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfo_Register);
}

void *beGeneraterInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beGeneraterInfo_GetMetaObject,
        beGeneraterInfo_className,
        0x20, /* instance size */
        beGeneraterInfo_GetVTable,
        beGeneraterInfo_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfo_callbackList /* callback list */
    );
}

void beGeneraterInfo_GetMetaObject(void)
{
    FUN_0035f720();
}

void beGeneraterInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005894d8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6988[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035f9d0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6990[0], &DAT_004c6998[0], &DAT_004c69a0[0], temp_s2);
}

