namespace Gap {
namespace Sg {

void igTransformSequence1_5::removeScaleChannel() {
    _drivenChannels &= (unsigned char)~8;
    _scaleList = (igVec3fList *)0;
}

/* Address of key {index} in this sequence's scale track, or 0 when the sequence does not drive
 * that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation slots, 8
 * = scale); the key array starts 16 bytes into the list object and each key is 0xC bytes. */

igVec3f const *igTransformSequence1_5::getScale(int index) const {
    if (_drivenChannels & 8) {
        return (const igVec3f *)_scaleList->_data + index;
    }
    return 0;
}

void igTransformSequence1_5::removeTranslationChannel() {
    _drivenChannels &= (unsigned char)~1;
    _xlateList = (igVec3fList *)0;
}

long long igTransformSequence1_5::getDuration() {
    return _animationDuration;
}

long long igTransformSequence1_5::getTimeAsLong(int arg1) const {
    return _timeListLong->get(arg1);
}

/* Address of key {index} in this sequence's translation track, or 0 when the sequence does not
 * drive that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation
 * slots, 8 = scale); the key array starts 16 bytes into the list object and each key is 0xC bytes. */

igVec3f const *igTransformSequence1_5::getTranslation(int index) const {
    if (_drivenChannels & 1) {
        return (const igVec3f *)_xlateList->_data + index;
    }
    return 0;
}

int igTransformSequence1_5::getTranslationCount() const { if (_drivenChannels & 1) return _xlateList->_count; return 0; }

int igTransformSequence1_5::getScaleCount() const {
    return (_drivenChannels & 8) ? _scaleList->_count : 0;
}

/* IgTransformSequence1_5 slot 60, returns the reflected _drivenChannels byte (+72). */

unsigned char igTransformSequence1_5::getComponentChannels() const {
    return _drivenChannels;
}
}
}

int FUN_001abb50(S_1abb50 *arg0, A *arg1) {
    int n;
    Rc_1abb50 *r;
    n = arg1->vX();
    if (n == 0 || (arg0->f8 != 0) != 0) {
        return 0;
    }
    if (arg1 != 0) {
        arg1->f4 = arg1->f4 + 1;
    }
    r = arg0->f8;
    if (r != 0) {
        r->refs = r->refs - 1;
        if (((unsigned long long)(long long)r->refs & 0x7fffffULL) == 0) {
            igObject_Destroy((igObject *)r);
        }
    }
    arg0->f8 = (Rc_1abb50 *)arg1;
    arg0->f12 = ((Gap::Core::igObject *)arg0)->malloc(n * 4);
    return 1;
}

