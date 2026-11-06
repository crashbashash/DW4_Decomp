extern "C" {
void *beModelCtrlAIMap_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00354510(void);
}
void FUN_00354510(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMap_Register);
}
