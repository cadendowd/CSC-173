#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CSG.c"
#include "SNAP.c"
#include "CDH.c"
#include "CP.c"
#include "CR.c"
#include "Database.c"
#include "CRDH.c"
#include "DH.c"
#include "Query.c"
#include "Student.c"

unsigned int string_hash(void *string) {
	
	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}

int Hash(int id) {
	return abs(id % 1009);
}

int main(){

    printf("Part1: \n");
    
    Database* db = Database_New();
   
    //initializing tables for each relation
    SNAPTable* snaptable = db->SNAP;
    CRTable* crtable = db->CR;
    CDHTable* cdhtable = db->CDH;
    CSGTable* csgtable = db->CSG;
    CPTable* cptable = db->CP;

    Database_print(db);

    //CSG
    CSG_insert(CSG_new("CS101", 12345, "A"), csgtable);
    CSG_insert(CSG_new("CS101", 67890, "B"), csgtable);
    CSG_insert(CSG_new("EE200", 12345, "C"), csgtable);
    CSG_insert(CSG_new("EE200", 22222, "B+"), csgtable);
    CSG_insert(CSG_new("CS101", 33333, "A-"), csgtable);
    CSG_insert(CSG_new("PH100", 67890, "C+"), csgtable);

    //SNAP
    SNAP_insert(SNAP_new(12345, "C. Brown", "12 Apple St.", 5551234), snaptable);
    SNAP_insert(SNAP_new(67890, "L. Van Pelt", "134 Pear Ave.", 5555678), snaptable);
    SNAP_insert(SNAP_new(22222, "P. Patty", "56 Grape Blvd.", 5559999), snaptable);

    //CP
    CP_insert(CP_new("CS101", "CS100"), cptable);
    CP_insert(CP_new("EE200", "EE005"), cptable);
    CP_insert(CP_new("EE200", "CS100"), cptable);
    CP_insert(CP_new("CS120", "CS101"), cptable);
    CP_insert(CP_new("CS121", "CS120"), cptable);
    CP_insert(CP_new("CS205", "CS101"), cptable);
    CP_insert(CP_new("CS206", "CS121"), cptable);
    CP_insert(CP_new("CS206", "CS205"), cptable);

    //CDH
    CDH_insert(CDH_new("CS101", "M", "9AM"), cdhtable);
    CDH_insert(CDH_new("CS101", "W", "9AM"), cdhtable);
    CDH_insert(CDH_new("CS101", "F", "9AM"), cdhtable);
    CDH_insert(CDH_new("EE200", "Tu", "10AM"), cdhtable);
    CDH_insert(CDH_new("EE200", "W", "1PM"), cdhtable);
    CDH_insert(CDH_new("EE200", "Th", "10AM"), cdhtable);

    //CR
    CR_insert(CR_new("CS101", "Turing Aud."), crtable);
    CR_insert(CR_new("EE200", "25 Ohm Hall"), crtable);
    CR_insert(CR_new("PH100", "Newton Lab."), crtable);


    printf("Printing Database after inserting data\n");
    Database_print(db);

    
    printf("\nTesing lookup methods:\n");

    //SNAP lookup
    printf("\nSNAP lookup:\n");
    SNAP_print(SNAP_lookup(67890, snaptable)); //lookup 67890
    printf("\n");
    SNAP_print(SNAP_lookup(1, snaptable)); //lookup 1 (not in table)

    //CP lookup
    printf("\nCP lookup:\n");
    CP_print(CP_lookup("EE200", cptable));
    printf("\n");
    CP_print(CP_lookup("CS120", cptable));
    printf("\n");
    CP_print(CP_lookup("EE200", cptable));
    printf("\n");
    CP_print(CP_lookup("CS206", cptable));
    printf("\n");
    CP_print(CP_lookup("CS888", cptable)); //not in table

    //CDH lookup
    printf("\nCDH lookup:\n");
    CDH_print(CDH_lookup("EE200", cdhtable));
    printf("\n");
    CDH_print(CDH_lookup("EE500", cdhtable)); //not in table


    //Saving and loading to file
    printf("Saving and loading to file");
    DataBase_Save(db, "newFile.txt");

    Database* db2 = DataBase_Load("newFile.txt");

    printf("Printing new DB\n");
    Database_print(db2);


    //delete methods
    printf("\nTesting delete methods\n");
    CSG_delete(12345, "CS101", csgtable);
    SNAP_delete(12345, snaptable);
    CDH_delete("EE200", cdhtable);
    CR_delete("CS101", crtable);
    CP_delete("EE200", cptable);
   
    Database_print(db);
    


    //Part 2
    printf("\n Part 2: \n");
    
    printf("\n What grade did C. Brown get in CS101?\n");
    printf("ANS: \n");
    char query1[] = "What grade did \'C. Brown\' get in CS101?";
    printf("%s\n", GradeInCourse(query1, db2));

    printf("\n Where is C. Brown at 9AM on M?' as a string input\n");
    printf("ANS:\n");
    char query2[] = "Where is \'C. Brown\' at 9AM on M?";
    printf("%s\n", LocationOnDay(query2, db2));

    //Part 3
    printf("\n Part3: \n");
    printf("\n Selection Operator: \n");
    printf("Selecting course 'CS101' in CSG table: \n");
    CSGTable_print(CSG_Selection(db2->CSG, "course", "CS101"));

	//PROJECTION
	printf("\nProjection operator: \n");
	printf("Projecting all the tuples for CS101 in the CSG relation: \n");

	CSGTable* newTable = CSG_Selection(db2->CSG, "course", "CS101");
    CSGTable_print(newTable);

    STable* stable = projection_s(newTable, "StudentId");
    printf("\nANS: \n");
    STable_print(stable);

    

    //JOIN
    printf("\nJoin Operator: CDH and CR\n");
    CRTable* crJoin = CRTable_new();
	CDHTable* cdhJoin = CDHTable_new();

	CR_insert(CR_new("CS101", "Turing Aud."), crJoin);
	CR_insert(CR_new("EE200", "Ohm Hall"), crJoin);
	CR_insert(CR_new("PH100", "Newton Lab."), crJoin);

	CDH_insert((CDH_new("CS101", "M", "9AM")), cdhJoin);
	CDH_insert((CDH_new("CS101", "W", "9AM")), cdhJoin);
	CDH_insert((CDH_new("CS101", "F", "9AM")), cdhJoin);
	CDH_insert((CDH_new("EE200", "Tu", "10AM")), cdhJoin);
	CDH_insert((CDH_new("EE200", "W", "1PM")), cdhJoin);
	CDH_insert((CDH_new("EE200", "Th", "10AM")), cdhJoin);


	CRDHTable* crdh = CRDHTable_new(crJoin, cdhJoin);
    printf("ANS: \n");
	CRDHTable_print(crdh);
}