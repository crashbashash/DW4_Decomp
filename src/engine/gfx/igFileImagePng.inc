int FUN_00150390(int arg0) {
    FUN_00150570();
    return igMetaObject_CreateInstance(*(int *)0x55FF68, arg0);
}

igMetaObject *igFileImagePng_GetMetaObject(void)
{
    igMetaObject *g = g_igFileImagePng_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00150570();
    return g_igFileImagePng_metaObject[0];
}

int igFileImagePng_GetVTable(void) {
    union U_150420 u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[88] = 0;
    u.vt = (int)&DAT_00525d20[0];
    p = (int *)&u.b[92];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00525d20[0];
    FUN_00150180((void **)p, -1);
    FUN_00150490((S_150490 *)u.b, 0);
    return temp_s0;
}

void *FUN_00150490(struct S_150490 *arg0, short arg1) {
    void *p;
    igObject *o;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00526c50[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_00526800[0];
            if (&arg0->f58) {
                p = arg0->f58;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
            if (&arg0->f44) {
                o = (igObject *)arg0->f44;
                if (o != 0) {
                    rc = o->_refCount - 1;
                    o->_refCount = rc;
                    if (((unsigned long long) ((long long) (int) o->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(o);
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

void FUN_00150570(void)
{
    igMetaObject_RunStaticInit(igFileImagePng_Register);
}

void igFileImagePng_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileImagePng_metaObject,
        igFileImage_Register,
        igFileImage_GetPublishedMetaObject,
        thunk_igFileImagePng_GetMetaObject,
        igFileImagePng_className,
        0x60, /* instance size */
        igFileImagePng_GetVTable,
        &igFileImagePng_InitFields,
        0, /* extra callback item */
        g_igFileImagePng_callbackList /* callback list */
    );
}

void thunk_igFileImagePng_GetMetaObject(void) {
    igFileImagePng_GetMetaObject();
}

igMetaObject *FUN_00150610(void) {
    return g_igFileImage_metaObject[0];
}

void igFileImagePng_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFileImagePng_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igFileImagePng_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c4ce0();
    igMetaObject_NameFields(temp_s0, &g_igFileImagePng_fieldTable[0], &DAT_00489220[0], &DAT_00489228[0], temp_s2);
}

