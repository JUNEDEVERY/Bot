#include "stdio.h"
#include "Windows.h"
#define SIZE_BUFFER 512

int main()
{
	system("chcp 1251 > nul");
	LPSTR pipeName = "\\\\.\\pipe\Pipe";
	BOOL flag = TRUE;
	char message_user[SIZE_BUFFER];
	DWORD size_buf = SIZE_BUFFER; // размер буффера для записи
	DWORD actual_read_bite; // размер реально записано байт;
	DWORD actual_write_bite; // размер реально записано байт;
	LPWSTR buffer;
	while (TRUE) {

		char message_user[SIZE_BUFFER];
		HANDLE myPIPE = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		DWORD dMode = PIPE_READMODE_MESSAGE;
		BOOL isConnected = SetNamedPipeHandleState(pipeName, &dMode, NULL, NULL);
		if (isConnected == FALSE) {
			printf("Сервер временно недоступен");
			flag = TRUE;
		}
		else {
			
			printf("Соединение установлено успешно!");
			Sleep(1000);
			system("clear");
			if (flag == TRUE) {
				printf("Введите сообщение ");
				gets(message_user);
				buffer = &message_user;
				WriteFile(pipeName, buffer, SIZE_BUFFER, &actual_write_bite, NULL);
				flag = FALSE;
			}
			buffer = (CHAR*)calloc(size_buf, sizeof(CHAR));
			BOOL SuccesRead = ReadFile(pipeName, buffer, SIZE_BUFFER, &actual_read_bite, NULL);
			if (SuccesRead) {
				printf("Ответ: \n");
				printf(buffer);
				printf("\n");
				flag = TRUE;



			}
		}
		Sleep(1000);
		CloseHandle(pipeName);


	}



	

}