igMetaObject *g_beNDMWShopSelect52_metaObject;

void beNDMWShopSelect52_Create(int arg0) {
    beNDMWShopSelect52_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelect52_metaObject, arg0);
}

void *beNDMWShopSelect52_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWShopSelect52_metaObject == 0) goto make;
    ok = !!(g_beNDMWShopSelect52_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWShopSelect52_EnsureRegistered();
done:;
    return g_beNDMWShopSelect52_metaObject;
}

int beNDMWShopSelect52_GetVTable(void) {
    struct Obj_3b44a0 obj;
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
    obj.vt = (&g_beNDMWShopSelect52_vtable[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWShopSelect52_vtable[0]);
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return temp_s0;
}

void beNDMWShopSelect52_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect52_Register);
}

void *beNDMWShopSelect52_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect52_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect52_GetMetaObjectFunction,
        "beNDMWShopSelect52",
        0x70, /* instance size */
        beNDMWShopSelect52_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect52_GetMetaObjectFunction(void)
{
    beNDMWShopSelect52_GetMetaObject();
}

