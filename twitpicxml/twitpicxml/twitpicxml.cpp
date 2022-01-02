// twitpicxml.cpp : Defines the entry point for the console application.

//

#include "stdafx.h"

#include "twitpicxml.h"

#include "twitpicclass.h"

#ifdef _DEBUG

#define new DEBUG_NEW

#endif

// The one and only application object

CWinApp theApp;

using namespace std;

using namespace twitpicn;

#define string2wstring s2ws

#define wstring2string ws2s

wstring string2wstring(string str);

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

                // TODO: code your application's behavior here.

                string taccount;

                int i=0,j;

                cout<<"twitter account : ";

                cin>>taccount;

                cout<<endl;

				cout<<"Start Page : ";

				cin>>i;

				i=i-1;
				int i2=i;

				cout<<endl;

                cout<<"Last Page : ";

                cin>>j;

				if((i>j)|(i<0)){i=0;}
				if(j<0){j=0;}
                

                twitpic TP(taccount);

                char k[4];

                CMarkup xml;

                wstring xmlname;

                char mode;

                cout<<"Save image mode:a"<<endl;

                cout<<"Mode : ";

                cin>>mode;

                cout<<endl;

                if(mode=='a')

                {

                        goto image_mode;

                }

                for(i;i<j;i++)

                {

                        itoa(i+1,k,10);

                        string url=TP.user_show(k);

                        string name=TP.getaccount()+" - "+k+".xml";

                        TP.getxml(url,name);

                        cout<<name<<endl;

                }

image_mode:

                cout<<"Do you want save images?"<<"<y/n>"<<endl;

                char yn;

                cin>>yn;

                switch(yn)

                {

                case 'y':

                case 'Y':

                        for(i=i2;i<j;i++)

                        {
							wcout<<"page : "<<i+1<<endl;

                                itoa(i+1,k,10);

                                string sxmlname = TP.getaccount()+" - "+k+".xml";

                                xmlname = s2ws(sxmlname);

                                xml.Load(xmlname.c_str());

                                xml.FindElem(_T("user"));

                                xml.FindChildElem(_T("images"));

                                xml.IntoElem();

                                while(xml.FindChildElem(_T("image")))

                                {

                                        xml.IntoElem();

                                        xml.FindChildElem(_T("short_id"));

                                        wstring short_id = xml.GetChildData();

                                        xml.OutOfElem();

                                        string imageurl = TP.media_show(ws2s(short_id));

                                        TP.getxml(imageurl,ws2s(short_id)+".xml");

                                        string fimageurl = TP.media_large(ws2s(short_id),"large");

                                        TP.getxml(fimageurl,ws2s(short_id));

                                        CFile imagefile;

										wstring destName = short_id;

                                        char cbufsignature[30];

                                        char sig_jpg[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00/*null*/};

                                        char sig_png[] = {0x89, 0x50, 0x4E, 0x47, 0x00/*null*/};

                                        char sig_gif1[] = "GIF87a";

                                        char sig_gif2[] = "GIF89a";
										
										if(!imagefile.Open(short_id.c_str(),CFile::modeReadWrite|CFile::shareDenyNone))
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

                                                destName = short_id+L".jpg";

                                        }

                                        if(memcmp(cbufsignature, sig_png, strlen(sig_png)) == 0)

                                        {

                                                destName = short_id+L".png";

                                        }

                                        if(memcmp(cbufsignature, sig_gif1, strlen(sig_gif1)) == 0 |

                                                memcmp(cbufsignature, sig_gif2, strlen(sig_gif2)) == 0)

                                        {

                                                destName = short_id+L".gif";

                                        }

                                        

                                        _wrename(short_id.c_str(),destName.c_str());									
rename:

                                        wcout<<destName<<endl;

                                }
                        }

                        break;

                case 'n':

                case 'N':

                        break;

                default:

                        break;

                }

                cout<<"Complete!";

                fflush(stdin);

                getchar();

        }

        return nRetCode;

}

wstring string2wstring(string str)

{

        wstring wstr(str.length(),L' ');

        copy(str.begin(),str.end(),wstr.begin());

        return wstr;

}

string wstring2string(wstring wstr)

{

        string str(wstr.length(),' ');

        copy(wstr.begin(),wstr.end(),str.begin());

        return str;

}