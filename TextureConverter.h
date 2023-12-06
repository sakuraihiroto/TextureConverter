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

	void SeparateFilePath(const std::wstring& filePath);

	void SaveDDSTextureToFile();

private:

	//�摜�̏��
	DirectX::TexMetadata metadata_;
	//�摜�C���[�W�̃R���e�i
	DirectX::ScratchImage scratchImage_;

private:

	std::wstring directoryPath_;

	std::wstring fileName_;

	std::wstring fileExt_;


};

