extern unsigned char g_BecLibrary_registered[4];
void BecLibrary_MarkRegistered(void) {
    if (g_BecLibrary_registered[0] == 0) {
        g_BecLibrary_registered[0] = 1;
    }
}
