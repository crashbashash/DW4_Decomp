extern "C" {
void *beNDMWItemInstant_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8490(void);
}
void FUN_003c8490(void)
{
    igMetaObject_RunStaticInit(beNDMWItemInstant_Register);
}
