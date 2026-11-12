igMetaObject *igCompressedAnimationSequenceQS_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igCompressedAnimationSequenceQS_metaObject[0] != 0) {
        ready = (g_igCompressedAnimationSequenceQS_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001a2940();
done:
    return g_igCompressedAnimationSequenceQS_metaObject[0];
}

int igCompressedAnimationSequenceQS_GetVTable(void) {
    union U_1a2810 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00529260[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00529260[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q2);
            }
        }
    }
    return temp_s0;
}

void FUN_001a2940(void)
{
    igMetaObject_RunStaticInit(igCompressedAnimationSequenceQS_Register);
}

void igCompressedAnimationSequenceQS_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCompressedAnimationSequenceQS_metaObject),
        igAnimationSequence_Register,
        igAnimationSequence_GetPublishedMetaObject,
        thunk_igCompressedAnimationSequenceQS_GetMetaObject,
        igCompressedAnimationSequenceQS_className,
        0x40, /* instance size */
        igCompressedAnimationSequenceQS_GetVTable,
        &igCompressedAnimationSequenceQS_InitFields,
        0, /* extra callback item */
        g_igCompressedAnimationSequenceQS_callbackList /* callback list */
    );
}

void thunk_igCompressedAnimationSequenceQS_GetMetaObject(void) {
    igCompressedAnimationSequenceQS_GetMetaObject();
}

void igCompressedAnimationSequenceQS_InitFields(void) {
    int temp_s0;
    int temp_s1;
    struct Fld_1a29e0 *temp_s2;
    struct Fld_1a29e0 *temp_s2_2;
    struct Fld_1a29e0 *temp_s2_3;
    struct Fld_1a29e0 *temp_s2_4;
    struct Fld_1a29e0 *temp_v0;
    struct Fld_1a29e0 *temp_v0_2;

    temp_s1 = DAT_00561c38[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048c4e0[0], 0xC);
    temp_s2 = ((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0));
    temp_s2->f56 = FUN_002ca030();
    temp_s2_2 = ((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    temp_s2_2->f56 = FUN_002ca030();
    temp_s2_3 = ((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    temp_s2_3->f56 = FUN_002ca030();
    FUN_0030ec10(((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7)), 0xFFFFFFFFFFFFFFFFULL);
    temp_v0 = ((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    FUN_002dc7a0(temp_v0, &DAT_0048c5a0[0]);
    temp_v0->f52 = (int)&FUN_002d1870;
    temp_v0_2 = ((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    FUN_002ea4b0(temp_v0_2, 1);
    temp_v0_2->f38 = 0;
    FUN_0030e750(((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA)), 0);
    temp_s2_4 = ((struct Fld_1a29e0 *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    temp_s2_4->f52 = 3;
    igMetaObject_NameFields(temp_s1, &DAT_0048c510[0], &DAT_0048c540[0], &DAT_0048c570[0], temp_s0);
}

void **FUN_001a2b40(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((void *)r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001a2bc0(ObjectRefWord *self,int delete_storage) {
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

int *FUN_001a2c40(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_001a2c50(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_001a2c60(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

