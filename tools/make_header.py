from typing import Sequence
import xml.etree.ElementTree as et
from xml.etree.ElementTree import Element


def find_or_fail(src: Element, expr: str):
    res = src.find(expr)
    assert res is not None
    return res


def gen_isr(src: Element):
    at = src.attrib
    doc = f"addr: { at['addr'] }, enable: { at.get('enable') }, pending: { at.get('pending') }, prio: { at.get('priority') }"
    return f"""// { doc }
#define { at['name'] }_IRQN { at['irq'] }
"""


def gen_bitfields(module: Element, reg: Element):
    res: list[str] = []
    for bf in reg.findall("bitfield"):
        try:
            bits = int(bf.attrib["bits"])
        except:
            continue
        res.append(f"#define { module.get('name') }_{ reg.get('name') }_{ bf.get('name') } (1U << { bits })")
    return res


# NOTE: assuming all regs are 8-bit
def gen_reg(sfr: Element):
    reg = sfr.findall("register")
    assert len(reg) == 1
    reg = reg[0]
    name = reg.get("name")
    desc = reg.get("description")
    return f"volatile uint8_t { name };  // { desc }"


def gen_ordered_regs(sfrs: Sequence[Element]):
    counter = 0
    last_addr = int(sfrs[0].attrib["address"], base=16)
    yield gen_reg(sfrs[0])
    for sfr in sfrs[1:]:
        addr = int(sfr.attrib["address"], base=16)
        gap = addr - last_addr - 1
        if gap:
            yield f"uint8_t _res{ counter }[{ gap }];"
            counter += 1
        yield gen_reg(sfr)
        last_addr = addr


def gen_module(module: Element):
    name = module.get("name")
    sfrs = module.findall("SFR")
    base_addr = sfrs[0].get("address")
    regs = gen_ordered_regs(sfrs)
    bitfields: list[str] = []
    for sfr in sfrs:
        for reg in sfr.findall("register"):
            bfs = gen_bitfields(module, reg)
            if bfs:
                bitfields.extend(["", *bfs])

    return f"""\
// { name }
typedef struct
{{
{ '\n'.join([f'    { reg }' for reg in regs]) }
}} { name }_t;

{ '\n'.join(bitfields) }

#define { name } (({ name }_t *){ base_addr })

"""


def gen_memory(src: Element):
    start = src.get("addr_start")
    end = src.get("addr_end")
    return f"""\
#define { src.tag }_ADDR_START { start }U
#define { src.tag }_ADDR_END { end }U
"""


def process(src: str, guard: str):
    doc = et.fromstring(src)

    mems = find_or_fail(doc, "memory").findall('*')
    isrs = find_or_fail(doc, "interrupt_table").findall("interrupt[@irq!='']")
    modules = find_or_fail(doc, "special_function_registers").findall("module")

    return f"""\
#ifndef { guard }
#define { guard }

#include <stdint.h>

// Memory regions

{ '\n'.join([gen_memory(mem) for mem in mems])}

// Interrupts

{ '\n'.join([gen_isr(isr) for isr in isrs])}

// Registers

{ '\n'.join([gen_module(m) for m in modules])}

#endif
"""


if __name__ == "__main__":
    with open("../vendor/stm8s003f3.xml", "r") as f:
        res = process(f.read(), "STM8S003F3_H")
    with open("../firmware/stm8s003f3.h", "w") as f:
        f.write(res)

# print(modules)
