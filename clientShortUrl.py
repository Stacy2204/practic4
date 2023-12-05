import requests

def main():
    while True:
        msg=input("Введите ссылку для сокращения: ")
        if (msg[:8] == "https://"):
            msg = msg[8:]
        if (msg[:7] == "http://"):
            msg = msg[7:]
        params={"url":msg}
        data=requests.post("http://127.0.0.1",params)
        print("Сокращенная ссылка: http://127.0.0.1/" + data.text)

if __name__ == "__main__":
    main()