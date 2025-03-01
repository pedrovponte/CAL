/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve()
{
    int best_x, best_y;

    if(isComplete())
        return true;

    if(!choose_best(best_x, best_y))
        return false;

    for(int i = 1; i < 10; i++){
        if(!columnHasNumber[best_y][i] && !lineHasNumber[best_x][i] && !block3x3HasNumber[best_x / 3][best_y / 3][i]){
            numbers[best_x][best_y] = i;
            lineHasNumber[best_x][i] = true;
            columnHasNumber[best_y][i] = true;
            block3x3HasNumber[best_x / 3][best_y / 3][i] = true;
            countFilled++;
            if(solve()) {
                return true;
            }
            else{
                numbers[best_x][best_y] = 0;
                lineHasNumber[best_x][i] = false;
                columnHasNumber[best_y][i] = false;
                block3x3HasNumber[best_x / 3][best_y / 3][i] = false;
                countFilled--;
            }
        }
    }
    return false;
}

bool Sudoku::choose_best(int &best_x, int &best_y){
    best_x = -1, best_y = -1;
    int best_poss = 10;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(numbers[i][j] == 0){
                int possibilities = 0;
                for(int p = 1; p < 10; p++){
                    if(accepts(i,j,p))
                        possibilities++;
                }
                if(possibilities == 0)
                    return false;

                if(possibilities < best_poss) {
                    best_poss = possibilities;
                    best_x = i;
                    best_y = j;
                    if(possibilities == 1)
                        return true;
                }
            }
        }
    }
    return best_x >= 0;
}

bool Sudoku::accepts(int i, int j, int n){
    return !lineHasNumber[i][n] && !columnHasNumber[j][n] && !block3x3HasNumber[i][j][n];
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
