extern unsigned char g_AdxMovieLibrary_registered[4];
void AdxMovieLibrary_MarkRegistered(void) {
    if (g_AdxMovieLibrary_registered[0] == 0) {
        g_AdxMovieLibrary_registered[0] = 1;
    }
}
