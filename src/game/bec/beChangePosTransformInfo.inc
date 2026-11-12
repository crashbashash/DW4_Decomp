S_3685a0 *FUN_003685a0(void) {
    S_3685a0 *g = DAT_00589b78[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00368660();
done:
    return DAT_00589b78[0];
}

int beChangePosTransformInfo_GetVTable(void) {
    struct Obj_3685f0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_00534b00[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00534b00[0]);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s0;
}

void FUN_00368660(void)
{
    igMetaObject_RunStaticInit(beChangePosTransformInfo_Register);
}

void *beChangePosTransformInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beChangePosTransformInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beChangePosTransformInfo_GetMetaObject,
        beChangePosTransformInfo_className,
        0x1c, /* instance size */
        beChangePosTransformInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beChangePosTransformInfo_GetMetaObject(void)
{
    FUN_003685a0();
}

