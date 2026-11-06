extern "C" {
void *beWaterPlainInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003402c0(void);
}
void FUN_003402c0(void)
{
    igMetaObject_RunStaticInit(beWaterPlainInfoRam_Register);
}
