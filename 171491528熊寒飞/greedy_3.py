#coding:utf-8
from __future__ import division
input_box = input('箱数:')
input_h = input('最大承受重量:')
list_a = []
list_b = []
for i in range(1,int(input_box)+1):
    input_Tvalue = input('第'+str(i)+'箱的总价值:')
    input_Theav = input('第'+str(i)+'箱的重量:')
    avg = round(int(input_Tvalue)/int(input_Theav),1)#每一箱单位重量的价值
    list_a.append(avg)#添加到列表，用于比较
    list_b.append([int(input_Theav),avg,0])
list_a.sort(reverse=True) # 降序排序
sum =[0,0]# 用于存放取走的总重量，第一个参数是取走的重量，第二个判断是否超出的备份信息
num =0
full = 0
for i in range(len(list_a)):
    for k in range(len(list_b)):
        if full == 0:#是否超出最大承受量，未超出为0
            if (list_a[i] == list_b[k][1]) and (list_b[k][2]==0):
                sum[1] = sum[0]#备份
                sum[0] = sum[0] + list_b[k][0]#取走的重量
                v = list_b[k][0]#取走的重量
                if sum[0] > int(input_h):#如果取走的重量超出最大承重量
                    full = 1#超出为1
                    t= list_b[k][0]
                    while True:#依次减去1单位的重量
                        z = sum[1] + t#使用备份进行判断
                        if z <= int(input_h):
                            break
                        t = t-1
                    v=t#等于最大承受量时，价值较大的一件物品应取走的数量
                    sum[0]=sum[1]
                    sum[0] = sum[0] + t
                num = list_a[i]*v + num
                list_b[k][2] = 1
print ('能带走的货物的最大价值为:',num)