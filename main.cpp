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

	//�e�N�X�`���R�[�h
	TextureConverter converter;

	//�e�N�X�`���ϊ�
	converter.ConverterTextureWICToDDS(argv[kFilePath]);

	//COM ���C�u�����[�̏I��
	CoUninitialize();

	system("pause");
	return 0;
}