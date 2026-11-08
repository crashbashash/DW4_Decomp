/* Returns 1 when a header carries the tag DAT_004ed868 at offset 0 and DAT_004ed870 at offset 8. */
int memcmp(const void *a, const void *b, int length);
extern char DAT_004ed868[];
extern char DAT_004ed870[];

int FUN_0025f200(const char *header) {
    if (memcmp(header, DAT_004ed868, 4) == 0 && memcmp(header + 8, DAT_004ed870, 4) == 0) {
        return 1;
    }
    return 0;
}
