extern "C" {
void *beWaterPlainInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00340bb0(void);
}
void FUN_00340bb0(void)
{
    igMetaObject_RunStaticInit(beWaterPlainInfo_Register);
}
