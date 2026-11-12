void FUN_003c8970(int arg0) {
    FUN_003c8a40();
    igMetaObject_CreateInstance(*(int *)0x58BF50, arg0);
}

void *beNDMWItemYellowArmor_GetReadyMetaObject(void) {
    bool ok;
    if (DAT_0058bf50[0] == 0) goto make;
    ok = !!(DAT_0058bf50[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003c8a40();
done:;
    return DAT_0058bf50[0];
}

int beNDMWItemYellowArmor_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540880[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003c8a40(void)
{
    igMetaObject_RunStaticInit(beNDMWItemYellowArmor_Register);
}

void *beNDMWItemYellowArmor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemYellowArmor_metaObject,
        beNDMWItemRevisionBase_Register,
        beNDMWItemRevisionBase_GetPublishedMetaObject,
        beNDMWItemYellowArmor_GetMetaObject,
        beNDMWItemYellowArmor_className,
        0x18, /* instance size */
        beNDMWItemYellowArmor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemYellowArmor_GetMetaObject(void)
{
    beNDMWItemYellowArmor_GetReadyMetaObject();
}

int FUN_003c8af0(void) {
    return ((int *)DAT_0058bf78)[0];
}

