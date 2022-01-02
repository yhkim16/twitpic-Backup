// twitpic id to img.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "twitpic id to img.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;
#define wstring2string ws2s

using namespace std;
void getimg(string id);
string wstring2string(wstring wstr);



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		wstring id;

		bool is;
		while(is=TRUE){

		cout<<"id:";
		wcin>>id;
		cout<<endl;

		string sid = ws2s(id);

		getimg(sid);

		CFile imagefile;

		wstring destName = id;

		char cbufsignature[30];

		char sig_jpg[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00/*null*/};

		char sig_png[] = {0x89, 0x50, 0x4E, 0x47, 0x00/*null*/};

		char sig_gif1[] = "GIF87a";

		char sig_gif2[] = "GIF89a";

		if(!imagefile.Open(id.c_str(),CFile::modeReadWrite|CFile::shareDenyNone))
		{
			cout<<"Image doesn't exist!";
			cout<<endl;
			goto rename;
		}
		
		if(imagefile.GetLength()<30)
		{
			goto rename;
		}

		imagefile.Read(cbufsignature,30);

		imagefile.Close();       

		if(memcmp(cbufsignature, sig_jpg, strlen(sig_jpg)) == 0)
		{

			destName = id+L".jpg";
		}

		if(memcmp(cbufsignature, sig_png, strlen(sig_png)) == 0)
		{

			destName = id+L".png";

		}
		if(memcmp(cbufsignature, sig_gif1, strlen(sig_gif1)) == 0 |
			
			memcmp(cbufsignature, sig_gif2, strlen(sig_gif2)) == 0)

		{

			destName = id+L".gif";

		}

		_wrename(id.c_str(),destName.c_str());									
rename:

		wcout<<destName<<endl;

		}
	}

	return nRetCode;
}

void getimg(string id)
{
	string url = "http://twitpic.com/show/large/"+id;
	WCHAR* wurl = new WCHAR[url.length()+1];
	WCHAR* wname = new WCHAR[id.length()+1];
	_swprintf(wname, L"%s", CA2W(id.c_str()));
	_swprintf(wurl, L"%s", CA2W(url.c_str()));

	string id2=id+".xml";
	string url2 = "http://api.twitpic.com/2/media/show.xml?id="+id;
	WCHAR* wurl2 = new WCHAR[url2.length()+1];
	WCHAR* wname2 = new WCHAR[id2.length()+1];
	_swprintf(wname2, L"%s", CA2W(id2.c_str()));
	_swprintf(wurl2, L"%s", CA2W(url2.c_str()));

	DeleteUrlCacheEntry(wurl);
	HRESULT hr = ::URLDownloadToFile(NULL,wurl,wname,0,NULL);
	DeleteUrlCacheEntry(wurl2);
	HRESULT hr2 = ::URLDownloadToFile(NULL,wurl2,wname2,0,NULL);


	delete [] wname,wname2,wurl,wurl2;
}

string wstring2string(wstring wstr)

{

        string str(wstr.length(),' ');

        copy(wstr.begin(),wstr.end(),str.begin());

        return str;

}
