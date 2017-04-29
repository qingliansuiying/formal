#include<iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;
int sum,turn=0,answer,correct,rig=0,wro=0,flag=0;    //answer，用于接收用户输入的答案，correct用于存储计算所得正确答案，flag用于检测生成式子是否符合要求
float num[5];
char sig[4];
void scan()            //用于和用户交互
{
	if(turn==0)                              //用turn控制scan部分的输出，进行初始界面和与用户交互界面的切换
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
		choose=rand()%4;
    	switch(choose)
		{
          	case 0:sig[j]='+';break;
        	case 1:sig[j]='-';break;
			case 2:sig[j]='*';break;
			default:sig[j]='/';
		}
	}
}

float jisuan(float num1,char sign1,float num2,char sign2,float num3)    //得出三个数字的计算结果
{
	float result;
	if(sign1=='+')
	{
		result=num1+num2;
	}
	if(sign1=='-')
	{
		result=num1-num2;
	}
	if(sign1=='*')
	{
		result=num1*num2;
	}
	if(sign1=='/')
	{
		if(num2!=0)
		{
			result=num1/num2;
		}
		else
		{
			flag=1;
		}
	}
	if(sign2=='+')
	{
		result=result+num3;
	}
	if(sign2=='-')
	{
		result=result-num3;
	}
	if(sign2=='*')
	{
		if(sign1=='+')
			result=num1+(num2*num3);
		else if(sign1=='-')
			result=num1-(num2*num3);
		else
			result=result*num3;
	}
	if(sign2=='/')
	{
		if(num2!=0)
		{
			if(sign1=='+')
				result=num1+(num2/num3);
			else if(sign1=='-')
				result=num1-(num2/num3);
			else
				result=result/num3;
		}
		else
		{
			flag=1;
		}
	}
	return result;
}

void generateExpression(int type)     //输出随机式子
{
    switch(type)                     //用一个随机数控制输出随机式子，与calculateResult() 配套使用
	{
		case 0:cout<<num[1]<<sig[1]<<num[2]<<sig[2]<<num[3]<<sig[3]<<num[4]<<'=';break;					//1+2+3+4=
		case 1:cout<<'('<<num[1]<<sig[1]<<num[2]<<')'<<sig[2]<<num[3]<<sig[3]<<num[4]<<'=';break;		//(1+2)+3+4=
		case 2:cout<<num[1]<<sig[1]<<num[2]<<sig[2]<<'('<<num[3]<<sig[3]<<num[4]<<')'<<'=';break;		//1+2+(3+4)=
		case 3:cout<<num[1]<<sig[1]<<'('<<num[2]<<sig[2]<<num[3]<<')'<<sig[3]<<num[4]<<'=';break;		//1+(2+3)+4=
		case 4:cout<<'('<<num[1]<<sig[1]<<num[2]<<sig[2]<<num[3]<<')'<<sig[3]<<num[4]<<'=';break;		//(1+2+3)+4=
		case 5:cout<<num[1]<<sig[1]<<'('<<num[2]<<sig[2]<<num[3]<<sig[3]<<num[4]<<')'<<'=';break;		//1+(2+3+4)=
	}
}
void calculateResult(int type)      //计算生成的随机式子的结果
{
	float te,result;
	float t[5];
	int test,sign[5];
	int k;
	if(type==0)									//1+2+3+4=
	{
		sig[0]='*';
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
	if(type==1)						//(1+2)+3+4=
	{
		if(sig[1]=='+')
		{
			te=num[1]+num[2];
		}
		if(sig[1]=='-')
		{
			te=num[1]-num[2];
		}
		if(sig[1]=='*')
		{
			te=num[1]*num[2];
		}
		if(sig[1]=='/')
		{
			if(num[2]!=0)
			{
				te=num[1]/num[2];
			}
			else
				flag=1;
		}
		if(flag==0)
		{
			result=jisuan(te,sig[2],num[3],sig[3],num[4]);
			test=result;
			if(test==result&&test>=0)
			{
				correct=test;
			}
			else
			{
				flag=1;
			}
		}
	}
	if(type==2)						//1+2+(3+4)=
	{
		if(sig[3]=='+')
		{
			te=num[3]+num[4];
		}
		if(sig[3]=='-')
		{
			te=num[3]-num[4];
		}
		if(sig[3]=='*')
		{
			te=num[3]*num[4];
		}
		if(sig[3]=='/')
		{
			if(num[4]!=0)
			{
				te=num[3]/num[4];
			}
			else
				flag=1;
		}
		if(flag==0)
		{
			result=jisuan(num[1],sig[1],num[2],sig[2],te);
			test=result;
			if(test==result&&test>=0)
			{
				correct=test;
			}
			else
			{
				flag=1;
			}
		}
	}
	if(type==3)						//1+(2+3)+4=
	{
		if(sig[2]=='+')
		{
			te=num[2]+num[3];
		}
		if(sig[2]=='-')
		{
			te=num[2]-num[3];
		}
		if(sig[2]=='*')
		{
			te=num[2]*num[3];
		}
		if(sig[2]=='/')
		{
			if(num[3]!=0)
			{
				te=num[2]/num[3];
			}
			else
				flag=1;
		}
		if(flag==0)
		{
			result=jisuan(num[1],sig[1],te,sig[3],num[4]);
			test=result;
			if(test==result&&test>=0)
			{
				correct=test;
			}
			else
			{
				flag=1;
			}
		}
	}
	if(type==4)						//(1+2+3)+4=
	{
		te=jisuan(num[1],sig[1],num[2],sig[2],num[3]);
		if(sig[3]=='+')
		{
			result=te+num[4];
		}
		if(sig[3]=='-')
		{
			result=te-num[4];
		}
		if(sig[3]=='*')
		{
			result=te*num[4];
		}
		if(sig[3]=='/')
		{
			if(num[4]!=0)
			{
				result=te/num[4];
			}
			else
				flag=1;
		}
		if(flag==0)
		{
	
			test=result;
			if(test==result&&test>=0)
			{
				correct=test;
			}
			else
			{
				flag=1;
			}
		}
	}
	if(type==5)						//1+(2+3+4)=
	{
		te=jisuan(num[2],sig[2],num[3],sig[3],num[4]);
		if(sig[1]=='+')
		{
			result=num[1]+te;
		}
		if(sig[1]=='-')
		{
			result=num[1]-te;
		}
		if(sig[1]=='*')
		{
			result=num[1]*te;
		}
		if(sig[1]=='/')
		{
			if(t!=0)
			{
				result=num[1]/te;
			}
			else
				flag=1;
		}
		if(flag==0)
		{
	
			test=result;
			if(test==result&&test>=0)
			{
				correct=test;
			}
			else
			{
				flag=1;
			}
		}
	}
}


void print()                //输出统计结果
{ 
	cout<<"正确题数："<<rig<<endl;
	cout<<"错误题数："<<wro<<endl;
}

int main()           //主函数
{	
	srand(time(0));
	int i,type;
	scan();
	turn=1;
	for(i=1;i<=sum;)
	{
		randomNumber();
		randomOperation();
		type=rand()%6;
		calculateResult(type);
		if(flag==0)
		{
		
			generateExpression(type);
			scan();
		}
		else
		{
			flag=0;
			continue;
		}
		i++;
	}
	print();
	return 0;
}
