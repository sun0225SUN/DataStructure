// 一些引用，宏定义或重命名一些要素，便于描述算法
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

/************************** 初始化单链表 *****************************/

// 定义了一个结点
typedef struct Node {
	ElemType data;		// 数据域
	struct Node* next;	// 指针域 struct类型的指针，名字叫做Node
} Node;
// 给 Node* 再改个名字为 LinkList，linklist为一个结构体指针。
typedef struct Node* LinkList;

/************************** 头插法创建单链表 *****************************/

/* 需求描述 */
/*
	随机生成n个元素的值，建立带表头结点的单链线性表L（头插法）
*/

/* 算法思路 */
/*
	1、声明一结点p；
	2、初始化一空链表L；
	3、让L的头节点的指针指向	NULL，即建立一个带头结点的单链表；
	4、循环：
		生成一新节点赋值给p；
		随机生成一数字赋值给p的数据与p->data；
		将p插入到头节点与前一新结点之间。
*/

void CreateListHead(LinkList* L, int n) {
	// 1、声明了一个结点p，LinkList是一个结构体指针，它指向的是我们定义好的结点。
	LinkList p;
	// 2、初始化一个带有头结点的空链表，
	// 动态分配内存，向系统申请一个空间，存储一个LinkList类型的指针结点，*L是这个结点
	*L = (LinkList)malloc(sizeof(Node));
	// 3、这个头结点的指针指向NULL
	(*L)->next = NULL;
	// 4、循环生成元素，接到头结点上
	int i;		// 计数器
	srand(time(0));		// 初始化随机种子
	// 循环生成元素
	for (i = 0; i < n; i++) {
		// 申请一个p结点
		p = (LinkList)malloc(sizeof(Node));
		// p结点的数据
		p->data = rand() % 100 + 1;
		// 先让p的指针拽住后面的元素，初始的时候下一个元素为NULL
		p->next = (*L)->next;
		// 在让头节点的指针指向p
		(*L)->next = p;
	}
}

/************************** 尾插法创建单链表 *****************************/

void CreateListTail(LinkList* L, int n) {
	// 定义了两个结点
	LinkList p, r;
	// 动态分配内存，定义一个结点，头结点
	*L = (LinkList)malloc(sizeof(Node));
	// 拷贝一份头结点给r
	r = *L;
	// 循环开始创建元素
	int i;
	srand(time(0));
	for (i = 0; i < n; i++) {
		// 申请一个结点，动态分配
		p = (Node*)malloc(sizeof(Node));
		// 给p结点赋值
		p->data = rand() % 100 + 1;
		// r指向p
		r->next = p;
		// 让r=p
		r = p;
	}
	// r的指针NULL
	r->next = NULL;
}

/************************** 单链表整表删除 *****************************/

Status ClearList(LinkList* L) {
	// 定义两个指针，单链表结点类型的，它指向的肯定也是单链表啦！
	LinkList p, q;
	// p指向单链表的头结点（也可以是第一个结点，如果没有头结点的话，但本程序假设头结点存在，便于描述）
	p = (*L)->next;
	// 当p指针指向的元素不为空时，
	while (p) {
		// 把待删除的元素赋值给q
		q = p->next;	//初始值不是头结点，是第一个结点
		//把p释放掉
		free(p); //现在p指向的是头结点，把头结点给干掉
		// 让p=q
		p = q; // 现在头结点被干掉了，p指向第一个结点，就是把q赋值给q
	}
	// 头结点为空？？？，头结点不是被干掉了么，现在这个应该是最后一个结点，但是最后一个结点数据域里有东西
	(*L)->next = NULL;
	// 成功！！！
	return OK;
}

/************************** 单链表读取元素 *****************************/

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

		让p一直游走，走到i就返回这个数据
*/

Status GetElem(LinkList L, int i, ElemType* e) {
	int j;
	LinkList p;		// 声明一个指针，头指针
	p = L->next;	// 让p指向链表L的第一个结点
	j = 1;		// j为计数器
	// 循环遍历
	// 如果p不为空，就让p一直游走下去
	while (p && j < i) { 
		p = p->next;
		j++;
	}
	// 如果p指针指向空，或者j>i，抛出异常。
	if (!p || j > i) {
		return ERROR;
	}
	// p指向i元素，把i元素的data交给e
	*e = p->data;
	// 成功
	return OK;
}

/************************** 单链表插入元素 *****************************/
// s->next=p->next;		p->next=s;
Status ListInsert(LinkList* L, int i, ElemType e) {
	// 两个指针，链表结点类型的
	LinkList p, s;
	// p指向链表
	p = *L;
	int j = 1;
	// p不为空，j<i，遍历
	while (p && j < i) {
		p = p->next;
		j++;
	}
	int j = 1;
	// p为空或者j>i，抛出异常
	if (!p || j > i) {
		return ERROR;
	}
	// 定义一个结点
	s = (LinkList)malloc(sizeof(Node));
	// 结点的数据为e
	s->data = e;
	// 结点拽住i的下一个结点，也就是现在p指向的那个元素
	s->next = p->next;
	// 拽住之后，现在p可以指向s了
	p->next = s;
	//插入完成
	return OK;
}
/************************** 单链表删除元素 *****************************/
// q=p->next;	p->next=q->next;

Status ListDelete(LinkList* L, int i, ElemType* e) {
	// 定义了两个指针，链表结点类型的。
	LinkList p, q;
	// p指向整个单链表
	p = *L;
	// 计数器
	int j = 1;
	// p不为空，在j<i的范围内，p一直往后移动。
	while (p->next && j < i) {
		p = p->next;
		j++;
	}
	// 如果p指向为空，或者j大于i了，就抛出异常
	if (!(p->next) || j > i) {
		return ERROR;
	}
	//现在p指向了待删除的结点，把这个结点给q
	q = p->next;
	// 绕过中间的，现在最左边的（p->next）指向最右边的(q->next)
	p->next = q->next;
	// 要删除的数据就是q->data
	*e = q->data;
	// 释放掉这个空间
	free(q);
	// 完美结束！！！
	return OK;
}