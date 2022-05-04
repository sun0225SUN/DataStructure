// 宏定义或者重命名一些要素，便于描述算法
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MaxSize 100		// 宏定义线性表的长度

typedef int Status;		// Status 是函数的返回值类型，其值是函数的状态代码，如OK等。
typedef int ElemType;	// 元素类型，这里通过重命名int来表示，便于描述算法


/************************** 初始化顺序表 *****************************/

/* 第一种方式，使用静态数组初始化一个线性表 */
typedef struct {
	ElemType data[MaxSize];		//顺序表的元素
	int length;		//顺序表的当前长度
}SqList;		//顺序表的类型定义

/* 第二种方式，动态分配内存 */
/*
#define InitSize 100
typedef int ElemType;
typedef struct {
	ElemType* data;		//指示动态分配数组的指针
	int MaxSize, length;		//数组的最大容量和当前个数
}SeqList; //动态分配数组的顺序表的类型定义
*/

/************************** 顺序表查询元素 *****************************/

/* 需求描述 */
/*
	初始条件：顺序表L已存在，1<=i<=ListLength(L)
	操作结果：用e返回L中第i个数据元素的值。
*/

Status GetElem(SqList L, int i, ElemType* e) {
	// 健壮性操作，以下情况不符合题设，应报错
	// 因为要获取第i个元素，i是1开始数的，所以 i<1 非法
	// 当线性表的长度为0时，即L.length==0，线性表里没有任何元素，非法
	// 当获取元素超出线性表长度时，非法
	if (L.length == 0 || i<1 || i>L.length) {
		return ERROR;
	}
	// 将线性表的第i个元素交给*e，返回状态码OK。
	*e = L.data[i - 1];
	return OK;
}


/************************** 顺序表插入元素 *****************************/

/* 需求描述 */
/*
	初始条件：顺序表L已存在，1<=i<=ListLength(L)
	操作结果：在L中第i个位置之前插入一个新的元素e，L的长度+1
*/

/*	算法思路 */
/*
	1、健壮性操作：
		如果插入的元素位置不合理，抛出异常。
		如果线性表长度大于等于数组长度，抛出异常或动态增加容量。
	2、准备阶段：
		从最后一个元素向前遍历到第i个位置，分别将他们往后移动一个位置。
	3、开始插入：
		将要插入的元素插入位置i处。
	4、插入之后：
		表长加一。
*/

Status ListInsert(SqList* L, int i, ElemType e) {
	// 健壮性操作1，如果顺序表满了，抛出异常
	if (L->length == MaxSize) {
		return ERROR;
	}
	// 健壮性操作2，如果i的位置不合法，抛出异常，
	// 这里记得i大于顺序表的长度+1才算不合法，因为要预留一个插入
	if (i<1 || i>L->length + 1) {
		return ERROR;
	}
	// 开始插入，如果插入的元素不在表尾（在表尾的直接让e=L.data[l.length+1]就好了，这里不写了）
	if (i <= L->length + 1) {
		int j; // j的初始值为顺序表的最后一个元素。
		// 因为要在i前插一个，所以j可以取到i，最终的判断条件为，j >= i
		for (j = L->length; j >= i; j--) {
			// 每个元素向后面移动一个位置，第j个元素对应的数组下标为j-1
			L->data[j] = L->data[j - 1];
		}
	}
	// 插入新元素
	L->data[i - 1] = e;
	// 表长++
	L->length++;
	return OK;
}

/************************** 顺序表删除元素 *****************************/

/* 需求描述 */
/*
	初始条件：顺序表L已存在，1<=i<=ListLength(L)
	操作结果：在L中删除第i个位置的元素，表长-1
*/

/* 算法思路 */
/*
	1、健壮性操作：
		如果线性表为空，抛出异常。
		如果删除的位置不合理，抛出异常。
	2、开始删除：
		取出待删除的元素
	3、删除之后：
		从删除位置开始遍历到最后一个元素位置，分别将他们往前移动一个位置。
		表长减一。
*/

Status ListDelete(SqList* L, int i, ElemType* e) {
	// 健壮性操作1：如果线性表为空，抛出异常！
	if (L->length == 0) {
		return ERROR;
	}
	// 健壮性操作2：如果i的取值范围不合法，抛出异常
	if (i<1 || i>L->length) {
		return ERROR;
	}
	// 将待删除元素取出来给e
	*e = L->data[i - 1];
	// 从i开始遍历，后面的元素前移。
	int j;
	for (j = i; j < L->length; j++) {
		L->data[j - 1] = L->data[j];
	}
	// 表长-1
	L->length--;
	return OK;
}