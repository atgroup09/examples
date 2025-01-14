# @page Тест: Bytearray
# @date 2023.08.08

import struct;

# 1.0
Arr1 = [0, 0, 128, 63, 0, 0];

Addr = 0;
Sz   = 4;

Val  = struct.unpack("f", bytearray(Arr1[Addr:Addr+Sz]));

print(Val);
# (1.0, )
