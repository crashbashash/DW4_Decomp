int FUN_0014c290(void) {
    if (DAT_0055fb38[0] == 0) {
        DAT_0055fb38[0] = igMetaEnum_Create(&IG_GFX_SPRITE_SIZE_SPACE[0], &DAT_00488860[0], &DAT_00488868[0], 2);
    }
    return DAT_0055fb38[0];
}

igMetaObject *FUN_0014c2f0(void) {
    if (g_igPointSpriteExt_metaObject[0] == 0) {
        g_igPointSpriteExt_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igPointSpriteExt_metaObject[0];
}

igMetaObject *igPointSpriteExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPointSpriteExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014c670();
    return g_igPointSpriteExt_metaObject[0];
}

int igPointSpriteExt_GetVTable(void) {
    struct PointSpriteExtInstance o;
    int r;
    char *pa = (char *)&o;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = &DAT_00526600[0];
    o.f16 = 0;
    o.f24 = 0;
    igMatrix44f_SetIdentity((float *)&o.t[8]);
    igMatrix44f_SetIdentity((float *)(pa + 104));
    igMatrix44f_SetIdentity((float *)(pa + 168));
    igMatrix44f_SetIdentity((float *)(pa + 232));
    igMatrix44f_SetIdentity((float *)(pa + 296));
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00526600[0];
    FUN_001338d0(&o.f24, -1);
    FUN_0014c580((O_14c580 *)&o, 0);
    return r;
}

O *FUN_0014c440(O *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00526600[0];
        if (&arg0->m24) {
            S1 *t0 = arg0->m24;
            if (t0) { t0->f4 -= 1; if ((t0->f4 & 0x7fffff) == 0) igObject_Destroy(t0); }
        }
        if (arg0) {
            arg0->vt = &DAT_00527020[0];
            if (arg0) {
                arg0->vt = &DAT_00530a10[0];
                if (&arg0->m16) {
                    S1 *t = arg0->m16;
                    if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
                }
                if (&arg0->m8) {
                    S1 *t2 = arg0->m8;
                    if (t2) { t2->f4 -= 1; if ((t2->f4 & 0x7fffff) == 0) igObject_Destroy(t2); }
                }
            }
        }
        if (arg1 > 0) thunk_Memory_FreeBuffer(arg0);
    }
    return arg0;
}

O_14c580 *FUN_0014c580(O_14c580 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00527020[0];
        if (arg0) {
            arg0->vt = &DAT_00530a10[0];
            if (&arg0->m16) {
                S1 *t = arg0->m16;
                if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
            }
            if (&arg0->m8) {
                S1 *t2 = arg0->m8;
                if (t2) { t2->f4 -= 1; if ((t2->f4 & 0x7fffff) == 0) igObject_Destroy(t2); }
            }
        }
        if (arg1 > 0) thunk_Memory_FreeBuffer(arg0);
    }
    return arg0;
}

void FUN_0014c670(void)
{
    igMetaObject_RunStaticInit(igPointSpriteExt_Register);
}

void igPointSpriteExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPointSpriteExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igPointSpriteExt_GetMetaObject,
        igPointSpriteExt_className,
        0x188, /* instance size */
        igPointSpriteExt_GetVTable,
        &igPointSpriteExt_InitFields,
        0, /* extra callback item */
        g_igPointSpriteExt_callbackList /* callback list */
    );
}

void thunk_igPointSpriteExt_GetMetaObject(void) {
    igPointSpriteExt_GetMetaObject();
}

void igPointSpriteExt_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_s1;

    temp_s1 = (void *)(g_igPointSpriteExt_metaObject[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igPointSpriteExt_ctorTable[0], 0x12);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0014a040();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    ((igMetaField *)temp_s2)->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0014b980();
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    igFloatMetaField_SetDefault(temp_v0, 1.0f);
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    igEnumMetaField_SetDefaultValue(temp_v0_2, &DAT_004889b8[0]);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_0014c290);
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11))->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &g_igPointSpriteExt_fieldTable[0], &DAT_00488920[0], &DAT_00488970[0], temp_s0);
    *(int *)((char *)(g_igPointSpriteExt_metaObject[0]) + 60) = (int)(&thunk_igPsx2PointSpriteExt_GetMetaObject);
}

