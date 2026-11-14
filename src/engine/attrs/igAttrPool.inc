int FUN_0013a640(int arg0) {
    FUN_0013a900();
    return igMetaObject_CreateInstance(*(int *)0x55F428, arg0);
}

igMetaObject *igAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a900();
    return g_igAttrPool_metaObject[0];
}

int igAttrPool_GetVTable(void) {
    union U_13a6d0 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_005242a0[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_005242a0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s0;
}

void **FUN_0013a800(void **arg0, short arg1) {
    S_temp_a0_13a800 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_13a800 *)((void *)(*arg0));
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

ObjectRefWord *FUN_0013a880(ObjectRefWord *self,int delete_storage) {
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

void FUN_0013a900(void)
{
    igMetaObject_RunStaticInit(igAttrPool_Register);
}

void igAttrPool_Register(void) {
    AttrsLibrary_MarkRegistered();  /* Set-once latch: writes a gp-relative byte flag only if it is clear. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrPool_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrPool_GetMetaObject,
        igAttrPool_className,
        0x14, /* instance size */
        igAttrPool_GetVTable,
        &igAttrPool_InitFields,
        FUN_0013aa90,                      /* static-initializer callback item (appended on fresh configuration) */
        g_igAttrPool_callbackList     /* 0-terminated dependency-callback list */
    );
}

void thunk_igAttrPool_GetMetaObject(void) {
    igAttrPool_GetMetaObject();
}

void igAttrPool_InitFields(void) {
    void *temp_s1;
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_igAttrPool_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAttrPool_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igMetaObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igMetaObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0013abd0();
    ((igObjectRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igAttrPool_fieldTable[0], &DAT_00486c18[0], &DAT_00486c28[0], temp_s2);
    igMetaObject_AddExitCallback((int)thunk_FUN_0013c110);
}

void FUN_0013aa90(void) {
    FUN_0013c170();
}

void thunk_FUN_0013c110(void) {
    FUN_0013c110();
}

