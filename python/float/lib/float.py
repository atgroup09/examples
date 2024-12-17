# @page Processing the float-values

import struct;


# @def Order type
# Big-Endian
FLOAT_ORDER_BE = 0;
# Little-Endian
FLOAT_ORDER_LE = 1;


# @func Split Float to list of bytes
# @param  FloIn   - float-value (32bit) (0.0 by default)
# @param  ByOrdIn - order of bytes
# #arg    = FLOAT_ORDER_BE
# #arg    = FLOAT_ORDER_LE (by default)
# @return List of bytes (8bit, 8bit, 8bit, 8bit)
def floatToBytes(FloIn=0.0, ByOrdIn=FLOAT_ORDER_LE):
    if(ByOrdIn==FLOAT_ORDER_LE):
        return (list(struct.pack("<f", FloIn)));
    else:
        return (list(struct.pack(">f", FloIn)));

# @func Split Float to list of words
# @param  FloIn   - float-value (32bit) (0.0 by default)
# @param  ByOrdIn - order of bytes
# #arg    = FLOAT_ORDER_BE
# #arg    = FLOAT_ORDER_LE (by default)
# @param  WoOrdIn - order of words
# #arg    = FLOAT_ORDER_BE
# #arg    = FLOAT_ORDER_LE (by default)
# @return List of words (16bit, 16bit)
def floatToWords(FloIn=0.0, ByOrdIn=FLOAT_ORDER_LE, WoOrdIn=FLOAT_ORDER_LE):
    ByLst = floatToBytes(FloIn, ByOrdIn);
    WoObj = struct.unpack("HH", bytearray(ByLst));
    if(WoOrdIn==FLOAT_ORDER_LE):
        return ([WoObj[0], WoObj[1]]);
    else:
        return ([WoObj[1], WoObj[0]]);

# @func Merge List of bytes to Float
# @param  ByLstIn - list of bytes (8bit, 8bit, 8bit, 8bit)
# @param  ByOrdIn - order of bytes
# #arg    = FLOAT_ORDER_BE
# #arg    = FLOAT_ORDER_LE (by default)
# @return Float (32bit) (0.0 by default)
def floatFromBytes(ByLstIn=None, ByOrdIn=FLOAT_ORDER_LE):
    if(ByLstIn==None):
        return (0.0);
    if(ByOrdIn==FLOAT_ORDER_LE):
        FloObj = struct.unpack("<f", bytearray(ByLstIn));
    else:
        FloObj = struct.unpack(">f", bytearray(ByLstIn));
    return (FloObj[0]);

# @func Merge List of words to Float
# @param  WoLstIn - list of words (16bit, 16bit)
# @param  ByOrdIn - order of bytes
# #arg    = FLOAT_ORDER_BE
# #arg    = FLOAT_ORDER_LE (by default)
# @param  WoOrdIn - order of words
# #arg    = FLOAT_ORDER_BE
# #arg    = FLOAT_ORDER_LE (by default)
# @return Float (32bit) (0.0 by default)
def floatFromWords(WoLstIn=None, ByOrdIn=FLOAT_ORDER_LE, WoOrdIn=FLOAT_ORDER_LE):
    if(WoLstIn==None):
        return (0.0);
    if(WoOrdIn==FLOAT_ORDER_LE):
        ByLst = (list(struct.pack("H", WoLstIn[0])) + list(struct.pack("H", WoLstIn[1])));
    else:
        ByLst = (list(struct.pack("H", WoLstIn[1])) + list(struct.pack("H", WoLstIn[0])));
    return (floatFromBytes(ByLst, ByOrdIn));


# Test
'''
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
'''
