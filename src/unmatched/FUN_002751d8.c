/* Queries FUN_00274e30 into a 48-byte local record and reports whether its first word is non-zero. */
struct Info275 {
    int first;
    int rest[11];
};

extern void FUN_00274e30(int handle, struct Info275 *info);

int FUN_002751d8(int handle) {
    struct Info275 info;

    FUN_00274e30(handle, &info);
    return info.first != 0;
}
