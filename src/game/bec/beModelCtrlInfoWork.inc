void FUN_00350020(int arg0) {
    FUN_00350fb0();
    igMetaObject_CreateInstance(*(int *)0x588888, arg0);
}

igMetaObject *FUN_00350060(void) {
    if (g_beModelCtrlInfoWork_metaObject[0] == 0) {
        g_beModelCtrlInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlInfoWork_metaObject[0];
}

void *FUN_003500b0(void) {
    igMetaObject *g = g_beModelCtrlInfoWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00350fb0();
    }
    return g_beModelCtrlInfoWork_metaObject[0];
}

void *FUN_00350410(beNDMWMdlPlayer2InfoWork *arg0, long long arg1) {
    void *p;
    igObject *o;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&g_beModelCtrlInfoWork_vtable[0];
        OBJ(arg0->_baseAABox)
        OBJ(arg0->_subCommand)
        STR(arg0->_hitParentName)
        OBJ(arg0->_hitBody)
        OBJ(arg0->_debugHitBoxNode)
        OBJ(arg0->_rideOnData)
        OBJ(arg0->_moveObjectList)
        STR(arg0->_posLockBoneName)
        STR(arg0->_posLockModelName)
        OBJ(arg0->_posLockTrc)
        OBJ(arg0->_posLockNode)
        STR(arg0->_keyEventName)
        STR(arg0->_targetSpc1)
        STR(arg0->_targetKind)
        STR(arg0->_targetMode)
        OBJ(arg0->_aI)
        STR(arg0->_wCheckName)
        OBJ(arg0->_pdMoveDataList)
        STR(arg0->_luaFHit)
        STR(arg0->_luaWHit)
        STR(arg0->_luaBHit)
        OBJ(arg0->_labelOffsetList)
        OBJ(arg0->_labelNameList)
        OBJ(arg0->_labelSeqList)
        OBJ(arg0->_comData)
        STR(arg0->_seqCodeName)
        OBJ(arg0->_hp)
        OBJ(arg0->_mHp)
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_00350b10(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00350b90(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_00350c10(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_00350c90(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00350d10(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_00350d90(void **arg0, short arg1) {
    S_temp_a0_350d90 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_350d90 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00350e10(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_00350e90(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

int *FUN_00350f10(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00350f20(int *p)
{
    *p = 0;
    return p;
}

int *FUN_00350f30(int *p)
{
    *p = 0;
    return p;
}

int *FUN_00350f40(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00350f50(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00350f60(int *p)
{
    *p = 0;
    return p;
}

int *FUN_00350f70(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00350f80(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00350f90(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00350fa0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_00350fb0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoWork_Register);
}

void *beModelCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoWork_GetMetaObject,
        beModelCtrlInfoWork_className,
        0xec, /* instance size */
        beModelCtrlInfoWork_GetVTable,
        beModelCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoWork_callbackList /* callback list */
    );
}

void beModelCtrlInfoWork_GetMetaObject(void)
{
    FUN_003500b0();
}

void beModelCtrlInfoWork_InitFields(void) {
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_14;
    void *temp_s2_15;
    void *temp_s2_16;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlInfoWork_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beModelCtrlInfoWork_ctorTable[0], 0x32);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00365550();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00365550();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), -1);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_003567d0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002b9120();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002b9120();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igIntList_GetOrCreateMetaObject();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 0);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF), 1);
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_002c9780();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12), 0);
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)FUN_00352180();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x16), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x17), 0);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1C), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x20), -1.0f);
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x22));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)FUN_0034fd40();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x23));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)FUN_00353240();
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x27));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)FUN_003527b0();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x28));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)FUN_00351e60();
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x29));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_0019f210();
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2A));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = (int)FUN_00352410();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2B), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2C), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2D), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2E), 0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x2F), 0);
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x30));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = (int)FUN_0034f210();
    ((igRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x31));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_0018a6a0();
    igMetaObject_NameFields(temp_s0, &g_beModelCtrlInfoWork_fieldTable[0], &DAT_004c4f70[0], &DAT_004c5040[0], temp_s1);
}

