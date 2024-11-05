#include <graphics.h>
#include <cmath>
#include <thread>
#include <chrono>

const int WIDTH = 800;
const int HEIGHT = 600;
const float SUN_X = WIDTH / 2.0f;
const float SUN_Y = HEIGHT / 2.0f - 50; // Elevate the Sun by 50 pixels

// Orbital parameters for planets (semi-major axis, semi-minor axis, speed)
const float SEMI_MAJOR_AXIS[] = {60.0f, 90.0f, 120.0f, 150.0f, 180.0f, 210.0f, 240.0f, 270.0f};
const float SEMI_MINOR_AXIS[] = {40.0f, 70.0f, 100.0f, 130.0f, 160.0f, 190.0f, 220.0f, 250.0f};

// Increased speeds for each planet
const float SPEED[] = {0.4f, 0.32f, 0.24f, 0.2f, 0.16f, 0.12f, 0.08f, 0.04f}; 
const int NUM_PLANETS = 8;

// Colors for each planet
const int PLANET_COLORS[] = {BLUE, GREEN, RED, CYAN, MAGENTA, YELLOW, WHITE, LIGHTGRAY};

void drawEllipses() {
    // Draw static elliptical orbits
    for (int i = 0; i < NUM_PLANETS; ++i) {
        setcolor(LIGHTGRAY); // Orbit color
        for (float theta = 0; theta < 2 * M_PI; theta += 0.01) {
            int orbitX = static_cast<int>(SUN_X + SEMI_MAJOR_AXIS[i] * cos(theta));
            int orbitY = static_cast<int>(SUN_Y + SEMI_MINOR_AXIS[i] * sin(theta));
            putpixel(orbitX, orbitY, LIGHTGRAY); // Draw orbit points
        }
    }
}

void drawSun() {
    setcolor(YELLOW);
    circle(SUN_X, SUN_Y, 25); // Draw Sun
    floodfill(SUN_X, SUN_Y, YELLOW); // Fill Sun
}

void drawPlanet(int planetIndex, float angle) {
    // Calculate planet position using elliptical orbits
    int planetX = static_cast<int>(SUN_X + SEMI_MAJOR_AXIS[planetIndex] * cos(angle));
    int planetY = static_cast<int>(SUN_Y + SEMI_MINOR_AXIS[planetIndex] * sin(angle));

    // Draw the planet
    setcolor(PLANET_COLORS[planetIndex]); // Change color for each planet
    circle(planetX, planetY, 10); // Draw planet
    floodfill(planetX, planetY, PLANET_COLORS[planetIndex]); // Fill planet
}

void erasePlanet(int planetIndex, float angle) {
    // Calculate previous planet position using elliptical orbits
    int planetX = static_cast<int>(SUN_X + SEMI_MAJOR_AXIS[planetIndex] * cos(angle));
    int planetY = static_cast<int>(SUN_Y + SEMI_MINOR_AXIS[planetIndex] * sin(angle));

    // Erase the planet by redrawing its last position with background color
    setcolor(BLACK);
    circle(planetX, planetY, 10); // Draw "over" the planet
    floodfill(planetX, planetY, BLACK); // Fill "over" the planet
}

int main() {
    // Initialize the graphics system
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // Specify the path to BGI files if needed

    // Draw static ellipses and the Sun once
    drawEllipses();
    drawSun();

    float angles[NUM_PLANETS] = {0.0f}; // Initial angles for each planet

    while (true) {
        // Loop through each planet
        for (int i = 0; i < NUM_PLANETS; ++i) {
            // Erase the previous position of the planet
            erasePlanet(i, angles[i]); 
            
            // Update angle for rotation
            angles[i] += SPEED[i]; 
            // Ensure angles wrap around
            if (angles[i] > 2 * M_PI) angles[i] -= 2 * M_PI; 
            
            // Draw the planet at the new position
            drawPlanet(i, angles[i]); 
        }

        // Pause for a bit to control the speed of the animation
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Adjust as necessary
    }

    // Close the graphics system (this won't be reached in this infinite loop)
    closegraph();
    return 0;
}

