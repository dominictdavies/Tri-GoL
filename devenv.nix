{ pkgs, ... }: {
  languages.cplusplus.enable = true;

  packages = [
    pkgs.valgrind
    pkgs.SDL2
  ];
}
