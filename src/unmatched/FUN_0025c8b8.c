/* Recognises a Sun/NeXT audio header: ".snd" or ".sd" magic at +0. memcmp compares like
 * memcmp (pointer, pointer, length). */
int memcmp(const void *a, const void *b, unsigned int size);

extern const char _snd[];
extern const char _sd[];

int FUN_0025c8b8(const char *header) {
    if (memcmp(header, _snd, 4) == 0 || memcmp(header, _sd, 4) == 0) {
        return 1;
    }
    return 0;
}
