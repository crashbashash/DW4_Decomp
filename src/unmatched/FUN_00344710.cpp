extern "C" {
void *bePlaySEList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00344710(void);
}
void FUN_00344710(void)
{
    igMetaObject_RunStaticInit(bePlaySEList_Register);
}
