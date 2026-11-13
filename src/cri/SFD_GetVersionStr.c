extern char cri_sfd_version[];

/* "\nCRI SFD/PS2EE Ver.1.946 Build:..." */
char *SFD_GetVersionStr(void) {
    return cri_sfd_version;
}
