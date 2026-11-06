extern "C" {
void *beLoadingNode_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034e710(void);
}
void FUN_0034e710(void)
{
    igMetaObject_RunStaticInit(beLoadingNode_Register);
}
