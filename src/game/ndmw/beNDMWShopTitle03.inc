void FUN_003b2c00(int arg0) {
    FUN_003b30f0();
    igMetaObject_CreateInstance(*(int *)0x58AB38, arg0);
}

void *FUN_003b2c40(void) {
    igMetaObject *g = g_beNDMWShopTitle03_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b30f0();
    }
    return g_beNDMWShopTitle03_metaObject[0];
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
    obj.vt = &DAT_00540300[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00540300[0];
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
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_003b2f30(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_003b2fb0(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

int **FUN_003b3030(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0053f790[0];
        if (arg0 != 0) {
            *arg0 = &g_beNDMWWindow_vtable[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x4C), -1);
            ObjectRef_Destruct_00150eb0((int **)((char *)arg0 + 0x48), -1);
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x44), -1);
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x40), -1);
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x3C), -1);
            FUN_003b2f30((void **)((int **)((char *)arg0 + 0x38)), -1);
            FUN_003b2fb0((void **)((int **)((char *)arg0 + 0x34)), (short)(-1));
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_003b30f0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle03_Register);
}

void *beNDMWShopTitle03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopTitle03_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle03_GetMetaObject,
        beNDMWShopTitle03_className,
        0x50, /* instance size */
        beNDMWShopTitle03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopTitle03_GetMetaObject(void)
{
    FUN_003b2c40();
}

igMetaObject *FUN_003b31a0(void) {
    return g_beNDMWWindowTitle_metaObject[0];
}

