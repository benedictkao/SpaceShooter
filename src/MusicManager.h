#pragma once

#include "SDLWrapper.h"
#include <unordered_map>

class MusicManager {
private:
  typedef std::unordered_map<int, SDL2::Music> MusicMap;
  typedef std::unordered_map<int, SDL2::Sound> SoundMap;

  MusicMap _musicMap;
  SoundMap _soundMap;

public:
  void init();
  void playMusic(int) const;
  void stopPlayingMusic() const;
  void stopSounds() const;

  void playSound(int) const;
  void close();

private:
  void initSound(unsigned int id);
  void initSound(unsigned int id, int volume);
};