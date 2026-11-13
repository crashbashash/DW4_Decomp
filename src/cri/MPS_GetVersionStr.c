extern char cri_mps_version[];

/* "\nCRI MPS/PS2EE Ver.1.924 Build:..." */
char *MPS_GetVersionStr(void) {
    return cri_mps_version;
}
