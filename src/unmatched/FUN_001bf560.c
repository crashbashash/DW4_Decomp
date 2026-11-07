#pragma optimize_for_size off
typedef struct QSUShortList { int _pad0[4]; unsigned short *_data; } QSUShortList;
typedef struct QSView {
    int _pad0[2];
    QSUShortList *_compressedTranslationList;
    QSUShortList *_compressedQuaternionList;
    int _pad10;
    float _translationBase;
    float _translationRangeOverMaxUShort;
    float _quaternionBase;
    float _quaternionRangeOverMaxUShort;
} QSView;
void FUN_001bf560(QSView *o, int index, float *out) {
    unsigned short *p = o->_compressedQuaternionList->_data + index * 4;
    int i;
    for (i = 0; i < 4; i++) {
        *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
    }
}
