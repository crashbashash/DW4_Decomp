extern "C" {
void *beDataObjStringList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00364930(void);
}
void FUN_00364930(void)
{
    igMetaObject_RunStaticInit(beDataObjStringList_Register);
}
