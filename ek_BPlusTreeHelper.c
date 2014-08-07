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

int printBufferIndex;
char printBuffer[4*1024];

int __bptreePrint( BPlusTreeRecord* node, int level, int required){
	if( level > required ){
		return 0;
	}else if( level == required ){
		printBufferIndex += sprintf(printBuffer+printBufferIndex, "[%c(%d)%c(%d)%c] ",
			node->p1==NULL?'-':'+', node->d1, node->p2==NULL?'-':'+', node->d2, node->p3==NULL?'-':'+');
		return 1;
	}
	int total = 0;
	if( node->p1 != NULL ) total += __bptreePrint(node->p1, level+1, required);
	if( node->p2 != NULL ) total += __bptreePrint(node->p2, level+1, required);
	if( node->p3 != NULL ) total += __bptreePrint(node->p3, level+1, required);
	return total;
}
void _bptreePrint(){
	printBufferIndex = 0;
	if( root == NULL ){ printBuffer[0] = 0; return; }
	
	int required = 1;
	while( __bptreePrint(root, 1, required) > 0 ){
		required++;
		printBufferIndex += sprintf(printBuffer+printBufferIndex, "\n");
	}
	printBuffer[printBufferIndex+1] = 0;
}
void bptreePrint(){
	_bptreePrint();
	printf("<---\n%s--->\n", printBuffer);
}

