### a2

seed 0

page directory content: 83 fe e0 da 7f d4 7f eb be 9e d5 ad e4 ac 90 d6 92 d8 c1 f8 9f e1 ed e9 a1 e8 c7 c2 a9 d1 db ff
pde size = 1 byte
page size = 32 bytes

---

0x611c => 0b11000 01000 11100
pdi 0b11000 => 24
pti 0b01000 => 8
offset 0b11100 => 28
pde 0xa1 => 0b1 0100001
pde.valid = 1
pde.fn = 0b0100001 = 0x21 => 33
page 33: 7f 7f 7f 7f 7f 7f 7f 7f b5 7f 9d 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f f6 b1 7f 7f 7f 7f
                                 |
                                pti 8
pte 0xb5 => 0b1 0110101
pte.valid = 1
pte.pfn = 0x35 => 53
page 53: 0f 0c 18 09 0e 12 1c 0f 08 17 13 07 1c 1e 19 1b 09 16 1b 15 0e 03 0d 12 1c 1d 0e 1a 08 18 11 00
                                                                                             |
                                                                                          offset 28
---

0x3da8 => 0b01111 01101 01000
pdi 0b01111 => 15
pti 0b01101 => 13
offset 0b01000 => 8
pde 0xd6 => 0b1 1010110
pde.valid = 1
pde.fn = 0b1010110 = 0x56 => 86
page 86: 7f 7f 7f 7f 7f 7f 7f c5 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f ca 7f 7f ee 7f 7f 7f 7f 7f 7f 7f 7f
                                                |
                                              pti 13
pte 0x7f => 0b0 1111111
pte.valid = 0
=> fault
---

0x17f5 => 0b00101 11111 10101
pdi 0b00101 => 5
pti 0b11111 => 31
offset 0b10101 => 21
pde 0xd4 => 0b1 1010100
pde.valid = 1
pde.fn = 0b1010100 = 0x54 => 84
page 84: 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 94 7f 7f 7f 7f 7f ce
                                                                                                      |
                                                                                                    pti 31
pte 0xce => 0b1 1001110
pte.valid = 1
pte.fn = 0b1001110 = 0x4e => 78
page 78: 0e 02 17 1b 1c 1a 1b 1c 10 0c 15 08 19 1a 1b 12 1d 11 0d 14 1e 1c 18 02 12 0f 13 1a 07 16 03 06
                                                                         |
                                                                      offset 21
