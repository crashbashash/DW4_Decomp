extern unsigned char g_AdxMovieLibrary_registered;
void AdxMovieLibrary_MarkRegistered(void) {
    if (g_AdxMovieLibrary_registered == 0) {
        g_AdxMovieLibrary_registered = 1;
    }
}
