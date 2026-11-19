void FUN_001c51d0(void) {
    FieldHolder field;
    char *name;
    ObjectRefFieldView *held;
    if (((ObjectRefFieldView * *)DAT_00562768)[0] == 0) {
        field.p = (ObjectRefFieldView *)igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
        ((ObjectRefFieldView * *)DAT_00562768)[0] = field.p;
        name = internText("_geoSet");
        igMetaField_SetFieldName((igMetaField *)field.p, (void **)&name);
        if (name != 0) {
            int *header = (int *)name - 2;
            int count = ((int *)name)[-1] - 1;
            ((int *)name)[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
            }
        }
        field.p->_flag52 = 1;
        field.p->_flag38 = 0;
        field.p->_metaObject = (int)igGeometrySetAttr_GetMetaObject();
        igMetaObject_AddFieldAndFinalize(g_igGeometry_metaObject, field.p);
        held = field.p;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)held);
            }
        }
    }
}

void igGeometry_UserPostLoad(ParticleTimer *arg0) {
    void *temp_a0;
    int temp_a1;

    igGroup_UserPostLoad((SgLinkNode *)arg0);
    temp_a0 = (void *)(*(int *)((char *)arg0 + *(int *)((char *)(DAT_00562768[0]) + 8)));
    temp_a1 = arg0->_flags;
    if (temp_a1 & 8) {
        *(int *)((char *)(temp_a0) + 24) = 2;
        return;
    }
    if (temp_a1 & 4) {
        *(int *)((char *)(temp_a0) + 24) = 1;
        return;
    }
    *(int *)((char *)(temp_a0) + 24) = 0;
}

void igGeometry_SetFlags(ParticleTimer *arg0, int arg1) {
    void *temp_a0;

    arg0->_flags = arg1;
    temp_a0 = (void *)(*(int *)((char *)arg0 + *(int *)((char *)(DAT_00562768[0]) + 8)));
    if (arg1 & 8) {
        *(int *)((char *)(temp_a0) + 24) = 2;
        return;
    }
    if (arg1 & 4) {
        *(int *)((char *)(temp_a0) + 24) = 1;
        return;
    }
    *(int *)((char *)(temp_a0) + 24) = 0;
}

void igGeometry_EnableFlags(ParticleTimer *arg0, int arg1, int arg2) {
    int temp_a2;
    int *temp_a0;

    if (arg2 != 0) {
        arg0->_flags = arg0->_flags | arg1;
    } else {
        arg0->_flags = arg0->_flags & ~arg1;
    }
    temp_a0 = *(int **)((char *)arg0 + *(int *)((char *)(DAT_00562768[0]) + 8));
    temp_a2 = arg0->_flags;
    if (temp_a2 & 8) {
        temp_a0[6] = 2;
        return;
    }
    if (temp_a2 & 4) {
        temp_a0[6] = 1;
        return;
    }
    temp_a0[6] = 0;
}

void igGeometry_Transform(ParticleTimer *arg0, int arg1) {
    igObjectList *temp_s3 = (igObjectList *)arg0->_attributes;
    unsigned int temp_s2 = temp_s3->_count;
    unsigned int var_s1;
    for (var_s1 = 0; var_s1 < temp_s2; var_s1++) {
        AttributeObjView *temp_s0 = (AttributeObjView *)((int *)temp_s3->_data)[var_s1];
        if (temp_s0 != 0 && igObject_IsKindOf((igObject *)temp_s0, g_igGeometryAttr_metaObject) != 0) {
            if (!((((unsigned int)(*temp_s0->f12->v100() & 0xF0)) >> 4) & 0xFF)) {
                ((AttributeVtable *)temp_s0)->v132(arg1);
            }
        }
    }
}


extern "C" unsigned int Gap__Bec__ParticleTimer__getTriangleCount(ParticleTimer *self);

/* Triangle count of the timer's geometry attributes: triangle lists (_primType 3) add one per primitive, triangle
 * strips (4) add the vertex count less two per strip. */
unsigned int Gap__Bec__ParticleTimer__getTriangleCount(ParticleTimer *self)
{
    /* matching construct: declaration order sets the register colours (attrs last) */
    unsigned int triangles;
    unsigned int count;
    unsigned int i;
    igGeometryAttr *geom;
    igObjectList *attrs;

    attrs = (igObjectList *)self->_attributes;
    triangles = 0;
    count = attrs->_count;
    i = 0;
    /* matching construct: retail enters the loop through a zero-trip guard placed after the return (as igGroup_UserPostLoad) */
    goto guard;
next:
    geom = ((igGeometryAttr **)attrs->_data)[i];
    if (geom->_primType == 3) {
        triangles += geom->_numPrims;
    } else if (geom->_primType == 4) {
        triangles += ((igVertexArray *)geom->_vertexArray)->_numVerts - geom->_numPrims * 2;
    }
    i++;
test:
    if (i < count) goto next;
done:
    return triangles;
guard:
    if (i < count) goto test;
    goto done;
}

void igGeometry_Reset(ParticleAttributeObj *arg0) {
    /* matching construct: a typed view of the receiver declared first; a cast at each use changes how the compiler hoists the field address */
    ParticleTimer *self = (ParticleTimer *)arg0;
    unsigned temp_s1;
    unsigned var_s0;
    ParticleAttributeObj *temp_a0_2;

    temp_s1 = ((igObjectList *)self->_attributes)->_count;
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        ((ParticleAttributeObj **)((igObjectList *)self->_attributes)->_data)[var_s0]->vX();
    }
    temp_a0_2 = *(ParticleAttributeObj **)((char *)arg0 + ((FieldOffsetHolder * *)DAT_00562768)[0]->f8);
    if (temp_a0_2 != 0) {
        temp_a0_2->vX();
    }
}

void FUN_001c5660(Z_1c5660 *arg0, int arg1, int arg2) {
    unsigned int cnt;
    unsigned int i;
    Item_1c5660 *it;
    V_1c5660 *o;
    int cur;
    int a1;
    i = 0;
    cnt = arg0->f32->cnt;
    for (; i < cnt; i++) {
        it = arg0->f32->items[i];
        if (it != 0) {
            o = it->f12;
            if (o != 0) {
                cur = o->f20;
                if (arg2 != 0) {
                    a1 = cur | arg1;
                } else {
                    a1 = cur & ~(cur & ~arg1);
                }
                o->vX(a1);
            }
        }
    }
}

int FUN_001c5730(int *p, igObject *object)
{
    return ObjectList_AppendRetained(*(igObjectList **)((char *)p + 8), object);
}

void FUN_001c5740(U_1c5740 *arg0, T_1c5740 *arg1) {
    ((DW4VC_72_0 *)(arg1->f))->vX();
    igObject_Copy((igObject *)arg0->f, (igObject *)arg1->f, 0);
}

void igGraphPath_SetNodes(igGraphPath *path, igNodeList *nodes) {
    List_1c5790 *l = (List_1c5790 *)path->_path;
    int n = l->n;
    int i;
    for (i = 0; i < n; i++) {
        T *old = l->arr[i];
        if (old) {
            --old->references;
            if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)old);
        }
    }
    int n2 = l->n;
    int j;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->n = 0;
    ObjectList_AppendRetainedList((igTDataList<igObject *> *)path->_path, (igTDataList<igObject *> *)nodes);
}

void FUN_001c5870(void *arg0, int arg1) {
    int idx, tbl;
    tbl = *(int *)(*(int *)((char *)((void *)igGraphPath_GetTail((igGraphPath *)arg0)) + 28) + 16);
    idx = arg1 * 4;
    ObjectList_AppendRetained((igObjectList *)(*(int *)((char *)(arg0) + 8)), (igObject *)(*(int *)(tbl + idx)));
}

int FUN_001c58c0(T_1c58c0 *arg0) {
    int s2;
    L_1c58c0 *l;
    R_1c58c0 *o;
    int ret;
    if (FUN_001c59b0((void *)arg0) == 0) {
        l = arg0->f8;
        ret = *(int *)((char *)l->f10 + (f8_of(l) - 1) * 4);
        s2 = l->f8 - 1;
        o = (R_1c58c0 *)l->f10[s2];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long)((long long)o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        List_RemoveWordAt((igDataList *)l, s2);
        l->f10[l->f8] = 0;
        return ret;
    }
    return 0;
}

igNode *igGraphPath_GetTail(igGraphPath *path) {
    igNodeList *nodes = (igNodeList *)path->_path;
    return *(igNode **)(nodes->_data + (nodes->_count - 1) * 4);
}

int FUN_001c59b0(void *self) {
    return igGraphPath_GetCount((igGraphPath *)self) == 1;
}

int igGraphPath_GetCount(igGraphPath *path) {
    return ((igNodeList *)path->_path)->_count;
}

void FUN_001c59f0(OO *arg0, int arg1, int arg2, long long arg3) {
    int i;
    EE *e;

    igMatrix44f_SetIdentity((float *)arg2);
    for (i = 0; i < arg1; i++) {
        e = (EE *)arg0->list->items[i];
        if (igMetaObject_IsOfType((igMetaObject *)(((DW4VC_88_0 *)(e))->vX()), g_igTransform_metaObject) != 0) {
            if (e->f96 == 0) {
                ((DW4VC_156_2 *)(e))->vX(arg3);
                igMatrix44f_PreMultiply((float *)arg2, (const float *)((char *)e + 0x20));
            }
        } else if (igMetaObject_IsOfType((igMetaObject *)(((DW4VC_88_0 *)(e))->vX()), (igMetaObject *)DAT_005612d8[0]) != 0) {
            arg3 = ((DW4VC_164_1 *)(e))->vX(arg3);
        }
    }
}

