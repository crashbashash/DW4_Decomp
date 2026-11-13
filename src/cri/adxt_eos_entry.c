/* With both a source (+4) and a stream (+8): in normal mode (+108 clear) resets the source with
 * ADXSJD_SetTrapNumSmpl(source, -1) and opens the stream fully (ADXSTM_SetEos with 0x7fffffff); otherwise
 * passes the source's byte count (FUN_00267300) as 2048-byte sectors to FUN_0026a140. */
typedef struct Obj_26dc78 {
    int pad0;
    int source;         /* 0x04 */
    int stream;         /* 0x08 */
    char pad12[96];
    signed char mode;   /* 0x6c */
} Obj_26dc78;

int FUN_00267300(int source);
void ADXSJD_SetTrapNumSmpl(int source, int arg);
void ADXSTM_SetEos(int stream, int limit);
void FUN_0026a140(int stream, int sectors);

void adxt_eos_entry(Obj_26dc78 *obj) {
    int stream = obj->stream;
    int source = obj->source;
    int bytes;

    if (stream == 0 || source == 0) {
        return;
    }
    bytes = FUN_00267300(source);
    if (obj->mode == 0) {
        ADXSJD_SetTrapNumSmpl(obj->source, -1);
        ADXSTM_SetEos(obj->stream, 0x7fffffff);
    } else {
        FUN_0026a140(stream, bytes / 2048);
    }
}

