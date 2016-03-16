/*
 * InjectedCode.h
 *
 *  Created on: 02/04/2010
 *      Author: TheAnswer
 */

#ifndef INJECTEDCODE_H_
#define INJECTEDCODE_H_


typedef UINT  (WINAPI *WAIT_PROC)(HANDLE, DWORD); // WaitForSingleObject
typedef BOOL  (WINAPI *CLOSE_PROC)(HANDLE);       // CloseHandle
typedef BOOL  (WINAPI *DELETE_PROC)(LPCTSTR);     // DeleteFile
typedef VOID  (WINAPI *EXIT_PROC)(DWORD);         // ExitProcess
typedef HANDLE (WINAPI *CREATE_PROC)(LPCTSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE); // Createfile
typedef BOOL (WINAPI   *WRITE_PROC)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef UINT (WINAPI   *EXEC_PROC) (LPCSTR, UINT); // WinExec
typedef HRESULT (WINAPI *DOWN_PROC) (LPUNKNOWN, LPCTSTR, LPCTSTR, DWORD, LPUNKNOWN); // URLDownloadToFileA
typedef HRESULT (WINAPI *DOWNTOCACHE_PROC) (LPUNKNOWN, LPCSTR, LPTSTR, DWORD, DWORD, LPUNKNOWN); //URLDownloadToCacheFile
typedef DWORD	(WINAPI *GETHEIGHT_PROC) (DWORD, LPVOID, LPVOID); // GetHeight
typedef LPVOID	(WINAPI *VIRTUALALLOC_PROC) (LPVOID, SIZE_T, DWORD, DWORD); //VirtualAlloc
typedef BOOL	(WINAPI *VIRTUALFREE_PROC)	(LPVOID, SIZE_T, DWORD); //VirtualFree
typedef BOOL	(WINAPI *SETENDOFFILE_PROC)	(HANDLE); //SetEndOfFile
typedef	DWORD	(WINAPI *TELEPORT_PROC)		(DWORD, DWORD, float, float); // Teleport
typedef	DWORD	(WINAPI *SLEEP_PROC)		(DWORD);
typedef char*	(WINAPI *ITOA_PROC)			(int, char*, int);
typedef int		(WINAPI *SPRINTF_PROC)		(char*, const char*, ...);
typedef void	(WINAPI *PRINT_PROC)		(const char*, ...);
typedef void	(WINAPI *SETFLAGS_PROC)		(DWORD);
typedef DWORD 	(WINAPI *HTONL_PROC)		(DWORD);
typedef float	(WINAPI *NOISE_PROC)		(DWORD, float, float);

typedef DWORD (WINAPI *REMOTETHREAD)(LPVOID);     // Our remote code

typedef struct {
   WAIT_PROC fnWaitForSingleObject;
   CLOSE_PROC fnCloseHandle;
   DELETE_PROC fnDeleteFile;
   EXIT_PROC fnExitProcess;
   HTONL_PROC fnHtonl;
   HANDLE hProcess;
   CREATE_PROC fnCreateFile;
   WRITE_PROC fnWriteFile;
   EXEC_PROC fnWinExec;
   PRINT_PROC fnPrint;
   SETFLAGS_PROC fnSetFlags;
   NOISE_PROC fnNoise;
   char szFileName[MAX_PATH];
   char terrainFile[MAX_PATH];
   unsigned char file[100];
   DWORD clientAppearanceAddress;
   GETHEIGHT_PROC fnGetHeight;
   VIRTUALALLOC_PROC fnVirtualAlloc;
   VIRTUALFREE_PROC	fnVirtualFree;
   SETENDOFFILE_PROC fnSetEndOfFile;
   DWORD clientControllerPointer;
   DWORD messageQueueDataTransformPointer;
   TELEPORT_PROC fnTeleport;
   SLEEP_PROC fnSleep;
   ITOA_PROC fnItoa;
   SPRINTF_PROC fnSprintf;
   DWORD x;
   DWORD y;
   DWORD heightAddress;
   DWORD affectorHeightFractalAddress;
} INJECT;

typedef struct {
	float posX;
	float posZ;
	float posY;
} Coordinates;

PVOID GetFunctionAddr(PVOID func) {
   #ifdef _DEBUG
       // get address of function from the JMP <relative> instruction
       DWORD *offset = (BYTE *)func + 1;
       return (PVOID)(*offset + (BYTE *)func + 5);
   #else
       return func;
   #endif
}

DWORD WINAPI GetHeight(DWORD thisPointer, void* coords, void* posZ) {
	//@bool getHeight(Coordinates* coords, float* posZ);
	int (*getHeight)(void*, void*);
	*(int*)&getHeight = 0x00B5DF50;

	asm("push %ecx");
	asm("movl 8(%ebp), %ecx"); // moving this pointer

	int ret = getHeight(coords, posZ); // magic;

	asm("pop %ecx");

	return ret;
}



void WINAPI Teleport(DWORD CreatureControllerPointer, DWORD MessageQueueDataTransform, float x, float y) {
	int (*handleNetUpdateTransform)(DWORD);
	*(int*)&handleNetUpdateTransform = 0x006E4E50;

	asm("push %ecx");
	asm("movl 8(%ebp), %ecx"); // moving this pointer

	float* queueData = (float*) MessageQueueDataTransform;

	queueData[5] = x; // X
	queueData[9] = -1000.f;// Z;
	queueData[13] = y;// y;

	handleNetUpdateTransform(MessageQueueDataTransform); // magic;

	asm("pop %ecx");
}

/*void WINAPI setFlags(DWORD flag) {

}

void WINAPI print(const char*, ...) {

}*/

void WINAPI GetCurrentPlayerPosition(DWORD CreatureObjectPointer) {

}

float WINAPI GetNoise(DWORD thisaddress, float x, float y) {
	double (*noise)(DWORD, DWORD, DWORD, DWORD);
	*(int*)&noise = 0x013E7C00;

	register float result;

	asm("push %ecx");
	asm("movl 8(%ebp), %ecx"); // moving this pointer

	noise(*(DWORD*)&(x), *(DWORD*)&(y), 0, 0); // magic;

	asm("pop %ecx");

	//return (float)result;
}

DWORD WINAPI RemoteThread(INJECT *remote) {
	remote->fnSleep(20000);

	HANDLE hFile;
	DWORD dwResult;

	float* heights = (float *)remote->fnVirtualAlloc(NULL, sizeof(float) * 256 * 256,
					   MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	hFile = remote->fnCreateFile(
						(const TCHAR*)remote->szFileName,     // name of the write
						GENERIC_WRITE,          // open for writing
						0,                      // do not share
						NULL,                   // default security
						CREATE_ALWAYS,          // overwrite existing
						FILE_ATTRIBUTE_NORMAL,  // normal file
						NULL);                  // no attr. template

	int i = 0;
	for (int x = 0; x < 256; ++x) {
		for (int y = 0; y < 256; ++y) {
			heights[i++] = remote->fnNoise(remote->affectorHeightFractalAddress, x, y);
		}
	}

	remote->fnWriteFile(hFile, heights, sizeof(float) * 256 * 256, &dwResult, NULL);

	remote->fnCloseHandle(hFile);

	remote->fnSetFlags(3);
	remote->fnPrint(remote->szFileName);

	/*void* (*createClientProceduralTerrain)(char*);

	*(int*)&createClientProceduralTerrain = 0x00B262A0;

	void* address = createClientProceduralTerrain(remote->terrainFile);


	remote->fnPrint(remote->szFileName, 2, 3);*/

	/*
	 *
	 *
	 * mov     eax, [eax+28h]
	 * push    0
	 * push    offset ??_R0?AVProceduralTerrainAppearance@@@8 ; ProceduralTerrainAppearance `RTTI Type Descriptor'
	 * push    offset ??_R0?AVAppearance@@@8 ; Appearance `RTTI Type Descriptor'
	 * push    0
	 * push    eax
	 * call    ___RTDynamicCast ; Call Procedure
	 *
	 */
/*
	void* (*getTerrainObjectPointer)();
	*(int*)&getTerrainObjectPointer = 0x00B5B710;

	void* creaturePointer = getCreatureObjectPointer();

	//asm("movl 8(%ebp), %ecx"); // moving this pointer

	int* pointer = (int*) creaturePointer;

	void* creatureController = (void*) pointer[10];

	remote->fnSetFlags(3);
	remote->fnPrint(remote->szFileName, (DWORD)creatureController, 2);

	for (int i = 0; i < 10; ++i) {
		remote->fnSleep(1000);

		float posX, posY;
		posX = ((float*)pointer)[43];
		posY = ((float*)pointer)[44];

		//posY = remote->fnHtonl(posX);

		remote->fnSetFlags(3);
		remote->fnPrint(remote->szFileName, posX, posY);
	}

	((float*)pointer)[44] = 0;
*/

	return 1;
}

DWORD WINAPI RemoteThread3(INJECT *remote) {
	remote->fnSleep(1000);

	HANDLE hFile;
	DWORD dwResult;
	char filename[MAX_PATH];

	Coordinates coords;

	coords.posX = 0;
	coords.posY = 0;
	coords.posZ = 0;

	float* addZ = (float*) remote->heightAddress;

	while (true) {
		remote->fnSleep(250);

		float* addX = (float*) remote->x;
		float* addY = (float*) remote->y;

		coords.posX = *addX;
		coords.posY = *addY;

		float height;

		remote->fnGetHeight(remote->clientAppearanceAddress, &coords, &height);

		*addZ = height;

	}


/*	remote->fnGetHeight(remote->clientAppearanceAddress, &coords, &height)

	float* heights = (float *)remote->fnVirtualAlloc(NULL, sizeof(float) * 40,
				   MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	float height;

	for (int x = remote->x; x <= 7640; x += 80) {
		for (int y = -7640; y <= 7640; y += 80) {
			remote->fnTeleport(remote->clientControllerPointer, remote->messageQueueDataTransformPointer, (float)x, (float)y);
			remote->fnSleep(1000);

			remote->fnSprintf(filename, remote->szFileName, x, y);

			hFile = remote->fnCreateFile(
					(const TCHAR*) filename,     // name of the write
					GENERIC_WRITE,          // open for writing
					0,                      // do not share
					NULL,                   // default security
					CREATE_ALWAYS,          // overwrite existing
					FILE_ATTRIBUTE_NORMAL,  // normal file
					NULL);                  // no attr. template

			for (int i = -40; i <= 40; ++i) {
				for (int j = -40; j <= 40; ++j) {
					coords.posX = x + i;
					coords.posY = y + j;

					int tests = 0;

					while (!remote->fnGetHeight(remote->clientAppearanceAddress, &coords, &height) && tests < 2) {
						remote->fnTeleport(remote->clientControllerPointer, remote->messageQueueDataTransformPointer, (float)x, (float)y);
						remote->fnSleep(200);
						++tests;
						height = -1600;
					}

					if (j < 0) {
						heights[j + 40] = height;
					} else if (j == 0) {
						remote->fnWriteFile(hFile, heights, sizeof(float) * 40, &dwResult, NULL);
						remote->fnSetEndOfFile(hFile);
						remote->fnWriteFile(hFile, &height, sizeof(float), &dwResult, NULL);
						remote->fnSetEndOfFile(hFile);
					} else if (j > 0) {
						heights[j - 1] = height;
					}
				}
				remote->fnWriteFile(hFile, heights, sizeof(float) * 40, &dwResult, NULL);
				remote->fnSetEndOfFile(hFile);
			}

			remote->fnCloseHandle(hFile);
		}
	}

	//remote->fnVirtualFree(heights, 0, MEM_RELEASE);
*/
    return 1;
}


#endif /* INJECTEDCODE_H_ */
