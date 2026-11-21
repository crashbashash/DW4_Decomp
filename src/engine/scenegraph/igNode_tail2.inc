int igNode_IsTransformable(void **arg0) {
    return ((DW4VC_92_0 *)(arg0))->vX() < 2;
}

void igGroup_Transform(int *arg0, int arg1) {
    unsigned int n;
    unsigned int i;

    if (arg0[7] != 0) {
        n = ((Q_1c6340 *)arg0[7])->count;
    } else {
        n = 0;
    }
    for (i = 0; i < n; i++) {
        ((Q_1c6340 *)arg0[7])->data[i]->vX(arg1);
    }
}

void igNode_Transform(void) {

}

char g_invarianceFunctionFieldResolved;

void *g_invarianceFunctionMetaField;

void FUN_001c63e0(int arg0, int arg1) {
    int (*temp_v1)(int);

    if (g_invarianceFunctionFieldResolved == 0) {
        g_invarianceFunctionMetaField = (void *)(((void *)igMetaObject_FindFieldByName(Gap::Core::igMetaField::getClassMeta(), "_invarianceFunction")));
        g_invarianceFunctionFieldResolved = 1;
    }
    temp_v1 = (int (*)(int))(*(int *)(arg0 + *(int *)((char *)(g_invarianceFunctionMetaField) + 8)));
    if (temp_v1 != 0) {
        temp_v1(arg1);
    }
}

igSmartPointer<igObject> *igSmartPointer_igStringRefList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

