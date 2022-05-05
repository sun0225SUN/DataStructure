#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

/*********************** 双向链表的初始化（存储结构） ******************************/
typedef struct DuLNode {
	ElemType data;			// 数据域
	struct DuLNode* prior;	// 指向直接前驱
	struct DuLNode* next;	// 指向直接后继
}DuLinkList;

/*********************** 双向链表插入元素操作 ******************************/

s->prior = p;	// 待插入元素先拽住左边
s->next = p->next;	// 待插入元素拽住右边
p->next->prior = s;	// 右边的拽住待插入元素
p->next = s;	//左边的再拽住待插入元素

/*********************** 双向链表删除元素操作 ******************************/
p->prior->next = p->next;	//p的后面的直接给p的前面的
p->next->prior = p->prior; // p的前面的直接给p的后面的的