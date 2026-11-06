extern "C" {
void *beDataObjList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00364170(void);
}
void FUN_00364170(void)
{
    igMetaObject_RunStaticInit(beDataObjList_Register);
}
