#include <cstdio>
#include <iostream>
using namespace std;

const int Leap_Month_Day[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};//the element 0 has no meaning
const int NLeap_Month_Day[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//the element 0 has no meaning


bool isLeap(int year){//the function which shows whether the year is a Leap Year;
    if(year%400==0){
        return true;
    }
    else if(year%4==0&&year%100!=0){
        return true;
    }
    else{
        return false;
    }
}

class CDate{
    private:
    //member var
    int year;
    int month;
    int day;
    bool Leap;

    public:
    //member func
    //the init function
    CDate(int inityear=2024,int initmonth=3,int initday=14){
        year=inityear;
        month=initmonth;
        day=initday;
        Leap=isLeap(year);
    }

    //these functions are using to reset the date
    void Reset(int oyear,int omonth,int oday);
    void Reset(CDate odate);

    //the function which counts the span days
    int Span(CDate odate);
    
    //this function is using to show the date
    void Show();
};

void CDate::Reset(int oyear,int omonth,int oday){
    year=oyear;
    month=omonth;
    day=oday;
    Leap=isLeap(oyear);
    return;
}

void CDate::Reset(CDate odate){
    year=odate.year;
    month=odate.month;
    day=odate.day;
    Leap=odate.Leap;
    return;
}

void CDate::Show(){
    cout<<year<<"/"<<month<<"/"<<day<<" ";
    return;
}

int CDate::Span(CDate odate){
    //step 1:find the later one
    CDate late,before;
    if(odate.year==year){//in the same year?
        if(odate.month==month){//in the same month?
           if(odate.day>=day){
               late.Reset(odate);
               before.Reset(year,month,day);
           }
           else{
               late.Reset(year,month,day);
               before.Reset(odate);
           }
        }
        else if(odate.month>month){//od is later
            late.Reset(odate);
            before.Reset(year,month,day);
        }
        else{
            late.Reset(year,month,day);
            before.Reset(odate);
        }
    }
    else if(odate.year>year){//od is later than this
        late.Reset(odate);
        before.Reset(year,month,day);
    }
    else{
        late.Reset(year,month,day);
        before.Reset(odate);
    }
    
    //step 2: count the day
    int sum=0;
    //mini step 1:reset the before to 1.1
    if(before.Leap){//before is leap year
        sum-=before.day-1;
        for(int basemonth=before.month;basemonth>1;basemonth--){
            sum-=Leap_Month_Day[basemonth-1];
        }
        before.Reset(before.year,1,1);
    }
    else{
        sum-=before.day-1;
        for(int basemonth=before.month;basemonth>1;basemonth--){
            sum-=NLeap_Month_Day[basemonth-1];
        }
        before.Reset(before.year,1,1);
    }
    //mini step 2:reset the late to 1.1
    if(late.Leap){
        sum+=late.day-1;
        for(int basemonth=late.month;basemonth>1;basemonth--){
            sum+=Leap_Month_Day[basemonth-1];
        }
        late.Reset(late.year,1,1);
    }
    else{
        sum+=late.day-1;
        for(int basemonth=late.month;basemonth>1;basemonth--){
            sum+=NLeap_Month_Day[basemonth-1];
        }
        late.Reset(late.year,1,1);
    }
    //mini step 3:count the year
    for(int baseyear=before.year;baseyear<late.year;baseyear++){
        if(isLeap(baseyear)){
            sum+=366;
        }
        else{
            sum+=365;
        }
    }
    return sum;
}

int main(){
    cout<<"please enter the first date"<<endl;
    int year,month,day;
finput:
    scanf("%d %d %d",&year,&month,&day);
    if(month<0||month>12){
        cout<<"wrong input,do it again"<<endl;
        goto finput;
    }
    if(isLeap(year)){
        if(day<0||day>Leap_Month_Day[month]){
            cout<<"wrong input,do it again"<<endl;
            goto finput;
        }
    }
    else{
        if(day<0||day>NLeap_Month_Day[month]){
            cout<<"wrong input,do it again"<<endl;
            goto finput;
        }
    }
    cout<<"well done!"<<endl;
    CDate date1(year,month,day);
    cout<<"please enter the second date"<<endl;
sinput:
    scanf("%d %d %d",&year,&month,&day);
    if(month<0||month>12){
        cout<<"wrong input,do it again"<<endl;
        goto sinput;
    }
    if(isLeap(year)){
        if(day<0||day>Leap_Month_Day[month]){
            cout<<"wrong input,do it again"<<endl;
            goto sinput;
        }
    }
    else{
        if(day<0||day>NLeap_Month_Day[month]){
            cout<<"wrong input,do it again"<<endl;
            goto sinput;
        }
    }
    cout<<"well done!"<<endl;
    CDate date2(year,month,day);
    int spanDays=date1.Span(date2);
    cout<<"the spandays between ";
    date1.Show();
    cout<<"and ";
    date2.Show();
    cout<<"are "<<spanDays<<" days"<<endl;
    return 0;
}

