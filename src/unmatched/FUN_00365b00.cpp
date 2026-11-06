extern "C" {
void *beDataBase_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00365b00(void);
}
void FUN_00365b00(void)
{
    igMetaObject_RunStaticInit(beDataBase_Register);
}
