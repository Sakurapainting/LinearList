#define _CRT_SECURE_NO_WARNINGS
/*
��д���������������A��B��C�ļ������㣬ʹ�ã�A= A �ɣ� B �� C ����
	��1�����Ҫ��ʹ�����Ա��˳��洢�ṹ��ʾ����A��B��C����ʵ��˳���Ļ��������������û������������ɼ��ϵ����㡣
	��2���������Ҫ�����������е�Ԫ��Ϊ�������ֱ����û����뼯���е����ݣ���0��Ϊ���������ԭ�е��������ϵ�Ԫ�أ�������A�е�Ԫ�ء�
���磺 �������� ����A��
					2  5  6  4  0
				   ����B��
					1  4  2   0
					����C��
					2  5  3   0
		�����ʾ	����A��2  5  6  4
					����B��1  4  2
					����C��2  5  3
					�����A��2  5   4

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

// ˳���� ˳��洢 �ṹ����
typedef struct {
	ElemType* elem;   //�洢�ռ��ַ
	int listsize;     //��ǰ����洢����
	int length;       //˳�����
}SqList; 

// ��ʼ��˳���
Status InitList_Sq(SqList& L) {
	L.elem = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = INIT_SIZE;
	return OK;
}

// ȡֵ ������Ա�L���ڵ�i��Ԫ�أ�����e������ֵ
Status GetElem_Sq(SqList L, int i, ElemType& e) {
	if (i < 1 || i > L.length) return ERROR;	// iֵ���Ϸ�
	e = L.elem[i - 1];
	return OK;
}

//LocateElem(L, e): ��L�в��������ֵe��ȵ�Ԫ�أ�������ҳɹ������ظ�Ԫ����L�е�λ�򣬷��򷵻�0
int LocateElem_Sq(SqList L, ElemType e) {
	int i;
	for (i = 0; i < L.length; i++) {
		if (L.elem[i] == e) return i + 1;
	}
	return 0;
}

//ListInsert_Sq(L, i, e): ��L���ڣ���i��1��n+1֮�䣬����L�е�i��λ�� ��֮ǰ�� �����µ�Ԫ��e��L�ĳ��ȼ�1
Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	int j;
	if (i < 1 || i > L.length + 1) return ERROR;	// iֵ���Ϸ�
	// ��ǰ�洢�ռ����������ӷ���
	if (L.length >= L.listsize) {
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);	// �洢����ʧ��
		L.elem = newbase;				// �»�ַ
		L.listsize += LISTINCREMENT;	// ���Ӵ洢����
	}
	for (j = L.length - 1; j >= i - 1; j--) {
		L.elem[j + 1] = L.elem[j];		// ����λ�ü�֮���Ԫ�غ���
	}
	L.elem[i - 1] = e;					// ����e
	++L.length;							// ����1
	return OK;
}

// ListDelete_Sq(L, i, e): ��L������i��1��n֮�䣬��ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
	int j;
	if (i < 1 || i > L.length) return ERROR;	// iֵ���Ϸ�
	e = L.elem[i - 1];						// ��ɾ��Ԫ�ص�ֵ����e
	for (j = i; j < L.length; j++) {
		L.elem[j - 1] = L.elem[j];			// ��ɾ��Ԫ��֮���Ԫ��ǰ��
	}
	--L.length;								// ����1
	return OK;
}

// ListLength(L): ����L������Ԫ�صĸ���
Status ListLength(SqList L) {
	return L.length;
}
// ------------------------------------------------------------------------------------------------------------

////union ����
//void union_Sq(SqList La, SqList Lb, SqList &Lc){
//	int La_len = ListLength(La);
//	int Lb_len = ListLength(Lb);
//	Lc = La;
//	for (int i = 1; i <= Lb_len; i++){
//		ElemType e;
//		GetElem_Sq(Lb, i, e);
//		ElemType p = LocateElem_Sq(La, e);
//		if (p == 0)							//���La��û��e
//			ListInsert_Sq(Lc, ListLength(Lc) + 1, e);
//	}
//}

//union ����
void union_Sq(SqList& La, SqList Lb){
	int La_len = ListLength(La);
	int Lb_len = ListLength(Lb);
	for (int i = 1; i <= Lb_len; i++){
		ElemType e;
		GetElem_Sq(Lb, i, e);
		ElemType p = LocateElem_Sq(La, e);
		if (p == 0)							//���La��û��e
			ListInsert_Sq(La, La_len + 1, e);
	}
}

//Mix ����
void Mix_Sq(SqList La, SqList Lb, SqList& Lc) {
	int La_len = ListLength(La);
	int Lb_len = ListLength(Lb);
	for (int i = 1; i <= La_len; i++) {
		ElemType e;
		GetElem_Sq(La, i, e);
		ElemType p = LocateElem_Sq(Lb, e);
		if (p == 0)							//���Lb��û��e
			ListDelete_Sq(Lc, i, e);
	}
}

//���A= A �ɣ� B �� C ��
int main() {
	SqList La, Lb, Lc, TEMP;
	InitList_Sq(La);
	InitList_Sq(Lb);
	InitList_Sq(Lc);
	InitList_Sq(TEMP);

	//���뼯��A
	printf("�����뼯��A��\n");
	ElemType e;
	scanf("%d", &e);
	while (e != 0) {
		ListInsert_Sq(La, ListLength(La) + 1, e);
		scanf("%d", &e);
	}

	//���뼯��B
	printf("�����뼯��B��\n");
	scanf("%d", &e);
	while (e != 0) {
		ListInsert_Sq(Lb, ListLength(Lb) + 1, e);
		scanf("%d", &e);
	}
		
	//���뼯��C
	printf("�����뼯��C��\n");
	scanf("%d", &e);
	while (e != 0) {
		ListInsert_Sq(Lc, ListLength(Lc) + 1, e);
		scanf("%d", &e);
	}
		
	//�������A
	printf("����A��");
	for (int i = 1; i <= ListLength(La); i++) {
		GetElem_Sq(La, i, e);
		printf("%d ", e);
	}
	printf("\n");

	//�������B
	printf("����B��");
	for (int i = 1; i <= ListLength(Lb); i++) {
		GetElem_Sq(Lb, i, e);
		printf("%d ", e);
	}
	printf("\n");

	//�������C
	printf("����C��");
	for (int i = 1; i <= ListLength(Lc); i++) {
		GetElem_Sq(Lc, i, e);
		printf("%d ", e);
	}
	printf("\n");

	//���A= A �ɣ� B �� C ��
	union_Sq(Lb, Lc);
	Mix_Sq(La, Lb, La);

	//��������A
	printf("�����A��");
	for (int i = 1; i <= ListLength(La); i++) {
		GetElem_Sq(La, i, e);
		printf("%d ", e);
	}
	printf("\n");

	return 0;
}