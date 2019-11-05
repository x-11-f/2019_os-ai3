#include<queue>
#include<iostream>

#include "stdlib.h" 
#include "time.h" 
#include<stack>
using namespace std;
#define num 9
struct Node{
	int state[9];
	struct Node* parent;
	int value;
	int depth;
	friend bool operator < (Node A, Node B) //����valueֵС�ķ����������ȼ�����
	{
		return A.value > B.value;
	}
};

priority_queue<Node> openTable;     //open��
queue<Node> closeTable;     //close��
stack<Node> Path;     //����·��
int count1=0,count2=0;

int  read(Node& S,Node& G){
	/*��ʼ��*/
	S.parent=NULL;	S.depth=0;	S.value=0;
	G.parent=NULL;	G.depth=0;	G.value=0;

	 
	 cout<<"�������ʼ״̬\n";
	 for(int i=0;i<num;i++)
		 cin>>S.state[i];
	 cout<<"������Ŀ��״̬\n";
	  for(int i=0;i<num;i++)
		  cin>>G.state[i];

	  for(int i=0;i<=num-2;i++)
		  for(int j=i+1;j<num;j++)
			if(S.state[i]>S.state[j]&&S.state[i]*S.state[j]!=0)
				count1++;

	   for(int i=0;i<=num-2;i++)
		  for(int j=i+1;j<num;j++)
			if(G.state[i]>G.state[j]&&G.state[i]*G.state[j]!=0)
				count2++;


	   if(count1%2!=count2%2)
	   {
		   return 0;
	   }
		   return 1;
}

int value1(Node A,Node G){
	int count=8;
	
	for(int i=0;i<num;i++)
		if(A.state[i]==G.state[i]&&G.state[i]!=0)
			count--;

	return count +A.depth;

}

int value2(Node A,Node G){
	int count=0,begin[3][3],end[3][3];           //count��¼���������ƶ�����ȷλ����Ҫ�Ĳ���
	for(int i = 0; i < num; i++){
		begin[i/3][i%3]=A.state[i];
		end[i/3][i%3]=G.state[i];
	}


	for(int i = 0; i < 3; i++)   //��鵱ǰͼ�ε���ȷ��
		for(int j = 0; j < 3; j++)
		{
			if(begin[i][j] == 0)
				continue;
			else if(begin[i][j] != end[i][j])
			{
				for(int k=0; k<3; k++)
					for(int w=0; w<3; w++)
						if(begin[i][j] == end[k][w])
							count = count + fabs(i-k*1.0) + fabs(j-w*1.0);
			}
		}
	return count +A.depth; 

}



bool judge(Node S, Node G)
{
	for (int i = 0; i <= 8; i++)
	{
		if (S.state[i] != G.state[i])
		{
			return false;
		}
	}
	return true;
}

//�����½ڵ㣬����OPEN��
void creatNode(Node& S, Node G)
{
	/* ����ԭ״̬��,�ո����ڵ����������Ӷ��жϿո�������ĸ������ƶ� */
	int blank; //����ո��±�
	for(blank=0;blank<9&&S.state[blank]!=0;blank++) ;//�ҵ��հ׸�

	int x =blank / 3, y = blank % 3; //��ȡ�ո��������б��

	for (int d = 0; d < 4; d++) //�ҵ�S��չ���ӽڵ㣬����open����
	{   
		int newX=x,newY=y;//�¿հ׸�����
		Node tempNode;

		/*�ƶ��հ׸�*/
		if(d==0)  newX = x -1;
	    if(d==1)	 newY = y -1;
	    if(d==2)  newX = x +1;
	    if(d==3)	 newY = y +1;

		int newBlank = newX * 3 + newY; //�ո��µ�λ��

		if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) //����ƶ��Ϸ�
		{
			/* �����¾ɿհ׸������*/
			tempNode = S;
			tempNode.state[blank] = S.state[newBlank];
			tempNode.state[newBlank] =0;

			if ( S.parent!=NULL&&(*S.parent).state[newBlank] == 0) //����½ڵ��үү�ڵ�һ���������ýڵ�
			{
				continue;
			}

			/* ���ӽڵ㶼����open���� */
			tempNode.parent = &S;
			tempNode.value = value2(tempNode, G);
			tempNode.depth = S.depth + 1;
			openTable.push(tempNode);
		}
	}
}

int main()
{
	Node S0,Sg;
	if(!read(S0,Sg))
	{cout<<"����֮�䲻�ɴ";
	system("pause"); 
		return 0;
	}
	 
		openTable.push(S0);
		while (true)
		{
			closeTable.push(openTable.top()); //��open�������ȼ���ߵ�Ԫ��ѹ��close����
			openTable.pop(); //�޳�open�������ȼ���ߵ�Ԫ��
			if (!judge(closeTable.back(), Sg)) //�����ǰ�����Ŀ����ֲ���ͬ������չ��ǰ�ڵ�
			{
			creatNode(closeTable.back(), Sg);
			}
			else
			{
				break;
			}
		}

		Node tempNode;   //��ʱ�����ݴ��ǰ����
		tempNode = closeTable.back();
		while (tempNode.parent != NULL)
		{
			Path.push(tempNode);//ѹ��
			tempNode = *(tempNode.parent);//ָ�򸸽ڵ�
		}
		Path.push(tempNode);
		cout << "����Ҫ�ƶ�" << Path.size() - 1 << "��" << endl;

		/* ������� */
		while (Path.size() != 0)
		{
			for (int i = 0; i <= 8; i++)
			{
				cout << Path.top().state[i]<<" ";
				if((i+1)%3==0)
					cout <<endl;
			}
			Path.pop();
			cout << "\n";
		}
	


	return 0;
}