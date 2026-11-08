struct Info0028d510 {
    char data[32];
};

struct Stream0028d510 {
    char pad0[72];
    struct Info0028d510 info[1]; /* +72, 32 bytes each */
};

int FUN_0028da60(struct Stream0028d510 *stream);
int FUN_0028d890(int a0, int code);

int FUN_0028d510(struct Stream0028d510 *stream, struct Info0028d510 *out, int index) {
    int result = FUN_0028da60(stream);

    if (result != 0) {
        return FUN_0028d890(0, 0xff020202);
    }
    *out = stream->info[index];
    return result;
}
