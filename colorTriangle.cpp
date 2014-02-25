#include "Shaders_Init.h"
using namespace std;
int counter=0;

GLuint vaoID, vboID[2];

GLfloat vertexarray[]={0.5f,0.5f,0.0f,//vertice array
			1.0f,0.0f,0.0f,
                       1.0f,-1.0f,0.0f, 
                       0.0f,1.0f,0.0f,
                       -1.0f,1.0f,0.0f
                       };
                       
GLfloat colorarray[]={1.0f,1.0f,0.0f,1.0f,//color array
                       0.0f,1.0f,0.0f,1.0f,
                       1.0f,0.0f,0.0f,1.0f,
                       0.0f,0.0f,1.0f,1.0f
                       };                       

void init(){

  ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertex_shader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragment_shader.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);
  
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);
  
  glGenBuffers(2, vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertexarray),vertexarray,GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
  glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(colorarray),colorarray,GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void drawscene(){
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_POLYGON,0,3+(counter%6));
  glFlush();
}

void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    counter++;
    drawscene();
  }
}


int main(int argc,char ** argv){

  glutInit(&argc, argv);
  glutCreateWindow("Shapes");
  
  
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);

	init();

  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

  glutDisplayFunc(drawscene);
  glutMouseFunc(mousepress);
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}
