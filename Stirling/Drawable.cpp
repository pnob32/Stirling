/*! \file Drawable.cpp
    \brief Source file for base drawing file... this should contain the opengl calls necessary for drawing
*/

#include "Drawable.h"

Drawable::Drawable(Program* p, GLenum mode) {
    shader = p;
    drawMode = mode;
    VAO = 0;
    VBO = 0;
}

int Drawable::draw() {

    glBindVertexArray(VAO);
    glDrawArrays(drawMode, 0, verticeCount);
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

int Drawable::initLayout(int attribCount) {

    for (int i = 0; i < attribCount; ++i) {
        glVertexAttribPointer(i, verticeCount, GL_FLOAT, GL_FALSE, 
            3 * attribCount * sizeof(GLfloat), (GLvoid*)(3 * i * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
    }

    glBindVertexArray(0);

    PPK_ASSERT_WARNING(glGetError() == GL_NO_ERROR, "Problem loading layout buffer\n");
    if (glGetError != GL_NO_ERROR) {
        return -1;
    }

    return 1;
}

int Drawable::loadLayoutBuffer(vector<GLfloat> vertices, int size) {
    layoutVertexBuf = vertices;

    bufferType = STIRLING_TYPE_LAYOUT;
    verticeCount = size;

    //GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    PPK_ASSERT_WARNING(glGetError() == GL_NO_ERROR, "Problem loading layout buffer\n");
    if (glGetError != GL_NO_ERROR) {
        return -1;
    }

    return 1;
}