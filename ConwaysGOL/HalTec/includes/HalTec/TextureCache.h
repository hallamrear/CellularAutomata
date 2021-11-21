#pragma once
#include <unordered_map>

struct SDL_Texture;

class Texture;

class TextureCache
{
private:
	TextureCache() = default;

	static TextureCache* mInstance;
	std::unordered_map<std::string, Texture*> mTextures;

	Texture* GetTexture_Internal(const std::string& texture_path);

public:
	static TextureCache* Get();
	static Texture* GetTexture(const std::string& texture_path);

	~TextureCache();
};

