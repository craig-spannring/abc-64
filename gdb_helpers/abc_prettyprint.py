#!/usr/bin/env python3

import sys
import os
from gdb.printing import PrettyPrinter, register_pretty_printer
import gdb
    
class ValuePrettyPrinter(object):
    def __init__(self, val):
        self.val = val

    def to_string(self):
        lf='\n'
        #print(self.val.keys())
        return (f'{{ {lf}'
                f'  type={self.val["type"]} {lf}'
                f'  refcnt={self.val["refcnt"]} {lf}'
                f'  len={self.val["len"]} {lf}'
                f'  cts={self.val["cts"]} {lf}'
                f'}}')
        # return '{\n' + f'  e = {self.val["e"]}\n  x = {self.val["x"]}' + '\n}'


class CustomPrettyPrinterLocator(PrettyPrinter):
    """Given a gdb.Value, search for a custom pretty printer"""

    def __init__(self):
        super(CustomPrettyPrinterLocator, self).__init__(
            "my_pretty_printers", []
        )

    def __call__(self, val):
        """Return the custom formatter if the type can be handled"""

        typename = gdb.types.get_basic_type(val.type).tag
        if typename is None:
            typename = val.type.name

        if typename == "value_":
            return ValuePrettyPrinter(val)
        return 


register_pretty_printer(None, CustomPrettyPrinterLocator(), replace=True)

