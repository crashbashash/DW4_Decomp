/* Fetches the stream's two buffer spans (FUN_002a8e50), submits them in the uncached segment to
 * FUN_002a9dc8 and reports the result to FUN_002a8f40. */
void FUN_002a8e50();
void FUN_002a8f40();
int FUN_002a9dc8();

/* Converts an address to the EE uncached segment (0x20000000). */
#define UNCACHED(address) (((address) & 0x0FFFFFFF) | 0x20000000)

int FUN_002a9a30(void *stream, int arg1, int arg2) {
    unsigned int first;
    int firstSize;
    unsigned int second;
    int secondSize;
    int result;

    FUN_002a8e50(stream, &first, &firstSize, &second, &secondSize);
    result = FUN_002a9dc8(UNCACHED(first), firstSize, UNCACHED(second), secondSize, arg1, arg2, 0, 0);
    FUN_002a8f40(stream, result);
    return result;
}
