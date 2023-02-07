#define MAXBLOCKSIZE 1024
#pragma comment( lib, "wininet.lib" ) ;
#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include<io.h>
#include<fcntl.h>
#include<locale>
#include<codecvt>
#include <algorithm> 
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

void error_quit( const char *msg )
{
  perror( msg );
  exit( -1 );
}
void change_path( const char *path )
{
  //printf( "Leave %s Successed . . .\n", getcwd( NULL, 0 ) );
  if ( chdir( path ) == -1 )
    error_quit( "chdir" );
  //printf( "Entry %s Successed . . .\n", getcwd( NULL, 0 ) );
}

void rm_dir( const char *path )
{
  DIR    *dir;
  struct dirent  *dirp;
  struct stat  buf;
  char    *p = getcwd( NULL, 0 );
  if ( (dir = opendir( path ) ) == NULL )
    error_quit( "OpenDir" );
  change_path( path );
  while ( dirp = readdir( dir ) )
  {
    if ( (strcmp( dirp->d_name, "." ) == 0) || (strcmp( dirp->d_name, ".." ) == 0) )
      continue;
    if ( stat( dirp->d_name, &buf ) == -1 )
      error_quit( "stat" );
    if ( S_ISDIR( buf.st_mode ) )
    {
      rm_dir( dirp->d_name );
      /*if(rmdir(dirp->d_name)==-1)
       *  error_quit("rmdir");
       * printf("rm %s Successed . . .\n",dirp->d_name);*/
      continue;
    }
    if ( remove( dirp->d_name ) == -1 )
      error_quit( "remove" );
    //printf( "rm %s Successed . . .\n", dirp->d_name );
  }
  closedir( dir );
  change_path( p );
  if ( rmdir( path ) == -1 )
    error_quit( "rmdir" );
  //printf( "rm %s Successed . . .\n", path );
}

void download(const char *Url,string name) {
	byte Temp[MAXBLOCKSIZE];
	ULONG Number = 1;
	FILE *stream;
  /*
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stream), _O_U16TEXT);
  */
	HINTERNET hSession = InternetOpen(TEXT("RookIE/1.0"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL) {
		HINTERNET handle2 = InternetOpenUrl(hSession, TEXT(Url), NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (handle2 != NULL) {
			std::locale loc = std::locale::global(std::locale(""));
			if( (stream = fopen( name.c_str(), "wb" )) != NULL ) {
				while (Number > 0) {
					InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);
					fwrite(Temp, sizeof (char), Number , stream);
				}
				fclose( stream );
			}
			std::locale::global(loc);
			InternetCloseHandle(handle2);
			handle2 = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
}

string readFileIntoString(string filename) {
	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch))
	buf.put(ch);
	return buf.str();
}

string UTFtoGBK(string ipt) {
	unsigned char* chSMS=NULL;
	chSMS = (unsigned char *)ipt.c_str();
	strncpy((char *)chSMS, ipt.c_str(),ipt.size());
	int len=MultiByteToWideChar(CP_UTF8,0,(LPCCH)chSMS,-1,NULL,0);
	wchar_t* wstr=new wchar_t[len+1];
	memset(wstr,0,len+1);
	MultiByteToWideChar(CP_UTF8,0,(LPCCH)chSMS,-1,wstr,len);
	len=WideCharToMultiByte(CP_ACP, 0,wstr,-1,NULL,0,NULL,NULL);
	char* str=new char[len+1];
	memset(str,0,len+1);
	WideCharToMultiByte(CP_ACP, 0,wstr,-1,str,len,NULL,NULL);
	
	if (wstr) delete[] wstr;
	return str;
}

string pack(string ipt){
	string c=ipt;
	c=UTFtoGBK(c);
	c.erase(std::remove_if(c.begin(), c.end(), [](char ch) {return int(ch) == -62 || int(ch) == -96; }), c.end());
	for(int i=0;i<c.size();i++){
		if(int(c[i])==63){
			c[i]=32;
		}
		//cout<<int(c[i])<<" ";
	}
	return c;	
}

int main(int argc, char* argv[]) {
  
}