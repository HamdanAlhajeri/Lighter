#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// This is our vertex shaders (Given for now no explaination will be explained later)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);\n"
"}\n\0";


int main() {
	// Initialize glfw
	glfwInit();

	// Tell glfw what OpenGL verision we're using in this case it's 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Tell glfw to use the core (mordern) features of OpenGL and ignore compatibility (modern & outdated) features of OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Now we need shaders
	// In OpenGL shaders are objects that can only be accessed through refrences, ALL OpenGL objects are accessed through refrences


	// Create a window
	// GLFWwindow* is the datatype for a window (pointer?)
	// window is varible name
	// glfwCreateWidnow create the window taking 5 inputs width, height, window name, Fullscreen or not and the Last thing is share (if it shares resoruces with other windows)
	

	// 16:9 aspect ratios are 1280x720 1920x1080 
	int w = 1280;
	int h = 720;
	GLFWwindow* window = glfwCreateWindow(w, h, "Lighter", NULL, NULL);

	// Error checking if the window is not found
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Now we tell glfw to ACTUALLY use the window we made
	glfwMakeContextCurrent(window);

	// Here we will tell Glad to load neccarry functionality
	gladLoadGL();

	// This checks if glad loaded
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, w, h);

	// Here we will store our vertex shader 
	// Gluint is OpenGL's version of an unsigned integer
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// We are attaching our shader (refernce line 6) 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Since the gpu can't understand our code, we have to compile it from now into machine code
	glCompileShader(vertexShader);

	// Now we do the same thing but with the fragment shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Now we have to wrap the vertex and fragment shaders into a shader program
	GLuint shaderProgram = glCreateProgram();
	// We will attach our shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Now we will wrap everything up to be sent off
	glLinkProgram(shaderProgram);

	// Now we will clean up the memory by deleting vertex and fragment shaders since they are already being stored in shaderProgram variable
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Make an array of GLfloat since 
	// These are the coordiantes

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Bottom left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Bot right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Top Corner
	};

	/*
		Now we will have to move data from the CPU -> GPU and since moving that information is slow we will do it in big batches
		These big batches are also refered to as buffers (Not to be confused with the front and back buffers
	*/
	// VBO is usually an array of objects but for now we have only one object so it can be a singular instead of an array
	// VAOs store pointers to diffrent VBOs and tells OpenGL how to interpret them and be able to quickly switch between diffrent VBOs
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object
	glBindVertexArray(VAO);

	// In OpenGL we can bind objects which means a 'certain' object becomes the current object  
	// Whenever a function is called it means it the current object we be the subject of the function's actions
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* 
		We will now store our verticies in VBO
		for the 4th parameter refrence https://registry.khronos.org/OpenGL-Refpages/gl4/ 
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// A vertex attribute communicates with a vertext shader from the outside
	glVertexAttribPointer(0, 3, GL_FLOAT,  GL_FALSE, 3 * sizeof(float), (void*)0);

	// Now we need to enable the vertex attribute
	glEnableVertexAttribArray(0);

	// Extra
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Set a color :)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clear the back buffer
	glClear(GL_COLOR_BUFFER_BIT);

	/*
		Frames are usually swapping between the front and back buffers constantly to give the illusion of
		motion, when one of the buffers is displayed the other is being processed.

		Now we have 2 buffers the front and back
		the back buffer is the one we set just now in glClearColor 
		and the front buffer at this moment the defualt frame (white initally)
		so we want to display our back buffer

		to do that we will use the glfwSwapBuffers function
	*/
	glfwSwapBuffers(window);



	// Now that we actually have the window it's appearing then disappearing so we create a loop tell the program to keep the window up until we don't want it anymore
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Updates the old frams
		glfwSwapBuffers(window);
		// Tell glfw to process the events (not sure what that means at the moment)
		// TODO: what does this part mean
		glfwPollEvents();
	}


	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	// Destory the window after it's not in use
	glfwDestroyWindow(window);
	// Terminate glfw after the session ends
	glfwTerminate();
	return 0;



	/*
		Thoughts:
			Why are function names soooo long
	*/
}