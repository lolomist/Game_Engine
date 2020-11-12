//#define STB_IMAGE_IMPLEMENTATION
//
//#include "Engine.h";
//#include "GlfwWindow.h";
//#include "physics_directionalMovement.h";
//
//int main() {
//    Window* win = new GlfwWindow(1280, 720, "Engine window");
//    double mouseX = 0;
//    double mouseY = 0;
//    double mouseOffsetX = 0;
//    double mouseOffsetY = 0;
//
//    Engine engine(win, glm::vec3(0.f));
//    Camera *camera = engine.createCamera(glm::vec3(-3.0f, 8.0f, 0.0f), glm::vec3(90.f, 0.f, 90.f));
//    camera->setFreeMovement(true);
//
//    engine.setDirectionalLight(glm::vec3(0.f, 0.f, -5.f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.20f, 0.19f, 0.62f), glm::vec3(1.0f, 0.6f, 0.0f));
//
//   //Model *bigCube = engine.createCube("textures/batimentsTexture.png", "textures/cube_specular3.png","textures/neon1.png", glm::vec3(-80.f, 0.f, -80.f), glm::vec3(0.f), glm::vec3(20.f));
//   // Model *plane = engine.createCustomModel("models/synthwave_plane4.obj", "textures/ground.png", "textures/Vaporwave_Grid.png", glm::vec3(0.f, 0.f, -440.f), glm::vec3(0.f), glm::vec3(1.f), true);
//    //Model *plane2 = engine.createCustomModel("models/synthwave_plane4.obj", "textures/ground.png", "textures/Vaporwave_Grid.png", glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f), true);
//    //Model *bat1 = engine.createCustomModel("models/Batiment4.obj", "textures/ground.png", "textures/cube_specular_rec.png", "textures/neon1.png", glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f));
//    //Model *bat2 = engine.createCustomModel("models/petitBatiment4.obj", "textures/ground.png", "textures/cube_specular_rec.png", "textures/neon1.png", glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f));
//    //Model *bat1 = engine.createCustomModel("models/buildings.obj", "textures/ground.png", "textures/cube_specular_rec.png", "textures/neon1.png", glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f), glm::vec3(1.f));
//    
//    //Model* cube1 = engine.createCube(glm::vec3(1.0, 1.0, 1.0), glm::vec3(15.0, 5.f, 0.f), glm::vec3(0.0), glm::vec3(1.f));
//    
//    Model* cube1 = engine.createCube(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0), glm::vec3(1.f));
//    Model* cube2 = engine.createCustomModel("models/cubeGauche.obj",glm::vec3(1.0, 0.0,0.0), glm::vec3(0., 0.0, 0.0), glm::vec3(0.0), glm::vec3(1.f));
//
//    //std::vector<Vertex> vertex = cube2->getVertices();
//
//
//    //std::vector<Vertex>test = cube1->getVertices();
//    //std::cout << "Vertex 1 =" << test.at(0).pos.x << std::endl;
//
//    float emissionRate = 0.0f;
//    glm::vec3 emissionColor = glm::vec3(0.0f);
//
//    glm::vec3 cameraDir = camera->getDirection();
//
//    while (engine.isWindowOpen()) {
//        win->pollEvents();
//        win->getMousePos(&mouseX, &mouseY);
//        camera->setMousePos(mouseX, mouseY, engine.getTime());
//        
//        double fade = sin(glfwGetTime() * 0.1f) * 1.0f;
//        float dt = engine.getTime();
//        emissionRate = fade;
//        emissionColor.r = 1.0 * fade;
//        emissionColor.g = -1.0 * fade;
//        emissionColor.b = -0.5 * fade;
//
//        glm::vec3 pos = cube2->getPosition();
//
//        if (CheckCollision(cube1->getVerticesFloat(), cube2->getVerticesFloat()) == true) {
//            std::cout << "Collision !!!!";
//        }
//
//
//       /* std::cout << "POS X " << pos.x << std::endl;
//        std::cout << "POS Y" << pos.y << std::endl;
//        std::cout << "POS Z" << pos.z << std::endl;*/
//
//     /*   plane2->setEmissionRate(emissionRate);
//        plane2->setEmissionColor(emissionColor);
//        plane->setEmissionRate(emissionRate);
//        plane->setEmissionColor(emissionColor);
//        bigCube->setEmissionRate(emissionRate);
//        bigCube->setEmissionColor(emissionColor);
//        bat1->setEmissionRate(emissionRate);
//        bat1->setEmissionColor(emissionColor);*/
//
//        if (win->isKeyPressed(GLFW_KEY_ESCAPE)) {
//            win->close();
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_W)) {
//            //camera->move(10.f, FORWARD, dt);
//            cube2->move(10.f, FORWARD, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_A)) {
//            //obj->move(10.f, LEFT, dt);
//            //camera->move(10.f, LEFT, dt);
//            cube2->move(10.f, LEFT, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_S)) {
//            //obj->move(10.f, BACKWARD, dt);
//            //camera->move(10.f, BACKWARD, dt);
//            cube2->move(10.f, BACKWARD, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_D)) {
//            //obj->move(10.f, RIGHT, dt);
//            //camera->move(10.f, RIGHT, dt);
//            cube2->move(10.f, RIGHT, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_SPACE)) {
//            //obj->move(10.f, UP, dt);
//            //camera->move(10.f, UP, dt);
//            cube2->move(10.f, UP, dt);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_ENTER)) {
//            //obj->move(10.f, UP, dt);
//            //camera->move(10.f, UP, dt);
//            //cube1->printVerticesFloat();
//            cube2->printVerticesFloat();
//            //cube2->getVerticesFloat();
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_RIGHT_SHIFT)) {
//            cube1->printVerticesFloat();
//        }
//
//
//
//        engine.drawObjects();
//    }
//    return 0;
//};