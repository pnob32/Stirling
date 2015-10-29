/*! \file Drawable.h
    \brief Generic Draw Class
    This class is the base level of drawable objects to be sent to openGL to be rendered
*/

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "global_includes.h"
#include "Program.h"

#define STIRLING_TYPE_DISTINCT 0
#define STIRLING_TYPE_LAYOUT 1

class Drawable {
public:
    Drawable(GLenum mode);

    ~Drawable();

    /*! \fn draw - draw routine
        \return integer: 1 if ran correctly, -1 if error occured
    */
    int draw();

    /*! \fn init - initiates array/buffer objects
        \return integer: 1 if ran correctly, -1 if error occured
    */
    int init();

    /*! \fn init - initiates array/buffer objects
        \param int attribCount: number of attributes per vertex 
        \return integer: 1 if ran correctly, -1 if error occured
    */
    int initLayout(int attribCount, int stride);

    /*! \fn loadLayoutBuffer - loads vertex buffer into Drawable and instantiates class as using a layout loading method
        \param GLfloat* vertices
        \param int size: number of vertices
        \return integer: 1 if ran correctly, -1 if error occured
    */
    int loadLayoutBuffer(vector<GLfloat> vertices, int size);

    int setIndexBuffer(vector<GLuint> iBuf);

	inline void setShader(Program* _shader) { shader = _shader; }

	inline void setProjection(glm::mat4 _P) { P = _P; }
	
	inline void setView(glm::mat4 _V) { V = _V; }

	inline void setModel(glm::mat4 _M) { M = _M; }
	inline glm::mat4* getModel() { return &M; }

protected:
    vector<GLfloat> posBuf;
    vector<GLfloat> norBuf;
    vector<GLuint> indBuf;
    vector<GLint> colorBuf;

    vector<GLfloat> layoutVertexBuf;

    Program* shader;

    int verticeCount;

    vector<GLuint> textures;

    GLuint VAO, VBO, EBO;

private:
    int bufferType;

    GLenum drawMode;

	glm::mat4 P; // Projection Matrix

	glm::mat4 V; // View Matrix

	glm::mat4 M; // Model Matrix

};

#endif