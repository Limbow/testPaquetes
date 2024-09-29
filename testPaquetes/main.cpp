#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h> // Para GetAsyncKeyState
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <TlHelp32.h>

using namespace std;

// Funciones para manipular la memoria
//DWORD GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
void MemoryRead(HANDLE hProcess, uintptr_t address, DWORD& value);
void SendKey(int key);
void MouseMoveAndClick(int x, int y);

void ChangeProcessName(const char* newName) {
    HANDLE hProcess = GetCurrentProcess();
    WCHAR szFileName[MAX_PATH];
    GetModuleFileNameW(NULL, szFileName, MAX_PATH);
    WCHAR szNewName[MAX_PATH];
    mbstowcs(szNewName, newName, MAX_PATH);
    MoveFileW(szFileName, szNewName);
}

int main() {

    ChangeProcessName("Discord.exe");
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in dest;
    char packet[7] = {0x24, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00};; // Paquete en formato hexadecimal
    int packetSize = sizeof(packet);
    int sendResult;

    // Inicializa Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Fallo en la inicialización de Winsock.\n");
        return 1;
    }

    // Crea el socket RAW
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock == INVALID_SOCKET) {
        printf("Error al crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configura la dirección del destino
    dest.sin_family = AF_INET;
    dest.sin_port = htons(9502); // Puerto, ajusta según sea necesario
    dest.sin_addr.s_addr = inet_addr("45.235.98.26"); // Dirección IP del juego



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    POINT mousePos;
    POINT inicioPos;

    // Captura la posición inicial del mouse
    MessageBoxA(NULL, "Pon el mouse sobre tu cabeza y presiona enter", "Posición", MB_OK);
    GetCursorPos(&mousePos);
    inicioPos = mousePos;
    MessageBoxA(NULL, "Listo", "Posición", MB_OK);

    // Variables de memoria
    DWORD procId = 0;
    HWND hwnd = FindWindowA(NULL, "your game"); 
    GetWindowThreadProcessId(hwnd, &procId);

    uintptr_t  baseAdr = 0x00400000;// Reemplaza "ImperiumClassic.exe" por el nombre real del módulo
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, procId);

    const DWORD offsetX1 = 0xc;
	const DWORD offsetX2 = 0x70;
	const DWORD offsetX3 =0xbc;
	const DWORD offsetX4 =0x2c;
	const DWORD offsetX5 =0x1ac;
	const DWORD offsetX6 =0x2c;
	const DWORD offsetX7 =0x7b8;

    const DWORD offsetY1 = 0xc;
    const DWORD offsetY2 = 0x9c;
    const DWORD offsetY3 = 0xe8;
    const DWORD offsetY4 = 0x188;
    const DWORD offsetY5 = 0x18;
    const DWORD offsetY6 = 0x0;
    const DWORD offsetY7 = 0xa98;

    const DWORD offsetAmigoX1 = 0xc;
    const DWORD offsetAmigoX2 = 0xc0;
    const DWORD offsetAmigoX3 = 0x8b4;
    const DWORD offsetAmigoX4 = 0x214;
    const DWORD offsetAmigoX5 = 0x214;
    const DWORD offsetAmigoX6 = 0x1fc;
    const DWORD offsetAmigoX7 = 0x68;

    const DWORD offsetAmigoY1 = 0xc;
    const DWORD offsetAmigoY2 = 0x2c;
    const DWORD offsetAmigoY3 = 0x78;
    const DWORD offsetAmigoY4 = 0x38;
    const DWORD offsetAmigoY5 = 0x14;
    const DWORD offsetAmigoY6 = 0x4;
    const DWORD offsetAmigoY7 = 0x6c;

    DWORD StaticoffsetX = 0x007F1AE4;
    DWORD StaticoffsetY = 0x007F1AE4;
    DWORD StaticoffsetXAmigo = 0x007F1AE4;
    DWORD StaticoffsetYAmigo = 0x007F1AE4;

    uintptr_t adrBasura = 0;

	DWORD sXmia, sYmia, sXamigo, sYamigo;
    // Bucle principal
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break; // Salir si se presiona ESC
        }
        if (GetAsyncKeyState(VK_INSERT)){
            HWND hwnd = GetConsoleWindow();
            ShowWindow(hwnd, SW_HIDE);
        }

        // Leer coordenadas X y Y

		ReadProcessMemory(hProcess, (PBYTE*)(baseAdr), &sXmia, sizeof(sXmia), 0);
		ReadProcessMemory(hProcess, (PBYTE*)(baseAdr + StaticoffsetX), &adrBasura, sizeof(sXmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetX1), &adrBasura, sizeof(sXmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetX2), &adrBasura, sizeof(sXmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetX3), &adrBasura, sizeof(sXmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetX4), &adrBasura, sizeof(sXmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetX5), &adrBasura, sizeof(sXmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetX6), &adrBasura, sizeof(sXmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetX7), &sXmia, sizeof(sXmia), 0);
        sXmia = sXmia+2;

		ReadProcessMemory(hProcess, (PBYTE*)(baseAdr), &sYmia, sizeof(sYmia), 0);
		ReadProcessMemory(hProcess, (PBYTE*)(baseAdr + StaticoffsetY), &sYmia, sizeof(sYmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetY1), &adrBasura, sizeof(sYmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetY2), &adrBasura, sizeof(sYmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetY3), &adrBasura, sizeof(sYmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetY4), &adrBasura, sizeof(sYmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetY5), &adrBasura, sizeof(sYmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetY6), &adrBasura, sizeof(sYmia), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetY7), &sYmia, sizeof(sYmia), 0);
        sYmia = sYmia+2;

        ReadProcessMemory(hProcess, (PBYTE*)(baseAdr), &sXamigo, sizeof(sXamigo), 0);
        ReadProcessMemory(hProcess, (PBYTE*)(baseAdr + StaticoffsetXAmigo), &sXamigo, sizeof(sXamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoX1), &adrBasura, sizeof(sXamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoX2), &adrBasura, sizeof(sXamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoX3), &adrBasura, sizeof(sXamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoX4), &adrBasura, sizeof(sXamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoX5), &adrBasura, sizeof(sXamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoX6), &adrBasura, sizeof(sXamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoX7), &sXamigo, sizeof(sXamigo), 0);
        sXamigo = sXamigo+2;

        ReadProcessMemory(hProcess, (PBYTE*)(baseAdr), &sYamigo, sizeof(sYamigo), 0);
        ReadProcessMemory(hProcess, (PBYTE*)(baseAdr + StaticoffsetYAmigo), &sYamigo, sizeof(sYamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoY1), &adrBasura, sizeof(sYamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoY2), &adrBasura, sizeof(sYamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoY3), &adrBasura, sizeof(sYamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoY4), &adrBasura, sizeof(sYamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoY5), &adrBasura, sizeof(sYamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoY6), &adrBasura, sizeof(sYamigo), 0);
    	ReadProcessMemory(hProcess, (PBYTE*)(adrBasura + offsetAmigoY7), &sYamigo, sizeof(sYamigo), 0);
        sYamigo = sYamigo+2;

        // Calcula la distancia
        int deltaTileX = sXamigo - sXmia;
        int deltaTileY = sYamigo - sYmia;
        int tamanoTile = 32;

        int distanciaX = deltaTileX * tamanoTile;
        int distanciaY = deltaTileY * tamanoTile;



        // Movimiento del mouse
        if (GetAsyncKeyState(0x51)) { // Tecla Q
            packet[1] = sXamigo - 0x18;
            packet[3] = sYamigo - 0x18;
            SendKey(0x31); // Envía "1"
            sendResult = sendto(sock, packet, packetSize, 0, (struct sockaddr*)&dest, sizeof(dest));
            if (sendResult == SOCKET_ERROR) {
                printf("Error al enviar el paquete: %d\n", WSAGetLastError());
                break;
            }
            //SetCursorPos(inicioPos.x + distanciaX, inicioPos.y + distanciaY);
            Sleep(1);
//            MOUSEEVENTF_LEFTDOWN;
//            MOUSEEVENTF_LEFTUP;
            Sleep(10);
        }

        if (GetAsyncKeyState(0x52)) { // Tecla R
            packet[1] = sXmia - 0x18;
            packet[3] = sYmia - 0x18;
            SendKey(0x31); // Envía "1"
            sendResult = sendto(sock, packet, packetSize, 0, (struct sockaddr*)&dest, sizeof(dest));
            if (sendResult == SOCKET_ERROR) {
                printf("Error al enviar el paquete: %d\n", WSAGetLastError());
                break;
            }
//            SetCursorPos(inicioPos.x, inicioPos.y);
            Sleep(1);
//            MOUSEEVENTF_LEFTDOWN;
//            MOUSEEVENTF_LEFTUP;
            Sleep(10);
        }
    }

    // Limpieza
    closesocket(sock);
    WSACleanup();
    CloseHandle(hProcess);
    return 0;
}


//DWORD GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
//    DWORD_PTR modBaseAddr = 0;
//    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
//    if (hSnap != INVALID_HANDLE_VALUE) {
//        MODULEENTRY32 modEntry;
//        modEntry.dwSize = sizeof(modEntry);
//        if (Module32First(hSnap, &modEntry)) {
//            do {
//                if (!_wcsicmp(modEntry.szModule, modName)) {
//                    modBaseAddr = (DWORD_PTR)modEntry.modBaseAddr;
//                    break;
//                }
//            } while (Module32Next(hSnap, &modEntry));
//        }
//    }
//    CloseHandle(hSnap);
//    return modBaseAddr;
//}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i) {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}

void SendKey(int key) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(5);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}


