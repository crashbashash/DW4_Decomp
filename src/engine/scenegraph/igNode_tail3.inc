void Gap__Sg__igNode__vfunc_09(void **arg0, int arg1) {
    Gap__Core__igObject__userConstruct((igObject *)arg0);
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
        igGroup_RemoveChild((igGroup *)c, (igNode *)o);
        i--;
    }
    igGroup_AppendChild((igGroup *)with, (igNode *)o);
    release_1d3410((int *)&held);
}

void Gap__Sg__igNode__resetFields(igNode *arg0, int flags) {
    Gap__Core__igObject__resetFields((igObject *)arg0, flags);
    *(int *)((char *)(arg0) + 24) = (int)((int) *(int *)((char *)(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX()) + 8));
}

void Gap__Sg__igNode__vfunc_17(void *arg0) {
    igObject_UserPostLoad();
    *(int *)((char *)(arg0) + 24) = (int)((int) *(int *)((char *)(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX()) + 8));
}

void **igSmartPointer_igInfoList_Destruct(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **igSmartPointer_igSceneInfo_Destruct(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

O *igSmartPointer_igDirectory_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

