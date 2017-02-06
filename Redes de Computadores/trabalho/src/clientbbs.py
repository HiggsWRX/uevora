import socket, select, sys

def sendusermessage(m):
    sys.stdout.write(m)
    sys.stdout.flush()

def menu() :
    sendusermessage( ('Menu:\n'
                      '  1) Register\n'
                      '  2) Login\n'
                      '  3) Read public messages [MAXDAYS]\n'
                      '  4) Read private messages [MAXDAYS]\n'
                      '  5) Send public message\n'
                      '  6) Send private message\n'
                      '  7) Online users\n'
                      '  8) Logout\n'))

def prompt() :
    sys.stdout.write('\ncommand? ')
    sys.stdout.flush()

def getinput():
    while 1:
        msg = sys.stdin.readline()
        msg = msg.strip()
        if msg != "":
            break
        else:
            print("Mandatory field\n")
    return msg

def handleinput(msg):
    aux = msg.split()
    msg = aux[0]
    if msg == '1':
        sendusermessage("\nUsername: ")
        usr = getinput()
        sendusermessage("\nPassword: ")
        pwd = getinput()
        msg = "REGISTER {} {}".format(usr, pwd)
    elif msg == '2':
        sendusermessage("\nUsername: ")
        usr = getinput()
        sendusermessage("\nPassword: ")
        pwd = getinput()
        msg = "LOGIN {} {}".format(usr, pwd)
    elif msg == '3':
        msg = "PUBLICMSGS"
        if len(aux) > 1:
            msg += " {}".format(aux[1])
    elif msg == '4':
        msg = "PRIVMSGS"
        if len(aux) > 1:
            msg += " {}".format(aux[1])
    elif msg == '5':
        sendusermessage("\nMessage to send? ")
        usermsg = getinput()
        msg = "SENDMSG " + usermsg
    elif msg == '6':
        sendusermessage("\nUser to send message? ")
        usr = getinput()
        sendusermessage("\nMessage to send? ")
        usermsg = getinput()
        msg = "SENDPRIVMSG {} {}".format(usr, usermsg)
    elif msg == '7':
        msg = "WHOSONLINE"
    elif msg == '8':
        msg = "GOODBYE"
    return msg

def main(host, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)
     
    # liga ao host remoto
    try :
        s.connect((host, port))
    except :
        print('Unable to connect')
        sys.exit()
     
    print('Connected to remote host.')
    menu()
    prompt()
    while True:
        socket_list = [sys.stdin, s]
         
        # Espera por um socket com dados (ou stdin)
        read_sockets, write_sockets, error_sockets = select.select(socket_list , [], [])
         
        for sock in read_sockets:
            #chegou uma mensagem no socket
            if sock == s:
                data = sock.recv(4096)
                if not data :
                    print('\nDisconnected from remote server')
                    sys.exit()
                else :
                    sys.stdout.write("\n" + data.decode() + "\n")
                    sys.stdout.flush()
                    prompt()
             
            #mensagem escrita no teclado
            else :
                msg = getinput()
                msg = handleinput(msg)
                s.send(msg.encode())
                if msg == "GOODBYE":
                    print('\nDisconnected from remote server')
                    sys.exit()

#main function
if __name__ == "__main__":
     
    if(len(sys.argv) < 3) :
        print('Usage : python %s hostname port' % (sys.argv[0],))
        sys.exit()
     
    host = sys.argv[1]
    port = int(sys.argv[2])

    main(host, port)
                