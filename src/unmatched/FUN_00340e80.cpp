extern "C" {
void *beWaterPlain_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00340e80(void);
}
void FUN_00340e80(void)
{
    igMetaObject_RunStaticInit(beWaterPlain_Register);
}
