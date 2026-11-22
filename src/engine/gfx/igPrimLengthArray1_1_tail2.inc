namespace Gap {
namespace Gfx {

unsigned int igPrimLengthArray1_1::configure(unsigned int num, int dataSize, igVisualContext *context)
{
    unsigned int size;

    _dataSize = dataSize;
    _numStrips = num;
    size = _numStrips * 4;
    if (size != 0) {
        _lengthData = (unsigned char *)realloc(_lengthData, size);
    } else {
        if (_lengthData != 0) {
            free(_lengthData);
        }
        _lengthData = 0;
    }
    return size;
}

/* Stores the length `length` of primitive strip `stripIndex` in the per-strip length table
 * (_lengthData is an int array, _numStrips entries). */

void igPrimLengthArray1_1::setPrimLength(unsigned int stripNumber, unsigned int value)
{
    ((unsigned int *)_lengthData)[stripNumber] = value;
}

/* Returns the length of primitive strip `stripIndex` from the per-strip length table (_lengthData
 * is an int array, _numStrips entries); the getter paired with the setter in vfunc_26. */

unsigned int igPrimLengthArray1_1::getPrimLength(unsigned int stripNumber) const
{
    return ((unsigned int *)_lengthData)[stripNumber];
}

unsigned int *igPrimLengthArray1_1::getEditablePrimLength(unsigned int editFlags, unsigned int startLength, unsigned int num)
{
    return (unsigned int *)_lengthData + startLength;
}

void igPrimLengthArray1_1::commitPrimLengthEdits(unsigned int *lengths, unsigned int commitFlags, unsigned int startLength, unsigned int num)
{

}
}
}

void *FUN_00167310(png_structp png, int size) {
    return ((Gap::Core::igObject *)DAT_00560840)->malloc(size);
}

void FUN_00167320(png_structp png, void *storage) {
    ((Gap::Core::igObject *)DAT_00560840)->free(storage);
}

void FUN_00167330(png_structp png, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(png_get_io_ptr(png));
    ((DW4VC_108_3 *)(temp_v0))->vX((int)(arg1), (int)(1), (int)(arg2));
}

void FUN_00167380(void) {

}

void FUN_00167390(void) {

}

