extern unsigned char g_BecLibrary_registered;
void BecLibrary_MarkRegistered(void) {
    if (g_BecLibrary_registered == 0) {
        g_BecLibrary_registered = 1;
    }
}
