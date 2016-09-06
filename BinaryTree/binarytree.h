/*
** �������ڵ�����
*/
typedef struct BTNode
{
	int value;
	BTNode* p_left;
	BTNode* p_right;
};

/*
** ������
*/
typedef struct BTNode* BinaryTree;

/*
** ��ʼ��������
*/
void InitBTree(BTNode** tree);

/*
** ���� �ݹ� ����������
*/
void PreOrder(BinaryTree tree);

/*
** ���� �ݹ� ����������
*/
void MidOrder(BinaryTree tree);

/*
** ���� �ݹ� ����������
*/
void PostOrder(BinaryTree tree);

/*
** ���� �ǵݹ� ����������
*/
void PreOrder_NoneRec(BinaryTree tree);

/*
** ���� �ǵݹ� ����������
*/
void MidOrder_NoneRec(BinaryTree tree);

/*
** ���� �ǵݹ� ����������
*/
void PostOrder_NoneRec_2(BinaryTree tree);

/*
** ���� �ǵݹ���� ʹ��
*/
typedef struct PostOrderNoneRecNode
{
	BTNode* bt_node;
	int int_flag;
};

/*
** ���� �ǵݹ� ����������
*/
void PostOrder_NoneRec(BinaryTree tree);

/*
** ��α���
*/
void LevelOrder(BinaryTree tree);

/*
** ������������
*/
int DeepComputing(BinaryTree tree);

/*
** �����������������ع�������
** ������
** preorder: ��������������
** midorder: ��������������
** lenght: ���鳤��
*/
BTNode* Construct(int* preorder, int* midorder, int lenght);

/*
** �ع��ݹ麯��
** ������
** s_preorder: �������������ʼָ��
** e_preorder: ��������������ָ��
** s_midorder: �������������ʼָ��
** e_midorder: ��������������ָ��
*/
BTNode* ConstructCore(int* s_preorder, int* e_preorder, int* s_midorder, int* e_midorder);

/*
** �ع��ݹ麯��
** ������
** s_preorder: �������������ʼָ��
** e_preorder: ��������������ָ��
** s_midorder: �������������ʼָ��
** e_midorder: ��������������ָ��
*/
BTNode* MyConstruct(int* s_preorder, int* e_preorder, int* s_midorder, int* e_midorder);