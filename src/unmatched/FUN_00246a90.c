typedef struct HashNode {
    unsigned int key;
    struct HashNode *next;
    struct HashNode *prev;
} HashNode;

void FUN_002468e0(void);
extern unsigned int DAT_00498718;
extern unsigned int DAT_00498720;
extern unsigned int DAT_0056df60;
extern HashNode **DAT_0056df68;

void FUN_00246a90(HashNode *node) {
    HashNode **bucket;

    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        bucket = &DAT_0056df68[(DAT_00498720 - 1) & (node->key ^ (node->key >> DAT_00498718))];
        if (*bucket == node) {
            *bucket = node->next;
        } else {
            return;
        }
    }
    DAT_0056df60--;
    FUN_002468e0();
}
