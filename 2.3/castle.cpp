#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
using namespace std;

struct block {
    bool visited;
    int walls, room;

    block (): visited(false) {}
};

// Walks all the blocks of a room
// marks them as visited, assigns them to the room
// and returns the room's size
int walkRoom ( int room, int y, int x, block **blocks ) {
    if ( blocks[y][x].visited ) return 0;

    blocks[y][x].visited = true;
    blocks[y][x].room = room;

    int size = 1,
        noWalls = 16 - blocks[y][x].walls;
    for ( int i = 3, p; i >= 0; i-- ) {
        p = pow(2, i);
        if ( noWalls > p ) {
            size += walkRoom( room, y + (i-2)%2, x + (i-1)%2, blocks );
            noWalls -= p; 
        }
    }

    return size;
}

int main() {
    ifstream input("castle.in");
    ofstream output("castle.out");

    // Read params
    int rows, columns, y, x;
    input >> rows >> columns;
    block *blocks[rows];
    for ( y = 0; y < rows; y++ ) {
        blocks[y] = new block[columns];
        for ( x = 0; x < columns; x++ ) input >> blocks[y][x].walls;
    }

    // Find all rooms and room sizes
    int size;
    vector<int> roomSizes;
    for ( y = 0; y < rows; y++ ) {
        for ( x = 0; x < columns; x++ ) {
            size = walkRoom(roomSizes.size(), y, x, blocks);
            if ( size > 0 ) roomSizes.push_back(size);
        }
    }


    // Loop through all blocks, find any two
    // adjacent that do not belong to the same
    // room and figure out the size of their combined
    // rooms and store the maximum size
    int maxSize = 0,
        room, topRoom, eastRoom;
    ostringstream wall;
    for ( x = 0; x < columns; x++ ) {
        for ( y = rows-1; y >= 0; y-- ) {
            room = topRoom = eastRoom = blocks[y][x].room;
            if ( y-1 >= 0 ) topRoom = blocks[y-1][x].room;
            if ( x+1 < columns ) eastRoom = blocks[y][x+1].room;

            if ( room != topRoom ) {  
                size = roomSizes[room] + roomSizes[topRoom];  
                if ( size > maxSize ) {  
                    maxSize= size;  
                    (wall.str(""), wall) << y+1 << " " << x+1 << " N";  
                }  
            }  
            if ( room != eastRoom ) {  
                size = roomSizes[room] + roomSizes[eastRoom];  
                if ( size > maxSize ) {  
                    maxSize = size;  
                    (wall.str(""), wall) << y+1 << " " << x+1 << " E";  
                }  
            }
        }
    }


    output << roomSizes.size() << "\n"
           << *max_element(roomSizes.begin(), roomSizes.end()) << "\n"
           << maxSize << "\n"
           << wall.str() << endl;


    // Wrap things up
    for ( y= 0; y < rows; y++ ) delete[] blocks[y];
    input.close();
    output.close();

    return 0;
}