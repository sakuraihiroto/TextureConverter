#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"


enum Argument {
	kApplicationPath,
	kFilePath,

	NumArgument
};


int main(int argc, char* argv[])
{
	
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコード
	TextureConverter converter;

	//テクスチャ変換
	converter.ConverterTextureWICToDDS(argv[kFilePath]);

	//COM ライブラリーの終了
	CoUninitialize();

	system("pause");
	return 0;
}