extern "C" {
void *igCriMovieData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00335c10(void);
}
void FUN_00335c10(void)
{
    igMetaObject_RunStaticInit(igCriMovieData_Register);
}
