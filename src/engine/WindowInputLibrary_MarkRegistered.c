extern unsigned char g_WindowInputLibrary_registered[4];
void WindowInputLibrary_MarkRegistered(void) {
    if (g_WindowInputLibrary_registered[0] == 0) {
        g_WindowInputLibrary_registered[0] = 1;
    }
}
