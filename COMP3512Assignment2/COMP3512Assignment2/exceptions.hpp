#pragma once
#include <exception>
#include <stdexcept>

class EmptyQueueException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "The queue is empty or the element was not found. Please, add users before performing actions";
	}
} ex;

class ElementNotFound : public std::exception
{
	virtual const char* what() const throw()
	{
		return "The requested patient was not found.";
	}
} nf;