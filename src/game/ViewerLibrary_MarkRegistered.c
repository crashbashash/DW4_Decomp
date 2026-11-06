extern unsigned char g_ViewerLibrary_registered[4];
void ViewerLibrary_MarkRegistered(void) {
    if (g_ViewerLibrary_registered[0] == 0) {
        g_ViewerLibrary_registered[0] = 1;
    }
}
