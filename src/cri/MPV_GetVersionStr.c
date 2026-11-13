extern char cri_mpv_version[];

/* "\nCRI MPV/PS2EE Ver.1.933 Build:..." */
char *MPV_GetVersionStr(void) {
    return cri_mpv_version;
}
