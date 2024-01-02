#include "model.h"
#include "interface.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct Cell_Content spreadsheet[NUM_ROWS][NUM_COLS] = {0};
struct Graph DependencyGraph;

void graph_init(struct Graph* graph){
    for (size_t i = 0; i < NUM_ROWS; i++){
        for (size_t j = 0; j < NUM_COLS; j++){
            graph->Nodes[i][j] = NULL;
        }
    }
    graph->num_nodes = 0;
}

void model_init() {
    for (size_t i = 0; i < NUM_ROWS; i++){
        for (size_t j = 0; j < NUM_COLS; j++){
            clear_cell(i,j);
        } 
    }
    graph_init(&DependencyGraph);
}

void add_node(struct Graph* graph, int row, int col){
    if(graph->num_nodes >= NUM_ROWS * NUM_COLS){ //If there is max num of Deps
        return; 
    }
    if(graph->Nodes[row][col] != NULL){ //If the Node exists
        return;
    }
    struct Node* new_node = malloc(sizeof(struct Node*));
    new_node->col = col;
    new_node->row = row;
    new_node->num_Deps = 0;
    graph->Nodes[row][col] = new_node; //graph->Node stores the pointer to the node for access 
    //Dynamically allocated memory is pased to the Grpah and is the Graph's resposiblity to clear before termiating the Program

    graph->num_nodes++;
}

int add_dependency(struct Node* Source, struct Node* Dependent){
    
    for (size_t i = 0; i < Source->num_Deps; i++){ //Check if the depedency exists
        if(Source->dep[i] == Dependent)
            return 1;
    }

    Source->dep[Source->num_Deps++] = Dependent;

    if(has_circular_dependency(Source,Source)){ //If it is Circularly dependent remove dependency
        Source->dep[--Source->num_Deps] = NULL;
        return 0;
    }
    return 1;
}

int add_dependency_to_range(int s_row, int s_col, int f_row, int f_col, ROW dep_row,COL dep_col){
    for (size_t i = s_row ; i <= f_row; i++){
        for (size_t j = s_col; j <= f_col; j++){
            add_node(&DependencyGraph,i,j);
            if(!add_dependency(DependencyGraph.Nodes[i][j],DependencyGraph.Nodes[dep_row][dep_col])){
                return error(dep_row,dep_col,"ERROR");
            }
        }
    }
    return 1;
}

int has_circular_dependency(struct Node* Source, struct Node* ref){ 
    int check = 0;
    if(Source->num_Deps == 0) 
        return 0;
    for (size_t i = 0; i < Source->num_Deps; i++)
    {
        check += (int)(Source->dep[i] == ref); //Is any dep = ref 
        if(check != 0) return check;
        check += has_circular_dependency(Source->dep[i],ref); //Check each sub tree with same refrence
        if(check != 0) return check;
        check += has_circular_dependency(Source->dep[i],Source->dep[i]);//check each sub tree with the sub tree root as refrence
        if(check != 0) return check; 
    }
    return check; //0 if not dep
}

void update_dependency(struct Node* source){
    //updates the deepest node first
    if(source->num_Deps != 0){ //For every non leaf node
        for (size_t i = 0; i < source->num_Deps; i++) { //Check dependecies of subtree
            update_dependency(source->dep[i]); 
        }
    }
        
    spreadsheet[source->row][source->col].Data = comp_formula(source->row,source->col); //Re calculate the formula
    update_cell_display(source->row,source->col,get_display_value(source->row,source->col)); //Update the display
}

void set_cell_value(ROW row, COL col, char *text) {
    double value = 0;
    char* endPtr = NULL;
    
    clear_cell(row,col);        

    if(text[0] == '='){
        spreadsheet[row][col].Type = Formula;
        spreadsheet[row][col].Text = strdup(text);
        spreadsheet[row][col].Data = comp_formula(row,col);
    }else{
        value = strtod(text,&endPtr); //strtod converts the string to a Double value with the first numbers and an EndPtr of everything after

        if(*endPtr == '\0'){ //if endPtr = NULL then the string is only digits
            spreadsheet[row][col].Type = Data;
            spreadsheet[row][col].Data = value;
        }else{
            spreadsheet[row][col].Type = Text;
            spreadsheet[row][col].Text = strdup(text);
        }
    }    

    if (DependencyGraph.Nodes[row][col] != NULL) //If node has dependencies, update the dependencies
        update_dependency(DependencyGraph.Nodes[row][col]);
    update_cell_display(row,col,get_display_value(row,col));
}

void clear_cell(ROW row, COL col) {
    free(spreadsheet[row][col].Text); //Frees any memory allocated for this cell before clearing it 
    spreadsheet[row][col].Type = Blank;
    spreadsheet[row][col].Text = NULL;
    spreadsheet[row][col].Data = 0;   

    update_cell_display(row, col,get_display_value(row,col));
}

char *get_display_value(ROW row, COL col) {
    char *value = strdup(" "); //default blank
    switch (spreadsheet[row][col].Type){
    case Text:
        value = strdup(spreadsheet[row][col].Text);
        break;
    case Data:
        value = malloc(sizeof(char)*24); //24 chars to store the max size of double in scientific notation
        snprintf(value, sizeof(char)*24, "%g", spreadsheet[row][col].Data); //snprintf prevents buffer overflow errors
        break;
    case Formula: //formula shows number in display
        value = malloc(sizeof(char)*24);
        snprintf(value, sizeof(char)*24, "%g", spreadsheet[row][col].Data);
        break;
    }        
    return value;
}

char *get_textual_value(ROW row, COL col) {
    char *value = strdup(" "); //defualt blank
    switch (spreadsheet[row][col].Type){
    case Text:
        value = strdup(spreadsheet[row][col].Text);
        break;
    case Data:
        value = malloc(sizeof(char)*24); //24 chars to store the max size of double in scientific notation
        snprintf(value, sizeof(char)*24, "%g", spreadsheet[row][col].Data);
        break;
    case Formula: //formual shows text in edit
        value = strdup(spreadsheet[row][col].Text);
        break;
    }        
    return value;
}

double comp_formula(ROW row,COL col){
    if (spreadsheet[row][col].Type != Formula) {
        return spreadsheet[row][col].Data; 
    }
    char* formula = NULL;
    char* token = NULL;
    char* endPtr = NULL;
    double value = 0.0;
    int cell_row = -1 , cell_col = -1;
    int start_row= -1, start_col= -1, end_row= -1, end_col= -1;

    formula = strdup(spreadsheet[row][col].Text); //Formula is allocated dynamic memory here, Must be freed later

    add_node(&DependencyGraph,row,col); //adds node for dependency graph

    //SUM,AVG,MIN,MAX functions
    //  
    //all fucntions follow the same form
    if(starts_with(formula + 1,"SUM[")){ 

        if(!get_range(formula + 5,&start_row,&start_col,&end_row,&end_col)) return 0.0; //convert range to indicies

        if(add_dependency_to_range(start_col,start_col,end_row,end_col,row,col)){ //Add dependencies, if successful evaluate function
           value = sum_of_range(start_col,start_col,end_row,end_col); 
        }else return 0.0;
        

    }else if(starts_with(formula + 1,"AVG[")){
        
        if(!get_range(formula + 5 ,&start_row,&start_col,&end_row,&end_col)) return 0.0;

        if(add_dependency_to_range(start_col,start_col,end_row,end_col,row,col)){
           value = avg_of_range(start_col,start_col,end_row,end_col); 
        }else return 0.0;

    }else if(starts_with(formula + 1,"MIN[")){

        if(!get_range(formula + 5,&start_row,&start_col,&end_row,&end_col)) return 0.0;

        if(add_dependency_to_range(start_col,start_col,end_row,end_col,row,col)){
           value = min_of_range(start_col,start_col,end_row,end_col); 
        }else return 0.0;

    }else if(starts_with(formula + 1,"MAX[")){
    
        if(!get_range(formula + 5,&start_row,&start_col,&end_row,&end_col)) return 0.0;

        if(add_dependency_to_range(start_col,start_col,end_row,end_col,row,col)){
           value = max_of_range(start_col,start_col,end_row,end_col); 
        }else return 0.0;

    //Addition fucntion    
    }else{
        token = strtok(formula + 1, "+"); //strtok splits the formula into tokens seperated by +
        while(token != NULL){ //while not at the end of the formula
            if(coord_to_indicie(token,&cell_row,&cell_col)){
                if(spreadsheet[cell_row][cell_col].Type == Data || spreadsheet[cell_row][cell_col].Type == Formula){
                    value += spreadsheet[cell_row][cell_col].Data;
                    add_node(&DependencyGraph,cell_row,cell_col);
                    if(!add_dependency(DependencyGraph.Nodes[cell_row][cell_col],DependencyGraph.Nodes[row][col])){
                        return error(row,col,"ERROR");
                    }
                }else{
                    return error(row,col,"ERROR");
                }
            }else if ((int)isdigit(*token)){ //if token is a number
                value += strtod(token,&endPtr); //add to value
            }else //otherwise its an error
                return error(row,col,"ERROR");
            token = strtok(NULL, "+");//update token
        }
    }
    free(formula); //Dynamicly allocated memory is freed

    return value;
}

int coord_to_indicie(char* coordinate, int* row, int* col){
    if( !isalpha(coordinate[0]) || !isdigit(coordinate[1]) ) //first index has to be a letter , second index is a number
        return 0;
    *col = coordinate[0] - 'A'; //converts from letter to digit with A = 0 ...
    *row = atoi(&coordinate[1]) - 1; //convert from textual to int with 1 = 0 ...
    return 1;
}

int get_range(char* formula,int* s_row, int* s_col,int* f_row, int* f_col ){
    
    if(!coord_to_indicie(formula,s_row,s_col)){ //Convert first Coordinate
        return 0;
    };
    
    if(*(formula+2)  != ':'){ //check for ':' in between
        return 0;
    };
    
    if(!coord_to_indicie(formula+3,f_row,f_col)){ //Convert second coordinate
        return 0;
    }

    return 1;   
}

double sum_of_range(int s_row, int s_col, int f_row, int f_col){
    double value = 0;
    for (size_t i = s_row; i <= f_row; i++){
        for (size_t j = s_col ; j <= f_col; j++){
            value += spreadsheet[i][j].Data; //Sum
        }
    }
    return value;
}

double avg_of_range(int s_row, int s_col, int f_row, int f_col){
    double value = 0;
    int count = 0;
    for (size_t i = s_row; i <= f_row; i++){
        for (size_t j = s_col; j <= f_col; j++){
            value += spreadsheet[i][j].Data; //Sum
            count++; //Num of values
        }
    }
    value /= count; //Sum/Num of value = Avg
    return value;
}

double min_of_range(int s_row, int s_col, int f_row, int f_col){
    double value = spreadsheet[s_row][s_col].Data;
    for (size_t i = s_row; i <= f_row; i++){
        for (size_t j = s_col; j <= f_col; j++){
            if(spreadsheet[i][j].Data < value) //min
                value = spreadsheet[i][j].Data;
        }
    }
    return value;
}

double max_of_range(int s_row, int s_col, int f_row, int f_col){
    double value = spreadsheet[s_row][s_col].Data;
    for (size_t i = s_row; i <= f_row; i++){
        for (size_t j = s_col; j <= f_col; j++){
            if(spreadsheet[i][j].Data > value) //max
                value = spreadsheet[i][j].Data;
        }
    }
    return value;
}

int starts_with(const char *str, const char *prefix) {
    return *prefix == '\0' || *str == *prefix && starts_with(str + 1, prefix + 1);
}

int error(ROW row,COL col,char* err){
    spreadsheet[row][col].Type = Text;
    spreadsheet[row][col].Text = strdup(err);
    
    return 0;
}
