#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define M 20
#define N 20

struct mark { // 定义迷宫内点的坐标类型
	int x;
	int y;
};

struct Element { // 链栈元素
	int x, y; //x行,y列
	int d; //d下一步的方向
};

typedef struct LStack { //链栈
	Element elem;
	struct LStack* next;
}*PLStack;

// 栈函数

int initStack(PLStack& S) { //构造栈
	S = NULL;
	return 1;
}

int StackEmpty(PLStack S) { //判断栈是否为空
	if (S == NULL)
		return 1;
	else
		return 0;
}

int Push(PLStack & S, Element e) { //压栈
	PLStack p;
	p = (PLStack)malloc(sizeof(LStack));
	p->elem = e;
	p->next = S;
	S = p;
	return 1;
}

int Pop(PLStack & S, Element & e) { //出栈
	PLStack p;
	if (!StackEmpty(S)) {
		e = S->elem;
		p = S;
		S = S->next;
		free(p);
		return 1;
	}
	else
		return 0;
}

// 求迷宫路径
void mazePath(struct mark start, struct mark end, int** maze, int diradd[4][2]) {
	int i, j, d;
	int a, b;
	Element elem, e;
	PLStack S1, S2;
	initStack(S1);
	initStack(S2);
	maze[start.x][start.y] = 2; //入口点作上标记
	elem.x = start.x;
	elem.y = start.y;
	elem.d = -1; //开始为-1
	Push(S1, elem);
	while (!StackEmpty(S1)) { //栈不为空 有路径可走
		Pop(S1, elem);
		i = elem.x;
		j = elem.y;
		d = elem.d + 1; //下一个方向
		while (d < 4) { //试探各个方向
			a = i + diradd[d][0];
			b = j + diradd[d][1];
			if (a == end.x && b == end.y && maze[a][b] == 0) { //如果到了出口
				elem.x = i;
				elem.y = j;
				elem.d = d;
				Push(S1, elem);
				elem.x = a;
				elem.y = b;
				elem.d = 4; 
				Push(S1, elem);
				printf("\n0=右 1=下 2=左 3=上\n");
				while (S1) { //逆置序列 并输出迷宫路径序列
					Pop(S1, e);
					Push(S2, e);
				}
				int count = 1;
				while (S2) {
					Pop(S2, e);
					printf("第%d步：%d,%d,%d \n", count, e.x, e.y, e.d);
					count++;
				}
				return; //跳出两层循环
			}
			if (maze[a][b] == 0) { //找到可以前进的非出口的点
				maze[a][b] = 2; //标记走过此点
				elem.x = i;
				elem.y = j;
				elem.d = d;
				Push(S1, elem); //当前位置入栈
				i = a; //下一点转化为当前点
				j = b;
				d = -1;
			}
			d++;
		}
	}
	printf("很遗憾，没有找到通路！\n");
}

// 随机迷宫生成器
int** mazeMaker(int row, int col) {
	int** maze = new int* [M];
	for (int i = 0; i < M; ++i) {
		maze[i] = new int[N];
	}
	srand(unsigned(time(0)));
	for (int j = 1; j <= row; ++j) {
		for (int k = 1; k <= col; ++k) {
			maze[j][k] = rand() % 6;
			if (maze[j][k] != 0) {
				maze[j][k] = 0;
			}
			else {
				maze[j][k] = 1;
			}
		}
	}
	for (int i = 0; i <= row + 1; i++) { //加一圈墙
		maze[i][0] = 1;
		maze[i][col + 1] = 1;
	}
	for (int j = 0; j <= col + 1; j++) {
		maze[0][j] = 1;
		maze[row + 1][j] = 1;
	}
	printf("\n随机生成的迷宫为：\n");
	for (int i = 0; i <= row + 1; i++) { //输出迷宫
		for (int j = 0; j <= col + 1; j++)
			printf("%d ", maze[i][j]);
		printf("\n");
	}
	return maze;
}

int main() {
	struct mark start, end; //入口和出口的坐标
	int add[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; //行增量和列增量 方向依次为右左下上

	int row, col; //迷宫行,列
	printf("下面请输入迷宫的行数和列数，注意，要求行数和列数均不超过18！\n");
	printf("\n请输入迷宫的行数:");
	scanf("%d", &row);
	printf("请输入迷宫的列数:");
	scanf("%d", &col);
	int** maze = mazeMaker(row, col);

	printf("请输入入口:\n");
	scanf("%d %d", &start.x, &start.y);
	printf("请输入出口：\n");
	scanf("%d %d", &end.x, &end.y);
	
	mazePath(start, end, maze, add);
	system("PAUSE");
	return 0;
}