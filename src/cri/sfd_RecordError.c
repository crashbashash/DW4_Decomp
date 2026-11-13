/* Error block of a handle (or the library's global one): the first error code it records and the
 * callback told about every error. */
typedef struct {
    void (*func)(void *obj, int code);
    void *obj;
    int code;
} SfdErrBlock;

void sfd_RecordError(SfdErrBlock *err, int code) {
    if (err->code == 0) {
        err->code = code;
    }
    if (code != 0 && err->func != 0) {
        err->func(err->obj, code);
    }
}
