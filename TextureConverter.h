#pragma once
#include <string>
#include <DirectXTex.h>



//テクスチャコンバーター
class TextureConverter
{
public:

	void ConverterTextureWICToDDS(const std::string& filePath);

private:

	void LoadWICTextureFromFile(const std::string& filePath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

private:

	////画像の情報
	//DirectX::TexMetadata matadata_;
	////画像イメージのコンテナ
	//DirectX::ScratchImage scratchImage_;


};

