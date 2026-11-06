extern "C" {
void *beGeneraterInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035f5d0(void);
}
void FUN_0035f5d0(void)
{
    igMetaObject_RunStaticInit(beGeneraterInfoRam_Register);
}
