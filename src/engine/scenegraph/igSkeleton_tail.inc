void Gap__Sg__igSkeleton__vfunc_23(SkeletonView *o, SkeletonSlots *clock, int unused, SkeletonMatrix *local, SkeletonMatrix *global, SkeletonMatrix *out, SkeletonOverrideListView *overrides) {
    SkeletonMatrix *inv;
    int count;
    int n;
    int i;
    int j;
    float translation[3];
    SkeletonMatrix m;
    count = o->getBoneCount();
    inv = o->_invJointArray;
    if (overrides == 0 || (n = overrides->_count) == 0) {
        for (i = 1; i < count; i++) {
            SkeletonBoneInfoView *info = o->_boneInfoList->_data[i];
            SkeletonMatrix *g;
            int parent = info->_parentIdx;
            if (parent == 0) {
                g = &global[i];
                Matrix44_Copy(g, &local[i]);
            } else {
                g = &global[i];
                FUN_00190470(g, &local[i], &global[parent]);
            }
            if (info->_bmIdx != -1) {
                FUN_00190470(&out[info->_bmIdx], inv, g);
                inv++;
            }
        }
        return;
    }
    for (i = 1; i < count; i++) {
        int off;
        SkeletonBoneInfoView *info;
        SkeletonMatrix *g;
        info = o->_boneInfoList->_data[i];
        off = i << 6;
        Matrix44_Copy(&m, (SkeletonMatrix *)((char *)local + off));
        for (j = 0; j < n; j++) {
            SkeletonOverrideView *ov = overrides->_data[j];
            if (i == ov->_bone) {
                SkeletonMatrix *src;
                SkeletonSourceView *source = ov->_source;
                source->update(clock->getTime());
                src = &ov->_source->_matrix;
                if (ov->_mode == 2) { Matrix44_Copy(&m, src); }
                if (ov->_mode == 3) {
                    Matrix44_GetTranslation(&m, translation);
                    Matrix44_Copy(&m, src);
                    Matrix44_SetTranslation(&m, translation);
                } else if (ov->_mode == 0) {
                    FUN_001906d0(&m, src);
                } else if (ov->_mode == 1) {
                    FUN_001904f0(&m, &m, src);
                }
            }
        }
        if (info->_parentIdx != 0) {
            g = (SkeletonMatrix *)((char *)global + off);
            FUN_001904f0(g, &m, &global[info->_parentIdx]);
        } else {
            g = (SkeletonMatrix *)((char *)global + off);
            Matrix44_Copy(g, &m);
        }
        if (info->_bmIdx != -1) {
            FUN_001904f0(&out[info->_bmIdx], inv, g);
            inv++;
        }
    }
}

int Gap__Sg__igSkeleton__vfunc_24(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 8);
}

int Gap__Sg__igSkeleton__vfunc_27(S_1d9500 *arg0, int arg1) {
    int i;
    int *p;

    for (i = 0; i < arg0->l->cnt; i++) {
        p = arg0->l->arr[i]->f8;
        p = p != 0 ? p : &emptyString[0];
        if (strcasecmp(p, arg1) == 0) {
            return i;
        }
    }
    return -1;
}

int Gap__Sg__igSkeleton__vfunc_29(O_1d95a0 *arg0, int arg1, int *arg2) {
    int i;
    while ((i = *arg2) < ((VC_1d95a0 *)arg0)->vX()) {
        E_1d95a0 *e = arg0->b->arr[i];
        *arg2 += 1;
        if (e->f12 == arg1) {
            return *arg2 - 1;
        }
    }
    return -1;
}

int Gap__Sg__igSkeleton__vfunc_31(void **arg0, int arg1, int arg2) {
    int sp5C;
    int temp_v0;
    int var_s0;

    sp5C = 0;
    var_s0 = 0;
loop_1:
    temp_v0 = ((V116 *)arg0)->vX(arg1, &sp5C);
    if ((temp_v0 != -1) && (var_s0 == arg2)) {
        return temp_v0;
    }
    var_s0 += 1;
    if (temp_v0 == -1) {
        return -1;
    }
    goto loop_1;
}

int Gap__Sg__igSkeleton__vfunc_30(VC_1d96d0 *arg0, int arg1) {
    int sp4C;
    int temp_v0;
    int var_s0;

    sp4C = 0;
    var_s0 = 0;
    do {
        temp_v0 = arg0->vX(arg1, &sp4C);
        if (temp_v0 != -1) {
            var_s0 += 1;
        }
    } while (temp_v0 != -1);
    return var_s0;
}

int FUN_001d9740(void *arg0, int arg1) {
    int temp_v1;
    int var_v0;

    temp_v1 = *(int *)((char *)arg0 + 12);
    var_v0 = 0;
    if (temp_v1 != 0) {
        var_v0 = FUN_001e04c0((S_1e04c0 *)arg1, (V_1e04c0 *)temp_v1);
    }
    return var_v0;
}

void **FUN_001d9770(void **arg0, short arg1) {
    S_temp_a0_1d9770 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1d9770 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001d97f0(ObjectRefWord *self,int delete_storage) {
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

void **FUN_001d9870(void **arg0, short arg1) {
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

