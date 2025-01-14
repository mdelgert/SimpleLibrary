find . -mindepth 1 \
  -name '.git' -prune -o \
  -name '.gitignore' -prune -o \
  -print

find . -mindepth 1 \
  ! -path './.git' \
  ! -path './.git/*' \
  ! -name '.gitignore' \
  -print
