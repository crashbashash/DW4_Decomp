extern "C" {
void *igMovieInfoList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00335ec0(void);
}
void FUN_00335ec0(void)
{
    igMetaObject_RunStaticInit(igMovieInfoList_Register);
}
