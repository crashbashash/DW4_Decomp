void beNDMWStatusTitle00_Create(int arg0) {
    FUN_003b3d90();
    igMetaObject_CreateInstance(*(int *)0x58AB70, arg0);
}

igMetaObject *FUN_003b3cc0(void) {
    igMetaObject *g = g_beNDMWStatusTitle00_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003b3d90();
done:
    return g_beNDMWStatusTitle00_metaObject[0];
}

int beNDMWStatusTitle00_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[12] = 0;
    f.w[13] = 0;
    f.w[14] = 0;
    f.w[15] = 0;
    f.w[16] = 0;
    f.w[17] = 0;
    f.w[18] = 0;
    f.vt = &DAT_0053f720[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_0053f720[0];
    FUN_003b3030((int **)&f, (long long)0);
    return temp_s0;
}

void FUN_003b3d90(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle00_Register);
}

void *beNDMWStatusTitle00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusTitle00_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle00_GetMetaObject,
        beNDMWStatusTitle00_className,
        0x50, /* instance size */
        beNDMWStatusTitle00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle00_GetMetaObject(void)
{
    FUN_003b3cc0();
}

