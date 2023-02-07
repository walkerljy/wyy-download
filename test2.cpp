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
#include<locale.h>

using namespace std;
int main()
{
  setlocale(LC_ALL,"zh-CN");    
  SetConsoleOutputCP(CP_UTF8);
  int cnt=0;
  string test="Normal聽No聽More - (涓嶅啀骞冲�