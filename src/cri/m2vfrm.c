int M2VLIB_CheckHn(void *hn);
int M2VERR_SetCode(void *hn, int code);
int MPV_GoNextDelimSj(void *sj);
int MPV_MoveChunk(void *sj, int id, int nbyte);

void M2V_SkipFrm(void *hn, void *sj)
{
    int err;
    int code;

    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF03020A);
        return;
    }
    err = 0xFF030305;
    for (;;) {
        code = MPV_GoNextDelimSj(sj);
        if (code == 0) {
            break;
        }
        if (code & 0xCC) {
            err = 0;
            break;
        }
        if (MPV_MoveChunk(sj, 1, 4) != 4) {
            break;
        }
    }
    M2VERR_SetCode(hn, err);
}

void M2V_DecodeFrm(void)
{
}
