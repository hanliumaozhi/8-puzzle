//  Created by han on 12-10-7.
//  Copyright (c) 2012年 han. All rights reserved.
//

#include "chrome.h"


//chrom::chrom(sinfo nset,sinfo goal,unsigned char Xset,unsigned char Yset):Xpost(Xset),Ypost(Yset){
//Goal = goal;
chrom::chrom(sinfo nset,int Xset,int Yset,sinfo goal):Xpost(Xset),Ypost(Yset){
    Goal = goal;
    arr = nset;
    time = 0;
    flag = true;
    val = cal();
    
}

chrom::chrom(const chrom& other,int Xsetf,int Ysetf,int no){
    time = other.time + 1;
    Xpost = other.Xpost + Xsetf;
    Ypost = other.Ypost + Ysetf;
    Goal=other.Goal;
    if (Xpost >-1 and Xpost < 3 and Ypost > -1 and Ypost < 3) {
        flag = true;
    }
    else{
        flag = false;
    }
    if (flag) {
        sinfo tem(other.arr,no);
        arr = tem;
        swap(arr.arr[Xpost][Ypost],arr.arr[other.Xpost][other.Ypost]);
        val = cal();
    }
    
}

int chrom::cal(){
    int ans = 0;
    ans += time;
    for (int i = 0; i != 3 ; i++) {
        for (int j = 0; j!= 3; j++) {
            if (arr.arr[i][j] != 0) {
                if (Goal.arr[i][j] != arr.arr[i][j]) {
                    ans++;
                }
            }
        }
    }
    for (int i = 0; i != 3 ; i++) {
        for (int j = 0; j!= 3; j++) {
            if ( arr.arr[i][j] != 0) {
                for (int k = 0; k != 3; k++) {
                    for (int l = 0; l != 3; l++) {
                        if (arr.arr[i][j] == Goal.arr[k][l]) {
                            ans += (abs(i-k) + abs(j-l));
                        }
                    }
                }
            }
        }
    }
    return ans;
}

void chrom::chaVal(int vv){
    val=vv;
}
sinfo chrom::resin(){
    return arr;
}

bool chrom::reFlag(){
    return flag;
}

int chrom::reTime(){
    return time;
}

bool chrom::iseq(){
    if (Goal == arr) {
        return true;
    }
    else{
        return false;
    }
}

void chrom::chaApre(int val){
    arr.pre=val;
}

void chrom::chaAflag(bool reflag){
    arr.flag=reFlag();
}

int chrom::getVal(){
    return val;
}

int chrom::repre(){
    return arr.pre;
}