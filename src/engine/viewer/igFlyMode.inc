void FUN_0045c8e0(int arg0) {
    FUN_0045ca20();
    igMetaObject_CreateInstance(*(int *)0x58CC80, arg0);
}

igMetaObject *igFlyMode_GetMetaObject(void) {
    igMetaObject *g = g_igFlyMode_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0045ca20();
done:
    return g_igFlyMode_metaObject[0];
}

int igFlyMode_GetVTable(void) {
    struct Obj_45c970 o;
    int r;
    int *t;
    igObject_InitHeader(&o);
    o.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(o.sub);
    o.vt = &DAT_00542840[0];
    o.ref = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    o.vt = &DAT_00542840[0];
    if (&o.ref != 0) {
        t = o.ref;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void FUN_0045ca20(void)
{
    igMetaObject_RunStaticInit(igFlyMode_Register);
}

void igFlyMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFlyMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igFlyMode_GetMetaObject,
        igFlyMode_className,
        0xA0, /* instance size */
        igFlyMode_GetVTable,
        &igFlyMode_InitFields,
        0, /* extra callback item */
        g_igFlyMode_callbackList /* callback list */
    );
}

void thunk_igFlyMode_GetMetaObject(void) {
    igFlyMode_GetMetaObject();
}

void igFlyMode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_a0_7;
    void *temp_a0_6;
    void *temp_a0_5;
    void *temp_a0_4;
    void *temp_a0_3;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;
    struct V3 a;
    struct V3 b;
    struct V2 c;
    struct V3 d;
    struct V2 e;
    struct V2 f;
    struct V2 g;

    temp_s0 = (void *)g_igFlyMode_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1590[0], 0xB);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    a.x = 0;
    a.y = 0;
    a.z = 0;
    FUN_0018e470(temp_a0, &a);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    b.x = 0;
    b.y = 0;
    b.z = 0;
    FUN_0018e470(temp_a0_2, &b);
    temp_a0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    c.x = 0;
    c.y = 0;
    FUN_0018e2f0(temp_a0_3, &c);
    temp_a0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    d.x = 0;
    d.y = 0;
    d.z = 0;
    FUN_0018e470(temp_a0_4, &d);
    temp_a0_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    e.x = 0;
    e.y = 0;
    FUN_0018e2f0(temp_a0_5, &e);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    *(int *)((char *)(temp_s1) + 56) = FUN_00145d40();
    temp_a0_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    f.x = 0;
    f.y = 0;
    FUN_0018e2f0(temp_a0_6, &f);
    temp_a0_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    g.x = 0;
    g.y = 0;
    FUN_0018e2f0(temp_a0_7, &g);
    igMetaObject_NameFields(temp_s0, &DAT_004d15c0[0], &DAT_004d15f0[0], &DAT_004d1620[0], temp_s2);
}

