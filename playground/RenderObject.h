#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Point.h"
#include "Triangle.h"

class RenderObject {

public:
    RenderObject();

    virtual ~RenderObject();

    void InitializeVAO();

    void SetVertices(std::vector<glm::vec3>);

    void SetNormals(std::vector<glm::vec3>);

    void SetTexture(std::vector<glm::vec2>, GLubyte textureData[]);

    void SetTexture(std::vector<glm::vec2>, const std::string &bmpPath);

    void DrawObject() const;


    GLuint VertexArrayID{};
    int VertexBufferSize{};

    glm::mat4 model;

    GLuint vertexBuffer{};
    GLuint normalBuffer{};

    GLuint uvBuffer{};
    GLuint texID{};
    GLuint textureSamplerID{};

    static void computeTrianglesVertices(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals);

    static std::vector<glm::vec3> getTriangleNormals(Point vertex, const std::vector<Triangle> &triangles);

    static glm::vec3 calculateMeanVector(const std::vector<glm::vec3> &);

};

#endif