#include "Model.h"
#include <string>
#include <fstream>
#include "MGstream.h"


Model::Model(void)
{
	numFace = 0;
}

bool Model::LoadModel(const char *filename)
{
	std::ifstream file(filename);
	std::string line;
	std::vector<std::string> split_line(0);
	std::vector<std::string> face_split(0);

	std::vector<std::string> temp(0);

	unsigned short i = 0;

	glGenVertexArrays(1,&VAOM);
	glGenBuffers(1,&VBOM);
	glGenBuffers(1,&VBOnorm);
	glGenBuffers(1,&VBOtex);

	DBOUT("Loading: " << filename << "..." << std::endl);

	while(std::getline(file,line))
	{
		split_line = MGstream::split(line,' ');
		if(split_line.size() != 0)
		{
			if(split_line[0].length() == 2)
			{
				//If its a Vertex Normal
				if(split_line[0][0] == 'v' && split_line[0][1]== 'n')
				{
					array_vNormal.push_back(atof(split_line[1].c_str()));
					array_vNormal.push_back(atof(split_line[2].c_str()));
					array_vNormal.push_back(atof(split_line[3].c_str()));
				}
				else //if its a Vertex Texture
					if(split_line[0][0] == 'v' && split_line[0][1]== 't')
					{
						array_vTexture.push_back(atof(split_line[1].c_str()));
						array_vTexture.push_back(atof(split_line[2].c_str()));
					}
			}
			else
				if(split_line[0].length() == 1)
				{
					//if its a vertex
					if(split_line[0][0] == 'v')
					{
						array_vertex.push_back(atof(split_line[1].c_str()));
						array_vertex.push_back(atof(split_line[2].c_str()));
						array_vertex.push_back(atof(split_line[3].c_str()));
					}
					else//if its a face
					if(split_line[0][0] == 'f')
					{
						i = 1;
						
						if(split_line.size() > 4)
							return false;
						else
						{
							
							while(i < split_line.size())
							{
								face_split = MGstream::split(split_line[i],'/');
								array_vertexToVBO.push_back(array_vertex[atof(face_split[0].c_str())*3-3]);
								array_vertexToVBO.push_back(array_vertex[atof(face_split[0].c_str())*3-2]);
								array_vertexToVBO.push_back(array_vertex[atof(face_split[0].c_str())*3-1]);
								array_vTextureToVBO.push_back(array_vTexture[atof(face_split[1].c_str())*2-2]);
								array_vTextureToVBO.push_back(array_vTexture[atof(face_split[1].c_str())*2-1]);
								array_vNormalToVBO.push_back(array_vNormal[atof(face_split[2].c_str())*3-3]);
								array_vNormalToVBO.push_back(array_vNormal[atof(face_split[2].c_str())*3-2]);
								array_vNormalToVBO.push_back(array_vNormal[atof(face_split[2].c_str())*3-1]);
								i++;
							}
						}

						numFace++;
					}
				}
		}
	}

	array_vertex.clear();
	array_vNormal.clear();
	array_vTexture.clear();

	GLfloat lol[9] = {0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,2.0f,0.0f,0.0f};
	GLfloat lol2[9] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
	GLfloat lol3[6] = {0.0f,0.0f,0.5f,0.5f,1.0f,0.0f};

	GLenum error;

	glBindVertexArray(VAOM);

	error = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER,VBOM);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER,array_vertexToVBO.size() * sizeof(GLfloat),&array_vertexToVBO[0],GL_STATIC_DRAW);

	error = glGetError();
	
	glBindVertexArray(VAOM);
	glBindBuffer(GL_ARRAY_BUFFER,VBOnorm);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(1);
	
	glBufferData(GL_ARRAY_BUFFER,array_vNormalToVBO.size() * sizeof(GLfloat),&array_vNormalToVBO[0],GL_STATIC_DRAW);

	error = glGetError();
	glBindVertexArray(VAOM);
	glBindBuffer(GL_ARRAY_BUFFER,VBOtex);

	glVertexAttribPointer(4,2,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(4);

	glBufferData(GL_ARRAY_BUFFER,array_vTextureToVBO.size() * sizeof(GLfloat),&array_vTextureToVBO[0],GL_STATIC_DRAW);

	error = glGetError();
	
	
	return true;
}

void Model::Draw()
{
	glBindVertexArray(VAOM);
	glDrawArrays(GL_TRIANGLES,0,(array_vertexToVBO.size()));
}

Model::~Model(void)
{
	glDeleteBuffers(1,&VAOM);
	glDeleteBuffers(1,&VBOM);
	glDeleteBuffers(1,&VBOnorm);
	glDeleteBuffers(1,&VBOtex);
}
