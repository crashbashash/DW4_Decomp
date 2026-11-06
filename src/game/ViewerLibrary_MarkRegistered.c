extern unsigned char g_ViewerLibrary_registered;
void ViewerLibrary_MarkRegistered(void) {
    if (g_ViewerLibrary_registered == 0) {
        g_ViewerLibrary_registered = 1;
    }
}
