typedef struct IniSectionNode { char _pad0[28]; int _parent; } IniSectionNode;
extern int FUN_001c6520(IniSectionNode *, int);
extern int FUN_00306360(int, void *, int);
extern unsigned char FUN_00306910(int, int, void *, char **, void *, int);
extern void StringChunk_ReleaseHeader(int, int *);
extern int DAT_004e4690[4];
extern int DAT_004e4678[4];
extern int DAT_004e4660[4];
static inline char *releaseText(char *s) {
    if (s != 0) {
        int *header = (int *)s - 2;
        int count = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    return 0;
}
int FUN_001c6fa0(char **out, IniSectionNode *node) {
    char *text;
    int index;
    int ok;
    if ((ok = FUN_001c6520(node, 0)) == 0) {
        *out = 0;
        return;
    }
    index = FUN_00306360(node->_parent, DAT_004e4690, 0);
    if (index == -1) {
        *out = 0;
        return;
    }
    text = 0;
    if (FUN_00306910(node->_parent, index, DAT_004e4678, &text, DAT_004e4660, 0) == 0) {
        *out = 0;
        return (int)releaseText(text);
    }
    *out = text;
    if (*out != 0) {
        ((int *)*out)[-1]++;
    }
    return (int)releaseText(text);
}
