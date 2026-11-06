extern "C" {
void *igMovieInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003364c0(void);
}
void FUN_003364c0(void)
{
    igMetaObject_RunStaticInit(igMovieInfo_Register);
}
