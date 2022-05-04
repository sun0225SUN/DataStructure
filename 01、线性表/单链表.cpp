// һЩ���ã��궨���������һЩҪ�أ����������㷨
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

/************************** ��ʼ�������� *****************************/

// ������һ�����
typedef struct Node {
	ElemType data;		// ������
	struct Node* next;	// ָ����
} Node;
// �� Node �ٸĸ�����Ϊ LinkList
typedef struct Node* LinkList;

/************************** ͷ�巨���������� *****************************/

/* �������� */
/*
	�������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��ͷ�巨��
*/

/* �㷨˼· */
/*
	1������һ���p�ͼ���������i��
	2����ʼ��һ������L��
	3����L��ͷ�ڵ��ָ��ָ��	NULL��������һ����ͷ���ĵ�����
	4��ѭ����
		����һ�½ڵ㸳ֵ��p��
		�������һ���ָ�ֵ��p��������p->data��
		��p���뵽ͷ�ڵ���ǰһ�½��֮�䡣
*/

void CreateListHead(LinkList* L, int n) {
	LinkList p;
	int i;
	srand(time(0));		//��ʼ���������
	// �ȹ���һ��ͷ���
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	// ����ѭ�����ӵ�ͷ�����
	for (i = 0; i < n; i++) {
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		//�ӵ�ͷ��
		(*L)->next = p;
	}

}

/************************** β�巨���������� *****************************/

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
/************************** ����������ɾ�� *****************************/
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

/************************** �������ѯԪ�� *****************************/

/* �������� */
/*
	��ʼ�������������Ѵ��ڣ� 1<=i<=ListLength(L)
	�����������e����L�еĵ�i������Ԫ�ص�ֵ
*/

/* �㷨˼· */
/*
	1������ͷ���
		����һ�����pָ������ĵ�һ����㡣
	2����������
		j=1����j<iʱ����������������p���������ƶ�
	3������֮��
		û�ҵ��������������ĩβpΪ�գ���˵����i��Ԫ�ز����ڡ�
		�ҵ�������������ҳɹ������ؽ��p�����ݡ�
*/

Status GetElem(LinkList L, int i, ElemType* e) {
	int j;
	LinkList p;		// ����һ�����
	p = L->next;	// ��pָ������L�ĵ�һ�����
	j = 1;		// jΪ������
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

/************************** ���������Ԫ�� *****************************/
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
/************************** ������ɾ��Ԫ�� *****************************/
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