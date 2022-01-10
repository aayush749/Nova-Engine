#pragma once
#include "Texture.h"
class Texture2D : public Texture
{
public:
	Texture2D(const std::string& imgPath, int nDesiredChannels = 3, bool filpOnLoad = true, bool generateMipMaps = false);
	void BindTexture(GLushort slot = 0) override;
	void UnbindTexture() override;
};


