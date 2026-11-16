igMetaObject *g_beSvPlatDataPC_metaObject;

void *beSvPlatDataPC_GetMetaObject(void) {
    bool ok;
    if (g_beSvPlatDataPC_metaObject == 0) goto make;
    ok = !!(g_beSvPlatDataPC_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beSvPlatDataPC_EnsureRegistered();
done:;
    return g_beSvPlatDataPC_metaObject;
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
    u.vt = (int)&g_beSvPlatBaseData_vtable[0];
    u.vt = (int)&g_beSvPlatDataPC_vtable[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSvPlatBaseData_vtable[0];
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
        arg0->vt = &g_beSvPlatBaseData_vtable[0];
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
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void beSvPlatDataPC_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPC_Register);
}

void *beSvPlatDataPC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataPC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPC_GetMetaObjectFunction,
        "beSvPlatDataPC",
        0x18, /* instance size */
        beSvPlatDataPC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPlatDataPC_GetMetaObjectFunction(void)
{
    beSvPlatDataPC_GetMetaObject();
}

igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void) {
    return g_beSvPlatBaseData_metaObject;
}

