typedef struct TransformSequenceInterpolationView { char pad[44]; float _centerOfRotation[3]; int _timeListLong; int _interpolationDataTranslation; int _interpolationDataRotation; int _interpolationDataScale; } TransformSequenceInterpolationView;
extern float DAT_004e1058[3];
int Gap__Sg__igTransformSequence1_5__vfunc_29(TransformSequenceInterpolationView *o) {
    int r = o->_centerOfRotation[0] != DAT_004e1058[0];
    if (!r) { r = o->_centerOfRotation[1] != DAT_004e1058[1]; }
    if (!r) { r = o->_centerOfRotation[2] != DAT_004e1058[2]; }
    if (r) { return 0; }
if (o->_interpolationDataTranslation != 0 || o->_interpolationDataRotation != 0 || o->_interpolationDataScale != 0) { return 0; }
return 1;
}
