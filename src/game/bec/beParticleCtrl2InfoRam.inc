void *FUN_0034bcc0(void) {
    igMetaObject *g = g_beParticleCtrl2InfoRam_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034bec0();
    }
    return g_beParticleCtrl2InfoRam_metaObject[0];
}

int beParticleCtrl2InfoRam_GetVTable(void) {
    struct Obj_34bd10 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[9] = 0;
    obj.vt = &DAT_00538740[0];
    obj.w[10] = 0;
    obj.w[11] = 0;
    obj.w[12] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00538740[0];
    FUN_0034be40((ObjectRefWord *)(&obj.w[12]), -1);
    FUN_0034bdc0((void **)(&obj.w[11]), (short)(-1));
    FUN_001a7580(&obj.w[10], -1);
    FUN_0033e920((S *)((int *)&obj), (long long)0);
    return t;
}

void **FUN_0034bdc0(void **arg0, short arg1) {
    S_temp_a0_34bdc0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_34bdc0 *)(*arg0);
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

ObjectRefWord *FUN_0034be40(ObjectRefWord *self,int delete_storage) {
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

void FUN_0034bec0(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2InfoRam_Register);
}

void *beParticleCtrl2InfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beParticleCtrl2InfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beParticleCtrl2InfoRam_GetMetaObject,
        beParticleCtrl2InfoRam_className,
        0x38, /* instance size */
        beParticleCtrl2InfoRam_GetVTable,
        beParticleCtrl2InfoRam_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoRam_callbackList /* callback list */
    );
}

void beParticleCtrl2InfoRam_GetMetaObject(void)
{
    FUN_0034bcc0();
}

void beParticleCtrl2InfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beParticleCtrl2InfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c45c0[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00196190();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0036e5c0();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0034c080();
    igMetaObject_NameFields(temp_s0, &DAT_004c45d0[0], &DAT_004c45e0[0], &DAT_004c45f0[0], temp_s2);
}

