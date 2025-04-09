#include <windows.h>
#include <iostream>
#include <string>
#include <psapi.h>
#include <thread>
#include <chrono>
using namespace std;

void DisplayGlobalMemoryInfo(){
    MEMORYSTATUSEX meminfo;
    meminfo.dwLength = sizeof(meminfo);
    if (GlobalMemoryStatusEx(&meminfo)) {
        cout << "[系统内存信息]" << endl;
        cout << "当前使用百分比：" << meminfo.dwMemoryLoad << "%" << endl;
        cout << "总物理内存：" << meminfo.ullTotalPhys / (1024 * 1024) << "MB" << endl;
        cout << "当前可用物理内存：" << meminfo.ullAvailPhys / (1024 * 1024) << "MB" << endl;
        cout << "总虚拟内存：" << meminfo.ullTotalVirtual / (1024 * 1024) << "MB" << endl;
        cout << "当前可用虚拟内存：" << meminfo.ullAvailVirtual / (1024 * 1024) << "MB" << endl;
    }
    else {
        cerr << "获取系统内存信息失败！" << endl;
    }
}

void DisplayProcessInfo(){
    cout << "[系统中运行的进程]" << endl;
    DWORD Processes[1024], returnBytes;
    if (!EnumProcesses(Processes, sizeof(Processes), &returnBytes)) {
        cerr << "获取进程列表失败！" << endl;
        return;
    }
    int ProcessCount = returnBytes / sizeof(DWORD);
    int viableProcessCount = 0;
    for (int i = 0; i < ProcessCount; i++) {
        if (Processes[i] != 0) {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Processes[i]);
            if (hProcess) {
                wchar_t processName[MAX_PATH] = L"unknown";
                HMODULE hMod;
                DWORD cbNeeded;
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                    GetModuleBaseNameW(hProcess, hMod, processName, sizeof(processName) / sizeof(wchar_t));
                    wcout << Processes[i]<<" "<< processName << endl;
                    viableProcessCount++;
                } 
            }
            CloseHandle(hProcess);
        }
    }
    cout<<"共计"<<viableProcessCount<<"个可访问进程"<<endl;
    return;
}

void DisplayMemoryLayout(HANDLE processHandle){
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    cout << "[进程地址空间布局]" << endl;
    cout << "系统地址空间起始地址：" << sysinfo.lpMinimumApplicationAddress << endl;
    cout << "系统地址空间结束地址：" << sysinfo.lpMaximumApplicationAddress << endl;

    MEMORY_BASIC_INFORMATION meminfo;
    PVOID baseAddress = sysinfo.lpMinimumApplicationAddress;

    while (baseAddress < sysinfo.lpMaximumApplicationAddress) {
        if (VirtualQueryEx(processHandle, baseAddress, &meminfo, sizeof(meminfo)) == 0) {
            DWORD dwError = GetLastError();
            cerr << "获取内存信息失败！错误代码：" << dwError << endl;
            return;
        }
        cout << "基地址：" << meminfo.BaseAddress << endl;
        cout << "区域大小：" << meminfo.RegionSize / 1024 << "KB" << endl;
        if (meminfo.State == MEM_COMMIT) {
            cout << "状态：已提交" << endl;
        } else if (meminfo.State == MEM_FREE) {
            cout << "状态：空闲" << endl;
        } else if (meminfo.State == MEM_RESERVE) {
            cout << "状态：保留" << endl;
        }
        baseAddress = (PVOID)((long long)meminfo.BaseAddress + meminfo.RegionSize);
    }
}

void DisplayWorkingSetInfo(HANDLE processHandle) {
    PSAPI_WORKING_SET_INFORMATION* wsInfo=(PSAPI_WORKING_SET_INFORMATION*)malloc(1024*1024);
    if(!wsInfo){
        cerr<<"内存分配失败！"<<endl;
        return;
    }
    if (QueryWorkingSet(processHandle, wsInfo, 1024*1024)) {
        cout << "[工作集信息]" << endl;
        cout << "工作集内物理页数: " << wsInfo->NumberOfEntries << endl;
        cout << "工作集大小: " << (wsInfo->NumberOfEntries * 4096) / (1024 * 1024) << "MB" << endl;
    } else {
        DWORD dwError = GetLastError();
        cerr << "无法获取工作集信息! 错误代码：" << dwError << endl;
    }
}


int main(){
    system("chcp 65001");
    int control=-1;

    cout<<"请选择您的使用方式："<<endl;
    cout<<"0.查看系统内存信息"<<endl;
    cout<<"1.查看进程内存信息"<<endl;
    cin>>control;
    system("cls");

    if(control==0){
        while(true){
            DisplayGlobalMemoryInfo();
            Sleep(2000);
            system("cls");
        }
        return 0;
    }
    else if(control==1){
        DisplayProcessInfo();
        cout << "请输入进程ID：";
        DWORD processID;
        cin >> processID;
        system("cls");
        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
        if (processHandle == NULL) {
            DWORD dwError = GetLastError();
            cerr << "打开进程失败！错误代码：" << dwError << endl;
            return -1;
        }
        while(true){
            DisplayMemoryLayout(processHandle);
            Sleep(3000);
            system("cls");
            DisplayWorkingSetInfo(processHandle);
            Sleep(3000);
            system("cls");
        }    
        CloseHandle(processHandle);
        return 0;
    }
    else{
        cerr<<"无效的输入！"<<endl;
        return -1;
    }

}