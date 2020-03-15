JAVAC=javac
JAVA=java

#Aqui esta la lista de parametros


#Archivos de cabecera


#Archivos
SERVER_01=Server1
SERVER_02=Server2
CLIENT_01=Client1
CLIENT_02=Cliente2
ALL=*
#Parametros

#Procesos
all: uno

uno:
	@echo "**************** COMPILADO CODIGO: $(SERVER_01) $(CLIENT_01) $(CLIENT_02) ****************"
	$(JAVAC) $(ALL).java

startRunservers:
	@echo "**************** COMPILADO CODIGO ****************"
	$(JAVAC) $(ALL).java
	@echo "**************** Levantando registro ****************"
	rmiregistry &
	@echo "**************** Levantando servidor ****************"
	$(JAVA) $(SERVER_01) &
	$(JAVA) $(SERVER_02) &

runservers:
	@echo "**************** COMPILADO CODIGO ****************"
	$(JAVAC) $(ALL).java
	@echo "**************** Levantando servidor ****************"
	rmiregistry &
	$(JAVA) $(SERVER_01) &
	$(JAVA) $(SERVER_02) &

run:
	@echo "**************** COMPILADO CODIGO ****************"
	$(JAVAC) $(ALL).java
	@echo "**************** corre programas ****************"
	$(JAVA) Client1 &
	$(JAVA) Client2 &
	@echo ""
