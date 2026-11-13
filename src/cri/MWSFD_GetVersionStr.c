extern char mwsfd_version[];

/* "\nMWSFD/PS2EE Ver.3.33s281 Build:..." */
char *MWSFD_GetVersionStr(void) {
    return mwsfd_version;
}
