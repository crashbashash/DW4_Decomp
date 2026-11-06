extern "C" {
void *igCriMovieCodec_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003359b0(void);
}
void FUN_003359b0(void)
{
    igMetaObject_RunStaticInit(igCriMovieCodec_Register);
}
