extern "C" {
void *beWaterMove_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003405c0(void);
}
void FUN_003405c0(void)
{
    igMetaObject_RunStaticInit(beWaterMove_Register);
}
