extern "C" {
void *beNDMWStatus_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bb8e0(void);
}
void FUN_003bb8e0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatus_Register);
}
