#include <stdio.h>
#include <stdlib.h>

/*GAME PLAN TO FINISH THIS

  Let’s use for loop to pick numbers from 1 to 9
  then establish counter and see how many possible values are able to be inputted
	 if counter == 1, then just place that one value in the spot
	 if not, continue to next 0 and do the same with a reset counter
*/

int sanityChecker(int matrix[9][9], int digit, int row, int column){//Will return 0 for FAIL and 1 for SUCCESS
  int i,j;
  int rowlow=0;
  int rowtop=0;
  int columnlow=0;
  int columntop=0;
  //we will check if the number is in the row, column, and in the 3x3 grid

  //First lets check ROW
  for(i=0; i<9; i++){
    if(matrix[row][i] == digit){
      return 0;
    }
  }
  //Next lets check COLUMN
  for(i=0; i<9; i++){
    if(matrix[i][column] == digit){
      return 0;
    }
  }
  //Now we need to check the box that it is in
  if(row<3){
    rowlow = 0;
    rowtop = 3;
  }else if(row<6){
    rowlow = 3;
    rowtop = 6;
  }else{
    rowlow = 6;
    rowtop = 9;
  }
  if(column < 3){
    columnlow = 0;
    columntop = 3;
  }else if(column < 6){
    columnlow = 3;
    columntop = 6;
  }else{
    columnlow = 6;
    columntop = 9;
  }
  for(i=rowlow; i<rowtop; i++){
    for(j=columnlow; j<columntop; j++){
      if(matrix[i][j] == digit){
        return 0;
      }
    }
  }
  return 1;
}

int charToInt(char c){
  if(c == '1'){
    return 1;
  }
  if(c == '2'){
    return 2;
  }
  if(c == '3'){
    return 3;
  }
  if(c == '4'){
    return 4;
  }
  if(c == '5'){
    return 5;
  }
  if(c == '6'){
    return 6;
  }
  if(c == '7'){
    return 7;
  }
  if(c == '8'){
    return 8;
  }
  if(c == '9'){
    return 9;
  }
  return 0;
}

void printMatrix(int matrix[9][9]){
  int i,j;

  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      if(j == 8){
        printf("%d\n", matrix[i][j]);
      }else{
        printf("%d\t", matrix[i][j]);
      }
    }
  }
  return;
}

int isDone(int matrix[9][9]){//will return 0 for FAIL and 1 for SUCCESS
  int i,j;

  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      if(matrix[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

int solveSudoku(int matrix[9][9]){//will return 0 for FAIL and 1 for SUCCESS
  int i,j,k;
  int counter;
  int num;
  int canWork = 1;

  while(isDone(matrix) == 0){
    canWork = 0;
    for(i=0; i<9; i++){
      for(j=0; j<9; j++){
        if(matrix[i][j] == 0){
          counter = 0;
          for(k=1; k<10; k++){
            if(sanityChecker(matrix, k, i, j) == 1){
              counter++;
              num = k;
            }
          }
	  if(counter == 1){
	    matrix[i][j] = num;
	    if(canWork == 0){
	      canWork = 1;
	    }
	  }else if(counter == 0){
	    //bad-matrix
	    return 0;
	  }
        }
      }
    }
    if(canWork == 0){
	//bad-matrix
	return 0;
    }
  }
  return 1;
}

int main(int argc, char** argv){
  FILE* fp;
  char c;
  int num;
  int i,j;

  if(argc != 2){
    printf("error\n");
    exit(0);
  }


  fp = fopen(argv[1], "r");

  //we need to create a matrix to store in the inputs
  int grid[9][9];
  //lets read the inputs and store in grid
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){

      if(j == 8){
        fscanf(fp, "%c\n", &c);
        num = charToInt(c);
        grid[i][j] = num;
      }else{
        fscanf(fp, "%c\t", &c);
        num = charToInt(c);
        grid[i][j] = num;
      }
    }
  }
  //now we need to go to the next available spot and run the sanityChecker to check
  //if we can add a number, add and continue
  //if not, return bad-matrix
  if(solveSudoku(grid) == 1){
    printMatrix(grid);
  }else{
    printf("no-solution\n");
    return 0;
  }

  return 0;
}
