struct BitSlots { char pad[80]; unsigned int bits; };
int FUN_002e23b0(struct BitSlots *arg0, int arg1)
{
  if (arg1 < 0x10)
  {
    return (arg0->bits >> (arg1 * 2)) & 3;
  }
  return 0;
}
