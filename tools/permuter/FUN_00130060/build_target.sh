#!/bin/bash
# Build target.o from the RETAIL bytes, transcribed symbolically.
#
# Why symbolic and not a raw byte copy: decomp-permuter compares the disassembly
# TEXT of target.o against the compiled candidate, and its MIPS backend normalises
# relocations by symbol name (src/objdump.py: process_mips_reloc). A raw byte copy
# would show literal immediates (`lui at,0x56`) while the candidate shows a
# resolved reloc, so the two would never compare equal. Transcribing with %hi/%lo
# against the same symbols the candidate uses makes both sides render alike.
#
# The instructions below are FUN_00130060 at 0x130060, 72 bytes, copied from
# `mipsel-linux-gnu-objdump -d` on the retail ELF. target.o is GENERATED and must
# never be committed (it is a copy of game code, and the repo bans binary extracts;
# see AGENTS.md rule 1).
set -eu
cd "$(dirname "$0")"

cat > target.s <<'ASM'
	# DAT_0055ebc0 is deliberately left UNDEFINED: referencing it via %hi/%lo makes
	# `as` emit R_MIPS_HI16/R_MIPS_LO16 against the symbol, which is how MWCC renders
	# the candidate -- so the permuter's relocation normalisation sees the same thing
	# on both sides. Pinning it to a constant instead resolves the pair at assembly
	# time and the target would show `lui at,0x56` where the candidate shows a reloc.
	.set	mips3
	.set	noreorder
	.set	nomacro
	.set	noat
	.text
	.globl	FUN_00130060
FUN_00130060:
	addiu	$sp,$sp,-16
	lui	$at,%hi(DAT_0055ebc0)
	sd	$ra,0($sp)
	lw	$v0,%lo(DAT_0055ebc0)($at)
	beqz	$v0,.Lcall
	nop
	lw	$v0,36($v0)
	andi	$v0,$v0,0x4
	sltu	$v0,$zero,$v0
	bnez	$v0,.Lend
	nop
.Lcall:
	jal	FUN_001301c0
	nop
.Lend:
	lui	$at,%hi(DAT_0055ebc0)
	ld	$ra,0($sp)
	lw	$v0,%lo(DAT_0055ebc0)($at)
	jr	$ra
	addiu	$sp,$sp,16
ASM

# Two traps in this MIPS `as`, both hit while writing this:
#  * registers must be $-prefixed -- bare `sp`/`ra` parse as symbols and every line
#    fails with "invalid operands";
#  * `.set noreorder` is REQUIRED -- in the default reorder mode `as` inserts filler
#    nops for load hazards and the target comes out 96 bytes instead of 72, which
#    silently makes the comparison meaningless.
mipsel-linux-gnu-as -mips3 -G0 -o target.o target.s

# GNU as pads EVERY section up to 16 bytes, so the 72-byte function lands in an
# 80-byte .text and the padding disassembles as extra instructions -- the permuter
# disassembles the whole object (no symbol filter), so that padding would make a
# perfect score unreachable. Shrinking sh_size is safe: the relocations all sit
# below 72 bytes and the pad becomes unreferenced slack.
python3 - <<'PYEOF'
import struct
d = bytearray(open("target.o", "rb").read())
shoff, = struct.unpack_from("<I", d, 0x20)
entsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 0x2e)
strtab = shoff + shstrndx * entsize
strbase, = struct.unpack_from("<I", d, strtab + 16)
for i in range(shnum):
    o = shoff + i * entsize
    nameoff, = struct.unpack_from("<I", d, o)
    end = d.find(b"\0", strbase + nameoff)
    if d[strbase + nameoff:end].decode() == ".text":
        old, = struct.unpack_from("<I", d, o + 20)
        struct.pack_into("<I", d, o + 20, 72)
        print(f"  .text sh_size {old} -> 72")
open("target.o", "wb").write(d)
PYEOF

echo "built target.o: $(mipsel-linux-gnu-objdump -h target.o | awk '/\.text/{print "0x"$3}') bytes, $(mipsel-linux-gnu-readelf -rW target.o | grep -c R_MIPS) relocs"
