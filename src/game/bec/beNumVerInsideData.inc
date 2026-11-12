int FUN_0034de60(int arg0) {
    FUN_0034df30();
    return igMetaObject_CreateInstance(*(int *)0x5886B0, arg0);
}

void *FUN_0034dea0(void) {
    bool ok;
    if (g_beNumVerInsideData_metaObject[0] == 0) goto make;
    ok = !!(g_beNumVerInsideData_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0034df30();
done:;
    return g_beNumVerInsideData_metaObject[0];
}

int beNumVerInsideData_GetVTable(void) {
    struct Obj_34def0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538330[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034df30(void)
{
    igMetaObject_RunStaticInit(beNumVerInsideData_Register);
}

void *beNumVerInsideData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerInsideData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerInsideData_GetMetaObject,
        beNumVerInsideData_className,
        0x10, /* instance size */
        beNumVerInsideData_GetVTable,
        beNumVerInsideData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumVerInsideData_GetMetaObject(void)
{
    FUN_0034dea0();
}

void beNumVerInsideData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNumVerInsideData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4a00[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c4a08[0], &DAT_004c4a10[0], &DAT_004c4a18[0], temp_s1);
}

