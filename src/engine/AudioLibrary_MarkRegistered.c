extern unsigned char g_AudioLibrary_registered[4];
void AudioLibrary_MarkRegistered(void) {
    if (g_AudioLibrary_registered[0] == 0) {
        g_AudioLibrary_registered[0] = 1;
    }
}
