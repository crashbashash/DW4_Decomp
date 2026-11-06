extern "C" {
void *beModelCtrlAIMapList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00354290(void);
}
void FUN_00354290(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMapList_Register);
}
