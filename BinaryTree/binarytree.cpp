#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <exception>
#include "binarytree.h"

using namespace std;

int main(int argc, char *argv[])
{
	BinaryTree tree = NULL;
	InitBTree(&tree);

	printf("\n*********���� �ݹ�*********\n");
	PreOrder(tree);
	printf("\n*********���� �ݹ�*********\n");
	MidOrder(tree);
	printf("\n*********���� �ݹ�*********\n");
	PostOrder(tree);

	printf("\n");
	printf("\n*********���� �ǵݹ�*********\n");
	PreOrder_NoneRec(tree);
	printf("\n*********���� �ǵݹ�*********\n");
	MidOrder_NoneRec(tree);
	printf("\n*********���� �ǵݹ�*********\n");
	PostOrder_NoneRec(tree);
	printf("\n");
	PostOrder_NoneRec_2(tree);

	printf("\n");
	printf("\n*********��α���*********\n");
	LevelOrder(tree);

	printf("\n");
	printf("\n*********��ȼ���*********\n");
	int deep = DeepComputing(tree);
	printf("---> ��ȣ�%d ", deep);

	printf("\n");
	printf("\n*********�������ع�*********\n");
	int preorder[8] = { 5, 2, 1, 4, 3, 7, 6, 8 };
	int midorder[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	printf("--->����: 5, 2, 1, 4, 3, 7, 6, 8\n");
	printf("--->����: 1, 2, 3, 4, 5, 6, 7, 8\n");
	printf("--->���ع�������: ");
	BinaryTree r_tree = NULL;
	try
	{
		r_tree = Construct(preorder, midorder, 8);
	}
	catch (exception e)
	{
		printf(e.what());
	}
	PostOrder(r_tree);


	printf("\n\n");
	system("pause");
}


void PreOrder(BinaryTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->value);
		PreOrder(tree->p_left);
		PreOrder(tree->p_right);
	}
}

void MidOrder(BinaryTree tree)
{
	if (tree != NULL)
	{
		MidOrder(tree->p_left);
		printf("%d ", tree->value);
		MidOrder(tree->p_right);
	}
}

void PostOrder(BinaryTree tree)
{
	if (tree != NULL)
	{
		PostOrder(tree->p_left);
		PostOrder(tree->p_right);
		printf("%d ", tree->value);
	}
}

void PreOrder_NoneRec(BinaryTree tree)
{
	/*
	˼·��
	1�����ʸ��ڵ�
	2�����ýڵ���վ����������������ֱ����������
	3����ȡջ��Ԫ�أ����һ���ǿսڵ㣩����ջ�������ʸýڵ��������
	*/
	if (tree == NULL)
		return;
	stack<BTNode*> s;

	while (tree || !s.empty())
	{
		if (tree != NULL)
		{
			// ��ջ
			s.push(tree);
			// ���ʸýڵ�
			printf("%d ", tree->value);
			// ����������
			tree = tree->p_left;
		}
		else
		{
			// ��ջ
			tree = s.top();		// �ؼ���䣬���ظ����
			s.pop();
			// ����������
			tree = tree->p_right;
		}
	}
}

void MidOrder_NoneRec(BinaryTree tree)
{
	/*
	����ǵݹ����������ǵݹ�����
	����ǵݹ����������ջʱ���ʽڵ�
	����ǵݹ�������ڳ�ջʱ���ʽڵ�
	*/
	if (tree == NULL)
		return;
	stack<BTNode*> s;

	while (tree || !s.empty())
	{
		if (tree != NULL)
		{
			// ��ջ
			s.push(tree);
			// ����������
			tree = tree->p_left;
		}
		else
		{
			// ��ջ
			tree = s.top();		// �ؼ���䣬���ظ����
			// ���ʸýڵ�
			printf("%d ", tree->value);
			s.pop();
			// ����������
			tree = tree->p_right;
		}
	}

}

void PostOrder_NoneRec(BinaryTree tree)
{
	/*
	˼·��
	1�������ڵ���ջ���������ʱ����1����ʾ��һ�η��ʸýڵ㣩
	2����������������ջ�������1����ֱ��Ϊ��
	3�����һ���ǿսڵ��ջ��ջ��Ԫ�أ��������
	   flagΪ1ʱ��flag��Ϊ2�����ٴν��ýڵ���ջ�������ʸýڵ��������
	   flagΪ2ʱ�����ʸýڵ�
	*/
	if (tree == NULL)
		return;

	// ����ǵݹ���� ��ʱ�ڵ�����
	stack<PostOrderNoneRecNode*> s;
	PostOrderNoneRecNode* temp = NULL;

	while (tree != NULL || !s.empty())
	{
		while (tree != NULL)
		{
			PostOrderNoneRecNode* p = (PostOrderNoneRecNode*)malloc(sizeof(PostOrderNoneRecNode));
			p->bt_node = tree;
			// �ýڵ��һ����վ
			p->int_flag = 1;
			s.push(p);

			tree = tree->p_left;
		}
		if (!s.empty())
		{
			temp = s.top();
			s.pop();
			
			if (temp->int_flag == 1)
			{
				// ���ýڵ��ǵ�һ�γ�����ջ��
				// �޸ı�ǣ���ջ
				temp->int_flag = 2;
				s.push(temp);

				// ���ʸýڵ��������
				tree = temp->bt_node->p_right;
			}
			else
			{
				printf("%d ", temp->bt_node->value);
			}
		}
	}


}

void PostOrder_NoneRec_2(BinaryTree tree)
{
	if (NULL == tree)
		return;

	BTNode *p = tree;
	stack<BTNode *> st;
	st.push(p);
	st.push(p);

	while (!st.empty())
	{
		p = st.top();
		st.pop();
		if (!st.empty() && p == st.top())
		{
			if (p->p_right)
			{
				st.push(p->p_right);
				st.push(p->p_right);
			}
			if (p->p_left)
			{
				st.push(p->p_left);
				st.push(p->p_left);
			}
		}
		else
			printf("%d ", p->value);
	}
	printf("\n");
	return;
}

void LevelOrder(BinaryTree tree)
{
	if (tree == NULL)
		return;
	queue<BTNode*> q;
	q.push(tree);
	while (!q.empty())
	{
		tree = q.front();
		printf("%d ", tree->value);
		q.pop();

		if (tree->p_left != NULL)
			q.push(tree->p_left);
		
		if (tree->p_right != NULL)
			q.push(tree->p_right);
	}
}

int DeepComputing(BinaryTree tree)
{
	int hight, h_left, h_right;
	if (tree == NULL)
		return 0;

	h_left = DeepComputing(tree->p_left);
	h_right = DeepComputing(tree->p_right);

	hight = (h_left > h_right ? h_left : h_right) + 1;
	return hight;
}

BTNode* Construct(int* preorder, int* midorder, int lenght)
{
	if (preorder == NULL || midorder == NULL || lenght <= 0)
		return NULL;
	//return ConstructCore(preorder, preorder + lenght - 1, midorder, midorder + lenght - 1);
	return MyConstruct(preorder, preorder + lenght - 1, midorder, midorder + lenght - 1);
}

BTNode* ConstructCore(int* s_preorder, int* e_preorder, int* s_midorder, int* e_midorder)
{
	// ���������һ���ڵ㼴Ϊ���ڵ�
	int rootValue = s_preorder[0];
	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	root->value = rootValue;
	root->p_left = root->p_right = NULL;

	// ����������������ʼָ�������ָ����ͬ�����εݹ����
	if (s_preorder == e_preorder)
	{
		// ����ʱ�����������ʼ��ַ�������ַ��ͬ
		// �Ҹôεݹ��������ڵ���������ڵ���ͬ�������εݹ���ڵ�ȷ����
		// �򱾴εݹ���������ظ������ĸ��ڵ�
		if (s_midorder == e_midorder && *s_preorder == *s_midorder)
			return root;
		else
			throw exception("�������ݴ���");
	}

	// �������������������׽ڵ�(���εݹ�ĸ��ڵ�)������������в��Ҹ������ĸ��ڵ�
	int* rootMidorder = s_midorder;
	while (rootMidorder <= e_midorder && *rootMidorder != rootValue)
		++rootMidorder;

	// ����������в����ڸô�ѭ���ĸ��ڵ㣬�����
	if (rootMidorder == e_midorder && *rootMidorder != rootValue)
		throw exception("�������ݴ���");

	// ���������������еĸ��ڵ㣬ȷ���ø��ڵ����������
	int leftLength = rootMidorder - s_midorder;
	int* leftPreorderEnd = s_preorder + leftLength;
	if (leftLength > 0)
	{
		// ����������
		root->p_left = ConstructCore(s_preorder + 1, leftPreorderEnd, s_midorder, rootMidorder - 1);
	}
	if (leftLength < e_preorder - s_preorder)
	{
		// ����������
		root->p_right = ConstructCore(leftPreorderEnd + 1, e_preorder, rootMidorder + 1, e_midorder);
	}

	return root;
}

BTNode* MyConstruct(int* s_preorder, int* e_preorder, int* s_midorder, int* e_midorder)
{
	int rootValue = s_preorder[0];
	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	root->value = rootValue;
	root->p_left = root->p_right = NULL;

	// ����������Ľ����ֻ����һ���ڵ�ʱ�����ýڵ�Ϊ���εݹ�ĸ��ڵ㣩
	if (s_preorder == e_preorder)
	{
		// ����ʱ����������������ֻ����һ���ڵ㣬������������нڵ�ֵ��ȣ���ýڵ����ȷ����������
		if (s_midorder == e_midorder && *s_preorder == *s_midorder)
			return root;
		else
			throw exception("Input Error!");
	}

	// ȷ���������������е�ǰ�ݹ�ĸ��ڵ�
	int* rootMidorder = s_midorder;
	while (rootMidorder < e_midorder && *rootMidorder != rootValue)
		++rootMidorder;

	// ������������������δ�ҵ����α����ĸ��ڵ㣬�����
	if (rootMidorder == e_midorder && *rootMidorder != rootValue)
		throw exception("Input Error!");

	// ���εݹ��������ĳ��ȣ��ڵ������
	int leftLength = rootMidorder - s_midorder;
	// ���εݹ飬�����������������������Ľ�����ַ
	int* leftPreorderEnd = s_preorder + leftLength;

	// ������������
	if (leftLength > 0)
	{
		// ������������
		// ��ʼ��ַ��������ʼ�ڵ��1 
		// ������ַ��leftPreorderEnd
		//
		// ������������
		// ��ʼ��ַ��ԭ��ʼ��ַ
		// ������ַ��������ڵ��1
		root->p_left = MyConstruct(s_preorder + 1, leftPreorderEnd, s_midorder, rootMidorder - 1);
	}

	// ����������Ľ���������ݸ��� ���� ����������
	// �����������
	// if (leftLength < e_preorder - s_preorder)
	if (rootMidorder < e_midorder)
	{
		root->p_right = MyConstruct(leftPreorderEnd + 1, e_preorder, rootMidorder + 1, e_midorder);
	}

	return root;
}

void InitBTree(BTNode** tree)
{
	BTNode* t = (BTNode*)malloc(sizeof(BTNode));
	t->value = 10;
	t->p_left = NULL;
	t->p_right = NULL;

	BTNode* t1 = (BTNode*)malloc(sizeof(BTNode));
	t1->value = 6;
	t1->p_left = NULL;
	t1->p_right = NULL;

	BTNode* t2 = (BTNode*)malloc(sizeof(BTNode));
	t2->value = 14;
	t2->p_left = NULL;
	t2->p_right = NULL;

	BTNode* t3 = (BTNode*)malloc(sizeof(BTNode));
	t3->value = 4;
	t3->p_left = NULL;
	t3->p_right = NULL;

	BTNode* t4 = (BTNode*)malloc(sizeof(BTNode));
	t4->value = 8;
	t4->p_left = NULL;
	t4->p_right = NULL;

	BTNode* t5 = (BTNode*)malloc(sizeof(BTNode));
	t5->value = 12;
	t5->p_left = NULL;
	t5->p_right = NULL;

	BTNode* t6 = (BTNode*)malloc(sizeof(BTNode));
	t6->value = 16;
	t6->p_left = NULL;
	t6->p_right = NULL;

	BTNode* t7 = (BTNode*)malloc(sizeof(BTNode));
	t7->value = 20;
	t7->p_left = NULL;
	t7->p_right = NULL;

	t->p_left = t1;
	t->p_right = t2;

	t1->p_left = t3;
	t1->p_right = t4;

	t2->p_left = t5;
	t2->p_right = t6;

	t6->p_right = t7;

	(*tree) = t;
}

