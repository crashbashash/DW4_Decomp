extern "C" {
void *beNDMWSaveIntfComMdlCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bc350(void);
}
void FUN_003bc350(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfComMdlCtrl_Register);
}
