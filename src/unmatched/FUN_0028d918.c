/* 0x0028d918 — FUN_0028d918 (148 bytes). Applies FUN_0028d9b0(target, a, b) to a stream handle's +4 block
   after validating it (FUN_0028da60), or to the global work area 0x004bcc68 when the handle is null; an
   invalid handle is reported as error 0xFF020101 through FUN_0028d890 and its result returned. Returns 0
   otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Stream28d {
    int state;
    char block[4];   /* +4 */
};

extern void FUN_0028d9b0(void *target, int a, int b);
extern int FUN_0028da60(struct Stream28d *stream);
extern int FUN_0028d890(int a0, int code);
extern void *DAT_004bcc68;

int FUN_0028d918(struct Stream28d *stream, int a, int b) {
    if (stream == 0) {
        FUN_0028d9b0(DAT_004bcc68, a, b);
    } else {
        if (FUN_0028da60(stream) != 0) {
            return FUN_0028d890(0, 0xFF020101);
        }
        FUN_0028d9b0(stream->block, a, b);
    }
    return 0;
}
