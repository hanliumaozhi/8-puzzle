// Astar
package main

import (
	"./prio"  //优先队列的库
	"errors"  //标准错误
	"fmt"     //提供打印函数的库
	"os"      //获取参数的库
	"strconv" //字符串处理的库
)

//下面为搜索状态的类 
type Node struct {
	Arr   [3][3]int //存储棋面状态的
	Val   int       //f*(x)的值
	Time  int       //g*(x)的值
	index int       //因为优先队列是由堆实现的所以需要一个index
	post  [2]int    //0所在的位置
}

//下面是为了存储在closed表里面的
type NodeMap struct {
	Arr  [3][3]int
	Val  int
	Time int
}

//下面2个函数是为了实现 优先的队列的 接口
func (x *Node) Less(y prio.Interface) bool { return x.Val < y.(*Node).Val }
func (x *Node) Index(i int)                { x.index = i }

func main() {
	var q prio.Queue               //q为open表
	var NodeDB map[NodeMap]NodeMap //NodeDB为closed表
	NodeDB = make(map[NodeMap]NodeMap)

	move := [4][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}} //move为空块移动的位置的相对坐标
	ww := [3][3]int{{2, 1, 3}, {8, 0, 4}, {7, 5, 6}}    //ww为起始节点
	posta := [2]int{1, 0}                               //空块的位置
	Goal := [3][3]int{{1, 2, 3}, {8, 0, 4}, {7, 6, 5}}  //目的节点
	//下面是 依据输入的数据修改初始节点
	if len(os.Args) == 10 || len(os.Args) == 19 {
		b := 0
		for i := 0; i != 9; i++ {
			b, _ = strconv.Atoi(string(os.Args[i+1])) //将字符串修改为数字
			if b == 0 {
				posta[0] = i / 3
				posta[1] = i % 3
			}
			ww[i/3][i%3] = b
		}
	}
	if len(os.Args) == 19 {
		b := 0
		for i := 0; i != 9; i++ {
			b, _ = strconv.Atoi(string(os.Args[i+1+9])) //将字符串修改为数字
			Goal[i/3][i%3] = b
		}
	}

	if checkV(ww) == checkV(Goal) { //判断是否可行
		ss := NewNode(ww, Goal, posta) //初始化 初始节点
		ssnil := NodeMap{Arr: ww, Val: 0, Time: -1}
		NodeDB[ss.New()] = ssnil
		q.Push(ss)
		for {
			if q.Len() == 0 { //如果队列为空跳出
				break
			}
			ss := q.Pop().(*Node) //启发值最小的出队
			if ss.isEquel(Goal) { //如果节点和目标值一样
				//下面几行是回溯可行解的路径
				stem := ss.New()
				anss := []NodeMap{stem}
				for {
					tem := NodeDB[stem]
					if tem.Time == -1 {
						break
					}
					anss = append(anss, tem)
					stem = tem
				}
				fmt.Println("ok")
				fmt.Printf("共%d步\n", len(anss)-1)
				//打印路径
				for i := (len(anss) - 1); i != -1; i-- {
					show(anss[i].Arr)
					fmt.Println("")
				}
				break
			}
			//空白块向四面移动
			for i := 0; i != 4; i++ {
				other, err := ss.chrom(move[i][:], Goal)
				//如果生成 合理的方块
				if err == nil {
					_, ok := NodeDB[other.New()]
					if !ok {
						q.Push(other)
						NodeDB[other.New()] = ss.New()
					}
				}
			}

		}
	} else {
		fmt.Println("无解")
	}
}

//Node类的构造函数
func NewNode(ss [3][3]int, Goal [3][3]int, posta [2]int) *Node {
	Val := calVal(ss, Goal, 0)
	return &Node{Arr: ss, Val: Val, Time: 0, post: posta}
}

//NodeMap类的构造函数
func (a Node) New() NodeMap {
	return NodeMap{Arr: a.Arr, Val: a.Val, Time: a.Time}
}

//检查棋面的奇偶值
func checkV(a [3][3]int) bool {
	count := 0
	flag := true
	for i := 0; i != 9; i++ {
		if a[i/3][i%3] != 0 {
			for j := 0; j != i; j++ {
				if a[j/3][j%3] > a[i/3][i%3] {
					count++
				}
			}

		}
	}
	if count%2 != 0 {
		flag = false
	}
	return flag

}

//打印棋面
func show(Arr [3][3]int) {
	fmt.Println(Arr[0][0], Arr[0][1], Arr[0][2])
	fmt.Println(Arr[1][0], Arr[1][1], Arr[1][2])
	fmt.Println(Arr[2][0], Arr[2][1], Arr[2][2])
}

//判断是否到达目的节点
func (a Node) isEquel(b [3][3]int) bool {
	flag := true
	for i := 0; i != 3; i++ {
		for j := 0; j != 3; j++ {
			if a.Arr[i][j] != b[i][j] {
				flag = false
			}
		}
	}
	return flag
}

//node的构造函数 用于由老节点生成新节点
func (a Node) chrom(mstep []int, Goal [3][3]int) (nNode *Node, err error) {
	btime := a.Time + 1
	bpost := a.post
	bpost[0] += mstep[0]
	bpost[1] += mstep[1]
	if bpost[0] < 0 || bpost[0] > 2 || bpost[1] < 0 || bpost[1] > 2 {
		err = errors.New("0001")
		return
	}

	bArr := a.Arr
	bArr[bpost[0]][bpost[1]], bArr[a.post[0]][a.post[1]] = bArr[a.post[0]][a.post[1]], bArr[bpost[0]][bpost[1]]
	bval := calVal(bArr, Goal, btime)
	return &Node{Arr: bArr, Val: bval, Time: btime, post: bpost}, nil
}

//计算启发函数f*（）的值
func calVal(a [3][3]int, goal [3][3]int, Time int) int {
	ans := 0
	ans += Time

	for i := 0; i != 3; i++ {
		for j := 0; j != 3; j++ {
			if a[i][j] != 0 {
				if a[i][j] != goal[i][j] {
					ans++
				}
			}
		}
	}

	for i := 0; i != 3; i++ {
		for j := 0; j != 3; j++ {
			if a[i][j] != 0 {
				for k := 0; k != 3; k++ {
					for l := 0; l != 3; l++ {
						if a[i][j] == goal[k][l] {
							ans += (abs(i-k) + abs(j-l))
						}
					}
				}
			}
		}
	}

	return ans
}

//整数的绝对值函数
func abs(data int) int {
	if data < 0 {
		data = -data
	}
	return data
}
