#include "dw4/reflected.h"
/* Check that the named entry (arg1) is available among the owner's two direct entries and its
 * list; arg0 owner with entries at +32/+36 and list at +40 */
extern "C" {
int strlen(int *);
int FUN_00332490(int);
int ObjectList_AppendRetained(int, int);
int ObjectList_RemoveFirstRetained(int *, int, int, int);
int igStrCmp(int *, int *);
extern int DAT_004e0858[4];
extern int DAT_0050e488[4];
unsigned char FUN_0037dd10(beCri *arg0, int *arg1);
}

unsigned char FUN_0037dd10(beCri *arg0, int *arg1) {
    unsigned char res1;
    int i1;
    unsigned char res2;
    int i2;
    beCriHandle *it;
    int *p;
    beCriHandle *it1;
    int h7c;
    int h78;

    if (igStrCmp(arg1, &DAT_0050e488[0]) == 0) {
        res1 = 1;
        ObjectList_AppendRetained(arg0->_hdSEs, arg0->_hdBGM);
        ObjectList_AppendRetained(arg0->_hdSEs, arg0->_hdENV);
        i1 = 0;
        if (0 < ((beCriHandleList *)arg0->_hdSEs)->_count) {
            do {
                it1 = ((beCriHandle **)((beCriHandleList *)arg0->_hdSEs)->_data)[i1];
                if (it1->_playID != 0 && ((beCriAudio *)it1->_audio)->_audioType == 1 && FUN_00332490(((beCriAudio *)it1->_audio)->_adxt) != 3) {
                    res1 = 0;
                    break;
                }
                i1 += 1;
            } while (i1 < ((beCriHandleList *)arg0->_hdSEs)->_count);
        }
        ObjectList_RemoveFirstRetained(&h7c, arg0->_hdSEs, arg0->_hdBGM, 0);
        ObjectList_RemoveFirstRetained(&h78, arg0->_hdSEs, arg0->_hdENV, 0);
        return res1;
    }
    res2 = 1;
    p = (int *)((beCriHandle *)arg0->_hdBGM)->_name;
    if ((p != 0 ? p : &DAT_004e0858[0]) != 0 && igStrCmp(p != 0 ? p : &DAT_004e0858[0], arg1) == 0) {
        if (FUN_00332490(((beCriAudio *)((beCriHandle *)arg0->_hdBGM)->_audio)->_adxt) != 3) res2 = 0;
    } else {
        p = (int *)((beCriHandle *)arg0->_hdENV)->_name;
        if ((p != 0 ? p : &DAT_004e0858[0]) != 0 && igStrCmp(p != 0 ? p : &DAT_004e0858[0], arg1) == 0) {
            if (FUN_00332490(((beCriAudio *)((beCriHandle *)arg0->_hdENV)->_audio)->_adxt) != 3) res2 = 0;
        } else {
            i2 = 0;
            if (0 < ((beCriHandleList *)arg0->_hdSEs)->_count) {
                do {
                    it = ((beCriHandle **)((beCriHandleList *)arg0->_hdSEs)->_data)[i2];
                    p = (int *)it->_name;
                    if ((p != 0 ? p : &DAT_004e0858[0]) != 0) {
                        if (strlen(p != 0 ? p : &DAT_004e0858[0]) != 0) {
                            if (igStrCmp(arg1, (int *)it->_name != 0 ? (int *)it->_name : &DAT_004e0858[0]) == 0 && it->_playID != 0 && FUN_00332490(((beCriAudio *)it->_audio)->_adxt) != 3) {
                                res2 = 0;
                                break;
                            }
                        }
                    }
                    i2 += 1;
                } while (i2 < ((beCriHandleList *)arg0->_hdSEs)->_count);
            }
        }
    }
    return res2;
}

