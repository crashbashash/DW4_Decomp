void FUN_00349af0(int arg0) {
    FUN_00349cc0();
    igMetaObject_CreateInstance(*(int *)0x588278, arg0);
}

void *FUN_00349b30(void) {
    bool ok;
    if (g_beSvFileFindApi_metaObject[0] == 0) goto make;
    ok = !!(g_beSvFileFindApi_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00349cc0();
done:;
    return g_beSvFileFindApi_metaObject[0];
}

int beSvFileFindApi_GetVTable(void) {
    union U_349b80 u;
    int temp_s2;
    int *q2;
    int *q1;
    int *q3;
    igObject *a0;

    igObject_InitHeader(u.b);
    q1 = &u.o._imageWork;
    *q1 = 0;
    u.o._vtable = (int)(&DAT_0053c070[0]);
    q2 = &u.o._mountWork;
    *q2 = 0;
    q3 = &u.o._iconWork;
    *q3 = 0;
    u.o._vtable = (int)(&DAT_0053bf90[0]);
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.o._vtable = (int)(&DAT_0053c070[0]);
    if (q3 != 0) {
        a0 = (igObject *)*q3;
        if (a0 != 0) {
            a0->_refCount = (int)a0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (q2 != 0) {
        a0 = (igObject *)*q2;
        if (a0 != 0) {
            a0->_refCount = (int)a0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (q1 != 0) {
        a0 = (igObject *)*q1;
        if (a0 != 0) {
            a0->_refCount = (int)a0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return temp_s2;
}

void FUN_00349cc0(void)
{
    igMetaObject_RunStaticInit(beSvFileFindApi_Register);
}

void *beSvFileFindApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvFileFindApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFileFindApi_GetMetaObject,
        beSvFileFindApi_className,
        0x54, /* instance size */
        beSvFileFindApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvFileFindApi_GetMetaObject(void)
{
    FUN_00349b30();
}

