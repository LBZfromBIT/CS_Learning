#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;


//before you read this part,please read the README.md as an explaination
typedef struct appearance{
    string name;//name
    int time=0;//app. time
}app;

//the compare function
int cmp(const void* a,const void* b){
    return (*(app*)b).time-(*(app*)a).time;
}


class CText{
    private://member var
        string filepath;
        int word;
        int time[5];//the appearance time of each role
    public:
        CText(string fpath);
        int count();
        void view();
};

//the init function
CText::CText(string fpath){
    filepath=fpath;
    word=0;
    for(int i=0;i<5;i++){
        time[i]=0;
    }
}
//the count function
int CText::count(){
    ifstream fin;
    fin.open(filepath,ios::in);
    char buf[2048]={0};//the buffer
    int sum=0;//the count var
    while(fin>>buf){//read by block
        for(int i=0;i<strlen(buf);i++){
           if (buf[i]>=0&&buf[i]<=127){//not chinese
            sum++;
           }
           else{//chinese
            sum++;
            i++;
           }
        }
    }
    word=sum;
    fin.close();
    return word;
}
//the view function
void CText::view(){
    app arr[5];//struct array to store the result
    //init 
    arr[0].name="大圣";
    arr[1].name="玉帝";
    arr[2].name="王母娘娘";
    arr[3].name="仙女";
    arr[4].name="天王";
    //read the text
    ifstream fin;
    fin.open(filepath,ios::in);
    char buf[2048]={0};
    while(fin>>buf){
        string sc=buf;
        for(int i=0;i<5;i++){
            int index=0,sum=0;
            while((index=sc.find(arr[i].name,index))!=string::npos){
                sum++;
                index+=arr[i].name.size();
            }
            arr[i].time+=sum;
        }
    
    }
    fin.close();
    qsort(arr,5,sizeof(app),cmp);
    cout<<"The very important two guys are:"<<endl;
    for(int i=0;i<2;i++){
        cout<<arr[i].name<<" "<<arr[i].time<<endl;
    }
    return;
}

int main(){
    CText textGB("JourneyToWest(GB2312).txt");
    cout<<"there are "<<textGB.count()<<" characters in this text"<<endl;
    CText textUTF("JourneyToWest(utf-8).txt");
    textUTF.view();
    return 0;
}