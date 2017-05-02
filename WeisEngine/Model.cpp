#include "Model.h"


//default constructor
Model::Model()
{
	//set defaults to zero
	vertArr = 0;
	vertCount = 0;
}

//default destructor
Model::~Model()
{

}

//buffer and setup the model
bool Model::buffer(std::string objFile)
{
	std::vector<glm::vec3> locations;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<VertInd> vertInds;

	//read in the obj file
	std::ifstream instream(objFile);//opens file
	if (!instream.is_open()) return false;

	std::string line;
	while (std::getline(instream, line))
	{
		std::istringstream ss(line);

		float num1, num2, num3;
		std::string label;

		//get the type of line that will be read in next
		ss >> label;


		if (label == "v")//if the line starts with a v read in three floats and use those to make a vec3 to add into vertex locations
		{
			ss >> num1 >> num2 >> num3;
			locations.push_back(glm::vec3(num1, num2, num3));
		}
		else if (label == "vt")//if the line starts with a vt read in two floats and use those to make a vec2 to add into texture/uv vertices
		{
			ss >> num1 >> num2;
			uvs.push_back(glm::vec2(num1, num2));
		}
		else if (label == "vn")//if the line starts with a vn read in three floats and use those to make a vec3 to add into vertex normals
		{
			ss >> num1 >> num2 >> num3;
			normals.push_back(glm::vec3(num1, num2, num3));
		}
		else if (label == "f")//if the line starts with f read in 3 ints separated by slashes 3 times -- each one is one of the vertices that make up a face
		{
			unsigned int vFace, vtFace, vnFace;//the location vertex, uv vertex, and normal vertex for this vertex
			char slash;//holds the slash character -- we don't do anything with this information
			for (int i = 0; i < 3; i++)
			{
				ss >> vFace >> slash >> vtFace >> slash >> vnFace;//read in the data and store it in temp variables
				vFace--;
				vtFace--;
				vnFace--;
				//store these values in an instance of the VertInd struct
				VertInd vIndex;
				vIndex.locInd = vFace; vIndex.uvInd = vtFace; vIndex.normInd = vnFace;

				//add the vertex indices to the vector
				vertInds.push_back(vIndex);
			}
		}
	}
	//close the file
	instream.close();//destructor closes it after function exits if you forget

	//open gl uses right handed coordinate system

	//connect the dots/vertices --- some engines use backface culling, so draw triangles counterclockwise so there are no issues -- already done in model
	vertCount = vertInds.size();

	//Duplicate vertices into a single buffer
	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = { locations[vertInds[i].locInd], 
							uvs[vertInds[i].uvInd], 
							normals[vertInds[i].normInd]};
	}

	///step 1: generate a buffer
	vertArr;//hold number identifying the array we are generating
	GLuint vertBuf;//hold number identifying buffer we are generating

	//open gl will create the buffers internally and return indices
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	///step 2: bind the buffer --- binding the buffer controls which one is active (the bound one is active)
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);//first parameter is the 'target' that the buffer is bound to

	///step 3: store data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertCount, &vertBufData[0], GL_STATIC_DRAW); //first param is where to copy to, 2 param is the # of bytes to copy, 
	//3 param is where to copy from, 4 param is a "hint" to OpenGL that we will never change the data --- lets it optimize the usage of the buffer

	///step 4: describe the buffer --- the computer just recieved a bunch of data, doesn't know what it relates to
	//enable the attribute
	glEnableVertexAttribArray(0); //attribute index - 0
	//set up the attribute for location
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); //1 param is the attribute index - 0 in this case, 2 param is the number of components (x, y, z)
	//3 param is the type of data, 4 param is whether or not the data should be normalized, 5 param is the stride (bytes per vertex), 6 param is the offset to this attribute

	//enable the attribute
	glEnableVertexAttribArray(1); //attribute index - 1
	//set up the attribute for uvs
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

	//enable the attribute
	glEnableVertexAttribArray(2); //attribute index - 2
	//set up the attribute for normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	//3 param is the type of data, 4 param is whether or not the data should be normalized, 5 param is the stride (bytes per vertex), 6 param is the offset to this attribute
	glBindVertexArray(0); //unbind when finished editing

	return true;
}

//draws the model to the screen
void Model::render()
{
	//render game objects
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}
