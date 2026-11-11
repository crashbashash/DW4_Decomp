int FUN_004592e0(void) {
    if (DAT_0058c788[0] == 0) {
        DAT_0058c788[0] = igMetaEnum_Create(&DAT_0051eaf0[0], &DAT_004d0ae0[0], &DAT_004d0af0[0], 3);
    }
    return DAT_0058c788[0];
}

void FUN_00459340(int arg0) {
    FUN_00459e40();
    igMetaObject_CreateInstance(*(int *)0x58C790, arg0);
}

int FUN_00459380(void) {
    if (DAT_0058c790[0] == 0) {
        DAT_0058c790[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c790[0];
}

void *igViewerSceneInfoManager_GetMetaObject(void) {
    bool ok;
    if (DAT_0058c790[0] == 0) goto make;
    ok = !!(((MetaObjectFlags *)DAT_0058c790[0])->f & 4);
    if (ok != false) goto done;
make:
    FUN_00459e40();
done:;
    return (void *)DAT_0058c790[0];
}

int igViewerSceneInfoManager_GetVTable(void) {
    union U u;
    int r;
    char *p352;
    char *p344;
    char *p340;
    char *p316;
    char *p312;
    char *p308;
    char *p304;
    char *p300;
    char *p296;
    FUN_00458630(u.b);
    u.vt = (int)&DAT_005424c0[0];
    FUN_00459e30((int *)&u.b[16]);
    FUN_00459e20((int *)&u.b[20]);
    FUN_00459e10((int *)&u.b[24]);
    FUN_00459e00((int *)&u.b[28]);
    FUN_00459df0((int *)&u.b[32]);
    FUN_00459de0((int *)&u.b[36]);
    FUN_00459dd0((int *)&u.b[44]);
    FUN_00458620(&u.b[48]);
    FUN_00458610(&u.b[52]);
    FUN_00458600(&u.b[56]);
    FUN_00458600(&u.b[60]);
    FUN_00458610(&u.b[64]);
    FUN_00458600(&u.b[68]);
    FUN_00458610(&u.b[72]);
    FUN_00458610(&u.b[76]);
    FUN_00458610(&u.b[80]);
    FUN_00458610(&u.b[84]);
    FUN_00458610(&u.b[88]);
    FUN_00458600(&u.b[92]);
    FUN_00458610(&u.b[96]);
    FUN_00458610(&u.b[100]);
    FUN_00458610(&u.b[104]);
    FUN_00458610(&u.b[108]);
    FUN_00458610(&u.b[112]);
    FUN_004585f0(&u.b[116]);
    FUN_004585f0(&u.b[120]);
    FUN_004585f0(&u.b[124]);
    FUN_004585f0(&u.b[128]);
    FUN_00459dc0((int *)&u.b[132]);
    p296 = &u.b[136];
    FUN_00459db0((int *)p296);
    p300 = &u.b[140];
    FUN_00459da0((int *)p300);
    p304 = &u.b[144];
    FUN_00459d90((int *)p304);
    p308 = &u.b[148];
    FUN_002c3d50(p308);
    p312 = &u.b[152];
    FUN_00459d80((int *)p312);
    p316 = &u.b[156];
    FUN_002c3d50(p316);
    p340 = &u.b[180];
    FUN_00459d70((int *)p340);
    p344 = &u.b[184];
    FUN_00459d60((int *)p344);
    p352 = &u.b[192];
    FUN_00458600(p352);
    r = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    *(int **)u.b = &DAT_005424c0[0];
    FUN_003cafa0(p352, -1);
    FUN_00459ce0((void **)p344, -1);
    FUN_00131aa0(p340, -1);
    FUN_0014aa70(p316, -1);
    FUN_00458470(p312, -1);
    FUN_0014aa70(p308, -1);
    FUN_0044c1c0(p304, -1);
    FUN_00459c60((ObjectRefWord *)p300, -1);
    FUN_00459be0((void **)p296, -1);
    FUN_00459b60((ObjectRefWord *)&u.b[132], -1);
    FUN_00458570(&u.b[128], -1);
    FUN_00458570(&u.b[124], -1);
    FUN_00458570(&u.b[120], -1);
    FUN_00458570(&u.b[116], -1);
    FUN_0025a2b0(&u.b[112], -1);
    FUN_0025a2b0(&u.b[108], -1);
    FUN_0025a2b0(&u.b[104], -1);
    FUN_0025a2b0(&u.b[100], -1);
    FUN_0025a2b0(&u.b[96], -1);
    FUN_003cafa0(&u.b[92], -1);
    FUN_0025a2b0(&u.b[88], -1);
    FUN_0025a2b0(&u.b[84], -1);
    FUN_0025a2b0(&u.b[80], -1);
    FUN_0025a2b0(&u.b[76], -1);
    FUN_0025a2b0(&u.b[72], -1);
    FUN_003cafa0(&u.b[68], -1);
    FUN_0025a2b0(&u.b[64], -1);
    FUN_003cafa0(&u.b[60], -1);
    FUN_003cafa0(&u.b[56], -1);
    FUN_0025a2b0(&u.b[52], -1);
    FUN_004583f0(&u.b[48], -1);
    FUN_00459ae0((O *)&u.b[44], -1);
    FUN_00459a60((void **)&u.b[36], -1);
    FUN_004599e0((struct Ref **)&u.b[32], -1);
    FUN_00459960((void **)&u.b[28], -1);
    FUN_004598e0((void **)&u.b[24], -1);
    FUN_00459860((ObjectRefWord *)&u.b[20], -1);
    FUN_004597e0((struct R **)&u.b[16], -1);
    FUN_00231030(u.b, 0);
    return r;
}

struct R **FUN_004597e0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00459860(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_004598e0(void **arg0, int arg1) {
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

void **FUN_00459960(void **arg0, short arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_004599e0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_00459a60(void **arg0, long long arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_00459ae0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00459b60(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_00459be0(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00459c60(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_00459ce0(void **arg0, short arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

int *FUN_00459d60(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d70(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d80(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d90(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459da0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459db0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459dc0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459dd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459de0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459df0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e00(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e10(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e20(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e30(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_00459e40(void)
{
    igMetaObject_RunStaticInit(igViewerSceneInfoManager_Register);
}

void igViewerSceneInfoManager_Register(void) {
    ViewerLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerSceneInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManager_GetMetaObject,
        igViewerSceneInfoManager_className,
        0xC8, /* instance size */
        igViewerSceneInfoManager_GetVTable,
        FUN_00459ee0,                               /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igViewerSceneInfoManager_callbackList /* callback list */
    );
}

void thunk_igViewerSceneInfoManager_GetMetaObject(void) {
    igViewerSceneInfoManager_GetMetaObject();
}

void FUN_00459ee0(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_10;
    void *temp_s0_11;
    void *temp_s0_12;
    void *temp_s0_13;
    void *temp_s0_14;
    void *temp_s0_15;
    void *temp_s0_16;
    void *temp_s0_17;
    void *temp_s0_18;
    void *temp_s0_19;
    void *temp_s0_20;
    void *temp_s0_21;
    void *temp_s0_22;
    void *temp_s0_23;
    void *temp_s0_24;
    void *temp_s0_25;
    void *temp_s0_26;
    void *temp_s0_27;
    void *temp_s0_28;
    void *temp_s0_29;
    void *temp_s0_2;
    void *temp_s0_30;
    void *temp_s0_31;
    void *temp_s0_32;
    void *temp_s0_33;
    void *temp_s0_34;
    void *temp_s0_35;
    void *temp_s0_36;
    void *temp_s0_37;
    void *temp_s0_38;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;
    void *temp_s1;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = (void *)(DAT_0058c790[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d0b50[0], 0x2B);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_0051ee50[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_0051ee60[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058c798[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_0045a8c0();
    *(char *)((char *)(temp_s0) + 52) = 1;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    *(int *)((char *)(temp_s0_2) + 56) = FUN_0045b420();
    *(char *)((char *)(temp_s0_2) + 52) = 1;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    *(int *)((char *)(temp_s0_3) + 56) = FUN_0045aaf0();
    *(char *)((char *)(temp_s0_3) + 52) = 1;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    *(int *)((char *)(temp_s0_4) + 56) = FUN_0045de90();
    *(char *)((char *)(temp_s0_4) + 52) = 1;
    temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    *(int *)((char *)(temp_s0_5) + 56) = FUN_0045d830();
    *(char *)((char *)(temp_s0_5) + 52) = 1;
    temp_s0_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5));
    *(int *)((char *)(temp_s0_6) + 56) = FUN_00233a40();
    *(char *)((char *)(temp_s0_6) + 52) = 1;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6), -1);
    temp_s0_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7));
    *(int *)((char *)(temp_s0_7) + 56) = FUN_0044ded0();
    *(char *)((char *)(temp_s0_7) + 52) = 1;
    temp_s0_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8));
    *(int *)((char *)(temp_s0_8) + 56) = FUN_0045b8d0();
    *(char *)((char *)(temp_s0_8) + 52) = 1;
    temp_s0_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    *(int *)((char *)(temp_s0_9) + 56) = FUN_00452340();
    temp_s0_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xA));
    *(int *)((char *)(temp_s0_10) + 56) = FUN_0044ff40();
    temp_s0_11 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB));
    *(int *)((char *)(temp_s0_11) + 56) = FUN_0044ff40();
    temp_s0_12 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xC));
    *(int *)((char *)(temp_s0_12) + 56) = FUN_00452340();
    temp_s0_13 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xD));
    *(int *)((char *)(temp_s0_13) + 56) = FUN_0044ff40();
    temp_s0_14 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xE));
    *(int *)((char *)(temp_s0_14) + 56) = FUN_00452340();
    temp_s0_15 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xF));
    *(int *)((char *)(temp_s0_15) + 56) = FUN_00452340();
    temp_s0_16 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x10));
    *(int *)((char *)(temp_s0_16) + 56) = FUN_00452340();
    temp_s0_17 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x11));
    *(int *)((char *)(temp_s0_17) + 56) = FUN_00452340();
    temp_s0_18 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x12));
    *(int *)((char *)(temp_s0_18) + 56) = FUN_00452340();
    temp_s0_19 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x13));
    *(int *)((char *)(temp_s0_19) + 56) = FUN_0044ff40();
    temp_s0_20 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x14));
    *(int *)((char *)(temp_s0_20) + 56) = FUN_00452340();
    temp_s0_21 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x15));
    *(int *)((char *)(temp_s0_21) + 56) = FUN_00452340();
    temp_s0_22 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x16));
    *(int *)((char *)(temp_s0_22) + 56) = FUN_00452340();
    temp_s0_23 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x17));
    *(int *)((char *)(temp_s0_23) + 56) = FUN_00452340();
    temp_s0_24 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x18));
    *(int *)((char *)(temp_s0_24) + 56) = FUN_00452340();
    temp_s0_25 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x19));
    *(int *)((char *)(temp_s0_25) + 56) = FUN_00458c50();
    temp_s0_26 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1A));
    *(int *)((char *)(temp_s0_26) + 56) = FUN_00458c50();
    temp_s0_27 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1B));
    *(int *)((char *)(temp_s0_27) + 56) = FUN_00458c50();
    temp_s0_28 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1C));
    *(int *)((char *)(temp_s0_28) + 56) = FUN_00458c50();
    temp_s0_29 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1D));
    *(int *)((char *)(temp_s0_29) + 56) = FUN_0044d840();
    *(char *)((char *)(temp_s0_29) + 52) = 1;
    temp_s0_30 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1E));
    *(int *)((char *)(temp_s0_30) + 56) = FUN_0045d100();
    *(char *)((char *)(temp_s0_30) + 52) = 1;
    temp_s0_31 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1F));
    *(int *)((char *)(temp_s0_31) + 56) = FUN_004586a0();
    *(char *)((char *)(temp_s0_31) + 52) = 1;
    temp_s0_32 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x20));
    *(int *)((char *)(temp_s0_32) + 56) = FUN_0044fdd0();
    *(char *)((char *)(temp_s0_32) + 52) = 1;
    temp_s0_33 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x21));
    *(int *)((char *)(temp_s0_33) + 56) = igObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_33) + 52) = 1;
    temp_s0_34 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x22));
    *(int *)((char *)(temp_s0_34) + 56) = FUN_0044cdf0();
    *(char *)((char *)(temp_s0_34) + 52) = 1;
    temp_s0_35 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x23));
    *(int *)((char *)(temp_s0_35) + 56) = igObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_35) + 52) = 1;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x26));
    FUN_002dc7a0(temp_v0_3, &DAT_004d0e10[0]);
    *(int *)((char *)(temp_v0_3) + 52) = (int)(&FUN_004592e0);
    temp_s0_36 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x27));
    *(int *)((char *)(temp_s0_36) + 56) = FUN_0013a360();
    *(char *)((char *)(temp_s0_36) + 52) = 1;
    temp_s0_37 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x28));
    *(int *)((char *)(temp_s0_37) + 56) = FUN_0045a450();
    *(char *)((char *)(temp_s0_37) + 52) = 1;
    temp_s0_38 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x2A));
    *(int *)((char *)(temp_s0_38) + 56) = FUN_0044ff40();
    igMetaObject_NameFields(temp_s1, &DAT_004d0c00[0], &DAT_004d0cb0[0], &DAT_004d0d60[0], temp_s2);
}

