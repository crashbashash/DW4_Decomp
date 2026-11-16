igMetaObject *g_beNDMWShopCtrl00_metaObject;

/* Factory used by the SUBWND lifecycle; registers on demand, then creates the instance from the
 * (possibly just published) metadata. */
beNDMWShopCtrl00 *beNDMWShopCtrl00_Create(int allocator) {
    beNDMWShopCtrl00_EnsureRegistered();
    return (beNDMWShopCtrl00 *)igMetaObject_CreateInstance(g_beNDMWShopCtrl00_metaObject, (igMemoryPoolView *)allocator);
}

/* Lazy accessor. A null handle, or one whose _validity word lacks bit 4, runs the registrar; the
 * handle is re-read afterwards because the callback may publish a different object. */
igMetaObject *beNDMWShopCtrl00_ResolveMetaObject(){
    igMetaObject *meta=g_beNDMWShopCtrl00_metaObject;
    if(!meta||((meta->_validity&4)!=0)==false){
        beNDMWShopCtrl00_EnsureRegistered();
    }
    return g_beNDMWShopCtrl00_metaObject;
}

int beNDMWShopCtrl00_GetVTable(void) {
    beNDMWWindowCtrl o;
    int r;
    igObject_InitHeader(&o);
    o._subWindow = 0;
    o._mother = 0;
    o._textCloseTypeList = 0;
    o._textCloseNameList = 0;
    o._modelCloseInfoNameList = 0;
    o._modelCloseRamNoList = 0;
    o._modelCloseSeqNameList = 0;
    o._vtable = (int)&g_beNDMWShopCtrl00_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem) + 916));
    o._vtable = (int)&g_beNDMWShopCtrl00_vtable[0];
    beNDMWWindowCtrl_Destroy(&o, (long long)0);
    return r;
}

void beNDMWShopCtrl00_EnsureRegistered(){igMetaObject_RunStaticInit(beNDMWShopCtrl00_Register);}

CallbackArray *beNDMWShopCtrl00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl00_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        (igMetaObjectCallback)beNDMWShopCtrl00_GetMetaObject,
        "beNDMWShopCtrl00",
        0x54, /* instance size */
        beNDMWShopCtrl00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *beNDMWShopCtrl00_GetMetaObject(){return beNDMWShopCtrl00_ResolveMetaObject();}

