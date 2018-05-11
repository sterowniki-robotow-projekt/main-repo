#pragma once
#include <iostream>

enum exception_type : char
{
	index_error,
	is_null,
	singular_matrix
};

class Exception
{
private:
	exception_type type;
	const char* message;
	char index;

public:
	Exception(exception_type temp_type, const char* temp_message);
	Exception(exception_type temp_type, const char* temp_message, char temp_index);
	~Exception();
	exception_type gType() const;
	const char *gMessage() const;
	char gIndex() const;
};
std::ostream &operator << (std::ostream &out, const Exception& error);

