#!/usr/bin/env python3
"""Check GAMERAM incoming-s0 paths and the valid-level skill-band bound.

This is a constrained static proof over the retail instructions, not a general
R5900 emulator. Loads and call results are unknown. Calls preserve callee-save
registers under the engine ABI; branch delay slots execute before call clobbers.
Only paths before the first assignment to s0 participate in the incoming-s0
check. The independent skill bound applies to levels 1..999, not edited records
outside that range. No game or recovery source is written.
"""
import argparse
from collections import deque
import json
import os
from pathlib import Path
import re
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import automatch

BEGIN, END = 0x3FCA10, 0x406D98
REGS = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 "
        "s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp s8 ra").split()
INDEX = {name: i for i, name in enumerate(REGS)}
CALLER = "at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 t8 t9 ra".split()
BRANCH = {"b", "beq", "bne", "beqz", "bnez", "bltz", "bgez", "bgtz", "blez"}
NO_DEST = BRANCH | {"sb", "sw", "sd", "sq", "mtc1", "jal", "jalr", "jr", "div", "divu", "nop"}
ALLOWED = NO_DEST | {"addiu", "addu", "andi", "daddiu", "lbu", "ld", "lh", "li", "lq",
                     "lui", "lw", "mfhi", "mflo", "move", "mult", "mult1", "negu", "ori",
                     "sll", "slt", "slti", "sltiu", "sra", "srl", "subu"}


def signed(value, bits=32):
    value &= (1 << bits) - 1
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


class Flow:
    def __init__(self, image):
        self.image = image
        self.ins = automatch.disassemble(image, BEGIN, END)
        if len(self.ins) != (END - BEGIN) // 4:
            raise ValueError("incomplete instruction decode")
        for pc, (mnemonic, _operands, _word) in self.ins.items():
            if mnemonic not in ALLOWED:
                raise ValueError(f"unsupported instruction at {pc:#x}: {mnemonic}")
        for pc, word in ((BEGIN, 0x27BDFB50), (0x3FCA2C, 0x7FB30030),
                         (0x3FCA44, 0x7FB00000), (END - 8, 0x03E00008),
                         (END - 4, 0x27BD04B0)):
            if self.word(pc) != word:
                raise ValueError(f"reviewed callback boundary differs at {pc:#x}")
        for address, branch, low in ((0x3FCA60, 0x102028BE, 0x24639370),
                                     (0x3FDE90, 0x1020230A, 0x24639310)):
            expected = (0x2C410016, branch, 0, 0x3C030052, 0x00021080,
                        low, 0x00431021, 0x8C420000, 0x00400008, 0)
            if tuple(self.word(address + i * 4) for i in range(10)) != expected:
                raise ValueError(f"reviewed switch sequence differs at {address:#x}")
        self.switches = {0x3FCA80: [self.word(0x519370 + i * 4) for i in range(22)],
                         0x3FDEB0: [self.word(0x519310 + i * 4) for i in range(22)]}
        if any(not BEGIN <= target < END or target % 4
               for targets in self.switches.values() for target in targets):
            raise ValueError("switch target outside reviewed body")

    def word(self, address):
        return struct.unpack_from("<I", self.image, address - 0x100000 + 0x80)[0]

    def destination(self, pc):
        mnemonic, operands, _word = self.ins[pc]
        if mnemonic in NO_DEST:
            return None
        if mnemonic in {"mult", "mult1"} and operands.count(",") != 2:
            return None
        first = operands.split(",")[0].strip()
        return first if first in INDEX and first != "zero" else None

    def reads_s0(self, pc):
        if pc == 0x3FCA44:  # verified prologue snapshot of caller-owned s0
            return False
        operands = self.ins[pc][1]
        count = len(re.findall(r"\bs0\b", operands))
        return count > (1 if self.destination(pc) == "s0" else 0)

    def transfer(self, pc, state):
        mnemonic, operands, _word = self.ins[pc]
        destination = self.destination(pc)
        if destination is None:
            return state
        parts = operands.split(",")

        def value(part):
            if part in INDEX:
                return state[INDEX[part]]
            try:
                return int(part, 0)
            except ValueError:
                return None

        a = value(parts[1]) if len(parts) > 1 else None
        b = value(parts[2]) if len(parts) > 2 else None
        result = None
        if mnemonic == "move":
            result = a
        elif mnemonic == "li":
            result = signed(a)
        elif mnemonic == "lui":
            result = signed(a << 16)
        elif a is not None and b is not None:
            if mnemonic in {"addu", "addiu"}: result = signed(a + b)
            elif mnemonic == "daddiu": result = signed(a + b, 64)
            elif mnemonic == "subu": result = signed(a - b)
            elif mnemonic == "ori": result = a | (b & 65535)
            elif mnemonic == "andi": result = a & (b & 65535)
            elif mnemonic == "slt": result = int(a < b)
            elif mnemonic == "slti": result = int(a < signed(b, 16))
            elif mnemonic == "sltiu": result = int((a & ((1 << 64) - 1)) < (signed(b, 16) & ((1 << 64) - 1)))
            elif mnemonic == "sll": result = signed(a << b)
            elif mnemonic == "sra": result = signed(a) >> b
            elif mnemonic == "srl": result = (a & 0xFFFFFFFF) >> b
        values = list(state)
        values[INDEX[destination]] = result
        return tuple(values)

    def decision(self, pc, state):
        mnemonic, operands, _word = self.ins[pc]
        parts = operands.split(",")
        a = state[INDEX[parts[0]]] if parts[0] in INDEX else None
        b = state[INDEX[parts[1]]] if len(parts) > 1 and parts[1] in INDEX else None
        if mnemonic in {"beq", "bne"}:
            if parts[0] == parts[1]: equal = True
            elif a is None or b is None: return None
            else: equal = a == b
            return equal if mnemonic == "beq" else not equal
        if a is None: return None
        if mnemonic == "beqz": return a == 0
        if mnemonic == "bnez": return a != 0
        if mnemonic == "bltz": return a < 0
        if mnemonic == "bgez": return a >= 0
        if mnemonic == "bgtz": return a > 0
        if mnemonic == "blez": return a <= 0
        return None

    def successors(self, pc, state):
        mnemonic, operands, word = self.ins[pc]
        if mnemonic in {"jal", "jalr"}:
            return [(pc + 4, pc + 8, True)]
        if mnemonic == "jr":
            if operands == "ra": return [(pc + 4, END, False)]
            if pc not in self.switches: raise ValueError(f"unreviewed indirect jump at {pc:#x}")
            return [(pc + 4, target, False) for target in self.switches[pc]]
        if mnemonic in BRANCH:
            target = pc + 4 + signed(word & 65535, 16) * 4
            if not BEGIN <= target < END: raise ValueError("branch leaves reviewed body")
            decision = self.decision(pc, state)
            if mnemonic == "b" or decision is True: return [(pc + 4, target, False)]
            if decision is False: return [(pc + 4, pc + 8, False)]
            return [(pc + 4, target, False), (pc + 4, pc + 8, False)]
        return [(pc + 4, None, False)] if pc + 4 < END else []

    def incoming_s0_reads(self):
        initial = [None] * 32
        initial[0] = 0
        start = (BEGIN, None, False)
        incoming, queue, reads = {start: tuple(initial)}, deque([start]), set()
        while queue:
            node = queue.popleft()
            pc, pending, call = node
            state = incoming[node]
            if self.reads_s0(pc): reads.add(pc)
            if self.destination(pc) == "s0": continue
            output = self.transfer(pc, state)
            if pending is not None:
                if call:
                    output = list(output)
                    for register in CALLER: output[INDEX[register]] = None
                    output = tuple(output)
                children = [(pending, None, False)] if pending < END else []
            else:
                children = self.successors(pc, state)
            for child in children:
                old = incoming.get(child)
                merged = output if old is None else tuple(a if a == b else None for a, b in zip(old, output))
                if old != merged:
                    incoming[child] = merged
                    queue.append(child)
        return {"contextual_nodes": len(incoming), "reads": [f"0x{pc:08x}" for pc in sorted(reads)]}

    def level_cap(self, level):
        state = [None] * 32
        state[0], state[INDEX["s1"]] = 0, level
        pc, pending = 0x3FF268, None
        for _ in range(40):
            if pc == 0x3FF2CC and pending is None:
                return state[INDEX["s8"]]
            result = self.transfer(pc, tuple(state))
            if pending is not None:
                pc, pending = pending, None
            else:
                children = self.successors(pc, tuple(state))
                if len(children) != 1 or children[0][2]:
                    raise ValueError("level-cap fragment is not deterministic")
                pc, pending, _ = children[0]
            state = result
        raise ValueError("level-cap fragment exceeded its reviewed bound")


def check(image):
    flow = Flow(image)
    report = flow.incoming_s0_reads()
    thresholds = struct.unpack_from("<21h", image, 0x4CF590 - 0x100000 + 0x80)
    caps = [flow.level_cap(level) for level in range(1, 1000)]
    if any(cap is None for cap in caps) or sorted(thresholds) != list(thresholds):
        raise ValueError("skill cap/threshold proof incomplete")
    report.update(maximum_level_cap=max(caps), final_skill_threshold=thresholds[-1],
                  all_valid_level_caps_covered=max(caps) <= thresholds[-1])
    return report


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--elf", default=os.environ.get("DW4_ELF", ROOT / "orig/SLUS-20836/SLUS_208.36"))
    args = parser.parse_args()
    result = check(Path(args.elf).read_bytes())
    print(json.dumps(result, indent=2))
    raise SystemExit(bool(result["reads"]) or not result["all_valid_level_caps_covered"])
