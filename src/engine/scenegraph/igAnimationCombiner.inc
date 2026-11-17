igMetaObject *g_igAnimationCombiner_metaObject;
igMetaField *g_igAnimationCombiner_boneInfoListListMetaField;
igMetaField *g_igAnimationCombiner_boneInfoListBaseMetaField;
igMetaField *g_igAnimationCombiner_animationStateListMetaField;
igMetaField *g_igAnimationCombiner_resultQuaternionArrayMetaField;
igMetaField *g_igAnimationCombiner_animationCacheMatrixArrayMetaField;
igMetaField *g_igAnimationCombiner_cacheTimeMetaField;
igMetaField *g_igAnimationCombiner_cacheValidMetaField;
igMetaField *g_igAnimationCombiner_hierarchyUpdatedMetaField;
igMetaField *g_igAnimationCombiner_boneMatrixArrayMetaField;
igMetaField *g_igAnimationCombiner_blendMatrixArrayMetaField;
igMetaField *g_igAnimationCombiner_animationStateTimeMetaField;
igMetaField *g_igAnimationCombiner_lastCleanStatesTimeMetaField;
igMetaField *g_igAnimationCombiner_cleanStatesTimeThresholdMetaField;
igMetaField *g_igAnimationCombiner_cleanStatesTransitionMarginMetaField;

igMetaObject *FUN_001a8520(void)
{
    igMetaObject *g = g_igAnimationCombiner_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationCombiner_EnsureRegistered();
    return g_igAnimationCombiner_metaObject;
}

int igAnimationCombiner_GetVTable(void) {
    struct Obj_1a8570 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.vt = &g_igAnimationCombiner_vtable[0];
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igAnimationCombiner_vtable[0];
    FUN_001a8780((struct R * *)&obj.w14, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj.w13, -1);
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
                    igObject_Destroy((igObject *)p);
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
                        StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
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
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
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
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igAnimationCombiner_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationCombiner_Register);
}

static igMetaObjectCallback g_igAnimationCombiner_callbackList[] = { igAnimationCombinerBoneInfoListList_EnsureRegistered, igIntList_EnsureRegistered, igAnimationStateList_EnsureRegistered, 0 };

CallbackArray *igAnimationCombiner_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationCombiner_metaObject,
        igAnimationSystem_Register,
        igAnimationSystem_GetPublishedMetaObject,
        thunk_FUN_001a8520,
        "igAnimationCombiner",
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
    return g_igAnimationSystem_metaObject;
}

static FieldFactory g_igAnimationCombiner_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
};
static const char *g_igAnimationCombiner_fieldTable[] = {
    "_boneInfoListList",
    "_boneInfoListBase",
    "_animationStateList",
    "_resultQuaternionArray",
    "_animationCacheMatrixArray",
    "_cacheTime",
    "_cacheValid",
    "_hierarchyUpdated",
    "_boneMatrixArray",
    "_blendMatrixArray",
    "_animationStateTime",
    "_lastCleanStatesTime",
    "_cleanStatesTimeThreshold",
    "_cleanStatesTransitionMargin",
};
static igMetaField **g_igAnimationCombiner_fieldHandles[] = {
    &g_igAnimationCombiner_boneInfoListListMetaField,
    &g_igAnimationCombiner_boneInfoListBaseMetaField,
    &g_igAnimationCombiner_animationStateListMetaField,
    &g_igAnimationCombiner_resultQuaternionArrayMetaField,
    &g_igAnimationCombiner_animationCacheMatrixArrayMetaField,
    &g_igAnimationCombiner_cacheTimeMetaField,
    &g_igAnimationCombiner_cacheValidMetaField,
    &g_igAnimationCombiner_hierarchyUpdatedMetaField,
    &g_igAnimationCombiner_boneMatrixArrayMetaField,
    &g_igAnimationCombiner_blendMatrixArrayMetaField,
    &g_igAnimationCombiner_animationStateTimeMetaField,
    &g_igAnimationCombiner_lastCleanStatesTimeMetaField,
    &g_igAnimationCombiner_cleanStatesTimeThresholdMetaField,
    &g_igAnimationCombiner_cleanStatesTransitionMarginMetaField,
};
static int g_igAnimationCombiner_fieldOffsets[] = {
    48,
    52,
    56,
    60,
    64,
    72,
    80,
    81,
    84,
    88,
    16,
    24,
    32,
    40,
};

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

    temp_s0 = (void *)g_igAnimationCombiner_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationCombiner_ctorTable, 0xE);
    temp_s2 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1));
    temp_s2->f56 = (int)FUN_001a7e20();
    temp_s2->f52 = 1;
    temp_s2_2 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    temp_s2_2->f56 = igIntList_GetOrCreateMetaObject();
    temp_s2_2->f52 = 1;
    temp_s2_3 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2));
    temp_s2_3->f56 = (int)FUN_001a6920();
    temp_s2_3->f52 = 1;
    temp_s2_4 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3));
    temp_s2_4->f60 = FUN_00187520();
    temp_s2_4->f53 = 1;
    temp_s2_4->f64 = 1;
    temp_s2_4->f65 = 1;
    temp_s2_5 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4));
    temp_s2_5->f60 = FUN_001888e0();
    temp_s2_5->f53 = 1;
    temp_s2_5->f64 = 1;
    temp_s2_5->f65 = 1;
    ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7))->f38 = 0;
    temp_s2_6 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8));
    temp_s2_6->f60 = FUN_001888e0();
    temp_s2_6->f53 = 1;
    temp_s2_6->f64 = 1;
    temp_s2_6->f65 = 1;
    temp_s2_7 = ((struct Fld_1a88b0 *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    temp_s2_7->f60 = FUN_001888e0();
    temp_s2_7->f53 = 1;
    temp_s2_7->f64 = 1;
    temp_s2_7->f65 = 1;
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA), -1);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC), 0x05F5E100);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD), 0xFED260);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationCombiner_fieldTable, g_igAnimationCombiner_fieldHandles, g_igAnimationCombiner_fieldOffsets, temp_s1);
    igMetaObject_AddExitCallback((int)&thunk_FUN_001abdf0);
}

void thunk_FUN_001abca0(void) {
    FUN_001abca0();
}

void thunk_FUN_001abdf0(void) {
    FUN_001abdf0();
}

