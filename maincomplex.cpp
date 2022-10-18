#include <iostream>
#include <string>
using namespace std;

// Реализация класса комплексных чисел
class Complex
{
private:
	double re;
	double im;

	double SqrAbs() { return this->re * this->re + this->im * this->im; }

public:
	// конструктор по умолчанию и с параметрами
	Complex(double re = 0, double im = 0) :re(re), im(im) {}
	// конструктор копирования
	Complex(const Complex& complex) :re(complex.re), im(complex.im) {}
	// деструктор
	~Complex() { this->re = 0; this->im = 0; }



	// ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ
	
	// модуль числа
	double Abs() { return sqrt(this->SqrAbs()); }
	// аргумент числа
	double Arg() { return atan2(this->im, this->re); }
	// нахождение обратного
	Complex Reverse()
	{
		Complex complex(this->im, this->re);
		double a = this->re * this->re + this->im * this->im;
		if (a > 0) {
			complex.re = this->re / a;
			complex.im = -this->im / a;
		}
		return complex;
	}
	// преобразование числа в строку
	string ToString()
	{
		if (this->im == 0) return to_string(this->re);
		if (this->re == 0) return to_string(this->im) + "i";

		// вывод комплексного числа с положительной мнимой частью
		if (this->im >= 0)
		{
			if (this->im == 1) return to_string(this->re) + "+i";
			if (this->re == 1) return to_string(this->im) + "i";
			return to_string(this->re) + "+" + to_string(this->im) + "i";
		}
		// вывод комплексного числа с отрицательной мнимой частью
		else
		{
			return to_string(this->re) + to_string(this->im) + "i";
		}
		
		return "";
	}
	// проверка равенства двух комплексных чисел
	bool Equals(Complex other) { return ((this->re == other.re) && (this->im == other.im)); }




	// ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ
	 
	// оператор присваивания
	Complex& operator=(const Complex& complex)
	{
		// проверка на самоприсваивание
		if (&complex == this) return *this;
		this->re = complex.re;
		this->im = complex.im;

		// возвращаем текущий объект
		return *this;
	}
	// оператор умножения комплексных чисел
	friend Complex operator*(Complex cx1, Complex cx2) { 
		// инициализация объекта комплексного числа
		Complex complex = Complex();
		complex.re = cx1.re * cx2.re - cx1.im * cx2.im;
		complex.im = cx1.im * cx2.re + cx1.re * cx2.im;
		return Complex(complex.re, complex.im);
	}
	// оператор умножения на комплексное
	friend Complex operator*(double d, Complex complex) { return complex * d; }
	// оператор умножения на вещественное число
	friend Complex operator*(Complex complex, double d) { return Complex(complex.re * d, complex.im * d); }
	// оператор сложения
	friend Complex operator+(Complex cx1, Complex cx2) { return Complex(cx1.re + cx2.re, cx1.im + cx2.im); }
	friend Complex operator~(Complex complex) { return Complex(complex.re, -complex.im); }
	friend Complex operator/(Complex cx1, Complex cx2) { 
		// инициализация объекта комплексного числа
		Complex complex = Complex();
		// вычисление частного комплексных чисел
		complex.re = (cx1.re * cx2.re + cx1.im * cx2.im) / (cx2.re * cx2.re + cx2.im * cx2.im);
		complex.im = (cx1.re * cx2.re + cx1.im * cx2.im) / (cx2.re * cx2.re + cx2.im * cx2.im);
		return complex;// возвращает комплексное число - результат
	}
	// операторы вычитания
	friend Complex operator-(Complex complex) { return Complex(-complex.re, -complex.im); }
	friend Complex operator-(Complex cx1, Complex cx2) { return cx1 + (-cx2); }
	// оператор вывода в поток
	friend ostream& operator<<(ostream& stream, const Complex& complex)
	{
		stream << complex.re << showpos << complex.im << "i" << noshowpos;
		return stream;
	}
	friend bool operator==(Complex cx1, Complex cx2) {
		// проверка значения на null
		if (cx1 == NULL || cx2 == NULL) return false;
		return cx1.Equals(cx2);
	}
};



int main()
{
	setlocale(LC_ALL, "RU");

	// массив комплексных чисел
	Complex complex[3];
	int re = 0, im = 0;

	// ввод комплексных чисел с клавиатуры
	for (int i = 0; i < 2; i++) {
		cout << "Создаем " << i+1 << "-е комплексное число\n";
		cout << "Вещественная часть: "; cin >> re;
		cout << "Мнимая часть: "; cin >> im;
		complex[i] = Complex(re, im);
	}
	
	complex[2] = Complex();
	cout << endl << endl;

	// работа с комплексными числами
	for (int i = 0; i < 2; i++) {
		cout << "Комплексное число №" << (i + 1) << " = " << complex[i] << endl;
		cout << "Модуль: " << complex[i].Abs() << endl;
		cout << "Аргумент: " << complex[i].Arg() << endl;
		cout << "Нахождение обратного: " << complex[i].Reverse() << endl;
		cout << endl;
	}
	
	
	complex[2] = complex[0] + complex[1];
	cout << "Сумма = " << complex[2] << endl;

	complex[2] = complex[0] - complex[1];
	cout << "Разница = " << complex[2] << endl;

	complex[2] = complex[0] * complex[1];
	cout << "Произведение = " << complex[2] << endl;

	complex[2] = complex[0] / complex[1];
	cout << "Частное = " << complex[2] << endl;
	

	cout << endl;
	system("pause");
	return 0;

}
