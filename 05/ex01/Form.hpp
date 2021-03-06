#pragma once

class Bureaucrat;
#include "Bureaucrat.hpp"

#define F_GRADE_EXCEPT Form::GradeTooHighException, Form::GradeTooLowException


class Form {
public:
	Form();
	Form(const std::string &name, int required, int exec_required) throw(F_GRADE_EXCEPT);
	Form(const Form &);
	virtual ~Form();

	Form &operator=(const Form &);
	friend std::ostream &operator<<(std::ostream &os, const Form &b);

	const std::string &getName() const;
	int getRequired() const;
	void beSigned(const Bureaucrat &b) throw(F_GRADE_EXCEPT);

	class GradeTooHighException : public std::exception {
	public:
		using std::exception::what;
		const char *what();
	};

	class GradeTooLowException : public std::exception {
	public:
		using std::exception::what;
		const char *what();
	};

private:
	const std::string _name;
	const int _required;
	const int _exec_required;
	bool _signed;

};

  
