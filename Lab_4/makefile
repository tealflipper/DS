MPICC=mpicc
MRUN=mpirun

#Aqui esta la lista de parametros
PAR_I= -Wall -lm
PAR_LIB= -c -Wall -shared

#Archivos de cabecera
INC=.

#Archivos
PROG_01=ex
out=pp
maq=hostfile
#Parametros
NODES=25

#Procesos
all: uno

uno:
	@echo "**************** COMPILADO CODIGO: $(PROG_01) ****************"
	$(MPICC) $(PAR_I) $(PROG_01).c -o $(out) -I$(INC)

rununo:
	@echo "**************** COMPILADO CODIGO: $(PROG_01) ****************"
	$(MPICC) $(PAR_I) $(PROG_01).c -o $(out) -I$(INC)
	$(MRUN) -np $(NODES) -hostfile $(maq) $(out)
