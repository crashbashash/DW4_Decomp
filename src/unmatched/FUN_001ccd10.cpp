#include "dw4/igobject_release.h"
struct IniObjectRef { int pad0; int _refCount; };
struct IniStringValue { char pad0[8]; char *text; };
struct IniEntry { char *name; IniStringValue *value; };
struct IniEntryList { char pad0[8]; int count; char pad1[4]; IniEntry **data; };
struct IniNodeList;
struct IniNode { int type; char pad0[4]; IniEntryList *entries; char pad1[4]; IniNodeList *children; };
struct IniNodeList { char pad0[8]; int count; char pad1[4]; IniNode **data; };
struct IniShaderFactoryView;
extern "C" {
int FUN_0030ba90(char *, void *);
void FUN_001cdbb0(IniObjectRef **, IniShaderFactoryView *, char *);
void igObject_Destroy(void *);
extern char *DAT_004c22f0[4];
extern int DAT_004e46e0[4];
void FUN_001ccd10(IniShaderFactoryView *self, IniNodeList *list) {
    int i;
    int j;
    if (list != 0) {
        for (i = 0; i < list->count; i++) {
            IniNode *node = list->data[i];
            switch (node->type) {
            case 0:
                FUN_001ccd10(self, node->children);
                break;
            case 1: {
                IniEntryList *entries = node->entries;
                for (j = 0; j < entries->count; j++) {
                    IniEntry *e = entries->data[j];
                    if (FUN_0030ba90(e->name, DAT_004e46e0) != 0) {
                        char *s = e->value->text;
                        IniObjectRef *ref;
                        s = (s == 0) ? DAT_004c22f0[0] : s;
                        FUN_001cdbb0(&ref, self, s);
                        IG_OBJECT_RELEASE(ref);
                    }
                }
                break;
            }
            }
        }
    }
}
}
