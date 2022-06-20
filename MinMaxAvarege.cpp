
#include <windows.h>
#include <iostream>
using namespace std;
namespace maxMinTempAvarageArr {
    volatile int n, max_id, min_id, mid;
    volatile int* arr;
    DWORD WINAPI min_max()
    {
        min_id = 0;
        max_id = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i] > arr[max_id]) {
                max_id = i;
            }
            Sleep(7);
            if (arr[i] < arr[min_id]) {
                min_id = i;
            }
            Sleep(7);
        }
        cout << "min = " << arr[min_id] << "\nmax = " << arr[max_id] << "\n";
        return 0;
    }
    void WINAPI average() {
        int sum = arr[0];
        for (int i = 1; i < n; i++) {
            sum += arr[i];
            Sleep(12);
        }
        mid = sum / n;
        cout << "average = " << mid << "\n";
    }
}
    int main()
    {
        HANDLE hmin_max;
        DWORD IDmin_max;
        HANDLE haverage;
        DWORD IDaverage;
        cout << "enter size of array:\nsizeArr = ";

        int tempSize;
        cin >> tempSize;
        maxMinTempAvarageArr::n = tempSize;

        maxMinTempAvarageArr::arr = new int[maxMinTempAvarageArr::n];
        cout << "enter array:\n";
        for (int i = 0; i < maxMinTempAvarageArr::n; i++) {
            cout << "a[" << i << "] = ";
            int elem;
            cin >> elem;
            maxMinTempAvarageArr::arr[i] = elem;
        }
        hmin_max = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)maxMinTempAvarageArr::min_max, NULL, 0, &IDmin_max);
        if (hmin_max == NULL)
            return GetLastError();

        haverage = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)maxMinTempAvarageArr::average, NULL, 0, &IDaverage);
        if (haverage == NULL)
            return GetLastError();
        WaitForSingleObject(hmin_max, INFINITE);
        WaitForSingleObject(haverage, INFINITE);
        CloseHandle(hmin_max);
        CloseHandle(haverage);
        maxMinTempAvarageArr::arr[maxMinTempAvarageArr::min_id] = maxMinTempAvarageArr::arr[maxMinTempAvarageArr::max_id] = maxMinTempAvarageArr::mid;
        for (int i = 0; i < maxMinTempAvarageArr::n; i++) {
            cout << maxMinTempAvarageArr::arr[i] << " ";
        }
        system("pause");
        return 0;
    }
