typedef struct {
    unsigned int src;
    unsigned int dest;
    int size;
    int attr;
} DmaData;
extern DmaData DAT_0055d500;
int FUN_0010b280(int id);
int FUN_0010b2a0(DmaData *d, int n);
int FUN_00119090(unsigned int src, unsigned int dest, int size, int wait) {
    int id;
    if (wait == 0) return -1;
    DAT_0055d500.src = src;
    DAT_0055d500.dest = dest;
    DAT_0055d500.size = size;
    DAT_0055d500.attr = 0;
    id = FUN_0010b2a0(&DAT_0055d500, 1);
    if (id == 0) return -1;
    if (wait == 1) {
        while (FUN_0010b280(id) >= 0);
    }
    return 0;
}
