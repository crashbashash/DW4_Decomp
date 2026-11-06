extern "C" {
void *beCriAcxData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003677b0(void);
}
void FUN_003677b0(void)
{
    igMetaObject_RunStaticInit(beCriAcxData_Register);
}
