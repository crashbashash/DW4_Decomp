extern "C" {
void *beDataObjBoolList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00364ea0(void);
}
void FUN_00364ea0(void)
{
    igMetaObject_RunStaticInit(beDataObjBoolList_Register);
}
