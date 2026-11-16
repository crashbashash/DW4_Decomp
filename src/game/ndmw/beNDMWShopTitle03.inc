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
    struct Obj_3b2c90 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &g_beNDMWShopTitle03_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopTitle03_vtable[0];
    FUN_003b3030((int **)&obj, (long long)0);
    return t;
}

void *FUN_003b2d10(beNDMWWindowCtrl *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&g_beNDMWWindow_vtable[0];
        if (&arg0->_modelCloseSeqNameList) {
            p = (igObject *)arg0->_modelCloseSeqNameList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_modelCloseRamNoList) {
            p = (igObject *)arg0->_modelCloseRamNoList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_modelCloseInfoNameList) {
            p = (igObject *)arg0->_modelCloseInfoNameList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_textCloseNameList) {
            p = (igObject *)arg0->_textCloseNameList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_textCloseTypeList) {
            p = (igObject *)arg0->_textCloseTypeList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_mother) {
            p = (igObject *)arg0->_mother;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_subWindow) {
            p = (igObject *)arg0->_subWindow;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *beNDMWShopTitle03_igSmartPointer_beNDMWWindow_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *FUN_003b2fb0(igSmartPointer<igObject> *self,int delete_storage) {
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

int **FUN_003b3030(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &g_beNDMWWindowTitle_vtable[0];
        if (arg0 != 0) {
            *arg0 = &g_beNDMWWindow_vtable[0];
            igSmartPointer_igStringRefList_Destruct((int **)((char *)arg0 + 0x4C), -1);
            igSmartPointer_igIntList_Destruct((int **)((char *)arg0 + 0x48), -1);
            igSmartPointer_igStringRefList_Destruct((int **)((char *)arg0 + 0x44), -1);
            igSmartPointer_igStringRefList_Destruct((int **)((char *)arg0 + 0x40), -1);
            igSmartPointer_igStringRefList_Destruct((int **)((char *)arg0 + 0x3C), -1);
            beNDMWShopTitle03_igSmartPointer_beNDMWWindow_Destruct((igSmartPointer<igObject> *)((int **)((char *)arg0 + 0x38)), -1);
            FUN_003b2fb0((igSmartPointer<igObject> *)((int **)((char *)arg0 + 0x34)), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
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

