/* Flushes a pending gather list through FUN_001258b0 and resets it; the shape of newlib's vfprintf
 * helper __sprint (hypothesis: printf-family copy; FUN_001258b0 reads uio->resid at +8 as
 * __sfvwrite does). */
typedef struct GatherList {
    void *iov;      /* +0: vector of {base, len} */
    int iovcnt;     /* +4: entries in use */
    int resid;      /* +8: bytes still to write */
} GatherList;

int FUN_001258b0(void *stream, GatherList *uio);

int FUN_0012d4c8(void *stream, GatherList *uio) {
    int err;

    if (uio->resid == 0) {
        uio->iovcnt = 0;
        return 0;
    }
    err = FUN_001258b0(stream, uio);
    uio->resid = 0;
    uio->iovcnt = 0;
    return err;
}
