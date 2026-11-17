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

igSmartPointer<igObject> *igSmartPointer_igInfoList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igSceneInfo_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igDirectory_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

