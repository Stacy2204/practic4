#include <sys/socket.h> //реализует функцию сокет
#include <sys/types.h> //работа с константами (аргументами функции сокет)
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "erproc.h"
#include "basedata.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //создаем и инициализируем мьютекс

void* connectthread(void* filedesc) //поток для обработки пользовательского запроса
{
        int fd = *(int*) filedesc;
        ssize_t nread; //количество считанных байт от пользователя

        while(1)
        {
            char buf[256] = {'\0'};
            nread = read(fd, buf, 256);
            if (nread==-1)
            {
                perror("read failed.\n");
                break;
            }
            if(nread==0)
            {
                printf("END OF FILE occured.\n");
                break;
            }

            printf("Client command: %s\n", buf);

            // Обрабатываем команду пользователя
            pthread_mutex_lock(&mutex); //используем мьютекс для ограничения доступа к общим данным, пока текущий поток не завершил работу с ними
            char* answer = basedata(buf);
            pthread_mutex_unlock(&mutex);

            // Отправляем ответ клиенту
            write(fd, answer, strlen(answer));
        }

        close(fd); //закрываем сокет
        pthread_exit(NULL);
}

int main()
{
    // Создаем сокет
    int server = Socket(AF_INET, SOCK_STREAM,0);

    // Задаем параметры сервера
    struct sockaddr_in adr = {0 };
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    Bind(server, (struct sockaddr*) &adr,sizeof adr);

    // Начинаем прослушивание порта
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;

    int fd = 0; //инициализируем файловый дескриптор 
    while (fd = Accept(server, (struct sockaddr*) &adr, &adrlen)) //пока сервер принимает соединения
    {
        // Создаем новый поток для обработки запроса клиента
        pthread_t thread = 0; //создаем и инициализируем поток
        int new_connection = fd; 
        if (pthread_create(&thread, NULL, connectthread, (void*) &new_connection) < 0) //св случае неудачи выводим ошибку
        {
            perror("Create thread error");
            exit(EXIT_FAILURE);
        }
    }

    close (fd);
    close(server);
    return 0;
}