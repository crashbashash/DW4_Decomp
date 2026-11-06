/* The receiver is the address of an igObjectRefMetaField slot (every caller
 * passes &beNDMWGameRam::_dBEnemy / _dBPcTech, plain int handles in
 * reflected.h); the function dereferences the slot, so there is no reflected
 * struct member to name. */
int FUN_00406ee0(int *p)
{
    return *p;
}
