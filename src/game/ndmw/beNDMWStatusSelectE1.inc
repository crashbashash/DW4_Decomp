void FUN_003b51b0(int arg0) {
    FUN_003b52c0();
    igMetaObject_CreateInstance(*(int *)0x58ABD8, arg0);
}

void *FUN_003b51f0(void) {
    struct G *g = DAT_0058abd8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b52c0();
    }
    return DAT_0058abd8[0];
}

int beNDMWStatusSelectE1_GetVTable(void) {
    struct Obj_3b5240 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    obj.w27 = 0;
    obj.vt = &DAT_0053f330[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053f330[0];
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return t;
}

void FUN_003b52c0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE1_Register);
}

void *beNDMWStatusSelectE1_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSelectE1_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE1_GetMetaObject,
        beNDMWStatusSelectE1_className,
        0x70, /* instance size */
        beNDMWStatusSelectE1_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelectE1_GetMetaObject(void)
{
    FUN_003b51f0();
}

