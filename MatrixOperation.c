// TASK 2: Medium - Matrix Operations
// Write a program to implement:
// Matrix Addition
// Matrix Multiplication
// Transpose
// Use functions and 2D arrays for better modularity.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


//Assuming the matrix size are equal so, no check for it is there


float **createMatrix(int row,int col)
{
	float **Matrix;
	Matrix = (float **)malloc(row * sizeof(float *));
	
	for(int i=0; i<row; i++){
		
		Matrix[i] = (float *)malloc(col * sizeof(float));	
	}
	
	return Matrix;
}

void inputMatrix(float **matrix,int rows,int cols)
{
	printf("\n");
	printf("Enter the element of matrix row wise ");
	printf("\n");
	printf("\n");
	
	for(int i=0 ; i<rows ; i++){
		
		printf("%d  ", i+1);
		
		for(int j=0 ; j<cols ; j++){
			
			scanf("%f",&matrix[i][j]);
		}
	}
}

void displayMatrix(float **matrix, int rows, int cols)
{
    printf("\n");

    for (int i = 0; i < rows; i++){
        
		for (int j = 0; j < cols; j++){
            
			printf("%.2f    ", matrix[i][j]);
        }
        
	printf("\n");
    }
}



void additionMatrix(float **X , float **Y,float **Z,int rows, int cols)
{
	for(int i=0 ; i<rows ; i++){
		
		for(int j=0 ; j<cols ; j++ ){
			
			Z[i][j] = X[i][j] + Y[i][j] ;
		}
	}
	displayMatrix( Z, rows, cols);
} 

void multiplyMatrix(float **X, float **Y, float **Z,int rows,int cols)
{
	for(int i=0 ; i<rows ; i++){
		
		for(int j=0 ; j<cols ; j++){
			
			Z[i][j] = 0;
			
			for(int k=0 ;k<cols ; k++ ){
				
				Z[i][j] += X[i][k] * Y[k][j];
			}
		}
	}
	displayMatrix( Z, rows, cols);
}

void transposeMatrix (float **A, float **T, int rows, int cols)
{
	for(int i=0; i<rows; i++){
		
		for(int j=0; j<cols; j++){
			
			T[j][i] = A[i][j]; 
		}
	}
	displayMatrix( T, rows, cols);
}


void freeMatrix(float **matrix, int rows)
{
    for (int i = 0; i < rows; i++){
        
		free(matrix[i]);
    }

    free(matrix);
}

int main(){
	
	int rows,cols;
	printf("Enter the row and column of matrix: ");
	scanf("%d %d",&rows,&cols);
	
	float **X = createMatrix(rows,cols);
	float **Y = createMatrix(rows,cols);
	
	printf("\n");
	printf("\n");
	printf("Enter element of Matrix X ");
	inputMatrix(X,rows,cols);
	
	printf("\n");
	printf("\n");
	printf("Enter element of Matrix Y ");
	inputMatrix(Y,rows,cols);
	
	int digit = 0;
	printf("\n To Perform any operation enter respective number: ");
	while (digit != 4)
	{
	printf("\n");
	printf("1. Addition \n");
	printf("2. Multiplication \n");
	printf("3. Transpose \n");
	printf("4. Exit \n");
	
	scanf("%d", &digit);
	
	switch(digit)
	{
		case 1:
		{
			float **sum = createMatrix(rows,cols);
			additionMatrix( X, Y, sum, rows, cols);
			freeMatrix(sum, rows);
			break;	
		}
		case 2:
		{
			float **product = createMatrix(rows,cols);
			multiplyMatrix( X, Y, product, rows, cols);	
			freeMatrix(product, rows);
			break;
		}
		case 3:
			{
			float **transpose = createMatrix(rows,cols);
			printf(" \n Which Matrix You Want To Transpose X or Y : ");
			char opt;
			scanf("%c",&opt);
			if(opt == 'X' || opt == 'x')
			{
    			transposeMatrix(X, transpose, rows, cols);
			}
			else if(opt == 'Y' || opt == 'y')
			{
    			transposeMatrix(Y, transpose, rows, cols);
			}
			else
			{
    			printf("Invalid Choice\n");
			} 
			
			freeMatrix(transpose, cols);
			break;
			}
		case 4:
			{
			printf("Exiting program ");
			break;
			}
		default:
			{
			printf("Invalid choice");	
			}
	}
}

freeMatrix(X, rows);
freeMatrix(Y, rows);

return 0;

}
