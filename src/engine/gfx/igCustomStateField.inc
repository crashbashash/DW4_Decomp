void FUN_0014eae0(int arg0) {
    FUN_0014ecd0();
    igMetaObject_CreateInstance(*(int *)0x55FE50, arg0);
}

igMetaObject *igCustomStateField_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ecd0();
    return g_igCustomStateField_metaObject[0];
}

int igCustomStateField_GetVTable(void) {
    union U_14eb70 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00526df0[0];
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00526df0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void **FUN_0014ec50(void **arg0, int arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0014ecd0(void)
{
    igMetaObject_RunStaticInit(igCustomStateField_Register);
}

void igCustomStateField_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateField_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igCustomStateField_GetMetaObject,
        igCustomStateField_className,
        0x14, /* instance size */
        igCustomStateField_GetVTable,
        &igCustomStateField_InitFields,
        0, /* extra callback item */
        g_igCustomStateField_callbackList /* callback list */
    );
}

void thunk_igCustomStateField_GetMetaObject(void) {
    igCustomStateField_GetMetaObject();
}

void igCustomStateField_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCustomStateField_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCustomStateField_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002beca0();
    igMetaObject_NameFields(temp_s0, &g_igCustomStateField_fieldTable[0], &DAT_00489030[0], &DAT_00489038[0], temp_s2);
}

