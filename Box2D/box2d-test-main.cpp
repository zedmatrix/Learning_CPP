#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <GL/glew.h>
#include <iostream>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr float PIXELS_PER_METER = 100.0f;

void drawBox(const b2Body* body) {
    auto pos = body->GetPosition();
    auto angle = body->GetAngle();

    glPushMatrix();
    glTranslatef(pos.x * PIXELS_PER_METER, SCREEN_HEIGHT - pos.y * PIXELS_PER_METER, 0);
    glRotatef(angle * 180.0f / 3.14159f, 0, 0, 1);

    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.6f, 0.9f);
    glVertex2f(-50, -25);
    glVertex2f( 50, -25);
    glVertex2f( 50,  25);
    glVertex2f(-50,  25);
    glEnd();

    glPopMatrix();
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Box2D Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext gl_ctx = SDL_GL_CreateContext(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed\n";
        return -1;
    }


    // Setup Box2D world
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    // Ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(4.0f, 1.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(4.0f, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Falling box
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(4.0f, 10.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.25f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        world.Step(1.0f / 60.0f, 6, 2);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        drawBox(body);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_GL_DeleteContext(gl_ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
