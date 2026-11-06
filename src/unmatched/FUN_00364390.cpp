extern "C" {
void *beDataObjFloatList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00364390(void);
}
void FUN_00364390(void)
{
    igMetaObject_RunStaticInit(beDataObjFloatList_Register);
}
