#include<stdio.h>
#include<stdlib.h>


int fase = 1;
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
	
	double w[] = {-1, -4, 0, 1, 0, 	0, -14};
	double a1[] = {2, 3, 0, -1, 1, 0, 13};
	double a2[] = {-1, 1, 0, 0, 0, 1, 1};
	double f1[] = {4, 1, 1, 0, 0, 0, 21};
	double z[] = {-6, 1, 0, 0, 0, 0, 0};
	
	/*
	double w[] = {0, 0, 0, -1, -1, 	0, 0};
	double a1[] = {3, 1, 0, 1, 0, 0, 3};
	double a2[] = {4, 3, -1, 0, 0, 1, 1};
	double f1[] = {4, 1, 1, 0, 0, 0, 21};
	*/
	for(int i = 0; i < ncols; i++) {
		matrix[0][i] = w[i];
		matrix[1][i] = f1[i];
		matrix[2][i] = a1[i];
		matrix[3][i] = a2[i];
		matrix[4][i] = z[i];
	}
}

void reinit(double **matrix, double **newMatrix, int nrows, int ncols) {
	int new_ncols = ncols - 2;
	int new_nrows = nrows - 1;
	
	for(int col = 0; col < new_ncols; col++) {
		if(col == new_ncols - 1) newMatrix[0][col] = matrix[nrows - 1][ncols -1];
		else newMatrix[0][col] = matrix[nrows - 1][col];
	}
	
	for(int row = 1; row < new_nrows; row++) {
		for(int col = 0; col < new_ncols; col++) {
			if(col == new_ncols - 1) newMatrix[row][col] = matrix[row][ncols -1];
			else newMatrix[row][col] = matrix[row][col];
		}
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
	
	for(int i = 1; i < ncols -1; i++) {
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
	
	for(int i = 1; i < nrows; i++) {
		result = matrix[i][ncols - 1] / matrix[i][pivoCol];
		if(i == nrows - 1 && fase == 1) continue;
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
		 
	int nrows = 5, ncols = 7, step = 0;
	int pivoRow, pivoCol;
	double **matrix = table(nrows, ncols);
	double **newMatrix;

	initializer(matrix, ncols);
	

	printf("primeira fase: \n");
	printf("step: %d \n", step);
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
	
	
	
	printf("\n\nSegunda fase: \n");
	step = 0;
	fase = 2;
	printf("step: %d \n", step); 
	newMatrix = table(nrows -1, ncols - 2);
	reinit(matrix, newMatrix, nrows, ncols);
	
	preview(newMatrix, nrows - 1, ncols -2);
	
	
	while(isOptimized(newMatrix, ncols) == 0) {
		
		step += 1;
		
		printf("\n\n");
		printf("step: %d\n", step);
		pivoCol = getPivoCol(newMatrix, ncols -2);
		pivoRow = getPivoRow(newMatrix, nrows - 1, ncols - 2, pivoCol);
		
		calculate(newMatrix, pivoRow, pivoCol, nrows - 1, ncols -2);
		preview(newMatrix, nrows -1, ncols -2);	
	}
	
	
	printf("\n\nBest Value of Optimization: z = %.2f", newMatrix[0][ncols -3]);

	free(matrix);
	free(newMatrix);
	return 0;
}
