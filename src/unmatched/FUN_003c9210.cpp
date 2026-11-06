extern "C" {
void *beNDMWItemBaseList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c9210(void);
}
void FUN_003c9210(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBaseList_Register);
}
