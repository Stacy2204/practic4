import random
import time
import client
from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib.parse
import requests



def shortUrlAlphabet():
    
    result = ''
    for i in range(8):
        r = random.random()
        if (r<=0.2):
            result += chr(int(random.random()*1000 % 10 + 48))
        elif (r>0.2 and r<=0.6):
            result += chr(int(random.random()*1000 % 26 + 65))
        else:
            result += chr(int(random.random()*1000 % 26 + 97))

    return result

def getShortUrl(fullUrl : str):
    shortUrl = shortUrlAlphabet()
    counter = 0 

    hashmapMass = (client.client("HALL myhash")) #берем с БД хэш-таблицу
    if (not ("is empty" in hashmapMass)):
        hashmapMass=hashmapMass.split(';')
        if (hashmapMass[0] == ''):  #если в начале/конце пустой элемент - убираем
            hashmapMass = hashmapMass[1:]
        if (hashmapMass[-1] == ''):
            hashmapMass = hashmapMass[:-1]

        urlTable = {} #хэш-таблица
        
        for el in hashmapMass:
            shortUrl = el.split(':')[0]
            fullUrl_t = el.split(':')[1]
            urlTable[shortUrl] = fullUrl_t
        for el in urlTable:
            if (urlTable[el] == urllib.parse.unquote(fullUrl)):
                return el
        
    while ((not ("Значение не найдено" in client.client("HGET myhash " + shortUrl))) and
                not (fullUrl in client.client("HGET myhash " + shortUrl) ) ):
        shortUrl = shortUrlAlphabet()
        counter+=1
        if (counter==50):
            return ''
    decoded_url = urllib.parse.unquote(fullUrl)
    client.client("HSET myhash " + shortUrl + " " + decoded_url)
    return shortUrl

class RQs_Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        hashmapMass = (client.client("HALL myhash").split(';')) #берем с БД хэш-таблицу
        if (hashmapMass[0] == ''):  #если в начале/конце пустой элемент - убираем
            hashmapMass = hashmapMass[1:]
        if (hashmapMass[-1] == ''):
            hashmapMass = hashmapMass[:-1]
            
        urlTable = {} #хэш-таблица
        for el in hashmapMass:
            shortUrl = el.split(':')[0]
            fullUrl = el.split(':')[1]
            urlTable[shortUrl] = fullUrl 

        serched = False
        fullUrl = client.client("HGET myhash "+self.path[1:])
        shortUrl = self.path[1:]
        print(urlTable)
        print()
        print(shortUrl)
        if not "Значение не найдено" in fullUrl:
            self.send_response(302) #перенаправление
            self.send_header('Location', "http://" + fullUrl) #перенаправляем "http://"
            self.end_headers()
            serched = True
            params = {"IP": self.address_string(), "Full":fullUrl, "Short": shortUrl, "Time": time.time()}
            requests.post("http://127.0.0.1:8080/",params)
        if (serched==False):
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b'404 Not Found')

    def do_POST(self):
        content_length = int(self.headers['Content-Length']) 
        body = self.rfile.read(content_length).decode() #помещаем содержимое параметров от пользователя
        fullUrl = body[4:] 
        shortUrl = getShortUrl(fullUrl)
        self.send_response(200) #успех
        self.end_headers()
        self.wfile.write(shortUrl.encode()) #отправляем ответ пользователю (хранится в data)


def run():
    host = '127.0.0.1'
    port = 80
    server = HTTPServer((host, port), RQs_Handler) #создаем http сервер на локальном адресе и задаем для него обработчик запросов
    print(f'Server running on {host}:{port}')
    server.serve_forever()

if __name__ == '__main__':
    run()