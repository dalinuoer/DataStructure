// 讨论题 2-4
void delete(Linklist &L) {
    // 有头节点。
    Linklist *p = L->next, ans, previous = L;
    ans = p;
    while (p->next) {
        if (p->next->data < ans->data) {
            previous = p;
            ans = p->next;
        }
        p = p->next;
    }
    previous->next = ans->next;
    free(ans);
}
// 讨论题 2-5
void josephCircle(Polyn *p, int n, int m) { // p是一个循环链表
    Polyn *p1, *p2;
    p1 = p;
    for (int i = 1; i < m; ++i) {   // 一次死掉一个人，最后剩一个
        for (int j = 1; j < n; ++j) {
            p1 = p1->next;
        }
        cout << p1->data;
        n = p1->psw;
        p2 = p1->next;
        p1->next = p1->next->next;
        free(p2);
    }
}
// 练习题 2-11
Status InsertOrderedList(SqList &a, ElemType x) {
    if (a.length == a.listsize) {
        return (OVERFLOW);
    } else {
        i = a.length - 1;
        while (i >= 0 && x < a.elem[i]) {
            --i;
        }
        for (j = a.length - 1; j >= i + 1; --j) {
            a.elem[j + 1] = a.elem[j];
        }
        a.elem[j + 1] = x;
        ++a.length;
        return OK;
    }
}
// 练习题 2-12
Status CompareList(SqList &a, SqList &b) {
    m = a.length;
    n = b.length;
    while (i <= m && i <= n) {
        if (a.elem[i] < b.elem[i]) {
            return (A < B);
        } else if (a.elem[i] > b.elem[i]) {
            return (A > B);
        }
        ++i;
    }
    if (i == m && m < n) {
        return (A < B);
    } else if (i == n && n < m) {
        return (A > B);
    } else if (i == m && m == n) {
        return (A = B);
    }
}
// 练习题 2-14
int Length(SqList &p) {
    p = p->next;
    n = 0;
    while (p) {
        ++n；
        p = p->next;
    }
    return n;
}
// 练习题 2-15
ListNode* Linklist(ListNode *ha, ListNode *hb， int m, int n) {
    if (m <= n) {   // a表比较短，应把 b 表连接到 a 
        ha = ha->next;
        while (ha) {
            ha = ha->next;
        }
        ha->next = hb->next;
        free(hb);
        return ha;
    } else {
        hb = hb，->next;
        while (hb) {
            hb = hb->next;
        }
        hb->next = ha->next;
        free(ha);
        return hb;
    }
}
时间复杂度：O(min(m, n))
// 练习题 2-19
void DeleteList(ListNode *a, double mink, double maxk) {
    if (mink >= maxk) {
        return ERROR;
    }
    ListNode *pre, *cur, *temp;
    pre = a;
    cur = a->next;
    while (cur->next) {
        if (cur->data > mink && cur->data < maxk) {
            pre->next = cur->next;
            temp = cur;
            cur = cur->next;
            free(temp);
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
}
// 练习题 2-21
int a, b;   // 互换位置
a = a + b;
b = a - b;
a = a - b;
void ReverseList(SqList &a) {
    m = a.length;
    for (i = 0; i <= m / 2 - 1; ++i) {
        a[i] = a[i] + a[m - 1 - i];
        a[m - 1 - i] = a[i] - a[m - 1 - i];
        a[i] = a[i] - a[m - 1 - i];
    }
}
// 练习题 2-22
// 头插法
ListNode* ReverseList(ListNode *head) {
    ListNode *p, *q;
    p = head->next;
    head->next = NULL;
    while (p != NULL) {
        q = p;
        p = p->next;

        q->next = head->next;
        head->next = q;
    }
   return head;
}
// 递归法
ListNode* ReverseList(ListNode *head) {
    if (head == NULL || head->next == NULL) { // 空表
        return a;
    }
    /*递归*/
    ListNode* headOfReverse = ReverseList(head->next);
    /*回溯：将当前表头结点链接到逆序链表的尾部*/
    head->next->next = head;
    head->next = NULL;
    return headOfReverse;
}
// 练习题 2-24
void MergeList(ListNode *&a, ListNode *&b, ListNode *&n) {
	//新链表递减排列，故可以采用头插法-假设均带头节点 
	ListNode *p = a->next, *q = b->next, *r, *m;
	r = n = a;
	r->next = NULL;
	free(b);
	while (p != NULL and q != NULL) {
		if (p->num < q->num) {
			m = p->next;
			p->next = r->next;
			r->next = p;
			p = m;
		} else {
			m = q->next;
			q->next = r->next;
			r->next = q;
			q = m;
		}
	} 
	while (p != NULL) {
		m = p->next;
		p->next = r->next;
		r->next = p;
		p = m;
	}
	while (q != NULL){
		m = q->next;
		q->next = r->next;
		r->next = q;
		q = m;
	}
}
// 练习题 2-33
void Classification(ListNode *p) {
    ListNode *n, *l, *pre, *cur, *temp;
    n = nn = new ListNode;
    l = ll = new ListNode;

    pre = p;
    cur = p->next;
    p = p->next;
    while (p) {
        pre->next = cur->next;
        temp = cur;
        cur = cur->next;
        if (temp->data == numberChar) {
            n->next = temp;
            temp->next = NULL;
            n = temp;
        } else if (temp->data == lettersChar) {
            l->next = temp;
            temp->next = NULL;
            l = temp;
        }
    }
    p->next = p;
    n->next = nn;
    ll->next = ll;
}
