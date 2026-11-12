int FUN_0033fd70(void) {
    if (((int *)DAT_00587a98)[0] == 0) {
        ((int *)DAT_00587a98)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587a98)[0];
}

S_33fdc0 *FUN_0033fdc0(void) {
    S_33fdc0 *g = DAT_00587a98[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0033fe50();
done:
    return DAT_00587a98[0];
}

int igAppearanceListList_GetVTable(void) {
    Obj_33fe10 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00539b40[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0033fe50(void)
{
    igMetaObject_RunStaticInit(igAppearanceListList_Register);
}

void *igAppearanceListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAppearanceListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAppearanceListList_GetMetaObject,
        igAppearanceListList_className,
        0x14, /* instance size */
        igAppearanceListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAppearanceListList_callbackList /* callback list */
    );
}

void igAppearanceListList_GetMetaObject(void)
{
    FUN_0033fdc0();
}

int FUN_0033ff00(void) {
    if (((int *)DAT_00587aa0)[0] == 0) {
        ((int *)DAT_00587aa0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587aa0)[0];
}

