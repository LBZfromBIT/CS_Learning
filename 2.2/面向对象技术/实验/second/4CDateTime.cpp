#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class CDateTime{
    private:
    int year;
    int month;
    int day;
    int hour;//default 24 hours
    int minute;
    int second;
    int weekday;
    public:
    CDateTime();
    static CDateTime Now(){
        return CDateTime();
    };
    void ShowTime12();
    void ShowTime24();
    void ShowDate();
};

//the init function
CDateTime::CDateTime(){//get the current time as default
    time_t now;
    time(&now);
    tm *t=localtime(&now);
    year=t->tm_year+1900;
    month=t->tm_mon+1;
    day=t->tm_mday;
    hour=t->tm_hour;
    minute=t->tm_min;
    second=t->tm_sec;
    weekday=t->tm_wday;
}

//show the time in 12 hours
void CDateTime::ShowTime12(){
    if(hour>=12){
        cout<<hour-12<<":"<<minute<<":"<<second<<" PM"<<endl;
    }
    else{
        cout<<hour<<":"<<minute<<":"<<second<<" AM"<<endl;
    }
}
//show the time in 24 hours
void CDateTime::ShowTime24(){
    cout<<hour<<":"<<minute<<":"<<second<<endl;
}
//show the date
void CDateTime::ShowDate(){
    string weekname[7]={"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};
    cout<<year<<"年"<<month<<"月"<<day<<"日"<<weekname[weekday]<<endl;
}

int main(){
    //use the loop to show the time in dynamiclly
    int tmp=3;
    CDateTime dt;
    while(tmp>0){
        dt=CDateTime::Now();
        dt.ShowDate();
        dt.ShowTime24();
        dt.ShowTime12();
        Sleep(1000);
        tmp--;
        system("cls");//clear the screnn
    }
    return 0;
}