extern "C" {
void *beActionStarterInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036b4b0(void);
}
void FUN_0036b4b0(void)
{
    igMetaObject_RunStaticInit(beActionStarterInfo_Register);
}
