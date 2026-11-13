struct SfdHdrInfo {
    char pad0[20];
    int extFirst;   /* +20: present from header version 225 */
    int extSecond;  /* +24 */
};

struct SfdHdrSrc {
    char pad0[176];
    struct SfdHdrInfo info; /* +176 */
};

struct SfdHdrHn {
    int pad0;
    struct SfdHdrSrc *src; /* +4 */
    int pad8;
    int version;           /* +12 */
};

int sfd_GetHdrExtInfoSecond(struct SfdHdrHn *hn, int *value) {
    struct SfdHdrInfo *info;

    *value = 0;
    info = &hn->src->info;
    if (hn->version < 225) {
        return 0;
    }
    *value = info->extSecond;
    return 1;
}
