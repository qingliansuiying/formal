#include<iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;
int sum,turn=0,answer,correct,rig=0,wro=0,flag=0,num[5],test0=0;    //answer�����ڽ����û�����Ĵ𰸣�correct���ڴ洢����������ȷ�𰸣�flag���ڼ������ʽ���Ƿ����Ҫ��test0���ڼ������Ƿ�Ϊ0
char sig[4];
void scan()            //���ں��û�����
{
	if(turn==0)                              //��turn����scan���ֵ���������г�ʼ��������û�����������л�
	{
		cout<<"Welcome!"<<endl;
		cout<<"����������Ҫ����Ŀ������"<<endl;
		cin>>sum;
	}
	else
	{
		cin>>answer;
		if(answer==correct)
		{
			rig++;
			cout<<"����ȷ��"<<endl;
		}
		else
		{
			wro++;
			cout<<"�𰸴�����ȷ���ǣ�"<<correct<<endl;
		}

	}
} 
void randomNumber()          //���������
{
	int j;
	srand(time(0));
	for(j=1;j<=4;j++)
	{
		num[j]=rand()%10;
	}

}
void randomOperation()    //�����������
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

float jisuan(float num1,char sign1,int num2,char sign2,int num3)    //�ó��������ֵļ�����
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
			test0=1;
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
			result=(num1+num2)*num3;
		if(sign2=='-')
			result=(num1-num2)*num3;
		else
			result=result*num3;
	}
	if(sign2=='/')
	{
		if(num2!=0)
		{
			if(sign1=='+')
				result=(num1+num2)/num3;
			if(sign2=='-')
				result=(num1-num2)/num3;
			else
				result=result/num3;
		}
		else
		{
			test0=1;
		}
	}
	return result;
}

void generateExpression(int type)     //������ʽ�ӣ��˲����д�����
{
    switch(type)                     //��һ�����������������ʽ�ӣ���calculateResult() ����ʹ��
	{
		case 0:cout<<num[1]<<sig[1]<<num[2]<<sig[2]<<num[3]<<sig[3]<<num[4]<<'=';break;					//1+2+3+4=
		case 1:cout<<'('<<num[1]<<sig[1]<<num[2]<<')'<<sig[2]<<num[3]<<sig[3]<<num[4]<<'=';break;		//(1+2)+3+4=
		case 2:cout<<num[1]<<sig[1]<<num[2]<<sig[2]<<'('<<num[3]<<sig[3]<<num[4]<<')'<<'=';break;		//1+2+(3+4)=
		case 3:cout<<num[1]<<sig[1]<<'('<<num[2]<<sig[2]<<num[3]<<')'<<sig[3]<<num[4]<<'=';break;		//1+(2+3)+4=
		case 4:cout<<'('<<num[1]<<sig[1]<<num[2]<<sig[2]<<num[3]<<')'<<sig[3]<<num[4]<<'=';break;		//(1+2+3)+4=
	}
}
void calculateResult(int type)      //�������ɵ����ʽ�ӵĽ�����˲����д�����
{

	if(type==0)									//1+2+3+4=
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
	if(type==1)						//(1+2)+3+4=
	{
		float t,result;
		int test;
		if(sig[1]=='+')
		{
			t=num[1]+num[2];
		}
		if(sig[1]=='-')
		{
			t=num[1]-num[2];
		}
		if(sig[1]=='*')
		{
			t=num[1]*num[2];
		}
		if(sig[1]=='/')
		{
			if(num[2]!=0)
			{
				t=num[1]/num[2];
			}
			else
				test0=1;
		}
		if(test0!=0)
		{
			result=jisuan(t,sig[2],num[3],sig[3],num[4]);
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
		float t,result;
		int test;
		if(sig[3]=='+')
		{
			t=num[3]+num[4];
		}
		if(sig[3]=='-')
		{
			t=num[3]-num[4];
		}
		if(sig[3]=='*')
		{
			t=num[3]*num[4];
		}
		if(sig[3]=='/')
		{
			if(num[4]!=0)
			{
				t=num[3]/num[4];
			}
			else
				test0=1;
		}
		if(test0!=0)
		{
			result=jisuan(num[1],sig[1],num[2],sig[2],t);
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
		float t,result;
		int test;
		if(sig[2]=='+')
		{
			t=num[2]+num[3];
		}
		if(sig[2]=='-')
		{
			t=num[2]-num[3];
		}
		if(sig[2]=='*')
		{
			t=num[2]*num[3];
		}
		if(sig[2]=='/')
		{
			if(num[3]!=0)
			{
				t=num[2]/num[3];
			}
			else
				test0=1;
		}
		if(test0!=0)
		{
			result=jisuan(num[1],sig[1],t,sig[3],num[4]);
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
		float t,result;
		int test;
		t=jisuan(num[1],sig[1],num[2],sig[2],num[3]);
		if(sig[3]=='+')
		{
			result=t+num[4];
		}
		if(sig[3]=='-')
		{
			result=t-num[4];
		}
		if(sig[3]=='*')
		{
			result=t*num[4];
		}
		if(sig[3]=='/')
		{
			if(num[4]!=0)
			{
				result=t/num[4];
			}
			else
				test0=1;
		}
		if(test0!=0)
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


void print()                //���ͳ�ƽ��
{ 
	cout<<"��ȷ������"<<rig<<endl;
	cout<<"����������"<<wro<<endl;
}

int main()           //������
{	
	srand(time(0));
	int i,type;
	scan();
	turn=1;
	for(i=1;i<=sum;)
	{
		randomNumber();
		randomOperation();
		type=rand()%5;
		calculateResult(type);
		if(flag==0)
		{
		
			generateExpression(type);
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