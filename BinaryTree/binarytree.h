/*
** 二叉树节点类型
*/
typedef struct BTNode
{
	int value;
	BTNode* p_left;
	BTNode* p_right;
};

/*
** 二叉树
*/
typedef struct BTNode* BinaryTree;

/*
** 初始化二叉树
*/
void InitBTree(BTNode** tree);

/*
** 先序 递归 遍历二叉树
*/
void PreOrder(BinaryTree tree);

/*
** 中序 递归 遍历二叉树
*/
void MidOrder(BinaryTree tree);

/*
** 后序 递归 遍历二叉树
*/
void PostOrder(BinaryTree tree);

/*
** 先序 非递归 遍历二叉树
*/
void PreOrder_NoneRec(BinaryTree tree);

/*
** 中序 非递归 遍历二叉树
*/
void MidOrder_NoneRec(BinaryTree tree);

/*
** 后序 非递归 遍历二叉树
*/
void PostOrder_NoneRec_2(BinaryTree tree);

/*
** 后序 非递归遍历 使用
*/
typedef struct PostOrderNoneRecNode
{
	BTNode* bt_node;
	int int_flag;
};

/*
** 后序 非递归 遍历二叉树
*/
void PostOrder_NoneRec(BinaryTree tree);

/*
** 层次遍历
*/
void LevelOrder(BinaryTree tree);

/*
** 计算二叉树深度
*/
int DeepComputing(BinaryTree tree);

/*
** 根据先序和中序遍历重构二叉树
** 参数：
** preorder: 先序遍历结果数组
** midorder: 中序遍历结果数组
** lenght: 数组长度
*/
BTNode* Construct(int* preorder, int* midorder, int lenght);

/*
** 重构递归函数
** 参数：
** s_preorder: 先序遍历数组起始指针
** e_preorder: 先序遍历数组结束指针
** s_midorder: 中序遍历数组起始指针
** e_midorder: 中序遍历数组结束指针
*/
BTNode* ConstructCore(int* s_preorder, int* e_preorder, int* s_midorder, int* e_midorder);

/*
** 重构递归函数
** 参数：
** s_preorder: 先序遍历数组起始指针
** e_preorder: 先序遍历数组结束指针
** s_midorder: 中序遍历数组起始指针
** e_midorder: 中序遍历数组结束指针
*/
BTNode* MyConstruct(int* s_preorder, int* e_preorder, int* s_midorder, int* e_midorder);