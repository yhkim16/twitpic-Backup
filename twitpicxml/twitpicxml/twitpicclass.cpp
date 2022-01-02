#include "twitpicclass.h"
namespace twitpicn
{
	    twitpic::twitpic()
		{
			account="twitpic";
			APIURL = "http://api.twitpic.com/2/";
		}
	    twitpic::twitpic(string twitpic_account)
		{
			account = twitpic_account;
			APIURL = "http://api.twitpic.com/2/";
		}
		twitpic::~twitpic()
		{
			return;
		}
		string twitpic::media_show(string id)
		{
			string url=APIURL+"media/show.xml"+"?id="+id;
			return url;
		}
		string twitpic::media_large(string id,string size)
		{
			string url="http://twitpic.com/show/"+size+"/"+id;
			return url;
		}
		string twitpic::user_show(string page)
		{
			string url=APIURL+"users/show.xml"+"?username="+account+"&page="+page;
			return url;
		}
		void twitpic::getxml(string url,string name)
		{

			WCHAR* wurl = new WCHAR[url.length()+1];
			WCHAR* wname = new WCHAR[name.length()+1];
			_swprintf(wurl, L"%s", CA2W(url.c_str()));
			_swprintf(wname, L"%s", CA2W(name.c_str()));

			DeleteUrlCacheEntry(wurl);
			HRESULT hr = ::URLDownloadToFile(NULL,wurl,wname,0,NULL);

			delete [] wurl ,wname;
		}
		int twitpic::saveimage(string url)
		{
			return 0;
		}
}