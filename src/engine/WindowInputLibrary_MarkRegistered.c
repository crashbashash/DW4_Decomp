extern unsigned char g_WindowInputLibrary_registered;
void WindowInputLibrary_MarkRegistered(void) {
    if (g_WindowInputLibrary_registered == 0) {
        g_WindowInputLibrary_registered = 1;
    }
}
