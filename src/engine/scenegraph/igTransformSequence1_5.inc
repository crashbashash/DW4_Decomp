igMetaObject *g_igTransformSequence1_5_metaObject;
igMetaField *g_igTransformSequence1_5_timeListLongMetaField;
igMetaField *g_igTransformSequence1_5_timeListMetaField;
igMetaField *g_igTransformSequence1_5_interpolationDataTranslationMetaField;
igMetaField *g_igTransformSequence1_5_interpolationDataRotationMetaField;
igMetaField *g_igTransformSequence1_5_interpolationDataScaleMetaField;
igMetaField *g_igTransformSequence1_5_drivenChannelsMetaField;
igMetaField *g_igTransformSequence1_5_interpolationMethodMetaField;
igMetaField *g_igTransformSequence1_5_keyframeTimeOffsetMetaField;
igMetaField *g_igTransformSequence1_5_animationDurationMetaField;
igMetaField *g_igTransformSequence1_5_compressedDataObjectMetaField;

igMetaObject *igTransformSequence1_5_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSequence1_5_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformSequence1_5_EnsureRegistered();
    return g_igTransformSequence1_5_metaObject;
}

int igTransformSequence1_5_GetVTable(void) {
    struct Obj_194f40 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.vt = &g_igTransformSequence1_5_vtable[0];
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[23] = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igTransformSequence1_5_vtable[0];
    igSmartPointer_igCompressedTransformSequence1_5Data_Destruct((ObjectRefWord *)&obj.w[23], -1);
    igSmartPointer_igVec3fList_Destruct((igSmartPointer<igObject> *)&obj.w[16], -1);
    igSmartPointer_igVec3fList_Destruct((igSmartPointer<igObject> *)&obj.w[15], -1);
    igSmartPointer_igVec3fList_Destruct((igSmartPointer<igObject> *)&obj.w[14], -1);
    igSmartPointer_igLongList_Destruct((igSmartPointer<igObject> *)&obj.w[13], -1);
    FUN_00195030((Obj_195030 *)((int *)&obj), 0);
    return t;
}

Obj_195030 *FUN_00195030(Obj_195030 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_005283e0[0];
        arg0->rel(&arg0->m20);
        arg0->rel(&arg0->m16);
        arg0->rel(&arg0->m12);
        arg0->rel(&arg0->m8);
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igLongList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

ObjectRefWord *igSmartPointer_igCompressedTransformSequence1_5Data_Destruct(ObjectRefWord *self,int delete_storage) {
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

void igTransformSequence1_5_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformSequence1_5_Register);
}

static igMetaObjectCallback g_igTransformSequence1_5_callbackList[] = { igLongList_EnsureRegistered, igVec3fList_EnsureRegistered, igCompressedTransformSequence1_5Data_EnsureRegistered, 0 };

CallbackArray *igTransformSequence1_5_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransformSequence1_5_metaObject,
        igTransformSequence_Register,
        igTransformSequence_GetPublishedMetaObject,
        igTransformSequence1_5_GetMetaObjectFunction,
        "igTransformSequence1_5",
        sizeof(igTransformSequence1_5),                      /* Instance size. */
        igTransformSequence1_5_GetVTable,
        &igTransformSequence1_5_InitFields,
        thunk_FUN_001ddfd0, /* extra callback item */
        g_igTransformSequence1_5_callbackList /* callback list */
    );
}

void igTransformSequence1_5_GetMetaObjectFunction(void) {
    igTransformSequence1_5_GetMetaObject();
}

