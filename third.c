#include <stdio.h>
#include <stdlib.h>

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

int solveSudoku(int matrix[9][9]){
  int i,j,k;

  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      if(matrix[i][j] == 0){
        for(k=1; k<10; k++){
          if(sanityChecker(matrix, k, i, j) == 1){
            matrix[i][j] = k;
            if(solveSudoku(matrix) == 1){
              return 1;//1 means SUCCESS
            }else{
              matrix[i][j] = 0;//reset to 0 to say that it didn't work
            }
          }//sanity checker
        }//close k loop from 1 to 9
        return 0;
      }//if(matrix[i][j] == 0) ends
    }//close j loop
  }//close i loop
  return 1;

}

void printMatrix(int matrix[9][9]){
  int i,j;

  for(i=0; i<9; i++){
    if(i%3 == 0){
      printf("================================\n");
    }
    for(j=0; j<9; j++){
      if(j == 3 || j == 6){
        printf("|  ");
      }
      if(j == 8){
        printf("%d\n", matrix[i][j]);
      }else{
      printf("%d  ", matrix[i][j]);
      }
    }
  }
  printf("================================\n\n");
  return;
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

int main(int argc, char** argv){
  FILE* fp;
  char c;
  int num;
  int i,j;

  if(argc != 2){
    printf("Not enough arguments!\n");
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
  //lets replace all -'s with a 0
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      if((grid[i][j]>=10) && (grid[i][j]<= 0)){
        grid[i][j] = 0;
      }
    }
  }

  printMatrix(grid);

  return 0;
}
