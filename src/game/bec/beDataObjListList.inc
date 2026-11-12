void FUN_00363e80(int arg0) {
    FUN_00363fa0();
    igMetaObject_CreateInstance(*(int *)0x589838, arg0);
}

int FUN_00363ec0(void) {
    if (((int *)DAT_00589838)[0] == 0) {
        ((int *)DAT_00589838)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589838)[0];
}

S_363f10 *FUN_00363f10(void) {
    S_363f10 *g = DAT_00589838[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00363fa0();
done:
    return DAT_00589838[0];
}

int beDataObjListList_GetVTable(void) {
    Obj_363f60 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005355a0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00363fa0(void)
{
    igMetaObject_RunStaticInit(beDataObjListList_Register);
}

void *beDataObjListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataObjListList_GetMetaObject,
        beDataObjListList_className,
        0x14, /* instance size */
        beDataObjListList_GetVTable,
        0,
        0, /* extra callback item */
        pA6 /* callback list */
    );
}

void beDataObjListList_GetMetaObject(void)
{
    FUN_00363f10();
}

