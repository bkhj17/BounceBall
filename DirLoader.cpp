#include "Game.h"
#include "DirLoader.h"
#include "io.h"

DirLoader::DirLoader()
{
}


DirLoader::~DirLoader()
{
}

void DirLoader::load(const TCHAR * dirName)
{
	vFile.clear();

	_finddata_t fd;
	long handle;
	int result = 1;

	TCHAR str[128] = { 0, };

	_stprintf_s(str, _countof(str), TEXT("%s\\*.*"), dirName);
	
	handle = _findfirst(str, &fd);  //���� ���� �� ��� ������ ã�´�.

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		vFile.push_back(fd.name);
		printf("File: %s\n", fd.name);
		result = _findnext(handle, &fd);
	}
}
