#include "TextureConverter.h"

using namespace DirectX;


std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//���C�h������
	std::wstring wString;

	wString.resize(filePathBufferSize);

	//���C�h������ɕϊ�
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;

}


void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring exceptExt;

	//��؂蕶��'.'���o�Ă����ԍŌ�̕���������
	pos1 = filePath.rfind('.');
	//�������q�b�g������
	if (pos1 != std::wstring::npos)
	{
		//��؂蕶�������̃t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//��؂蕶���̑O�܂Ŕ����o��
		exceptExt = filePath.substr(0, pos1);
	}
	else
	{
		fileExt_ = L"";
		exceptExt = filePath;
	}

	//��؂蕶��'\\'���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('\\');
	if(pos1 !=std::wstring::npos)
	{
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C���Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//��؂蕶��'/'���o�Ă����ԍŌ�̕���������
	pos1 =exceptExt.rfind('/');
	if (pos1 != std::wstring::npos)
	{
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//��؂蕶���̌����t�@�C���Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	else
	{
		directoryPath_ = L"";
		fileName_ = exceptExt;
	}
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	HRESULT result;

	//�t�@�C���p�X�����C�h������ɕϊ�����
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	//WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &matadata_, scratchImage_);
	assert(SUCCEEDED(result));

	//�t�H���_�p�X�ƃt�@�C�����𕪗�����
	SeparateFilePath(wfilePath);
}

void TextureConverter::SaveDDSTextureToFile()
{
	HRESULT result;

	//�o�̓t�@�C������ݒ肷��
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDS�t�@�C�������o��
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), matadata_,
		DDS_FLAGS_NONE, filePath.c_str());
		assert(SUCCEEDED(result));

	//�ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	matadata_.format = MakeSRGB(matadata_.format);
}

void TextureConverter::ConverterTextureWICToDDS(const std::string& filePath)
{
	//�e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);
	//DDS�`���ɕϊ����ď����o��
	SaveDDSTextureToFile();

}


