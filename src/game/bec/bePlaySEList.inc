int FUN_00344630(void) {
    if (((int *)DAT_00587ec8)[0] == 0) {
        ((int *)DAT_00587ec8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587ec8)[0];
}

SFUN_00344680 *FUN_00344680(void) {
    if (DAT_00587ec8[0] == 0 || !DAT_00587ec8[0]->ok()) FUN_00344710();
    return DAT_00587ec8[0];
}

int bePlaySEList_GetVTable(void) {
    struct Obj_3446d0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00539280[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00344710(void)
{
    igMetaObject_RunStaticInit(bePlaySEList_Register);
}

void *bePlaySEList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePlaySEList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        bePlaySEList_GetMetaObject,
        bePlaySEList_className,
        0x14, /* instance size */
        bePlaySEList_GetVTable,
        0,
        0, /* extra callback item */
        g_bePlaySEList_callbackList /* callback list */
    );
}

void bePlaySEList_GetMetaObject(void)
{
    FUN_00344680();
}

