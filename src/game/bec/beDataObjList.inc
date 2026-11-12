void FUN_00364050(int arg0) {
    FUN_00364170();
    igMetaObject_CreateInstance(*(int *)0x589840, arg0);
}

int FUN_00364090(void) {
    if (((int *)DAT_00589840)[0] == 0) {
        ((int *)DAT_00589840)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589840)[0];
}

SFUN_003640e0 *FUN_003640e0(void) {
    if (DAT_00589840[0] == 0 || !DAT_00589840[0]->ok()) FUN_00364170();
    return DAT_00589840[0];
}

int beDataObjList_GetVTable(void) {
    struct Obj_364130 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535530[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00364170(void)
{
    igMetaObject_RunStaticInit(beDataObjList_Register);
}

void *beDataObjList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataObjList_GetMetaObject,
        beDataObjList_className,
        0x14, /* instance size */
        beDataObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataObjList_callbackList /* callback list */
    );
}

void beDataObjList_GetMetaObject(void)
{
    FUN_003640e0();
}

