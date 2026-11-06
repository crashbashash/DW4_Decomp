extern "C" {
void beNDMWAfsSetup_ResolveMetaObject(void);
void beNDMWAfsSetup_GetMetaObject(void);
}
void beNDMWAfsSetup_GetMetaObject(void)
{
    beNDMWAfsSetup_ResolveMetaObject();
}
