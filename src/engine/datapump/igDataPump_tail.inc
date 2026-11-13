void FUN_001e6230(igDataPump *arg0, Src **arg1, int arg2) {
    igObject *s0;
    igObject *old;
    igMetaField *fld;
    int name;
    int v;
    int newv;
    int oldv;
    s0 = (igObject *)*arg1;
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    old = (igObject *)arg0->_destObj;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->_destObj = (int)s0;
    fld = (igMetaField *)igMetaObject_FindFieldByName((*arg1)->vX(), arg2);
    if (fld != 0) {
        fld->_refCount = fld->_refCount + 1;
    }
    old = (igObject *)arg0->_destMeta;
    if (old != 0) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->_destMeta = (int)fld;
    name = ((igMetaObject *)((igMetaField *)arg0->_destMeta)->_parentMetaObject)->_name;
    if (g_stringPool[0] == 0) {
        v = StringPool_Allocate(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    newv = StringPool_Intern(g_stringPool[0], name);
    oldv = arg0->_destMetaClassName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_destMetaClassName = newv;
    name = ((igMetaField *)arg0->_destMeta)->_fieldName;
    if (g_stringPool[0] == 0) {
        v = StringPool_Allocate(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    newv = StringPool_Intern(g_stringPool[0], name);
    oldv = arg0->_destMetaFieldName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_destMetaFieldName = newv;
}

void FUN_001e6410(S0 *arg0, void **arg1) {
    S_temp_a0 *temp_a0;
    S_temp_s0 *temp_s0;
    temp_s0 = (S_temp_s0 *)(*arg1);
    if (temp_s0 != 0) {
        temp_s0->f4 = (int)((int) (temp_s0->f4 + 1));
    }
    temp_a0 = (S_temp_a0 *)(arg0->f18);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f18 = (int)(temp_s0);
}

int FUN_001e6490(ValueBinding *binding, int selection) {
    igSmartPointer<Value> value(binding->source->value(), kRetainReference);
    int sinkType = binding->sink->type();
    if (((FUN_002fe290(value->type(), sinkType) != 0) ^ 1) != 0) {
        return 0;
    }
    binding->source->select(selection);
    binding->sink->write(binding->key, (int)binding->source + value->offset);
    if (DAT_00562c60[0] == 0) {
        DAT_00562c60[0] = igMetaObject_FindFieldByName(g_igMetaField_metaObject[0], &text_invarianceFunction_2[0]);
    }
    Notify notify = *(Notify *)((char *)binding->sink + ((FieldDesc *)DAT_00562c60[0])->offset);
    if (notify != 0) {
        notify(binding->key);
    }
    return 1;
}

void Gap__igDataPump__vfunc_17(igDataPump *pump) {
    igSmartPointer<igObject> meta;
    meta = igObjectSystem_FindMetaByNameDefault(pump->_destMetaClassName);
    if (meta.get() != 0) {
        igObject *field = igMetaObject_FindFieldByName(meta.get(), pump->_destMetaFieldName);
        igObject *old;
        if (field != 0) {
            field->_refCount = field->_refCount + 1;
        }
        old = (igObject *)pump->_destMeta;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        pump->_destMeta = (int)field;
    }
}

void Gap__igDataPump__vfunc_14(void) {

}

int FUN_001e6770(int *p)
{
    return *(int *)((char *)p + 20);
}

int FUN_001e6780(void *arg0) {
    ObjectList_AppendRetained(*(int *)((char *)arg0 + 20));
    return 1;
}

int FUN_001e67a0(S *arg0, int arg1) {
    int i;
    int n;

    n = arg0->list->count;
    for (i = 0; i < n; i++) {
        FUN_001e6490((ValueBinding *)arg0->list->data[i], arg1);
    }
    return 1;
}

int FUN_001e6820(struct D *arg0, struct L_1e6820 *arg1) {
    int i;
    int n;

    n = arg1->count;
    for (i = 0; i < n; i++) {
        ObjectList_AppendRetained(arg0->f8, arg1->items[i]);
    }
    return 1;
}

int FUN_001e68a0(int arg0, int arg1) {
    FUN_001e6820((struct D *)arg0, (struct L_1e6820 *)FUN_001e6770((int *)arg1));
    return 1;
}

static inline int count_of(const Lst *list) { return list->count; }

int FUN_001e68e0(Lst *arg0, int arg1) {
    int var_s0;
    int temp_v1;
    Mat *d;

    var_s0 = arg0->count;
    if (var_s0 == 0) {
        if (var_s0 < arg0->cap) {
            arg0->count = count_of(arg0) + 1;
        } else {
            List_Resize(arg0, var_s0 + 1, 0x40);
        }
        Matrix44_Copy(arg0->data + var_s0, arg1);
    } else {
        temp_v1 = count_of(arg0);
        if (temp_v1 == 0) {
            var_s0 = 0;
        } else {
            if (var_s0 < arg0->cap) {
                arg0->count = temp_v1 + 1;
            } else {
                List_Resize(arg0, var_s0 + 1, 0x40);
            }
            d = arg0->data;
            Matrix44_Copy(d + var_s0, d + (var_s0 - 1));
        }
        FUN_001906d0(arg0->data + (arg0->count - 1), arg1);
    }
    return var_s0;
}

static inline int f8_of(const struct S_1e69e0 *list) { return list->f8; }

int FUN_001e69e0(struct S_1e69e0 *arg0, int arg1) {
    char *temp_a0;
    char *temp_a1;
    int temp_v1;
    int var_s0;

    var_s0 = f8_of(arg0);
    if (var_s0 == 0) {
        if (var_s0 < arg0->f12) {
            arg0->f8 = arg0->f8 + 1;
        } else {
            List_Resize(arg0, var_s0 + 1, 0x40);
        }
        Matrix44_Copy(arg0->f16 + (var_s0 << 6), arg1);
    } else {
        temp_v1 = arg0->f8;
        if (temp_v1 == 0) {
            var_s0 = 0;
        } else {
            if (var_s0 < arg0->f12) {
                arg0->f8 = temp_v1 + 1;
            } else {
                List_Resize(arg0, var_s0 + 1, 0x40);
            }
            temp_a1 = arg0->f16;
            Matrix44_Copy(temp_a1 + (var_s0 << 6), temp_a1 + ((var_s0 - 1) << 6));
        }
        temp_a0 = arg0->f16 + ((arg0->f8 - 1) << 6);
        FUN_001904f0(temp_a0, temp_a0, arg1);
    }
    return var_s0;
}

void FUN_001e6ae0(struct S1e *arg0) {
    FUN_001906d0(arg0->base + (arg0->cnt - 1) * 64);
}

void FUN_001e6b00(void *arg0, int arg1) {
    int p;
    p = *(int *)((char *)(arg0) + 16) + ((*(int *)((char *)(arg0) + 8) - 1) << 6);
    FUN_001904f0(p, p, arg1);
}

