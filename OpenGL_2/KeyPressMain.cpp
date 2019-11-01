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


// 必須在 glewInit(); 執行完後,在執行物件實體的取得
CQuad* pPlayer; // 宣告 Quad 指標物件，結束時記得釋放
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
// 函式的原型宣告
void IdleProcess();

void init(void) {
	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	pPlayer = new CQuad();
	position = vec3();
	rotation = vec3();
	scale = vec3(1.0f);

	//  產生 projection 矩陣，此處為產生正投影矩陣
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
	glutSwapBuffers(); // 交換 Frame Buffer
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
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 ，換成 Y 軸
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:  // 目前按下的是向左方向鍵
		break;
	case GLUT_KEY_RIGHT: // 目前按下的是向右方向鍵
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
	glutKeyboardFunc(Win_Keyboard); // 處理 ASCI 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc(Win_SpecialKeyboard); // 處理 NON-ASCI 按鍵如 F1、Home、方向鍵...等等
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);

	glutMainLoop();
	return 0;
}