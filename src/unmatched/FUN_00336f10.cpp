extern "C" {
void *igMovieManager_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00336f10(void);
}
void FUN_00336f10(void)
{
    igMetaObject_RunStaticInit(igMovieManager_Register);
}
