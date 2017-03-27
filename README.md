# C-Project-Mazes-

# C++ and Multidimensional Arrays 

C++ doesn't have very good support for dynamically allocated multidimensional arrays; languages like Java are much better at this kind of thing. In C++, we typically allocate a 1-dimensional array with enough space for the total number of elements, and then map our 2D (or 3D, or whatever) coordinates into our 1D array. For example, given a 2D array with Nrows rows and Ncols columns:

-The program can allocate a 1D array with Nrows × Ncols elements
-An element at 2D position (row, col) can be mapped to row × Ncols + col

This mapping should make sense: for each row we are going to skip, we must move past Ncols cells to get to the next row. Of course, this is not the only way we can map 2D coordinates into the 1D array, but this is the typical approach for C and C++. It is called a row-major order. (A few other languages, like MATLAB and Fortran, use a column-major order for how they represent multidimensional arrays.)

# Accessing Maze Cells and Walls
In order to provide a simple abstraction for people to use, we will implement a Maze class that uses cell coordinates to reference various aspects of the maze, but internally we will map cell coordinates into the "expanded representation" we use internally. We will call the coordinates in the expanded representation expanded coordinates.

You should be able to see how to map cell coordinates into expanded coordinates very easily. Given a maze with Ncell − rows × Ncell − cols cells, we can map the cell coordinates (rcell, ccell) into expanded coordinates (rexp, cexp) as follows:

-rexp = 2rcell + 1
-cexp = 2ccell + 1
Given a particular cell, we will want to know if there is a wall on a particular side of the cell; we will use the cardinal directions "North", "East", "South" or "West" of the cell. Then, we can ask questions like:

-Is there a wall to the west (left) of cell (1, 2) in the original maze? Yes.
-Is there a wall to the north of cell (2, 3) in the maze? No.
Accessing the walls between cells is similarly straightforward:

-To access the wall north of a given cell, compute the cell's expanded coordinates and subtract 1 from the row value.
-To access the wall south of a given cell, compute the cell's expanded coordinates and add 1 to the row value.
-To access the wall east of a given cell, compute the cell's expanded coordinates and add 1 to the column value.
-To access the wall west of a given cell, compute the cell's expanded coordinates and subtract 1 from the column value.
