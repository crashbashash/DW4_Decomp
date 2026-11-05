/* 0x0028b608 — FUN_0028b608 (88 bytes). Stores a word into +16 of a stream handle after validating it
   (FUN_0028da60); an invalid handle is reported as error 0xFF020302 through FUN_0028d890.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Stream28b {
    int state;
    char pad4[12];
    int value16;   /* +16 */
};

extern int FUN_0028da60(struct Stream28b *stream);
extern void FUN_0028d890(int a0, int code);

/* matching construct: hand search — int return type with no return value (implicit-int style); with void
   the epilogue restores are scheduled differently */
int FUN_0028b608(struct Stream28b *stream, int value) {
    if (FUN_0028da60(stream) != 0) {
        FUN_0028d890(0, 0xFF020302);
        return;
    }
    stream->value16 = value;
}
