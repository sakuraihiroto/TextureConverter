#include "TextureConverter.h"

using namespace DirectX;


std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//ワイド文字列
	std::wstring wString;

	wString.resize(filePathBufferSize);

	//ワイド文字列に変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;

}


void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring exceptExt;

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = filePath.rfind('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos)
	{
		//区切り文字を後ろのファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前まで抜き出す
		exceptExt = filePath.substr(0, pos1);
	}
	else
	{
		fileExt_ = L"";
		exceptExt = filePath;
	}

	//区切り文字'\\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	if(pos1 !=std::wstring::npos)
	{
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイルとして保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字'/'が出てくる一番最後の文字を検索
	pos1 =exceptExt.rfind('/');
	if (pos1 != std::wstring::npos)
	{
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイルとして保存
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

	//ファイルパスをワイド文字列に変換する
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	//WICテクスチャのロード
	result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &matadata_, scratchImage_);
	assert(SUCCEEDED(result));

	//フォルダパスとファイル名を分離する
	SeparateFilePath(wfilePath);
}

void TextureConverter::SaveDDSTextureToFile()
{
	HRESULT result;

	//出力ファイル名を設定する
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDSファイル書き出し
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), matadata_,
		DDS_FLAGS_NONE, filePath.c_str());
		assert(SUCCEEDED(result));

	//読み込んだテクスチャをSRGBとして扱う
	matadata_.format = MakeSRGB(matadata_.format);
}

void TextureConverter::ConverterTextureWICToDDS(const std::string& filePath)
{
	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);
	//DDS形式に変換して書き出す
	SaveDDSTextureToFile();

}


