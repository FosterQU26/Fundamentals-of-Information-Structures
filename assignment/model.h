#ifndef ASSIGNMENT_MODEL_H
#define ASSIGNMENT_MODEL_H

#include "defs.h"

struct Cell_Content {
    enum types {Blank, Data, Text, Formula} Type; //type dictates what kind of value is stored at the Cell
    double Data;
    char* Text;  
};

struct Node {
    int row, col, num_Deps; 
    struct Node* dep[NUM_ROWS * NUM_COLS];
};

struct Graph {
    struct Node* Nodes[NUM_ROWS][NUM_COLS];
    int num_nodes;
};

// Initializes the data structure.
//
// This is called once, at program start.
void model_init();

// Initializes a Graph to store dependencies
//
// Is called along side Model_init
void graph_init(struct Graph* graph);

//Adds a node to the Graph
void add_node(struct Graph* graph, int row, int col);

//Links two nodes together with a dependency
//Returns 0 if there is a circular dependency, 1 otherwise
int add_dependency(struct Node* Source, struct Node* Dependent);

//Adds a dependency from every cell within a range
int add_dependency_to_range(int s_row, int s_col, int f_row, int f_col, ROW dep_row,COL dep_col);

//Checks for circular dependencies betwen nodes
//Returns 1 if there is a circular dependency, 0 otherwise
int has_circular_dependency(struct Node* Source, struct Node* ref);

// Updates the Dependent nodes fo the source
void update_dependency(struct Node* source);

// Sets the value of a cell based on user input.
//
// The string referred to by 'text' is now owned by this function and/or the
// cell contents data structure; it is its responsibility to ensure it is freed
// once it is no longer needed.
void set_cell_value(ROW row, COL col, char *text);

// Clears the value of a cell.
void clear_cell(ROW row, COL col);

//Gets a textual representation of the numerical value of a cell, for displaying.
//
// The returned string must have been allocated using 'malloc' and is now owned
// by the interface. The cell contents data structure must not modify it or
// retain any reference to it after the function returns.
char *get_display_value(ROW row, COL col);

// Gets a textual representation of the value of a cell, for editing.
//
// The returned string must have been allocated using 'malloc' and is now owned
// by the interface. The cell contents data structure must not modify it or
// retain any reference to it after the function returns.
char *get_textual_value(ROW row, COL col);

//Computes the formula stored in the text at a cell
//returns the answer as a double
double comp_formula(ROW row,COL col);

//Converts from the Coordinate from A1 to Indicies (0,0)
int coord_to_indicie(char* coordinate, int* row, int* col);

//Converts from a Range of Cells [A1:B2] to start and end indicies (0,0),(1,1)
int get_range(char* formula,int* s_row, int* s_col,int* f_row, int* f_col );

//Takes the Sum value of a Range
double sum_of_range(int s_row, int s_col, int f_row, int f_col);

//Takes the Average value of a Range
double avg_of_range(int s_row, int s_col, int f_row, int f_col);

//Takes the Minimum value of a Range
double min_of_range(int s_row, int s_col, int f_row, int f_col);

//Takes the Maximum value of a Range
double max_of_range(int s_row, int s_col, int f_row, int f_col);

//Helper function to assert the Prefix of a string
int starts_with(const char *str, const char *prefix);

//Error Function
int error(ROW row,COL col,char* err);

#endif //ASSIGNMENT_MODEL_H

