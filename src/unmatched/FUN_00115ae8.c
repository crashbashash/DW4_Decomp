typedef struct Node {
    struct Node *next;
    int f4;
    int f8;
    int f12;
} Node;
extern Node DAT_0055c940[64];
extern Node *DAT_0055cd40;
int FUN_00115ae8(void) {
    int i;
    DAT_0055cd40 = DAT_0055c940;
    for (i = 63; i >= 0; i--) DAT_0055c940[i].next = &DAT_0055c940[i + 1];
    DAT_0055c940[63].next = 0;
    return 0;
}
