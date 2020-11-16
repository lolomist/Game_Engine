#define STB_IMAGE_IMPLEMENTATION

#include "Engine.h";
#include "GlfwWindow.h";
#include "physics_directionalMovement.h";

int main() {
    Window* win = new GlfwWindow(1280, 720, "Engine window");
    double mouseX = 0;
    double mouseY = 0;
    double mouseOffsetX = 0;
    double mouseOffsetY = 0;

    Engine engine(win, glm::vec3(0.f));
    Camera* camera = engine.createCamera(glm::vec3(-8.0f, 10.0f, 3.0f), glm::vec3(0.f, 0.f, 0.f));
    camera->setFreeMovement(true);

    engine.setDirectionalLight(glm::vec3(0.f, 0.f, -5.f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.20f, 0.19f, 0.62f), glm::vec3(1.0f, 0.6f, 0.0f));

    Model* redCube = engine.createCube(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0), glm::vec3(1.f));
    Model* blueCube = engine.createCube(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0), glm::vec3(1.f));
    //Model* redCube = engine.createCustomModel("models/cubeGauche.obj", glm::vec3(1.0, 0.0, 0.0), glm::vec3(0., 0.0, 0.0), glm::vec3(0.0), glm::vec3(1.f));

    float emissionRate = 0.0f;
    glm::vec3 emissionColor = glm::vec3(0.0f);

    glm::vec3 cameraDir = camera->getDirection();

    float *posFloat = redCube->getVerticesFloat();
    std::vector<glm::vec3> verticesPos = redCube->getVerticesPos();

    while (engine.isWindowOpen()) {
        win->pollEvents();
        win->getMousePos(&mouseX, &mouseY);
        camera->setMousePos(mouseX, mouseY, engine.getTime());
        float dt = engine.getTime();

        if (CheckCollision(redCube->getVerticesFloat(), blueCube->getVerticesFloat()) == true) {
            std::cout << "Collision !!!!";
        }

        if (win->isKeyPressed(GLFW_KEY_ESCAPE)) {
            win->close();
        }

        if (win->isKeyPressed(GLFW_KEY_W)) {
            camera->move(10.f, FORWARD, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_A)) {
            camera->move(10.f, LEFT, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_S)) {
            camera->move(10.f, BACKWARD, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_D)) {
            camera->move(10.f, RIGHT, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_SPACE)) {
            camera->move(10.f, UP, dt);
        }

        if (win->isKeyPressed(GLFW_KEY_UP)) {
            redCube->move(10.f, FORWARD, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_LEFT)) {
            redCube->move(10.f, LEFT, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_DOWN)) {
            redCube->move(10.f, BACKWARD, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_RIGHT)) {
            redCube->move(10.f, RIGHT, dt);
        }
        if (win->isKeyPressed(GLFW_KEY_SPACE)) {
            camera->move(10.f, UP, dt);
        }

        if (win->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
            camera->move(10.f, DOWN, dt);
        }


        if (win->isKeyPressed(GLFW_KEY_ENTER)) {
            redCube->printVerticesFloat();
        }

        if (win->isKeyPressed(GLFW_KEY_RIGHT_SHIFT)) {
            blueCube->printVerticesFloat();
        }

        engine.drawObjects();
    }
    return 0;
};