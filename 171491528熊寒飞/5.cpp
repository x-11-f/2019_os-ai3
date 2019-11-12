#include "iostream"
using namespace std;
int num = 0;
int p,q;
int QP[3][3]; //�����������ݵ�����
int con[3][3]; //��¼����״̬
const int depth = 3;//����������������3

void Init(){ //��ʼ������״̬��0��ʾΪ��
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			con[i][j]=0;
}

void printQP(){ //��ӡ����
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<con[i][j]<<'\t';
			cout<<endl;
		}
	}
}

void UserInput(){ //�û����루�û����壩
	int chess,x,y;
L1: cout<<"Please input your chess(xy):";
	cin>>chess;
	x=chess/10;
	y=chess%10;
	if(x>0 && x<4 && y>0 && y<4 && con[x-1][y-1]==0)
		con[x-1][y-1]= -1;
	else{
		cout<<"Input error!";
		goto L1;
	}
}

int checkWin(){ //����Ƿ�����Ӯ��
	for(int i=0;i<3;i++){
		if(con[i][0]==1 && con[i][1]==1 && con[i][2]==1)
			return 1;
		if(con[i][0]==-1 && con[i][1]==-1 && con[i][2]==-1)
			return -1;
	}
	for(int i=0;i<3;i++){
		if(con[0][i]==1 && con[1][i]==1 && con[2][i]==1)
			return 1;
		if(con[0][i]==-1 && con[1][i]==-1 && con[2][i]==-1)
			return -1;
	}
	if((con[0][0]==1 &&con[1][1]==1 && con[2][2]==1) || (con[0][2]==1 && con[1][1]==1 && con[2][0]==1))
		return 1;
	if((con[0][0]== -1 &&con[1][1]== -1 && con[2][2]== -1) || (con[0][2]== -1 && con[1][1]== -1 && con[2][0]== -1))
		return -1;
	return 0;
}

int value(){ //�жϵ�ǰ���̵�״̬
	int p=0;
	int q=0;
	//����
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(con[i][j] == 0){
				QP[i][j]=1;
			}
			else QP[i][j]= con[i][j];
		}
	}
	for(int i=0;i<3;i++)
		p=p+(QP[i][0]+QP[i][1]+QP[i][2])/3;
	for(int i=0;i<3;i++)
		p+=(QP[0][i]+QP[1][i]+QP[2][i])/3;
	p+=(QP[0][0]+QP[1][1]+QP[2][2])/3;
	p+=(QP[0][2]+QP[1][1]+QP[2][0])/3;

	//��
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(con[i][j] == 0){
				QP[i][j]=-1;
			}
			else QP[i][j]= con[i][j];
		}
	}
	for(int i=0;i<3;i++)
		p=p+(QP[i][0]+QP[i][1]+QP[i][2])/3;
	for(int i=0;i<3;i++)
		p+=(QP[0][i]+QP[1][i]+QP[2][i])/3;
	p+=(QP[0][0]+QP[1][1]+QP[2][2])/3;
	p+=(QP[0][2]+QP[1][1]+QP[2][0])/3;
	return p+q; //��������״ֵ̬
}

int cut (int &val , int dep, bool max){//aһB��֦���㷨,valΪ��һ��Ĺ���ֵ,depΪ�������,max��¼��һ���Ƿ�Ϊ�����
if (dep==depth||dep+num==9) //���������ȴﵽ�����ȣ�������ȼ��ϵ�ǰ�������Ѿ��ﵽ9,ֱ�ӵ��ù��ƺ���
return value () ;
int i, j, flag, temp ;  //flag��¼����ļ�ֵ��temp��¼�²���õĹ���ֵ
//out��¼

bool out=false ;//�Ƿ��֦����ʼΪfalse

/*if(CheckWin ()==1)  . //��������Ӯ�ˣ�������һ��Ĺ���ֵΪ����(�úܴ��ֵ��������)

val =10000 ;
return 0;
}*/
	if(max){ //�����һ���Ǽ����,��������Ҫ�Ǽ�С�㣬��¼flagΪ�����;��֮����Ϊ��¼Ϊ�������
		flag=10000 ;
	} //flag��¼����ڵ�ļ�ֵ
else{
flag = -10000 ;

for(i=0;i<3 && !out ;i++){ //˫ ��ѭ����������������λ��
	for(j=0;j<3 && !out;j++){
		if (con[i][j]==0){//�����λ����û������
			if (max){  //������һ��Ϊ�����,������Ϊ��С��,�ֵ��û��������
				con[i][j]=-1; //��λ�������û��������
				if (checkWin()==-1){ //����û����Ӯ��
					temp=-10000; //�����̹���ֵΪ������
				}
				else{
					temp=cut(flag,dep+1,!max);
				}
				if(temp<flag){ //�����һ�����̵Ĺ���ֵС�ڱ���ڵ�ļ�ֵ���ñ��㼫ֵΪ��С���Ǹ�
					flag=temp;}
					if (flag<=val) { //����� ��ļ�ֵ�Ѿ�С����һ��Ĺ���ֵ������Ҫ������ȥ����֦
						out=true ;
				}
			}
			else{ //�����һ��Ϊ��С�㣬����Ϊ�����,�ֵ�������ߡ�
				con[i][j]=1 ;//��λ�����ϼ��������
				if (checkWin()==1){ //��������Ӯ��
					temp = 10000 ;}//�����̹���ֵΪ����}
				else{
					temp=cut(flag,dep+1,!max);
				}
				if(temp>flag){ //�����һ�����̵Ĺ���ֵС�ڱ���ڵ�ļ�ֵ���ñ��㼫ֵΪ��С���Ǹ�
					flag=temp;}
					if (flag>=val){  //����� ��ļ�ֵ�Ѿ�С����һ��Ĺ���ֵ������Ҫ������ȥ����֦
						out=true ;
				}
			}
			con[i][j]=0;//��ģ���µ��廹ԭ������
		}
	}
}
}
if (max){  //������һ���Ƿ�Ϊ����㣬�ñ���ļ�ֵ�޸���һ��Ĺ���ֵ
	if (flag>val){
		val =flag ;
	}
}
else{
if (flag<val){
	val =flag ;}}

      return flag; //�������� ���Ǳ���ļ�ֵ

      }

int main(){//������
      int m= -10000, val= -10000, dep=1; //m�����������val
      int x_pos,y_pos;  //��¼����߲�������
      Init () ;
	  cout<<"Qipan:" <<endl ;
	  printQP () ;
	  char IsFirst ;
	  cout<<"Do you want do first ? (y/n) ";
		  cin>>IsFirst;
	  while (IsFirst !='y' &&IsFirst !='n'){
		  cout<<" ERROR ! "<<"Do you want first?(y/n) ";
		  cin>>IsFirst;
	  }
	  if (IsFirst=='n'){//֭�������
L5:  for(int x=0;x<3;x++){
		  for(int y=0;y<3;y++){
			  if (con[x][y]==0){
				  con[x][y]=1;
				  cut(val,dep,1);//�������̽����һ���壬�ı�����״̬���ڸ�״̬�¼������̹���ֵ
				  if (checkWin()==1){
					  cout<<" The computer put the qiziat:"<<x+1<<y+1<<endl;
					  printQP();
					  cout<<"The computer WIN ! GAME0VER. "<< endl;
					  return 0;
				  }
				  if (val>m){ //mҪ��¼ͨ����̽��õ�����״̬��������ֵ
					  m=val;
					  x_pos=x,y_pos=y;
				  }
				  val= -10000 ;
				  con [x][y]=0;
			  }
		  }
	 }
	 con[x_pos][y_pos]=1 ;
	 val= -10000;
	 m= -10000;
	 dep=1;
	 cout <<"The computer put the qiziat:"<<x_pos+1<<y_pos+1<<endl ;
	 printQP ();
	 num++ ;
	 value () ;
	 if (p==0){
		 cout<<" DOWN GAME!"<<endl ;
		 return 0;
	 }
	 UserInput () ;//�����һ����
	 printQP () ;
	 cout<<endl ;
	 num++;
	 value () ;
	 if (p==0){
		 cout<<"DOWN GAME!" <<endl ;
		 return 0;
	  }
	  if (checkWin ()==-1){
		  cout<< " Conguatulations ! You Win !GAME OVER."<<endl ;
			  return 0;
	  }
	  goto L5;
	  }

	  else{ //������
L4:  UserInput();
	  printQP () ;
	  cout<<endl ;
	  num++;
	  value () ;
	  if (q==0){
		  cout<<"DOWN GAME!"<<endl ;
		  return 0;
	  }
	  if (checkWin ()==-1){
		  cout <<" You Win ! GAME OVER."<<endl;
		  return 0;
	  }
	  for (int x=0;x<3;x++){
		  for (int y=0;y<3;y++){
			  if (con[x][y]==0){
				  con[x][y]=1;
				  cut (val,dep, 1);
				  if (checkWin ()==1){
					  cout <<"The computer put the qiziat:"<<x+1<<y+1<<endl ;
					  cout <<" The computer WIN ! GAME0VER. " <<endl ;
					  return 0;
				  }
				  if (val >m){
					  m=val ;
					  x_pos=x;
					  y_pos=y;
				  }
				  val= -10000 ;
				  con[x][y]=0;
			  }
		  }
	  }
	  con[x_pos][y_pos]=1;
	  val= -10000 ;
	  m= -10000 ;
	  dep=1 ;
	  cout <<"The computer put the qiziat:"<<x_pos+1<<y_pos+1<<endl ;
	  printQP () ;
	  cout<<endl ;
	  num++ ;
	  value () ;
	  if (q==0){
		  cout<<"Down Game!"<<endl;
		  return 0;
	  }
	  goto L4;
	  }
	  return 0;
}