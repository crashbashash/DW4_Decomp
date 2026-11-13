igMetaObject *igEnbayaAnimationState_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaAnimationState_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a2030();
    return g_igEnbayaAnimationState_metaObject[0];
}

int igEnbayaAnimationState_GetVTable(void) {
    union U_1a1e80 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p58;
    char *p48;
    char *pB8;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00529550[0];
    p48 = &u.b[8];
    *(int *)p48 = 0;
    p58 = &u.b[24];
    *(int *)p58 = 0;
    pB8 = &u.b[120];
    *(int *)pB8 = 0;
    u.vt = (int)&DAT_00529170[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00529550[0];
    if (pB8 != 0) {
        v1 = *(int **)pB8;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)v1);
            }
        }
    }
    if (p58 != 0) {
        v1 = *(int **)p58;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)v1);
            }
        }
    }
    return r;
}

void FUN_001a2030(void)
{
    igMetaObject_RunStaticInit(igEnbayaAnimationState_Register);
}

void igEnbayaAnimationState_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnbayaAnimationState_metaObject),
        igAnimationState_Register,
        igAnimationState_GetPublishedMetaObject,
        thunk_igEnbayaAnimationState_GetMetaObject,
        igEnbayaAnimationState_className,
        sizeof(igEnbayaAnimationState),                   /* Instance size. */
        igEnbayaAnimationState_GetVTable,
        &igEnbayaAnimationState_InitFields,
        FUN_001a2190, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEnbayaAnimationState_GetMetaObject(void) {
    igEnbayaAnimationState_GetMetaObject();
}

igMetaObject *FUN_001a20d0(void) {
    return g_igAnimationState_metaObject[0];
}

void igEnbayaAnimationState_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEnbayaAnimationState_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igEnbayaAnimationState_ctorTable[0], 2);
    *(char *)((char *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1))) + 38) = 0;
    FUN_002d3890(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)), 1);
    igMetaObject_NameFields(temp_s0, &g_igEnbayaAnimationState_fieldTable[0], &DAT_0048c350[0], &DAT_0048c358[0], temp_s1);
    FUN_002fe480(FUN_001a21a0);
}

void FUN_001a2190(void) {
    FUN_001c10f0();
}

void FUN_001a21a0(void) {
    FUN_001c1100();
}

