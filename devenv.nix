{ pkgs, ... }: {
  languages.cplusplus.enable = true;

  packages = with pkgs; [
    valgrind
    sdl3
    catch2_3
  ];
}
