#include "Map.h"

#define VERTEX_BY_CUBE 108
#define SIZEOFQUADS 300000
#define SIZEOFTEXTURE 200000
#define SIZE 2.0

using namespace vmath;

Map::Map(void): fQuad()
{
}

bool Map::loadmap(const char *filename)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	unsigned width,height;

	lodepng::load_file(png,filename);

	if(!lodepng::decode(image,width,height,png))
	{
		createmap(image,width,height);

		return true;
	}
	else
		return false;
}

void Map::createmap(std::vector<unsigned char> &img, unsigned width, unsigned height)
{
	//std::fill_n(fQuad,SIZEOFQUADS,0);

	int vertexid = 0; 
	int idtest = 0;
	int idtext = 0;
	int idnormal = 0;

	glGenVertexArrays(3,VAO);
	glGenBuffers(3,VBO);
	glGenBuffers(3,VBOnormal);
	glGenBuffers(1,&VBOTexture);
	
	

	GLfloat vTex[72] = {
		0.0,0.0,
		1.0,0.0,
		0.0,1.0,
		1.0,0.0,
		0.0,1.0,
		1.0,1.0,

		0.0,0.0,
		1.0,0.0,
		0.0,1.0,
		1.0,0.0,
		0.0,1.0,
		1.0,1.0,
	
		0.0,0.0,
		1.0,0.0,
		0.0,1.0,
		1.0,0.0,
		0.0,1.0,
		1.0,1.0,
	
		0.0,0.0,
		1.0,0.0,
		0.0,1.0,
		1.0,0.0,
		0.0,1.0,
		1.0,1.0,
	
		0.0,0.0,
		1.0,0.0,
		0.0,1.0,
		1.0,0.0,
		0.0,1.0,
		1.0,1.0,
	
		0.0,0.0,
		1.0,0.0,
		0.0,1.0,
		1.0,0.0,
		0.0,1.0,
		1.0,1.0};
		
		
	
		for(int i = 0 ; i < 3 ; i++)
		{
			
			glBindVertexArray(VAO[i]);
			glBindBuffer(GL_ARRAY_BUFFER,VBO[i]);

			glBufferData(GL_ARRAY_BUFFER, width * height * sizeof(fQuad),0,GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

			glBindBuffer(GL_ARRAY_BUFFER,VBOnormal[i]);

			glBufferData(GL_ARRAY_BUFFER, width * height * sizeof(fQuad),0,GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);

			glBindBuffer(GL_ARRAY_BUFFER,VBOTexture);
			glBufferData(GL_ARRAY_BUFFER,width * height * sizeof(vTex),0,GL_STATIC_DRAW);

			glEnableVertexAttribArray(4);
			//glBindBuffer(GL_ARRAY_BUFFER,VBOTexture);
			glVertexAttribPointer(4,2,GL_FLOAT,GL_FALSE,0,0);


		}

	
	

	for(int i = 0;i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			idtest = (i * width + j) * sizeof(fQuad);
			idtext = (i * width + j) * sizeof(vTex);
			for(int k = 0; k < 3; k++)
			{
				vertexid = i*width*4+ j *4 + k;
				idnormal = (i*width + j) * sizeof(vNormal);
				if(img[vertexid] != 0)
				{
					
					//front
					fQuad[0] = (0.0f + i) * SIZE;
					fQuad[1] = (0.0f + k)  * SIZE;
					fQuad[2] = (0.0f + j) * SIZE;

					fQuad[3] = (1.0f + i) * SIZE;
					fQuad[4] = (0.0f + k)  * SIZE;
					fQuad[5] = (0.0f + j) * SIZE;

					fQuad[6] = (0.0f + i) * SIZE;
					fQuad[7] = (1.0f + k) * SIZE;
					fQuad[8] = (0.0f + j) * SIZE;

					fQuad[9] = (1.0f + i) * SIZE;
					fQuad[10] = (0.0f + k)  * SIZE;
					fQuad[11] = (0.0f + j) * SIZE;

					fQuad[12] = (0.0f + i) * SIZE;
					fQuad[13] = (1.0f + k) * SIZE;
					fQuad[14] = (0.0f + j) * SIZE;

					fQuad[15] = (1.0f + i) * SIZE;
					fQuad[16] = (1.0f + k) * SIZE;
					fQuad[17] = (0.0f + j) * SIZE;


					//Back
					fQuad[18] = (0.0f + i) * SIZE;
					fQuad[19] = (0.0f + k)  * SIZE;
					fQuad[20] = (1.0f + j) * SIZE;

					fQuad[21] = (1.0f + i) * SIZE;
					fQuad[22] = (0.0f + k)  * SIZE;
					fQuad[23] = (1.0f + j) * SIZE;

					fQuad[24] =(0.0f + i) * SIZE;
					fQuad[25] = (1.0f + k) * SIZE;
					fQuad[26] = (1.0f + j) * SIZE;

					fQuad[27] = (1.0f + i) * SIZE;
					fQuad[28] = (0.0f + k)  * SIZE;
					fQuad[29] = (1.0f + j) * SIZE;

					fQuad[30] = (0.0f + i) * SIZE;
					fQuad[31] = (1.0f + k) * SIZE;
					fQuad[32] = (1.0f + j) * SIZE;

					fQuad[33] = (1.0f + i) * SIZE;
					fQuad[34] = (1.0f + k) * SIZE;
					fQuad[35] = (1.0f + j) * SIZE;

					//Top
					fQuad[36] = (0.0f + i) * SIZE;
					fQuad[37] = (1.0f + k) * SIZE;
					fQuad[38] = (0.0f + j) * SIZE;

					fQuad[39] = (1.0f + i) * SIZE;
					fQuad[40] = (1.0f + k) * SIZE;
					fQuad[ 41] = (0.0f + j) * SIZE;

					fQuad[42] = (0.0f + i) * SIZE;
					fQuad[ 43] = (1.0f + k) * SIZE;
					fQuad[44] = (1.0f + j) * SIZE;

					fQuad[45] = (1.0f + i) * SIZE;
					fQuad[46] = (1.0f + k) * SIZE;
					fQuad[47] = (0.0f + j) * SIZE;

					fQuad[48] = (0.0f + i) * SIZE;
					fQuad[49] = (1.0f + k) * SIZE;
					fQuad[50] = (1.0f + j) * SIZE;

					fQuad[51] = (1.0f + i) * SIZE;
					fQuad[52] = (1.0f + k) * SIZE;
					fQuad[53] = (1.0f + j) * SIZE;
				
					//bas
					fQuad[54] = (0.0f + i) * SIZE;
					fQuad[55] = (0.0f + k)  * SIZE;
					fQuad[56] = (0.0f + j) * SIZE;

					fQuad[57] = (1.0f + i) * SIZE;
					fQuad[58] = (0.0f + k)  * SIZE;
					fQuad[59] = (0.0f + j) * SIZE;

					fQuad[60] = (0.0f + i) * SIZE;
					fQuad[61] = (0.0f + k)  * SIZE;
					fQuad[62] = (1.0f + j) * SIZE;

					fQuad[63] = (1.0f + i) * SIZE;
					fQuad[64] = (0.0f + k)  * SIZE;
					fQuad[65] = (0.0f + j) * SIZE;

					fQuad[66] = (0.0f + i) * SIZE;
					fQuad[ 67] = (0.0f + k)  * SIZE;
					fQuad[68] = (1.0f + j) * SIZE;

					fQuad[69] =(1.0f + i) * SIZE;
					fQuad[70] = (0.0f + k)  * SIZE;
					fQuad[71] = (1.0f + j) * SIZE;

					//gauche
					fQuad[72] = (0.0f + i) * SIZE;
					fQuad[73] = (0.0f + k)  * SIZE;
					fQuad[74] = (0.0f + j) * SIZE;

					fQuad[75] = (0.0f + i) * SIZE;
					fQuad[76] = (0.0f + k) * SIZE;
					fQuad[77] = (1.0f + j) * SIZE;

					fQuad[78] = (0.0f + i) * SIZE;
					fQuad[79] = (1.0f + k) * SIZE;
					fQuad[80] = (0.0f + j) * SIZE;

					fQuad[81] = (0.0f + i) * SIZE;
					fQuad[82] = (0.0f + k) * SIZE;
					fQuad[83] = (1.0f + j) * SIZE;

					fQuad[84] = (0.0f + i) * SIZE;
					fQuad[85] = (1.0f + k)  * SIZE;
					fQuad[86] = (0.0f + j) * SIZE;

					fQuad[87] = (0.0f + i) * SIZE;
					fQuad[88] = (1.0f + k)  * SIZE;
					fQuad[89] = (1.0f + j) * SIZE;

					////droite
					fQuad[90] = (1.0f + i) * SIZE;
					fQuad[91] = (0.0f + k)  * SIZE;
					fQuad[92] = (0.0f + j) * SIZE;

					fQuad[93] = (1.0f + i) * SIZE;
					fQuad[94] = (0.0f + k) * SIZE;
					fQuad[95] = (1.0f + j) * SIZE;

					fQuad[96] = (1.0f + i) * SIZE;
					fQuad[97] = (1.0f + k) * SIZE;
					fQuad[98] = (0.0f + j) * SIZE;

					fQuad[99] = (1.0f + i) * SIZE;
					fQuad[100] = (0.0f + k) * SIZE;
					fQuad[101] = (1.0f + j) * SIZE;

					fQuad[102] = (1.0f + i) * SIZE;
					fQuad[103] = (1.0f + k)  * SIZE;
					fQuad[104] = (0.0f + j) * SIZE;

					fQuad[105] = (1.0f + i) * SIZE;
					fQuad[106] = (1.0f + k)  * SIZE;
					fQuad[107] = (1.0f + j) * SIZE;

					
					glBindVertexArray(VAO[k]);
					glBindBuffer(GL_ARRAY_BUFFER,VBO[k]);
					glBufferSubData(GL_ARRAY_BUFFER,idtest,sizeof(fQuad),fQuad);
					glBindBuffer(GL_ARRAY_BUFFER,VBOTexture);
					glBufferSubData(GL_ARRAY_BUFFER,idtext,sizeof(vTex),vTex);

					

					calculNormalVertex(fQuad,idtest,k);

					//glBindBuffer(GL_ARRAY_BUFFER,VBOnormal[k]);
					//glBufferSubData(GL_ARRAY_BUFFER,idnormal,sizeof(vNormal),vNormal);
					std::fill_n(fQuad,108,0);
					std::fill_n(vNormal,36,0);
				}
			
			}
		}
	}
	//delete[] fQuad;
	//glBufferData(GL_ARRAY_BUFFER,SIZEOFQUADS * sizeof(float),fQuad,GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER,108 * sizeof(float),fQuad,GL_STATIC_DRAW);
	
}

void Map::calculNormalVertex(GLfloat *fQuad, int index, int indexVBO)
{
	//glBindVertexArray(VAO[indexVBO]);
	glBindBuffer(GL_ARRAY_BUFFER,VBOnormal[indexVBO]);

	vec3 triangleP1;
	vec3 triangleP2;
	vec3 triangleP3;

	vec3 U;
	vec3 V;
	

	for(int i = 0; i< 6 ; i++)
	{
		triangleP1 = vec3(fQuad[i*18],fQuad[i*18 + 1],fQuad[i*18 + 2]);
		triangleP2 = vec3(fQuad[i*18+3],fQuad[i*18 + 4],fQuad[i*18 + 5]);
		triangleP3 = vec3(fQuad[i*18+6],fQuad[i*18 + 7],fQuad[i*18 + 8]);

		U = triangleP2 - triangleP1;
		V = triangleP3 - triangleP1;
		
		vNormal[i*18] =  U[1] * V[2] - U[2] * V[1];
		vNormal[i*18+1] = U[2] * V[0] - U[0] * V[2];
		vNormal[i*18+2] = U[0] * V[1] - U[1] * V[0];

		if(i == 0 || i == 2 || i == 5)
		{
			vNormal[i*18] *= -1;
			vNormal[i*18+1] *= -1;
			vNormal[i*18+2] *= -1;
		}

		vNormal[i*18+3] = vNormal[i*18];
		vNormal[i*18+4] = vNormal[i*18+1];
		vNormal[i*18+5] = vNormal[i*18+2];

		vNormal[i*18+6] = vNormal[i*18];
		vNormal[i*18+7] = vNormal[i*18+1];
		vNormal[i*18+8] = vNormal[i*18+2];

		vNormal[i*18+9] = vNormal[i*18];
		vNormal[i*18+10] = vNormal[i*18+1];
		vNormal[i*18+11] = vNormal[i*18+2];

		vNormal[i*18+12] = vNormal[i*18];
		vNormal[i*18+13] = vNormal[i*18+1];
		vNormal[i*18+14] = vNormal[i*18+2];

		vNormal[i*18+15] = vNormal[i*18];
		vNormal[i*18+16] = vNormal[i*18+1];
		vNormal[i*18+17] = vNormal[i*18+2];

	}
	glBufferSubData(GL_ARRAY_BUFFER,index,sizeof(vNormal),vNormal);
}

Map::~Map(void)
{
	glDeleteBuffers(3,VBOnormal);
	glDeleteBuffers(3,VBO);
	glDeleteBuffers(3,VAO);
	glDeleteBuffers(1,&VBOTexture);
}
