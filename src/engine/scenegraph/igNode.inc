igMetaObject *g_igNode_metaObject;
igMetaField *g_igNode_boundMetaField;
igMetaField *g_igNode_parentListMetaField;
igMetaField *g_igNode_flagsMetaField;
igMetaField *g_igNode_handleMetaField;

igMetaObject *igNode_GetOrCreateMetaObject(void) {
    if (g_igNode_metaObject == 0) {
        g_igNode_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNode_metaObject;
}

igMetaObject *igNode_GetMetaObject(void)
{
    igMetaObject *g = g_igNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNode_EnsureRegistered();
    return g_igNode_metaObject;
}

int igNode_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)u.b);
    q2 = &u.b[8];
    *(int *)q2 = 0;
    u.vt = (int)&g_igNode_vtable[0];
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igNode_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q2 != 0) {
        temp_v1 = *(int **)q2;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igNode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNode_Register);
}

static igMetaObjectCallback g_igNode_callbackList[] = { igVolume_EnsureRegistered, igNonRefCountedNodeList_EnsureRegistered, 0 };

CallbackArray *igNode_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNode_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igNode_GetMetaObjectFunction,
        "igNode",
        0x1C, /* instance size */
        igNode_GetVTable,
        &igNode_InitFields,
        0, /* extra callback item */
        g_igNode_callbackList /* callback list */
    );
}

void igNode_GetMetaObjectFunction(void) {
    igNode_GetMetaObject();
}

static FieldFactory g_igNode_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igNode_fieldTable[] = {
    "_bound",
    "_parentList",
    "_flags",
    "_handle",
};
static igMetaField **g_igNode_fieldHandles[] = {
    &g_igNode_boundMetaField,
    &g_igNode_parentListMetaField,
    &g_igNode_flagsMetaField,
    &g_igNode_handleMetaField,
};
static int g_igNode_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igNode_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;
    void *temp_s1;

    temp_s1 = (void *)g_igNode_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igNode_ctorTable, 4);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igVolume_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igNonRefCountedNodeList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_resetMethod = 3;
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_2)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_2)->_deepCopyMethod = 4;
    ((igObjectRefMetaField *)temp_s2_2)->_shallowCopyMethod = 4;
    ((igObjectRefMetaField *)temp_s2_2)->_constructCopyMethod = 4;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((Gap::Core::igIntMetaField *)temp_v0)->setDefault(-1);
    ((igIntMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igNode_fieldTable, g_igNode_fieldHandles, g_igNode_fieldOffsets, temp_s0);
}

void **igSmartPointer_igRenderListAttr_Destruct(void **arg0, long long arg1) {
    struct Rc *a;
    if (arg0 != 0) {
        a = (struct Rc *)*arg0;
        if (a != 0) { a->rc = a->rc - 1; if ((a->rc & 0x7FFFFF) == 0) { igObject_Destroy((igObject *)a); } }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

igGeometry *igGeometry_Destroy(igGeometry *self, short deleteFlag) {
    void *p;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igGeometry_vtable[0];
        if (&self->_renderList) {
            p = (void *)self->_renderList;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (self != 0) {
            self->_vtable = (int)&g_igAttrSet_vtable[0];
            igSmartPointer_igAttrList_Destruct((igSmartPointer<igObject> *)&self->_attributes, -1);
            igGroup_Destroy((igGroup *)self, 0);
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igMetaObject *g_igGeometry_metaObject;
igMetaField *g_igGeometry_triggerMetaField;
igMetaField *g_igGeometry_renderListMetaField;

igMetaObject *igGeometry_GetPublishedMetaObject(void) {
    return g_igGeometry_metaObject;
}

int *igSmartPointer_igFloatList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

igSmartPointer<igObject> *igSmartPointer_igIntListList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igMetaObject *g_igModelViewMatrixBoneSelectListSg_metaObject;

igMetaObject *igModelViewMatrixBoneSelectListSg_GetOrCreateMetaObject(void) {
    if (g_igModelViewMatrixBoneSelectListSg_metaObject == 0) {
        g_igModelViewMatrixBoneSelectListSg_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixBoneSelectListSg_metaObject;
}

