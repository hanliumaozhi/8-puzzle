//  Created by han on 12-10-7.
//  Copyright (c) 2012年 han. All rights reserved.
//

#ifndef __neA___chrome__
#define __neA___chrome__

#include <cmath>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

struct sinfo{
    int arr[3][3];
    int pre;
    bool flag;
    sinfo operator = (const sinfo& other)
    {
        for(int i = 0; i != 3;i++){
            for(int j = 0; j!=3;j++){
                arr[i][j]=other.arr[i][j];
            }
        }
        pre = other.pre;
        return *this;
    }
    
    bool operator == (const sinfo& other) const
    {
        bool flag = true;
        for(int i = 0; i != 3;i++){
            for(int j = 0; j!=3;j++){
                if(arr[i][j] != other.arr[i][j]){
                    flag = false;
                }
            }
        }
        return flag;
    }
    long long int val() const{
       long long int s=0;
        for(int i=0;i != 3;i++){
            for(int j=0;j!=3;j++){
                long long int tem = arr[i][j];
                for(int k = 0 ; k != i*3+j;k++)
                {
                    tem *= 10;
                }
                s += tem;
            }
        }
        return s;
    }
    
    //bool operator < (const sinfo &other) const
    //{
    //    return val()<other.val();
    //}
    
    sinfo(int temarr[][3]){
        for (int i = 0; i != 3; i++) {
            for (int j = 0; j != 3; j++) {
                arr[i][j]=temarr[i][j];
            }
        }
    }
    
    sinfo(const sinfo& other,int ppre){
        for (int i = 0; i != 3; i++) {
            for (int j = 0; j != 3; j++) {
                arr[i][j]=other.arr[i][j];
            }
        }
        pre=ppre;
    }
    
    sinfo(){}
    
    friend ostream &operator << (ostream& out,const sinfo &a){
        for(int i=0; i!=3; i++)
        {
            for(int j=0; j!=3; j++){
                out<<int(a.arr[i][j])<<"  ";
            }
            out<<endl;
        }
        out<<endl;
        return out;
    }
    
    int check(int pos){
        int y= pos%3;
        int x= (pos-y)/3;
        return arr[x][y];
    }
    
    int checkTr(){
        int count = 0;
        for (int i = 0; i != 9; i++) {
            if (check(i) != 0) {
                for(int j = 0; j != i;j++){
                    if(check(j) > check(i)){
                        count++;
                    }
                }
            }
        }
        if(count%2 == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    
    };

class chrom{
private:
    sinfo Goal;
    sinfo arr;
    int time;
    int val;
    bool flag;
    int Xpost;
    int Ypost;
public:
    chrom(sinfo nset,int Xset,int Yset,sinfo goal);
    chrom(const chrom& other,int Xsetf,int Ysetf,int no);
    int cal();
    void chaVal(int vv);
    void chaApre(int val);
    void chaAflag(bool reflag);
    sinfo resin();
    bool reFlag();
    int reTime();
    bool iseq();
    int getVal();
    int repre();
    bool operator < (const chrom &a) const
    {
        return a.val < val;
    }
};


#endif /* defined(__neA___chrome__) */
