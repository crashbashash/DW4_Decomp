igMetaObject *FUN_0014f420(void)
{
    unsigned char ready;
    if (g_igExternalImageEntry_metaObject[0] != 0) {
        ready = (g_igExternalImageEntry_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0014f6d0();
done:
    return g_igExternalImageEntry_metaObject[0];
}

int igExternalImageEntry_GetVTable(void) {
    struct W_14f470 o;
    int r;
    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[6] = 0;
    o.f[7] = 0;
    o.f[9] = 0;
    o.vt = DAT_00526930;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = DAT_00526930;
    FUN_0014f580((W_14f580 *)&o, 0);
    return r;
}

void *FUN_0014f4e0(struct S *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00530900[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_00524950[0];
            if (&arg0->f8) {
                p = arg0->f8;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

W_14f580 *FUN_0014f580(W_14f580 *t, short flag)
{
    if (t != 0) {
        t->vt = DAT_00530360;
        t->s40.~Str();
        t->s32.~Str();
        t->s28.~Str();
        if (t != 0) {
            t->vt = DAT_00530900;
            if (t != 0) {
                t->vt = DAT_00524950;
                t->s8.~Str();
            }
        }
        if (flag > 0) {
            thunk_FUN_002ed460__002ff810(t);
        }
    }
    return t;
}

void FUN_0014f6d0(void)
{
    igMetaObject_RunStaticInit(igExternalImageEntry_Register);
}

void igExternalImageEntry_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExternalImageEntry_metaObject,
        igExternalDirEntry_Register,
        igExternalDirEntry_GetPublishedMetaObject,
        thunk_igExternalImageEntry_GetMetaObject_0014f750,
        igExternalImageEntry_className,
        0x2C, /* instance size */
        igExternalImageEntry_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_FUN_0014f420(void) {
    FUN_0014f420();
}

int FUN_0014f760(void) {
    return g_igExternalDirEntry_metaObject[0];
}

igMetaObject *FUN_0014f770(void) {
    if (g_igDisableExt_metaObject[0] == 0) {
        g_igDisableExt_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igDisableExt_metaObject[0];
}

