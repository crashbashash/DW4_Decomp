typedef struct HashNode {
    unsigned int key;
    struct HashNode *next;
    struct HashNode *prev;
} HashNode;
extern int DAT_004986c8;
extern int DAT_004986c0;
extern HashNode **DAT_0056ded8;
extern int DAT_0056ded0;
void FUN_00245310(HashNode *node);
void FUN_00245ca0(HashNode *node) {
    HashNode **bucket;

    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        bucket = &DAT_0056ded8[(DAT_004986c8 - 1) & (node->key ^ (node->key >> DAT_004986c0))];
        if (*bucket == node) {
            *bucket = node->next;
        } else {
            return;
        }
    }
    DAT_0056ded0--;
    FUN_00245310(node);
}
