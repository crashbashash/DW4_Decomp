extern "C" {
void *beNDMWLoadSavePlWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c5780(void);
}
void FUN_003c5780(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWork_Register);
}
