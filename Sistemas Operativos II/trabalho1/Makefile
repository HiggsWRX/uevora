all: connector client server

classes/sgespacos/SGEspacos.class: src/sgespacos/SGEspacos.java
	javac -d classes src/sgespacos/SGEspacos.java
classes/sgespacos/SGEspacosImpl.class: src/sgespacos/SGEspacosImpl.java classes/sgespacos/SGEspacos.class
	javac -d classes -classpath classes src/sgespacos/SGEspacosImpl.java

connector: classes/sgespacos/PostgresConnector.class
classes/sgespacos/PostgresConnector.class: src/sgespacos/PostgresConnector.java
	javac -d classes -classpath classes src/sgespacos/PostgresConnector.java

client: classes/sgespacos/SGEspacosClient.class 
classes/sgespacos/SGEspacosClient.class: src/sgespacos/SGEspacosClient.java classes/sgespacos/SGEspacos.class
	javac -d classes -classpath classes src/sgespacos/SGEspacosClient.java

server: classes/sgespacos/SGEspacosServer.class 
classes/sgespacos/SGEspacosServer.class: src/sgespacos/SGEspacosServer.java classes/sgespacos/SGEspacosImpl.class
	javac -d classes -classpath classes src/sgespacos/SGEspacosServer.java

# executar o servidor
rs:
	java -classpath classes:resources/postgresql.jar sgespacos.SGEspacosServer 9000


# executar o cliente
rc:
	java -classpath classes:resources/postgresql.jar sgespacos.SGEspacosClient localhost 9000


clean:
	rm -rf classes/* *~ src/*~ src/sgespacos/*~
