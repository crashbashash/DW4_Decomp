/* The link of one libkernl kernel patch (config/SLUS-20836/kernel-patches.tsv, tools/kpatch.py): its code closed by
 * a zero doubleword, then its data on the next 128-byte boundary, then its zeroed data, the shape of the SDK's
 * application link script. tools/kpatch.py places .text at the patch's run address and keeps .text and .data,
 * the bytes the owner file copies into the kernel. */
SECTIONS
{
    .text : { *(.text) QUAD(0) }
    .data ALIGN(128) : { *(.data) *(.rodata) }
    .bss : { *(.bss) *(COMMON) }
    kExecArg = .;
    /DISCARD/ : { *(.reginfo) *(.mdebug) *(.comment) *(.pdr) }
}
