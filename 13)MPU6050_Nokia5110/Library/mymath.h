////////////////////////////////////////////////////////////////////
// THU VIEN HAM TINH TOAN RUT GON
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Email:	terran991992@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// AP DUNG CHO MACH UNG DUNG MSP430
//******************************************************************/
void _itoa(int n, char str[], int he)
{
	int i=0,j=0;
	unsigned char dau=0;
	char ch[]="0123456789ABCDEF";
	if(n==0)str[0]=ch[0];
	if(n<0)
	{
		dau=1;
		n*=-1;
	}

	while(n)
	{
		str[i]=ch[n%he];
		n /= he;
		i++;
	}
	if(dau==1){str[i]='-';i++;}
	for(j=0;j<i/2;j++)
	str[j] ^= str[i-j-1] ^= str[j] ^= str[i-j-1];
	str[i]=0;
}

void _itoa_unsigned(unsigned int n, char str[], int he)
{
	unsigned int i=0,j=0;
	char ch[]="0123456789ABCDEF";
	if(n==0)str[0]=ch[0];

	while(n)
	{
		str[i]=ch[n%he];
		n /= he;
		i++;
	}
	for(j=0;j<i/2;j++)
	str[j] ^= str[i-j-1] ^= str[j] ^= str[i-j-1];
	str[i]=0;
}

double myabs(double x)
{
	return ((x>=0)?x:(-x));
}

//	cach tinh can 2 của a :  x_(n+1) = (x_n + a / x_n) / 2
float mysqrt(float a)
{
	float xo, xn=1, e= 0.000001;
	do
	{
	   xo=xn;
	   xn=(a/xo+xo)/2.0;
	}
	while (myabs(xn-xo)>e);
	return xn;
}
float mypow(float x,int y)	//x mu y
{
	float ans=1;
	int i=0;
	for(i=0;i<y;i++)
		ans*=x;
	return ans;
}
long myfact(int n)
{
	long ans=1;
	for(n;n>0;n--)ans*=n;
	return ans;
}

float mysin(float a)
{
	float y=0;
	int dau,n=0;
	while(n<10)
	{
		if(n%2!=0)dau=-1;
		else dau=1;
		y=(float)dau*mypow(a,2*n+1)/myfact(2*n+1);
		n++;
	}
	return y;
}

