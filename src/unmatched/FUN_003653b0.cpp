extern "C" {
void *beDataObjIntList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003653b0(void);
}
void FUN_003653b0(void)
{
    igMetaObject_RunStaticInit(beDataObjIntList_Register);
}
