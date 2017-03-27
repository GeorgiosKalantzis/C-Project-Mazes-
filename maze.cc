#include "maze.hh"

int Maze::getArrayIndex(const Location loc) const{

	int noExpandCols = 2 * numCols + 1;

	return loc.row * noExpandCols + loc.col;
}

Location Maze::getCellArrayCoord(int cellRow, int cellCol) const{

	return Location(2 * cellRow + 1, 2 * cellCol + 1);
}

Location Maze::getWallArrayCoord(int cellRow, int cellCol,
                                 Direction direction) const{

	int expandRow = 2 * cellRow + 1;

	int expandCol = 2 * cellCol + 1;

	switch (direction)
	{
	case Direction::NORTH:
		return Location(expandRow - 1, expandCol);
		break;

	case Direction::SOUTH:
		return Location(expandRow + 1, expandCol);
		break;

	case Direction::EAST:
		return Location(expandRow, expandCol + 1);
		break;

	case Direction::WEST:
		return Location(expandRow, expandCol - 1);
		break;

	default:
		return Location();
		break;
	}
}


Maze::Maze(int rows, int cols)
{
	numRows = rows;

	numCols = cols;

	int expandRows = 2 * numRows + 1;

	int expandCols = 2 * numCols + 1;

	cells = (MazeCell*)malloc(expandRows * expandCols * sizeof(MazeCell));

	start = Location();

	end = Location();
}

Maze::Maze(const Maze &m)
{
	numRows = m.numRows;

	numCols = m.numCols;

	int expandRows = 2 * numRows + 1;

	int expandCols = 2 * numCols + 1;

	cells = (MazeCell*)malloc(expandRows * expandCols * sizeof(MazeCell));

	for (int i = 0; i<expandRows * expandCols; i++)
	{
		cells[i] = m.cells[i];
	}

	start = Location(m.getStart().row, m.getStart().col);

	end = Location(m.getEnd().row, m.getEnd().col);
}

Maze::~Maze()
{
	free(cells);
}


Maze& Maze::operator=(const Maze &m)
{
	numRows = m.numRows;

	numCols = m.numCols;

	int expandRows = 2 * numRows + 1;

	int expandCols = 2 * numCols + 1;

	cells = (MazeCell*)realloc(cells, expandRows * expandCols * sizeof(MazeCell));

	for (int i = 0; i<expandRows * expandCols; i++)
	{
		cells[i] = m.cells[i];
	}
	start = m.getStart();

	end = m.getEnd();

	return *this;
}


int Maze::getNumRows() const
{
	return numRows;
}

int Maze::getNumCols() const
{
	return numCols;
}

Location Maze::getStart() const
{
	return start;
}

Location Maze::getEnd() const
{
	return end;
}

MazeCell Maze::getCell(int cellRow, int cellCol) const
{
	Location loc = getCellArrayCoord(cellRow, cellCol);

	int index = getArrayIndex(loc);

	return cells[index];
}

Location Maze::getNeighborCell(int cellRow, int cellCol, Direction direction) const
{

	switch (direction)
	{
	case Direction::NORTH:

		return Location(cellRow - 1, cellCol);

		break;
	case Direction::SOUTH:

		return Location(cellRow + 1, cellCol);

		break;
	case Direction::EAST:

		return Location(cellRow, cellCol + 1);

		break;
	case Direction::WEST:

		return Location(cellRow, cellCol - 1);

		break;

	default:
		return Location();
		break;
	}
}

bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const
{
	Location wall = getWallArrayCoord(cellRow, cellCol, direction);

	int index = getArrayIndex(wall);

	if (cells[index] == MazeCell::WALL) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool Maze::isVisited(int cellRow, int cellCol) const
{
	if (getCell(cellRow, cellCol) == MazeCell::VISITED)
	{
		return true;
	}
	else 
	{
		return false;
	}
}


void Maze::setStart(int row, int col)
{
	start.row = row;

	start.col = col;
}

void Maze::setEnd(int row, int col)
{
	end.row = row;

	end.col = col;
}

void Maze::clear()
{
	int expandRows = 2 * numRows + 1;

	int expandCols = 2 * numCols + 1;

	for (int i = 0; i< expandRows * expandCols; i++)
	{
		cells[i] = MazeCell::EMPTY;
	}
}

void Maze::setAllWalls()
{
	int expandRows = 2 * numRows + 1;

	int expandCols = 2 * numCols + 1;

	for (int i = 1; i< expandRows * expandCols; i = i + 2)
	{
		cells[i] = MazeCell::WALL;
	}

}

void Maze::setCell(int cellRow, int cellCol, MazeCell val)
{
	Location loc = getCellArrayCoord(cellRow, cellCol);

	int index = getArrayIndex(loc);

	cells[index] = val;
}

void Maze::setWall(int cellRow, int cellCol, Direction direction)
{
	Location wall = getWallArrayCoord(cellRow, cellCol, direction);

	int index = getArrayIndex(wall);

	cells[index] = MazeCell::WALL;
}

void Maze::clearWall(int cellRow, int cellCol, Direction direction)
{
	Location wall = getWallArrayCoord(cellRow, cellCol, direction);

	int index = getArrayIndex(wall);

	cells[index] = MazeCell::EMPTY;
}

void Maze::setVisited(int cellRow, int cellCol)
{
	setCell(cellRow, cellCol, MazeCell::VISITED);
}

void Maze::print(ostream &os) const
{
	
	os << numRows << " " << numCols << endl;

	Location loc;
	
	for (int r = 0; r < numRows; r++)
	{
		os << "+";                  

		for (int c = 0; c < numCols; c++)
		{
			if (hasWall(r, c, Direction::NORTH)) {
				os << "---";          
			}
			else {
				os << "   ";            
			}
			os << "+";               
		}
		os << endl;
		
		if (hasWall(r, 0, Direction::WEST))
		{
			os << "|";                
		else 
		{
			os << " ";               
		}
		for (int c = 0; c < numCols; c++) 
		{
			loc = Location(r, c);

			if (loc == start)
			{
				os << " S ";          
			}
			else if (loc == end)
			{
				os << " E ";           
			}
			else
			{
				os << "   ";            
			}

			
			if (hasWall(r, c, Direction::EAST))
			{
				os << "|";           
			}
			else 
			{
				os << " ";            
			}
		}
		os << endl;
	}
	
	os << "+";                
	for (int c = 0; c < numCols; c++) 
	{
		if (hasWall(numRows - 1, c, Direction::SOUTH))
		{
			os << "---";           
		}
		else 
		{
			os << "   ";          
		}
		os << "+";              
	}
	os << endl;
}
