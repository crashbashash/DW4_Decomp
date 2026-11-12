igMetaObject *FUN_001a8520(void)
{
    igMetaObject *g = ((igMetaObject * *)g_igAnimationCombiner_metaObject)[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8800();
    return ((igMetaObject * *)g_igAnimationCombiner_metaObject)[0];
}

int igAnimationCombiner_GetVTable(void) {
    struct Obj_1a8570 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.vt = &DAT_00529630[0];
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00529630[0];
    FUN_001a8780((struct R * *)&obj.w14, -1);
    ObjectRef_Destruct_00150eb0(&obj.w13, -1);
    FUN_001a8700((ObjectRefWord *)&obj.w12, -1);
    FUN_001a8620((struct S_1a8620 *)&obj, 0);
    return t;
}

void *FUN_001a8620(struct S_1a8620 *arg0, short arg1) {
    igObject *p;
    void *hp;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00529c40[0];
        if (&arg0->fc) {
            p = arg0->fc;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &g_igNamedObject_vtable[0];
            if (&arg0->f8) {
                hp = arg0->f8;
                if (hp != 0) {
                    h = (int *)((char *)(hp) - 8);
                    rc = *(int *)((char *)(hp) - 4) - 1;
                    *(int *)((char *)(hp) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001a8700(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

struct R **FUN_001a8780(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_001a8800(void)
{
    igMetaObject_RunStaticInit(igAnimationCombiner_Register);
}

void igAnimationCombiner_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationCombiner_metaObject),
        igAnimationSystem_Register,
        igAnimationSystem_GetPublishedMetaObject,
        thunk_FUN_001a8520,
        igAnimationCombiner_className,
        0x60, /* instance size */
        igAnimationCombiner_GetVTable,
        &igAnimationCombiner_InitFields,
        thunk_FUN_001abca0,                                /* static-initializer callback item (appended on fresh configuration) */
        g_igAnimationCombiner_callbackList        /* 0-terminated dependency-callback list */
    );
}

void thunk_FUN_001a8520(void) {
    FUN_001a8520();
}

igMetaObject *FUN_001a88a0(void) {
    return g_igAnimationSystem_metaObject[0];
}

void igAnimationCombiner_InitFields(void) {
    int temp_s1;
    struct Fld_1a88b0 *temp_s2;
    struct Fld_1a88b0 *temp_s2_2;
    struct Fld_1a88b0 *temp_s2_3;
    struct Fld_1a88b0 *temp_s2_4;
    struct Fld_1a88b0 *temp_s2_5;
    struct Fld_1a88b0 *temp_s2_6;
    struct Fld_1a88b0 *temp_s2_7;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationCombiner_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d360[0], 0xE);
    temp_s2 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1));
    temp_s2->f56 = (int)FUN_001a7e20();
    temp_s2->f52 = 1;
    temp_s2_2 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    temp_s2_2->f56 = igIntList_GetOrCreateMetaObject();
    temp_s2_2->f52 = 1;
    temp_s2_3 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    temp_s2_3->f56 = (int)FUN_001a6920();
    temp_s2_3->f52 = 1;
    temp_s2_4 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    temp_s2_4->f60 = FUN_00187520();
    temp_s2_4->f53 = 1;
    temp_s2_4->f64 = 1;
    temp_s2_4->f65 = 1;
    temp_s2_5 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    temp_s2_5->f60 = FUN_001888e0();
    temp_s2_5->f53 = 1;
    temp_s2_5->f64 = 1;
    temp_s2_5->f65 = 1;
    ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7))->f38 = 0;
    temp_s2_6 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    temp_s2_6->f60 = FUN_001888e0();
    temp_s2_6->f53 = 1;
    temp_s2_6->f64 = 1;
    temp_s2_6->f65 = 1;
    temp_s2_7 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    temp_s2_7->f60 = FUN_001888e0();
    temp_s2_7->f53 = 1;
    temp_s2_7->f64 = 1;
    temp_s2_7->f65 = 1;
    FUN_002ebc00(((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA)), -1);
    FUN_002ebc00(((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC)), 0x05F5E100);
    FUN_002ebc00(((struct Fld_1a88b0 *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD)), 0xFED260);
    igMetaObject_NameFields(temp_s0, &DAT_0048d3a0[0], &DAT_0048d3e0[0], &DAT_0048d420[0], temp_s1);
    FUN_002fe480(&thunk_FUN_001abdf0);
}

void thunk_FUN_001abca0(void) {
    FUN_001abca0();
}

void thunk_FUN_001abdf0(void) {
    FUN_001abdf0();
}

