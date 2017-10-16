CC=gcc
C_FLAGS=-gdwarf-2

tricky_list : List.o 
	$(CC) $(C_FLAGS) -o tricky_list List.c test_list.c


clean :
	rm -f core tricky_list  
