igMetaObject *g_beParticleCtrl2InfoRam_metaObject;
igMetaField *g_beParticleCtrl2InfoRam_transformMetaField;
igMetaField *g_beParticleCtrl2InfoRam_particleTimerMetaField;
igMetaField *g_beParticleCtrl2InfoRam_workMetaField;

void *beParticleCtrl2InfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beParticleCtrl2InfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beParticleCtrl2InfoRam_EnsureRegistered();
    }
    return g_beParticleCtrl2InfoRam_metaObject;
}

int beParticleCtrl2InfoRam_GetVTable(void) {
    struct Obj_34bd10 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[9] = 0;
    obj.vt = &g_beParticleCtrl2InfoRam_vtable[0];
    obj.w[10] = 0;
    obj.w[11] = 0;
    obj.w[12] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beParticleCtrl2InfoRam_vtable[0];
    igSmartPointer_beParticleCtrl2InfoWork_Destruct((ObjectRefWord *)(&obj.w[12]), -1);
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

ObjectRefWord *igSmartPointer_beParticleCtrl2InfoWork_Destruct(ObjectRefWord *self,int delete_storage) {
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

void beParticleCtrl2InfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2InfoRam_Register);
}

static igMetaObjectCallback g_beParticleCtrl2InfoRam_callbackList[] = { igTransform_EnsureRegistered, ParticleTimer_EnsureRegistered, beParticleCtrl2InfoWork_EnsureRegistered, 0 };

void *beParticleCtrl2InfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beParticleCtrl2InfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beParticleCtrl2InfoRam_GetMetaObjectFunction,
        "beParticleCtrl2InfoRam",
        0x38, /* instance size */
        beParticleCtrl2InfoRam_GetVTable,
        beParticleCtrl2InfoRam_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoRam_callbackList /* callback list */
    );
}

void beParticleCtrl2InfoRam_GetMetaObjectFunction(void)
{
    beParticleCtrl2InfoRam_GetMetaObject();
}

static FieldFactory g_beParticleCtrl2InfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beParticleCtrl2InfoRam_fieldTable[] = {
    "_transform",
    "_particleTimer",
    "_work",
};
static igMetaField **g_beParticleCtrl2InfoRam_fieldHandles[] = {
    &g_beParticleCtrl2InfoRam_transformMetaField,
    &g_beParticleCtrl2InfoRam_particleTimerMetaField,
    &g_beParticleCtrl2InfoRam_workMetaField,
};
static int g_beParticleCtrl2InfoRam_fieldOffsets[] = {
    44,
    48,
    52,
};

void beParticleCtrl2InfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beParticleCtrl2InfoRam_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beParticleCtrl2InfoRam_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igTransform_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)ParticleTimer_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beParticleCtrl2InfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beParticleCtrl2InfoRam_fieldTable, g_beParticleCtrl2InfoRam_fieldHandles, g_beParticleCtrl2InfoRam_fieldOffsets, temp_s2);
}

