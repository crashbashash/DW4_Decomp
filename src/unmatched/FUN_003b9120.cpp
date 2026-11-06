extern "C" {
void *beNDMWStatusSubMenu_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b9120(void);
}
void FUN_003b9120(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSubMenu_Register);
}
