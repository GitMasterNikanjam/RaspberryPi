**old kernel inf:**   
Linux lotus 6.1.21-v8+ #1642 SMP PREEMPT Mon Apr  3 17:24:16 BST 2023 aarch64 GNU/Linux    

**new kernel real time kernel inf:**       
Linux lotus 6.1.77-rt24-v8+ #1 SMP PREEMPT_RT Tue Feb 13 17:01:58 +0330 2024 aarch64 GNU/Linux   
DEPMOD  /home/farazcomm/rpi-kernel/rt-kernel/lib/modules/6.1.77-rt24-v8+    

test benchmark for old kernel: sudo cyclictest -t20 -p 80 -i 10000 -l 5000    
```
for old kernel:
T: 0 ( 1633) P:80 I:10000 C:   5000 Min:      9 Act:   11 Avg:   21 Max:     161
T: 1 ( 1634) P:80 I:10500 C:   4762 Min:      9 Act:   10 Avg:   20 Max:     185
T: 2 ( 1635) P:80 I:11000 C:   4545 Min:      9 Act:   11 Avg:   19 Max:     143
T: 3 ( 1636) P:80 I:11500 C:   4348 Min:      9 Act:    9 Avg:   20 Max:     148
T: 4 ( 1637) P:80 I:12000 C:   4166 Min:      9 Act:   12 Avg:   20 Max:     128
T: 5 ( 1638) P:80 I:12500 C:   4000 Min:      9 Act:   11 Avg:   21 Max:     143
T: 6 ( 1639) P:80 I:13000 C:   3846 Min:      9 Act:   14 Avg:   21 Max:     143
T: 7 ( 1640) P:80 I:13500 C:   3703 Min:      9 Act:   12 Avg:   21 Max:     155
T: 8 ( 1641) P:80 I:14000 C:   3571 Min:      9 Act:   15 Avg:   20 Max:     119
T: 9 ( 1642) P:80 I:14500 C:   3448 Min:      9 Act:   10 Avg:   21 Max:     112
T:10 ( 1643) P:80 I:15000 C:   3333 Min:      9 Act:   12 Avg:   20 Max:     108
T:11 ( 1644) P:80 I:15500 C:   3225 Min:      9 Act:   18 Avg:   21 Max:     148
T:12 ( 1645) P:80 I:16000 C:   3125 Min:     10 Act:   10 Avg:   21 Max:     116
T:13 ( 1646) P:80 I:16500 C:   3030 Min:      9 Act:   13 Avg:   21 Max:     136
T:14 ( 1647) P:80 I:17000 C:   2941 Min:     10 Act:   12 Avg:   22 Max:     124
T:15 ( 1648) P:80 I:17500 C:   2857 Min:      9 Act:   10 Avg:   22 Max:     135
T:16 ( 1649) P:80 I:18000 C:   2777 Min:      9 Act:   12 Avg:   20 Max:     154
T:17 ( 1650) P:80 I:18500 C:   2702 Min:     10 Act:   13 Avg:   22 Max:     158
T:18 ( 1651) P:80 I:19000 C:   2631 Min:      9 Act:   14 Avg:   21 Max:     152
T:19 ( 1652) P:80 I:19500 C:   2564 Min:     10 Act:   20 Avg:   22 Max:     123

for new kernel:
T: 0 ( 1191) P:80 I:10000 C:   5000 Min:      4 Act:    8 Avg:    9 Max:      81
T: 1 ( 1192) P:80 I:10500 C:   4762 Min:      4 Act:    6 Avg:   10 Max:      95
T: 2 ( 1193) P:80 I:11000 C:   4546 Min:      4 Act:   12 Avg:    9 Max:      76
T: 3 ( 1194) P:80 I:11500 C:   4348 Min:      4 Act:    6 Avg:    9 Max:      94
T: 4 ( 1195) P:80 I:12000 C:   4167 Min:      4 Act:   15 Avg:    9 Max:     127
T: 5 ( 1196) P:80 I:12500 C:   4000 Min:      4 Act:    7 Avg:    9 Max:      96
T: 6 ( 1197) P:80 I:13000 C:   3846 Min:      4 Act:    8 Avg:    8 Max:      57
T: 7 ( 1198) P:80 I:13500 C:   3704 Min:      4 Act:    9 Avg:    9 Max:      93
T: 8 ( 1199) P:80 I:14000 C:   3571 Min:      4 Act:    7 Avg:    9 Max:      81
T: 9 ( 1200) P:80 I:14500 C:   3448 Min:      4 Act:    7 Avg:    9 Max:      79
T:10 ( 1201) P:80 I:15000 C:   3333 Min:      4 Act:    7 Avg:   10 Max:      98
T:11 ( 1202) P:80 I:15500 C:   3226 Min:      4 Act:   39 Avg:    9 Max:      98
T:12 ( 1203) P:80 I:16000 C:   3125 Min:      4 Act:   13 Avg:   10 Max:      85
T:13 ( 1204) P:80 I:16500 C:   3030 Min:      4 Act:    6 Avg:    9 Max:      75
T:14 ( 1205) P:80 I:17000 C:   2941 Min:      4 Act:   10 Avg:    8 Max:      72
T:15 ( 1206) P:80 I:17500 C:   2857 Min:      4 Act:    8 Avg:   10 Max:     117
T:16 ( 1207) P:80 I:18000 C:   2778 Min:      4 Act:   13 Avg:    9 Max:      79
T:17 ( 1208) P:80 I:18500 C:   2703 Min:      4 Act:   12 Avg:    9 Max:      78
T:18 ( 1209) P:80 I:19000 C:   2631 Min:      4 Act:    8 Avg:   10 Max:      96
T:19 ( 1210) P:80 I:19500 C:   2564 Min:      5 Act:    8 Avg:    9 Max:     100
```