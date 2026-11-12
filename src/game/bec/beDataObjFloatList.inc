void FUN_00364220(int arg0) {
    FUN_00364390();
    igMetaObject_CreateInstance(*(int *)0x589848, arg0);
}

void *FUN_00364260(void) {
    igMetaObject *g = g_beDataObjFloatList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00364390();
    }
    return g_beDataObjFloatList_metaObject[0];
}

int beDataObjFloatList_GetVTable(void) {
    union U_3642b0 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q38;
    void **q3c;

    igObject_InitHeader(u.b);
    q38 = &u.p[2];
    *q38 = 0;
    u.w[0] = (int)(&DAT_005354d0[0]);
    q3c = &u.p[3];
    *q3c = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_005354d0[0]);
    if (q3c != 0) {
        a = (struct Rc *)*q3c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q38 != 0) {
        c = (char *)*q38;
        if (c != 0) {
            a1 = (int *)(c - 8);
            v0 = *(int *)(c - 4) - 1;
            *(int *)(c - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_00364390(void)
{
    igMetaObject_RunStaticInit(beDataObjFloatList_Register);
}

void *beDataObjFloatList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjFloatList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjFloatList_GetMetaObject,
        beDataObjFloatList_className,
        0x10, /* instance size */
        beDataObjFloatList_GetVTable,
        beDataObjFloatList_InitFields,
        0, /* extra callback item */
        g_beDataObjFloatList_callbackList /* callback list */
    );
}

void beDataObjFloatList_GetMetaObject(void)
{
    FUN_00364260();
}

void beDataObjFloatList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjFloatList_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7118[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c7120[0], &DAT_004c7128[0], &DAT_004c7130[0], temp_s2);
}

