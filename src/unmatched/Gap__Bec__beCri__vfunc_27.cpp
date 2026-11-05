#include "dw4/reflected.h"
struct CriSystemState { char p0[88]; int f88; };
extern "C" {
int FUN_00332cf0(...);
int FUN_0037caf0(...);
int FUN_003a6f70(...);
int FUN_003a70c0(...);
int FUN_003a7300(...);
int FUN_003a73b0(...);
int FUN_003a74b0(...);
int FUN_003a7890(...);
int FUN_003a79a0(...);
int ObjectList_AppendRetained(...);
int ObjectList_RemoveFirstRetained(...);
void Gap__Bec__beCri__vfunc_27(beCri *arg0);
}
void Gap__Bec__beCri__vfunc_27(beCri *arg0) {
    int sp9C, sp98, sp94, sp90, sp8C, sp88;
    int i;
    int j;
    int k;
    int v;
    beCriHandle *s2;
    beCriAudio *s1;
    beCriHandle *t;
    int r;
    beCriVolume *s0;
    FUN_00332cf0(1);
    if (arg0->_execDvdErr > 0) {
        if (((CriSystemState *)arg0->_system)->f88 == 0) {
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdBGM);
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdENV);
            i = 0;
            if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
                i = 0;
                do {
                    t = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[i];
                    if (t->_playID != 0) FUN_003a74b0((beCriAudio *)t->_audio, ((igObjectList *)arg0->_hdSEs));
                    i++;
                } while (i < ((igObjectList *)arg0->_hdSEs)->_count);
            }
            ObjectList_RemoveFirstRetained(&sp9C, ((igObjectList *)arg0->_hdSEs), arg0->_hdBGM, 0);
            ObjectList_RemoveFirstRetained(&sp98, ((igObjectList *)arg0->_hdSEs), arg0->_hdENV, 0);
            arg0->_execDvdErr = 0;
        }
    } else {
        if (((CriSystemState *)arg0->_system)->f88 > 0) {
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdBGM);
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdENV);
            j = 0;
            if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
                j = 0;
                do {
                    t = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[j];
                    if (t->_playID != 0) FUN_003a73b0((beCriAudio *)t->_audio, ((igObjectList *)arg0->_hdSEs));
                    j++;
                } while (j < ((igObjectList *)arg0->_hdSEs)->_count);
            }
            ObjectList_RemoveFirstRetained(&sp94, ((igObjectList *)arg0->_hdSEs), arg0->_hdBGM, 0);
            ObjectList_RemoveFirstRetained(&sp90, ((igObjectList *)arg0->_hdSEs), arg0->_hdENV, 0);
            arg0->_execDvdErr = 1;
            return;
        }
        ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdBGM);
        ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdENV);
        i = 0;
        if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
            k = 0;
            do {
                s2 = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[k];
                if (s2->_playID != 0) {
                    s1 = (beCriAudio *)s2->_audio;
                    s0 = (beCriVolume *)s2->_volume;
                    r = FUN_003a70c0(s1, ((igObjectList *)arg0->_hdSEs));
                    switch (r) {
                    case 1:
                        if (FUN_003a7300(s1) == 0) {
                            switch (s0->_isExec) {
                            case 3: {
                                if (s1->_audioType == 3) {
                                    v = FUN_003a79a0(s0, arg0->_baseVolume);
                                } else {
                                    v = FUN_003a7890(s0, arg0->_baseVolume);
                                }
                                FUN_003a6f70(s1, v);
                                if (s0->_end == 0.0f) {
                                    if (s1->_audioType == 3) {
                                        if (v < 13) FUN_0037caf0(arg0, s2);
                                    } else if (v < -209) {
                                        FUN_0037caf0(arg0, s2);
                                    }
                                }
                                break;
                            }
                            }
                        }
                        break;
                    case -1:
                    case 0:
                        FUN_0037caf0(arg0, s2);
                        break;
                    }
                }
                k++;
            } while (k < ((igObjectList *)arg0->_hdSEs)->_count);
        }
        ObjectList_RemoveFirstRetained(&sp8C, ((igObjectList *)arg0->_hdSEs), arg0->_hdBGM, 0);
        ObjectList_RemoveFirstRetained(&sp88, ((igObjectList *)arg0->_hdSEs), arg0->_hdENV, 0);
    }
}
