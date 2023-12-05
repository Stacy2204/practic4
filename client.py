import socket


def client(message : str): #передаем команды для сервера БД
    hostname = socket.gethostname()
    port = 6379
    sock = socket.socket()
    sock.connect((hostname, port))
    sock.send(message.encode())

    data = sock.recv(1024)
    data = data.decode()
 
    sock.close() #закрываем сокет  

    return data

