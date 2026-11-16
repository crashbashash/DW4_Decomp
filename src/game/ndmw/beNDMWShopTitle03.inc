igMetaObject *g_beNDMWShopTitle03_metaObject;

void beNDMWShopTitle03_Create(int allocator) {
    beNDMWShopTitle03_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopTitle03_metaObject, allocator);
}

void *beNDMWShopTitle03_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopTitle03_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopTitle03_EnsureRegistered();
    }
    return g_beNDMWShopTitle03_metaObject;
}

int beNDMWShopTitle03_GetVTable(void) {
    beNDMWShopTitle03 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopTitle03_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopTitle03_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void *beNDMWWindow_Destroy(beNDMWWindowCtrl *self, short flags) {
    if (self != 0) {
        self->_vtable = (int)&g_beNDMWWindow_vtable[0];
        if (&self->_modelCloseSeqNameList != 0) {
            igRelease((igObject *)self->_modelCloseSeqNameList);
        }
        if (&self->_modelCloseRamNoList != 0) {
            igRelease((igObject *)self->_modelCloseRamNoList);
        }
        if (&self->_modelCloseInfoNameList != 0) {
            igRelease((igObject *)self->_modelCloseInfoNameList);
        }
        if (&self->_textCloseNameList != 0) {
            igRelease((igObject *)self->_textCloseNameList);
        }
        if (&self->_textCloseTypeList != 0) {
            igRelease((igObject *)self->_textCloseTypeList);
        }
        if (&self->_mother != 0) {
            igRelease((igObject *)self->_mother);
        }
        if (&self->_subWindow != 0) {
            igRelease((igObject *)self->_subWindow);
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igSmartPointer<igObject> *beNDMWWindow_igSmartPointer_beNDMWWindow_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWWindowList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

beNDMWWindowTitle *beNDMWWindowTitle_Destroy(beNDMWWindowTitle *self, short flags) {
    if (self != 0) {
        *(int **)&self->_vtable = &g_beNDMWWindowTitle_vtable[0];
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

void beNDMWShopTitle03_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle03_Register);
}

void *beNDMWShopTitle03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopTitle03_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle03_GetMetaObjectFunction,
        "beNDMWShopTitle03",
        0x50, /* instance size */
        beNDMWShopTitle03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopTitle03_GetMetaObjectFunction(void)
{
    beNDMWShopTitle03_GetMetaObject();
}

igMetaObject *beNDMWWindowTitle_GetPublishedMetaObject(void) {
    return g_beNDMWWindowTitle_metaObject;
}

