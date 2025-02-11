#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int processes_list(){
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if (hProcessSnap == INVALID_HANDLE_VALUE){
        printf("ERROR IN GATHERING PROCESSES SNAPSHOT!\n");
        CloseHandle(hProcessSnap);
        return -1;
    }

    if (!Process32First(hProcessSnap, &pe32)){
        printf("ERROR IN GATHERING FIRST PROCESS SNAPSHOT!\n");
        CloseHandle(hProcessSnap);
        return -1;
    }

    printf("LIVE PROCESSES LIST:\n");
    do {
        printf("PID: %d | name: %s\n", pe32.th32ProcessID, pe32.szExeFile);

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return 0;
}


int main(){
    processes_list();
   
    return 0;
}
