/* Recognises an AIFF header: "FORM" at +0 and "AIFF" at +8. FUN_00127004 compares like memcmp
 * (pointer, pointer, length). */
int FUN_00127004(const void *a, const void *b, unsigned int size);

extern const char FORM[];
extern const char AIFF[];

int FUN_0025bfd0(const char *header) {
    if (FUN_00127004(header, FORM, 4) == 0 && FUN_00127004(header + 8, AIFF, 4) == 0) {
        return 1;
    }
    return 0;
}
