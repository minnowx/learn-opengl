#include "Common.h"

Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int Colors()
{
	// Init GLFW window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseEvent);
	glfwSetScrollCallback(window, scollEvent);

	// Init GLAD OpenGL Context
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		//glfwTerminate();
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};

	// Vertex Buffer Object
	unsigned int VBO, CubeVAO, LightVAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &CubeVAO);
	glGenVertexArrays(1, &LightVAO);

	// 后续针对 VBO 的操作都将绑定到该 VAO 上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(CubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(CubeVAO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(LightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	Shader CubeShader{ "resources/shader/2.1.shader.vs", "resources/shader/2.1.shader.fs" };
	Shader LightShader{ "resources/shader/2.1.shader.vs", "resources/shader/2.1.shader.light.fs" };

	glEnable(GL_DEPTH_TEST);

	glm::vec3 LightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 ObjectColor(1.0f, 0.5f, 0.31f);
	glm::vec3 LightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 CubePos(0.0f, 0.0f, 0.0f);
	// Show window
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection, model;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);
		model = glm::translate(model, CubePos);
		CubeShader.use();
		CubeShader.setMat4("view", glm::value_ptr(camera.GetViewMatrix()));
		CubeShader.setMat4("projection", glm::value_ptr(projection));
		CubeShader.setMat4("model", glm::value_ptr(model));
		CubeShader.setVec3("lightColor", glm::value_ptr(LightColor));
		CubeShader.setVec3("objectColor", glm::value_ptr(ObjectColor));
		CubeShader.setVec3("lightPos", glm::value_ptr(LightPos));
		//CubeShader.setVec3("viewPos", glm::value_ptr(camera.Position));
		glBindVertexArray(CubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		LightPos.x = 1.0f + glm::sin(glfwGetTime()) * 2.0f;
		LightPos.y = glm::sin(glfwGetTime() / 2.0f) * 1.0f;

		model = glm::mat4();
		model = glm::translate(model, LightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		LightShader.use();
		LightShader.setMat4("view", glm::value_ptr(camera.GetViewMatrix()));
		LightShader.setMat4("projection", glm::value_ptr(projection));
		LightShader.setMat4("model", glm::value_ptr(model));
		glBindVertexArray(LightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Destory
	glDeleteVertexArrays(1, &CubeVAO);
	glDeleteVertexArrays(1, &LightVAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}
