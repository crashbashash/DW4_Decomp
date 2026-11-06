extern "C" {
void *beNDMWLoadSavePlWorkList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c5600(void);
}
void FUN_003c5600(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWorkList_Register);
}
