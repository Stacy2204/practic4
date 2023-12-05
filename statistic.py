from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib
import client
import json
import time

class staticNote:
    def __init__(self, logstr):
        self.ipsrc    = urllib.parse.parse_qs(logstr)['IP'][0]
        self.longUrl  = urllib.parse.parse_qs(logstr)['Full'][0]
        self.shortUrl = urllib.parse.parse_qs(logstr)['Short'][0]
        self.time     = float(urllib.parse.parse_qs(logstr)['Time'][0])
    def get(self, field):
        if (field == "SourceIP"):
            return self.ipsrc
        if (field == "URL"):
            return f"{self.longUrl} ({self.shortUrl})"
        if (field == "TimeInterval"):
            return time.ctime(int(self.time/100)*100)[11:-8] + " - " + time.ctime(int(self.time/100)*100+60)[11:-8]
        else:
            return None

class reportNote:
    def __init__(self, id=None, pid=None, ipsrc=None, url=None, timeint=None,count=0):
        self.Id = id
        self.Pid = pid
        self.SourceIP = ipsrc
        self.URL = url
        self.TimeInterval = timeint
        self.Count = count
    def set(self, filed, value):
        if (filed=="SourceIP"):
            self.SourceIP = value
        if (filed=="URL"):
            self.URL = value
        if (filed=="TimeInterval"):
            self.TimeInterval = value
        if (filed=="Id"):
            self.Id = value
        if (filed=="count"):
            self.Count = value
    def __eq__(self, other): 
        return self.SourceIP==other.SourceIP and self.URL == other.URL and self.TimeInterval == other.TimeInterval and(
             self.Pid == other.Pid)


class StatisticRequestHandler(BaseHTTPRequestHandler):

    def do_POST(self):
        if self.path == '/':
            content_length = int(self.headers['Content-Length']) 
            body = self.rfile.read(content_length).decode()
            query1 = client.client("QREAD myqueue")
            query2 = client.client("QREAD MYQUEUE")

            if ("is empty" in query1 and 
                "is empty" in query2):
                client.client(f"QPUSH myqueue {body}")
            elif ("is empty" in query1 and 
                  not "is empty" in query2):
                client.client(f"QPUSH MYQUEUE {body}")
            elif (not"is empty" in query1 and 
                  "is empty" in query2):
                client.client(f"QPUSH myqueue {body}")
            self.send_response(200)
            self.end_headers()

        elif self.path == '/report':
            query1 = client.client("QREAD myqueue")
            query2 = client.client("QREAD MYQUEUE")
            logs = []

            if ("is empty" in query1 and 
                "is empty" in query2):
                self.send_response(500)
                return
            elif ("is empty" in query1 and 
                  not "is empty" in query2):
                while (not "is empty" in query2):
                    logs.append(query2.split(' ')[-1])
                    client.client(f"QPUSH myqueue {query2.split(' ')[-1]}")
                    query2 = client.client("QPOP MYQUEUE")
            elif (not "is empty" in query1 and 
                    "is empty" in query2):
                while (not "is empty" in query1):
                    logs.append(query1.split(' ')[-1])
                    client.client(f"QPUSH MYQUEUE {query1.split(' ')[-1]}")
                    query1 = client.client("QPOP myqueue")

            logs = [staticNote(logstr) for logstr in logs]
            content_length = int(self.headers['Content-Length'])
            body = self.rfile.read(content_length).decode()
            clientreq = json.loads(clientreq)


            report = []
            pids = {}
            id = 1

            for l in logs:
                record = reportNote(count=1)
                record.set(clientreq[0], l.get(clientreq[0]))
                record.set("Id", id)
                if record in report:
                    report[report.index(record)].Count += 1
                else:
                    report.append(record)
                    pids[l.get(clientreq[0])] = id
                    id+=1
                
                record = reportNote(count=1)
                record.set(clientreq[1], l.get(clientreq[1]))
                pid = pids[l.get(clientreq[0])]
                record.Pid = pid
                if record in report:
                    report[report.index(record)].Count += 1
                else:
                    pids[l.get(clientreq[1])] = id
                    record.set("Id", id)
                    report.append(record)
                    id+=1


                record = reportNote(count=1)
                record.set(clientreq[2], l.get(clientreq[2]))
                pid = pids[l.get(clientreq[1])]
                record.Pid = pid
                if record in report:
                    report[report.index(record)].Count += 1
                else:
                    pids[l.get(clientreq[2])] = id
                    record.set("Id", id)
                    report.append(record)
                    id+=1

            answer = [r.__dict__ for r in report]
            answer = json.dumps(answer)
            
            self.send_response(200)
            self.end_headers()
            self.wfile.write(answer.encode())
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b"Not Found file")


def run():
    host = '127.0.0.1'
    port = 8080
    server = HTTPServer((host, port), StatisticRequestHandler)
    print(f'Server running on {host}:{port}')
    server.serve_forever()

if __name__ == '__main__':
    run()