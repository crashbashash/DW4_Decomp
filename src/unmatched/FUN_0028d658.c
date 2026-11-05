/* 0x0028d658 — FUN_0028d658 (124 bytes). Copies the five 64-bit words at +168..+200 of a stream handle to
   out[0..4] after validating it (FUN_0028da60); an invalid handle is reported as error 0xFF020203 through
   FUN_0028d890. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Stream28d {
    int state;
    char pad4[164];
    long long info[5];   /* +168 */
};

extern int FUN_0028da60(struct Stream28d *stream);
extern void FUN_0028d890(int a0, int code);

/* matching construct: hand search — returns the validation result on the success path (keeps it live in v0,
   so the copy uses v1/a0); the error path returns no value, as in the implicit-int original */
int FUN_0028d658(struct Stream28d *stream, long long *out) {
    int result;

    result = FUN_0028da60(stream);
    if (result != 0) {
        FUN_0028d890(0, 0xFF020203);
        return;
    }
    out[0] = stream->info[0];
    out[1] = stream->info[1];
    out[2] = stream->info[2];
    out[3] = stream->info[3];
    out[4] = stream->info[4];
    return result;
}
