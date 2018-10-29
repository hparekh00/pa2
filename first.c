#include <stdio.h>
#include <stdlib.h>

void printMatrix(int rows, int columns, double matrix[rows][columns]){
  int i, j;
  for(i=0; i<rows; i++){
    for(j=0; j<columns; j++){
      printf("%lf\t", matrix[i][j]);
    }
    printf("\n");
  }
}

void multiply(int rows1, int columns1, int rows2,  int columns2, double matrix1[rows1][columns1], double matrix2[rows2][columns2], double output[rows1][columns2]){
  double result;
  int i,j,k,l;

  for(i = 0; i < rows1; i++){
    for(j=0; j<columns2; j++){
      result = 0.000000;
      for(k=0,l=0; k<columns1 && l<rows2; k++, l++){
        result = result + (matrix1[i][k] * matrix2[l][j]);
      }
      output[i][j] = result;
    }
  }
  return;
}

void inverse(int length, double matrix[length][length], double final[length][length]){
    int i,j,k;
    double divider;
    double coefficient;

for(i=0; i<length; i++){
  for(j=0; j<length; j++){
    if(i==j){
      final[i][j] = 1.0;
    }else{
      final[i][j] = 0.0;
    }
  }
}

//matrix is now ready for inversing
    for(i=0; i<length; i++){//this will be for the column traversing
      //lets divide row to create 1 in designated spot
      divider = matrix[i][i];
      //divide all columns in the row by divider
      for(j=0; j<length; j++){
        matrix[i][j] = matrix[i][j]/divider;
	      final[i][j] = final[i][j]/divider;
      }
      
      for(j=0; j<length; j++){//this will be to traverse the rows
        if(j != i){
          //we need to now get 0's in place
          coefficient = matrix[j][i];
          for(k=0; k<length; k++){//traverse through columns staying in row j
            matrix[j][k] = matrix[j][k] - coefficient*matrix[i][k];//will result in 0 in our designated column
	          final[j][k] = final[j][k] - coefficient*final[i][k];
          }
        }
      }
    }
}

int main(int argc, char** argv){
  if(argc != 3){
    printf("ERROR -- Not enough arguments\n");
    exit(0);
  }
  int attributes = 0;
  int examples = 0;
  FILE* fp;
  int i;
  int j;
  double temp;

  int num;


  fp = fopen(argv[1], "r");
  fscanf(fp, "%d\n", &attributes);
  fscanf(fp, "%d\n", &examples);

  //We can now initialize the 2 arrays, X and Y
  //Arrays are initiated ROWxCOLUMN
  double X[examples][attributes+1];
  double Y[examples][1];

  //lets give the X matrix a column of 1's
  for(i=0; i<examples; i++){
    X[i][0] = 1;
  }

  for(i=0; i<examples; i++){
    for(j=1; j<attributes+2; j++){
      if(j == attributes+1){
        fscanf(fp, "%lf\n", &temp);
        //store the value in designated array
        Y[i][0] = temp;
      }else{
          fscanf(fp, "%lf,", &temp);
          //store the value in designated array
          X[i][j] = temp;
      }
    }
  }
  fclose(fp);//close the training data file
//==============================================================
//We have now inputted training data into matrix X and Y

//Let's now TRANSPOSE Matrix X
  double XT[attributes+1][examples];//define Transposed Matrix
//Fill in values of Transposed Matrix
  for(i=0; i<examples; i++){
    for(j=0; j<attributes+1; j++){
      XT[j][i] = X[i][j];
    }
  }

//We now have X, Y and XT matrices

//We need to now multiply XT and X
//Let's store it in new matrix Product
  double product[attributes+1][attributes+1];//now declared product matrix XT times X

  multiply(attributes+1, examples, examples, attributes+1, XT, X, product);
//we now have product matrix

//We must now take the Inverse of product

  double part1[attributes+1][attributes+1];//to store inverse array
  for(i=0; i<attributes+1; i++){
    for(j=0; j<attributes+1; j++){
      part1[i][j] = 0;
    }
  }
  inverse(attributes+1, product, part1);

  double part2[attributes+1][examples];
  multiply(attributes+1, attributes+1, attributes+1, examples, part1, XT, part2);

  double weights[attributes+1][1];
  multiply(attributes+1, examples, examples, 1, part2, Y, weights);

fp = fopen(argv[2], "r");
fscanf(fp, "%d\n", &num);
double test[num][attributes+1];

//we need to initialize first column to 1
for(i=0; i<num; i++){
  test[i][0] = 1;
}


for(i=0; i<num; i++){
  for(j=1; j<attributes+1; j++){
    if(j == attributes+1){
      fscanf(fp, "%lf\n", &temp);
      test[i][j] = temp;
    }else{
      fscanf(fp, "%lf,", &temp);
      test[i][j] = temp;
    }
  }
}
//now we have loaded the test input matrix
//now we only need to multiply test with weights to get final matrix to output

  double final[num][1];

  multiply(num, attributes+1, attributes+1, 1, test, weights, final);


  for(i=0; i<num; i++){
    printf("%0.0lf\n", final[i][0]);
  }
  printf("\n");

  return 0;
}
