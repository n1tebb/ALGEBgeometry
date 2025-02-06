#include "include.h"

class Integer
{
public:
	Integer() :sign_(false), units_(0) { }
	Integer(int value)
	{
		sign_ = value < 0;
		units_ = abs(value);
	}

	void setSign(bool sign)
	{
		this->sign_ = sign;
	}

	void setUnits(unsigned units)
	{
		this->units_ = units;
	}

	bool getSign() const
	{
		return sign_;
	}

	unsigned getUnits() const
	{
		return units_;
	}

	//проверка четности 
	bool isOdd() const
	{
		return units_ % 2 != 0;
	}

	//проверка положительности
	bool isPositive() const
	{
		return !sign_ && units_ != 0;
	}

	//проверка отрицательности
	bool isNegative() const
	{
		return sign_ && units_ != 0;
	}

	//проверка простое ли число
	bool isProstoe() const
	{
		if (units_ <= 1) return false;
		for (unsigned i = 2; i <= sqrt(units_); i++)
		{
			if (units_ % i == 0) return false;
		}
		return true;
	}

	//взаимопростые числа
	bool isVzaimProstoe(const Integer& other) const
	{
		unsigned a = units_;
		unsigned b = other.units_;

		while (a != 0 && b != 0)
		{
			if (a > b)
			{
				a %= b;
			}
			else
			{
				b %= a;
			}
		}
		return (a + b) == 1;
	}

	Integer findNOD(const Integer& b) const
	{
		unsigned x = getUnits();
		unsigned y = b.getUnits();

		while (x != 0 && y != 0)
		{
			if (x > y)
			{
				x %= y;
			}
			else
			{
				y %= x;
			}
		}
		return Integer(x + y);
	}

	Integer findNOK(const Integer& b) const
	{
		Integer nok = findNOD(b);
		unsigned nokUnits = (getUnits() / nok.getUnits()) * b.getUnits();

		return Integer(nokUnits);
	}

	int getValue() const
	{
		return sign_ ? -(int)units_ : (int)units_;
	}

	Integer operator+(const Integer& other) const
	{
		return Integer(this->getValue() + other.getValue());
	}

	Integer operator-(const Integer& other) const
	{
		return Integer(this->getValue() - other.getValue());
	}

	Integer operator*(const Integer& other) const
	{
		return Integer(this->getValue() * other.getValue());
	}

	Integer operator/(const Integer& other) const
	{
		return Integer(this->getValue() / other.getValue());
	}

	Integer operator%(const Integer& other) const
	{
		return Integer(this->getValue() % other.getValue());
	}

	Integer operator+=(const Integer& other)
	{
		*this = *this + other;
		return *this;
	}

	Integer operator-=(const Integer& other)
	{
		*this = *this - other;
		return *this;
	}

	Integer operator*=(const Integer& other)
	{
		*this = *this * other;
		return *this;
	}

	Integer operator/=(const Integer& other)
	{
		*this = *this / other;
		return *this;
	}

	Integer operator%=(const Integer& other)
	{
		*this = *this % other;
		return *this;
	}

	Integer& operator++()
	{
		if (sign_)
		{
			if (units_ > 0)
			{
				units_ -= 1;
				if (units_ == 0) sign_ = false;
			}
		}
		else {
			units_ += 1;
		}
		return *this;
	}

	Integer operator++(int)
	{
		Integer temp(*this);
		++(*this);
		return temp;
	}

	Integer& operator--()
	{
		if (sign_)
		{
			units_ += 1;
		}
		else
		{
			if (units_ > 0)
			{
				units_ -= 1;
				if (units_ == 0) sign_ = true;
			}
		}
		return *this;
	}

	Integer operator--(int)
	{
		Integer temp(*this);
		--(*this);
		return temp;
	}

	friend std::ostream& operator<<(std::ostream& os, const Integer obj)
	{
		os << obj.getValue();
		return os;
	}

private:
	bool sign_;
	unsigned units_;

};

class Rational
{
public:
	Rational() : numerator_(0), denominator_(1) { }

	Rational(const Integer& numerator, const Integer& denominator) : numerator_(numerator), denominator_(denominator)
	{
		if (denominator_.getUnits() == 0)
		{
			std::cerr << "ошибка не может быть 0";
			exit(EXIT_FAILURE);
		}
	}

	Integer getNumerator() const
	{
		return numerator_;
	}

	Integer getDenominator() const
	{
		return denominator_;
	}

	void reduce()
	{
		auto NOD = numerator_.findNOD(denominator_);
		numerator_ = Integer(numerator_.getUnits()) / NOD;
		denominator_ = Integer(denominator_.getUnits()) / NOD;
	}

	Rational operator+(const Rational& other) const
	{
		Integer commonDenom = denominator_.findNOK(other.denominator_);
		Integer newNumerator1 = numerator_ * (commonDenom / denominator_);
		Integer newNumerator2 = other.numerator_ * (commonDenom / other.denominator_);
		Integer resNumerator = newNumerator1 + newNumerator2;

		Rational result(resNumerator, commonDenom);
		result.reduce();
		return result;
	}

	Rational operator-(const Rational& other) const
	{
		Integer commonDenom = denominator_.findNOK(other.denominator_);
		Integer newNumerator1 = numerator_ * (commonDenom / denominator_);
		Integer newNumerator2 = other.numerator_ * (commonDenom / other.denominator_);
		Integer resNumerator = newNumerator1 - newNumerator2;

		Rational result(resNumerator, commonDenom);
		result.reduce();
		return result;
	}

	Rational operator*(const Rational& other) const
	{
		Integer commonDenom = denominator_.findNOK(other.denominator_);
		Integer newNumerator1 = numerator_ * (commonDenom / denominator_);
		Integer newNumerator2 = other.numerator_ * (commonDenom / other.denominator_);
		Integer resNumerator = newNumerator1 * newNumerator2;

		Rational result(resNumerator, commonDenom);
		result.reduce();
		return result;
	}

	Rational operator/(const Rational& other) const
	{
		Integer commonDenom = denominator_.findNOK(other.denominator_);
		Integer newNumerator1 = numerator_ * (commonDenom / denominator_);
		Integer newNumerator2 = other.numerator_ * (commonDenom / other.denominator_);
		Integer resNumerator = newNumerator1 / newNumerator2;

		Rational result(resNumerator, commonDenom);
		result.reduce();
		return result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Rational& obj)
	{
		os << obj.numerator_.getValue() << "/" << obj.denominator_.getValue();
		return os;
	}

private:
	Integer numerator_;
	Integer denominator_;
};

class Real
{
private:
	Integer wholePart_;
	Rational fractionalPart_;

public:
	Real() : wholePart_(0), fractionalPart_(Integer(0), Integer(1)) { }
	
	void normalize()
	{
		if (fractionalPart_.getNumerator().getUnits() >= fractionalPart_.getDenominator().getUnits())
		{
			Integer extra = fractionalPart_.getNumerator() / fractionalPart_.getDenominator();
			wholePart_ += extra;
			fractionalPart_ = Rational(fractionalPart_.getNumerator() % fractionalPart_.getDenominator(), fractionalPart_.getDenominator());
		}
	}

	Real(const Integer& whole, const Rational& factorial) : wholePart_(whole), fractionalPart_(factorial)
	{
		normalize();
	}

	Real(int value) : wholePart_(value), fractionalPart_(Integer(0), Integer(1)) { }

	Real(double value)
	{
		wholePart_ = Integer(static_cast<int>(value));
		double frac = value - static_cast<int>(value);
		int denom = 1000000;
		int num = static_cast<int>(frac * denom);
		fractionalPart_ = Rational(Integer(num), Integer(denom));
		fractionalPart_.reduce();
	}

	Integer getWholePart() const 
	{ 
		return wholePart_;
	}

	Rational getFractionalPart() const
	{
		return fractionalPart_;
	}

	void setWholePart(const Integer& whole)
	{
		wholePart_ = whole;
	}

	void setFractionalPart(const Rational& fractional)
	{
		fractionalPart_ = fractional;
		normalize();
	}

	bool isDeci() const 
	{
		return fractionalPart_.getDenominator().getUnits() != 0;
	}

	bool isPositive() const
	{
		return wholePart_.isPositive() || fractionalPart_.getNumerator().isPositive();
	}

	bool isNegative() const
	{
		return wholePart_.isNegative() || fractionalPart_.getNumerator().isNegative();
	}

	bool isSameObj(const Real& other) const
	{
		return this == &other;
	}

	Real operator+(const Real& other) const
	{
		return Real(wholePart_ + other.wholePart_, fractionalPart_ + other.fractionalPart_);
	}

	Real operator-(const Real& other) const
	{
		return Real(wholePart_ - other.wholePart_, fractionalPart_ - other.fractionalPart_);
	}

	Real operator*(const Real& other) const
	{
		return Real(wholePart_ - other.wholePart_, fractionalPart_ - other.fractionalPart_);
	}


	Real operator/(const Real& other) const
	{
		if (other.wholePart_.getUnits() == 0 && other.fractionalPart_.getNumerator().getUnits() == 0)
		{
			std::cerr << "деление на 0";
			exit(EXIT_FAILURE);
		}
		return Real(wholePart_ / other.wholePart_, fractionalPart_ / other.fractionalPart_);
	}

	Real operator-() const
	{
		return Real(wholePart_, fractionalPart_);
	}

	Real operator+() const
	{
		return *this;
	}


};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Integer a(15);
	Integer b(20);

	std::cout << "исходные числа:\n";
	std::cout << "a: " << a << ", b: " << b << "\n\n";

	std::cout << "a - четное: " << !a.isOdd() << "\n";
	std::cout << "b - четное: " << !b.isOdd() << "\n\n";

	std::cout << "a - нечетное: " << a.isOdd() << "\n";
	std::cout << "b - нечетное: " << b.isOdd() << "\n\n";

	std::cout << "a - положительное: " << a.isPositive() << "\n";
	std::cout << "b - положительное: " << b.isPositive() << "\n\n";

	std::cout << "a - отрицательное: " << a.isNegative() << "\n";
	std::cout << "b - отрицательное: " << b.isNegative() << "\n\n";

	std::cout << "a - простое: " << a.isProstoe() << "\n";
	std::cout << "b - простое: " << b.isProstoe() << "\n\n";

	std::cout << "a и b - взаимопростые: " << a.isVzaimProstoe(b) << "\n\n";

	Integer nod = a.findNOD(b);
	Integer nok = a.findNOK(b);

	std::cout << "НОД a и b - " << nod << "\n";
	std::cout << "НОК a и b - " << nok << "\n\n";

	std::cout << "инкремент и декремент:\n";
	std::cout << "++a: " << ++a << "\n";
	std::cout << "a++: " << a++ << ", a стало = " << a << "\n";
	std::cout << "--a: " << --a << "\n";
	std::cout << "a--: " << a-- << ", a стало = " << a << "\n\n";
	std::cout << "++b: " << ++b << "\n";
	std::cout << "b++: " << b++ << ", b стало = " << b << "\n";
	std::cout << "--b: " << --b << "\n";
	std::cout << "b--: " << b-- << ", b стало = " << b << "\n\n";

	Rational r(a, b);
	std::cout << "Дробь r: " << r << "\n";

	Real real1(5, Rational(Integer(3), Integer(4)));
	Real real2(3, Rational(Integer(1), Integer(2)));
	Real real3(7.25);

	std::cout << "Действительные числа: \n";
	std::cout << "real1: " << real1 << "\n";
	std::cout << "real2: " << real2 << "\n";
	std::cout << "real3: " << real3 << "\n\n";

	Real sum = real1 + real2;
	Real diff = real1 - real2;
	Real mnoj = real1 * real2;
	Real dele = real1 / real2;

	std::cout << "сложение: real1 + real2 = " << sum << "\n";
	std::cout << "Вычитание: real1 - real2 = " << diff << "\n";
	std::cout << "Умножение: real1 * real2 = " << mnoj << "\n";
	std::cout << "Деление: rea1 / real2 = " << dele << "\n\n";

	return 0;
}