extern "C" {
void *igMovieCodec_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003357a0(void);
}
void FUN_003357a0(void)
{
    igMetaObject_RunStaticInit(igMovieCodec_Register);
}
