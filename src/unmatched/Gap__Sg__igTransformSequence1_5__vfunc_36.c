typedef struct TransformSequenceChannelView { char pad[8]; int _xlateList; int _quatList; int _scaleList; char pad2[36]; int _timeListLong; char pad3[12]; unsigned char _drivenChannels; } TransformSequenceChannelView;
void List_RemoveAt(int list, int index, int size);
void Gap__Sg__igTransformSequence1_5__vfunc_36(TransformSequenceChannelView *o, int index) {
    List_RemoveAt(o->_timeListLong, index, 8);
    if (o->_drivenChannels & 1) { List_RemoveAt(o->_xlateList, index, 12); }
    if ((o->_drivenChannels & 2) || (o->_drivenChannels & 4)) { List_RemoveAt(o->_quatList, index, 16); }
    if (o->_drivenChannels & 8) { List_RemoveAt(o->_scaleList, index, 12); }
}
