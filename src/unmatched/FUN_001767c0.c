/* Run the shared slot-57 step, then store the value into the +392 word of the object (past the
 * reflected igPsx2UserUCodeExt fields). */
int FUN_0015cb50();

void FUN_001767c0(void *self, int value) {
    FUN_0015cb50();
    *(int *)((char *)self + 392) = value;
}
