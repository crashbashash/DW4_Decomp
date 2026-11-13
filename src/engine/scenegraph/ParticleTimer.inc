void FUN_001c51d0(void) {
    FieldHolder field;
    char *name;
    ObjectRefFieldView *held;
    if (((ObjectRefFieldView * *)DAT_00562768)[0] == 0) {
        field.p = igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587038[0]));
        ((ObjectRefFieldView * *)DAT_00562768)[0] = field.p;
        name = internText(DAT_004e4630);
        igMetaField_SetFieldName(field.p, &name);
        if (name != 0) {
            int *header = (int *)name - 2;
            int count = ((int *)name)[-1] - 1;
            ((int *)name)[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        field.p->_flag52 = 1;
        field.p->_flag38 = 0;
        field.p->_metaObject = igGeometrySetAttr_GetMetaObject();
        FUN_002fe570(g_igGeometry_metaObject[0], field.p);
        held = field.p;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)held);
            }
        }
    }
}

void Gap__Bec__ParticleTimer__vfunc_15(ParticleTimer *arg0) {
    void *temp_a0;
    int temp_a1;

    FUN_001c5b80((SgLinkNode *)arg0);
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

void Gap__Bec__ParticleTimer__vfunc_27(ParticleTimer *arg0, int arg1) {
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

void Gap__Bec__ParticleTimer__vfunc_26(ParticleTimer *arg0, int arg1, int arg2) {
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

void Gap__Bec__ParticleTimer__vfunc_25(ParticleTimer *arg0, int arg1) {
    igObjectList *temp_s3 = (igObjectList *)arg0->_attributes;
    unsigned int temp_s2 = temp_s3->_count;
    unsigned int var_s1;
    for (var_s1 = 0; var_s1 < temp_s2; var_s1++) {
        AttributeObjView *temp_s0 = (AttributeObjView *)((int *)temp_s3->_data)[var_s1];
        if (temp_s0 != 0 && igObject_IsKindOf(temp_s0, g_igGeometryAttr_metaObject[0]) != 0) {
            if (!((((unsigned int)(*temp_s0->f12->v100() & 0xF0)) >> 4) & 0xFF)) {
                ((AttributeVtable *)temp_s0)->v132(arg1);
            }
        }
    }
}

void Gap__Bec__ParticleTimer__vfunc_29(ParticleAttributeObj *arg0) {
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

int FUN_001c5730(int *p, int)
{
    return ObjectList_AppendRetained(*(int *)((char *)p + 8));
}

void FUN_001c5740(U_1c5740 *arg0, T_1c5740 *arg1) {
    ((DW4VC_72_0 *)(arg1->f))->vX();
    FUN_00300c00(arg0->f, arg1->f, 0);
}

void FUN_001c5790(Obj_1c5790 *arg0, int arg1) {
    List_1c5790 *l = arg0->list;
    int n = l->n;
    int i;
    for (i = 0; i < n; i++) {
        T *old = l->arr[i];
        if (old) {
            --old->references;
            if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
                igObject_Destroy((void *)old);
        }
    }
    int n2 = l->n;
    int j;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->n = 0;
    ObjectList_AppendRetainedList(arg0->list, arg1);
}

void FUN_001c5870(void *arg0, int arg1) {
    int idx, tbl;
    tbl = *(int *)(*(int *)((char *)((void *)igGraphPath_GetTail(arg0)) + 28) + 16);
    idx = arg1 * 4;
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 8), *(int *)(tbl + idx));
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
                igObject_Destroy((void *)o);
            }
        }
        List_RemoveWordAt(l, s2);
        l->f10[l->f8] = 0;
        return ret;
    }
    return 0;
}

int igGraphPath_GetTail(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 8));
    return *(int *)(*(int *)((char *)(temp_v0) + 16) + ((*(int *)((char *)(temp_v0) + 8) - 1) * 4));
}

int FUN_001c59b0(void *self) {
    return FUN_001c59e0((void *)self) == 1;
}

int FUN_001c59e0(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 8);
}

void FUN_001c59f0(OO *arg0, int arg1, int arg2, int arg3) {
    int i;
    EE *e;

    igMatrix44f_SetIdentity(arg2);
    for (i = 0; i < arg1; i++) {
        e = (EE *)arg0->list->items[i];
        if (FUN_002fe290(((DW4VC_88_0 *)(e))->vX(), g_igTransform_metaObject[0]) != 0) {
            if (e->f96 == 0) {
                ((DW4VC_156_1 *)(e))->vX(arg3);
                FUN_001906d0(arg2, (char *)e + 0x20);
            }
        } else if (FUN_002fe290(((DW4VC_88_0 *)(e))->vX(), DAT_005612d8[0]) != 0) {
            arg3 = ((DW4VC_164_1 *)(e))->vX(arg3);
        }
    }
}

