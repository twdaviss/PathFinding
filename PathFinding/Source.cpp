#include <REngine.h>
#include "Tilemap.h"
REng::Math::Vector2 position;
Texture2D myTexture;
Rectangle rect;
Rectangle source;
float offsetX = 80;
float offsetY = 96;
int frames = 6;
int currentFrame = 0;

float animMaxTime = 0.2f;
float currentTime = 0.0f;

Tilemap myTilemap;
void GameInit() {
	std::string fullPath;
	REng::ResourcesFullPath("hero_spritesheet.png",fullPath);
	rect.x = 0.0f;
	rect.y = offsetY;
	rect.width = offsetX;
	rect.height = offsetY;
	myTexture = LoadTexture(fullPath.c_str());

	myTilemap.LoadTilemap("Tilemap.txt",32);
	myTilemap.LoadTiles("Tiles.txt");
}

bool GameUpdate() {

	myTilemap.Render();

	float moveSpeed = 200.0f;
	if (IsKeyDown(KEY_RIGHT)) {
		position.x += moveSpeed * GetFrameTime();
		currentTime += GetFrameTime();
		if (currentTime > animMaxTime) {
			currentFrame++;
			currentFrame = currentFrame % frames;
			rect.x = currentFrame * offsetX;
			currentTime = 0.0f;
			rect.width = offsetX;
		}
	}
	if (IsKeyDown(KEY_LEFT)) {
		position.x -= moveSpeed * GetFrameTime();
		currentTime += GetFrameTime();
		if (currentTime > animMaxTime) {
			currentFrame++;
			currentFrame = currentFrame % frames;
			rect.x = currentFrame * offsetX;
			currentTime = 0.0f;
			rect.width = -offsetX;
		}
	}
	if (IsKeyDown(KEY_DOWN)) {
		position.y += moveSpeed * GetFrameTime();
	}
	if (IsKeyDown(KEY_UP)) {
		position.y -= moveSpeed * GetFrameTime();

	}

	DrawTextureRec(myTexture, rect, { position.x, position.y }, WHITE);

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_SPACE);
	return isStopped;
}

void GameCleanup() {
	myTilemap.Unload();
}

int main() {

	REng::Start("PathFinding");
	GameInit();
	REng::Run(GameUpdate);
	GameCleanup();
	REng::Stop();
	return 0;
}