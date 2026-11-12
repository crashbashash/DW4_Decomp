void Gap__Sg__igNode__vfunc_09(void **arg0, int arg1) {
    Gap__Core__igObject__vfunc_07();
    if (arg1 == 0) {
        ((DW4VC_112_2 *)(arg0))->vX((int)(((DW4VC_120_0 *)(arg0))->vX()), (int)(1));
    }
}

int FUN_001d3400(void) {
    return 0;
}

void FUN_001d3410(NodeSlots *o, void *with) {
    NodeSlots *held = o;
    int i;
    retain_1d3410((int *)&held);
    i = o->getChildCount() - 1;
    while (i >= 0) {
        GroupChild *c = o->getChild(i);
        NodeParentListView *l = c->_parents;
        NodeSlots *self = o;
        c->replaceChild(findParent(l, (int *)&self), with);
        FUN_001c6050((S_1c5eb0 *)c, (Obj_1c5eb0 *)o);
        i--;
    }
    FUN_001c5d10(with, (int)(o));
    release_1d3410((int *)&held);
}

void FUN_001d3550(void *arg0) {
    Gap__Core__igObject__vfunc_11();
    *(int *)((char *)(arg0) + 24) = (int)((int) *(int *)((char *)(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX()) + 8));
}

void Gap__Sg__igNode__vfunc_17(void *arg0) {
    Gap__Core__igObject__vfunc_15();
    *(int *)((char *)(arg0) + 24) = (int)((int) *(int *)((char *)(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX()) + 8));
}

void **FUN_001d35d0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_001d3650(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_001d36d0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

