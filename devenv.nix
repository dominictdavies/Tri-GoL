{ pkgs, ... }: {
  languages.cplusplus.enable = true;

  packages = [
    pkgs.SDL2
  ];
}
