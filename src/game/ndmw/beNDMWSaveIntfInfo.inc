S *FUN_003bc080(void) {
    S *g = DAT_0058b070[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003bc140();
done:
    return DAT_0058b070[0];
}

int beNDMWSaveIntfInfo_GetVTable(void) {
    union U_3bc0d0 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[0] = (int)(&DAT_0053d960[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053d960[0]);
    FUN_0033ec80(&u.w[0], 0);
    return temp_s0;
}

void FUN_003bc140(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfInfo_Register);
}

void *beNDMWSaveIntfInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveIntfInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWSaveIntfInfo_GetMetaObject,
        beNDMWSaveIntfInfo_className,
        0x1c, /* instance size */
        beNDMWSaveIntfInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveIntfInfo_GetMetaObject(void)
{
    FUN_003bc080();
}

