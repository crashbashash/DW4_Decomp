struct B8 { unsigned char x : 7; unsigned char flag : 1; };
struct Hdr { char pad0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char pad4[4]; unsigned int w0 : 12; unsigned int hi : 12; unsigned int w2 : 8; };
int FUN_00324b50(int arg0, char *arg1) {
    struct Hdr *h;

    if (arg1 == 0) {
        return -1;
    }
    h = (struct Hdr *)(arg1 - 4);
    if (((struct B8 *)(arg1 - 1))->flag == 1) {
        h = (struct Hdr *)(arg1 - 12);
    }
    if (h == 0) {
        return -1;
    }
    if (h->flag == 0) {
        return h->lo * 2;
    }
    return (h->lo + (h->hi << 5)) * 2;
}
