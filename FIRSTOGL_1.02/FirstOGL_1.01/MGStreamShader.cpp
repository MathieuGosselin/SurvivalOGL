#include "MGStreamShader.h"


//MGStreamShader::MGStreamShader(void)
//{
//}

std::string MGStreamShader::rdtxtshade(const char* Title)
{
	std::ifstream file(Title);
	std::string text;
	std::string line;

	while(std::getline(file,line)){
		text += line;
		text.push_back('\n');
	}

	
	return text;
}

//MGStreamShader::~MGStreamShader(void)
//{
//}
