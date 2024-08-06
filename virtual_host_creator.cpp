#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

string rootDir(string root_pro_dir)
{
  string result;
  result = "\nDocumentRoot \"" + root_pro_dir + "\"\n<Directory \"" + root_pro_dir + "\">\n\tOptions Indexes FollowSymLinks Includes ExecCGI\n\tAllowOverride All\n\tRequire all granted\n</Directory>\n";
  return result;
}

string virtualDir(string pro_dir, string server_name)
{
  string result;
  result = "\n<VirtualHost *:80>\n\tDocumentRoot \"" + pro_dir + "\"\n\tServerName " + server_name + "\n</VirtualHost>\n";
  return result;
}

string driverHost(string server_name)
{
  string result;
  result = "127.0.0.1 " + server_name + "\n";
  return result;
}

void writeData(string filename, string new_data)
{
  fstream write_data;
  write_data.open(filename, ios::app);
  if (write_data.is_open())
  {
    write_data << new_data;
  }
  write_data.close();
}

int main()
{
  system("cls");
  string xampp = getenv("xa-con");
  string xampp_installed_folder = xampp.substr(0, xampp.find_last_of('\\'));

  // 1. get the public directory (folder) of your project
  string project_dir;
  cout << "Enter public folder of your project (D:\\projects\\proj1\\public) : ";
  cin >> project_dir;

  // 2. get the preferred server name
  string server_name;
  cout << "Enter a server name (dev.proj1.test) : ";
  cin >> server_name;

  // 3. create a root directory for your project
  int last_slash_idx = project_dir.find_last_of("\\");
  string root_project_dir = project_dir.substr(0, last_slash_idx);

  // 4. write a new DocumentRoot into the root-creating config file
  string new_root = rootDir(root_project_dir);
  writeData(xampp_installed_folder + "/apache/conf/httpd.conf", new_root);

  // 5. write a new VirtualHost into the virtulhost config file
  string new_virtual_host = virtualDir(project_dir, server_name);
  writeData(xampp_installed_folder + "/apache/conf/extra/httpd-vhosts.conf", new_virtual_host);

  // 6. write the driver address for computer
  string new_driver_host = driverHost(server_name);
  writeData("C:/Windows/System32/drivers/etc/hosts", new_driver_host);

  cout << "\n\033[1;31mDon't forget to restart the XAMPP server!\033[0m" << endl;
  cin.get();
}