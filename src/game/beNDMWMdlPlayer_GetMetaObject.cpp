extern "C" {
void beNDMWMdlPlayer_ResolveMetaObject(void);
void beNDMWMdlPlayer_GetMetaObject(void);
}
void beNDMWMdlPlayer_GetMetaObject(void)
{
    beNDMWMdlPlayer_ResolveMetaObject();
}
