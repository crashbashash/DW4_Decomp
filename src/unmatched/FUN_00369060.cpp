extern "C" {
void *beCameraDemoData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00369060(void);
}
void FUN_00369060(void)
{
    igMetaObject_RunStaticInit(beCameraDemoData_Register);
}
