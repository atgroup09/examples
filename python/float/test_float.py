# @page Test: Processing the float-values

from lib.float import *;


Flo     = 25.5;
FloFrom = 0.0;

ByLst   = floatToBytes(Flo, FLOAT_ORDER_BE);
FloFrom = floatFromBytes(ByLst, FLOAT_ORDER_BE);
print("ByLst BE   : {0} {1}".format(ByLst, FloFrom));

WoLst   = floatToWords(Flo, FLOAT_ORDER_BE, FLOAT_ORDER_LE);
FloFrom = floatFromWords(WoLst, FLOAT_ORDER_BE, FLOAT_ORDER_LE);
print("WoLst BE LE: {0} {1}".format(WoLst, FloFrom));

WoLst   = floatToWords(Flo, FLOAT_ORDER_BE, FLOAT_ORDER_BE);
FloFrom = floatFromWords(WoLst, FLOAT_ORDER_BE, FLOAT_ORDER_BE);
print("WoLst BE BE: {0} {1}".format(WoLst, FloFrom));

print();

ByLst   = floatToBytes(Flo, FLOAT_ORDER_LE);
FloFrom = floatFromBytes(ByLst, FLOAT_ORDER_LE);
print("ByLst LE   : {0} {1}".format(ByLst, FloFrom));

WoLst   = floatToWords(Flo, FLOAT_ORDER_LE, FLOAT_ORDER_LE);
FloFrom = floatFromWords(WoLst, FLOAT_ORDER_LE, FLOAT_ORDER_LE);
print("WoLst LE LE: {0} {1}".format(WoLst, FloFrom));

WoLst   = floatToWords(Flo, FLOAT_ORDER_LE, FLOAT_ORDER_BE);
FloFrom = floatFromWords(WoLst, FLOAT_ORDER_LE, FLOAT_ORDER_BE);
print("WoLst LE BE: {0} {1}".format(WoLst, FloFrom));
