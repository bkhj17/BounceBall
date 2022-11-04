#include "Game.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::Init()
{
	System_Create(&_system);
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	unsigned int nVersion;
	_system->getVersion(&nVersion);

	if (FMOD_VERSION < nVersion)
		return false;

	return true;
}

void SoundManager::AddSound(string keyName, string soundName, bool bgm, bool loop)
{
	SoundInfo* info = new SoundInfo;

	if (loop)
	{
		if (bgm)
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &info->sound);
		else
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &info->sound);
	}
	else
	{
		if (bgm)
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &info->sound);
		else
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &info->sound);
	}

	totalSound.insert(make_pair(keyName, info));
}

void SoundManager::Play(string keyName, float volume)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		_system->playSound(FMOD_CHANNEL_FREE, (it->second)->sound, false, &(it->second)->channel);
		(it->second)->channel->setVolume(volume);
	}
}

void SoundManager::Stop(string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->stop();
	}
}

void SoundManager::Pause(string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(true);
	}
}

void SoundManager::Resume(string keyName)
{
	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->setPaused(false);
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay = false;

	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->isPlaying(&isPlay);
	}

	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPaused = false;

	it = totalSound.find(keyName);

	if (it != totalSound.end())
	{
		(it->second)->channel->getPaused(&isPaused);
	}

	return isPaused;
}
