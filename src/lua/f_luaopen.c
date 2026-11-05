/* 0x00252fc0 — f_luaopen. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

int lua_newtable();
int lua_setglobal();
int lua_ref();
int luaD_init();
int luaX_init();
int luaS_init();
int luaH_new();
int luaT_init();
int lua_pushcclosure();
extern int DAT_004ebe78[4];
int errormessage();
void f_luaopen(void *arg0, int *arg1)
{
  int var_s0;  /* one variable for the size: a second temporary for `*arg1` is kept in v0 instead of s0 by the unit compiler (3.0b52 -O4) */
  var_s0 = *arg1;
  if (var_s0 == 0)
  {
    var_s0 = 0x400;
  }
  else
  {
    var_s0 = var_s0 + 0x14;
  }
  *((int *) (((char *) arg0) + 68)) = luaH_new(arg0, 0xA);
  luaD_init(arg0, var_s0);
  luaS_init(arg0);
  luaX_init(arg0);
  luaT_init(arg0);
  lua_newtable(arg0);
  lua_ref(arg0, 1);
  lua_pushcclosure(arg0, &errormessage, 0);
  lua_setglobal(arg0, &DAT_004ebe78[0]);
}
