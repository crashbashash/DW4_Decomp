typedef struct HashNode {
    unsigned int key;
    struct HashNode *next;
    struct HashNode *prev;
} HashNode;

void FUN_00245710(void);
extern unsigned int DAT_004986e0;
extern unsigned int DAT_004986e8;
extern unsigned int DAT_0056df00;
extern HashNode **DAT_0056df08;

void FUN_00245b50(HashNode *node) {
    HashNode **bucket;

    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        bucket = &DAT_0056df08[(DAT_004986e8 - 1) & (node->key ^ (node->key >> DAT_004986e0))];
        if (*bucket == node) {
            *bucket = node->next;
        } else {
            return;
        }
    }
    DAT_0056df00--;
    FUN_00245710();
}
