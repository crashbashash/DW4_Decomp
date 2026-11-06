extern unsigned char g_AudioLibrary_registered;
void AudioLibrary_MarkRegistered(void) {
    if (g_AudioLibrary_registered == 0) {
        g_AudioLibrary_registered = 1;
    }
}
