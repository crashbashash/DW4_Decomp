extern "C" {
void *beMatCtrlSearch_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035a120(void);
}
void FUN_0035a120(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearch_Register);
}
