#pragma once

UENUM( BlueprintType )
enum class ESnakeDirection : uint8
{
	Up,
	Down,
	Left,
	Right,
	None = 255
};

constexpr float TileSize = 100.f;
