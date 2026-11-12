void FUN_003b4410(int arg0) {
    FUN_003b4520();
    igMetaObject_CreateInstance(*(int *)0x58AB90, arg0);
}

void *FUN_003b4450(void) {
    bool ok;
    if (DAT_0058ab90[0] == 0) goto make;
    ok = !!(DAT_0058ab90[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003b4520();
done:;
    return DAT_0058ab90[0];
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
    obj.vt = (&DAT_0053fff0[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0053fff0[0]);
    FUN_003b4050((struct S_3b4050 *)&obj, (short)0);
    return temp_s0;
}

void FUN_003b4520(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect52_Register);
}

void *beNDMWShopSelect52_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect52_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect52_GetMetaObject,
        beNDMWShopSelect52_className,
        0x70, /* instance size */
        beNDMWShopSelect52_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect52_GetMetaObject(void)
{
    FUN_003b4450();
}

