void beNDMWItemWeapon_Create(int arg0) {
    FUN_003c8d60();
    igMetaObject_CreateInstance(*(int *)0x58BF60, arg0);
}

void *beNDMWItemWeapon_GetReadyMetaObject(void) {
    unsigned char b;
    if (g_beNDMWItemWeapon_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beNDMWItemWeapon_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003c8d60();
done:
    return g_beNDMWItemWeapon_metaObject[0];
}

int beNDMWItemWeapon_GetVTable(void) {
    union U_3c8d20 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540960[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_003c8d60(void)
{
    igMetaObject_RunStaticInit(beNDMWItemWeapon_Register);
}

void *beNDMWItemWeapon_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemWeapon_metaObject,
        beNDMWItemRevisionPocketBase_Register,
        beNDMWItemRevisionPocketBase_GetPublishedMetaObject,
        beNDMWItemWeapon_GetMetaObject,
        beNDMWItemWeapon_className,
        0x1c, /* instance size */
        beNDMWItemWeapon_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemWeapon_GetMetaObject(void)
{
    beNDMWItemWeapon_GetReadyMetaObject();
}

