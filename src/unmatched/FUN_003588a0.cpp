extern "C" {
void *beMessengerDelayList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003588a0(void);
}
void FUN_003588a0(void)
{
    igMetaObject_RunStaticInit(beMessengerDelayList_Register);
}
