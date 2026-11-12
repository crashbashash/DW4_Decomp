void Gap__Attrs__igPixelPipelineModeAttr__vfunc_24(int arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_146(arg1, *(int *)((char *)(arg0) + 12));
}

void Gap__Attrs__igPixelPipelineModeAttr__vfunc_26(void *arg0, void **arg1) {
    *(int *)((char *)(arg0) + 12) = ((DW4VC_588_0 *)(arg1))->vX();
}

/* Stores a float at +0x1c of the receiver. That offset lies past the 20 bytes the reflected
 * igPrimLengthArray1_1 describes, so the store stays an offset write. */
void FUN_0013fb00(igPrimLengthArray1_1 *self, float value) {
    *(float *)((char *)self + 28) = value;
}

