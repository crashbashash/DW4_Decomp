void beNDMWShopJunk_Create(int arg0) {
    beNDMWShopJunk_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopJunk_metaObject, arg0);
}

void *beNDMWShopJunk_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopJunk_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopJunk_EnsureRegistered();
    }
    return g_beNDMWShopJunk_metaObject;
}

int beNDMWShopJunk_GetVTable(void) {
    struct Obj_3b63a0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.vt = (&g_beNDMWShopJunk_vtable[0]);
    obj.f5C = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWShopJunk_vtable[0]);
    igSmartPointer_beNDMWItemBaseList_Destruct((void **)&obj.f5C, (long long)(-1));
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return temp_s0;
}

