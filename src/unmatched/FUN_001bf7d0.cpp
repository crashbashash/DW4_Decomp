class QSSequenceSlots {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual long long keyTime(int i);
};
struct QSTimeList { int _pad0[2]; int _count; };
struct QSSequenceView : QSSequenceSlots {
    int _refCount; int _pad8[2]; QSTimeList *_compressedTimeList; float _pad14[4]; int _pad24; unsigned long long _animationDuration; int _playMode; int _lastTime;
};
extern "C" {
void FUN_001bfc70(QSSequenceView *, long long, int *, int *, float *, float *);
int FUN_001dd4b0(long long, unsigned long long, long long *);
}
extern "C" void FUN_001bf7d0(QSSequenceView *o, unsigned char *before, unsigned char *after, int *key0, int *key1, float *t0, float *t1, long long time) {
    long long rem;
    long long end;
    long long first;
    long long last;
    *before = 0;
    *after = 0;
    first = o->keyTime(0);
    last = o->keyTime(o->_compressedTimeList->_count - 1);
    end = first + (long long)o->_animationDuration;
    if (end < time) {
        switch (o->_playMode) {
        case 1: *after = 1; return;
        case 3: case 0: FUN_001dd4b0(time - first, o->_animationDuration, &rem); time = first + rem; if (o->_lastTime != 1 && time < o->keyTime(o->_lastTime - 1)) { o->_lastTime = 1; } break;
        case 2: { unsigned long long cycle = (unsigned long long)(unsigned int)FUN_001dd4b0(time - first, o->_animationDuration, &rem); if ((int)cycle & 1) { time = end - rem; } else { time = first + rem; } } break;
        default: *before = 1; return;
        }
    } else if (time < first) {
        *before = 1;
        return;
    }
    if (last < time) {
        if (o->_playMode == 3) {
            int d;
            d = (int)((time - last) >> 18);
            *key0 = o->_compressedTimeList->_count - 1;
            *key1 = 0;
            *t0 = (float)(unsigned int)d;
            d = (int)((end - last) >> 18);
            *t1 = (float)(unsigned int)d;
            return;
        }
        *after = 1;
        return;
    }
    FUN_001bfc70(o, time, key0, key1, t0, t1);
}
