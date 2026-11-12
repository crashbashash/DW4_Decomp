int FUN_0035bb70(void) {
    if (((int *)DAT_00589230)[0] == 0) {
        ((int *)DAT_00589230)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589230)[0];
}

void *FUN_0035bbc0(void) {
    bool ok;
    if (DAT_00589230[0] == 0) goto make;
    ok = !!(DAT_00589230[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0035bc50();
done:;
    return DAT_00589230[0];
}

int igLightSetList_GetVTable(void) {
    struct Obj_35bc10 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536750[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0035bc50(void)
{
    igMetaObject_RunStaticInit(igLightSetList_Register);
}

void *igLightSetList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightSetList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igLightSetList_GetMetaObject,
        igLightSetList_className,
        0x14, /* instance size */
        igLightSetList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightSetList_callbackList /* callback list */
    );
}

void igLightSetList_GetMetaObject(void)
{
    FUN_0035bbc0();
}

