#include <stdio.h>
#include <Windows.h>

#define TARGET_VALUE 681

int main(void) {
 int foundCounter = 0;

 HWND hwnd = FindWindowA(NULL, "MySuika");
 if (hwnd == NULL) {printf("Cannot find window");exit(-1);
 }

 DWORD procID;
 GetWindowThreadProcessId(hwnd, &procID);
 HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
 if (handle == NULL) {printf("Cannot obtain process");exit(-1);}

 SYSTEM_INFO systemInfo;
 GetSystemInfo(&systemInfo);

 MEMORY_BASIC_INFORMATION info;
 unsigned char *addressPtr = NULL;

 unsigned char *ptrArr[100000] = {0}; //97 kiB bytes of memory allocated!

 while (1) {
  if(VirtualQueryEx(handle, addressPtr, &info, sizeof(info)) == sizeof(info)){
   if (info.State == MEM_COMMIT && (info.Type == MEM_MAPPED || info.Type == MEM_PRIVATE || info.Type == MEM_IMAGE)) {
    for (addressPtr = (unsigned char *)info.BaseAddress; addressPtr < (unsigned char *)info.BaseAddress + info.RegionSize; addressPtr++) {
     
     // Statement for testing
     if(addressPtr == (unsigned char *) 0x1B3474EB5A0)
      printf("Target found!");

     int valueAtAddress;
     ReadProcessMemory(handle, addressPtr, &valueAtAddress, sizeof(valueAtAddress), NULL);
     if (valueAtAddress == TARGET_VALUE) {
      ptrArr[foundCounter] = addressPtr;
      foundCounter++;
      printf("Target value: %d found at address: %p num: %d\n", valueAtAddress,addressPtr,foundCounter);
     }
    }
   }
   addressPtr += info.RegionSize;
  }
  else{
   int num;
   int val;
   int arrSize = 0;
   while(ptrArr[1] != 0){
    printf("What has the value changed to? ");
    scanf("%d", &num);
    printf("[");
    for(int i=0;i < foundCounter;i++){
     printf("0x%p,", ptrArr[i]);
     ReadProcessMemory(handle, ptrArr[i], &val, sizeof(val), NULL);
     if (val == num){
      ptrArr[arrSize];
      printf("The address %p complied with your macros",ptrArr[i]);
      arrSize++;
     }
    }
    printf("]");
    foundCounter = arrSize;
   }
   printf("Final value at: %p\n", ptrArr[0]);
   break;
  }
 }
 CloseHandle(handle);
 return 0;
}
