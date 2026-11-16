igMetaObject *g_beSvFormatApi_metaObject;

void beSvFormatApi_Create(int arg0) {
    beSvFormatApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588270, arg0);
}

void *beSvFormatApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvFormatApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvFormatApi_EnsureRegistered();
    }
    return g_beSvFormatApi_metaObject;
}

int beSvFormatApi_GetVTable(void) {
    union U_349900 u;
    int r;
    int *tv1, *ta1;
    int tc1;
    S_ref *q2;
    S_ref *q1;
    S_ref *q3;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beSaveApi_vtable[0];
    q1 = (S_ref *)&u.b[48];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[52];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[56];
    *(int *)q3 = 0;
    u.vt = (int)&g_beSvFormatApi_vtable[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSaveApi_vtable[0];
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return r;
}

void beSvFormatApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvFormatApi_Register);
}

void *beSvFormatApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvFormatApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFormatApi_GetMetaObjectFunction,
        "beSvFormatApi",
        0x40, /* instance size */
        beSvFormatApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvFormatApi_GetMetaObjectFunction(void)
{
    beSvFormatApi_GetMetaObject();
}

