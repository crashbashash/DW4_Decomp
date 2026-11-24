namespace Gap {
namespace Sg {

void igCommonTraversal::arkRegisterUser() {
    userRegister();
    igMetaObject_AddRegistrationCallback((int)registerClass);
}
}
}

void thunk_igCommonTraversal_UserUnregister(void) {
    Gap::Sg::igCommonTraversal::userUnregister();
}

int *igSmartPointer_igMetaObjectList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

