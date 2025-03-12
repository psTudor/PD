#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey, hSubKey;
    DWORD i = 0;
    DWORD retCode;
    char achKey[255];
    DWORD cbName;
    char lpData[32767];
    DWORD dwDataSize;
    DWORD dwType;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        printf("Eroare la deschiderea cheii HKLM\\%s\n", TEXT("SYSTEM\\CurrentControlSet\\Services"));
        return 1;
    } 

    
    i = 0;
    while (1) {
        cbName = 255;
        retCode = RegEnumKeyExA(hKey, i, achKey, &cbName, NULL, NULL, NULL, NULL);

        if (retCode != ERROR_SUCCESS) {
            break;
        }

        
        if (RegOpenKeyExA(hKey, achKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
            
            dwDataSize = 32767;
            if (RegQueryValueExA(hSubKey, "ImagePath", NULL, &dwType, (LPBYTE)lpData, &dwDataSize) == ERROR_SUCCESS) {
                printf("%s: %s\n", achKey, lpData);
            }

            RegCloseKey(hSubKey);
        }

        i++;
    }

    
    RegCloseKey(hKey);

    return 0;
}
