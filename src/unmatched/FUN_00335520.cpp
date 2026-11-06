extern "C" {
void *igMovieCodecList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00335520(void);
}
void FUN_00335520(void)
{
    igMetaObject_RunStaticInit(igMovieCodecList_Register);
}
