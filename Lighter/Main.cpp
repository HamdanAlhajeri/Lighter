#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	// Initialize glfw
	glfwInit();

	// Tell glfw what OpenGL verision we're using in this case it's 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Tell glfw to use the core (mordern) features of OpenGL and ignore compatibility (modern & outdated) features of OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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

	glViewport(0, 0, w, h);

	// Set a color :)
	glClearColor(0.212f, 0.016f, 0.322f, 1.0f);
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
		// Tell glfw to process the events (not sure what that means at the moment)
		// TODO: what does this part mean
		glfwPollEvents();
	}

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