#include <fstream>
#include <iostream>
using namespace std;
 
int main ()
{
    
   string data="hello 刘嘉远 666";
 
   // 以写模式打开文件
   ofstream outfile;
   outfile.open(".\\hello 刘嘉远.txt",ios::out);
   // 向文件写入用户输入的数据
   outfile << data << endl;
   outfile.close();
   return 0;
}