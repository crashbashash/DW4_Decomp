int FUN_0035ee00(void) {
    if (((int *)DAT_00589468)[0] == 0) {
        ((int *)DAT_00589468)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589468)[0];
}

void *FUN_0035ee50(void) {
    struct G *g = DAT_00589468[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035eee0();
    }
    return DAT_00589468[0];
}

int beGroupKeepList_GetVTable(void) {
    struct Obj_35eea0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536150[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0035eee0(void)
{
    igMetaObject_RunStaticInit(beGroupKeepList_Register);
}

void *beGroupKeepList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGroupKeepList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGroupKeepList_GetMetaObject,
        beGroupKeepList_className,
        0x14, /* instance size */
        beGroupKeepList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGroupKeepList_callbackList /* callback list */
    );
}

void beGroupKeepList_GetMetaObject(void)
{
    FUN_0035ee50();
}

