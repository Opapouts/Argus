#include "vendor/raylib/src/raylib.h"
#include "includes/graphics_engine.h"

int  main(void)
{
	InitWindow(800, 450, "Aerosphere - Radar Active");
	SetTargetFPS(60);
// 1. Setup the Camera (Before the while loop)
	Camera3D camera = { 0 };
	camera.position = (Vector3){ 0.0f, 0.0f, 10.0f }; // Camera is pulled back 10 units
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    // Looking at the center
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Mesh		earthMesh = GenMeshSphere(4.0f, 32, 32);
	Model		earthModel = LoadModelFromMesh(earthMesh);
	Texture2D	earthTexture = LoadTexture("src/graphics_engine/assets/2k_earth.png");
	earthModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = earthTexture;

// 2. Inside your while(!WindowShouldClose()) loop:
	while (!WindowShouldClose())
	{
		update_camera(&camera);
		BeginDrawing();
		ClearBackground(BLACK); // Space is black!

    // 3. Switch from 2D mode to 3D mode
		BeginMode3D(camera);
    
        // Draw a basic wireframe globe
		DrawModel(earthModel, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE);

        // (Phase 3 & 4: Here is where we will loop your planes and draw them in 3D!)

		EndMode3D(); // Switch back to 2D for text/UI

		DrawText("Live 3D Global Radar", 20, 20, 20, LIGHTGRAY);
		EndDrawing();
	}
	UnloadTexture(earthTexture);
	UnloadModel(earthModel);
	CloseWindow();
	return (0);
}
