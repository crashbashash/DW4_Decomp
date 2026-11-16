void beNDMWShopJunk_Create(int allocator) {
    beNDMWShopJunk_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopJunk_metaObject, allocator);
}

void *beNDMWShopJunk_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopJunk_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopJunk_EnsureRegistered();
    }
    return g_beNDMWShopJunk_metaObject;
}

int beNDMWShopJunk_GetVTable(void) {
    beNDMWShopJunk obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopJunk_vtable[0];
    obj._junkItemList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopJunk_vtable[0];
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)&obj._junkItemList, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

