extern "C" {
void *beMovieInfoData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034ed80(void);
}
void FUN_0034ed80(void)
{
    igMetaObject_RunStaticInit(beMovieInfoData_Register);
}
