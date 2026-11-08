struct Pair00298618 {
    int a;
    int b;
};

int FUN_0027d6b0(struct Pair00298618 *in, const char *key1, const char *key2, struct Pair00298618 *out);
void FUN_002b3c98(int stream, int x, int y);

extern char DAT_004f4458[];
extern char DAT_004f4460[];

void FUN_00298618(char *ply) {
    struct Pair00298618 in;
    struct Pair00298618 out;
    int *src = (int *)(ply + 424);
    int stream = *(int *)(ply + 172);

    if (src[1] == 0) {
        FUN_002b3c98(stream, 0, 0);
        return;
    }
    in.a = src[1];
    in.b = src[2];
    if (FUN_0027d6b0(&in, DAT_004f4458, DAT_004f4460, &out) == 0) {
        FUN_002b3c98(stream, 0, 0);
        return;
    }
    FUN_002b3c98(stream, out.a, out.b);
}
