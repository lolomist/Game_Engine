//#define STB_IMAGE_IMPLEMENTATION
//
//#include "Engine.h";
//#include "GlfwWindow.h";
//
//void keyEvents(Window* window, Model* obj, Camera* camera, float dt) {
//
//}
//
//int main() {
//    Window* win = new GlfwWindow(1280, 720, "Engine window");
//    double mouseX = 0;
//    double mouseY = 0;
//    double mouseOffsetX = 0;
//    double mouseOffsetY = 0;
//
//    glm::vec3 cubePositions[] = {
//        glm::vec3(0.0f,  0.0f,  0.0f),
//        glm::vec3(2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-3.7f,  3.0f, -7.5f),
//        glm::vec3(-1.3f, -2.0f, -2.5f),
//        glm::vec3(-5.5f,  2.0f, -2.5f),
//        glm::vec3(1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    Engine engine(win, glm::vec3(0.f));
//    //glm::vec3(0.16f, 0.f, 0.7f)
//    Camera* camera = engine.createCamera(glm::vec3(-3.0f, 8.0f, -10.0f), glm::vec3(90.f, 0.f, 90.f));
//    camera->setFreeMovement(true);
//
//    engine.setDirectionalLight(glm::vec3(15.f, 0.f, -0.f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.20f, 0.19f, 0.62f), glm::vec3(1.0f, 0.6f, 0.0f));
//
//    //engine.createPointLight(glm::vec3(0.7f, 0.2f, -82.0f), glm::vec3(1.0f, 0.6f, 0.0f), 1.0f, 0.09f, 0.032f, true);
//    engine.createSpotLight(glm::vec3(26.f, 4.f, 0.f), glm::vec3(15.f, -1.0f, -0.f), glm::vec3(1.0f, 0.f, 0.f), 1.0f, 0.09f, 0.032, glm::cos(glm::radians(35.5f)), glm::cos(glm::radians(37.5f)), true);
//    /* engine.createPointLight(glm::vec3(2.3f, -3.3f, -4.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f, true);
//     engine.createPointLight(glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(1.0f, 1.0, 0.0), 1.0f, 0.09f, 0.032f, true);
//     engine.createPointLight(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.2f, 0.2f, 1.0f), 1.0f, 0.09f, 0.032f, true);*/
//
//     /* SpotLight* TorchLight = engine.createSpotLight(camera->getPosition(), camera->getFront(), glm::vec3(0.f), 1.0f, 0.09f, 0.032, glm::cos(glm::radians(32.5f)), glm::cos(glm::radians(37.5f)), false);
//      engine.createSpotLight(glm::vec3(10.f, 4.f, 0.f), glm::vec3(-0.f, -1.0f, -0.f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032, glm::cos(glm::radians(35.5f)), glm::cos(glm::radians(37.5f)), true);
//      engine.createSpotLight(glm::vec3(16.f, 4.f, 0.f), glm::vec3(-0.f, -1.0f, -0.f), glm::vec3(0.f, 1.f, 0.f), 1.0f, 0.09f, 0.032, glm::cos(glm::radians(35.5f)), glm::cos(glm::radians(37.5f)), true);
//      engine.createSpotLight(glm::vec3(21.f, 4.f, 0.f), glm::vec3(-0.f, -1.0f, -0.f), glm::vec3(0.0f, 0.f, 1.f), 1.0f, 0.09f, 0.032, glm::cos(glm::radians(35.5f)), glm::cos(glm::radians(37.5f)), true);
//      engine.createSpotLight(glm::vec3(26.f, 4.f, 0.f), glm::vec3(-0.f, -1.0f, -0.f), glm::vec3(1.0f, 0.f, 0.f), 1.0f, 0.09f, 0.032, glm::cos(glm::radians(35.5f)), glm::cos(glm::radians(37.5f)), true);
//
//      engine.createPointLight(glm::vec3(10.f, 4.f, 5.f), glm::vec3(1.0f, 0.6f, 0.0f), 1.0f, 0.09f, 0.032f, true);
//      engine.createPointLight(glm::vec3(16.f, 4.f, 10.f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f, true);
//      engine.createPointLight(glm::vec3(21.f, 4.f, 15.f), glm::vec3(1.0f, 1.0, 0.0), 1.0f, 0.09f, 0.032f, true);
//      engine.createPointLight(glm::vec3(26.f, 4.f, 20.f), glm::vec3(1.0f, 1.0, 0.0), 1.0f, 0.09f, 0.032f, true);*/
//
//      /*engine.createCube(glm::vec3(0.f, 0.f, 1.f), glm::vec3(-3.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f));
//      engine.createCube("textures/cube.png", glm::vec3(0.f, 3.f, 0.f), glm::vec3(0.f), glm::vec3(1.f));*/
//
//    Model* bigCube = engine.createCube("textures/batimentsTexture.png", "textures/cube_specular3.png", "textures/neon1.png", glm::vec3(50.f, 10.f, 0.f), glm::vec3(0.f), glm::vec3(20.f));
//
//    /* for (unsigned int i = 0; i < 10; i++) {
//         float angle = 20.f * i;
//         engine.createCube("textures/cube.png", "textures/cube specular.png", cubePositions[i], glm::vec3(angle), glm::vec3(1.f));
//     }*/
//
//    engine.createCustomModel("models/viking_room.obj", "textures/viking_room.png", glm::vec3(-10.f, 0.f, 0.f), glm::vec3(-90.f, 0.f, 0.f), glm::vec3(50.f));
//
//    //engine.createCustomModel("models/synthwave_plane.obj", "textures/batimentsTexture.png", "textures/synthwave_specular2.png", "textures/Vaporwave_Grid.png", glm::vec3(0.f, 0.f, -80.f), glm::vec3(0.f), glm::vec3(1.f));
//    //Model *plane = engine.createCustomModel("models/synthwave_plane.obj", "textures/batimentsTexture.png", "textures/synthwave_specular2.png", "textures/Vaporwave_Grid.png", glm::vec3(0.f, 0.f, -80.f), glm::vec3(0.f), glm::vec3(1.f));
//    //Model *plane = engine.createCustomModel("models/synthwave_plane.obj", "textures/ground.png", "textures/synthwave_specular4.png", "textures/Vaporwave_Grid.png", glm::vec3(0.f, 0.f, -80.f), glm::vec3(0.f), glm::vec3(1.f));
//    Model* plane = engine.createCustomModel("models/synthwave_plane.obj", "textures/ground.png", "textures/Vaporwave_Grid.png", glm::vec3(0.f, 0.f, -80.f), glm::vec3(0.f), glm::vec3(1.f), true);
//
//
//    float emissionRate = plane->getEmissionRate();
//    glm::vec3 emissionColor = plane->getEmissionColor();
//    //emissionColor.r = 1.0f;
//    //emissionColor.g = 0.0f;
//    //emissionColor.b = 1.0f;
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
//        plane->setEmissionRate(emissionRate);
//        plane->setEmissionColor(emissionColor);
//        bigCube->setEmissionRate(emissionRate);
//        bigCube->setEmissionColor(emissionColor);
//
//        /* TorchLight->setPosition(camera->getPosition());
//         TorchLight->setDirection(camera->getFront());*/
//
//         /*  glm::vec3 lightColor;
//           lightColor.x = sin(glfwGetTime() * 1.0f);
//           lightColor.y = sin(glfwGetTime() * 0.7f);
//           lightColor.z = sin(glfwGetTime() * 0.3f);
//           light->setColor(lightColor);*/
//
//           //light->move(0.2f, RIGHT, engine.getTime());
//        if (win->isKeyPressed(GLFW_KEY_ESCAPE)) {
//            win->close();
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_W)) {
//            //obj->move(5.f, FORWARD, dt);
//            camera->move(10.f, FORWARD, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_A)) {
//            //obj->move(10.f, LEFT, dt);
//            camera->move(10.f, LEFT, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_S)) {
//            //obj->move(10.f, BACKWARD, dt);
//            camera->move(10.f, BACKWARD, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_D)) {
//            //obj->move(10.f, RIGHT, dt);
//            camera->move(10.f, RIGHT, dt);
//        }
//        if (win->isKeyPressed(GLFW_KEY_SPACE)) {
//            //obj->move(10.f, UP, dt);
//            camera->move(10.f, UP, dt);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_UP)) {
//            std::cout << "Emission RATE + :" << emissionRate << std::endl;
//            plane->setEmissionRate(emissionRate += 0.1);
//            bigCube->setEmissionRate(emissionRate += 0.1);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_DOWN)) {
//            std::cout << emissionRate << std::endl;
//            plane->setEmissionRate(emissionRate -= 0.1);
//            bigCube->setEmissionRate(emissionRate -= 0.1);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_R)) {
//            emissionColor.r += 0.1;
//            std::cout << "Emission Color RED +:" << emissionColor.r << std::endl;
//            plane->setEmissionColor(emissionColor);
//            bigCube->setEmissionColor(emissionColor);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_E)) {
//            emissionColor.r -= 0.1;
//            std::cout << "Emission Color RED -:" << emissionColor.r << std::endl;
//            plane->setEmissionColor(emissionColor);
//            bigCube->setEmissionColor(emissionColor);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_G)) {
//            emissionColor.g += 0.1;
//            std::cout << "Emission Color GREEN +:" << emissionColor.g << std::endl;
//            plane->setEmissionColor(emissionColor);
//            bigCube->setEmissionColor(emissionColor);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_F)) {
//            emissionColor.g -= 0.1;
//            std::cout << "Emission Color GREEN -:" << emissionColor.g << std::endl;
//            plane->setEmissionColor(emissionColor);
//            bigCube->setEmissionColor(emissionColor);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_B)) {
//            emissionColor.b += 0.1;
//            std::cout << "Emission Color BLUE +:" << emissionColor.b << std::endl;
//            plane->setEmissionColor(emissionColor);
//            bigCube->setEmissionColor(emissionColor);
//        }
//
//        if (win->isKeyPressed(GLFW_KEY_V)) {
//            emissionColor.b -= 0.1;
//            std::cout << "Emission Color BLUE -:" << emissionColor.b << std::endl;
//            plane->setEmissionColor(emissionColor);
//            bigCube->setEmissionColor(emissionColor);
//        }
//
//
//        //if (win->isKeyPressed(GLFW_KEY_F)) {
//        //    //obj->move(10.f, UP, dt);
//        //    if (TorchLight->getColor() == glm::vec3(0.f))
//        //        TorchLight->setColor(glm::vec3(1.f));
//        //    else if (TorchLight->getColor() == glm::vec3(1.f)) {
//        //        TorchLight->setColor(glm::vec3(0.f));
//        //    }
//        //}
//        if (win->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
//            //obj->move(10.f, DOWN, dt);
//            camera->move(10.f, DOWN, dt);
//        }
//
//        engine.drawObjects();
//    }
//    return 0;
//};