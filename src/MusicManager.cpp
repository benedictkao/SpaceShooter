#include "MusicManager.h"
#include "ResId.h"

static constexpr auto MUSIC_VOLUME{ 32 };
static constexpr auto DEFAULT_SOUND_VOLUME{ 32 };
static constexpr auto START_SOUND_VOLUME{ 128 };
static constexpr auto BG_MUSIC_PATH{ "../../../res/audio/cruising.mp3" };

void MusicManager::init() {
  _musicMap[MusicId::LOAD] = SDL2::loadMusic(BG_MUSIC_PATH);
  SDL2::setMusicVolume(MUSIC_VOLUME);

  initSound(SoundId::START, START_SOUND_VOLUME);
  initSound(SoundId::VICTORY, START_SOUND_VOLUME);
  initSound(SoundId::FAIL);
  initSound(SoundId::EXPLODE);
  initSound(SoundId::PLAYER_DAMAGE);
  initSound(SoundId::SMALL_SHOT);
  initSound(SoundId::FIREBALL);
}

void MusicManager::playMusic(int id) const {
  SDL2::Music music = _musicMap.find(id)->second;
  SDL2::playMusic(music);
}

void MusicManager::stopPlayingMusic() const {
  SDL2::stopMusic();
}

void MusicManager::stopSounds() const {
  SDL2::stopSounds();
}

void MusicManager::playSound(int id) const {
  SDL2::Sound sound = _soundMap.find(id)->second;
  SDL2::playSound(sound);
}

void MusicManager::close() {
  for (auto& it : _musicMap)
    SDL2::freeMusic(it.second);
  for (auto& it : _soundMap)
    SDL2::freeSound(it.second);
}

void MusicManager::initSound(unsigned int id) {
  SDL2::Sound sound = SDL2::loadSound(SoundId::getPath(id));
  SDL2::setSoundVolume(sound, DEFAULT_SOUND_VOLUME);
  _soundMap[id] = sound;
}

void MusicManager::initSound(unsigned int id, int volume) {
  SDL2::Sound sound = SDL2::loadSound(SoundId::getPath(id));
  SDL2::setSoundVolume(sound, volume);
  _soundMap[id] = sound;
}
