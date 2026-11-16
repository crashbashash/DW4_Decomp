igMetaObject *g_beNDMWShopSelectB0_metaObject;

void beNDMWShopSelectB0_Create(int allocator) {
    beNDMWShopSelectB0_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelectB0_metaObject, allocator);
}

void *beNDMWShopSelectB0_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelectB0_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelectB0_EnsureRegistered();
    }
    return g_beNDMWShopSelectB0_metaObject;
}

int beNDMWShopSelectB0_GetVTable(void) {
    beNDMWShopSelectB0 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    obj._infoName = 0;
    obj._decideList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopSelectB0_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopSelectB0_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void *beNDMWWindowSelect_Destroy(beNDMWWindowSelect *self, short flags) {
    if (self != 0) {
        *(int **)&self->_vtable = &g_beNDMWWindowSelect_vtable[0];
        if (&self->_decideList != 0) {
            igRelease((igObject *)self->_decideList);
        }
        if (&self->_infoName != 0) {
            releaseString((const char *)self->_infoName);
        }
        if (self != 0) {
            *(int **)&self->_vtable = &g_beNDMWWindow_vtable[0];
            igSmartPointer_igStringRefList_Destruct(&self->_modelCloseSeqNameList, -1);
            igSmartPointer_igIntList_Destruct(&self->_modelCloseRamNoList, -1);
            igSmartPointer_igStringRefList_Destruct(&self->_modelCloseInfoNameList, -1);
            igSmartPointer_igStringRefList_Destruct(&self->_textCloseNameList, -1);
            igSmartPointer_igStringRefList_Destruct(&self->_textCloseTypeList, -1);
            beNDMWWindow_igSmartPointer_beNDMWWindow_Destruct((igSmartPointer<igObject> *)&self->_mother, -1);
            igSmartPointer_beNDMWWindowList_Destruct((igSmartPointer<igObject> *)&self->_subWindow, -1);
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beNDMWShopSelectB0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelectB0_Register);
}

void *beNDMWShopSelectB0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelectB0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelectB0_GetMetaObjectFunction,
        "beNDMWShopSelectB0",
        0x70, /* instance size */
        beNDMWShopSelectB0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelectB0_GetMetaObjectFunction(void)
{
    beNDMWShopSelectB0_GetMetaObject();
}

igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void) {
    return g_beNDMWWindowSelect_metaObject;
}

