/* Copies the two 64-bit words at +24 / +32 of a stream handle to out[0] / out[1] after validating
 * it (FUN_0028da60); an invalid handle is reported as error 0xFF020201 through FUN_0028d890. */
struct Stream28d {
    int state;
    char pad4[20];
    long long first;    /* +24 */
    long long second;   /* +32 */
};

extern int FUN_0028da60(struct Stream28d *stream);
extern void FUN_0028d890(int a0, int code);

/* matching construct: hand search — returns the validation result on the success path (keeps it live in v0,
   so the copy uses v1/a0); the error path returns no value, as in the implicit-int original */
int FUN_0028d4a8(struct Stream28d *stream, long long *out) {
    int result;

    result = FUN_0028da60(stream);
    if (result != 0) {
        FUN_0028d890(0, 0xFF020201);
        return;
    }
    out[0] = stream->first;
    out[1] = stream->second;
    return result;
}
