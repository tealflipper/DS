JAVAC=javac
JAVA=java

#Aqui esta la lista de parametros


#Archivos de cabecera


#Archivos
SERVER_01=Server1
CLIENT_01=Client1
CLIENT_02=Cliente2
ALL=*
#Parametros

#Procesos
all: uno

uno:
	@echo "**************** COMPILADO CODIGO: $(SERVER_01) $(CLIENT_01) $(CLIENT_02) ****************"
	$(JAVAC) $(ALL).java

run:
	@echo "**************** COMPILADO CODIGO ****************"
	$(JAVAC) $(ALL).java
		@echo "**************** Levantando servidor ****************"
	$(JAVAC) $(ALL).java
	rmiregistry &
	$(JAVA) $(SERVER_01)

