void beBaseInfoDataList_Create(int arg0) {
    FUN_0036afa0();
    igMetaObject_CreateInstance(*(int *)0x589E00, arg0);
}

int FUN_0036aec0(void) {
    if (((int *)DAT_00589e00)[0] == 0) {
        ((int *)DAT_00589e00)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589e00)[0];
}

void *FUN_0036af10(void) {
    igMetaObject *g = DAT_00589e00[0];
    int ready;
    if (g) {
        /* matching construct: the readiness test materialised as an int (`sltu`) before
         * the branch; a bool or a direct `if` folds it into the branch under -O3,p */
        ready = (g->_validity & 4) != 0;
        if (ready) goto end;
    }
    FUN_0036afa0();
end:
    return DAT_00589e00[0];
}

int beBaseInfoDataList_GetVTable(void) {
    struct Obj_36af60 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005346e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0036afa0(void)
{
    igMetaObject_RunStaticInit(beBaseInfoDataList_Register);
}

void *beBaseInfoDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoDataList_GetMetaObject,
        beBaseInfoDataList_className,
        0x14, /* instance size */
        beBaseInfoDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoDataList_callbackList /* callback list */
    );
}

void beBaseInfoDataList_GetMetaObject(void)
{
    FUN_0036af10();
}

