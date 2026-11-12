void FUN_00132810(int arg0) {
    FUN_00132a00();
    igMetaObject_CreateInstance(*(int *)0x55ED88, arg0);
}

int FUN_00132850(void) {
    if (DAT_0055ed88[0] == 0) {
        DAT_0055ed88[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055ed88[0];
}

igMetaObject *igTextureBindAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureBindAttr_metaObject[0] != 0) {
        ready = (g_igTextureBindAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00132a00();
done:
    return g_igTextureBindAttr_metaObject[0];
}

int igTextureBindAttr_GetVTable(void) {
    struct Obj_1328f0 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522bd0[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00522bd0[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

ObjectRefWord *FUN_00132980(ObjectRefWord *self,int delete_storage) {
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

void FUN_00132a00(void)
{
    igMetaObject_RunStaticInit(igTextureBindAttr_Register);
}

void igTextureBindAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureBindAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureBindAttr_GetMetaObject,
        igTextureBindAttr_className,
        0x14, /* instance size */
        igTextureBindAttr_GetVTable,
        &igTextureBindAttr_InitFields,
        thunk_FUN_00140f40, /* extra callback item */
        g_igTextureBindAttr_callbackList /* callback list */
    );
}

void thunk_igTextureBindAttr_GetMetaObject(void) {
    igTextureBindAttr_GetMetaObject();
}

void igTextureBindAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    temp_s0 = (void *)DAT_0055ed88[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485cb0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00132ba0();
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s1 + 48) = (int)FUN_00140e40;
    igMetaObject_NameFields(temp_s0, &DAT_00485cb8[0], &DAT_00485cc0[0], &DAT_00485cc8[0], temp_s2);
}

void thunk_FUN_00140f40(void) {
    FUN_00140f40();
}

