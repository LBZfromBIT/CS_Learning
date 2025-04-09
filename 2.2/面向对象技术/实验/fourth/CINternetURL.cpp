#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

class CMyString{
    private:
    char* str;//store place
    int lenth;//string lenth
    public:
    CMyString();
    CMyString(const int& onum);
    CMyString(const double& ofnum);
    CMyString(const char* ostr);
    CMyString(const CMyString& ostr);
    int len();
    int Find(char ochr);
    int Find(char ochr,int pos);
    int Find(const CMyString& ostr);
    int Find(const CMyString& ostr,int pos);
    CMyString Mid(int sPos,int len);
    friend ostream& operator <<(ostream& os,const CMyString& ostr);
    CMyString& operator =(const CMyString& ostr);
    char& operator [](int index);
    friend CMyString operator +(const char* ostr,const CMyString& str2);
    friend CMyString operator +(const CMyString& str1,const char* ostr2);
    friend CMyString operator +(const CMyString& str1,const CMyString& str2);
    operator int();
    operator double();
};

//the init function
CMyString::CMyString(){
    str=new char[1];
    str[0]='\0';
    lenth=0;
}
CMyString::CMyString(const int& onum){
    str=new char[25];
    sprintf(str,"%d",onum);
    lenth=0;
    while(str[lenth]!='\0'){
        lenth++;
    }
}
CMyString::CMyString(const double& ofum){
    str=new char[25];
    sprintf(str,"%lf",ofum);
    lenth=0;
    while(str[lenth]!='\0'){
        lenth++;
    }
}
CMyString::CMyString(const char* ostr){
    lenth=0;
    //count the number
    while(ostr[lenth]!='\0'){//not to the end of the line
        lenth++;
    }
    //allocate the place
    str=new char[lenth];
    //copy the string
    for(int i=0;i<lenth;i++){
        str[i]=ostr[i];
    }
    str[lenth]='\0';
}
CMyString::CMyString(const CMyString& ostr){
    lenth=ostr.lenth;
    str= new char[lenth];
    for(int i=0;i<lenth;i++){
        str[i]=ostr.str[i];
    }
    str[lenth]='\0';
}
//to show lenth
int CMyString::len(){
    return lenth;
}
//the find function
int CMyString::Find(char ochr){
    int site=0;
    while(str[site]!='\0'){
        if(str[site]==ochr){
            return site;
        }
        else{
            site++;
            continue;
        }
    }
    return -1;
}
int CMyString::Find(char ochr,int pos){
    assert(pos>=0);
    int site=pos;
    while(str[site]!='\0'){
        if(str[site]==ochr){
            return site;
        }
        else{
            site++;
            continue;
        }
    }
    return -1;
}
int CMyString::Find(const CMyString& ostr){
    int site=0;
    while(str[site]!='\0'){
        if(str[site]!=ostr.str[0]){
            site++;
            continue;
        }
        else{
            int cmp=0;
            bool flag=true;
            while(flag==true&&str[site+cmp]!='\0'&&ostr.str[cmp]!='\0'){
                if(ostr.str[cmp]==str[site+cmp]){
                    cmp++;
                    continue;
                }
                else{
                    flag=false;
                    break;
                }
            }
            if(flag==true&&ostr.str[cmp]=='\0'){//to avoid the case as find 'abc'(ostr) in 'cab'(str)
                return site;
            }
            else{
                site++;
                continue;
            }
        }
    }
    return -1;
}
int CMyString::Find(const CMyString& ostr,int pos){
    assert(pos>=0);
    int site=pos;
    while(str[site]!='\0'){
        if(str[site]!=ostr.str[0]){
            site++;
            continue;
        }
        else{
            int cmp=0;
            bool flag=true;
            while(flag==true&&str[site+cmp]!='\0'&&ostr.str[cmp]!='\0'){
                if(ostr.str[cmp]==str[site+cmp]){
                    cmp++;
                    continue;
                }
                else{
                    flag=false;
                    break;
                }
            }
            if(flag==true&&ostr.str[cmp]=='\0'){//to avoid the case as find 'abc'(ostr) in 'cab'(str)
                return site;
            }
            else{
                site++;
                continue;
            }
        }
    }
    return -1;
}
//the mid function
CMyString CMyString::Mid(int sPos,int len){
    assert(sPos>0&&len>0&&sPos+len<=lenth);
    char* temp=new char[lenth];
    for(int i=sPos;i<sPos+len;i++){
        temp[i-sPos]=str[i];
    }
    temp[len]='\0';
    return CMyString(temp); 
}
//the opreator overloading
ostream& operator <<(ostream& os,const CMyString& ostr){
    os<<ostr.str;
    return os;
}
CMyString& CMyString::operator =(const CMyString& ostr){
    str=new char[ostr.lenth];
    for(int i=0;i<ostr.lenth;i++){
        str[i]=ostr.str[i];
    }
    lenth=ostr.lenth;
    str[lenth]='\0';
    return *this;
}
char& CMyString::operator[](int index){
    return str[index];
}
//attention: Addition satisfies the commutative property.
CMyString operator +(const CMyString& str1,const CMyString& str2){
    int len=str1.lenth+str2.lenth;
    char* temp=new char[len];
    int site=0,ptr=0;
    while(ptr<str1.lenth){
        temp[site]=str1.str[ptr];
        site++;
        ptr++;
    }
    ptr=0;
    while(ptr<str2.lenth){
        temp[site]=str2.str[ptr];
        site++;
        ptr++;
    }
    temp[len]='\0';
    return CMyString(temp);
}
CMyString operator +(const char* ostr,const CMyString& str2){
    CMyString str1(ostr);
    int len=str1.lenth+str2.lenth;
    char* temp=new char[len];
    int site=0,ptr=0;
    while(ptr<str1.lenth){
        temp[site]=str1.str[ptr];
        site++;
        ptr++;
    }
    ptr=0;
    while(ptr<str2.lenth){
        temp[site]=str2.str[ptr];
        site++;
        ptr++;
    }
    temp[len]='\0';
    return CMyString(temp);
}
CMyString operator +(const CMyString& str1,const char* ostr2){
    CMyString str2(ostr2);
    int len=str1.lenth+str2.lenth;
    char* temp=new char[len];
    int site=0,ptr=0;
    while(ptr<str1.lenth){
        temp[site]=str1.str[ptr];
        site++;
        ptr++;
    }
    ptr=0;
    while(ptr<str2.lenth){
        temp[site]=str2.str[ptr];
        site++;
        ptr++;
    }
    temp[len]='\0';
    return CMyString(temp);
}
CMyString::operator int(){
    return atoi(str);
}
CMyString::operator double(){
    return atof(str);
}


class CInternetURL{
    private:
    CMyString URL;
    public:
    CInternetURL(const char* pstr);
    CInternetURL(const CInternetURL& ostr);
    CMyString GetDomain();
    CMyString GetDomainCountry();
    CMyString GetDomainType();
    CMyString GetHomePage();    
};
//the init function
CInternetURL::CInternetURL(const char* pstr){
    URL=CMyString(pstr);
}
CInternetURL::CInternetURL(const CInternetURL& ostr){
    URL=ostr.URL;
}
//the get function
CMyString CInternetURL::GetDomain(){
    int spos=URL.Find("://");
    if(spos==-1){
        return CMyString("404 Not Found.");
    }
    spos=spos+3;//the start place
    int epos=URL.Find('/',spos);
    if(epos==-1){
        return CMyString("404 Not Found.");
    }
    CMyString temp=URL.Mid(spos,epos-spos);
    if(temp.Find("www")==-1){//change to the 3W
        temp[0]='w';
        temp[1]='w';
        temp[2]='w';
    };
    return temp;
}
CMyString CInternetURL::GetDomainCountry(){
    CMyString temp=GetDomain();
    int spos=0;
    for(int count=0;count<3&&spos!=-1&&spos<temp.len();spos=temp.Find('.',spos+1)){
        count++;
    }
    if(spos==-1){
        return CMyString("404 Not Found.");
    }
    return temp.Mid(spos+1,temp.len()-spos-1);
}
CMyString CInternetURL::GetDomainType(){
    CMyString temp=GetDomain();
    int epos=0,spos=0;
    for(int count=0;count<3&&epos!=-1&&epos<temp.len();epos=temp.Find('.',epos+1)){
        if(count==2){
            spos=epos+1;
        }       
        count++;        
    }
    if(spos==-1||epos==-1){
        return CMyString("404 Not Found.");
    }
    return temp.Mid(spos,epos-spos);
}
CMyString CInternetURL::GetHomePage(){
    int spos=URL.Find('/',URL.Find("://")+3);
    if(spos==-1){
        return CMyString("404 Not FOund.");
    }
    spos++;
    int epos=URL.Find('.',spos);
    if(epos==-1){
        return CMyString("404 Not Found.");
    }
    return URL.Mid(spos,epos-spos);
}

int main(){
    CMyString s1("BIT"),s2;
    s2="love";
    s2[0]='L';
    cout<<"I "+s2<<" "<<s1<<endl;

    int pos=s1.Find('T');
    cout<<pos<<endl;
    pos=s1.Find("IT");
    cout<<pos<<endl;
    pos=s1.Find("b");
    cout<<pos<<endl;

    int startPos=3,len=4;
    s2="Welcome";
    CMyString myStr=s2.Mid(startPos,len);
    cout<<myStr<<endl;

    CMyString str_num(123);
    int a=str_num;
    cout<<a<<endl;
    str_num=-123.456;
    double b=str_num;
    cout<<b<<endl;

    CInternetURL URL("https://jwc.bit.edu.cn/index.htm");
    cout<<URL.GetDomain()<<endl;
    cout<<URL.GetDomainCountry()<<endl;
    cout<<URL.GetDomainType()<<endl;
    cout<<URL.GetHomePage()<<endl;
    return 0;
}
