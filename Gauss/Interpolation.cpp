#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

void Gauss_straight(vector<vector <double> > &matrix, vector<double> &b)//прямой ход, подается ссылка на матрицу и на столбец b
{
	int N = b.size();//сохраняем длину столбца(кол-во строк или столбцов матрицы)
	double mult = 0;
	for (int i = 0; i < N; i++)
	{
		mult = matrix[i][i];//запоминаем диагональный элемент, чтобы делить на него строку
		for (int j = i; j < N; j++)//цикл от i потому что все что слева от диагонального элемента уже 0
		{
			matrix[i][j] /= mult;//делим строку на mult чтобы диагональный элемент был 1
		}
		b[i] /= mult;//делим соответсвующий элемент столбца
		for (int j = i + 1; j < N; j++)
		{
			mult = matrix[j][i];//запоминаем элемент строки j(из которой вычитаем) на месте которого должен быть 0
			for (int h = 0; h < N; h++)
			{
				matrix[j][h] -= matrix[i][h] * mult;//вычитаем соответсвующий элемент строки i умноженный на множетель mult из строки j
			}
			b[j] -= b[i] * mult;//и в столбце b
		}
	}
}

void Gauss_reverse(vector<vector <double> > &matrix, vector<double> &b)//обратный ход
{
	//проходя матрицу справа снизу выполняем те же действия кроме установления 1 на диагонали(там и так 1-цы)
	int N = b.size();
	double mult = 0;
	for (int i = N - 1; i > 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			mult = matrix[j][i];//запоминаем элемент строки j(из которой вычитаем) на месте которого должен быть 0
			for (int h = 0; h < N; h++)
			{
				matrix[j][h] -= matrix[i][h] * mult;//вычитаем соответсвующий элемент строки i умноженный на множетель mult из строки j
			}
			b[j] -= b[i] * mult;//и в столбце b
		}
	}
}

void PrintMb(vector<vector<double> > matrix, vector<double> b)//просто печать матрицы и столбца
{
	int N = b.size();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << "| " << b[i] << endl;
	}
}

int main()
{
	int N;// N размер матрицы 
	double V, c;//V - верхний диагональный элемент, c для V*0.01
	cout << "Vvedite kolichestvo uzlov x_k: " << endl;
	cin >> N;

	vector<double> x_k(N);
	vector<double> F_k(N);
	int ind = -1, sw;
	cout << "Vvedite x_k: " << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> x_k[i];
		if ((x_k[i] == 0) && (i != N - 1))//ищем 0
		{
			ind = i;
		}
	}
	cout << "Vvedite F_k: " << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> F_k[i];
	}

	if (ind != -1)//если был ноль переставляем в конец и значение функции для него тоже
	{
		F_k[ind] += F_k[N - 1];
		F_k[N - 1] = F_k[ind] - F_k[N - 1];
		F_k[ind] -= F_k[N - 1];

		x_k[ind] += x_k[N - 1];
		x_k[N - 1] = x_k[ind] - x_k[N - 1];
		x_k[ind] -= x_k[N - 1];
	}
	
	vector<vector<double> > matrix(N);//матрица с N строк
	vector<double> b(N);//столбец

	//далее заполняем матрицу и столбец
	for (int i = 0; i < N; i++)
	{
		matrix[i].resize(N);//i-ой строке N элементов
		matrix[i][N - 1] = 1;
		for (int j = N - 2; j >= 0; j--)
		{
			matrix[i][j] = matrix[i][j + 1] * x_k[i];
		}
	}

	Gauss_straight(matrix, F_k);//вызываем прямой ход
	PrintMb(matrix, F_k);
	Gauss_reverse(matrix, F_k);//вызываем обратный ход
	
	for (int i = 0; i < N - 1; i++)
	{
		cout << F_k[i] << " * x^" << (N - i - 1) << " + ";
	}
	cout << F_k[N - 1];

	cin.get();//чтобы консоль не закрылась
	cin.get();//чтобы консоль не закрылась

	return (0);
}