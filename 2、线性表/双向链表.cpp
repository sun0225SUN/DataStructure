#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

/*********************** ˫������ĳ�ʼ�����洢�ṹ�� ******************************/
typedef struct DuLNode {
	ElemType data;			// ������
	struct DuLNode* prior;	// ָ��ֱ��ǰ��
	struct DuLNode* next;	// ָ��ֱ�Ӻ��
}DuLinkList;

/*********************** ˫���������Ԫ�ز��� ******************************/

s->prior = p;	// ������Ԫ����קס���
s->next = p->next;	// ������Ԫ��קס�ұ�
p->next->prior = s;	// �ұߵ�קס������Ԫ��
p->next = s;	//��ߵ���קס������Ԫ��

/*********************** ˫������ɾ��Ԫ�ز��� ******************************/
p->prior->next = p->next;	//p�ĺ����ֱ�Ӹ�p��ǰ���
p->next->prior = p->prior; // p��ǰ���ֱ�Ӹ�p�ĺ���ĵ�