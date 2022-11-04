#include "BounceBallHeader.h"
#include "LevelButton.h"
#include "LevelSelect.h"


LevelSelect::LevelSelect() {}
LevelSelect::~LevelSelect() {}

HRESULT LevelSelect::init()
{
	if (_vStage.empty()) {
		vector<string> vStr = EDITER->dirLoad(TEXT("Stage"));
		vector<string>::iterator it_str;

		bool first = true;
		int x = 100;
		int y = 100;
		for (it_str = vStr.begin(); it_str != vStr.end(); it_str++) {
			vLevel.push_back(new LevelButton(it_str->c_str(), first, x, y));
			_vStage.push_back(pair<string, bool>(it_str->c_str(), first));
			x += 180;
			if (x > WINSIZEX - 100) {
				x = 100;
				y += 170;
			}

			first = false;
		}
	}
	else {
		vector<pair<string, bool>>::iterator it_v;

		vector<string> vStr = EDITER->dirLoad(TEXT("Stage"));
		vector<string>::iterator it_str;

		int x = 100;
		int y = 100;
		bool isExist = false;
		for (it_v = _vStage.begin(); it_v != _vStage.end();) {
			isExist = false;
			for (it_str = vStr.begin(); it_str != vStr.end(); it_str++) {
				//������ ���� �����ϴ��� �˻�
				if (_tcscmp(it_v->first.c_str(), it_str->c_str()) == 0) {
					//�����ϸ� ��ư ����
					vLevel.push_back(new LevelButton(it_v->first.c_str(), it_v->second, x, y));
					x += 180;
					if (x > WINSIZEX - 100) {
						x = 100;
						y += 170;
					}
					isExist = true;
					break;
				}
			}

			//������ Ȯ�������� ��������
			if (isExist)	it_v++;
			//������ ���ٸ� ��Ͽ��� ����
			else it_v = _vStage.erase(it_v);
		}
	}

	_tcscpy_s(_fileNow, TEXT(""));

	return S_OK;
}

void LevelSelect::release()
{
	vector<LevelButton*>::iterator it = vLevel.begin();

	for (; it != vLevel.end();) {
		(*it)->release();
		SAFE_DELETE(*it);
		it = vLevel.erase(it);
	}
}

void LevelSelect::update()
{
	vector<LevelButton*>::iterator it = vLevel.begin();
	vector<LevelButton*>::iterator it_end = vLevel.end();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		GetCursorPos(&g_ptMouse);
		ScreenToClient(g_hWnd, &g_ptMouse);

		for (; it != it_end; it++) {
			if ((*it)->isClicked(g_ptMouse)){
				vector<pair<string, bool>>::iterator it_vStg;

				for (it_vStg = _vStage.begin(); it_vStg != _vStage.end(); it_vStg++) {
					if (it_vStg->first == (*it)->getName()) break;
				}

				if (it_vStg == _vStage.end()) continue;

				if (it_vStg->second) {
					SOUNDMANAGER->Play(TEXT("ButtonSound"), DEFAULT_VOLUME);

					_tcscpy_s(_fileNow, (*it)->getName());
					SCENEMANAGER->ChangeScene(TEXT("playGame"));
					return;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_BACK)) {
		SCENEMANAGER->ChangeScene(TEXT("TitleScene"));
	}
}

void LevelSelect::render()
{
	IMAGEMANAGER->render(TEXT("BackGround_game"), getMemDC());

	vector<LevelButton*>::iterator it = vLevel.begin();
	vector<LevelButton*>::iterator it_end = vLevel.end();

	for (; it != it_end; it++) {
		(*it)->render(getMemDC());
	}
}
