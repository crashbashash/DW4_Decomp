typedef struct HashNode {
    unsigned int key;
    struct HashNode *next;
    struct HashNode *prev;
} HashNode;
extern int DAT_004986f8;
extern int DAT_004986f0;
extern HashNode **DAT_0056df20;
extern int DAT_0056df18;
void FUN_00245900(HashNode *node);
void FUN_00245ab0(HashNode *node) {
    HashNode **bucket;

    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        bucket = &DAT_0056df20[(DAT_004986f8 - 1) & (node->key ^ (node->key >> DAT_004986f0))];
        if (*bucket == node) {
            *bucket = node->next;
        } else {
            return;
        }
    }
    DAT_0056df18--;
    FUN_00245900(node);
}
