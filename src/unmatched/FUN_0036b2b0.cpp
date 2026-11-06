extern "C" {
void *beActionStarterInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036b2b0(void);
}
void FUN_0036b2b0(void)
{
    igMetaObject_RunStaticInit(beActionStarterInfoRam_Register);
}
