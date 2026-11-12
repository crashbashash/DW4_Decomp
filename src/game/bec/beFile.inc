void *FUN_00362e50(void) {
    struct G *g = DAT_00589778[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00362ee0();
    }
    return DAT_00589778[0];
}

int beFile_GetVTable(void) {
    struct Obj_362ea0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535810[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00362ee0(void)
{
    igMetaObject_RunStaticInit(beFile_Register);
}

void *beFile_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFile_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFile_GetMetaObject,
        beFile_className,
        8, /* instance size */
        beFile_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beFile_GetMetaObject(void)
{
    FUN_00362e50();
}

