void *FUN_00347060(void) {
    bool ok;
    if (DAT_00588038[0] == 0) goto make;
    ok = !!(DAT_00588038[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003471f0();
done:;
    return DAT_00588038[0];
}

int beSvPlatDataPC_GetVTable(void) {
    union U_3470b0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[12];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00538d40[0];
    u.vt = (int)&DAT_00538ce0[0];
    s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00538d40[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return s0;
}

O_347150 *FUN_00347150(O_347150 *arg0, short arg1) {
    Q *t;

    if (arg0 != 0) {
        arg0->vt = &DAT_00538d40[0];
        if (&arg0->m != 0) {
            t = arg0->m;
            if (t != 0) {
                t->f4 -= 1;
                if ((t->f4 & 0x7fffff) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_003471f0(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPC_Register);
}

void *beSvPlatDataPC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataPC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPC_GetMetaObject,
        beSvPlatDataPC_className,
        0x18, /* instance size */
        beSvPlatDataPC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPlatDataPC_GetMetaObject(void)
{
    FUN_00347060();
}

int FUN_003472a0(void) {
    return ((int *)DAT_00588308)[0];
}

