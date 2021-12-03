Final Project README for CSC245
Samantha Scholz

Problem:We want to create a directed graph and determine the most cost efficient routes to other vertices given a starting point using Dijstra's Algorithm.


GRAPH CLASS:
	-Graph takes input for the type of vertices to be stored 
	-in this program that vertex type is string
	-it is built with 2 one dimensional arrays(vertices and marks) and 1 two dimensional array(edges)
	-Functions Used:
		AddVertex:
			-takes specified vertex type (ex: string) input
			-creates a vertex with null edges through the 2 dimensional array: edges. Enters a 0 Value
		AddEdge:
			-takes specified vertex type (ex: string) input for tail of the arrow, specified vertex type (ex: string) input for head of the arrow,
			and an integer value for the weight/distance/cost between the two points
			-using the indexes of the two vertices the weight is recorded in the 2 dimensional array
		GetToVertices:
			-takes specified vertex type (ex: string) input and a queue object
			-fills the queue with the vertex's neighbors(anywhere there is a path)
		WeightIs:
			-takes specified vertex type (ex: string) input for tail of the arrow, specified vertex type (ex: string) input for head of the arrow
			-returns the weight/cost/distance if the path exists(i.e. does not equal 0 in the 2D array)
DIJKSTRA.CPP:
	-main:
		-takes char* argument at command line
		-if no argument received the program exits
		-graph, queue, and vector objects are created 
		-fillGraph is called to read input and add vertices to the graph using substr to separate values from ;s
		-boolean array marked is set to false(0) for all values through declareZero
		-int array distances is set to have infinite values through declareMax
		-prevVisit is instantiated to hold last vertex visited for each vertex
		-the vector is sorted and printed in printSorted
		-user is prompted for a starting vertex until a valid vertex is given using find method
		-start's distance is set to 0 and previously visited node is set to N/A
		-Dijkstra's Algorithm begins
		-while loop runs the algorithm until all nodes are marked using allVisited method
			-mark the start as visited
			-display values
			-enqueue neighbors using graph method GetToVertices
			-loop until queue is empty
				-if the neighbor is not marked as visited
					-if the calculated distance to reach the neighbor from the start is less than the distance in the distance array
						-update distance and previously visited values
				-dequeue
		-check for cycles
			-use declareZero to unmark all marked vertices
			-for each vertex recursively call isCycle until start node is reached or proven false
	-find:
		-int method
		-for every value in the vector: compare the specified word to the value at the index
		-if found return the position of the word in the vector
	-allVisited:
		-boolean method
		-run through a boolean array of values
		-return false if a value is found to be 0 (unmarked)
		-otherwise return true
	-fillGraph:
		-opens file
		-if incorrect file name is given the user is prompted for another
		-input is read from file
	-printSorted:
		-sorts vector using sort method and v.begin() and v.end()
		-prints each value in the vector with an inner if statement that prints an end line if index%3=0 and index does not equal 0
	-findMin:
		-int method
		-declare int min as INT_MAX
		-for every value in the array if the value is unmarked and has a smaller distance than min:
			-update min and record position/index
		-return position of min
		-using ; as a delimiter, string find function, and substr
		-origin, destination, and distance are collected
		-if the vector is not in the vector containing vertices it is added using push_back and added to myGraph using AddVertex
		-the distance is converted using atoi
		-myGraph adds an edge using the previous 3 variables mentioned
	-declareZero:
		-void method
		-set all values of an array to 0(false)
	-declareMax:
		-void method
		-set all values of an array to INT_MAX
