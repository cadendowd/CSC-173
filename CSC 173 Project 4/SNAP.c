#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SNAP {
	int StudentId;
	char* Name;
	char* Address;
	int Phone;
	struct SNAP* next;
}SNAP;

void SNAP_print(SNAP* snap){
    if (snap == NULL) {
        printf("SNAP printed is NULL\n");
        return;
    }
	printf("{%d, %s, %s, %d}, ", snap->StudentId, snap->Name, snap->Address, snap->Phone);
	if(snap->next != NULL) {
		SNAP_print(snap->next);
	}
}

SNAP* SNAP_new(int id, char* name, char* address, int phone) {
	SNAP* snap = (SNAP*) malloc(sizeof(SNAP));
	snap->StudentId = id;
	snap->Name = name;
	snap->Address = address;
	snap->Phone = phone;
	snap->next = NULL;
	return snap;
}

typedef struct SNAPTable{
	SNAP* table[1009];
} SNAPTable;

SNAPTable* SNAPTable_new(){
	SNAPTable* snap = (SNAPTable*) (malloc(sizeof(SNAPTable)));
	for(int i = 0; i < 1009; i++){
		snap->table[i] = NULL;
	}
	return snap;
}

SNAP* SNAP_list_search(int id, SNAP* list, SNAP* snap){
	if(list == NULL) {
		return snap;
	} else {
		if(list->StudentId == id){
			snap = SNAP_new(list->StudentId, list->Name, list->Address, list->Phone);
			snap->next = SNAP_list_search(id, list->next, snap->next);
			return snap;
		} else {
			snap = SNAP_list_search(id, list->next, snap);
			return snap;
		}
	}
}

SNAP* SNAP_lookup(int id, SNAPTable* table) {
	int hashval = HashSNAP(id);
	SNAP* snap = SNAP_list_search(id, table->table[hashval], NULL);
	return snap;
}


SNAP* SNAP_back_of_list(SNAP* snap){
	if(snap->next == NULL){
		return snap;
	} else {
		return SNAP_back_of_list(snap->next);
	}
}

void SNAP_insert(SNAP* snap, SNAPTable* table){
	if(SNAP_lookup(snap->StudentId, table) == NULL){
		int hashval = HashSNAP(snap->StudentId);
		if(table->table[hashval] == NULL){
			table->table[hashval] = snap;
		} else {
			SNAP_back_of_list(table->table[hashval])->next = snap;
		}
	}
}

void SNAP_delete_hash(int id, SNAP* list) {
	if(list->next == NULL){
		return;
	} else if(list->next->StudentId == id){
		list->next = list->next->next;
		SNAP_delete_hash(id, list->next);
		return;
	} else {
		SNAP_delete_hash(id, list->next);
	}
}

void SNAP_delete(int id, SNAPTable* table) {
	int hashval = HashSNAP(id);
	if((table->table[hashval])->StudentId == id){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		SNAP_delete_hash(id, table->table[hashval]);
	}
}

void SNAPTable_print(SNAPTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
            printf("%d: ", i);
            SNAP_print(table->table[i]);
            printf("\n");
		}
	}
}

unsigned int string_hashSNAP(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int HashSNAP(int id) {
	return abs(id % 1009);
}

SNAPTable* SNAP_Selection(SNAPTable* table, char* attribute, char* search) {
        SNAPTable* newTable = SNAPTable_new();
        if (strcmp(attribute, "name")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Name, search) == 0) {
                                        SNAP_insert(SNAP_new(table->table[i]->StudentId, table->table[i]->Name, table->table[i]->Address, table->table[i]->Phone), newTable);
                                }
                                SNAP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Name, search) == 0) {
                                                SNAP_insert(SNAP_new(element->StudentId, element->Name, element->Address, element->Phone), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "student")==0) {
                int sid = atoi(search);
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (sid==table->table[i]->StudentId) {
                                        SNAP_insert(SNAP_new(table->table[i]->StudentId, table->table[i]->Name, table->table[i]->Address, table->table[i]->Phone), newTable);
                                }
                                SNAP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (sid==element->StudentId) {
                                                SNAP_insert(SNAP_new(element->StudentId, element->Name, element->Address, element->Phone), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}