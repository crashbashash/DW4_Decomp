#!/usr/bin/env python3
"""igb_generators.py — resolve a pack's spawn/drop graph offline.

Uses the remap table (`scripts/igb_ids.py`) to walk:

    beGeneraterData                  the spawn row (enemy id, position, timer, modes)
      ._playerDataList  -> beGeneraterPlayerDataList
           -> beGeneraterPlayerData  (per-player settings)
                ._itemDataList / ._itemLastDataList -> beGeneraterItemDataList
                     -> beGeneraterItemData  (one drop category)
                          ._dataList -> beGeneraterItemDataOneList
                               -> beGeneraterItemDataOne  (category, _id, _rank, _rate)

and prints the result, or writes it as JSON.  Everything comes from the file: no
emulator and no live RAM.

  igb_generators.py NDMW.AFS --blob 0x21307000
  igb_generators.py NDMW.AFS --blob 0x21307000 --json /tmp/stag0102.json
"""
import argparse
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import igb_ids  # noqa: E402

ig = igb_ids.igb_inst


def build(file, blob, reflection):
    data = open(file, "rb").read()
    lo = int(blob, 0)
    size, where = ig.blob_extent(data, lo)
    b = data[lo:lo + (size or len(data) - lo)]
    dirs, s1, s2, _chains = igb_ids.sections(b, reflection)
    off, cnt, obj_of_id = igb_ids.find_table(b, s1, s2)

    lists = ig.list_records(s2)
    pool = max(r["end"] for r in s2)
    cur, listoff = pool, {}
    for dk, c, cls, i, _r in lists:
        listoff[i] = cur
        cur += c * ig.ITEM_SIZE.get(cls, 4)

    def fmap(r):
        return {k: v for k, v, _t in r["fields"]}

    def ref(v):
        return None if (v is None or v < 0 or v >= cnt) else obj_of_id[v]

    def ids(k):
        r = s2[k]
        n = next(v for kk, v, _t in r["fields"] if kk == "slot2")
        return [struct.unpack_from("<I", b, listoff[k] + 4 * j)[0] for j in range(n)]

    def one_rows(k):
        """Every beGeneraterItemDataOne reachable from a beGeneraterItemDataList."""
        out, seen = [], set()
        for item in ids(k):
            ik = ref(item)
            if ik is None or s2[ik]["class"] != "beGeneraterItemData":
                continue
            im = fmap(s2[ik])
            ol = ref(im.get("_dataList"))
            if ol is None:
                continue
            for row in ids(ol):
                ok = ref(row)
                if ok is None or s2[ok]["class"] != "beGeneraterItemDataOne":
                    continue
                if ok in seen:
                    continue
                seen.add(ok)
                f = fmap(s2[ok])
                out.append({"id": ok, "category": s2[ok]["name"],
                            "itemId": f.get("_id"), "rank": f.get("_rank"), "rate": f.get("_rate")})
        return out

    id_of_rec = {}
    for v, k in enumerate(obj_of_id):
        if k is not None:
            id_of_rec[k] = v
    gens = []
    for gi, r in enumerate(s2):
        if r["class"] != "beGeneraterData":
            continue
        f = fmap(r)
        drops = []
        pk = ref(f.get("_playerDataList"))
        if pk is not None and s2[pk]["class"] == "beGeneraterPlayerDataList":
            for pdv in sorted(set(ids(pk))):
                dk = ref(pdv)
                if dk is None or s2[dk]["class"] != "beGeneraterPlayerData":
                    continue
                dm = fmap(s2[dk])
                for key in ("_itemDataList", "_itemLastDataList"):
                    il = ref(dm.get(key))
                    if il is None:
                        continue
                    drops += one_rows(il)
        gens.append({
            "rec": gi,
            "name": r["name"], "enemyId": f.get("_geneEnemyId"),
            "pos": [round(x, 3) for x in f["_pos"]] if f.get("_pos") else None,
            "posIsGlobal": f.get("_genePosIsGlobal"), "startData": f.get("_startData"),
            "startMode": f.get("_startModeStr"), "fillMode": f.get("_fillModeStr"),
            "callLua": f.get("_callLua"), "drops": drops,
        })
    for g in gens:
        g["id"] = id_of_rec.get(g["rec"])
        del g["rec"]
    return {"blob": hex(lo), "where": where, "ids": cnt, "generators": gens}


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file")
    ap.add_argument("--blob", required=True)
    ap.add_argument("--json", dest="json_out")
    ap.add_argument("--reflection",
                    default=os.path.join(HERE, "..", "data", "reflection.json"))
    a = ap.parse_args()
    reflection = ig.load_reflection(a.reflection)
    res = build(a.file, a.blob, reflection)
    gens = res["generators"]
    distinct = set()
    for g in gens:
        for d in g["drops"]:
            distinct.add((d["category"], d["itemId"], d["rank"], d["rate"]))
    print("pack %s: %d generators, %d distinct drop rows, %d ids"
          % (res["blob"], len(gens), len(distinct), res["ids"]))
    for g in gens[:20]:
        print("  %-10s id=%-5s enemy=%-4s pos=%s mode=%s/%s drops=%d"
              % (g["name"], g["id"], g["enemyId"], g["pos"], g["startMode"], g["fillMode"],
                 len(g["drops"])))
        for d in g["drops"][:2]:
            print("        %-10s item=%-4s rank=%-3s rate=%s"
                  % (d["category"], d["itemId"], d["rank"], d["rate"]))
    if a.json_out:
        json.dump(res, open(a.json_out, "w"), indent=1)
        print("wrote", a.json_out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
