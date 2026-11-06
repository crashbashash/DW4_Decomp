extern "C" {
void *beNumberCtrlInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034d3d0(void);
}
void FUN_0034d3d0(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfoWork_Register);
}
