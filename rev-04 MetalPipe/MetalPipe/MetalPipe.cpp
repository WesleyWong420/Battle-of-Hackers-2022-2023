#include <Windows.h>
#include <iostream>
#include <thread>
#include "resource.h"
#include "obfuscate.h"
#include "anti_debug.hpp"

#pragma comment(lib, "winmm.lib")

using namespace std;

const int MESSAGE_SIZE = 512;
const string flag(AY_OBFUSCATE("ABOH{1nst4nc3_cr34710n_r4c3_c0nd1710n_CWE-421}"));

int Server()
{
	// [Server] Initialization
	LPCWSTR pwsPipeName = L"\\\\.\\pipe\\battle-of-hackers";
	HANDLE hServerPipe;
	HANDLE hFile = NULL;
	BOOL bSuccess;
	BOOL bPipeRead = TRUE;
	LPWSTR pReadBuf[MESSAGE_SIZE] = { 0 };
	LPDWORD pdwBytesRead = { 0 };

	//wprintf(L"[Server] Creating named pipe: %ls\n", pwsPipeName);
	hServerPipe = CreateNamedPipe(
		pwsPipeName,						// name of our pipe, must be in the form of \\.\pipe\<NAME>
		PIPE_ACCESS_INBOUND,				// open mode, specifying a inbound mode so only client can send data to server
		PIPE_TYPE_MESSAGE | PIPE_NOWAIT,	// MESSAGE mode to send/receive messages in discrete units (instead of a byte stream)
		PIPE_UNLIMITED_INSTANCES,			// number of instanced for this pipe
		2048,								// output buffer size
		2048,								// input buffer size
		20000,								// default timeout value, equal to 50 milliseconds
		NULL								// use default security attributes
	);

	// [Server] Listen for connection
	//wprintf(L"[Server] Waiting for incoming connections...\n");
	bSuccess = ConnectNamedPipe(hServerPipe, NULL);
	wprintf(L"Connected\n");

	Sleep(300);

	// [Server] Read from pipe
	//wprintf(L"[Server] Reading from pipe...\n");
	bPipeRead = ReadFile(hServerPipe, pReadBuf, MESSAGE_SIZE, pdwBytesRead, NULL);
	//wprintf(L"[Server] Received: %s\n", pReadBuf);

	// [Server] Close handle
	CloseHandle(hServerPipe);

	return 0;
}

int main()
{	
	for (int i = 45; i >= 0; i--) {
		// [Server] Start server on seperate thread
		std::thread t1(Server);
		Sleep(300);

		if (security::internal::memory::remote_debugger_present() == security::internal::debug_results::none && security::internal::memory::nt_query_information_process() == security::internal::debug_results::none) {
			// [Client] Initialization
			LPCWSTR pwsPipeName = L"\\\\.\\pipe\\battle-of-hackers";
			HANDLE hFile = NULL;
			DWORD dwFlags = 0;
			BOOL bSuccess;
			DWORD bytesWritten = 0;
			DWORD messageLength;

			// [Client] Connect to pipe server
			//wprintf(L"[Client] Connecting to %s\n", pwsPipeName);
			hFile = CreateFile(pwsPipeName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, dwFlags, NULL);
			//if (hFile != INVALID_HANDLE_VALUE) wprintf(L"[Client] Connection success.\n");
			//else wprintf(L"[Client - Error] Code: %d.\n", GetLastError());

			// [Client] Sending a message
			//wprintf(L"[Client] Sending: '%s'\n", &message[i]);

			bSuccess = WriteFile(hFile, &flag[i], 1, &bytesWritten, NULL);
			//if (!bSuccess) {
			//	wprintf(L"[Client - Error] Error writing to pipe. Error: %d\n", GetLastError());
			//}
			//else {
			//	wprintf(L"[Client] Message sent.\n");
			//}

			// [Client] Close handle
			CloseHandle(hFile);
		}

		t1.join();
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE);
	}

	return 0;
}