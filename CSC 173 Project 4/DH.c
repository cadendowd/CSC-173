#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct DH{
	char* Day;
	char* Hour;
	struct DH* next;
} DH;

unsigned int string_hashDH(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashDH(int id) {
	return abs(id % 1009);
}

DH* DH_new(char* day, char* hour){
	DH* out = (DH*) malloc(sizeof(DH));
	out->Day = day;
	out->Hour = hour;
	out->next = NULL;
	return out;
}

void DH_print(DH* dh) {
	printf("{%s, %s}, ", dh->Day, dh->Hour);
	if (dh->next != NULL) {
		DH_print(dh->next);
	}
}

typedef struct DHTable{
	DH* table[1009];
}DHTable;

DHTable* DHTable_new(){
	DHTable* out = (DHTable*) malloc(sizeof(DHTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}
DH* DH_back_of_list(DH* in){
	if(in->next == NULL){
		return in;
	} else {
		return DH_back_of_list(in->next);
	}
}

void DH_insert(DH* in, DHTable* table){
	int hashval = HashDH(string_hashDH(in->Day));
	if(table->table[hashval] == NULL){
		table->table[hashval] = in;
	} else {
		DH_back_of_list(table->table[hashval])->next = in;
	}
}

DHTable* projection_dh(CRDHTable* table, char* column1, char* column2) {
    DHTable* dhtable = DHTable_new();
    for (int i=0; i < 1009; i++) {
        if ((strcmp(column1, "Day")==0 && strcmp(column2, "Hour")==0) || (strcmp(column1, "Hour")==0 && strcmp(column2, "Day")==0)) {
            if (table->table[i] != NULL) {
                
                DH_insert(DH_new(table->table[i]->Day, table->table[i]->Hour), dhtable);

                CRDH* elem = table->table[i];
               
                while (elem != NULL) {
                    if (elem->next == NULL)
                            break;
                    elem=elem->next;
                    
                    DH_insert(DH_new(elem->Day, elem->Hour), dhtable);
                }
            }
        }
    }
    return dhtable;
}

void DHTable_print(DHTable* table) {
	for (int i = 0; i < 1009; i++) {
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			DH_print(table->table[i]);
			printf("\n");
		}
	}
}



