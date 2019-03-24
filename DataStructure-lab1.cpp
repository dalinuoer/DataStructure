/*
    实验一 一元稀疏多项式简单乘法器
    (1)输入并建立多项式；
    (2)输出多项式，输出形式为整数序列：n,c1,e1,c2,e2,...,cn,en,其中n 是多项式的项数，ci 和ei 分别是第i 项的系数和指数，序列按指数降序排列。
    (3)多项式a 与多项式b 相乘，建立多项式。

    Author：秦浩
    Date：2019/3/17
*/

#include <iostream>
using namespace std;

typedef struct PolynNode* Polynomial;   // 将Polynomial作为指向结构体PolyNode的指针的别名。
struct PolynNode {
    double coef; // 系数
    int expn;   // 指数
    Polynomial next;    // 指向下一个结点的指针。
};

Polynomial CreatPolyn() {  // 根据读入的多项式构成链表，并返回链表的头指针。
    int num, coef, expn;    // 项数， 系数， 指数.
    cin >> num; // 输入多项式的项数。

    Polynomial head, p, tempPointer;

    // 设置头节点。
    head = new PolynNode;
    head->coef = 0;
    head->expn = 0;
    head->next = NULL;

    tempPointer = head;

    while (num--) {
        cin >> coef >> expn;
        p = new PolynNode;   //创建新节点
        p->coef = coef; // 设置新节点
        p->expn = expn;
        p->next = NULL;
        tempPointer->next = p;  //连接新结点
        tempPointer = p;    //尾指针指向新节点
    }

    return head;
}

Polynomial AddPolyn(Polynomial p1, Polynomial p2) { // 多项式相加。
    Polynomial res, ans, ha, hb;
	res = new PolynNode;
	ans = res;
	ha = p1->next;
	hb = p2->next;

	while (ha && hb) {
		Polynomial temp = new PolynNode;
		if (ha->expn > hb->expn) { // 每次把指数较大的加入链表res
			temp->coef = ha->coef;
			temp->expn = ha->expn;
			ans->next = temp;
			ans = temp;
			ha = ha->next;
		} else if (ha->expn < hb->expn) {
			temp->coef = hb->coef;
			temp->expn = hb->expn;
			ans->next = temp;
			ans = temp;
			hb = hb->next;
		} else {
			double sumCoef = (ha->coef) + (hb->coef); // 指数相同,系数求和。
			if (sumCoef != 0) {
				temp->coef = sumCoef;
				temp->expn = ha->expn;
				ans->next = temp;
				ans = temp;
			}
			ha = ha->next;
			hb = hb->next;
		}
	}

	while (ha) {
			Polynomial temp = new PolynNode;
			temp->coef = ha->coef;
			temp->expn = ha->expn;
			ans->next = temp;
			ans = temp;
			ha = ha->next;
	}
	while (hb) {
			Polynomial temp = new PolynNode;
			temp->coef = hb->coef;
			temp->expn = hb->expn;
			ans->next = temp;
			ans = temp;
			hb = hb->next;
	}
	ans->next = NULL;

	return res;
}

Polynomial MultPolyn(Polynomial p1, Polynomial p2) {    // 多项式相乘，返回p1的地址。
	Polynomial res, ans, ha, hb;
	ha = p1->next;
	hb = p2->next;
	res = new PolynNode;
	res->next = NULL;

	if (ha == NULL || hb == NULL) { // 空表。
		return res;
	}

	Polynomial temp;
	while (ha != NULL) {
		temp = new PolynNode;
		ans = temp;
		hb = p2->next;
		while (hb != NULL) {
			Polynomial temp2 = new PolynNode;
			temp2->expn = ha->expn + hb->expn;
			temp2->coef = ha->coef * hb->coef;
			hb = hb->next;
			ans->next= temp2;
			ans = temp2;
		}

		ans->next = NULL;
		res = AddPolyn(res, temp);  // 乘法->加法.
		ha = ha->next;
	}

	return res;
}

void PrintPolyn(Polynomial p) { // 打印多项式。
    if (!(p->next)) {   // 空表
        cout << "0 0" << endl;
        return;
    }

    Polynomial pp;
    pp = p->next;    // 跳过头节点。
    int num = 0;
    while (pp) {
        if (pp->coef != 0) {
            ++num;
        }
        pp = pp->next;
    }
    cout << num << " " ;

    pp = p->next;
    while (pp) {
        if (pp->coef != 0) {
            if (pp->next == NULL) {
                cout << pp->coef << " " << pp->expn << endl;
            } else {
                cout << pp->coef << " " << pp->expn << " " ;
            }
        }
        pp = pp->next;
    }
}

int main(int argc, char** argv) {
    Polynomial p1, p2, p3;

    p1 = CreatPolyn();
    p2 = CreatPolyn();

    p3 = MultPolyn(p1, p2);

    PrintPolyn(p3);

    return 0;
}
