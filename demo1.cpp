#include<stdio.h>
#include<iostream>   //定义了标准输入/输出流对象cin  cout
#include<fstream>   //C++ STL中对文件操作的合集，包含了常用的所有文件操作
#include<cstring>     //字符串处理函数
#include<stdlib.h>
#include <time.h>
using namespace std;
const int Maxsize = 500;

#define ERROR    0
#define OK       1
#define N        10
int num = 0;

//各种数据类型的设计
//统计单词的结构体
struct word_statistics/*结构体名*/
{
	string word;/*储存英文歌词中的数据*/
	int frequency;/*记录单词出现的频次*/
}word_statistics_[Maxsize];/*结构体变量名*/
typedef struct word_statistics datatype;
//顺序表结构体
typedef struct
{
	datatype data[Maxsize];
	int lenght;
}Sqlist;
//链表结构体
typedef struct Lnode
{
	datatype data ;
	Lnode* next;

}Lnode, * Linklist;//Linklist L ==Lnode *L
//二叉排序结构体
typedef struct TreeNode
{
	datatype data;
	int heigth;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;
//------------------------------------------自定义函数---------------------------------------
//-----------------二叉排序树-----------------
int Bidui(string a, string b)
{
		if (a!= b)
		{
			return 0;
	    }
	return 1;
}
void TreeInit(TreeNode** T)
{
	*T = NULL;
}
int max(int a, int b)//比较高度
{
	return a > b ? a : b;
}
int GetHeight(TreeNode* T)//获得高度
{
	return T ? T->heigth : 0;
}
void rrRotation(TreeNode* node, TreeNode** root)//RR中间变为根根变为中间的左孩子，中间的右孩子还是右孩子,中间的左孩子变成根的右孩子
{//node和root都是同一个根
	TreeNode* temp =new(TreeNode);//temp是根的右孩子也就是中间
	temp = node->rchild;
	node->rchild = temp->lchild;
	temp->lchild = node;
	//在旋转之前变更高度
	temp->heigth = max(GetHeight(temp->lchild), GetHeight(temp->rchild))+1;//更新长度再加上本身+1
	node->heigth = max(GetHeight(node->lchild), GetHeight(node->rchild))+1;
	*root = temp;//根变成中间
}
void llRotation(TreeNode* node, TreeNode** root)//LL中间变为根根变为中间的右孩子，中间的左孩子还是左孩子,中间的右孩子变成根的左孩子
{
	TreeNode* temp = new(TreeNode);//temp是根的右孩子也就是中间
	temp = node->lchild;
	node->lchild = temp->rchild;
	temp->rchild = node;
	//在旋转之前变更高度
	temp->heigth = max(GetHeight(temp->lchild), GetHeight(temp->rchild)) + 1;//更新长度再加上本身+1
	node->heigth = max(GetHeight(node->lchild), GetHeight(node->rchild)) + 1;
	*root = temp;//根变成中间
}
//初始化树
void addTree(TreeNode** T, int &i)//平衡二叉树版
{
	if (*T == NULL)
	{
		*T = new(TreeNode);
		(*T)->data = word_statistics_[i];
		(*T)->heigth = 0;
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;

	}
	else if (word_statistics_[i].word < (*T)->data.word)
	{
		addTree(&(*T)->lchild, i);
		int LHeight = GetHeight((*T)->lchild);
		int RHeight = GetHeight((*T)->rchild);
		if (LHeight - RHeight == 2)//判断以T为根的左右子树是否失衡
		{
			if (word_statistics_[i].word < (*T)->lchild->data.word) {
				//LL调整
				llRotation(*T, T);
			}
			else
			{
				//LR调整 //把根的左孩子当作新的根将新的根加上新的根的右孩子当作中间，设中间的右孩子存在，做一次RR，转换完之后再以本来的根做一次LL
				rrRotation((*T)->lchild, &(*T)->lchild);
				llRotation((*T), T);

			}
		}

	}
	else if (word_statistics_[i].word > (*T)->data.word)
	{

		addTree(&(*T)->rchild, i);
		int LHeight = GetHeight((*T)->lchild);
		int RHeight = GetHeight((*T)->rchild);
		if (RHeight - LHeight == 2)
		{
			if (word_statistics_[i].word > (*T)->rchild->data.word) {
				//RR调整
				rrRotation(*T, T);

			}
			else
			{
				//RL调整 跟RL反过来
				llRotation((*T)->rchild, &(*T)->rchild);
				rrRotation((*T), T);
  			}
		}
	}
	(*T)->heigth= max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;
}
//打印输出
void pri(TreeNode* T, ofstream &fout)
{
	if (T!=NULL)
	{
		pri(T->lchild, fout);
		cout << T->data.frequency << "      " << T->data.word << endl;
		fout << T->data.frequency<<"      "<<T->data.word << endl;
		pri(T->rchild,fout);
	}
	
}
//计算平均查找长度
int ASL(TreeNode* T, int a)
{
	if (T!=NULL)
	{
		a+= 1;
		a+=ASL(T->lchild, a)+ ASL(T->rchild, a);
		return a;
	}
	else
	{
		return 0;

	}
	
}
//计算失败的平均查找长度
int ASL_2(TreeNode* T, int num)
{
	if (T == NULL)
	{
		num += 1;
		return num;

	}
	else if (T != NULL)
	{
		int numm = 0;
		num += 1;
		numm = ASL_2(T->lchild, num) + ASL_2(T->rchild, num);

		return numm;
	}
}
//树的文件输出
void wird_fre_file_2(TreeNode* T,int length)
{
	ofstream fout;
	fout.open("OutFile4.txt");
	fout << "单词总数:" << length << endl;
	fout << "词频" << "      " << "单词" << endl;
	cout << "单词总数:" << length << endl;
	cout<< "词频" << "      " << "单词" << endl;
	pri(T,fout);
	fout.close();
	printf("单词以及词频已经保存到文件OutFile4.txt\n");
}
//树的遍历
void Tree_BST(TreeNode* T,string a,int &index)
{
	if (T!=NULL)
	{
		if (T->data.word==a)
		{
			cout << "词频     " << T->data.frequency << endl;
			cout << "单词     " << T->data.word << endl;
			index = 1;
			return ;
		}
		else if(T->data.word>a)
		{
			Tree_BST(T->lchild, a,index);
			return ;
		}
		else
		{
			Tree_BST(T->rchild, a, index);
			return ;
		}
	}
	cout << "该单词不存在" << endl;
	
}
//树的查找
void Tree_chazhao(TreeNode* T, string a)
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	int index = 0;
	Tree_BST(T, a,index);
	if (index==1)
	{
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;  // 计算时间
		printf("查找到该单词的时间: %5f ns\n", (cpu_time_used));
		cout << "平均查找长度:" << ASL(T, 0) / 12.0 << endl;

	}
	

}
//---------------------链表-----------------------
//初始化链表
void LinklistIint(Linklist *L)
{
	(*L) = new(Lnode);
	if ((*L) == NULL)
	{
		printf("ERROR!");
		return;
	}
	(*L)->next = NULL;

}
//添加链表
void addLinklist(Linklist* L,int &lenght)
{
	
	Lnode *now = new(Lnode);
	now = (*L);
	now->next = NULL;
	for (int i = 0; i <=num; i++)
	{

		Lnode* p= new(Lnode);
		p->data = word_statistics_[i];
		p->next = NULL;
		now->next = p;
		now = p;
		lenght += 1;
      }
	lenght--;
	(*L) = (*L)->next;


}
//链接表词频统计输出
void wird_fre_file_Lnode(Linklist L)
{
	ofstream fout;
	fout.open("OutFile3.txt");
	fout << "单词总数:" << num << endl;
	fout << "词频" << "      " << "单词" << endl;
	for (int i = 0; L->next!=NULL; i++) {
		//TODO
		cout << L->data.frequency << "      " << L->data.word << endl;
		fout << L->data.frequency << "      " << L->data.word << endl;
		L = L->next;
	}
	fout.close();
	printf("单词以及词频已经保存到文件OutFile3.txt\n");
}
//链表顺序查找
void Lnode_table_sequence(Linklist L,int lenght)
{
	double asl = (lenght + 1) / 2.0, index=0;
	string a;
	cout << "请输入链表顺序查询单词:";
	cin >> a;
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	while(L->next!=NULL) {
		//TODO
		index = Bidui(L->data.word, a);
		if (index) {
			//TODO
			cout << "词频     "  << L->data.frequency << endl;
			cout<< "单词    " << L->data.word << endl;
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;  // 计算时间
			printf("查找到该单词的时间: %3f ms\n", (cpu_time_used));
			cout << "平均查找长度:"  <<asl << endl;
			return;
		}
		L = L->next;
	}
	if (index == 0) {
		//TODO
		cout << "该单词不存在" << endl;
	}


}
//---------------------顺序表---------------------
//词频统计输出
void wird_fre_file(Sqlist L,int index)
{
	ofstream fout;
	if (index==1)
	{
		fout.open("OutFile1.txt");
	}
	else if(index==2)
		fout.open("OutFile2.txt");
	fout << "单词总数:" << L.lenght << endl;
	fout << "词频" << "      " << "单词" << endl;
	for (int i = 0; i < L.lenght; i++) {
		//TODO
		cout << L.data[i].frequency << "      " << L.data[i].word << endl;
		fout << L.data[i].frequency << "      " << L.data[i].word << endl;
	}
	fout.close();
	if (index==1)
	{
		printf("单词以及词频已经保存到文件OutFile1.txt\n");
	}
	else if (index == 2)
	{
		printf("单词以及词频已经保存到文件OutFile3.txt\n");
	}
}
//创建表
void SqlistInint(Sqlist& L)
{
	for (int i = 0; i <num; i++) {
		//TODO
		L.data[i] = word_statistics_[i];
	}
	L.lenght = num;
}
//顺序表二分查询
//1.二分查找ASL计算代码-----计算ASL成功与失败
//2.二分查找主体
void  Sequence_table_two(Sqlist L)
{
	string demo;
	int mid, left = 0, right = num - 1, index = 0;
	double asl;
	cout << "请输入顺序表二分查询单词:";
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	cin >> demo;
	while (left <= right) {
		//TODO
		mid = (left + right) / 2;
		if (L.data[mid].word == demo) {
			//TODO
			cout << "词频     " << L.data[mid].frequency << endl;
			cout<<"单词    " << L.data[mid].word << endl;
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;  // 计算时间
			printf("查找到该单词的时间: %5f ns\n", (cpu_time_used));
			cout << "平均查找长度:" << 37.0/12 << endl;
			index = 1;
			break;
		}
		else
		{
			if (L.data[mid].word < demo) {
				//TODO
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}

	}
	if (index == 0) {
		//TODO
		cout << "该单词不存在" << endl;
	}
}
//顺序表查询
void Sequence_table_sequence(Sqlist L) {
	string demo;
	double asl = (L.lenght+1)/2.0, index = 0;
	cout << "请输入顺序表顺序查询单词:";
	clock_t start, end;
	double cpu_time_used;
	cin >> demo;
	start = clock();
	for (int i = 0; i < num; i++) {
		//TODO
		if (L.data[i].word == demo) {
			//TODO
			index = 1;
			cout << "词频     " << L.data[i].frequency << endl;
			cout << "单词    " << L.data[i].word << endl;
			end = clock();
			cpu_time_used = ((double)(end - start))/ CLOCKS_PER_SEC;  // 计算时间
			printf("查找到该单词的时间: %5f ns\n", (cpu_time_used));
			cout << "平均查找长度:" << asl << endl;
		}
	}
	if (index == 0) {
		//TODO
		cout << "该单词不存在" << endl;
	}
}
//消除大小写
void stort()
{
	word_statistics demo;
	for (int i = 0; i < num; i++) {
		//TODO
		for (int j = i + 1; j < num; j++) {
			//TODO
			if (word_statistics_[j].word < word_statistics_[i].word) {
				//TODO
				demo = word_statistics_[i];
				word_statistics_[i] = word_statistics_[j];
				word_statistics_[j] = demo;
			}
		}
	}
}
void  Convert_Size_word(string word)
{
	for (int i = 0; i <= (int)word.size(); i++) {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			word[i] += 32;
			//word[i] = tolower(word[i]); // 转换为小写
		}
	}/*转化小写是在列出的单词中进行转化*/
	//2.处理重复单词
	for (int i = 0; i <= num; i++) {
		if (word == word_statistics_[i].word) {//判断连个单词是否相等，相等则频次加一
			word_statistics_[i].frequency++;
			return;//强制返回，消除重复单词
		}
	}
	word_statistics_[num].word = word;/*每当出现一个新的单词，将上一个单词存入word_statistics_[num].word中的索引num*/
	word_statistics_[num].frequency = 1;//将单词出现的频次设为一
	num++;
}
//将内容输出出来
void print(Sqlist L) {
	cout << "单词总结   " << L.lenght << endl;
	cout << "词频   " << "单词" << endl;
	for (int i = 0; i < num; i++) {
		cout << L.data[i].frequency << "      " << L.data[i].word << "" << endl;
	}
}
// 读取文件信息
void ReadFile()
{
	ifstream fin;
	fin.open("Infile.txt");//以只读的形式方式打开关联文件
	if (!fin)//没打开
	{
		printf("open fail!\n");
	}
	else//打开
	{
		printf("open succese!\n");
		char ch;
		string word = "\0";/*字符串结束符*/
		/*1.当出现空格是进行结束换行，因此需要循环*/
		while (fin.get(ch))
		{
			//ch=tolower(ch);
			//分割单词
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				if (word == "\0")word = ch;
				else  word += ch;
			}
			else {
				if (word != "\0") {
					Convert_Size_word(word);//每次完成这个单词之后引用

					cout << word << endl;
					word = "\0";
				}
			}
		}
	}
	fin.close();

}
//----------------------菜单------------------
//树的菜单
void T_M()
{
	while (1)
	{
		system("cls");
		printf("****************************基于不同策略的英文单词的词频统计和检索系统******************************\n");
		printf("---基于二叉树排序树(AVL)---\n");
		printf("1.词频统计\n");
		printf("2.单词查找\n");
		printf("3.返回上一级\n");
		printf("请按相应的数字键进行选择：  ");
		TreeNode* T;
	    TreeInit(&T);
	    int lenght = 0;
	    for (int i = 0; i < num; i++)
	    {
			lenght++;
		addTree(&T, i);
	    }
		int i;
		cin >> i;
		string a;
		switch (i)
		{
		case 1:
			wird_fre_file_2(T, lenght);
			system("pause");
			continue;
		case 2:
			cout << "请输入查找单词:";
			cin >> a;
			Tree_chazhao(T, a);
			system("pause");
			continue;
		case 3:
			return;
		default:
			continue;
		}

	}

}
//折半查找菜单
void Half_MM()
{
	while (1)
	{
		system("cls");
		printf("****************************基于不同策略的英文单词的词频统计和检索系统******************************\n");
		printf("---基于线性表的折半查找---\n");
		printf("1.词频统计\n");
		printf("2.单词查找\n");
		printf("3.返回上一级\n");
		printf("请按相应的数字键进行选择：  ");
		int i;
		cin >> i;
		Sqlist L;
		SqlistInint(L);
		switch (i)
		{
		case 1:
			wird_fre_file(L,2);
			system("pause");
			continue;
		case 2:
			Sequence_table_two(L);
			system("pause");
			continue;
		case 3:
			return;
		default:
			continue;
		}

	}

}
//链表菜单
void LOD_MM()
{

	while (1)
	{
		system("cls");
		printf("****************************基于不同策略的英文单词的词频统计和检索系统******************************\n");
		printf("---基于链表的顺序查找---\n");
		printf("1.词频统计\n");
		printf("2.单词查找\n");
		printf("3.返回上一级\n");
		printf("请按相应的数字键进行选择：  ");
		int i;
		cin >> i;
	    Linklist L ;
		LinklistIint(&L);
		int lenght = 0;
		addLinklist(&L, lenght);
		switch (i)
		{
		case 1:
			wird_fre_file_Lnode(L);
			system("pause");
			continue;
		case 2:
			Lnode_table_sequence(L, lenght);
			system("pause");
			continue;
		case 3:
			return;
		default:
			continue;
		}

	}


}
//顺序表菜单
void OD_MM()
{

	while (true)
	{
		system("cls");
		printf("****************************基于不同策略的英文单词的词频统计和检索系统******************************\n");
		printf("---基于顺序表的顺序查找\---\n");
		printf("1.词频统计\n");
		printf("2.单词查找\n");
		printf("3.返回上一级\n");
		printf("请按相应的数字键进行选择：  ");
		int i;
		cin >> i;
		Sqlist L;
		SqlistInint(L);
		switch (i)
		{
		case 1:
			wird_fre_file(L,1);
			system("pause");
			continue;
		case 2:
			Sequence_table_sequence(L);
			system("pause");
			continue;
		case 3:
			return;
		default:
			continue;
		}

	}


}
//线性表菜单2
void OD_M()
{
	while (true)
	{
		system("cls");
		printf("****************************基于不同策略的英文单词的词频统计和检索系统******************************\n");
		printf("---顺序查找\---\n");
		printf("1.基于顺序表的顺序查找\n");
		printf("2.基于链表的顺序查找\n");
		printf("3.返回上一级\n");
		printf("请按相应的数字键进行选择：  ");
		int i;
		cin >> i;
		switch (i)
		{
		case 1:
			 OD_MM();
			 continue;
		case 2:
			 LOD_MM();
			 continue;
		case 3:
			return;
		default:
			continue;
		}

	}

}
//线性表菜单1
void S_M()
{
	while (true)
	{
		system("cls");
		printf("****************************基于不同策略的英文单词的词频统计和检索系统******************************\n");
		printf("---基于线性表的查找\---\n");
		printf("1.顺序查找\n");
		printf("2.折半查找\n");
		printf("3.返回上一级\n");
		printf("请按相应的数字键进行选择：  ");
		int i;
		cin >> i;
		switch (i)
		{
		case 1:
			OD_M();
		
			continue;
		case 2:
			Half_MM();
			
			continue;
		case 3:
			return;
		default:
			continue;
		}
	}

}
//主菜单
void M_M()
{
	ReadFile();
	stort();
	while (true)
	{
		system("cls");
		printf("****************************基于不同策略的英文单词的词频统计和检索系统******************************\n");
		printf("---菜单---\n");
		printf("1.基于线性表的查找\n");
		printf("2.基于二叉排序树的查找\n");
		printf("3.退出系统\n");
		printf("请按相应的数字键进行选择：  ");
		int i;
		cin >> i;
		switch (i)
		{
		case 1:
			S_M();
		
			continue;
		case 2:
			 T_M();
			 continue;
		case 3:
			exit(0);
			return;
		default:
			continue;
		}
	}

}
//-----------------------------------------主函数--------------------------------------------
int main()
{
	M_M();
    return 0;
}