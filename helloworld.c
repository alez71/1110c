#include<stdio.h>
#include<math.h>

#define pi acos(-1)

int main(){
    for(int i=1;i<10;i++){
        int x = pow(sin(i*pi/2),2);
        printf("%d\n",x);
    };
}