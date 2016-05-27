/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include<QString>
#include<string>
using std::string;

// trasforma un numero in una stringa
QString num2string(int num) {

  QString s;

  if(num>=0)
    do {
      s.push_front(num%10 + '0');
      num /= 10;
    } while(num);

  else
    s="'GNULLA";

  return s;

}

QString string2QString(string a)
{
  QString s;
  for (int i=0; static_cast<unsigned int>(i)<a.size(); ++i)
    s.push_back(a[i]);
  return s;
}

