//  Created by han on 12-10-7.
//  Copyright (c) 2012年 han. All rights reserved.
//
#include <iostream>
#include <queue>
//#include <set>
#include <vector>

#include "chrome.h"

using namespace std;

int movee[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int Goall[3][3]={{1,2,3},{8,0,4},{7,6,5}};
int stsr[3][3]={{8,1,3},{0,4,5},{2,7,6}};

int main(int argc, const char * argv[])
{
    
    priority_queue<chrom> open;
    //set<sinfo> closed;
    //set<sinfo>::iterator it;
//cout<<argc<<endl;
    int startX = 1;
    int startY = 0;
    if (argc == 10) {
        for (int i = 0; i != 3; i++) {
            for (int j = 0; j != 3; j++) {
                if ((argv[3*i+j+1][0]-'0') == 0) {
                    startX = i;
                    startY = j;
                }
                stsr[i][j]=argv[3*i+j+1][0]-'0';
            }
        }
    }
    vector<sinfo> closed;
    sinfo Goal(Goall);
    sinfo stt(stsr);
    cout<<startX<<endl<<startY<<endl;
    chrom snode(stt, startX, startY,Goal);
    int no;
    if (stt.checkTr() == Goal.checkTr()) {
        open.push(snode);
        int time = 0;
        while (!open.empty()) {
            chrom tem = open.top();
            time++;
            if (tem.iseq()) {
                vector<sinfo> ans;
                vector<sinfo>::iterator it;
                ans.push_back(tem.resin());
                for (int i = 0 ; i != tem.reTime(); i++) {
                    ans.push_back(closed[int(ans[i].pre)]);
                }
                reverse(ans.begin(), ans.end());
                for (it=ans.begin(); it != ans.end(); it++) {
                    cout<<*it;
                }
                cout<<ans.size()<<endl;
                //cout<<tem.resin().pre<<endl;
                cout<<closed.size()<<endl;
                break;
            }
            no = int(closed.size());
            closed.push_back(tem.resin());
            closed[no].flag = true;
            open.pop();
            for (int i = 0; i != 4; i++) {
                bool flag = true;
                chrom stem(tem,movee[i][0],movee[i][1],no);
                if (stem.reFlag()) {
                    for (int j = 0; j != closed.size(); j++) {
                        //cout<<stem.resin()<<endl;
                        if (closed[j].flag) {
                            if (stem.resin() == closed[j]) {
                                flag = false;
                                if (stem.resin().val() < closed[j].val()) {
                                    closed[j].flag = false;
                                    open.push(stem);
                                }
                                break;
                            }
                        }
                        
                    }
                    
                    if (flag) {
                        open.push(stem);
                    }
                }
            }
        }
    }
    else{
        cout<<"无解"<<endl;
    }
    
    return 0;
}
