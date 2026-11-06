extern "C" {
void *beDataObjInt_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00365680(void);
}
void FUN_00365680(void)
{
    igMetaObject_RunStaticInit(beDataObjInt_Register);
}
