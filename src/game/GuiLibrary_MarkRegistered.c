extern unsigned char g_GuiLibrary_registered;
void GuiLibrary_MarkRegistered(void) {
    if (g_GuiLibrary_registered == 0) {
        g_GuiLibrary_registered = 1;
    }
}
