extern "C" {
void *beMemory_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00359310(void);
}
void FUN_00359310(void)
{
    igMetaObject_RunStaticInit(beMemory_Register);
}
