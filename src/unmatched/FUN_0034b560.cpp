extern "C" {
void *beResetNode_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034b560(void);
}
void FUN_0034b560(void)
{
    igMetaObject_RunStaticInit(beResetNode_Register);
}
