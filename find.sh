echo "Removing everything else..."
find . -mindepth 1 \
  ! -name '.git' \
  ! -name '.gitignore' \
-print