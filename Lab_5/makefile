MPICC=mpicc
MRUN=mpirun

#Aqui esta la lista de parametros
PAR_I= -Wall -lm
PAR_LIB= -c -Wall -shared

#Archivos de cabecera
INC=.

#Archivos
PROG_01=p
out=pp
maq=hostfile
#Parametros
NODES=24

#Procesos
all: uno

uno:
	@echo "**************** COMPILADO CODIGO: $(PROG_01) ****************"
	$(MPICC) $(PAR_I) $(PROG_01).c -o $(out) -I$(INC)

run:
	@echo "**************** COMPILADO CODIGO: $(PROG_01) ****************"
	$(MPICC) $(PAR_I) $(PROG_01).c -o $(out) -I$(INC)
	$(MRUN) -np $(NODES) -hostfile $(maq) $(out)


