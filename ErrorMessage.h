#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include <iostream>

namespace sict
{
	class ErrorMessage
	{
		char* message_;

		public:

		ErrorMessage();
		ErrorMessage(const char*);
		
		ErrorMessage(const ErrorMessage&) = delete;
		ErrorMessage& operator=(const ErrorMessage&) = delete;

		~ErrorMessage();

		void clear();
		bool isClear()const;
		void message(const char*);
		const char* message()const;

		
		ErrorMessage& operator=(const char*);
	};
    
    	std::ostream& operator<<(std::ostream&,const ErrorMessage&);
}

#endif

