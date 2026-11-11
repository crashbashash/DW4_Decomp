int FUN_00146d90(void) {
    if (DAT_0055f730[0] == 0) {
        DAT_0055f730[0] = igMetaEnum_Create(&DAT_004d6ce8[0], &DAT_00487510[0], &DAT_00487520[0], 4);
    }
    return DAT_0055f730[0];
}

igMetaObject *igPsx2ControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ControllerManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146ee0();
    return g_igPsx2ControllerManager_metaObject[0];
}

int igPsx2ControllerManager_GetVTable(void) {
    union U_146e40 u;
    int temp_s0;
    S_ref *q1;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00524f00[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_00524c90[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00524f00[0]);
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

void FUN_00146ee0(void)
{
    igMetaObject_RunStaticInit(igPsx2ControllerManager_Register);
}

void igPsx2ControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ControllerManager_metaObject,
        igControllerManager_Register,
        igControllerManager_GetPublishedMetaObject,
        thunk_igPsx2ControllerManager_GetMetaObject,
        igPsx2ControllerManager_className,
        0x14, /* instance size */
        igPsx2ControllerManager_GetVTable,
        &igPsx2ControllerManager_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_00146f60(void) {
    return DAT_0055f698[0];
}

void igPsx2ControllerManager_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f738[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487530[0], 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00487570[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00146d90);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00487540[0], &DAT_00487550[0], &DAT_00487560[0], temp_s2);
}

