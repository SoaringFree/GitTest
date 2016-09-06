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

	printf("\n*********先序 递归*********\n");
	PreOrder(tree);
	printf("\n*********中序 递归*********\n");
	MidOrder(tree);
	printf("\n*********后序 递归*********\n");
	PostOrder(tree);

	printf("\n");
	printf("\n*********先序 非递归*********\n");
	PreOrder_NoneRec(tree);
	printf("\n*********中序 非递归*********\n");
	MidOrder_NoneRec(tree);
	printf("\n*********后序 非递归*********\n");
	PostOrder_NoneRec(tree);
	printf("\n");
	PostOrder_NoneRec_2(tree);

	printf("\n");
	printf("\n*********层次遍历*********\n");
	LevelOrder(tree);

	printf("\n");
	printf("\n*********深度计算*********\n");
	int deep = DeepComputing(tree);
	printf("---> 深度：%d ", deep);

	printf("\n");
	printf("\n*********二叉树重构*********\n");
	int preorder[8] = { 5, 2, 1, 4, 3, 7, 6, 8 };
	int midorder[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	printf("--->先序: 5, 2, 1, 4, 3, 7, 6, 8\n");
	printf("--->中序: 1, 2, 3, 4, 5, 6, 7, 8\n");
	printf("--->（重构）后序: ");
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
	思路：
	1、访问根节点
	2、将该节点入站，并访问左子树，直至无左子树
	3、获取栈顶元素（最后一个非空节点），出栈，并访问该节点的右子树
	*/
	if (tree == NULL)
		return;
	stack<BTNode*> s;

	while (tree || !s.empty())
	{
		if (tree != NULL)
		{
			// 入栈
			s.push(tree);
			// 访问该节点
			printf("%d ", tree->value);
			// 访问左子树
			tree = tree->p_left;
		}
		else
		{
			// 出栈
			tree = s.top();		// 关键语句，返回父结点
			s.pop();
			// 访问右子树
			tree = tree->p_right;
		}
	}
}

void MidOrder_NoneRec(BinaryTree tree)
{
	/*
	中序非递归遍历与先序非递归类似
	先序非递归遍历：在入栈时访问节点
	中序非递归遍历：在出栈时访问节点
	*/
	if (tree == NULL)
		return;
	stack<BTNode*> s;

	while (tree || !s.empty())
	{
		if (tree != NULL)
		{
			// 入栈
			s.push(tree);
			// 访问左子树
			tree = tree->p_left;
		}
		else
		{
			// 出栈
			tree = s.top();		// 关键语句，返回父结点
			// 访问该节点
			printf("%d ", tree->value);
			s.pop();
			// 访问右子树
			tree = tree->p_right;
		}
	}

}

void PostOrder_NoneRec(BinaryTree tree)
{
	/*
	思路：
	1、将根节点入栈，并将访问标记置1（表示第一次访问该节点）
	2、遍历左子树（入栈，标记置1），直至为空
	3、最后一个非空节点出栈（栈顶元素），检查标记
	   flag为1时：flag置为2，并再次将该节点入栈，并访问该节点的右子树
	   flag为2时：访问该节点
	*/
	if (tree == NULL)
		return;

	// 后序非递归遍历 临时节点类型
	stack<PostOrderNoneRecNode*> s;
	PostOrderNoneRecNode* temp = NULL;

	while (tree != NULL || !s.empty())
	{
		while (tree != NULL)
		{
			PostOrderNoneRecNode* p = (PostOrderNoneRecNode*)malloc(sizeof(PostOrderNoneRecNode));
			p->bt_node = tree;
			// 该节点第一次入站
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
				// 若该节点是第一次出现在栈顶
				// 修改标记，入栈
				temp->int_flag = 2;
				s.push(temp);

				// 访问该节点的右子树
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
	// 先序遍历第一个节点即为根节点
	int rootValue = s_preorder[0];
	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	root->value = rootValue;
	root->p_left = root->p_right = NULL;

	// 若先序遍历数组的起始指针与结束指针相同，本次递归结束
	if (s_preorder == e_preorder)
	{
		// 若此时中序遍历的起始地址与结束地址相同
		// 且该次递归的先序根节点与中序根节点相同（即本次递归根节点确定）
		// 则本次递归结束，返回该子树的根节点
		if (s_midorder == e_midorder && *s_preorder == *s_midorder)
			return root;
		else
			throw exception("输入数据错误！");
	}

	// 根据先序遍历的数组的首节点(本次递归的根节点)，在中序遍历中查找该子树的根节点
	int* rootMidorder = s_midorder;
	while (rootMidorder <= e_midorder && *rootMidorder != rootValue)
		++rootMidorder;

	// 若中序遍历中不存在该次循环的根节点，则错误
	if (rootMidorder == e_midorder && *rootMidorder != rootValue)
		throw exception("输入数据错误！");

	// 根据中序遍历结果中的根节点，确定该根节点的左右子树
	int leftLength = rootMidorder - s_midorder;
	int* leftPreorderEnd = s_preorder + leftLength;
	if (leftLength > 0)
	{
		// 构建左子树
		root->p_left = ConstructCore(s_preorder + 1, leftPreorderEnd, s_midorder, rootMidorder - 1);
	}
	if (leftLength < e_preorder - s_preorder)
	{
		// 构建右子树
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

	// 若先序遍历的结果中只含有一个节点时（即该节点为本次递归的根节点）
	if (s_preorder == e_preorder)
	{
		// 若此时中序遍历结果中有人只包含一个节点，且与先序遍历中节点值相等，则该节点得以确定，并返回
		if (s_midorder == e_midorder && *s_preorder == *s_midorder)
			return root;
		else
			throw exception("Input Error!");
	}

	// 确定中序遍历结果集中当前递归的根节点
	int* rootMidorder = s_midorder;
	while (rootMidorder < e_midorder && *rootMidorder != rootValue)
		++rootMidorder;

	// 如在中序遍历结果集中未找到本次遍历的根节点，则出错
	if (rootMidorder == e_midorder && *rootMidorder != rootValue)
		throw exception("Input Error!");

	// 本次递归左子树的长度（节点个数）
	int leftLength = rootMidorder - s_midorder;
	// 本次递归，在先序遍历结果集中左子树的结束地址
	int* leftPreorderEnd = s_preorder + leftLength;

	// 若存在左子树
	if (leftLength > 0)
	{
		// 先序左子树：
		// 起始地址：先序起始节点加1 
		// 结束地址：leftPreorderEnd
		//
		// 中序左子树：
		// 起始地址：原起始地址
		// 结束地址：中序根节点减1
		root->p_left = MyConstruct(s_preorder + 1, leftPreorderEnd, s_midorder, rootMidorder - 1);
	}

	// 若先序遍历的结果集中数据个数 大于 左子树个数
	// 则存在右子树
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

