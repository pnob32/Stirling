/*! \file Drawable.h
    \brief Generic Draw Class
    This class is the base level of drawable objects to be sent to openGL to be rendered
*/

#include "global_includes.h"
#include "Program.h"

#define STIRLING_TYPE_DISTINCT 0
#define STIRLING_TYPE_LAYOUT 1

class Drawable {
public:
    Drawable(Program* p, GLenum mode);

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
    int initLayout(int attribCount);

    /*! \fn loadLayoutBuffer - loads vertex buffer into Drawable and instantiates class as using a layout loading method
        \param GLfloat* vertices
        \param int size: number of vertices
        \return integer: 1 if ran correctly, -1 if error occured
    */
    int loadLayoutBuffer(vector<GLfloat> vertices, int size);

protected:
    vector<GLfloat> posBuf;
    vector<GLfloat> norBuf;
    vector<GLint> indBuf;
    vector<GLint> colorBuf;

    vector<GLfloat> layoutVertexBuf;

    Program* shader;

    int verticeCount;

private:
    int bufferType;

    GLuint VAO, VBO;

    GLenum drawMode;

};