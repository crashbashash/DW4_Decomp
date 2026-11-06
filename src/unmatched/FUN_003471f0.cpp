extern "C" {
void *beSvPlatDataPC_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003471f0(void);
}
void FUN_003471f0(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPC_Register);
}
