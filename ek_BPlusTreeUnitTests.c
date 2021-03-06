/*

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    -----

	B+ Tree Implementation 1.0.0 (7.Agu.2014)
    Engin Kuzu
    enginkuzu@gmail.com
    
	Ask for other licenses.

*/

// Thanks to https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "ek_BPlusTree.c"
#include "ek_BPlusTreeHelper.c"

void doTest(int no, int len, int task[], char* out){
	root = NULL;
	int i;
	for(i=0;i<len;i++){
		int value = task[i];
		if( value < 0 ){
			bptreeDelete(-1*value);
		}else{
			bptreeInsert(value);
		}
	}
	_bptreePrint();
	if( strcmp(printBuffer, out) == 0 ){
		printf("###### %d - PASS\n", no);
	}else{
		printf("###### %d - !!! FAIL !!!\n", no);
		printf("-calculated-\n%s-target-\n%s", printBuffer, out);
	}
}

int main(){
	
	puts("");
	puts("Add Tests");
	puts("");
	
	doTest(1, 1, (int[]){10},			"[-(10)-(-1)-] \n");
	doTest(2, 2, (int[]){10,20},		"[-(10)-(20)-] \n");
	doTest(3, 2, (int[]){10,5},			"[-(5)-(10)-] \n");

	doTest(4, 3, (int[]){10,20,30},		"[+(20)+(-1)-] \n[-(10)-(-1)-] [-(20)-(30)-] \n");
	doTest(5, 3, (int[]){10,20,0},		"[+(10)+(-1)-] \n[-(0)-(-1)-] [-(10)-(20)-] \n");
	doTest(6, 3, (int[]){10,20,15},		"[+(15)+(-1)-] \n[-(10)-(-1)-] [-(15)-(20)-] \n");

	doTest(7, 4, (int[]){10,20,30,5},		"[+(20)+(-1)-] \n[-(5)-(10)-] [-(20)-(30)-] \n");
	doTest(8, 4, (int[]){10,20,30,15},		"[+(20)+(-1)-] \n[-(10)-(15)-] [-(20)-(30)-] \n");
	doTest(9, 4, (int[]){10,20,30,25},		"[+(20)+(25)+] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(25)-(30)-] \n");
	doTest(10, 4, (int[]){10,20,30,35},		"[+(20)+(30)+] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(30)-(35)-] \n");

	doTest(11, 8, (int[]){10,20,30,40,50,60,70,-70},	"[+(30)+(50)+] \n[+(20)+(-1)-] [+(40)+(-1)-] [+(60)+(-1)-] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(40)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] \n");

	doTest(12, 10, (int[]){10,20,30,40,50,60,70,-70,31,32},		"[+(30)+(50)+] \n[+(20)+(-1)-] [+(31)+(40)+] [+(60)+(-1)-] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(31)-(32)-] [-(40)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] \n");
	doTest(13, 10, (int[]){10,20,30,40,50,60,70,-70,41,42},		"[+(30)+(50)+] \n[+(20)+(-1)-] [+(40)+(41)+] [+(60)+(-1)-] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(40)-(-1)-] [-(41)-(42)-] [-(50)-(-1)-] [-(60)-(-1)-] \n");

	doTest(14, 11, (int[]){10,20,30,40,50,60,70,-70,41,42,43},	"[+(41)+(-1)-] \n[+(30)+(-1)-] [+(50)+(-1)-] \n[+(20)+(-1)-] [+(40)+(-1)-] [+(42)+(-1)-] [+(60)+(-1)-] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(40)-(-1)-] [-(41)-(-1)-] [-(42)-(43)-] [-(50)-(-1)-] [-(60)-(-1)-] \n");
	doTest(15, 12, (int[]){10,20,30,40,50,60,70,-70,9,8,7,6},	"[+(30)+(-1)-] \n[+(9)+(-1)-] [+(50)+(-1)-] \n[+(7)+(-1)-] [+(20)+(-1)-] [+(40)+(-1)-] [+(60)+(-1)-] \n[-(6)-(-1)-] [-(7)-(8)-] [-(9)-(10)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(40)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] \n");
	doTest(16, 11, (int[]){10,20,30,40,50,60,70,-70,61,62,63},	"[+(50)+(-1)-] \n[+(30)+(-1)-] [+(61)+(-1)-] \n[+(20)+(-1)-] [+(40)+(-1)-] [+(60)+(-1)-] [+(62)+(-1)-] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(40)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(61)-(-1)-] [-(62)-(63)-] \n");
	/**/
	
	/**/
	puts("");
	puts("Delete Tests");
	puts("");
	
	doTest(1, 2, (int[]){10,-10},		"");
	doTest(2, 3, (int[]){10,20,-10},	"[-(20)-(-1)-] \n");
	doTest(3, 3, (int[]){10,20,-20},	"[-(10)-(-1)-] \n");

	// En alt bacaktaki tüm silmeler
	doTest(4, 7, (int[]){10,30,50,70,20,40,-10},		"[+(30)+(50)+] \n[-(20)-(-1)-] [-(30)-(40)-] [-(50)-(70)-] \n");
	doTest(5, 7, (int[]){10,30,50,70,20,40,-20},		"[+(30)+(50)+] \n[-(10)-(-1)-] [-(30)-(40)-] [-(50)-(70)-] \n");
	doTest(6, 7, (int[]){10,30,50,70,20,40,-30},		"[+(40)+(50)+] \n[-(10)-(20)-] [-(40)-(-1)-] [-(50)-(70)-] \n");
	doTest(7, 7, (int[]){10,30,50,70,20,40,-40},		"[+(30)+(50)+] \n[-(10)-(20)-] [-(30)-(-1)-] [-(50)-(70)-] \n");
	doTest(8, 7, (int[]){10,30,50,70,20,40,-50},		"[+(30)+(70)+] \n[-(10)-(20)-] [-(30)-(40)-] [-(70)-(-1)-] \n");
	doTest(9, 7, (int[]){10,30,50,70,20,40,-70},		"[+(30)+(50)+] \n[-(10)-(20)-] [-(30)-(40)-] [-(50)-(-1)-] \n");
	
	// Sağ bacaktaki ardışık silmeler
	doTest(10, 8, (int[]){10,30,50,70,20,40,-10,-20},			"[+(40)+(50)+] \n[-(30)-(-1)-] [-(40)-(-1)-] [-(50)-(70)-] \n");
	doTest(11, 9, (int[]){10,30,50,70,20,40,-10,-20,-30},		"[+(50)+(-1)-] \n[-(40)-(-1)-] [-(50)-(70)-] \n");
	doTest(12, 10, (int[]){10,30,50,70,20,40,-10,-20,-30,-40},	"[+(70)+(-1)-] \n[-(50)-(-1)-] [-(70)-(-1)-] \n");
	
	// Orta bacaktaki ardışık silmeler
	doTest(13, 8, (int[]){10,30,50,70,20,40,-40,-30},			"[+(20)+(50)+] \n[-(10)-(-1)-] [-(20)-(-1)-] [-(50)-(70)-] \n");
	doTest(14, 9, (int[]){10,30,50,70,20,40,-40,-30,-20},		"[+(50)+(70)+] \n[-(10)-(-1)-] [-(50)-(-1)-] [-(70)-(-1)-] \n");
	doTest(15, 10, (int[]){10,30,50,70,20,40,-40,-30,-20,-50},	"[+(70)+(-1)-] \n[-(10)-(-1)-] [-(70)-(-1)-] \n");
	
	// Sol bacaktaki ardışık silmeler
	doTest(16, 8, (int[]){10,30,50,70,20,40,-70,-50},			"[+(30)+(40)+] \n[-(10)-(20)-] [-(30)-(-1)-] [-(40)-(-1)-] \n");
	doTest(17, 9, (int[]){10,30,50,70,20,40,-70,-50,-40},		"[+(30)+(-1)-] \n[-(10)-(20)-] [-(30)-(-1)-] \n");
	doTest(18, 10, (int[]){10,30,50,70,20,40,-70,-50,-40,-30},	"[+(20)+(-1)-] \n[-(10)-(-1)-] [-(20)-(-1)-] \n");
	
	// Orta bloğun sağdan+soldan veri alması
	doTest(19, 12, (int[]){10,30,50,70,20,40,12,14,35,60,80,-30},				"[+(35)+(50)+] \n[+(12)+(14)+] [+(40)+(-1)-] [+(60)+(70)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(14)-(20)-] [-(35)-(-1)-] [-(40)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(70)-(80)-] \n");
	doTest(20, 13, (int[]){10,30,50,70,20,40,12,14,35,60,80,-30,-40},			"[+(14)+(50)+] \n[+(12)+(-1)-] [+(35)+(-1)-] [+(60)+(70)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(14)-(20)-] [-(35)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(70)-(80)-] \n");
	doTest(21, 14, (int[]){10,30,50,70,20,40,12,14,35,60,80,-30,-40,-14},		"[+(20)+(50)+] \n[+(12)+(-1)-] [+(35)+(-1)-] [+(60)+(70)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(35)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(70)-(80)-] \n");
	doTest(22, 15, (int[]){10,30,50,70,20,40,12,14,35,60,80,-30,-40,-14,-35},	"[+(20)+(60)+] \n[+(12)+(-1)-] [+(50)+(-1)-] [+(70)+(-1)-] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(70)-(80)-] \n");
	
	// Sol bloğun sağdan veri alması
	doTest(23, 15, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,-40,-70,-14},			"[+(30)+(50)+] \n[+(12)+(20)+] [+(35)+(45)+] [+(60)+(80)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(80)-(-1)-] \n");
	doTest(24, 16, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,-40,-70,-14,-10},		"[+(30)+(50)+] \n[+(20)+(-1)-] [+(35)+(45)+] [+(60)+(80)+] \n[-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(80)-(-1)-] \n");
	doTest(25, 17, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,-40,-70,-14,-10,-12},	"[+(35)+(50)+] \n[+(30)+(-1)-] [+(45)+(-1)-] [+(60)+(80)+] \n[-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(80)-(-1)-] \n");
	
	// Sağ bloğun soldan veri alması
	doTest(26, 15, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,-40,-70,-14},			"[+(30)+(50)+] \n[+(12)+(20)+] [+(35)+(45)+] [+(60)+(80)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] [-(80)-(-1)-] \n");
	doTest(27, 16, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,-40,-70,-14,-80},		"[+(30)+(50)+] \n[+(12)+(20)+] [+(35)+(45)+] [+(60)+(-1)-] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(60)-(-1)-] \n");
	doTest(28, 17, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,-40,-70,-14,-80,-60},	"[+(30)+(45)+] \n[+(12)+(20)+] [+(35)+(-1)-] [+(50)+(-1)-] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] \n");
	
	// Other...
	doTest(29, 22, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,90,52,54,72,74,-14,-40,-52,-74,-80},				"[+(50)+(-1)-] \n[+(30)+(-1)-] [+(70)+(-1)-] \n[+(12)+(20)+] [+(35)+(45)+] [+(54)+(60)+] [+(72)+(90)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(54)-(-1)-] [-(60)-(-1)-] [-(70)-(-1)-] [-(72)-(-1)-] [-(90)-(-1)-] \n");
	
	doTest(30, 24, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,90,52,54,72,74,-14,-40,-52,-74,-80,-10,-12},		"[+(50)+(-1)-] \n[+(35)+(-1)-] [+(70)+(-1)-] \n[+(30)+(-1)-] [+(45)+(-1)-] [+(54)+(60)+] [+(72)+(90)+] \n[-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(54)-(-1)-] [-(60)-(-1)-] [-(70)-(-1)-] [-(72)-(-1)-] [-(90)-(-1)-] \n");
	doTest(31, 25, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,90,52,54,72,74,-14,-40,-52,-74,-80,-10,-12,-20},	"[+(50)+(70)+] \n[+(35)+(45)+] [+(54)+(60)+] [+(72)+(90)+] \n[-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(54)-(-1)-] [-(60)-(-1)-] [-(70)-(-1)-] [-(72)-(-1)-] [-(90)-(-1)-] \n");
	
	doTest(32, 24, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,90,52,54,72,74,-14,-40,-52,-74,-80,-50,-54},		"[+(60)+(-1)-] \n[+(30)+(-1)-] [+(72)+(-1)-] \n[+(12)+(20)+] [+(35)+(45)+] [+(70)+(-1)-] [+(90)+(-1)-] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(60)-(-1)-] [-(70)-(-1)-] [-(72)-(-1)-] [-(90)-(-1)-] \n");
	doTest(33, 25, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,90,52,54,72,74,-14,-40,-52,-74,-80,-50,-54,-60},	"[+(30)+(70)+] \n[+(12)+(20)+] [+(35)+(45)+] [+(72)+(90)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(70)-(-1)-] [-(72)-(-1)-] [-(90)-(-1)-] \n");
	
	doTest(34, 24, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,90,52,54,72,74,-14,-40,-52,-74,-80,-90,-72},		"[+(50)+(-1)-] \n[+(30)+(-1)-] [+(60)+(-1)-] \n[+(12)+(20)+] [+(35)+(45)+] [+(54)+(-1)-] [+(70)+(-1)-] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(54)-(-1)-] [-(60)-(-1)-] [-(70)-(-1)-] \n");
	doTest(35, 25, (int[]){10,30,50,70,20,40,12,14,35,60,80,45,90,52,54,72,74,-14,-40,-52,-74,-80,-90,-72,-70},	"[+(30)+(50)+] \n[+(12)+(20)+] [+(35)+(45)+] [+(54)+(60)+] \n[-(10)-(-1)-] [-(12)-(-1)-] [-(20)-(-1)-] [-(30)-(-1)-] [-(35)-(-1)-] [-(45)-(-1)-] [-(50)-(-1)-] [-(54)-(-1)-] [-(60)-(-1)-] \n");
	
	doTest(38, 14, (int[]){0,2,5,7,11,15,17,18,19,21,22,24,-22,22},		"[+(11)+(-1)-] \n[+(5)+(-1)-] [+(17)+(19)+] \n[+(2)+(-1)-] [+(7)+(-1)-] [+(15)+(-1)-] [+(18)+(-1)-] [+(21)+(24)+] \n[-(0)-(-1)-] [-(2)-(-1)-] [-(5)-(-1)-] [-(7)-(-1)-] [-(11)-(-1)-] [-(15)-(-1)-] [-(17)-(-1)-] [-(18)-(-1)-] [-(19)-(-1)-] [-(21)-(22)-] [-(24)-(-1)-] \n");
	doTest(39, 15, (int[]){0,2,5,7,11,15,17,18,19,21,22,24,-22,22,-7},	"[+(17)+(-1)-] \n[+(11)+(-1)-] [+(19)+(-1)-] \n[+(2)+(5)+] [+(15)+(-1)-] [+(18)+(-1)-] [+(21)+(24)+] \n[-(0)-(-1)-] [-(2)-(-1)-] [-(5)-(-1)-] [-(11)-(-1)-] [-(15)-(-1)-] [-(17)-(-1)-] [-(18)-(-1)-] [-(19)-(-1)-] [-(21)-(22)-] [-(24)-(-1)-] \n");
	/**/
	
	
	
	puts("");
	puts("Special Tests");
	puts("");
	
	
	
	int i, limit = 7000;
	/**/
	printf("Test 1 - START\n");
	root = NULL;
	for(i=0;i<limit;i++){
		bptreeInsert(i);
	}
	for(i=0;i<limit;i++){
		bptreeDelete(i);
	}
	//bptreePrint();
	printf("Test 1 - END\n\n");
	
	
	
	printf("Test 2 - START\n");
	root = NULL;
	for(i=0;i<limit;i++){
		bptreeInsert(i);
	}
	for(i=limit-1;i>=0;i--){
		bptreeDelete(i);
	}
	//bptreePrint();
	printf("Test 2 - END\n\n");
	
	
	
	printf("Test 3 - START\n");
	int listSize = 1*1000, testCount = 10*1000*1000;
	char list[listSize];
	for(i=0;i<listSize;i++){
		list[i] = 0;
	}
	root = NULL;
	srand(time(NULL));
	while( testCount-- > 0 ){
		//bptreePrint();
		int index = rand() % listSize;
		if( list[index] == 1 ){
			bptreeDelete(index);
			list[index] = 0;
		}else{
			bptreeInsert(index);
			list[index] = 1;
		}
	}
	printf("Test 3 - ENDING\n");
	for(i=0;i<listSize;i++){
		if( list[i] == 1 ){
			bptreeDelete(i);
			list[i] = 0;
		}
	}
	printf("Test 3 - END\n\n");
	
}

