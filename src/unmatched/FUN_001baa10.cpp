struct RecorderFrame { char _pad0[16]; long long _time; };
struct RecorderFramePool { int _pad0[2]; int _capacity; int _pad0c; RecorderFrame **_data; int _used; };
class TransformRecorderVisitor {
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
    virtual long long sample(int a);
};
class TransformRecorderTraversal {
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
    virtual int channel();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void begin(long long t);
    virtual void end();
};
struct RecorderTraversalView : TransformRecorderTraversal {
    char _pad4[48]; int _state; char _pad38[20]; RecorderFramePool *_frames;
};
extern "C" {
void FUN_00130f20();
void FUN_001dca40(RecorderFramePool *, void (*)());
void FUN_001b1030(int, RecorderFrame *);
void FUN_001b1100(int, RecorderFrame *);
int FUN_001e07a0(RecorderTraversalView *, TransformRecorderVisitor *);
}
extern "C" int FUN_001baa10(RecorderTraversalView *o, TransformRecorderVisitor *v) {
    int state;
    int r;
    RecorderFramePool *pool;
    int i;
    long long t;
    RecorderFrame *frame;
    pool = o->_frames;
    state = o->_state;
    if (!(pool->_used < pool->_capacity)) {
        FUN_001dca40(pool, FUN_00130f20);
    }
    i = pool->_used;
    pool->_used = i + 1;
    frame = pool->_data[i];
    t = v->sample(o->channel());
    o->begin(t);
    frame->_time = t;
    FUN_001b1030(state, frame);
    r = FUN_001e07a0(o, v);
    FUN_001b1100(state, frame);
    o->end();
    if (r == 2) {
        return 2;
    }
    return 0;
}
