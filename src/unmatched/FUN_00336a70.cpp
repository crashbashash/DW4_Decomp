extern "C" {
void *igMovieRenderer_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00336a70(void);
}
void FUN_00336a70(void)
{
    igMetaObject_RunStaticInit(igMovieRenderer_Register);
}
