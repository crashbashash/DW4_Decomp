/* 0x0026dc78 — FUN_0026dc78 (140 bytes). With both a source (+4) and a stream (+8): in normal mode (+108 clear) resets the source with FUN_002671c8(source, -1) and opens the stream fully (FUN_0026a300 with 0x7fffffff); otherwise passes the source's byte count (FUN_00267300) as 2048-byte sectors to FUN_0026a140. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Obj_26dc78 {
    int pad0;
    int source;         /* 0x04 */
    int stream;         /* 0x08 */
    char pad12[96];
    signed char mode;   /* 0x6c */
} Obj_26dc78;

int FUN_00267300(int source);
void FUN_002671c8(int source, int arg);
void FUN_0026a300(int stream, int limit);
void FUN_0026a140(int stream, int sectors);

void FUN_0026dc78(Obj_26dc78 *obj) {
    int stream = obj->stream;
    int source = obj->source;
    int bytes;

    if (stream == 0 || source == 0) {
        return;
    }
    bytes = FUN_00267300(source);
    if (obj->mode == 0) {
        FUN_002671c8(obj->source, -1);
        FUN_0026a300(obj->stream, 0x7fffffff);
    } else {
        FUN_0026a140(stream, bytes / 2048);
    }
}

