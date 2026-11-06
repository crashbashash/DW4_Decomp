extern unsigned char g_BaseLibrary_registered;
void BaseLibrary_MarkRegistered(void) {
    if (g_BaseLibrary_registered == 0) {
        g_BaseLibrary_registered = 1;
    }
}
