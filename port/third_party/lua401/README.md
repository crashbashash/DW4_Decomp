# Lua 4.0.1 for the DW4 host

Source: https://www.lua.org/ftp/lua-4.0.1.tar.gz (2002-07-04).
SHA256: `df746e149cf6939e90009d2e540eee918d585b4d1bc6d68b19316a050d484d2a`.
The copyright and permission notice is preserved in `include/lua.h` and referenced
by each source file. This is Lua's original permissive license, not a substituted
modern Lua license. Core sources and base/string/math libraries are included;
IO/OS/debug libraries and the command-line interpreter/compiler are not linked.

Alterations are marked inline:

- `src/llimits.h`: `Instruction` uses `uint32_t` on LP64 and LLP64 hosts.
- `src/lundump.c`: serialized string sizes read four bytes on every host;
  the chunk header requires the original four-byte size_t format.
- `src/ldo.c`, `include/lua.h`: expose `lua_loadbuffer` to load a closure without
  executing it. This uses the original protected parser and error codes.

Opcodes, jumps, signed-operand bias, number type and Lua truthiness are unchanged.
The host preflights binary lengths before entering the legacy undumper. This
runtime accepts trusted game bytecode; it is not an untrusted-code sandbox.
No game bytecode is included here.
