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

#include <stdio.h>
#include <stdlib.h>

typedef struct BPlusTreeRecord {
	struct BPlusTreeRecord* p1;		// Pointer (left)
	int d1;							// Data 1
	struct BPlusTreeRecord* p2;		// Pointer (center)
	int d2;							// Data 2
	struct BPlusTreeRecord* p3;		// Pointer (right)
} BPlusTreeRecord;

BPlusTreeRecord* root = NULL;

BPlusTreeRecord* bptreeGetRecord(int d1, int d2){
	BPlusTreeRecord* record = (BPlusTreeRecord*)malloc(sizeof(BPlusTreeRecord));
	record->p1 = NULL;
	record->d1 = d1;
	record->p2 = NULL;
	record->d2 = d2;
	record->p3 = NULL;
	return record;
}

BPlusTreeRecord* _bptreeInsert( BPlusTreeRecord* node, int value){
	
	int d1 = node->d1;
	int d2 = node->d2;
	
	if( node->p1 == NULL && node->p2 == NULL && node->p3 == NULL ){
		
		if( d1 == -1 ){
			node->d1 = value;
		}else if( d2 == -1 ){
			if( d1 < value ){
				node->d2 = value;
			}else{
				node->d1 = value;
				node->d2 = d1;
			}
		}else{
			int min, center, max;
			if( value < d1 ){
				min = value;	center = d1;		max = d2;
			}else if( value < d2 ){
				min = d1;		center = value;		max = d2;
			}else{
				min = d1;		center = d2;		max = value;
			}
			BPlusTreeRecord* nodeLeft = bptreeGetRecord(min, -1);
			BPlusTreeRecord* nodeUp = bptreeGetRecord(center, -1);
			nodeUp->p1 = nodeLeft;
			nodeUp->p2 = node;
			node->d1 = center;
			node->d2 = max;
			return nodeUp;
		}
		
	}else{
		
		BPlusTreeRecord* nodeDown = NULL;
		if( value < d1 ){
			nodeDown = _bptreeInsert(node->p1, value);
		}else if( d2 != -1 && value >= d2 ){
			nodeDown = _bptreeInsert(node->p3, value);
		}else{
			nodeDown = _bptreeInsert(node->p2, value);
		}
		
		if( nodeDown != NULL ){
			if( d2 == -1 ){
				if( d1 < nodeDown->d1 ){
					node->d2 = nodeDown->d1;
					node->p2 = nodeDown->p1;
					node->p3 = nodeDown->p2;
				}else{
					node->d1 = nodeDown->d1;
					node->d2 = d1;
					node->p3 = node->p2;
					node->p1 = nodeDown->p1;
					node->p2 = nodeDown->p2;
				}
				free(nodeDown);
			}else{
				int center;
				BPlusTreeRecord* nodeNew = NULL;
				if( nodeDown->d1 < d1 ){
					center = d1;
					nodeNew = bptreeGetRecord(d2, -1);	// max
					nodeNew->p1 = node->p2;
					nodeNew->p2 = node->p3;
					node->p1 = nodeDown;
					node->p2 = nodeNew;
				}else if( nodeDown->d1 < d2 ){
					center = nodeDown->d1;
					nodeNew = bptreeGetRecord(d1, -1);	// min
					nodeNew->p1 = node->p1;
					nodeNew->p2 = nodeDown->p1;
					nodeDown->d1 = d2;					// max
					nodeDown->p1 = nodeDown->p2;
					nodeDown->p2 = node->p3;
					node->p1 = nodeNew;
					node->p2 = nodeDown;
				}else{
					center = d2;
					nodeNew = bptreeGetRecord(d1, -1);	// min
					nodeNew->p1 = node->p1;
					nodeNew->p2 = node->p2;
					node->p1 = nodeNew;
					node->p2 = nodeDown;
				}
				node->d1 = center;
				node->d2 = -1;
				node->p3 = NULL;
				return node;
			}
		}
		
	}
	return NULL;
}
void bptreeInsert(int value){
	//printf("ADD [%d]\n", value);
	if( root == NULL ) root = bptreeGetRecord(-1, -1);
	 BPlusTreeRecord* node = _bptreeInsert(root, value);
	if( node != NULL ) root = node;
}

typedef struct DeleteReturn {
	char code;
	int data;
} DeleteReturn;

// return codes
// 0 : NO ACTION
// 2 : LEAF DELETED (DOWN)
// 3 : SINGLE LEAF ALIVE (UPPER STAGES)
DeleteReturn _bptreeDelete( BPlusTreeRecord* node, int value){
	
	int d1 = node->d1;
	int d2 = node->d2;
	
	if( node->p1 == NULL && node->p2 == NULL && node->p3 == NULL ){
		
		if( d2 == -1 ){
			if( d1 == value ){
				return (DeleteReturn){ .code = 2, .data = -1 };
			}
		}else{
			if( d1 == value ){
				node->d1 = d2;
				node->d2 = -1;
				return (DeleteReturn){ .code = 0, .data = node->d1 };
			}else if( d2 == value ){
				node->d2 = -1;
				return (DeleteReturn){ .code = 0, .data = -1 };
			}
		}
		
		printf("value[%d] NOT FOUND !!!\n", value);
		return (DeleteReturn){ .code = 0, .data = -1 };
		
	}else{
		
		if( value < d1 ){
			DeleteReturn ret = _bptreeDelete(node->p1, value);
			if( ret.code == 2 ){
				if( node->p2->d2 != -1 ){					// sağdaki bacak 3 elemanlı veri ise, yandan al
					node->p1->d1 = node->p2->d1;
					node->p2->d1 = node->p2->d2;
					node->p2->d2 = -1;
					node->d1 = node->p2->d1;
					ret.data = node->p1->d1;
				}else if( d2 != -1 ){						// değilse burayı sil, yapıyı 2 bacaklı yap
					free(node->p1);
					node->p1 = node->p2;
					node->p2 = node->p3;
					node->p3 = NULL;
					node->d1 = d2;
					node->d2 = -1;
				}else{										// tek canlı bacak kalmış, o da p2
					free(node->p1);
					node->p1 = node->p2;
					node->p2 = NULL;
					ret.code = 3;
					ret.data = node->p1->d1;
					return ret;
				}
			}else if( ret.code == 3 ){
				if( node->p2->d2 != -1 ){					// sağdaki bacak 3 elemanlı ağaç ise, yandan al
					node->p1->p2 = node->p2->p1;
					node->p2->p1 = node->p2->p2;
					node->p2->p2 = node->p2->p3;
					node->p2->p3 = NULL;
					node->p1->d1 = d1;
					node->d1 = node->p2->d1;
					node->p2->d1 = node->p2->d2;
					node->p2->d2 = -1;
				}else{										// sağa entegre ol
					node->p2->p3 = node->p2->p2;
					node->p2->p2 = node->p2->p1;
					node->p2->p1 = node->p1->p1;
					node->p2->d2 = node->p2->d1;
					node->p2->d1 = d1;
					free(node->p1);
					node->p1 = node->p2;
					node->p2 = node->p3;
					node->p3 = NULL;
					node->d1 = d2;
					node->d2 = -1;
					if( node->p2 != NULL ) ret.code = 0;
					return ret;
				}
			}
			ret.code = 0;
			return ret;
		}else if( d2 != -1 && value >= d2 ){
			DeleteReturn ret = _bptreeDelete(node->p3, value);
			if( ret.data != -1 ){
				d2 = node->d2 = ret.data;
				ret.data = -1;
			}
			if( ret.code == 2 ){
				if( node->p2->d2 != -1 ){					// soldaki bacak 3 elemanlı veri ise, yandan al
					node->p3->d1 = node->p2->d2;
					node->d2 = node->p3->d1;
					node->p2->d2 = -1;
				}else{										// değilse burayı sil, yapıyı 2 bacaklı yap
					free(node->p3);
					node->p3 = NULL;
					node->d2 = -1;
				}
			}else if( ret.code == 3 ){
				if( node->p2->d2 != -1 ){					// soldaki bacak 3 elemanlı ise, yandan al
					node->p3->p2 = node->p3->p1;
					node->p3->p1 = node->p2->p3;
					node->p2->p3 = NULL;
					node->p3->d1 = d2;
					node->d2 = node->p2->d2;
					node->p2->d2 = -1;
				}else{										// sola entegre ol
					node->p2->p3 = node->p3->p1;
					free(node->p3);
					node->p3 = NULL;
					node->p2->d2 = d2;
					node->d2 = -1;
				}
			}
			ret.code = 0;
			return ret;
		}else{
			DeleteReturn ret = _bptreeDelete(node->p2, value);
			if( ret.data != -1 ){
				d1 = node->d1 = ret.data;
				ret.data = -1;
			}
			if( ret.code == 2 ){
				if( node->p1->d2 != -1 ){					// soldaki bacak 3 elemanlı veri ise, yandan al
					node->p2->d1 = node->p1->d2;
					node->d1 = node->p2->d1;
					node->p1->d2 = -1;
				}else if( d2 != -1 ){
					if( node->p3->d2 != -1 ){				// sağdaki bacak 3 elemanlı veri ise, yandan al
						node->p2->d1 = node->p3->d1;
						node->p3->d1 = node->p3->d2;
						node->p3->d2 = -1;
						node->d1 = node->p2->d1;
						node->d2 = node->p3->d1;
					}else{									// değilse burayı sil, yapıyı 2 bacaklı yap
						free(node->p2);
						node->p2 = node->p3;
						node->p3 = NULL;
						node->d1 = d2;
						node->d2 = -1;
					}
				}else{										// tek canlı bacak kalmış, o da p1
					free(node->p2);
					ret.code = 3;
					return ret;
				}
				ret.code = 0;
				return ret;
			}else if( ret.code == 3 ){
				if( node->p1->d2 != -1 ){					// soldaki bacak 3 elemanlı ağaç ise, yandan al
					node->p2->p2 = node->p2->p1;
					node->p2->p1 = node->p1->p3;
					node->p1->p3 = NULL;
					node->p2->d1 = d1;
					node->d1 = node->p1->d2;
					node->p1->d2 = -1;
				}else if( d2 != -1 && node->p3->d2 != -1 ){	// sağdaki bacak 3 elemanlı ağaç ise, yandan al
					node->p2->p2 = node->p3->p1;
					node->p3->p1 = node->p3->p2;
					node->p3->p2 = node->p3->p3;
					node->p3->p3 = NULL;
					node->p2->d1 = d2;
					node->d2 = node->p3->d1;
					node->p3->d1 = node->p3->d2;
					node->p3->d2 = -1;
				}else{										// sola entegre ol
					node->p1->p3 = node->p2->p1;
					free(node->p2);
					node->p2 = node->p3;
					node->p3 = NULL;
					node->p1->d2 = d1;
					node->d1 = d2;
					node->d2 = -1;
					if( node->p2 != NULL ) ret.code = 0;
					return ret;
				}
				ret.code = 0;
				return ret;
			}
		}
	}
	
	return (DeleteReturn){ .code = 0, .data = -1 };
}
void bptreeDelete(int value){
	//printf("DELETE [%d]\n", value);
	if( root == NULL ){ printf("value[%d] NOT FOUND, STRUCTURE NOT INITED!\n", value); return; }
	DeleteReturn ret = _bptreeDelete(root, value);
	if( ret.code == 3 ){
		BPlusTreeRecord* ptr = root->p1;
		free(root);
		root = ptr;
	}else if( ret.code == 2 ){
		root = NULL;
	}
}

