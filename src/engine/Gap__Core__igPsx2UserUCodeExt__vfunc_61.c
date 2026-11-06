/* Run the shared slot-57 step, then store the value into the +392 word of the object (past the
 * reflected igPsx2UserUCodeExt fields). */
int Gap__Core__igPrimLengthArray1_1__vfunc_57();

void Gap__Core__igPsx2UserUCodeExt__vfunc_61(void *self, int value) {
    Gap__Core__igPrimLengthArray1_1__vfunc_57();
    *(int *)((char *)self + 392) = value;
}
