typedef struct HashNode {
    unsigned int key;
    struct HashNode *next;
    struct HashNode *prev;
} HashNode;
extern int DAT_004986a8;
extern int DAT_004986a0;
extern HashNode **DAT_0056dea8;
extern int DAT_0056dea0;
void FUN_00244e70(HashNode *node);
void FUN_00245de0(HashNode *node) {
    HashNode **bucket;

    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        bucket = &DAT_0056dea8[(DAT_004986a8 - 1) & (node->key ^ (node->key >> DAT_004986a0))];
        if (*bucket == node) {
            *bucket = node->next;
        } else {
            return;
        }
    }
    DAT_0056dea0--;
    FUN_00244e70(node);
}
