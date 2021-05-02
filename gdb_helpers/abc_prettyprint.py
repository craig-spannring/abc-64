#!/usr/bin/env python3

import sys
import os
import traceback

from gdb.printing import PrettyPrinter, register_pretty_printer
import gdb

_lf='\n'

# key-
# value-  function that returns an object with an __init__() and to_string()
_printers = {}


# Decorator to register pretty printer functions. 
def prettyprint(typename):
    global _printers
    def decorator(func):
        class inner:
            def __init__(self, val): self.val = val;
            def to_string(self): return str(func(self.val))
        _printers[typename] = inner
        return func
    return decorator


@prettyprint("struct value_ *")
def print_struct_value__ptr(v):
    tmp = int(v.cast(gdb.lookup_type('long')))
    if (tmp & 0x01)==0x01:
        result = f"0x{tmp:x} {{i={tmp//2}}}"
    else:
        result = f"0x{tmp:x}  " + str(v.dereference())
    return result


def pp_dispatch(value):
    "Pick a pretty-printer for 'value'."
    global _printers
    
    raw_type        = value.type
    basic_type      = gdb.types.get_basic_type(value.type)
    basic_type_tag  = basic_type.tag
    stripped_type   = raw_type.strip_typedefs()
    unqualified_type = stripped_type.unqualified()
    
    typename = str(value.type.strip_typedefs().unqualified())

    return _printers[typename](value) if typename in _printers else None

gdb.pretty_printers.append(pp_dispatch)

