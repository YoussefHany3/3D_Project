#include "Angel.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float scalingFactor = 2.0f;

float cubeVertices[] = {
    -0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor, 0.0f,0.0f,-1.0f, 0.0f, 0.0f, 
     0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor, 0.0f,0.0f,-1.0f,  1.0f, 0.0f,
     0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor, 0.0f,0.0f,-1.0f,  1.0f, 1.0f,
     0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor, 0.0f,0.0f,-1.0f,  1.0f, 1.0f,
    -0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor, 0.0f,0.0f,-1.0f,  0.0f, 1.0f,
    -0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor, 0.0f,0.0f,-1.0f,  0.0f, 0.0f,
	                                                   
    -0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor, 0.0f,0.0f,1.0f,  0.0f, 0.0f,//front
     0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor, 0.0f,0.0f,1.0f, 1.0f, 0.0f,
     0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor, 0.0f,0.0f,1.0f, 1.0f, 1.0f,
     0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor, 0.0f,0.0f,1.0f, 1.0f, 1.0f,
    -0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor, 0.0f,0.0f,1.0f, 0.0f, 1.0f,
    -0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor, 0.0f,0.0f,1.0f, 0.0f, 0.0f,
                                                       
    -0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor, -1.0f,0.0f,0,  1.0f, 0.0f,//left
    -0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor, -1,0,0,  1.0f, 1.0f,
    -0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor, -1,0,0,  0.0f, 1.0f,
    -0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor, -1,0,0,  0.0f, 1.0f,
    -0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor, -1,0,0,  0.0f, 0.0f,
    -0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor, -1,0,0,  1.0f, 0.0f,
                                                       
     0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor,  1,0,0,  1.0f, 0.0f,//right
     0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor,  1,0,0,  1.0f, 1.0f,
     0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor,  1,0,0,  0.0f, 1.0f,
     0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor,  1,0,0,  0.0f, 1.0f,
     0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor,  1,0,0,  0.0f, 0.0f,
     0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor,  1,0,0,  1.0f, 0.0f,
                                                       
    -0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor,  0,-1,0, 0.0f, 1.0f,//bottom
     0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor,  0,-1,0, 1.0f, 1.0f,
     0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor,  0,-1,0, 1.0f, 0.0f,
     0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor,  0,-1,0, 1.0f, 0.0f,
    -0.5f *scalingFactor, -0.5f * scalingFactor,  0.5f * scalingFactor,  0,-1,0, 0.0f, 0.0f,
    -0.5f *scalingFactor, -0.5f * scalingFactor, -0.5f * scalingFactor,  0,-1,0, 0.0f, 1.0f,
                                                       
    -0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor,  0,1,0, 0.0f, 1.0f,//top
     0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor,  0,1,0, 1.0f, 1.0f,
     0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor,  0,1,0, 1.0f, 0.0f,
     0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor,  0,1,0, 1.0f, 0.0f,
    -0.5f *scalingFactor,  0.5f * scalingFactor,  0.5f * scalingFactor,  0,1,0, 0.0f, 0.0f,
    -0.5f *scalingFactor,  0.5f * scalingFactor, -0.5f * scalingFactor,  0,1,0, 0.0f, 1.0f
};

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
typedef Angel::vec3  point3;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distribution(1, 20);

int startTime = time(NULL);
int endTime;

int index = 0;

float tx[20];
float ty[20];
float tz[20];
float fuel = 20.0f;

float tx2[10];
float ty2[10];
float tz2[10];


bool isend = false;

Sphere sphere1(0.5f);
float speed = 0.1f, yaw = -90.0f;
GLuint program, vao, vbo1, ibo1, texture_back, texture_front, texture_top, texture_bottom, vTexture, vPosition, vNormal, modelUnifrom, modelAttrib, viewUniform, projectionUniform, cameraUniform;
GLuint vbo2, texture_ship, texture_fuel, texture_spikes;
glm::mat4 model;

glm::vec3 cameraPos, cameraTarget, cameraDirection, cameraRight, cameraUp, cameraFront;
glm::mat4 view, projection;

int random(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
void initLight()
{
    point4 light_direction(0.0, 0.0, -1.0, 0.0);

    color4 light_ambient(1.0, 1.0, 1.0, 1.0);
    color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
    color4 light_specular(1.0, 1.0, 1.0, 1.0);

    float material_shininess = 100.f;
    color4 material_ambient(0.5, 0.5, 0.5, 1.0);
    color4 material_diffuse(0.5, 0.5, 0.5, 1.0);
    color4 material_specular(0.5, 0.5, 0.5, 1.0);

    glUniform4fv(glGetUniformLocation(program, "directionalLight.ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "directionalLight.diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "directionalLight.specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "directionalLight.direction"), 1, light_direction);

    glUniform4fv(glGetUniformLocation(program, "material.ambient"), 1, material_ambient);
    glUniform4fv(glGetUniformLocation(program, "material.diffuse"), 1, material_diffuse);
    glUniform4fv(glGetUniformLocation(program, "material.specular"), 1, material_specular);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), material_shininess);
}
void initTexture()
{
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &texture_back);
    glBindTexture(GL_TEXTURE_2D, texture_back);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, channels;


    unsigned char* data1 = stbi_load("skfront.jpg", &width, &height, &channels, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data1);
     //front
    glGenTextures(1, &texture_front);
    glBindTexture(GL_TEXTURE_2D, texture_front);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    

    unsigned char* data2 = stbi_load("skfront.jpg", &width, &height, &channels, 0);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data2);
    //top
    glGenTextures(1, &texture_top);
    glBindTexture(GL_TEXTURE_2D, texture_top);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data3 = stbi_load("skfront.jpg", &width, &height, &channels, 0);
    if (data3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data3);
    glGenTextures(1, &texture_bottom);
    glBindTexture(GL_TEXTURE_2D, texture_bottom);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data4 = stbi_load("skfront.jpg", &width, &height, &channels, 0);
    if (data4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data4);
    //ship
    glGenTextures(1, &texture_ship);
    glBindTexture(GL_TEXTURE_2D, texture_ship);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data5 = stbi_load("SPACECRAFT.jpg", &width, &height, &channels, 0);
    if (data5)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data5);
    //fuel
    glGenTextures(1, &texture_fuel);
    glBindTexture(GL_TEXTURE_2D, texture_fuel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data6 = stbi_load("fuel.jpg", &width, &height, &channels, 0);
    if (data6)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data6);
	
    //spikes
    glGenTextures(1, &texture_spikes);
    glBindTexture(GL_TEXTURE_2D, texture_spikes);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data7 = stbi_load("metal.jpg", &width, &height, &channels, 0);
    if (data7)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data7);
}


void randomsphere()
{
    tx[0] = 0.0f;
    ty[0] = 0.0f;
    tz[0] = 0.1f;
    for (int i = 1; i < 20; i++)
    {
        int r;
        std::random_device rdd;
        std::mt19937 gen(rdd());
        std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

        r = random(0, 1);
        if (r == 0)
        {
            tx[i] = distribution(gen) * -1;
        }
        else
        {
            tx[i] = distribution(gen);
        }
        r = random(0, 1);
        if (r == 0)
        {
            ty[i] = distribution(gen) * -1;
        }
        else
        {
            ty[i] = distribution(gen);
        }
        r = random(0, 1);
        if (r == 0)
        {
            tz[i] = distribution(gen) * -1;
        }
        else
        {
            tz[i] = distribution(gen);
        }
    }
    for (int i = 0; i < 10; i++)
    {
        int r;
        std::random_device rdd;
        std::mt19937 gen(rdd());
        std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

        r = random(0, 1);
        if (r == 0)
        {
            tx2[i] = distribution(gen) * -1;
        }
        else
        {
            tx2[i] = distribution(gen);
        }
        r = random(0, 1);
        if (r == 0)
        {
            ty2[i] = distribution(gen) * -1;
        }
        else
        {
            ty2[i] = distribution(gen);
        }
        r = random(0, 1);
        if (r == 0)
        {
            tz2[i] = distribution(gen) * -1;
        }
        else
        {
            tz2[i] = distribution(gen);
        }
    }
}


void init()
{
    // Create a vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and initialize a vertex buffer object
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sphere1.getInterleavedVertexSize(), sphere1.getInterleavedVertices(), GL_STATIC_DRAW);

    // Create and initialize an index buffer object
    glGenBuffers(1, &ibo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere1.getIndexSize(), sphere1.getIndices(), GL_STATIC_DRAW);


    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Load shaders and use the resulting shader program
    program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);
    // set up vertex arrays
    vPosition = glGetAttribLocation(program, "vertexPosition");
    glEnableVertexAttribArray(vPosition);

    vNormal = glGetAttribLocation(program, "vertexNormal");
    glEnableVertexAttribArray(vNormal);

    vTexture = glGetAttribLocation(program, "vertexTexture");
    glEnableVertexAttribArray(vTexture);

    modelUnifrom = glGetUniformLocation(program, "model");
    viewUniform = glGetUniformLocation(program, "view");
    projectionUniform = glGetUniformLocation(program, "projection");
    cameraUniform = glGetUniformLocation(program, "camera");

    cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    projection = glm::perspective(glm::radians(45.f), 512.0f / 512.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

    initLight();
    initTexture();
    randomsphere();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

float new_pos_x[20];
float new_pos_y[20];
float new_pos_z[20];

void draw_sphere(float sx, float sy, float sz, float tx, float ty, float z,int i)
{
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(sx, sy, sz));
    model = glm::translate(model, glm::vec3(tx, ty, z));
    glm::vec3 position = glm::vec3(model[3]);
    new_pos_x[i] = position.x;
    new_pos_y[i] = position.y;
    new_pos_z[i] = position.z;
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
}


void drawskybox(glm::mat4* view)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glm::mat4 Null_val;

    ///back
    glBindTexture(GL_TEXTURE_2D, texture_back);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    Null_val = glm::mat4(glm::mat3(*view));
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(Null_val));
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 12);

    ////front
    glBindTexture(GL_TEXTURE_2D, texture_front);
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 12, 12);

    //top
    glBindTexture(GL_TEXTURE_2D, texture_top);
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 20, 6);

    //bottom
    glBindTexture(GL_TEXTURE_2D, texture_bottom);
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 30, 6);

}

bool checkCollision(float x1, float y1, float z1, float radius1, float x2, float y2, float z2, float radius2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dz = z1 - z2;

    float distanceSquared = dx * dx + dy * dy + dz * dz;
    float radiiSumSquared = (radius1 + radius2) * (radius1 + radius2);

    return distanceSquared < radiiSumSquared;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(cameraUniform, 1, glm::value_ptr(cameraPos));
    glBindTexture(GL_TEXTURE_2D, texture_fuel);    
    for (int i = 0; i < 20; i++)
    {        
        draw_sphere(0.3f, 0.3f, 0.2f, tx[i], ty[i], tz[i],i);

        if (checkCollision(cameraPos.x+cameraFront.x, cameraPos.y+cameraFront.y, cameraPos.z+cameraFront.z, 0.1f,
            new_pos_x[i], new_pos_y[i], new_pos_z[i], 0.1f))
        {                       
           tx[i] = distribution(gen);
           ty[i] = distribution(gen);
           tz[i] = 0.1f;
           fuel += 1.0f;
           index++;
           break;
        }
    }
    glBindTexture(GL_TEXTURE_2D, texture_spikes);
    for (int i = 0; i < 10; i++)
    {
        draw_sphere(0.1f, 0.1f, 0.1f, tx2[i], ty2[i], tz2[i], i);

        if (checkCollision(cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, cameraPos.z + cameraFront.z, 0.1f,
            new_pos_x[i], new_pos_y[i], new_pos_z[i], 0.1f))
        {
            tx2[i] = distribution(gen);
            ty2[i] = distribution(gen);
            tz2[i] = 0.1f;
            isend = true;
            break;
        }
    }

    drawskybox(&view);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBindTexture(GL_TEXTURE_2D, texture_ship);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sphere1.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, sphere1.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, sphere1.getInterleavedStride(), (void*)(6 * sizeof(float)));

    ///// camera 3d
    view = glm::mat4(1.0f);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, -0.1f, -0.5f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.7f));    
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
    model = glm::rotate(model,90.f, glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));    
    glDrawElements(GL_TRIANGLES, sphere1.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glutSwapBuffers();
}

void idle() {
    
    if (fuel < 0.0f)
    {
        isend = true;
    }
    if (isend)
    {
        endTime = time(NULL);
        std::cout << "score:" << index << " you lose" << std::endl;
        std::cout << "time:" << endTime - startTime <<" sec"<< std::endl;
        glutLeaveMainLoop();
    }
    else
    {
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033:
        exit(EXIT_SUCCESS);
        break;

    case 'r':
        if (fuel > 0.0f)
        {
            cameraPos += speed * cameraUp;
            fuel -= 0.1f;
        }
        break;

    case 'f':
        if (fuel > 0.0f)
        {
            cameraPos -= speed * cameraUp;
            fuel -= 0.1f;
        }        
        break;

    case 'w':
        if (fuel > 0.0f)
        {
            cameraPos += speed * cameraFront;
            fuel -= 0.1f;
        }        
        break;

    case 's':
        if (fuel > 0.0f)
        {
            cameraPos -= speed * cameraFront;
            fuel -= 0.1f;
        }        
        break;

    case 'a':
        if (fuel > 0.0f)
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
            yaw -= 5.0f;
            cameraDirection.x = glm::cos(glm::radians(yaw));
            cameraDirection.z = glm::sin(glm::radians(yaw));
            cameraFront = glm::normalize(cameraDirection);
            fuel -= 0.1f;
        }        
        break;

    case 'd':
        if (fuel > 0.0f)
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
            yaw += 5.0f;
            cameraDirection.x = glm::cos(glm::radians(yaw));
            cameraDirection.z = glm::sin(glm::radians(yaw));
            cameraFront = glm::normalize(cameraDirection);
            fuel -= 0.1f;
        }        
        break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Title");

    glewInit();

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
