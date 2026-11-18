void FUN_001a44d0(void) {
    igCommonTraversal_UserRegister();
    igMetaObject_AddRegistrationCallback((int)igCommonTraversal_RegisterClass);
}

void thunk_igCommonTraversal_UserUnregister(void) {
    igCommonTraversal_UserUnregister();
}

int *igSmartPointer_igMetaObjectList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

