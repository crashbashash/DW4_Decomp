void FUN_003b4f50(int arg0) {
    FUN_003b5070();
    igMetaObject_CreateInstance(*(int *)0x58ABC8, arg0);
}

void *FUN_003b4f90(void) {
    igMetaObject *g = g_beNDMWShopSelect00_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b5070();
    }
    return g_beNDMWShopSelect00_metaObject[0];
}

int beNDMWShopSelect00_GetVTable(void) {
    struct Obj_3b4fe0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.f50 = 0;
    obj.f6C = 0;
    obj.vt = (&DAT_00540290[0]);
    obj.f70 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_00540290[0]);
    StringRef_Destruct_00130720(&obj.f70, -1);
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return temp_s0;
}

void FUN_003b5070(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect00_Register);
}

void *beNDMWShopSelect00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect00_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect00_GetMetaObject,
        beNDMWShopSelect00_className,
        0x74, /* instance size */
        beNDMWShopSelect00_GetVTable,
        beNDMWShopSelect00_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect00_GetMetaObject(void)
{
    FUN_003b4f90();
}

void beNDMWShopSelect00_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopSelect00_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9798[0], 1);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c97a0[0], &DAT_004c97a8[0], &DAT_004c97b0[0], temp_s1);
}

