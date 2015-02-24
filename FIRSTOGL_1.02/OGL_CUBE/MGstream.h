#include <string>
#include <fstream>
#include <vector>
#include <sstream>


#define DBOUT( s ){                        \
	std::wostringstream os_;                \
	os_ << s;                               \
	OutputDebugString((os_.str().c_str())); } \

namespace MGstream {

	static inline std::string readtxt(const char* title)
	{
		std::ifstream file(title);
		std::string line;
		std::string txt;

		while(std::getline(file,line))
		{
			txt+= line;
			txt.push_back('\n');
		}
		return txt;

		
	}

	static inline void writetxt(const char* title,char *buffer)
	{
		FILE *_file;
		_file = fopen(title,"w");
		if(_file!=NULL)
		{
			fputs(buffer,_file);
			fclose(_file);
		}		
	}

	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems){
		std::stringstream ss(s);
		std::string item;

		while(std::getline(ss, item, delim)) {
			if(item.length() != 0)
			elems.push_back(item);
		}
		
		return elems;
	}

	static std::vector<std::string> split(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		split(s,delim,elems);
		return elems;
	}
};