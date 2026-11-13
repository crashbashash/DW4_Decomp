/* The bump allocator over the decoder's work area (_sceMpegAlalcAlloc). */
typedef struct {
    char *start;
    int size;
    char *cur;
    char *mark;
} MpegArena;

int _sceMpegAlalcRemaining(MpegArena *arena) {
    return arena->start + arena->size - arena->cur;
}
