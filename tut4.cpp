//  filesystem tut4.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
using std::cout;
using namespace boost::filesystem;

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Usage: tut4 path\n";
    return 1;
  }

  path p (argv[1]);

  try
  {
    if (exists(p))
    {
      if (is_regular_file(p))
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))
      {
        cout << p << " is a directory containing:\n";

        std::vector<path> v;

        for (auto&& x : directory_iterator(p))
          v.push_back(x.path()); 

        std::sort(v.begin(), v.end());  

        for (auto&& x : v)
        {
            if (is_regular_file(x))
            {
                        //    cout << "    " << x <<" to dodałem " << '\n';
                    ifstream file {x};
                   // file.open(x);
                    std::string str1;
                    while(std::getline(file, str1))
                    {
                        size_t pos, pos1, pos3 = str1.find(":");
                        std::string nn = str1.substr(0,pos3);
                                cout << "Name: " << nn << '\n';
                        pos =pos1= str1.find("|");
                        cout << "Pozycja | to: " << pos << '\n';
                        while (pos != std::string::npos && pos1 != std::string::npos)
                        {
                            
                            pos1 = str1.find(" |",pos+1,2);
                                std::string name ;
                            if (pos < pos1)
                                 name = str1.substr(pos, pos1-pos);
                            else
                                 name = str1.substr(pos1, pos-pos1);

                            cout << "    " << x <<" " << is_directory(x)<< "---> " << name << '\n';
                            pos = pos1;
                        }
                    }
                    file.close();
            }
          }
      }
      else
        cout << p << " exists, but is not a regular file or directory\n";
    }
    else
      cout << p << " does not exist\n";
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }

  return 0;
}
