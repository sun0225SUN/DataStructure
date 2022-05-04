// 一些引用，宏定义或重命名一些要素，便于描述算法
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

/************************** 初始化单链表 *****************************/

// 定义了一个结点
typedef struct Node {
	ElemType data;		// 数据域
	struct Node* next;	// 指针域
} Node;
// 给 Node 再改个名字为 LinkList
typedef struct Node* LinkList;

/************************** 头插法创建单链表 *****************************/

/* 需求描述 */
/*
	随机生成n个元素的值，建立带表头结点的单链线性表L（头插法）
*/

/* 算法思路 */
/*
	1、声明一结点p和计数器变量i；
	2、初始化一空链表L；
	3、让L的头节点的指针指向	NULL，即建立一个带头结点的单链表；
	4、循环：
		生成一新节点赋值给p；
		随机生成一数字赋值给p的数据与p->data；
		将p插入到头节点与前一新结点之间。
*/

void CreateListHead(LinkList* L, int n) {
	LinkList p;
	int i;
	srand(time(0));		//初始化随机种子
	// 先构造一个头结点
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	// 生成循环，接到头结点上
	for (i = 0; i < n; i++) {
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		//接到头上
		(*L)->next = p;
	}

}

/************************** 尾插法创建单链表 *****************************/

void CreateListTail(LinkList* L, int n) {
	LinkList p, r;
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	r = *L;
	for (i = 0; i < n; i++) {
		p = (Node*)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}
/************************** 单链表整表删除 *****************************/
Status ClearList(LinkList* L) {
	LinkList p, q;
	p = (*L)->next;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}

/************************** 单链表查询元素 *****************************/

/* 需求描述 */
/*
	初始条件：单链表已存在， 1<=i<=ListLength(L)
	操作结果：用e返回L中的第i个数据元素的值
*/

/* 算法思路 */
/*
	1、声明头结点
		声明一个结点p指向链表的第一个结点。
	2、遍历链表
		j=1，当j<i时，遍历链表，并且让p不断往后移动
	3、遍历之后
		没找到情况：若到链表末尾p为空，则说明第i个元素不存在。
		找到的情况：若查找成功，返回结点p的数据。
*/

Status GetElem(LinkList L, int i, ElemType* e) {
	int j;
	LinkList p;		// 声明一个结点
	p = L->next;	// 让p指向链表L的第一个结点
	j = 1;		// j为计数器
	while (p && j < i) { // 
		p = p->next;
		j++;
	}
	if (!p || j > i) {
		return ERROR;
	}
	*e = p->data;
	return OK;
}

/************************** 单链表插入元素 *****************************/
// s->next=p->next;p->next=s;
Status ListInsert(LinkList* L, int i, ElemType e) {
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p && j < 1) {
		p = p->next;
		j++;
	}
	if (!p || j > 1) {
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
/************************** 单链表删除元素 *****************************/
// q=p->next;	p->next=q->next;

Status ListDelete(LinkList* L, int i, ElemType* e) {
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < 1) {
		p = p->next;
		j++;
	}
	if (!(p->next) || j < i) {
		return ERROR;
	}
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}