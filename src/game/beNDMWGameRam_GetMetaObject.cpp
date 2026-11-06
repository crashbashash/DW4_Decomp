extern "C" {
void beNDMWGameRam_ResolveMetaObject(void);
void beNDMWGameRam_GetMetaObject(void);
}
void beNDMWGameRam_GetMetaObject(void)
{
    beNDMWGameRam_ResolveMetaObject();
}
