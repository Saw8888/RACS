#include <stdio.h>
#include <Windows.h>

//#define TARGET_VALUE 760
//#define MAX_ADDRESSES 100000

unsigned char *findData(const int TARGET_VALUE, HANDLE handle){
 int foundCounter = 0;
 unsigned char *ptrArr[100000] = {0};

 SYSTEM_INFO systemInfo;
 GetSystemInfo(&systemInfo);

 MEMORY_BASIC_INFORMATION mbi;
 unsigned char *addressPtr = (unsigned char *)systemInfo.lpMinimumApplicationAddress;
 SIZE_T bytesRead;

 while (addressPtr < systemInfo.lpMaximumApplicationAddress && foundCounter < 100000) {
  if (VirtualQueryEx(handle, addressPtr, &mbi, sizeof(mbi)) != 0) {
   if (mbi.State == MEM_COMMIT && (mbi.Protect == PAGE_READWRITE || mbi.Protect == PAGE_READONLY || mbi.Protect == PAGE_EXECUTE_READWRITE || mbi.Protect == PAGE_EXECUTE_READ)) {
    unsigned char *buffer = (unsigned char *)malloc(mbi.RegionSize);
    if (buffer != NULL) {
     if (ReadProcessMemory(handle, addressPtr, buffer, mbi.RegionSize, &bytesRead)) {
      for (SIZE_T i = 0; i < bytesRead - sizeof(int); i++) {
       if (*(int *)(buffer + i) == TARGET_VALUE) {
        ptrArr[foundCounter++] = addressPtr + i;
        if (foundCounter >= 100000) {
         break;
        }
       }
      }
     }
     free(buffer);
    }
   }
   addressPtr += mbi.RegionSize;
  } else {
   // If VirtualQueryEx fails, move to the next page
   addressPtr += 0x1000; // Skip 4KB
  }
 }
 return ptrArr;
}

int main(void) {
 HWND hwnd = FindWindowA(NULL, "MySuika"); // Window title of the target process
 if (hwnd == NULL) {
  printf("Cannot find window\n");
  return -1;
 }

 DWORD procID;
 GetWindowThreadProcessId(hwnd, &procID);
 HANDLE handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, procID);
 if (handle == NULL) {
  printf("Cannot obtain process\n");
  return -1;
 }

 unsigned char *ptrArr = findData(11,handle);
 for (int i = 0; i < 10000; i++) {
  printf("%p\n", ptrArr[i]);
 }

 CloseHandle(handle);
 return 0;
}