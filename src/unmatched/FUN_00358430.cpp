extern "C" {
void *beMessengerGroupList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00358430(void);
}
void FUN_00358430(void)
{
    igMetaObject_RunStaticInit(beMessengerGroupList_Register);
}
