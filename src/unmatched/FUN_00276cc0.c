/* Queries FUN_00276b18 into a 16-byte local record and reports whether its second word is non-
 * zero. */
struct Info276 {
    int f0;
    int second;
    int f8;
    int f12;
};

extern void FUN_00276b18(int handle, struct Info276 *info);

int FUN_00276cc0(int handle) {
    struct Info276 info;

    FUN_00276b18(handle, &info);
    return info.second != 0;
}
