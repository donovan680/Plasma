#include "TestException.h"

namespace CppUnitLite
{
	TestException::TestException( const char* file_, int line_, const char* message_ )
		: file( file_ )
		, line( line_ )
		, message( message_ )
	{
	}
}
