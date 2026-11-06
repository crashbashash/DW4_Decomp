extern "C" {
void *beGeneraterPlayerData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003601e0(void);
}
void FUN_003601e0(void)
{
    igMetaObject_RunStaticInit(beGeneraterPlayerData_Register);
}
