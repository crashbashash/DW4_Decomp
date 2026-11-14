void FUN_001a44d0(void) {
    FUN_001b6be0();
    igMetaObject_AddRegistrationCallback(FUN_001b68b0);
}

void thunk_FUN_001b6c50(void) {
    FUN_001b6c50();
}

int *FUN_001a4510(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

