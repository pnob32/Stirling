/*! \file Drawable.cpp
    \brief Source file for base drawing file... this should contain the opengl calls necessary for drawing
*/

#include "Drawable.h"

Drawable::Drawable(GLenum mode) {
    drawMode = mode;
	colorEmbedded = false;
    VAO = 0;
    VBO = 0;
    EBO = 0;
	M = glm::mat4(1.0f);
	V = glm::mat4(1.0f);
	P = glm::mat4(1.0f);
    textures.clear();
    posBuf.clear();
    norBuf.clear();
    indBuf.clear();
    colorBuf.clear();
    layoutVertexBuf.clear();
}

int Drawable::draw() {
	//shader->bind();
    // Bind Textures (if applicable)
	uint16_t activeTexture = 0x84C0;

	PPK_ASSERT_WARNING((int)textures.size() <= 16, "You have tried to load too many textures. OpenGL only supports up to 16\n");
	int texCount = (int)textures.size();
	if (texCount > 16) {
		texCount = 16;
	}
	for (int i = 0; i < texCount; ++i) {
		glActiveTexture((GLenum)activeTexture++);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		char texture[10];
		sprintf_s(texture, "texture%d", i);
		GLuint texUniform = shader->getUniform(texture);
		glUniform1i(texUniform, i);
	}

	// Get their uniform location
	GLint modelLoc = shader->getUniform("model");
	GLint viewLoc = shader->getUniform("view");
	GLint projLoc = shader->getUniform("projection");
	// Pass them to the shaders
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(V));
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(P));

	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(M));
	
    int indexCount;
    if (indBuf.size() > 0) {
        indexCount = (int) indBuf.size();
        glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    }
    else {
        indexCount = verticeCount;
        glDrawArrays(drawMode, 0, indexCount);
    }
    glBindVertexArray(0);
	//shader->unbind();

    PPK_ASSERT_WARNING(glGetError() == GL_NO_ERROR, "Problem loading layout buffer\n");
    if (glGetError != GL_NO_ERROR) {
        return -1;
    }
	
    return 1;
}

int Drawable::init() {
    return 1;
}

int Drawable::initLayout(int attribCount, int stride) {

    for (int i = 0; i < attribCount; ++i) {
        glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 
            stride * sizeof(GLfloat), (GLvoid*)(3 * i * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
    }

    glBindVertexArray(0);

    PPK_ASSERT_WARNING(glGetError() == GL_NO_ERROR, "Problem loading layout buffer\n");
    if (glGetError != GL_NO_ERROR) {
        return -1;
    }

    return 1;
}

int Drawable::setIndexBuffer(vector<GLuint> iBuf) { 
    indBuf = iBuf;

    return 1;
}

int Drawable::loadLayoutBuffer(vector<GLfloat> vertices, int size) {
    layoutVertexBuf = vertices;

    bufferType = STIRLING_TYPE_LAYOUT;
    verticeCount = size;

    //GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    if (indBuf.size() > 0) {
        glGenBuffers(1, &EBO);
    }
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    if (indBuf.size() > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(GLfloat), &indBuf[0], GL_STATIC_DRAW);
    }

    PPK_ASSERT_WARNING(glGetError() == GL_NO_ERROR, "Problem loading layout buffer\n");
    if (glGetError != GL_NO_ERROR) {
        return -1;
    }

    return 1;
}