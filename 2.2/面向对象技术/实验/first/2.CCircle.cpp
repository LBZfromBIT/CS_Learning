#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

class CCircle{
    private://member var
        int radius;
        int x;
        int y;
        int line;//the function arg
        void (*funcptr)(int);//the function pointer
    public://mumber function
        CCircle(int r,int xp,int yp);
        CCircle(int r);
        string Relationship(CCircle oc);
        void Exit(void (*function)(int),int n);
        ~CCircle();
};

//the init function
CCircle::CCircle(int r,int xp,int yp){
    radius=r;
    x=xp;
    y=yp;
    line=0;
    funcptr=nullptr;
}
CCircle::CCircle(int r){
    radius=r;
    x=0;
    y=0;
    line=0;
    funcptr=nullptr;
}

//the relationship function
string CCircle::Relationship(CCircle oc){
    string sc;
    double dis=sqrt(pow((x-oc.x),2)+pow((y-oc.y),2));//the distance between two core
    if(radius==oc.radius&&x==oc.x&&y==oc.y){//coincide
        sc="coincide.";
    }
    else if(radius+oc.radius==dis){//circumscribed
        sc="circumscribed.";
    }
    else if(fabs(radius-oc.radius)==dis){//inscribed
        sc="inscribed.";
    }
    else if(radius+oc.radius<dis){//seperated
        sc="seperated.";
    }
    else if(fabs(radius-oc.radius)<dis){//contained
        sc="contained.";
    }
    else if(radius+oc.radius>dis){//overlapped
        sc="overlapped.";
    }
    else{
        sc="unknown.";
    }
    return sc;
}

//the exit function,its arg list will fill in the member var
void CCircle::Exit(void (*function)(int),int n){
    funcptr=function;
    line=n;
}

//the destory function
CCircle::~CCircle(){
    funcptr(line);
    return;
}

//draw triangle,n is the line
void DrawTrangle(int n){
    for(int row=1;row<=n;row++){//row between 1 to n 
        for(int col=1;col<=2*n-1;col++){//column between 1 to 2n-1
            if(col<=n-row||col>=n+row){
                printf(" ");
            }
            else{
                printf("*");
            }
        }
        printf("\n");
    }
    return;
}
//draw the squre,n is the line
void DrawSqure(int n){
    for(int row=1;row<=n;row++){//row between 1 to n
        for(int col=1;col<=n;col++){//col between 1 to n
            if(row==1||row==n){
                printf("*");
            }
            else{
                if(col==1||col==n){
                    printf("*");
                }
                else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    return;
}

int  main(){
    CCircle c1(3);
    CCircle c2(2,4,3);
    
    c1.Exit(DrawTrangle,4);
    c2.Exit(DrawSqure,5);

    cout<<"The relationship is "<<c1.Relationship(c2)<<endl<<endl;
}

