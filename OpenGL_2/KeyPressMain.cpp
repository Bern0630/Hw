#include "Common\CQuad.h"
#include "Common\CQuadEX1.h"
#include "Header\Angel.h"


//For move
#define wKey 119
#define aKey 97
#define sKey 115
#define dKey 100
//For rotation
#define qKey 113
#define eKey 101
//For Scale
#define mKey 109
#define nKey 110
//Function Key
#define SPACE_KEY 32


// �����b glewInit(); ���槹��,�b���檫����骺���o
CQuad* pPlayer; // �ŧi Quad ���Ъ���A�����ɰO�o����
vec3 position;
vec3 rotation;
vec3 scale;
vec3 nPos;
vec3 nRot;
vec3 nScl;
//Input input = Input();
const float POS_VEL = 10000.0f;
const float ROT_VEL = 15000.0f;
const float SCL_VEL = 100.0f;

// For Model View and Projection Matrix
mat4 matModelView(1.0f);
mat4 matProjection;

bool bUpdateTRS = false;
//----------------------------------------------------------------------------
// �禡���쫬�ŧi
void IdleProcess();

void init(void) {
	// �����b glewInit(); ���槹��,�b���檫����骺���o
	pPlayer = new CQuad();
	position = vec3();
	rotation = vec3();
	scale = vec3(1.0f);

	//  ���� projection �x�}�A���B�����ͥ���v�x�}
	matProjection = Ortho(-20.0f, 20.0f, -20.0f, 20.0f, -2.0f, 2.0f);
	pPlayer->SetShader(matModelView, matProjection);

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}

//----------------------------------------------------------------------------


void UpdateTRS(float delta) {
	position += nPos * delta;
	rotation += nRot * delta;
	scale += nScl * delta;
	mat4 trsMat;
	trsMat = Translate(position);
	trsMat = trsMat * RotateZ(rotation.z);
	trsMat = trsMat * Scale(scale);
	bUpdateTRS = false;
	pPlayer->SetTRSMatrix(trsMat);
}

void GL_Display(void) {
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	pPlayer->Draw();
	glutSwapBuffers(); // �洫 Frame Buffer
}

void onFrameMove(float delta) {
	//Update(delta);
	if (bUpdateTRS)UpdateTRS(delta);
	GL_Display();
}

//----------------------------------------------------------------------------
void reset() {
	bUpdateTRS = false;
	position = vec3();
	rotation = vec3();
	scale = vec3(1.0f);
}
//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y) {
	nPos = vec3();
	nRot = vec3();
	nScl = vec3();
	switch (key) {
	case wKey:
		nPos.y += POS_VEL;
		bUpdateTRS = true;
		break;
	case sKey:
		nPos.y -= POS_VEL;
		bUpdateTRS = true;
		break;
	case aKey:
		nPos.x -= POS_VEL;
		bUpdateTRS = true;
		break;
	case dKey:
		nPos.x += POS_VEL;
		bUpdateTRS = true;
		break;
	case nKey:
		nRot.z += ROT_VEL;
		bUpdateTRS = true;
		break;
	case mKey:
		nRot.z -= ROT_VEL;
		bUpdateTRS = true;
		break;
	case eKey:
		nScl.x += SCL_VEL;
		nScl.y += SCL_VEL;
		bUpdateTRS = true;
		break;
	case qKey:
		nScl.x -= SCL_VEL;
		nScl.y -= SCL_VEL;
		bUpdateTRS = true;
		break;
	case 072:
		reset();
		break;
	case 033:
		delete pPlayer;
		exit(EXIT_SUCCESS);
		break;
	}
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // �ثe���U���O�ƹ�����
		break;
	case GLUT_MIDDLE_BUTTON:  // �ثe���U���O�ƹ����� �A���� Y �b
		break;
	case GLUT_RIGHT_BUTTON:   // �ثe���U���O�ƹ��k��
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:  // �ثe���U���O�V����V��
		break;
	case GLUT_KEY_RIGHT: // �ثe���U���O�V�k��V��
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Momoko Momoko Momoko");

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMouseFunc(Win_Mouse);
	glutKeyboardFunc(Win_Keyboard); // �B�z ASCI ����p A�Ba�BESC ��...����
	glutSpecialFunc(Win_SpecialKeyboard); // �B�z NON-ASCI ����p F1�BHome�B��V��...����
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}