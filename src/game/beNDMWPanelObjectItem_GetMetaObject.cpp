extern "C" {
void beNDMWPanelObjectItem_ResolveMetaObject(void);
void beNDMWPanelObjectItem_GetMetaObject(void);
}
void beNDMWPanelObjectItem_GetMetaObject(void)
{
    beNDMWPanelObjectItem_ResolveMetaObject();
}
