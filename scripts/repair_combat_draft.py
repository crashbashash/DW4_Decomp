#!/usr/bin/env python3
"""Repair reviewed accesses, control flow and evaluation order in the GAMERAM draft.

This is a diagnostic source transform, never a matching-source bank command.
Instruction guards and exact source preimages reject drift at reviewed sites.
The complete callback must still pass the byte/table oracle independently.
"""
import argparse
from pathlib import Path
import re
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import units

FUNCTION = "Gap__Bec__beNDMWGameRam__vfunc_34"
# All eighteen narrow accesses, four cursor steps and one bare word store.
# Some widths are supplied by the context; guard those and the source repairs.
WORDS = {0x3fd844: 0x24630004, 0x3fd8ac: 0x24630004, 0x3fd95c: 0x24630004,
         0x3ff4ac: 0x24630002, 0x3fd7ec: 0x90c20010, 0x3fd93c: 0x90c20010,
         0x4031b8: 0x90420008, 0x3fce00: 0x9042000c, 0x3ff7b8: 0x9042000c,
         0x3fdbf4: 0x90420000, 0x3fdc38: 0x93908180, 0x3fdc48: 0xa0500000,
         0x3fdc74: 0x90420000, 0x3fdcb8: 0x93908184, 0x3fdcc8: 0xa0500000,
         0x3fdcf4: 0x90450000, 0x3fde24: 0xa2820048, 0x3ff488: 0x84620000,
         0x3ff4e8: 0x84710000, 0x403e6c: 0xa3a20110, 0x403f7c: 0xa3a00110,
         0x403f80: 0x93a20110, 0x404570: 0xac510000}
HIT_WORDS = {0x3fdf20: 0x10620003, 0x3fdf28: 0x10000007,
             0x3fdf34: 0x0c0e3c54, 0x3fdf38: 0x24050001,
             0x3fdf3c: 0x100022e0, 0x3fdf48: 0x0c101c0c}


# Receiver, cached numerator/denominator, ratio local, original getter site.
RNG_SAMPLES = [("temp_v0_81", "temp_s5_11", "temp_s3_28", "temp_s0_61", 0x403b68),
               ("temp_v0_85", "temp_s5_14", "temp_s3_30", "temp_s0_67", 0x4043c0),
               ("temp_v0_91", "temp_s5_16", "temp_s3_32", "temp_s0_74", 0x404bd8)]
RNG_WORDS = {}
for receiver, numerator, denominator, ratio, site in RNG_SAMPLES:
    RNG_WORDS.update({site: 0x0c101b94, site + 4: 0x24440030,
                      site + 8: 0x8c590000, site + 12: 0x8f390060,
                      site + 16: 0x0320f809, site + 20: 0x0040202d,
                      site + 24: 0x24042710, site + 32: 0x0044001b,
                      site + 44: 0x00003010 if site == 0x403b68 else 0x00004010,
                      site + (64 if site == 0x403b68 else 60):
                          0x00b3001a if site == 0x403b68 else 0x00f3001a,
                      site + (76 if site == 0x403b68 else 84):
                          0x00002812 if site == 0x403b68 else 0x00003812})


# Result local, record index, compared effect string, original string-query site.
ATTACK_EFFECTS = [("var_s1_17", "temp_hi_6", "DAT_00519230", 0x403a4c),
                ("var_s2_11", "temp_hi_7", "DAT_00519238", 0x403d64),
                ("var_s1_18", "temp_hi_8", "DAT_00519248", 0x4042a4),
                ("var_s1_21", "temp_hi_9", "DAT_00519250", 0x404abc)]
EFFECT_WORDS = {}
for result, index, compared, site in ATTACK_EFFECTS:
    EFFECT_WORDS.update({site: 0x0c0ea560, site + 4: 0x24c691f0,
                         site + 16: 0x24a50000 | (int(compared[-8:], 16) & 0xffff),
                         site + 20: 0x0c04a929,
                         site + 24: 0x0000902d if result == "var_s2_11" else 0x0000882d})


# Technique row is multiplied by four once; both bases then use byte addition.
TABLE_WORDS = {0x405a04: 0x0c0ff1bc, 0x405a08: 0x27a70428,
               0x405a0c: 0x8fa40428, 0x405a10: 0x3c03004d,
               0x405a14: 0x3c02004d, 0x405a18: 0x2463f538,
               0x405a1c: 0x2442f558, 0x405a20: 0x00042080,
               0x405a24: 0x00641821, 0x405a28: 0x00441021,
               0x405a2c: 0x8c520000, 0x405a30: 0x10000005,
               0x405a34: 0x8c730000}


def guard_words(image, words):
    for address, expected in words.items():
        offset = address - 0x100000 + 0x80
        if offset + 4 > len(image) or struct.unpack_from("<I", image, offset)[0] != expected:
            raise ValueError(f"original instruction guard differs at 0x{address:x}")


def restore_hit_switch(source, image):
    """Equivalent sparse-switch projection of the first hit category guard.

    It evaluates the same pure local division once and preserves each arm's
    statements. Original syntax is unknown; this reproduces the BEQ/B shape.
    """
    if [name for name, _, _ in units.definitions(source)] != [FUNCTION]:
        raise ValueError("expected only the complete GAMERAM source definition")
    guard_words(image, HIT_WORDS)
    marker = "            if ((temp_s0_9 / 10000) != 4) {"
    if source.count(marker) != 1:
        raise ValueError("expected one reviewed hit category guard")
    clean = units._clean(source)
    start = source.index(marker)
    opening = source.index("{", start)
    end = units._match_brace(clean, opening)
    between = clean[end:]
    match = re.match(r"\s*else\s*\{", between)
    if match is None:
        raise ValueError("expected the hit category else arm")
    else_opening = end + match.end() - 1
    else_end = units._match_brace(clean, else_opening)
    regular = source[opening + 1:end - 1]
    magic = source[else_opening + 1:else_end - 1]
    for arm in [regular, magic]:
        tokens = units._clean(arm)
        if re.search(r"\b(?:break|continue|case|default)\b|(?m:^\s*\w+:)", tokens):
            raise ValueError("hit category arm has unreviewed control transfers")
    replacement = ("            switch (temp_s0_9 / 10000) {\n"
                   "            case 4:" + magic + "                break;\n"
                   "            default:" + regular + "                break;\n"
                   "            }")
    return source[:start] + replacement + source[else_end:]


def restore_rng_samples(source, image):
    """Materialize three reviewed bounded rolls before the cached ratio math.

    Raw m2c embeds the virtual call in a later condition while lifting its
    reusable ratio out of that condition. Retail samples first. Require exact
    source preimages and reject extra intervening statements before moving it.
    This operates on cleaned C, before optional C++ virtual-call projection.
    """
    if [name for name, _, _ in units.definitions(source)] != [FUNCTION]:
        raise ValueError("expected only the complete GAMERAM source definition")
    guard_words(image, RNG_WORDS)
    for receiver, numerator, denominator, ratio, _site in RNG_SAMPLES:
        name = "recovery_roll_" + receiver
        if re.search(r"\b" + name + r"\b", source):
            raise ValueError("RNG sample is already materialized")
        declaration = "    void **" + receiver + ";"
        if source.count(declaration) != 1:
            raise ValueError("reviewed RNG receiver declaration differs")
        expression = ("((int (*)())*(int *)((char *)((*" + receiver
                      + ")) + 96))(" + receiver + ") % 10000U")
        if source.count(expression) != 1:
            raise ValueError("expected one reviewed bounded RNG expression")
        assignments = list(re.finditer(r"(?m)^( +)" + receiver + r" = \(void \*\*\)"
                                       r"\(FUN_00406e50\(arg0->_system \+ 0x30\)\);\n", source))
        if (len(assignments) != 1
                or len(re.findall(r"\b" + receiver + r"\b", units._clean(source))) != 4):
            raise ValueError("reviewed RNG receiver assignment or uses differ")
        assignment = assignments[0]
        call_at = source.index(expression)
        condition_at = source.rfind("\n", 0, call_at) + 1
        ratio_statement = (ratio + " = (((int) (" + numerator + " * 3) / (int) "
                           + denominator + ") + 0x64) - ((int) " + denominator + " / 40);")
        if (condition_at < assignment.end()
                or source[assignment.end():condition_at].strip() != ratio_statement
                or source[condition_at:call_at].strip() != "if ((int) ("):
            raise ValueError("RNG sample has an unreviewed intervening statement or condition")
        source = source[:call_at] + name + source[call_at + len(expression):]
        source = (source[:assignment.end()] + assignment[1] + name + " = " + expression + ";\n"
                  + source[assignment.end():])
        source = source.replace(declaration, declaration + "\n    unsigned int " + name + ";", 1)
    return source


def restore_attack_effect_order(source, image):
    """Keep four KOUKA lookups before their unaliased result initialization.

    m2c combines each lookup with the comparison and leaves zero initialization
    ahead of the lookup. Retail initializes in the comparison call's delay slot.
    This is a statement-order projection, not a claim of original C++ syntax.
    """
    definitions = units.definitions(source)
    if [name for name, _, _ in definitions] != [FUNCTION]:
        raise ValueError("expected only the complete GAMERAM source definition")
    guard_words(image, EFFECT_WORDS)
    name = "recovery_attack_effect"
    clean = units._clean(source)
    if re.search(r"\b" + name + r"\b", clean):
        raise ValueError("attack effect lookup is already materialized")
    for result, index, compared, _site in ATTACK_EFFECTS:
        declaration = "    int " + result + ";"
        if (source.count(declaration) != 1
                or re.search(r"&\s*" + result + r"\b", clean)):
            raise ValueError("reviewed attack result declaration or address escape differs")
        query = ("beDataBase_GetRecordString(FUN_00406ee0(&arg0->_dBEneatk), "
                 + index + ", &DAT_005191f0[0])")
        pattern = re.compile(r"(?m)^( +)" + result + r" = 0;\n\1if \(igStrCmp\("
                             + re.escape(query) + ", " + re.escape("&" + compared + "[0]")
                             + r"\) == 0\) \{")
        matches = list(pattern.finditer(source))
        if len(matches) != 1:
            raise ValueError("expected one reviewed attack effect/result preimage")
        match = matches[0]
        replacement = (match[1] + name + " = " + query + ";\n"
                       + match[1] + result + " = 0;\n"
                       + match[1] + "if (igStrCmp(" + name + ", &" + compared + "[0]) == 0) {")
        source = source[:match.start()] + replacement + source[match.end():]
    opening = units._clean(source).index("{", definitions[0][1])
    return source[:opening + 1] + "\n    const char *" + name + ";" + source[opening + 1:]


def repair(source, image):
    if [name for name, _, _ in units.definitions(source)] != [FUNCTION]:
        raise ValueError("expected only the complete GAMERAM source definition")
    guard_words(image, WORDS)
    guard_words(image, TABLE_WORDS)
    changes = []

    def once(before, after, label):
        nonlocal source
        if source.count(before) != 1:
            raise ValueError(f"expected one reviewed source preimage: {label}")
        source = source.replace(before, after)
        changes.append(label)

    for variable, ctype, step in [("var_v1", "void **", 4), ("var_v1_2", "void **", 4),
                                 ("var_v1_3", "void **", 4), ("var_v1_5", "short *", 2)]:
        if not re.search(r"(?m)^\s*" + re.escape(ctype + variable) + r"\s*;", source):
            raise ValueError(f"reviewed cursor type differs: {variable}")
        once(f"{variable} += {step};", f"{variable} += 1;", f"{variable} element step")
    for variable in ["temp_a2", "temp_a2_2"]:
        before = f"*(int *)((char *)({variable}) + 16)"
        after = f"*(unsigned char *)((char *)({variable}) + 16)"
        once(before, after, f"{variable} item equip byte")
    once("*(int *)((char *)(FUN_00406dd0(temp_v0_74, 1)) + 8)",
         "*(unsigned char *)((char *)(FUN_00406dd0(temp_v0_74, 1)) + 8)",
         "rank override byte")
    # The cleaner defaults bare pointer-expression dereferences to int even
    # when m2c's context gave the getter a byte-pointer result. Restore all
    # three loads and two stores, each with its own unique source preimage.
    load = "*(int *)(FUN_00406f00(temp_s2_8) + temp_s1_13)"
    store = "*(int *)(temp_s1_13 + FUN_00406f00(temp_s2_8))"
    for suffix, label in [(" != 0", "set predicate"), (" == 0", "clear predicate"),
                          (");", "append result")]:
        once(load + suffix, load.replace("int *", "unsigned char *") + suffix,
             "byte-buffer " + label)
    for value in ["temp_s0_7", "temp_s0_8"]:
        once(store + " = " + value + ";",
             store.replace("int *", "unsigned char *") + " = " + value + ";",
             "byte-buffer store " + value)
    once("*DataList_GetData_003e9090(temp_v0_86) = temp_s1_55;",
         "*(int *)DataList_GetData_003e9090(temp_v0_86) = temp_s1_55;",
         "data-word address store")
    if source.count("temp_a0_9 = sp428 * 4;") != 1:
        raise ValueError("expected one reviewed table byte-offset preimage")
    for table in ["DAT_004cf538", "DAT_004cf558"]:
        # The decompiler's [4] extent is a placeholder, not a recovered bound.
        once("extern int " + table + "[4];", "extern int " + table + "[];",
             table + " unknown extent")
        once("*(int *)(&" + table + "[0] + temp_a0_9)",
             "*(int *)((char *)&" + table + "[0] + temp_a0_9)",
             table + " byte address")
    return source, changes


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, help="cleaned m2c C, before prior manual repairs")
    parser.add_argument("--raw", action="store_true", help="clean raw m2c_one output first")
    parser.add_argument("--hit-switch", action="store_true", help="restore the reviewed hit guard shape")
    parser.add_argument("--rng-samples", action="store_true",
                        help="restore three reviewed bounded RNG sampling points")
    parser.add_argument("--attack-effects", action="store_true",
                        help="restore four reviewed attack effect lookup/init sequences")
    parser.add_argument("--elf", type=Path, default=ROOT / "orig/SLUS-20836/SLUS_208.36")
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    source = args.source.read_text()
    if args.raw:
        import m2c_batch
        if source.startswith("=== m2c"):
            source = source.split("\n", 1)[1]
        source = m2c_batch.clean(source, addr_mode="hybrid",
                                 bounds=m2c_batch.load_bounds(str(args.elf)))
    result, changes = repair(source, args.elf.read_bytes())
    if args.hit_switch:
        result = restore_hit_switch(result, args.elf.read_bytes())
        changes.append("hit category sparse-switch projection")
    if args.rng_samples:
        result = restore_rng_samples(result, args.elf.read_bytes())
        changes.extend("bounded RNG sample " + item[0] for item in RNG_SAMPLES)
    if args.attack_effects:
        result = restore_attack_effect_order(result, args.elf.read_bytes())
        changes.extend("attack effect lookup " + item[0] for item in ATTACK_EFFECTS)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(result)
    print(f"applied {len(changes)} reviewed draft changes; full callback remains unverified")


if __name__ == "__main__":
    main()
