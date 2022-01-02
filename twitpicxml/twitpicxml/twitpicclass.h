#ifndef twitpic_class
#define twitpic_class
#include "stdafx.h"
#include <wininet.h>
#pragma comment(lib, "WinInet")

using namespace std;

namespace twitpicn
{

	class twitpic
	{
	private:
		string APIURL;
		string account;

	public:

		
		twitpic();
		twitpic(string twitpic_account);

		~twitpic();
		
		string media_show(string id);

		string media_large(string id,string size);

		string user_show(string page);

		void getxml(string url,string name);

		int saveimage(string url);

		string getaccount(){return account;}
	};
}
#endif