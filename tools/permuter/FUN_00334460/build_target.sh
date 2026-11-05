#!/bin/bash
# Build target.o from the RETAIL bytes of FUN_00334460 (0x334460), 76 bytes,
# transcribed symbolically — see the FUN_00130060 harness for why.
# GENERATED/checked against the retail words; target.o is never committed.
set -eu
cd "$(dirname "$0")"

cat > target.s <<'ASM'
	.set	mips3
	.set	noreorder
	.set	nomacro
	.set	noat
	.text
	.globl	FUN_00334460
FUN_00334460:
	addiu	$sp,$sp,-16
	lui	$at,%hi(DAT_00587628)
	sd	$ra,0($sp)
	lw	$v0,%lo(DAT_00587628)($at)
	beqz	$v0,.Lcall
	nop
	lw	$v0,36($v0)
	andi	$v0,$v0,0x4
	sltu	$v0,$zero,$v0
	bnez	$v0,.Lend
	nop
	nop
.Lcall:
	jal	FUN_003344f0
	nop
.Lend:
	lui	$at,%hi(DAT_00587628)
	ld	$ra,0($sp)
	lw	$v0,%lo(DAT_00587628)($at)
	jr	$ra
	addiu	$sp,$sp,16
ASM

mipsel-linux-gnu-as -mips3 -G0 -o target.o target.s

# GNU as pads every section to 16 bytes; shrink .text to the real 76 so the
# padding does not disassemble as extra instructions (see the 0x130060 harness).
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
        struct.pack_into("<I", d, o + 20, 76)
        print(f"  .text sh_size {old} -> 76")
open("target.o", "wb").write(d)
PYEOF

echo "built target.o: $(mipsel-linux-gnu-objdump -h target.o | awk '/\.text/{print "0x"$3}') bytes, $(mipsel-linux-gnu-readelf -rW target.o | grep -c R_MIPS) relocs"
