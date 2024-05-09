#include<stdio.h>
#include<iostream>   //�����˱�׼����/���������cin  cout
#include<fstream>   //C++ STL�ж��ļ������ĺϼ��������˳��õ������ļ�����
#include<cstring>     //�ַ���������
#include<stdlib.h>
#include <time.h>
using namespace std;
const int Maxsize = 500;

#define ERROR    0
#define OK       1
#define N        10
int num = 0;

//�����������͵����
//ͳ�Ƶ��ʵĽṹ��
struct word_statistics/*�ṹ����*/
{
	string word;/*����Ӣ�ĸ���е�����*/
	int frequency;/*��¼���ʳ��ֵ�Ƶ��*/
}word_statistics_[Maxsize];/*�ṹ�������*/
typedef struct word_statistics datatype;
//˳���ṹ��
typedef struct
{
	datatype data[Maxsize];
	int lenght;
}Sqlist;
//����ṹ��
typedef struct Lnode
{
	datatype data ;
	Lnode* next;

}Lnode, * Linklist;//Linklist L ==Lnode *L
//��������ṹ��
typedef struct TreeNode
{
	datatype data;
	int heigth;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;
//------------------------------------------�Զ��庯��---------------------------------------
//-----------------����������-----------------
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
int max(int a, int b)//�Ƚϸ߶�
{
	return a > b ? a : b;
}
int GetHeight(TreeNode* T)//��ø߶�
{
	return T ? T->heigth : 0;
}
void rrRotation(TreeNode* node, TreeNode** root)//RR�м��Ϊ������Ϊ�м�����ӣ��м���Һ��ӻ����Һ���,�м�����ӱ�ɸ����Һ���
{//node��root����ͬһ����
	TreeNode* temp =new(TreeNode);//temp�Ǹ����Һ���Ҳ�����м�
	temp = node->rchild;
	node->rchild = temp->lchild;
	temp->lchild = node;
	//����ת֮ǰ����߶�
	temp->heigth = max(GetHeight(temp->lchild), GetHeight(temp->rchild))+1;//���³����ټ��ϱ���+1
	node->heigth = max(GetHeight(node->lchild), GetHeight(node->rchild))+1;
	*root = temp;//������м�
}
void llRotation(TreeNode* node, TreeNode** root)//LL�м��Ϊ������Ϊ�м���Һ��ӣ��м�����ӻ�������,�м���Һ��ӱ�ɸ�������
{
	TreeNode* temp = new(TreeNode);//temp�Ǹ����Һ���Ҳ�����м�
	temp = node->lchild;
	node->lchild = temp->rchild;
	temp->rchild = node;
	//����ת֮ǰ����߶�
	temp->heigth = max(GetHeight(temp->lchild), GetHeight(temp->rchild)) + 1;//���³����ټ��ϱ���+1
	node->heigth = max(GetHeight(node->lchild), GetHeight(node->rchild)) + 1;
	*root = temp;//������м�
}
//��ʼ����
void addTree(TreeNode** T, int &i)//ƽ���������
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
		if (LHeight - RHeight == 2)//�ж���TΪ�������������Ƿ�ʧ��
		{
			if (word_statistics_[i].word < (*T)->lchild->data.word) {
				//LL����
				llRotation(*T, T);
			}
			else
			{
				//LR���� //�Ѹ������ӵ����µĸ����µĸ������µĸ����Һ��ӵ����м䣬���м���Һ��Ӵ��ڣ���һ��RR��ת����֮�����Ա����ĸ���һ��LL
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
				//RR����
				rrRotation(*T, T);

			}
			else
			{
				//RL���� ��RL������
				llRotation((*T)->rchild, &(*T)->rchild);
				rrRotation((*T), T);
  			}
		}
	}
	(*T)->heigth= max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;
}
//��ӡ���
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
//����ƽ�����ҳ���
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
//����ʧ�ܵ�ƽ�����ҳ���
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
//�����ļ����
void wird_fre_file_2(TreeNode* T,int length)
{
	ofstream fout;
	fout.open("OutFile4.txt");
	fout << "��������:" << length << endl;
	fout << "��Ƶ" << "      " << "����" << endl;
	cout << "��������:" << length << endl;
	cout<< "��Ƶ" << "      " << "����" << endl;
	pri(T,fout);
	fout.close();
	printf("�����Լ���Ƶ�Ѿ����浽�ļ�OutFile4.txt\n");
}
//���ı���
void Tree_BST(TreeNode* T,string a,int &index)
{
	if (T!=NULL)
	{
		if (T->data.word==a)
		{
			cout << "��Ƶ     " << T->data.frequency << endl;
			cout << "����     " << T->data.word << endl;
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
	cout << "�õ��ʲ�����" << endl;
	
}
//���Ĳ���
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
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;  // ����ʱ��
		printf("���ҵ��õ��ʵ�ʱ��: %5f ns\n", (cpu_time_used));
		cout << "ƽ�����ҳ���:" << ASL(T, 0) / 12.0 << endl;

	}
	

}
//---------------------����-----------------------
//��ʼ������
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
//�������
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
//���ӱ��Ƶͳ�����
void wird_fre_file_Lnode(Linklist L)
{
	ofstream fout;
	fout.open("OutFile3.txt");
	fout << "��������:" << num << endl;
	fout << "��Ƶ" << "      " << "����" << endl;
	for (int i = 0; L->next!=NULL; i++) {
		//TODO
		cout << L->data.frequency << "      " << L->data.word << endl;
		fout << L->data.frequency << "      " << L->data.word << endl;
		L = L->next;
	}
	fout.close();
	printf("�����Լ���Ƶ�Ѿ����浽�ļ�OutFile3.txt\n");
}
//����˳�����
void Lnode_table_sequence(Linklist L,int lenght)
{
	double asl = (lenght + 1) / 2.0, index=0;
	string a;
	cout << "����������˳���ѯ����:";
	cin >> a;
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	while(L->next!=NULL) {
		//TODO
		index = Bidui(L->data.word, a);
		if (index) {
			//TODO
			cout << "��Ƶ     "  << L->data.frequency << endl;
			cout<< "����    " << L->data.word << endl;
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;  // ����ʱ��
			printf("���ҵ��õ��ʵ�ʱ��: %3f ms\n", (cpu_time_used));
			cout << "ƽ�����ҳ���:"  <<asl << endl;
			return;
		}
		L = L->next;
	}
	if (index == 0) {
		//TODO
		cout << "�õ��ʲ�����" << endl;
	}


}
//---------------------˳���---------------------
//��Ƶͳ�����
void wird_fre_file(Sqlist L,int index)
{
	ofstream fout;
	if (index==1)
	{
		fout.open("OutFile1.txt");
	}
	else if(index==2)
		fout.open("OutFile2.txt");
	fout << "��������:" << L.lenght << endl;
	fout << "��Ƶ" << "      " << "����" << endl;
	for (int i = 0; i < L.lenght; i++) {
		//TODO
		cout << L.data[i].frequency << "      " << L.data[i].word << endl;
		fout << L.data[i].frequency << "      " << L.data[i].word << endl;
	}
	fout.close();
	if (index==1)
	{
		printf("�����Լ���Ƶ�Ѿ����浽�ļ�OutFile1.txt\n");
	}
	else if (index == 2)
	{
		printf("�����Լ���Ƶ�Ѿ����浽�ļ�OutFile3.txt\n");
	}
}
//������
void SqlistInint(Sqlist& L)
{
	for (int i = 0; i <num; i++) {
		//TODO
		L.data[i] = word_statistics_[i];
	}
	L.lenght = num;
}
//˳�����ֲ�ѯ
//1.���ֲ���ASL�������-----����ASL�ɹ���ʧ��
//2.���ֲ�������
void  Sequence_table_two(Sqlist L)
{
	string demo;
	int mid, left = 0, right = num - 1, index = 0;
	double asl;
	cout << "������˳�����ֲ�ѯ����:";
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	cin >> demo;
	while (left <= right) {
		//TODO
		mid = (left + right) / 2;
		if (L.data[mid].word == demo) {
			//TODO
			cout << "��Ƶ     " << L.data[mid].frequency << endl;
			cout<<"����    " << L.data[mid].word << endl;
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;  // ����ʱ��
			printf("���ҵ��õ��ʵ�ʱ��: %5f ns\n", (cpu_time_used));
			cout << "ƽ�����ҳ���:" << 37.0/12 << endl;
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
		cout << "�õ��ʲ�����" << endl;
	}
}
//˳����ѯ
void Sequence_table_sequence(Sqlist L) {
	string demo;
	double asl = (L.lenght+1)/2.0, index = 0;
	cout << "������˳���˳���ѯ����:";
	clock_t start, end;
	double cpu_time_used;
	cin >> demo;
	start = clock();
	for (int i = 0; i < num; i++) {
		//TODO
		if (L.data[i].word == demo) {
			//TODO
			index = 1;
			cout << "��Ƶ     " << L.data[i].frequency << endl;
			cout << "����    " << L.data[i].word << endl;
			end = clock();
			cpu_time_used = ((double)(end - start))/ CLOCKS_PER_SEC;  // ����ʱ��
			printf("���ҵ��õ��ʵ�ʱ��: %5f ns\n", (cpu_time_used));
			cout << "ƽ�����ҳ���:" << asl << endl;
		}
	}
	if (index == 0) {
		//TODO
		cout << "�õ��ʲ�����" << endl;
	}
}
//������Сд
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
			//word[i] = tolower(word[i]); // ת��ΪСд
		}
	}/*ת��Сд�����г��ĵ����н���ת��*/
	//2.�����ظ�����
	for (int i = 0; i <= num; i++) {
		if (word == word_statistics_[i].word) {//�ж����������Ƿ���ȣ������Ƶ�μ�һ
			word_statistics_[i].frequency++;
			return;//ǿ�Ʒ��أ������ظ�����
		}
	}
	word_statistics_[num].word = word;/*ÿ������һ���µĵ��ʣ�����һ�����ʴ���word_statistics_[num].word�е�����num*/
	word_statistics_[num].frequency = 1;//�����ʳ��ֵ�Ƶ����Ϊһ
	num++;
}
//�������������
void print(Sqlist L) {
	cout << "�����ܽ�   " << L.lenght << endl;
	cout << "��Ƶ   " << "����" << endl;
	for (int i = 0; i < num; i++) {
		cout << L.data[i].frequency << "      " << L.data[i].word << "" << endl;
	}
}
// ��ȡ�ļ���Ϣ
void ReadFile()
{
	ifstream fin;
	fin.open("Infile.txt");//��ֻ������ʽ��ʽ�򿪹����ļ�
	if (!fin)//û��
	{
		printf("open fail!\n");
	}
	else//��
	{
		printf("open succese!\n");
		char ch;
		string word = "\0";/*�ַ���������*/
		/*1.�����ֿո��ǽ��н������У������Ҫѭ��*/
		while (fin.get(ch))
		{
			//ch=tolower(ch);
			//�ָ��
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				if (word == "\0")word = ch;
				else  word += ch;
			}
			else {
				if (word != "\0") {
					Convert_Size_word(word);//ÿ������������֮������

					cout << word << endl;
					word = "\0";
				}
			}
		}
	}
	fin.close();

}
//----------------------�˵�------------------
//���Ĳ˵�
void T_M()
{
	while (1)
	{
		system("cls");
		printf("****************************���ڲ�ͬ���Ե�Ӣ�ĵ��ʵĴ�Ƶͳ�ƺͼ���ϵͳ******************************\n");
		printf("---���ڶ�����������(AVL)---\n");
		printf("1.��Ƶͳ��\n");
		printf("2.���ʲ���\n");
		printf("3.������һ��\n");
		printf("�밴��Ӧ�����ּ�����ѡ��  ");
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
			cout << "��������ҵ���:";
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
//�۰���Ҳ˵�
void Half_MM()
{
	while (1)
	{
		system("cls");
		printf("****************************���ڲ�ͬ���Ե�Ӣ�ĵ��ʵĴ�Ƶͳ�ƺͼ���ϵͳ******************************\n");
		printf("---�������Ա���۰����---\n");
		printf("1.��Ƶͳ��\n");
		printf("2.���ʲ���\n");
		printf("3.������һ��\n");
		printf("�밴��Ӧ�����ּ�����ѡ��  ");
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
//����˵�
void LOD_MM()
{

	while (1)
	{
		system("cls");
		printf("****************************���ڲ�ͬ���Ե�Ӣ�ĵ��ʵĴ�Ƶͳ�ƺͼ���ϵͳ******************************\n");
		printf("---���������˳�����---\n");
		printf("1.��Ƶͳ��\n");
		printf("2.���ʲ���\n");
		printf("3.������һ��\n");
		printf("�밴��Ӧ�����ּ�����ѡ��  ");
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
//˳���˵�
void OD_MM()
{

	while (true)
	{
		system("cls");
		printf("****************************���ڲ�ͬ���Ե�Ӣ�ĵ��ʵĴ�Ƶͳ�ƺͼ���ϵͳ******************************\n");
		printf("---����˳����˳�����\---\n");
		printf("1.��Ƶͳ��\n");
		printf("2.���ʲ���\n");
		printf("3.������һ��\n");
		printf("�밴��Ӧ�����ּ�����ѡ��  ");
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
//���Ա�˵�2
void OD_M()
{
	while (true)
	{
		system("cls");
		printf("****************************���ڲ�ͬ���Ե�Ӣ�ĵ��ʵĴ�Ƶͳ�ƺͼ���ϵͳ******************************\n");
		printf("---˳�����\---\n");
		printf("1.����˳����˳�����\n");
		printf("2.���������˳�����\n");
		printf("3.������һ��\n");
		printf("�밴��Ӧ�����ּ�����ѡ��  ");
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
//���Ա�˵�1
void S_M()
{
	while (true)
	{
		system("cls");
		printf("****************************���ڲ�ͬ���Ե�Ӣ�ĵ��ʵĴ�Ƶͳ�ƺͼ���ϵͳ******************************\n");
		printf("---�������Ա�Ĳ���\---\n");
		printf("1.˳�����\n");
		printf("2.�۰����\n");
		printf("3.������һ��\n");
		printf("�밴��Ӧ�����ּ�����ѡ��  ");
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
//���˵�
void M_M()
{
	ReadFile();
	stort();
	while (true)
	{
		system("cls");
		printf("****************************���ڲ�ͬ���Ե�Ӣ�ĵ��ʵĴ�Ƶͳ�ƺͼ���ϵͳ******************************\n");
		printf("---�˵�---\n");
		printf("1.�������Ա�Ĳ���\n");
		printf("2.���ڶ����������Ĳ���\n");
		printf("3.�˳�ϵͳ\n");
		printf("�밴��Ӧ�����ּ�����ѡ��  ");
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
//-----------------------------------------������--------------------------------------------
int main()
{
	M_M();
    return 0;
}