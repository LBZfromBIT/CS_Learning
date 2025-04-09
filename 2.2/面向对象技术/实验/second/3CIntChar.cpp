#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
using namespace std;

class bitset{//to store the binary
    private:
    int store[8];//1 char = 8 bits
    public:
    bitset();
    bool CtB(char c);
    char BtC();
    int getbit(int place);
};
//the init function
bitset::bitset(){
    for(int i=0;i<8;i++){
        store[i]=0;
    }
    return;
}
//the function which convert char to Binary
bool bitset::CtB(char c){
    if((c<'A'||c>'Z')&&(c<'a'||c>'z')&&(c<'0'||c>'9')){//check if the char is ok
        return false;
    }
    int temp=(int)c;//change to int
    //using the mod and division to get the binary
    int division=temp,mod=0,i=7;
    bool flag=false;
    while(i>=0){
        mod=division%2;
        store[i]=mod;
        i--;
        division=division/2;
    } 
    return true;
}
//the function which convert Binary to Char
char bitset::BtC(){
    int sum=0;
    for(int i=0;i<8;i++){
        sum=sum+store[i]*(int)pow(2,7-i);
    }
    return (char)sum;
}
//the function which get the bit in the place
int bitset::getbit(int place){
    if(place<0||place>7){
        cout<<"wrong."<<endl;
        return -1;
    }
    else{
        return store[place];
    }
}

class CIntChar{
    private:
    int lenth;
    bitset stash[4];
    public:
    CIntChar(string s);
    void ASC_Print();
    void Binary_Print();
    void Int_Print();
    char At(int place);
    string str();
};

//the init function
CIntChar::CIntChar(string s){
    int temp=s.length();
    if(temp<4){//less than four words
        lenth=temp;
        for(int i=0;i<temp;i++){
            stash[i].CtB(s[i]);//change the word into binary and store in the stash
        }
        //the rest will be full of zero automaticlly
    }
    else{
        lenth=4;
        for(int i=0;i<4;i++){
            stash[i].CtB(s[i]);//change the word into binary
        }
    }
    return;
}
//the function which print the ASCII
void CIntChar::ASC_Print(){
    string s;
    for(int i=0;i<lenth;i++){
        s=s+stash[i].BtC();
    }
    cout<<s<<endl;
    return;
}
//the function which print the Binary
void CIntChar::Binary_Print(){
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            cout<<stash[i].getbit(j);
            if(j==3||j==7){
                cout<<" ";
            }
        }
    }
    cout<<endl;
    return;
}
//the function which print the Integer
void CIntChar::Int_Print(){
    int temp[32]={0};
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            temp[i*8+j]=stash[i].getbit(j);
        }
    }
    //change the binary into integer
    int sum=0;
    for(int i=0;i<32;i++){
        sum=sum+temp[i]*(int)pow(2,31-i);
    }
    cout<<sum<<endl;
    return;
}
//the function which get the char in the place
char CIntChar::At(int place){
    if(place<1||place>lenth){
        cout<<"wrong."<<endl;
        return -1;
    }
    else{
        return stash[place-1].BtC();
    }
}
//the function which get the string
string CIntChar::str(){
    string s;
    for(int i=0;i<lenth;i++){
        s=s+stash[i].BtC();
    }
    return s;
}

int main(){
    CIntChar IC("Love");
    IC.ASC_Print();
    IC.Binary_Print();
    IC.Int_Print();
    cout<<IC.At(3)<<endl;
    cout<<IC.str()<<endl;
    return 0;
}