void beNDMWShopDevice_Create(int arg0) {
    FUN_003b67e0();
    igMetaObject_CreateInstance(*(int *)0x58ACA8, arg0);
}

void *FUN_003b6690(void) {
    unsigned char b;
    if (g_beNDMWShopDevice_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beNDMWShopDevice_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003b67e0();
done:
    return g_beNDMWShopDevice_metaObject[0];
}

int beNDMWShopDevice_GetVTable(void) {
    struct Obj_3b66e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053f800[0];
    obj.w24 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053f800[0];
    FUN_003b6090((void **)&obj.w24, (long long)(-1));
    FUN_003b6770((int **)&obj, (long long)0);
    return t;
}

int **FUN_003b6770(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0053f2c0[0];
        if (arg0 != 0) {
            *arg0 = &g_beNDMWWindowCtrl_vtable[0];
            FUN_003b2d10((beNDMWWindowCtrl *)arg0, (short)0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

void FUN_003b67e0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopDevice_Register);
}

void *beNDMWShopDevice_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopDevice_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopDevice_GetMetaObject,
        beNDMWShopDevice_className,
        0x64, /* instance size */
        beNDMWShopDevice_GetVTable,
        beNDMWShopDevice_InitFields,
        0, /* extra callback item */
        g_beNDMWShopDevice_callbackList /* callback list */
    );
}

void beNDMWShopDevice_GetMetaObject(void)
{
    FUN_003b6690();
}

igMetaObject *FUN_003b68a0(void) {
    return g_beNDMWListCtrl_metaObject[0];
}

void beNDMWShopDevice_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopDevice_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWShopDevice_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c9130();
    igMetaObject_NameFields(temp_s0, &g_beNDMWShopDevice_fieldTable[0], &DAT_004c9950[0], &DAT_004c9958[0], temp_s2);
}

