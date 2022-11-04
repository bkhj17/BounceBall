#pragma once
class DirLoader
{
	vector<string> vFile;
public:
	DirLoader();
	~DirLoader();

	void load(const TCHAR* dirName);
};

