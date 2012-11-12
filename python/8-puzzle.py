# -*- coding: utf-8 -*-
"""
Created on Tue Oct 16 19:23:39 2012

@author: han
"""

import copy, sys



class priorQueue:#构建一个优先队列
    def __init__(self):#初始化类
        self._qList = list()
        
    def isEmpty(self):#判断类是否为空
        return len(self) == 0
        
    def __len__(self):#返回队列的元素个数
        return len(self._qList)
        
    def enQueue(self, something):#入对
        self._qList.append(something)
        
    def deQueue(self):#出队
        assert not self.isEmpty(), "Cannot dequeue from an empty queue."
        #当队列为空的时候报错
        
        #下面是为了寻找启发值最小的
        minNum = self._qList[0].val
        post = 0
        for i in xrange(len(self._qList)):
            if self._qList[i].val < minNum:
                post = i
                minNum = self._qList[i].val
        something = self._qList[post]
        
        self._qList.pop(post)
        return something
        
class chrom:
    def __init__(self,*arg):#*arg 是参数列表 是为了 重载 类 构造函数:
        #此时创造的为初始节点 第一个参数为现在的棋盘状态 第二个为0的位置 第三个为目标状态
        if len(arg) == 3:
            self.cur = arg[0]
            self.xPost = arg[1][0]
            self.yPost = arg[1][1]
            self.goal = arg[2]
            self.flag = True
            self.time = 0
        elif len(arg) == 2:#此时为由节点生成后续节点的构造函数
            self.cur = copy.deepcopy(arg[0].cur)
            self.goal = arg[0].goal
            self.xPost = arg[0].xPost
            self.yPost = arg[0].yPost
            self.time = arg[0].time + 1
            xTem = self.xPost + arg[1][0]
            yTem = self.yPost + arg[1][1]
            if xTem < 3 and xTem > -1 and yTem < 3 and yTem > -1:
                self.flag = True
            else:
                self.flag = False
            if self.flag:
                self.cur[self.xPost][self.yPost], self.cur[xTem][yTem] = self.cur[xTem][yTem], self.cur[self.xPost][self.yPost]
                self.xPost = xTem
                self.yPost = yTem
                
        if self.flag:
            self.val = self.calculate()

        
    def calculate(self):#计算启发值
        ans = 0
        ans += self.time
        
        for i in xrange(3):
            for j in xrange(3):
                if self.cur[i][j] != 0:
                    if self.cur[i][j] != self.goal[i][j]:
                        ans += 1
                        
        for i in xrange(3):
            for j in xrange(3):
                if self.cur[i][j] != 0:
                    for k in xrange(3):
                        for l in xrange(3):
                            if self.cur[i][j] == self.goal[k][l]:
                                ans += (abs(i-k) + abs(j-l))
        return ans
        
    def isEqual(self):#判断是否到达目标状态
        equal = True
        for i in xrange(3):
            for j in xrange(3):
                if self.cur[i][j] != self.goal[i][j]:
                    equal = False
                    
        return equal
        
    def __str__(self):#重载输出值
        ansstr = ""
        for i in xrange(3):
            for j in xrange(3):
                ansstr += str(self.cur[i][j])
                ansstr += "\t"
            ansstr += '\n'
        return ansstr
        
    def hashtype(self):#返回特征
        sttr = ""
        for i in self.cur:
            for j in i:
                sttr += str(j)
        sttr += str(self.val)
        return sttr
        

def checkV(a):#检查棋面状态
    count = 0
    for i in xrange(9):
        if a[i/3][i%3] != 0:
            for j in xrange(i):
                if a[j/3][j%3] > a[i/3][i%3]:
                    count += 1
    if count%2 == 0:
        return 1
    else:
        return 0
        

if __name__ == "__main__":
    move = [[1,0],[-1,0],[0,1],[0,-1]]#空白块的移动
    start = [[2,1,3],[8,0,4],[7,5,6]]#初始节点
    Goal = [[1,2,3],[8,0,4],[7,6,5]]#目标节点
    ps = [1,1]#空白块的位置
    
    #以下为根据输入状态修改节点状态
    if len(sys.argv) == 10 or len(sys.argv) == 19:
        for i in xrange(9):
            start[i/3][i%3] = int(sys.argv[i+1])
            if sys.argv[i+1] == 0:
                ps = [i/3,i%3]
    if len(sys.argv) == 19:
        for i in xrange(9):
            Goal[i/3][i%3] = int(sys.argv[i+1+9])
            
    if checkV(start) == checkV(Goal):       
        a= chrom(start,ps,Goal)
        openList = priorQueue()#open表为优先队列
        clost = dict()#clost表为字典
        rclost = dict()
        openList.enQueue(a)
        clost[a.hashtype()] = "Nil"
        rclost[a.hashtype()] = a
        while not openList.isEmpty():
            tem = openList.deQueue()
    
            if tem.isEqual():#如果搜索值与目标一致 就跳出
                print "Solved"
                #下面为寻找解的路径
                ansl = list()
                ansl.append(rclost[tem.hashtype()])
                stem = rclost[clost[tem.hashtype()]]
                while True:
                    ansl.append(stem)
                    stem = clost[stem.hashtype()]
                    if stem == "Nil":
                        break
                    stem = rclost[stem]
                
                ansl.reverse()
                for i in ansl:
                    print i
                print len(clost)
                break
            else:
                for i in move:
                    stem = chrom(tem,i)
                    if stem.flag:
                        if not clost.has_key(stem.hashtype()):#判断是否为以前到达的节点 如果不是就到进入open表
                            openList.enQueue(stem)
                            clost[stem.hashtype()] = tem.hashtype()
                            rclost[stem.hashtype()] = stem
    else:
        print "无解"
        
    

                

        