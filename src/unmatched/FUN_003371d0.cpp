extern "C" {
void *igMoviePlugin_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003371d0(void);
}
void FUN_003371d0(void)
{
    igMetaObject_RunStaticInit(igMoviePlugin_Register);
}
