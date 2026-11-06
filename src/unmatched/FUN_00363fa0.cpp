extern "C" {
void *beDataObjListList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00363fa0(void);
}
void FUN_00363fa0(void)
{
    igMetaObject_RunStaticInit(beDataObjListList_Register);
}
