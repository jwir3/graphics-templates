#include "GLContext.h"

// #include <vector>

using namespace std;

GLContext::GLContext(int screenW, int screenH)
  : mLastMouseX(screenW/2.0), mLastMouseY(screenH/2.0) {
    initGL(screenW, screenH);
}

void GLContext::initGL(int screenW, int screenH) {
    // Initialise GLFW
	if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
		exit(-1);
	}

    // Enable 4x MSAA.
	glfwWindowHint(GLFW_SAMPLES, 4);

	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
	mWindow = glfwCreateWindow(screenW, screenH, "OpenGL Project", NULL, NULL);
	if (mWindow == NULL) {
        cerr << "Failed to open GLFW Window." << endl;
		glfwTerminate();
        exit(-1);
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	GLenum glewInitErr = glewInit();
	if (glewInitErr != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
		glfwTerminate();
        exit(-1);
	} else if (!GLEW_VERSION_4_1) {
		cerr << "OpenGL API V 4.1 is not supported" << endl;
	}

	// Ensure we can capture the mouse input by not displaying the cursor but capturing it.
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
}

GLContext::~GLContext() {
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void GLContext::setScene(Scene* s) {
	// cout << "Setting scene..." << endl;
	mScene = s;

	GLContext* myContext = this;
    glfwSetWindowUserPointer(getWindow(), myContext);

    auto keyCallbackFunc = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        static_cast<GLContext*>(glfwGetWindowUserPointer(w))->keyCallback(key, scancode, action, mods);
    };

	auto mouseCallbackFunc = [](GLFWwindow* w, double xpos, double ypos) {
		static_cast<GLContext*>(glfwGetWindowUserPointer(w))->mouseCallback(xpos, ypos);
	};

	// Don't initialize the key or mouse callbacks until the scene is initialized, since it depends on the camera
	glfwSetKeyCallback(getWindow(), keyCallbackFunc);
	glfwSetCursorPosCallback(getWindow(), mouseCallbackFunc);

	// cout << "Done setting scene" << endl;
}

void GLContext::initiateRenderLoop(void (*draw) ()) {
	if (mScene == NULL) {
		cerr << "WARNING: Attempted to initiate render loop before scene was loaded! This will silently return." << endl;
		return;
	}

	do {
        draw();

		// Swap buffers
		glfwSwapBuffers(getWindow());
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS
           && glfwWindowShouldClose(getWindow()) == 0 );
}

void GLContext::keyCallback(int key, int scancode, int action, int mods) {
	// TODO: It would be cool if we could eliminate GLContext's dependency on the scene. Ultimately,
	//       all we really need is the screen width and height to create the window.
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_W) {
			mScene->getCamera()->strafeForward();
		} else if (key == GLFW_KEY_S) {
			mScene->getCamera()->strafeBackward();
		} else if (key == GLFW_KEY_D) {
			mScene->getCamera()->strafeRight();
		} else if (key == GLFW_KEY_A) {
			mScene->getCamera()->strafeLeft();
		} else if (key == GLFW_KEY_LEFT) {
			mScene->getCamera()->gazeLeftRight(1);
		} else if (key == GLFW_KEY_RIGHT) {
			mScene->getCamera()->gazeLeftRight(-1);
		} else if (key == GLFW_KEY_UP) {
			mScene->getCamera()->gazeUpDown(1);
		} else if (key == GLFW_KEY_DOWN) {
			mScene->getCamera()->gazeUpDown(-1);
		}
	}
}

void GLContext::mouseCallback(double xPos, double yPos) {
	double differenceX = xPos - mLastMouseX;
	double differenceY = yPos - mLastMouseY;

	float sensitivity = 0.1f;
	differenceX *= sensitivity;
	differenceY *= sensitivity;

	mScene->getCamera()->gazeLeftRight(differenceX);
	mScene->getCamera()->gazeUpDown(differenceY);
	mLastMouseX = xPos;
	mLastMouseY = yPos;
}