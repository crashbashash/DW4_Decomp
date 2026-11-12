void FUN_0033f8b0(int arg0) {
    FUN_0033f9d0();
    igMetaObject_CreateInstance(*(int *)0x587A78, arg0);
}

int FUN_0033f8f0(void) {
    if (((int *)DAT_00587a78)[0] == 0) {
        ((int *)DAT_00587a78)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587a78)[0];
}

igMetaObject *FUN_0033f940(void)
{
    igMetaObject *g = DAT_00587a78[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0033f9d0();
    return DAT_00587a78[0];
}

int beWeaponAttachDataList_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00539c10[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_0033f9d0(void)
{
    igMetaObject_RunStaticInit(beWeaponAttachDataList_Register);
}

void *beWeaponAttachDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponAttachDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWeaponAttachDataList_GetMetaObject,
        beWeaponAttachDataList_className,
        0x14, /* instance size */
        beWeaponAttachDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWeaponAttachDataList_callbackList /* callback list */
    );
}

void beWeaponAttachDataList_GetMetaObject(void)
{
    FUN_0033f940();
}

