void igGuiComponentNode_resetFields(Node *self, int flags) {
    Vec3 origin;
    Gap__Sg__igNode__resetFields((igNode *)self, flags);
    igSmartPointer<igObject> transform(igAABox_CreateInstance((int)(igObject_GetAllocator(self))));
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
    FUN_001900d0(transform.get(), &origin);
    igObject *retained = transform.get();
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    igObject *previous = self->child;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->child = retained;
}

int FUN_00455ad0(int arg0, int arg1, int arg2) {
    if (g_activeMousePosObserver != 0) {
        FUN_00455f50((Z *)g_activeMousePosObserver, (Y *)arg2);
    }
    return 0;
}

