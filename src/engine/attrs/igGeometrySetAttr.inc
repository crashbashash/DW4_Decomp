int FUN_00136c80(void) {
    if (DAT_0055f110[0] == 0) {
        DAT_0055f110[0] = igMetaEnum_Create(&DAT_004d55c0[0], &DAT_00486478[0], &DAT_00486488[0], 3);
    }
    return DAT_0055f110[0];
}

igMetaObject *igGeometrySetAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometrySetAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00136e90();
    return g_igGeometrySetAttr_metaObject[0];
}

int igGeometrySetAttr_GetVTable(void) {
    union U_136d30 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005237b0[0];
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005237b0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
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
    return temp_s0;
}

void **FUN_00136e10(void **arg0, int arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00136e90(void)
{
    igMetaObject_RunStaticInit(igGeometrySetAttr_Register);
}

void igGeometrySetAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometrySetAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometrySetAttr_GetMetaObject,
        igGeometrySetAttr_className,
        0x20, /* instance size */
        igGeometrySetAttr_GetVTable,
        &igGeometrySetAttr_InitFields,
        0, /* extra callback item */
        g_igGeometrySetAttr_callbackList /* callback list */
    );
}

void thunk_igGeometrySetAttr_GetMetaObject(void) {
    igGeometrySetAttr_GetMetaObject();
}

void igGeometrySetAttr_InitFields(void) {
    int temp_s0;
    struct F_136f30 *temp_s2;
    struct F_136f30 *temp_s2_2;
    struct F_136f30 *temp_v0;
    struct F_136f30 *temp_v0_2;
    void *temp_s1;

    temp_s1 = (void *)g_igGeometrySetAttr_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004864b0[0], 5);
    temp_s2 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    temp_s2->f56 = FUN_0014a040();
    temp_s2->f38 = 0;
    temp_s2->f40 = 1;
    temp_s2->f39 = 1;
    temp_s2->f44 = 3;
    temp_v0 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    FUN_002ea4b0(temp_v0, -1);
    temp_v0->f38 = 0;
    temp_v0->f40 = 4;
    temp_v0->f39 = 4;
    temp_v0->f44 = 3;
    temp_s2_2 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    temp_s2_2->f56 = (int)FUN_0013a4d0();
    temp_v0_2 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    FUN_002dc7a0(temp_v0_2, &DAT_00486528[0]);
    temp_v0_2->f38 = 0;
    temp_v0_2->f52 = (int)(&FUN_00136c80);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1);
    igMetaObject_NameFields(temp_s1, &DAT_004864d0[0], &DAT_004864f0[0], &DAT_00486510[0], temp_s0);
}

