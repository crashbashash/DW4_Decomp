extern unsigned char g_GuiLibrary_registered[4];
void GuiLibrary_MarkRegistered(void) {
    if (g_GuiLibrary_registered[0] == 0) {
        g_GuiLibrary_registered[0] = 1;
    }
}
