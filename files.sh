find . -mindepth 1 \
  -name '.git' -prune -o \
  -name '.gitignore' -prune -o \
  -path "./lib/SimpleLibrary" -prune -o \
  -path "./lib/SimpleLibrary/*" -prune -o \
  -print

