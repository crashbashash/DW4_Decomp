extern "C" {
void *beDataObjString_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00364bf0(void);
}
void FUN_00364bf0(void)
{
    igMetaObject_RunStaticInit(beDataObjString_Register);
}
