#include<stdio.h>
#include<stdlib.h>



//função para visualizar tabela
void preview(double **matrix, int nrows, int ncols) {
	for(int i = 0; i < nrows; i++){
		for(int j = 0; j < ncols; j++) {
			//printf("[%d][%d]%.2f\t", i, j, matrix[i][j]);
			printf("%.2f\t", matrix[i][j]);
		}
		printf("\n");
	}
}

//função para gerar tabela vazia
double **table(int nrows, int ncols) {
	
	double **matrix = malloc(nrows * sizeof(double *));
	for(int i = 0; i < nrows; i++){
		matrix[i] = malloc(ncols * sizeof(double));
	}
	
	return matrix;
}


//função para inicializar tabela
void initializer(double **matrix, int ncols) {
	double z[] = {1, -5, -4, 0, 0, 0, 0, 0};
	double s1[] = {0, 6, 4, 1, 0, 0, 0, 24};
	double s2[] = {0, 1, 2, 0, 1, 0, 0, 6};
	double s3[] = {0, -1, 1, 0, 0, 1, 0, 1};
	double s4[] = {0, 0, 1, 0, 0, 0, 1, 2};
	
	for(int i = 0; i < ncols; i++) {
		matrix[0][i] = z[i];
		matrix[1][i] = s1[i];
		matrix[2][i] = s2[i];
		matrix[3][i] = s3[i];
		matrix[4][i] = s4[i];
	}
}

//função para verificar se matrix esta otimizada
int isOptimized(double **matrix, int ncols) {
	for(int i = 0; i < ncols; i++) {
		if(matrix[0][i] < 0)
			return 0;
		
	}
	return 1;
}

//função para encontrar coluna pivo
int getPivoCol(double **matrix, int ncols) {
	double min_col = matrix[0][0];
	int pivo = 0;
	
	for(int i = 1; i < ncols; i++) {
		if(matrix[0][i] < min_col) {
			min_col = matrix[0][i];
			pivo = i;
		}
	}
	return pivo; 
}

//função para encontrar linha pivo
int getPivoRow (double **matrix, int nrows, int ncols, int pivoCol) {

	double min_row = matrix[1][ncols - 1] / matrix[1][pivoCol];
	int pivo = 1;
	double result = 0;
	
	for(int i = 2; i < nrows; i++) {
		result = matrix[i][ncols - 1] / matrix[i][pivoCol];
		if(result < min_row && result > 0) {
			min_row = result;
			pivo = i;
		}
	}
	return pivo; 
}

void calculate(double **matrix, int pivoRow, int pivoCol, int nrows, int ncols) {
	
	
	double pivoElement = matrix[pivoRow][pivoCol];
	double colElement = 0 ;
	
	for(int i = 0; i < ncols; i++) {
		matrix[pivoRow][i] = matrix[pivoRow][i] / pivoElement;
	}
	for(int i = 0; i < nrows; i++) {
		if (i == pivoRow) continue;
		colElement = -1 * matrix[i][pivoCol];
		for(int j = 0; j < ncols; j++) {
			matrix[i][j] = matrix[i][j] + (matrix[pivoRow][j] * colElement);
		}	
	}
}

int main() {
		 
	//matrix A de coeficiente
	/*
	 *   z x1 x2 s1 s2 s3 s4 b
	 * 	z
	 * s1
	 * s2
	 * s3
	 * s4
	 * */
	 
	int nrows = 5, ncols = 8, step = 0;
	int pivoRow, pivoCol;
	double **matrix = table(nrows, ncols);

	initializer(matrix, ncols);
	
	printf("step: %d\n", step);
	preview(matrix, nrows, ncols);
	
	while(isOptimized(matrix, ncols) == 0) {
		step += 1;
		
		printf("\n\n");
		printf("step: %d\n", step);
		pivoCol = getPivoCol(matrix, ncols);
		pivoRow = getPivoRow(matrix, nrows, ncols, pivoCol);
		
		calculate(matrix, pivoRow, pivoCol, nrows, ncols);
		
		preview(matrix, nrows, ncols);	
	}
	
	printf("\n\nBest Value of Optimization: z = %.2f", matrix[0][ncols -1]);
	return 0;
}
