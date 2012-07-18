" .vimrc
" based on https://wiki.archlinux.org/index.php/Vim/.vimrc
" Joseph Walton-Rivers <webpigeon@gmail.com>

" Tab settings
set tabstop=4
set shiftwidth=4
set expandtab
set smarttab

" Text formatting
set textwidth=79

set number " Show line numbers

" backup files in ~/vim/backup rather than current directory
set backupdir=~/.vim/backup,/tmp

" Spelling options
autocmd FileType tex setlocal spell spelllang=en_gb

" File syntax highlight
filetype plugin on
syntax on
