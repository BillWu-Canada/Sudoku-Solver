#include <iostream>
#include <string>
#include <vector>

using namespace std;


class cell {
  
  public:
  int input;          // the number filled in the cell, 0 if the cell is blank
  int num_of_choice;  // the total number of choice that the cell has
  bool fixed;         // indicate whether it is solved or not

  vector<int> available_choice;    // vector to store the possible choice
  

  cell() {
    fixed = true;
  }

};


cell puzzle[9][9];

int step_count = 0;

//---------------------------------------------------------------------


void print_puzzle() {
   for (int i=0; i<9; i++) {
     for (int j=0; j<9; j++) {
        cout << puzzle[i][j].input << " ";

     }

     cout << endl;


   }

}



// check the constraints of a paticular cell

void check_add_constrain(cell &grid, int x, int y) {
   vector<int> candidnates;

   for (int i=0; i<=9; i++) {
       candidnates.push_back(i);  
   }

   // check on the row
   for (int j=0; j<9; j++) {
      int pop_var = puzzle[x][j].input;
      candidnates.at(pop_var) = 0;
   }
   
   // check on the col
   for (int i=0; i<9; i++) {
      int pop_var = puzzle[i][y].input;
      candidnates.at(pop_var) = 0;
   }

   int row_low;
   int row_high;
   int col_low;
   int col_high;

   if (0<=x and x<=2) {
     row_low = 0;
     row_high = 2;
   }   

   if (3<=x and x<=5) {
      row_low = 3;
      row_high = 5;
   }

   if (6<=x and x<=8) {
      row_low = 6;
      row_high = 8;
   }

   if (0<=y and y<=2) {
     col_low = 0;
     col_high = 2;
   }

   if (3<=y and y<=5) {
     col_low = 3;
     col_high = 5;
   }

   if (6<=y and y<=8) {
     col_low = 6;
     col_high = 8;
   }

   
  // check the box that the cell belongs
   for (int i=row_low; i<=row_high; i++) {
     for (int j=col_low; j<=col_high; j++) {
       int pop_var = puzzle[i][j].input;
       candidnates.at(pop_var) = 0;
         
     }

   }


   // update the avaliable of choice and num_of_choice for the cell

   // erease the old vector
    grid.available_choice.clear();
    grid.num_of_choice = 0;

   // push the acceptable candidnates and update the num_of_choice
    for(int k=0; k<candidnates.size(); k++) {
        int num = candidnates.at(k);
       if (num != 0) {
         grid.available_choice.push_back(num);
         grid.num_of_choice++;
       }
    
    }

} 



// check the constraint for all empty cells
void scan_constrain_for_all() {
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (puzzle[i][j].fixed == false) {
        check_add_constrain(puzzle[i][j], i, j);
      }  
    }
  }

}


// find the empty cell
bool find_empty_cell(cell puzzle[9][9], int &row, int &col) {
   for (row = 0; row < 9; row++) {
      for (col = 0; col < 9; col++) {
          if (puzzle[row][col].input == 0) {
             return true;
          }
      }
   }

   return false;
}



// check whether the num can pass the constraints check test
bool safety_check(cell puzzle[9][9], int row, int col, int num) {
    bool row_checker = true;
    bool col_checker = true;
    bool box_checker = true;

    for (int my_col = 0; my_col < 9; my_col++) {
       if (puzzle[row][my_col].input == num) {
           col_checker = false;
       }
    }

    for (int my_row = 0; my_row < 9; my_row++) {
       if (puzzle[my_row][col].input == num) {
          row_checker = false;
       }
    }

   int row_low;
   int row_high;
   int col_low;
   int col_high;

   if (0<=row and row<=2) {
     row_low = 0;
     row_high = 2;
   }   

   if (3<=row and row<=5) {
      row_low = 3;
      row_high = 5;
   }

   if (6<=row and row<=8) {
      row_low = 6;
      row_high = 8;
   }

   if (0<=col and col<=2) {
     col_low = 0;
     col_high = 2;
   }

   if (3<=col and col<=5) {
     col_low = 3;
     col_high = 5;
   }

   if (6<=col and col<=8) {
     col_low = 6;
     col_high = 8;
   }

  for (int i=row_low; i<=row_high; i++) {
     for (int j=col_low; j<=col_high; j++) {
        if (puzzle[i][j].input == num) {
           box_checker = false;
        }
         
     }

   }

   return (row_checker && col_checker && box_checker);
   
}


// main function of sudoku solver
bool solver(cell puzzle[9][9]) {
   int row;
   int col;

  if (find_empty_cell(puzzle, row, col) == false) {
      return true;
  }

  for (int i = 0; i<puzzle[row][col].num_of_choice; i++) {
     
     if (safety_check(puzzle, row, col, puzzle[row][col].available_choice.at(i))) {
  
       puzzle[row][col].input = puzzle[row][col].available_choice.at(i);
       step_count++;
   
       if ( solver(puzzle) ) {
          return true;
       }

       puzzle[row][col].input = 0;
      
     }

  }

 return false;

}





int main() {
  
  int num;
  int row = 0;
  int col = 0;


  // handle the inputs
  while (cin >> num) {
    
    puzzle[row][col].input = num;

    if (num == 0) {
       puzzle[row][col].fixed = false;  
    }

    if (col == 8) {
      col = 0;
      row++;
    }
    else {
      col++;
    }

  }

// end of inputs


cout << endl;
cout << "original is: " << endl;
print_puzzle();


// start solving puzzle 
scan_constrain_for_all();
solver(puzzle);
// finish solving

cout << endl;
cout << endl;

cout << "solution is: " << endl;
print_puzzle();

cout << endl;
cout << "step count is: " << step_count << endl;
cout << endl;

}






