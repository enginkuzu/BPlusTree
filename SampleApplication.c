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

#include "ek_BPlusTree.c"
#include "ek_BPlusTreeHelper.c"

int main(){
	
	bptreeInsert(1);
	bptreeInsert(2);
	bptreeInsert(3);
	bptreeInsert(4);
	bptreeInsert(5);
	
	bptreeDelete(3);
	
	bptreePrint();
	
	return 0;
}
