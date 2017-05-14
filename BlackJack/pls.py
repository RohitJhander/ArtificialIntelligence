# -*- coding: utf-8 -*-
"""
Created on Wed Oct 28 02:49:06 2015

@author: Deepak Saini
"""

from __future__ import print_function
from pprint import *
import sys
cards=["A","2","3","4","5","6","7","8","9","10"]

def add(l1,l2):
    return [l1[i]+l2[i] for i in range(min(len(l1),len(l2)))]
def gentable(pface):
    pnonface=1-pface
    hard={j:[0 for i in range(6)] for j in range(1,23)}
    soft={j:[0 for i in range(6)] for j in range(12,22)}
    
    for k,v in soft.items():
        if k>=17 and k<=21:
            v[k-17]=1
    for k,v in hard.items():
        if k>=17 and k<=22:
            v[k-17]=1
    i=16
    while i>=11:
        for k in range(1,11):
            if k==10:
                a=i+k
                if a>=22:
                    hard[i]=add(hard[i],[pface*x for x in hard[22]])
                else:
                    hard[i]=add(hard[i],[pface*x for x in hard[a]])
            else:
                a=i+k
                if a>=22:
                    hard[i]=add(hard[i],[(pnonface/9)*x for x in hard[22]])
                else:
                    hard[i]=add(hard[i],[(pnonface/9)*x for x in hard[a]])
        i-=1
    j=16
    while j>=12:
        for k in range(1,11):
            if k==10:
                a=j+k
                if a>21:
                    soft[j]=add(soft[j],[pface*x for x in hard[a-10]])
                elif a<=21:
                    soft[j]=add(soft[j],[pface*x for x in soft[a]])
            else:
                a=j+k
                if a>21:
                    soft[j]=add(soft[j],[(pnonface/9)*x for x in hard[a-10]])
                elif a<=21:
                    soft[j]=add(soft[j],[(pnonface/9)*x for x in soft[a]])
        j-=1
    t=10
    while t>=1:
        for k in range(1,11):
            if k==10:
                a=t+k
                if a>21:
                    hard[t]=add(hard[t],[pface*x for x in hard[22]])
                else:
                    hard[t]=add(hard[t],[pface*x for x in hard[a]])
            elif k==1:
                hard[t]=add(hard[t],[(pnonface/9)*x for x in soft[t+11]])
            elif k>=2 and k<=9:
                a=t+k
                if a>21:
                    hard[t]=add(hard[t],[(pnonface/9)*x for x in hard[22]])
                else:
                    hard[t]=add(hard[t],[(pnonface/9)*x for x in hard[a]])
        t-=1
    fout1=open("soft.txt","w")
    fout2=open("hard.txt","w")
    fout3=open("ace.txt","w")
    l1=sorted(hard.keys())
    for k in l1:
        print(" ".join(map(str,hard[k])),file=fout2)
        print(k,sum(hard[k]))
    print("soft")
    l2=sorted(soft.keys())
    for k in l2:
        print(" ".join(map(str,soft[k])),file=fout1)
        print(k,sum(soft[k]))
    a=[0 for i in range(6)]
    pprint(soft)
    for i in range(1,11):
        if i==10:
            a=add(a,[pface*x for x in soft[11+i]])
        else:
            a=add(a,[(pnonface/9)*x for x in soft[11+i]])
    print(" ".join(map(str,a)),file=fout3)
    
    fout1.close()
    fout2.close()
    fout3.close()
    pprint(hard)
    pprint(soft)
    print(sum(a))
 

gentable(float(sys.argv[1]))   
