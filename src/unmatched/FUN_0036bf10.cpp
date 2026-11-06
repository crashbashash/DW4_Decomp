extern "C" {
void *beActionStarterData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036bf10(void);
}
void FUN_0036bf10(void)
{
    igMetaObject_RunStaticInit(beActionStarterData_Register);
}
