extern "C" {
void *beNDMWGameRamInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ca480(void);
}
void FUN_003ca480(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRamInfo_Register);
}
