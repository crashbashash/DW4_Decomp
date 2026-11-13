struct Info0028d510 {
    char data[32];
};

struct Stream0028d510 {
    char pad0[72];
    struct Info0028d510 info[1]; /* +72, 32 bytes each */
};

int mps_CheckHn(struct Stream0028d510 *stream);
int mps_ReportError(int a0, int code);

int FUN_0028d510(struct Stream0028d510 *stream, struct Info0028d510 *out, int index) {
    int result = mps_CheckHn(stream);

    if (result != 0) {
        return mps_ReportError(0, 0xff020202);
    }
    *out = stream->info[index];
    return result;
}
