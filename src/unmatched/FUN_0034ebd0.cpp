extern "C" {
void *beMovieInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034ebd0(void);
}
void FUN_0034ebd0(void)
{
    igMetaObject_RunStaticInit(beMovieInfo_Register);
}
