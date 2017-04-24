#include<iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;
int sum,turn=0,answer,correct,rig=0,wro=0,flag=0,num[5],test0=0;
char sig[4];
void scan()            //用于和用户交互
{
	if(turn==0)
	{
		cout<<"Welcome!"<<endl;
		cout<<"请输入你想要的题目数量："<<endl;
		cin>>sum;
	}
	else
	{
		cin>>answer;
		if(answer==correct)
		{
			rig++;
			cout<<"答案正确！"<<endl;
		}
		else
		{
			wro++;
			cout<<"答案错误！正确答案是："<<correct<<endl;
		}

	}
} 
void randomNumber()          //生成随机数
{
	int j;
	srand(time(0));
	for(j=1;j<=4;j++)
	{
		num[j]=rand()%10;
	}

}
void randomOperation()    //生成随机符号
{
	srand(time(0));
	int choose,j;
	for(j=1;j<=3;j++)
	{
		choose=rand()%3;
    	switch(choose)
		{
          	case 0:sig[j]='+';break;
        	case 1:sig[j]='-';break;
			case 2:sig[j]='*';break;
			default:sig[j]='/';
		}
	}
}
void generateExpression()     //输出随机式子，此部分有待补充
{
	cout<<num[1]<<sig[1]<<num[2]<<sig[2]<<num[3]<<sig[3]<<num[4]<<'=';

	/*switch(type)                     打算用一个随机数控制输出随机式子，与calculateResult() 配套使用
	{
	case 0:cout<<num[1]<<sig[1]<<num[2]<<sig[2]<<num[3]<<sig[3]<<num[4]<<'=';break;
	case:1:cout<<'('<<num[1]<<sig[1]<<num[2]<<')'<<sig[2]<<num[3]<<sig[3]<<num[4]<<'=';break;
	case:2:cout<<num[1]<<sig[1]<<num[2]<<sig[2]<<'('<<num[3]<<sig[3]<<num[4]<<')'<<'=';break;
    default:3:cout<<'('<<num[1]<<sig[1]<<num[2]<<')'<<sig[2]<<'('<<num[3]<<sig[3]<<num[4]<<')<<'=';
	}
	*/
}
void calculateResult()      //计算生成的随机式子的结果，此部分有待补充
{

	sig[0]='*';
	float t[5];
	int test,sign[5];
	int k;
	t[1]=num[1];
	for(k=0;k<=3;k++)
	{
		if(sig[k]=='+')
			sign[k]=1;
		if(sig[k]=='-')
			sign[k]=2;
		if(sig[k]=='*')
			sign[k]=3;
		if(sig[k]=='/')
			sign[k]=4;
	}
	if(sign[3]+sign[4]==7&&sign[1]==1)
		flag=1;
	else if(sign[3]+sign[4]==7&&sign[1]==2)
		flag=1;
	else
	{
		for(k=1;k<=3;k++)
		{
    	 	if(sig[k]=='+')
			{
		    	 t[k+1]=t[k]+num[k+1];
			}
	    	if(sig[k]=='-')
			{
	    		t[k+1]=t[k]-num[k+1];
			}
	    	if(sig[k]=='*')
			{
		    	if(sig[k-1]=='+')
		    		t[k+1]=t[k-1]+num[k]*num[k+1];
	    		else if(sig[k-1]=='-')
		    		t[k+1]=t[k-1]-num[k]*num[k+1];
		    	else
			    	t[k+1]=t[k-1]*num[k+1];
			}
	    	if(sig[k]=='/')
			{
	    		if(num[k+1]==0)
				{
		    		flag=1;break;
				}
	    		if(sig[k-1]=='+')
	    			t[k+1]=t[k-1]+num[k]/num[k+1];
	    		else if(sig[k-1]=='-')
	    			t[k+1]=t[k-1]-num[k]/num[k+1];
		    	else
		    		t[k+1]=t[k-1]/num[k+1];
			}
		}
	}
	test=t[4];
	if(flag==0&&test==t[4]&&test>=0)
		correct=test;
	else
		flag=1;
}

void print()                //输出统计结果
{ 
	cout<<"正确题数："<<rig<<endl;
	cout<<"错误题数："<<wro<<endl;
}

int main()           //主函数
{
	int i;
	scan();
	turn=1;
	for(i=1;i<=sum;)
	{
		randomNumber();
		randomOperation();
		calculateResult();
		if(flag==0)
		{
			generateExpression();
			scan();
		}
		else
		{
			test0=0;
			flag=0;
			continue;
		}
		test0=0;
		i++;
	}
	print();
	return 0;
}


