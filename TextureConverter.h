#pragma once
#include <string>
#include <DirectXTex.h>



//�e�N�X�`���R���o�[�^�[
class TextureConverter
{
public:

	void ConverterTextureWICToDDS(const std::string& filePath);

private:

	void LoadWICTextureFromFile(const std::string& filePath);

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

private:

	////�摜�̏��
	//DirectX::TexMetadata matadata_;
	////�摜�C���[�W�̃R���e�i
	//DirectX::ScratchImage scratchImage_;


};

