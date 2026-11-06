extern "C" {
void *beNDMWStatusTitle00_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b3d90(void);
}
void FUN_003b3d90(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle00_Register);
}
