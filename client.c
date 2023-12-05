#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "erproc.h"

int main()
{
    // Создаем сокет семейства IPv4, TCP/IP
    int fd = Socket(AF_INET, SOCK_STREAM, 0 );

    // Задаем параметры адреса сервера
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr); //задаем адресс (тот же пк, где сервер)

    // Устанавливаем соединение с сервером
    Connect(fd, (struct sockaddr*) &adr, sizeof adr);

    while (1)
    {
        // Запрос команды у пользователя
        char request[256];
        printf("Введите команду серверу:");
        fgets(request, 256, stdin);
        int len = strlen(request);
        fflush(stdin);

        // Отправляем запрос на сервер
        write (fd, request, len);

        // Получаем ответ от сервера
        char buf[256] = {'\0'};
        ssize_t nread;
        nread = read(fd, buf, 256);
        if (nread==-1)
        {
            printf("read failed.\n");
            exit(EXIT_FAILURE);
        }
        if (nread==0)
        {
            printf("EOF occured.\n");
        }

        // Выводим ответ сервера на экран
        printf("сервер ответил: %s\n", buf);
    }

    // Закрываем соединение
    close (fd);

    return 0;
}
