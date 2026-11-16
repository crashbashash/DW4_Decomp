/* Once M2VLIB_CheckHn accepts the handle, polls `stream` with MPV_GoNextDelimSj (advancing with
 * MPV_MoveChunk while it returns 4) until a status in mask 0xCC appears, then reports 0 or
 * 0xFF030305 through M2VERR_SetCode. */
int M2VLIB_CheckHn(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void M2VERR_SetCode(void *handle, int error);
int MPV_GoNextDelimSj(void *stream);
int MPV_MoveChunk(void *stream, int a, int b);

void M2V_SkipFrm(void *handle, void *stream) {
    int error;
    int status;

    if (M2VLIB_CheckHn(handle) != 0) {
        M2VERR_SetCode(0, 0xFF03020A);
        return;
    }
    error = 0xFF030305;
    for (;;) {
        status = MPV_GoNextDelimSj(stream);
        if (status == 0) {
            break;
        }
        if (status & 0xCC) {
            error = 0;
            break;
        }
        if (MPV_MoveChunk(stream, 1, 4) != 4) {
            break;
        }
    }
    M2VERR_SetCode(handle, error);
}
