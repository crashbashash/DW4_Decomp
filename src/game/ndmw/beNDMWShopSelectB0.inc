void FUN_003b3f40(int arg0) {
    FUN_003b4190();
    igMetaObject_CreateInstance(*(int *)0x58AB80, arg0);
}

void *FUN_003b3f80(void) {
    struct G *g = DAT_0058ab80[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003b4190();
    }
    return DAT_0058ab80[0];
}

int beNDMWShopSelectB0_GetVTable(void) {
    struct W_3b3fd0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.w[19] = 0;
    o.w[26] = 0;
    o.vt = DAT_0053ff10;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_0053ff10;
    FUN_003b4050((struct S_3b4050 *)&o, (short)0);
    return r;
}

void *FUN_003b4050(struct S_3b4050 *arg0, short arg1) {
    struct R_3b4050 *p;
    int *h;
    int *a1;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0053f4f0[0];
        if (&arg0->f108) {
            p = arg0->f108;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f80) {
            h = arg0->f80;
            if (h != 0) {
                a1 = h - 2;
                rc = h[-1] - 1;
                h[-1] = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_0053dc30[0];
            ObjectRef_Destruct_001c6460(&arg0->f76, -1);
            ObjectRef_Destruct_00150eb0(&arg0->f72, -1);
            ObjectRef_Destruct_001c6460(&arg0->f68, -1);
            ObjectRef_Destruct_001c6460(&arg0->f64, -1);
            ObjectRef_Destruct_001c6460(&arg0->f60, -1);
            FUN_003b2f30((void **)&arg0->f56, -1);
            FUN_003b2fb0((void **)&arg0->f52, (short)(-1));
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_003b4190(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelectB0_Register);
}

void *beNDMWShopSelectB0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelectB0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelectB0_GetMetaObject,
        beNDMWShopSelectB0_className,
        0x70, /* instance size */
        beNDMWShopSelectB0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelectB0_GetMetaObject(void)
{
    FUN_003b3f80();
}

int FUN_003b4240(void) {
    return ((int *)DAT_0058abf8)[0];
}

