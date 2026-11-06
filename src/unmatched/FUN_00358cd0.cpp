extern "C" {
void *beMessengerArgDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00358cd0(void);
}
void FUN_00358cd0(void)
{
    igMetaObject_RunStaticInit(beMessengerArgDataList_Register);
}
