struct ConfigOutputList;
struct ConfigTreeToken { int vt; unsigned int _refCount; char *text; int kind; };
struct ConfigTreeNode;
struct ConfigTreeChildren { int vt; int rc; int count; int capacity; ConfigTreeNode **data; };
struct ConfigTreeNode { int kind; int pad4; void *name; ConfigTreeToken *value; ConfigTreeChildren *children; int attributes; ConfigTreeToken *selector; };
extern "C" {
int FUN_002db2f0(void *, ConfigTreeToken *, void *, void *);
void FUN_002db1d0(void *, void *, void *, int);
void *FUN_002d9cf0(void *, void *, char *);
void *FUN_002d9710(void *, void *);
int FUN_0012a78c(void *);
int FUN_002dbca0(void *, void *);
unsigned char FUN_002dbd10(void *, int, void *, int, char *);
extern char *DAT_004c22f0[4];
void FUN_002db040(void *self, int entry, void *a, void *b);
}
void FUN_002db040(void *self, int entry, void *a, void *b) {
    int i;
    ConfigTreeNode *node;
    ConfigTreeToken *selector;
    unsigned char ok;
    char *text;
    void *target;
    if (((ConfigTreeNode *)entry)->kind == 1) {
        int r;
        node = (ConfigTreeNode *)entry;
        r = FUN_002db2f0(self, ((ConfigTreeNode *)entry)->value, a, b);
        if (r != -1) {
            FUN_002db1d0(self, node->name, a, r);
        }
    } else {
        selector = ((ConfigTreeNode *)entry)->selector;
        node = (ConfigTreeNode *)entry;
        if (selector != 0 && selector->kind != 0) {
            text = selector->text;
            text = (text == 0) ? DAT_004c22f0[0] : text;
            target = FUN_002d9cf0(self, node->name, text);
        } else {
            target = FUN_002d9710(self, node->name);
        }
        if (target == 0 || FUN_0012a78c(target) == 0) {
            ok = 0;
        } else {
            text = node->value->text;
            text = (text == 0) ? DAT_004c22f0[0] : text;
            ok = FUN_002dbd10(self, FUN_002dbca0(self, node->name), target, node->attributes, text);
        }
        if (ok) {
            for (i = 0; i < node->children->count; i++) {
                FUN_002db040(self, (int)node->children->data[i], a, b);
            }
        }
    }
}
