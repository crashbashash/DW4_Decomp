extern "C" {
void *beDataBaseList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00365830(void);
}
void FUN_00365830(void)
{
    igMetaObject_RunStaticInit(beDataBaseList_Register);
}
