{ pkgs, ... }: {
  languages.cplusplus.enable = true;

  packages = [
    pkgs.valgrind
    pkgs.sdl3
  ];
}
