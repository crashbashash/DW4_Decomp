extern "C" {
void *beNDMWGameRamInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ca2d0(void);
}
void FUN_003ca2d0(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRamInfoRam_Register);
}
