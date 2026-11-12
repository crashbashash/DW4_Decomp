void *FUN_00340f30(void) {
    struct G *g = DAT_00587c00[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00340fc0();
    }
    return DAT_00587c00[0];
}

int beUnicode_GetVTable(void) {
    union U_340f80 u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00539870[0]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}

void FUN_00340fc0(void)
{
    igMetaObject_RunStaticInit(beUnicode_Register);
}

void *beUnicode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beUnicode_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beUnicode_GetMetaObject,
        beUnicode_className,
        8, /* instance size */
        beUnicode_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beUnicode_GetMetaObject(void)
{
    FUN_00340f30();
}

