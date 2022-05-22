// A  program  in C++ to solve Sudoku problem
#include <iostream>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <cstdio>

using namespace std;
// the grid of sudoku
// function declaration
int a[15][15],ans_pre,ans[15][15],b[15][15];
bool square[10][10],lie[10][10],hang[10][10],flag[15][15];
bool check;
bool f[15];
int c[15]; 
int difficult;
//( print the sudoku graphically) it deals with the colors of the game
void SetColor(unsigned short ForeColor=7,unsigned short BackGroundColor=0)
{
	HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
}
//* Driver Program to test above functions */
int ge(int x,int y)
{

    return(((x-1)/3)*3+(y-1)/3+1);

}
	// the display of the sudoku grid.....
int print(){
	SetColor(15);
	printf("+---+---+---");
	SetColor(2);
	printf("+");
	SetColor(15);
	printf("---+---+---");
	SetColor(2);
	printf("+");
	SetColor(15);
	printf("---+---+---+\n");

    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
        	if(a[i][j]==0) 
			{
				if(j==4||j==7) SetColor(2);
					cout<<"|   ";
				SetColor(15);
				if (j==9)  cout<<"|";
			}else 
			{
				if(j==4||j==7) SetColor(2);
				cout<<"| ";
				SetColor(15);
				if(b[i][j]==0) SetColor(11);
				cout<<a[i][j]<<" "; 
				SetColor(15);
				if (j==9) cout<<"|";
			}
		}  
        cout<<endl;
        if(i==3||i==6) 
		{
			SetColor(2); 
			cout<<"+---+---+---";
        	cout<<"+";
			cout<<"---+---+---";
			cout<<"+" ;
			cout<<"---+---+---+";
			cout<<endl;
			continue;
		}
        if(i!=9)
       {
        	cout<<"+---+---+---";
        	SetColor(2);
        	cout<<"+";
        	SetColor(15);
			cout<<"---+---+---";
			SetColor(2);
			cout<<"+" ;
			SetColor(15);
			cout<<"---+---+---+";
			cout<<endl;
		}    
        else 
        {
   			SetColor(15);
			printf("+---+---+---");
			SetColor(2);
			printf("+");
			SetColor(15);
			printf("---+---+---");
			SetColor(2);
			printf("+");
			SetColor(15);
			printf("---+---+---+\n");
		} 
        SetColor(15);
    }
}
// Display of the answer grid this help you to view all the answer after you type 0 0 0 enter ...
int print_y()
{
	SetColor(15);
	printf("+---+---+---");
	SetColor(2);
	printf("+");
	SetColor(15);
	printf("---+---+---");
	SetColor(2);
	printf("+");
	SetColor(15);
	printf("---+---+---+\n");

    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
        	if(ans[i][j]==0) 
			{
				if(j==4||j==7) SetColor(2);
					cout<<"|   ";
				SetColor(15);
				if (j==9)  cout<<"|";
			}else 
			{
				if(j==4||j==7) SetColor(2);
				cout<<"| ";
				SetColor(15);
				if(b[i][j]==0) SetColor(11);
   			    cout<<ans[i][j]<<" "; 
				SetColor(15);
				if (j==9) cout<<"|";
			}
		}  
        cout<<endl;
        if(i==3||i==6) 
		{
			SetColor(2); 
			cout<<"+---+---+---";
        	cout<<"+";
			cout<<"---+---+---";
			cout<<"+" ;
			cout<<"---+---+---+";
			cout<<endl;
			continue;
		}
        if(i!=9)
        {
        	cout<<"+---+---+---";
        	SetColor(2);
        	cout<<"+";
        	SetColor(15);
			cout<<"---+---+---";
			SetColor(2);
			cout<<"+" ;
			SetColor(15);
			cout<<"---+---+---+";
			cout<<endl;
		}      
         else 
        {
   			SetColor(15);
			printf("+---+---+---");
			SetColor(2);
			printf("+");
			SetColor(15);
			printf("---+---+---");
			SetColor(2);
			printf("+");
			SetColor(15);
			printf("---+---+---+\n");
		} 
        SetColor(15);
    }
}
// this deals with the algorithm of the sudoku grid
int dfs(int x,int y)
{
    if(!check) return 0;

    if(x==0&&y==9)
    {
        check=false;
        return 0;
    }
    
    if(a[x][y]==0)

    for(int j=1;j<=9;j++) 
    {
    	int i=c[j];
        
		if(square[ge(x,y)][i]&&lie[y][i]&&hang[x][i])
        {
            square[ge(x,y)][i]=false;
            lie[y][i]=false;
            hang[x][i]=false;
            ans[x][y]=i;

            if(y==1) dfs(x-1,9);else dfs(x,y-1);

            square[ge(x,y)][i]=true;
            lie[y][i]=true;
            hang[x][i]=true;

            if(!check) return 0;

        }
    }
    if(!check) return 0;

    if(a[x][y]!=0) if(y==1) dfs(x-1,9);else dfs(x,y-1);
}
// It help to set the arithemtic of the grid
int work(int x)
{
	if(x==10)
	{
		return 0;
	}
	int i=1;
	int y=rand()%9+1;

	while(!f[y]) y=rand()%9+1;
	f[y]=false;
	c[x]=y;
	work(x+1);
}
//intialized the sudoku grid
	//* A utility function to print grid  */
void init()
{
	srand(time(NULL));
    memset(a,0,sizeof(a));
    memset(lie,true,sizeof(lie));
    memset(hang,true,sizeof(hang));
    memset(square,true,sizeof(square));
    memset(f,true,sizeof(f));
    check=true;
    work(1);
    memset(a,sizeof(a),0);
    check=true;
    dfs(9,9); // board is already finished
    memcpy(a,ans,sizeof(ans));
    printf("Please Keydown the Difficulty you like 1~3 : \n");
    difficult=0;

    while(difficult>3||difficult<1) cin>>difficult;

}
// set the difficulty of the grid
void run()
{
	int sum=0;

	switch(difficult){
		case 1:sum=20;
				break;
		case 2:sum=40;
				break;
		case 3:sum=60;
				break;

	}

	int i=1;

	while(i<=sum)
	{
		int x,y;

		x=rand()%9+1;
		y=rand()%9+1;

		while(a[x][y]==0) 
		{
			x=rand()%9+1;
			y=rand()%9+1;
		}
		a[x][y]=0;
		i++;
	}
}
// check whether the grid is filled or not
bool check2()
{
	for(int i = 1; i <= 9; i ++)
	{
		for(int j = 1; j <= 9; j ++)
		{
			if(a[i][j] == 0)
			return false;
		}
	}
	return true;
}
// check whether the grid which player played is same with the answer grid or not
bool check3()
{
	int flag = 0;
	for(int i = 1; i <= 9; i ++)
	{
		for(int j = 1; j <= 9; j ++)
		{
			if(a[i][j] != ans[i][j])
			{
				cout <<i <<" row " << j <<" column is wrong." <<endl;
				flag = 1;
			}
		}
	}
	if(flag == 0)
	cout << "Congratulation! ^_^ " <<endl;
	else
	cout <<"Sorry, You LOSE. T_T " << endl;
}
// the main function of the sudoku game
int main()
{
	init();
	run();
	system("cls");
	memcpy(b,a,sizeof(a));
	print();

	int xx,yy,zz;

	cout<<"\nPlease Keydown the Standard Input Like 'x y z' Which Means that You Will Fill the Square(x,y) in Num 'z'\n\n";
	cout<<"You can Keydown x y 0 to Clean The Square(x,y)\n\n";
	cout<<"You can Keydown 0 0 0 to Get the Right Answer\n\n";

	while(cin>>xx>>yy>>zz)
	{
		if(xx==0&&yy==0&&zz==0)
		{	
			print_y();
			break;
		}
		if(b[xx][yy]==0)
		a[xx][yy]=zz;
	 system("cls");
		print();
		cout<<"Please Keydown the Standard Input Like 'x y z' Which Means that You Will Fill the Square(x,y) in Num 'z'\n\n";
		cout<<"You can Keydown x y 0 to Clean The Square(x,y)\n\n";
		cout<<"You can Keydown 0 0 0 to Get the Right Answer\n\n";

		if(b[xx][yy]!=0)
		{
			SetColor(12);
			cout<<"The Square You Fill in is Filled.\n";
			SetColor(15);
		}
		if(check2())
		{
		   check3();
		   break;
	    }
		
	}
	system("pause");
    return 0;
}
