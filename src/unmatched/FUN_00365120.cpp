extern "C" {
void *beDataObjBool_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00365120(void);
}
void FUN_00365120(void)
{
    igMetaObject_RunStaticInit(beDataObjBool_Register);
}
