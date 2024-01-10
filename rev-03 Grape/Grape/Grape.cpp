#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <tlhelp32.h>
#include "sha.h"
#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"
#include "obfuscate.h"

unsigned CountProcesses(const std::wstring& processName)
{
    unsigned nCount = 0;
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    if (Process32First(processesSnapshot, &processInfo))
    {
        do
        {
            if (!processName.compare(processInfo.szExeFile))
                ++nCount;
        } while (Process32Next(processesSnapshot, &processInfo));
    }
    CloseHandle(processesSnapshot);

    return nCount;
}

std::string AESDecrypt() {
    using namespace CryptoPP; using namespace std;

    HexEncoder encoder(new FileSink(cout));

    string sKey(AY_OBFUSCATE("battle-of-hackers"));
    string sIV(AY_OBFUSCATE("anti-tampering"));

    SecByteBlock key((const byte*)sKey.data(), AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv((const byte*)sIV.data(), AES::BLOCKSIZE);

    string cipher(AY_OBFUSCATE("82218172C7A3247CA0FB83FE2F065E25BCF58013A2E3599342491A1AC8191BBF"));
    string unhex, recovered;

    StringSource ss(cipher, true,
        new HexDecoder(
            new StringSink(unhex)
        ) // HexDecoder
    ); // StringSource

    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(unhex, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const Exception& e)
    {
        exit(1);
    }

    return recovered;
}

void detectEmulator() {

    HMODULE hModule;

    hModule = GetModuleHandle(L"kernel32.dll");
    if (hModule == NULL) {
        exit;
    }

    if (GetProcAddress(hModule, "wine_get_unix_file_name") != NULL) {

        hModule = GetModuleHandle(L"ntdll.dll");
        if (hModule == NULL) {
            exit;
        }

        if (GetProcAddress(hModule, "wine_get_version") != NULL) {

            if (CountProcesses(L"winlogon.exe") == 0) {

                HKEY hKey = nullptr;
                LONG result = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Wine\\Direct2D"), 0, KEY_READ, &hKey);

                if (result == ERROR_SUCCESS) {

                    if (RegQueryValueEx(hKey, TEXT("max_version_factory"), NULL, NULL, NULL, NULL) != ERROR_FILE_NOT_FOUND) {
                        RegCloseKey(hKey);
                        std::cout << AESDecrypt();
                        abort();
                    }
                }
            }
        }
    }

    std::cout << "The fairest grape is not for every mouth; nor is the sweetest wine for every lip.\0\n";
}

BOOL codeChecksum() {
    using namespace CryptoPP; using namespace std;

    // Calculate the hash of the function using SHA-256
    byte hash[SHA256::DIGESTSIZE];
    SHA256 hash_function;

    void (*foo)();
    foo = &detectEmulator;

    hash_function.Update((const byte*)foo, 576);
    hash_function.Final(hash);

    // Print the hash
    for (int i = 0; i < SHA256::DIGESTSIZE; i++) {
        cout << hex << setw(2) << setfill('0') << (int)hash[i] << " ";
    }
    cout << endl;

    // Compare the hash
    byte expected_hash[] = { 0x79, 0x0c, 0x9f, 0x8d, 0xda, 0xef, 0xde, 0x0a, 0x33, 0x71, 0xd4, 0xac, 0xd5, 0xc2, 0x13, 0xe2, 0x45, 0x5c, 0x08, 0x3d, 0xcd, 0x9d, 0x15, 0xc1, 0x46, 0x47, 0x8e, 0xe9, 0xcd, 0x6c, 0x90, 0x82 };
    bool is_equal = true;
    for (int i = 0; i < SHA256::DIGESTSIZE; i++) {
        if (hash[i] != expected_hash[i]) {
            is_equal = false;
            break;
        }
    }

    return is_equal;
}

int main()
{
   if (codeChecksum()) {
       detectEmulator();
   }
}
