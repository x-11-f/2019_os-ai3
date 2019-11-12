#include "iostream"
using namespace std;
int num = 0;
int p,q;
int QP[3][3]; //保存棋盘数据的数组
int con[3][3]; //记录棋盘状态
const int depth = 3;//搜索树的最大深度是3

void Init(){ //初始化棋盘状态，0表示为空
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			con[i][j]=0;
}

void printQP(){ //打印棋盘
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<con[i][j]<<'\t';
			cout<<endl;
		}
	}
}

void UserInput(){ //用户输入（用户落棋）
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

int checkWin(){ //检查是否有人赢棋
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

int value(){ //判断当前棋盘的状态
	int p=0;
	int q=0;
	//电脑
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

	//人
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
	return p+q; //返回棋盘状态值
}

int cut (int &val , int dep, bool max){//a一B剪枝的算法,val为上一层的估计值,dep为搜索深度,max记录上一层是否为极大层
if (dep==depth||dep+num==9) //如果搜索深度达到最大深度，或者深度加上当前棋子数已经达到9,直接调用估计函数
return value () ;
int i, j, flag, temp ;  //flag记录本层的极值，temp记录下层求得的估计值
//out记录

bool out=false ;//是否剪枝，初始为false

/*if(CheckWin ()==1)  . //如果计算机赢了，就置上一层的估计值为无穷(用很大的值代表无穷)

val =10000 ;
return 0;
}*/
	if(max){ //如果上一层是极大层,本层则需要是极小层，记录flag为无穷大;反之，则为记录为负无穷大
		flag=10000 ;
	} //flag记录本层节点的极值
else{
flag = -10000 ;

for(i=0;i<3 && !out ;i++){ //双 重循环，遍历棋盘所有位置
	for(j=0;j<3 && !out;j++){
		if (con[i][j]==0){//如果该位置上没有棋子
			if (max){  //并且上一层为极大层,即本层为极小层,轮到用户玩家走了
				con[i][j]=-1; //该位置填上用户玩家棋子
				if (checkWin()==-1){ //如果用户玩家赢了
					temp=-10000; //置棋盘估计值为负无穷
				}
				else{
					temp=cut(flag,dep+1,!max);
				}
				if(temp<flag){ //如果下一步棋盘的估计值小于本层节点的极值，置本层极值为更小的那个
					flag=temp;}
					if (flag<=val) { //如果本 层的极值已经小于上一层的估计值，则不需要搜索下去，剪枝
						out=true ;
				}
			}
			else{ //如果上一层为极小层，本层为极大层,轮到计算机走。
				con[i][j]=1 ;//该位置填上计算机棋子
				if (checkWin()==1){ //如果计算机赢了
					temp = 10000 ;}//置棋盘估计值为无穷}
				else{
					temp=cut(flag,dep+1,!max);
				}
				if(temp>flag){ //如果下一步棋盘的估计值小于本层节点的极值，置本层极值为更小的那个
					flag=temp;}
					if (flag>=val){  //如果本 层的极值已经小于上一层的估计值，则不需要搜索下去，剪枝
						out=true ;
				}
			}
			con[i][j]=0;//把模拟下的棋还原，回溯
		}
	}
}
}
if (max){  //根据上一层是否为极大层，用本层的极值修改上一层的估计值
	if (flag>val){
		val =flag ;
	}
}
else{
if (flag<val){
	val =flag ;}}

      return flag; //函数返回 的是本层的极值

      }

int main(){//主程序
      int m= -10000, val= -10000, dep=1; //m用来存放最大的val
      int x_pos,y_pos;  //记录最佳走步的坐标
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
	  if (IsFirst=='n'){//汁算机先走
L5:  for(int x=0;x<3;x++){
		  for(int y=0;y<3;y++){
			  if (con[x][y]==0){
				  con[x][y]=1;
				  cut(val,dep,1);//计算机试探性走一步棋，改变棋盘状态，在该状态下计算棋盘估计值
				  if (checkWin()==1){
					  cout<<" The computer put the qiziat:"<<x+1<<y+1<<endl;
					  printQP();
					  cout<<"The computer WIN ! GAME0VER. "<< endl;
					  return 0;
				  }
				  if (val>m){ //m要记录通过试探求得的棋盘状态的最大估计值
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
	 UserInput () ;//玩家走一步棋
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

	  else{ //人先走
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