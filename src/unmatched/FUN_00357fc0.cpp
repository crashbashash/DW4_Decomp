extern "C" {
void *beMessengerWorkList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00357fc0(void);
}
void FUN_00357fc0(void)
{
    igMetaObject_RunStaticInit(beMessengerWorkList_Register);
}
