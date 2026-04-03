# exec(open('./drgn_pager.py').read())
import pydoc

def REPR(x):
    pydoc.pager(repr(x))

def STR(x):
    pydoc.pager(str(x))
