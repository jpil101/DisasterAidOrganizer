#include "ErrorMessage.h"
#include <cstring>


namespace sict
{
    
    ErrorMessage::ErrorMessage()
    {
    	message_ = nullptr;
    }
	
	ErrorMessage::ErrorMessage(const char* errorm)
	{
		message_ = nullptr;

		message(errorm);
	}

	/*ErrorMessage::ErrorMessage(const ErrorMessage& em)
	{
		if(message_ != nullptr)
		{
			message_ = new char[strlen(em.message())+1];

			strcpy(message_,em.message());
		}
		else
			message_ = nullptr;
	}*/

	ErrorMessage::~ErrorMessage()
	{
		delete [] message_;
	}

	void ErrorMessage::clear()
	{
		delete [] message_;

		message_ = nullptr;
	}

	bool ErrorMessage::isClear()const
	{
		return (message_==nullptr);
	}

	void ErrorMessage::message(const char* errorm)
	{
		delete [] message_;

		message_ = new char[strlen(errorm)+1];

		strcpy(message_,errorm);
	}

	const char* ErrorMessage::message()const
	{
		return message_;
	}

	/*ErrorMessage& ErrorMessage::operator=(const ErrorMessage& em)
	{
		if(this!=&em)
		{
			delete [] message_;

			if(em.message()!=nullptr)
			{
				message_ = new char[strlen(em.message())+1];

				strcpy(message_,em.message());
			}
			else
				message_ = nullptr;
		}

		return *this;
	}*/

	ErrorMessage& ErrorMessage::operator=(const char* errorm)
	{
		
			delete [] message_;

			if(errorm!=nullptr)
			{
				message_ = new char[strlen(errorm)+1];

				strcpy(message_,errorm);
			}
			else
				message_ = nullptr;
		

		return *this;
	}

	std::ostream& operator<<(std::ostream& os,const ErrorMessage& em)
	{
		if(!em.isClear())
			os<<em.message();

		return os;
	}

}