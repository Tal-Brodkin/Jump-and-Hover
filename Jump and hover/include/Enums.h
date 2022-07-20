#pragma once
#include "box2d/box2d.h"
#include <string>

// Screen size
const int Width = 512;
const int Height = 416;

// Frame rate
const int Frames = 60;

// Game's name
const std::string JumpAndHover = "Jump & Hover";

// Theme color
const sf::Color ThemeColor = sf::Color(0, 171, 255, 255);

// World's gravity
const b2Vec2 Gravity = { 0.f, 50.f };

// Animation Speed
const float SwitchTime = 0.036f;

// Convert between pixel and real-world coordinates
static const float Scale = 30.f;

// Hover bar duration
static const float HoverTime = 0.7f;

// Player's move speed
const float Speed = 300.f;

// Player's jump force
const float Force = 1000.f;

// Player's friction decrease
const float PlayerFrictionDecrease = 0.7f;

// Platform's friction decrease
const float PlatformFrictionDecrease = 0.94f;

// Number of levels
const int NumberOfLevels = 8;

// The amount of time before platform falls down
const float FallDownDelay = 0.4f;

// Key status
const bool Pressed = true;
const bool UnPressed = false;

// Levels
const int FirstLevel = 0;
const int LastLevel = 7;

// Menu buttons names
const std::string StartButton = "START";
const std::string MusicButton = "MUSIC";
const std::string ExitButton = "EXIT";
const std::string LockedLevel = "X";

// Files names
const std::string BackgroundFile	= "background.txt";
const std::string TexturesList		= "textures_list.txt";
const std::string SoundsList		= "sounds_list.txt";
const std::string FontsList			= "fonts_list.txt";
const std::string LogFile			= "log.txt";

// Exeptions
const std::string UnknownError			= "Unknown error occurred";
const std::string TexturesFileProblem	= "Could not open textures list";
const std::string SoundsFileProblem		= "Could not open sounds list";
const std::string FontsFileProblem		= "Could not open fonts list";
const std::string LogFileProblem		= "Could not open log file";
const std::string LevelFileProblem		= "Could not open level file";
const std::string PlayerObjectMissing	= "Player object missing";
const std::string CouldNotLoad			= "Could not load ";

// Textures names
enum Textures
{
	PlayerTexture,
	HoverBarTexture,
	WallTexture,
	GroundTexture,
	PlatformTexture,
	MovingPlatformTexture,
	SpikesTexture,
	AppleTetxture,
	ExitTexture,
	ExitAchievedTexture,
	BackgroundTexture,
	FalingPlatformTexture,
	FalingPlatformOffTexture
};

// Sounds names
enum Sounds
{
	BackgroundMusic,
	PlayerJumpSound,
	PlayerDeadSound,
	PlayerDead2Sound,
	MenuClickSound,
	MenuClick2Sound,
	LevelWonSound,
	LevelWon2Sound,
	TakeBoostSound,
	ErrorSelectSound
};

// Objects names
enum Objects
{
	PlayerObject			= '@',
	PlatformObject			= 'P',
	MovingPlatformObject	= 'M',
	FallingPlatformObject	= 'F',
	SpikesObject			= 'S',
	WallObject				= 'W',
	GroundObject			= 'G',
	BoostHoverObject		= 'B',
	ExitObject				= 'X',
	EmptyObject				= ' '
};

// Animation type
enum AnimationType
{
	Idle,
	MoveLeft,
	MoveRight,
	Jump,
	Fall
};

enum class Orientation
{
	Normal		= 1,
	Reverse		= -1
};

// Menu select direction
enum Dir
{
	Back	= -1,
	Forward = 1
};