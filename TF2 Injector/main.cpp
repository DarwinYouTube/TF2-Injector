#include "library.h"

HWND tf2window;
DWORD procID;
HANDLE HandleTF2;
HANDLE RemoteThread;
char DllPath[MAX_PATH];

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle("Team Fortress 2 Injector by Darwin");

	if (!GetFullPathName(".\\darwin.dll", MAX_PATH, DllPath, 0)) {
		cout << "[-] ��� �� ������� �������� ������ � DLL �����" << endl;
		Sleep(2000);
		exit(-0);
	}

	tf2window = FindWindow(0, "Team Fortress 2");
	if (tf2window) {
		GetWindowThreadProcessId(tf2window, &procID);
		cout << "[+] ������� ���� Team Fortress 2 ������� �������" << endl;
	}

	if (procID == NULL) {
		cout << "[-] ������� ���� Team Fortress 2 �� ������" << endl;
		Sleep(2000);
		exit(-0);
	}

	HandleTF2 = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);

	if (HandleTF2 == NULL) {
		cout << "[-] �� �������� �������� ����� ���� Team Fortress 2" << endl;
		Sleep(2000);
		exit(-0);
	}

	void* AllocateMemory = VirtualAllocEx(HandleTF2, 0, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!AllocateMemory) {
		cout << "[-] ��� �� �������� ���������� ������ � �������� Team Fortress 2" << endl;
		Sleep(2000);
		exit(-0);
	}

	if (!WriteProcessMemory(HandleTF2, AllocateMemory, DllPath, MAX_PATH, 0)) {
		cout << "[-] ��� �� �������� �������� �������� � �������� Team Fortress 2" << endl;
		Sleep(2000);
		exit(-0);
	}

	RemoteThread = CreateRemoteThread(HandleTF2, 0, 0, LPTHREAD_START_ROUTINE(LoadLibraryA), AllocateMemory, 0, 0);
	if (!RemoteThread) {
		cout << "[-] ��� �� ������� ������� ����� � �������� Team Fortress 2" << endl;
		Sleep(2000);
		exit(-0);
	}

	CloseHandle(HandleTF2);
	VirtualFreeEx(HandleTF2, AllocateMemory, 0, MEM_RELEASE);
	CloseHandle(RemoteThread);

	system("cls");
	cout << "\n\n\n [+] ��� ��� ������� ������� � ������� ���� Team Fortress 2" << endl;
	cout << "       [+] ����������� ���������: Darwin" << endl;

	Sleep(1600);
	exit(1);
}