igMetaObject *g_beNDMWItemWeapon_metaObject;

void beNDMWItemWeapon_Create(int allocator) {
    beNDMWItemWeapon_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWItemWeapon_metaObject, allocator);
}

void *beNDMWItemWeapon_GetReadyMetaObject(void) {
    unsigned char b;
    if (g_beNDMWItemWeapon_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWItemWeapon_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWItemWeapon_EnsureRegistered();
done:
    return g_beNDMWItemWeapon_metaObject;
}

int beNDMWItemWeapon_GetVTable(void) {
    union U_3c8d20 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beNDMWItemWeapon_vtable[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void beNDMWItemWeapon_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemWeapon_Register);
}

void *beNDMWItemWeapon_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemWeapon_metaObject,
        beNDMWItemRevisionPocketBase_Register,
        beNDMWItemRevisionPocketBase_GetPublishedMetaObject,
        beNDMWItemWeapon_GetMetaObject,
        "beNDMWItemWeapon",
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

