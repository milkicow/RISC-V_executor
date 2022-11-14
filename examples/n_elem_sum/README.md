# sum of first n elements
There you can see n_elem_sum.c file that sum first n elements (default n = 10 you can change n in .c) beginning with zero elem

In the end of file "logfile.txt" you can see this sum:
```
instruction SW : 
 rd_ = 15 rs1_ = 8 rs2_ = 15
 imm_ = 4294967272
*--------------------------------------------------* 
 pc = 108 next_pc = 112
...
REG_08 = 589824
REG_15 = 45
...
*--------------------------------------------------* 
```
that will save in memory REG_15 = 45 this is desired value
```
sum = (0+9)/2 * 10 = 45
```
