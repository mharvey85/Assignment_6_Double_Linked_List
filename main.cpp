#include <stdio.h>
#include <iostream>
#include <string>
#include <random>
#include <math.h>
#include "coordinate.h"

void add_coordinate(Coordinate *list_end, float x, float y);
void forward_display(Coordinate *list_beginning);
void backward_display(Coordinate *list_end);
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete);
int list_length(Coordinate *list_beginning);
void closest_to(Coordinate *list_beginning, float x, float y);

int id_count = 0;

int main(int argc, char* argv[]){
    // checking if user input was given
    if (argc < 2){
        printf("Error: needs number of coordinates\n");
        return 1;
    }
    // setting user input to the number of coordinate pairs
    int num_pairs = atoi(argv[1]);

    // creating random numbers for number of pairs given
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> range(1, 100);
    
    // pointers for list
    Coordinate *head;
    Coordinate *tail;
    Coordinate *n;

    // start of list
    n = new Coordinate;
    n -> previous = NULL; 
    n -> x = range(gen);
    n -> y = range(gen);
    head = n;
    tail = n;
    n -> coord_id = 0;

    // creating rest of pointers
    for(int i = 0; i < num_pairs-1; i++){
        add_coordinate(tail, range(gen), range(gen));
        tail = tail->next;
    }
    tail -> next = NULL;    

    // calling functions

    std::cout << "\nforward display function: \n";
    forward_display(head);
    
    std::cout << "\nbackwards display function: \n";
    backward_display(tail); 
      
    int output = list_length(head);
    std::cout << "\nlist length: " << output << "\n\n";

    delete_coordinate(head, 3);
    std::cout << "\ndeleting 3rd coordinate\n";
    forward_display(head);

    std::cout << "\nclosest to function: \n";
    closest_to(head, 5, 7);

    return 0;
}

// adds a coordinate to the end of the linked list
void add_coordinate(Coordinate *list_end, float x, float y){
    Coordinate *n;
    n = new Coordinate; 

    id_count++;
    n -> coord_id = id_count;

    n -> x = x;
    n -> y = y;
    n -> previous = list_end;
    
    list_end -> next = n;
}

// displays all coordinates from the beginning to the end
void forward_display(Coordinate *list_beginning){
    Coordinate* temp = list_beginning;
    
    while (temp != NULL){
        std::cout << "x: " << temp -> x << "   y: " << temp -> y << "   "
        << "coord id: " << temp -> coord_id;

        std::cout << "\n";
        temp = temp -> next;
    }
    std::cout << "\n";

}

// displays all coordinates from end to beginning
void backward_display(Coordinate *list_end){
    Coordinate* temp = list_end;
    
    while (temp != NULL){
       std::cout << "x: " << temp -> x << "   y: " << temp -> y << "   "
        << "coord id: " << temp -> coord_id;

        std::cout << "\n";
        temp = temp -> previous;
    }
    std::cout << "\n";
}

// removes a coordinate from the linked list (frees memory)
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete){
    Coordinate* temp = list_beginning;
    Coordinate* n;
    Coordinate* p;
    
    while (temp != NULL){
        if(coord_id_to_delete == temp -> coord_id){
            n = temp -> next;
            p = temp -> previous;
            
            n->previous = p;
            p->next = n;

            delete temp;
        }
        temp = temp -> next;
    }

}

// returns the length of list
int list_length(Coordinate *list_beginning){
    Coordinate* temp = list_beginning;
    int count = 0;
    
    while (temp != NULL){
        count++;
        temp = temp -> next;
    }
    
    return count; 
}

//  find the coordinate that is closest to the given x, y and output the distance between the 2
void closest_to(Coordinate *list_beginning, float x, float y){
    Coordinate* temp = list_beginning;
    Coordinate* close;

    float min = 0;
    float dist;
    float x_abs;
    float y_abs;

    while (temp != NULL){
        x_abs = abs( (temp -> x) - x );
        y_abs = abs( (temp -> y) - y );

        dist = sqrt ( (x_abs * x_abs) + (y_abs * y_abs) );

        if (dist < min){
            min = dist;
            close = temp;
        }
    
        temp = temp -> next;
    }

    std::cout << "given coordinate\tx: " << x << " y: " << y << "\n";
    std::cout << "closest coordinate\tx: " <<  close -> x << " y: " << close -> y << "\n";
}