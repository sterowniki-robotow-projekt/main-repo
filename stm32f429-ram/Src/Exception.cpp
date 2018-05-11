#include "Exception.h"

Exception::Exception(exception_type n_type, const char * n_message)
{
	type = n_type;
	message = n_message;
}

Exception::Exception(exception_type n_type, const char * n_message, char n_index)
{
	type = n_type;
	message = n_message;
	index = n_index;
}

Exception::~Exception()
{
}

exception_type Exception::gType() const
{
	return type;
}

const char * Exception::gMessage() const
{
	return message;
}

char Exception::gIndex() const
{
	return index;
}

std::ostream & operator<<(std::ostream & out, const Exception & error)
{
	out << error.gMessage() << " ";
	
	switch (error.gType())
	{
	case exception_type::index_error:
		out << "'" << error.gIndex() << "' (" << ((int)error.gIndex()) << ")";
		break;
	case exception_type::is_null:
		break;
	case exception_type::singular_matrix:
		break;
	}	
	return out;
}