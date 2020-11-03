#define STB_IMAGE_IMPLEMENTATION
#include "Engine.h";
#include "GlfwWindow.h";

void keyEvents(Window *window, SceneObject *obj) {
    if (window->isKeyPressed(GLFW_KEY_ESCAPE)) {
        window->close();
    }

    if (window->isKeyPressed(GLFW_KEY_W)) {
        obj->move(0.1f, FORWARD);
    }
    if (window->isKeyPressed(GLFW_KEY_A)) {
        obj->move(0.1f, LEFT);
    }
    if (window->isKeyPressed(GLFW_KEY_S)) {
        obj->move(0.1f, BACKWARD);
    }
    if (window->isKeyPressed(GLFW_KEY_D)) {
        obj->move(0.1f, RIGHT);
    }
}

int main() {
    Window* win = new GlfwWindow(1280, 720, "Engine window");

    Engine engine(win);

    Camera camera = engine.createCamera(glm::vec3(0.f, 3.5f, -6.5f), glm::vec3(-25.f, 0.f, 90.f));

    SceneObject *vikingRoom = engine.createObject("models/viking_room.obj", "textures/viking_room.png", glm::vec3(15.5f, 0.0f, 0.5f), glm::vec3(-90.0f, 0.f, 180.f), glm::vec3(10.f));
    SceneObject *book = engine.createObject("models/book.obj", "textures/book.png", glm::vec3(-2.5f, 0.0f, -0.5f), glm::vec3(0.0f), glm::vec3(1.f));
    SceneObject *box = engine.createObject("models/box.obj", "textures/box.jpg", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.f));
    SceneObject *spaceShip = engine.createObject("models/spaceship.obj", "textures/spaceship1.jpg", glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.5f), camera);

    while (engine.isWindowOpen()) {
        win->pollEvents();
        keyEvents(win, spaceShip);
        engine.drawObjects();
    }
    return 0;
};