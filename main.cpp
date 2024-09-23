#define _CRT_SECURE_NO_WARNINGS
/*
编写程序求解三个集合A、B、C的集合运算，使得：A= A ∩（ B ∪ C ）。
	（1）设计要求：使用线性表的顺序存储结构表示集合A、B、C，先实现顺序表的基本操作，再利用基本操作编程完成集合的运算。
	（2）输入输出要求：三个集合中的元素为整数，分别由用户输入集合中的数据，以0作为结束；输出原有的三个集合的元素，及求解后A中的元素。
例如： 输入数据 集合A：
					2  5  6  4  0
				   集合B：
					1  4  2   0
					集合C：
					2  5  3   0
		输出显示	集合A：2  5  6  4
					集合B：1  4  2
					集合C：2  5  3
					结果集A：2  5   4

*/

#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LISTINCREMENT 10

typedef int Status;
typedef int ElemType;

// 顺序表的 顺序存储 结构定义
typedef struct {
	ElemType* elem;   //存储空间基址
	int listsize;     //当前分配存储容量
	int length;       //顺序表长度
}SqList; 

// 初始化顺序表
Status InitList_Sq(SqList& L) {
	L.elem = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = INIT_SIZE;
	return OK;
}

// 取值 如果线性表L存在第i个元素，则用e返回其值
Status GetElem_Sq(SqList L, int i, ElemType& e) {
	if (i < 1 || i > L.length) return ERROR;	// i值不合法
	e = L.elem[i - 1];
	return OK;
}

//LocateElem(L, e): 在L中查找与给定值e相等的元素，如果查找成功，返回该元素在L中的位序，否则返回0
int LocateElem_Sq(SqList L, ElemType e) {
	int i;
	for (i = 0; i < L.length; i++) {
		if (L.elem[i] == e) return i + 1;
	}
	return 0;
}

//ListInsert_Sq(L, i, e): 若L存在，且i在1和n+1之间，则在L中第i个位置 【之前】 插入新的元素e，L的长度加1
Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	int j;
	if (i < 1 || i > L.length + 1) return ERROR;	// i值不合法
	// 当前存储空间已满，增加分配
	if (L.length >= L.listsize) {
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);	// 存储分配失败
		L.elem = newbase;				// 新基址
		L.listsize += LISTINCREMENT;	// 增加存储容量
	}
	for (j = L.length - 1; j >= i - 1; j--) {
		L.elem[j + 1] = L.elem[j];		// 插入位置及之后的元素后移
	}
	L.elem[i - 1] = e;					// 插入e
	++L.length;							// 表长增1
	return OK;
}

// ListDelete_Sq(L, i, e): 若L存在且i在1和n之间，则删除L的第i个数据元素，并用e返回其值，L的长度减1
Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
	int j;
	if (i < 1 || i > L.length) return ERROR;	// i值不合法
	e = L.elem[i - 1];						// 被删除元素的值赋给e
	for (j = i; j < L.length; j++) {
		L.elem[j - 1] = L.elem[j];			// 被删除元素之后的元素前移
	}
	--L.length;								// 表长减1
	return OK;
}

// ListLength(L): 返回L中数据元素的个数
Status ListLength(SqList L) {
	return L.length;
}
// ------------------------------------------------------------------------------------------------------------

////union 并集
//void union_Sq(SqList La, SqList Lb, SqList &Lc){
//	int La_len = ListLength(La);
//	int Lb_len = ListLength(Lb);
//	Lc = La;
//	for (int i = 1; i <= Lb_len; i++){
//		ElemType e;
//		GetElem_Sq(Lb, i, e);
//		ElemType p = LocateElem_Sq(La, e);
//		if (p == 0)							//如果La中没有e
//			ListInsert_Sq(Lc, ListLength(Lc) + 1, e);
//	}
//}

//union 并集
void union_Sq(SqList& La, SqList Lb){
	int La_len = ListLength(La);
	int Lb_len = ListLength(Lb);
	for (int i = 1; i <= Lb_len; i++){
		ElemType e;
		GetElem_Sq(Lb, i, e);
		ElemType p = LocateElem_Sq(La, e);
		if (p == 0)							//如果La中没有e
			ListInsert_Sq(La, La_len + 1, e);
	}
}

//Mix 交集
void Mix_Sq(SqList La, SqList Lb, SqList& Lc) {
	int La_len = ListLength(La);
	int Lb_len = ListLength(Lb);
	for (int i = 1; i <= La_len; i++) {
		ElemType e;
		GetElem_Sq(La, i, e);
		ElemType p = LocateElem_Sq(Lb, e);
		if (p == 0)							//如果Lb中没有e
			ListDelete_Sq(Lc, i, e);
	}
}

//求解A= A ∩（ B ∪ C ）
int main() {
	SqList La, Lb, Lc, TEMP;
	InitList_Sq(La);
	InitList_Sq(Lb);
	InitList_Sq(Lc);
	InitList_Sq(TEMP);

	//输入集合A
	printf("请输入集合A：\n");
	ElemType e;
	scanf("%d", &e);
	while (e != 0) {
		ListInsert_Sq(La, ListLength(La) + 1, e);
		scanf("%d", &e);
	}

	//输入集合B
	printf("请输入集合B：\n");
	scanf("%d", &e);
	while (e != 0) {
		ListInsert_Sq(Lb, ListLength(Lb) + 1, e);
		scanf("%d", &e);
	}
		
	//输入集合C
	printf("请输入集合C：\n");
	scanf("%d", &e);
	while (e != 0) {
		ListInsert_Sq(Lc, ListLength(Lc) + 1, e);
		scanf("%d", &e);
	}
		
	//输出集合A
	printf("集合A：");
	for (int i = 1; i <= ListLength(La); i++) {
		GetElem_Sq(La, i, e);
		printf("%d ", e);
	}
	printf("\n");

	//输出集合B
	printf("集合B：");
	for (int i = 1; i <= ListLength(Lb); i++) {
		GetElem_Sq(Lb, i, e);
		printf("%d ", e);
	}
	printf("\n");

	//输出集合C
	printf("集合C：");
	for (int i = 1; i <= ListLength(Lc); i++) {
		GetElem_Sq(Lc, i, e);
		printf("%d ", e);
	}
	printf("\n");

	//求解A= A ∩（ B ∪ C ）
	union_Sq(Lb, Lc);
	Mix_Sq(La, Lb, La);

	//输出结果集A
	printf("结果集A：");
	for (int i = 1; i <= ListLength(La); i++) {
		GetElem_Sq(La, i, e);
		printf("%d ", e);
	}
	printf("\n");

	return 0;
}