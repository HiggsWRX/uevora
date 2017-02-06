# -*- coding: utf-8 -*-
import socket, select, traceback, json, hashlib, os
from collections import defaultdict
from datetime import datetime, timedelta
    
SOCKET_LIST = []    # lista de sockets abertos
RECV_BUFFER = 4096  # valor recomendado na doc. do python
PORT = 5000
SOCK_DIC = defaultdict(dict)

def putsockindic(sock):
    SOCK_DIC[sock]['logged'] = False
    SOCK_DIC[sock]['user'] = ''

def process_cmd(data, sock):
    # this is the function that processes data received from a client on
    # socket 'sock'
    if sock not in SOCK_DIC:
        putsockindic(sock)

    data = data.strip().decode().split(" ")
    logged = SOCK_DIC[sock]['logged']
    if data[0] == 'LOGIN':
        logged = login(sock, data)
        if logged:
            SOCK_DIC[sock]['logged'] = True
            SOCK_DIC[sock]['user'] = data[1]
            viewmessages(sock)
    elif data[0] == 'REGISTER':
        register(sock, data)
    elif data[0] == 'PUBLICMSGS':
        if logged:
            if len(data) > 1:
                viewmessages(sock, int(data[1]))
            else:
                viewmessages(sock)
        else:
            sock.send("ERR_NOT_LOGGED_IN\n".encode())
    elif data[0] == 'PRIVMSGS':
        if logged:
            if len(data) > 1:
                readprivate(sock, int(data[1]))
            else:
                readprivate(sock)
        else:
            sock.send("ERR_NOT_LOGGED_IN\n".encode())
    elif data[0] == 'SENDMSG':
        if logged:
            postmessages(sock, data)
        else:
            sock.send("ERR_NOT_LOGGED_IN\n".encode())
    elif data[0] == 'SENDPRIVMSG':
        if logged:
            sendprivate(sock, data)
        else:
            sock.send("ERR_NOT_LOGGED_IN\n".encode())
    elif data[0] == 'WHOSONLINE':
        listonline(sock)
    elif data[0] == 'GOODBYE':
        del SOCK_DIC[sock]

def login(socket, usrdetails):
    usr = usrdetails[1]
    pwd = usrdetails[2]
    pwd = hashpwd(pwd.encode())
    if authenticate(usr, pwd):
        print("{} is {}.".format(socket.getpeername(), usrdetails[1]))
        socket.send("OK_LOGIN {}".format(usr).encode())
        return True
    else:
        print("{} is trying to login as {}.".format(socket.getpeername(), usrdetails[1]))
        socket.send("ERR_LOGIN {}\n".format(usr).encode())
        return False

def authenticate(user, pwd):
    with open('userdb.txt', 'r') as file:
        db = json.load(file)

    if user in db:
        return db[user] == pwd
    else:
        return False

def register(socket, data):
    usr = data[1]
    pwd = data[2]

    if len(pwd) >= 24 or len(usr) >= 24:
        socket.send("ERR_INVALID_DATA")
        return

    pwd = hashpwd(pwd.encode())

    filename = "userdb.txt"
    with open(filename, 'r') as file:
        userdb = json.load(file)

        if usr in userdb:
            socket.send("ERR_ALREADY_EXISTS {}\n".format(usr).encode())
            return

        userdb[usr] = pwd
        socket.send("OK_REGISTERED {}\n".format(usr).encode())
        print("{} registered as {}.".format(socket.getpeername(), usr))

    with open(filename + ".temp", 'w') as file:
        json.dump(userdb, file)
    
    os.rename(filename, filename + ".bak")
    os.rename(filename + ".temp", filename)

def viewmessages(socket, opt=0):
    filename = "posts.txt"
    with open(filename, 'r') as file:
        post = file.readline()
        if post == "":
            socket.send("NO_PUBLICMSGS\n".encode())
            return
        while 1:
            if post == "":
                break

            if opt != 0:
                aux = post.split(" ")
                postdate = aux[0]
                postdate = datetime.strptime(postdate, '%d-%m-%Y')
                maxdate = datetime.now() - timedelta(days=opt)
                if postdate < maxdate:
                    post = file.readline()
                    continue

            msg = "MSG " + post
            socket.send(msg.encode())
            post = file.readline()

def readprivate(socket, opt=0):
    user = SOCK_DIC[socket]['user']
    filename = "privatedb.txt"
    with open(filename, 'r') as file:
        privatedb = json.load(file)

    if user not in privatedb:
        socket.send("NO_PRIVMSGS\n".encode())
        return

    for i in range(len(privatedb[user])):
        priv = privatedb[user][i]

        if opt != 0:
            aux = priv.split(" ")
            postdate = aux[0]
            postdate = datetime.strptime(postdate, '%d-%m-%Y')
            maxdate = datetime.now() - timedelta(days=opt)
            if postdate < maxdate:
                continue

        msg = "PRIVMSG " + priv
        socket.send(msg.encode())

def postmessages(socket, data):
    user = SOCK_DIC[socket]['user']
    date = str(datetime.now().strftime("%d-%m-%Y"))
    time = str(datetime.now().strftime("%H:%M"))
    msg = ""
    for i in range(1, len(data)):
        msg += data[i] + " "

    if len(msg) >= 500:
        socket.send("ERR_MSG_NOTSENT".encode())
        return

    msg = "{} {} {} {}\n".format(date, time, user, msg)

    with open('posts.txt', 'a') as file:
        file.write(msg)
        socket.send("OK_MSG_SENT\n".encode())

def sendprivate(socket, data):
    recipient = data[1]

    filename = "userdb.txt"
    with open(filename, 'r') as file: 
        userdb = json.load(file)

    if recipient not in userdb:
        socket.send("ERR_PRIVMSG_NOTSENT".encode())
        return

    sender = SOCK_DIC[socket]['user']
    date = str(datetime.now().strftime("%d-%m-%Y"))
    time = str(datetime.now().strftime("%H:%M"))
    msg = ""
    for i in range(2, len(data)):
        msg += data[i] + " "

    if len(msg) >= 500:
        socket.send("ERR_PRIVMSG_NOTSENT".encode())
        return

    msg = "{} {} {} {}\n".format(date, time, sender, msg)

    filename = "privatedb.txt"
    with open(filename, 'r') as file:
        msgdb = json.load(file)
        if recipient not in msgdb:
            msgdb[recipient] = []
        msgdb[recipient].append(msg)
    
    with open(filename + ".temp", 'w') as file:
        json.dump(msgdb, file)

    os.rename(filename, filename + ".bak")
    os.rename(filename + ".temp", filename)

    socket.send("OK_PRIVMSG_SENT\n".encode())

def listonline(sock):
    msg = "ONLINEUSERS "
    for key in SOCK_DIC:
        if SOCK_DIC[key]['logged']:
            msg += SOCK_DIC[key]['user'] + " "

    if len(msg) == 12:
        msg = "ONLINENOONE"

    msg += "\n"
    sock.send(msg.encode())

def hashpwd(pwd):
    return hashlib.sha256(pwd).hexdigest()

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(("0.0.0.0", PORT))  # aceita ligações de qualquer lado
    server_socket.listen(10)
    server_socket.setblocking(0) # we'll use select(), so no blocking
    
    # Add server socket to the list of readable connections
    SOCKET_LIST.append(server_socket)
    
    print("Server started on port %d" % (PORT,))

    while True:  # server loop

        # remove closed socks
        for sock in SOCKET_LIST:
            if sock.fileno() < 0:  # something closed the socket
                SOCKET_LIST.remove(sock)
                
        rsocks,wsocks,esocks = select.select(SOCKET_LIST,[],[])
 
        for sock in rsocks:  # rsocks are sockets with new data
             
            if sock == server_socket: # new client connection
                newsock, addr = server_socket.accept()
                newsock.setblocking(0)
                SOCKET_LIST.append(newsock)

                print("New client - %s" % (addr,))
                 
            else: # há dados num socket ligado a um cliente
                try:
                    data = sock.recv(RECV_BUFFER)
                    if data: 
                        process_cmd(data, sock) # process this client's data
                        
                    else: # não há dados, o cliente fechou o socket
                        print("Client disconnected 1")
                        sock.close()
                        SOCKET_LIST.remove(sock)
                        
                except Exception as e: # excepção ao ler o socket, o cliente fechou ou morreu
                    print(traceback.format_exc())
                    print("Client disconnected")
                    sock.close()
                    SOCKET_LIST.remove(sock)
                    
if __name__ == "__main__":
    main()