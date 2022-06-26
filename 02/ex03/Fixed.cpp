#include "Fixed.hpp"

Fixed::Fixed() {
	//std::cout << "Default constructor called" << std::endl;
	_val = 0;
	_f_bits = 8;
}

Fixed::Fixed(const int x) {
	//std::cout << "Int constructor called" << std::endl;
	_val = (x << 8);
	_f_bits = 8;
}


Fixed::Fixed(const float x) {//: _val(roundf(x * 256)) {
	//std::cout << "Float constructor called" << std::endl;

	// The code below sould be equivalent to _val = x * 256
	// It was made to check my comprension of float by
	// doing the multiplication manually on the bitset
	unsigned int t;

	_f_bits = 8;
	memcpy(&t, &x, 4);
	int exp=0, mantis=((t<<1) != 0);
	for (int i = 7; i >= 0; i--)
		exp = (exp << 1) | ((t >> (23 + i)) & 1);
	exp -= 127;
	for (int i = 22; i >= 0; i--)
		mantis = (mantis << 1) | ((t >> i) & 1);
	_val = (exp <= 15 ? mantis >> (15-exp) : mantis << (exp-15)) | (((t >> 31) & 1) << 31);
}

Fixed::Fixed(const Fixed &cpy) {
	//std::cout << "Copy constructor called" << std::endl;
	*this = cpy;
}

Fixed &Fixed::operator=(const Fixed &cpy) {
	//std::cout << "Assignement constructor called" << std::endl;
	_val = cpy.getRawBits();
	_f_bits = 8;
	return (*this);
}

bool Fixed::operator<(const Fixed& op) {
	return (this->_val < op._val);
}

bool Fixed::operator>(const Fixed& op) {
	return (this->_val > op._val);
}

bool Fixed::operator<=(const Fixed& op){
	return (this->_val <= op._val);
}

bool Fixed::operator>=(const Fixed& op) {
	return (this->_val >= op._val);
}

bool Fixed::operator==(const Fixed& op) {
	return (this->_val == op._val);
}

bool Fixed::operator!=(const Fixed& op) {
	return (this->_val != op._val);
}

Fixed Fixed::operator+(const Fixed& op) const {
	//Fixed out((float)this->toFloat() + (float)op.toFloat());
	//return out;
	Fixed ret;
	ret.setRawBits(getRawBits() + op.getRawBits());
	return ret;
}

Fixed Fixed::operator-(const Fixed& op) const {
	//Fixed out((float)this->toFloat() - (float)op.toFloat());
	//return out;
	Fixed ret;
	ret.setRawBits(getRawBits() - op.getRawBits());
	return ret;
}

Fixed Fixed::operator*(const Fixed& op) const {
	Fixed out((float)this->toFloat() * (float)op.toFloat());
	return out;
}

Fixed Fixed::operator/(const Fixed& op) const {
	Fixed out((float)this->toFloat() / (float)op.toFloat());
	return out;
}

Fixed &Fixed::operator++() {
	_val += (1 << _f_bits);
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed ret(*this);
	++(*this);
	return ret;
}

Fixed &Fixed::operator--() {
	_val -= (1 << _f_bits);
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed ret(*this);
	--(*this);
	return ret;
}

Fixed::~Fixed() {
	//std::cout << "Destructor called" << std::endl;
}  

std::ostream &operator<<(std::ostream &out, const Fixed& op) {
	std::cout << op.toFloat();
	return out;
}


int Fixed::getRawBits() const {
	return _val;
}

void Fixed::setRawBits(int const raw) {
	_val = raw;
}

float Fixed::toFloat() const {
	return ((float)_val / (float)(1 << _f_bits));
} 

int Fixed::toInt() const {
	return _val / (1 << _f_bits);
}