#include <stdio.h>
int size=0;
void average(double ar[], const int );
int main(void)
{
	double fantasyPoints[]= {14.4,15.3,15.8,15.8,16.4,16.8,16.8,17.4,17.6,17.7,17.9,18.3,
							18.4,19.4,19.5,19.6,19.7,20,20.1,20.2,20.6,20.9,20.9,21,21.2,
							21.5,21.7,21.7,23.4,26.3,27.6};
	size = sizeof(fantasyPoints)/sizeof(fantasyPoints[0]);
	average(fantasyPoints, size);


}
void average(double fantasyPoints[], const int size)
{
	

}