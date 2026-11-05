"""Dump reviewed Ghidra function spans, including holes in their address sets.

Run with --no-analysis -postScript scripts/dump_function_extents.py
--addr 0x003f5350 --out data/function-extents.json. Addresses are repeatable.
The ordinary dump's size counts occupied addresses, not the contiguous span.
Only reviewed functions are opted in; split.py rejects overlap with a neighbour.
"""
import json


def main():
    args = list(getScriptArgs())
    addresses, output = [], None
    while args:
        flag = args.pop(0)
        if flag == "--addr":
            addresses.append(int(args.pop(0), 0))
        elif flag == "--out":
            output = args.pop(0)
        else:
            raise ValueError("unknown argument: " + flag)
    if not addresses or not output:
        raise ValueError("--addr and --out are required")
    rows = []
    space = currentProgram.getAddressFactory().getDefaultAddressSpace()
    manager = currentProgram.getFunctionManager()
    for va in sorted(set(addresses)):
        fn = manager.getFunctionAt(space.getAddress(va))
        if fn is None:
            raise ValueError("no function at %#x" % va)
        body = fn.getBody()
        if body.getMinAddress().getOffset() != va:
            raise ValueError("body starts before entry at %#x" % va)
        ranges = []
        iterator = body.getAddressRanges()
        while iterator.hasNext():
            span = iterator.next()
            ranges.append({"start": "0x%08x" % span.getMinAddress().getOffset(),
                           "end_exclusive": "0x%08x" % (span.getMaxAddress().getOffset() + 1)})
        rows.append({"address": "0x%08x" % va,
                     "end_exclusive": "0x%08x" % (body.getMaxAddress().getOffset() + 1),
                     "body_bytes": int(body.getNumAddresses()), "name": fn.getName(),
                     "body_ranges": ranges})
    with open(output, "w") as fh:
        json.dump(rows, fh, indent=2)
        fh.write("\n")
    print("dump_function_extents: %d reviewed spans -> %s" % (len(rows), output))


main()
