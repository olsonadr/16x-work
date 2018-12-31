source $VIMRUNTIME/defaults.vim

"Vundle Stuff"
set nocompatible
filetype off 
set rtp+=~/.vim/bundle/Vundle.vim


call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'drewtempelmeyer/palenight.vim'
Plugin '~/.fzf'
Plugin 'itchyny/lightline.vim'
Plugin 'junegunn/fzf.vim'

call vundle#end()


filetype plugin indent on
let g:ycm_server_keep_logfiles = 1
let g:ycm_server_log_level = 'debug'
"End Vundle Stuff"


call plug#begin('~/.vim/plugged')
call plug#end()

set autoindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set mouse=a
syntax on
set background=dark
set number
colorscheme palenight
let g:palenight_terminal_italics=1

if (has("nvim"))
  "For Neovim 0.1.3 and 0.1.4 < https://github.com/neovim/neovim/pull/2198 >
  let $NVIM_TUI_ENABLE_TRUE_COLOR=1
endif

"For Neovim > 0.1.5 and Vim > patch 7.4.1799 < https://github.com/vim/vim/commit/61be73bb0f965a895bfb064ea3e55476ac175162 >
"Based on Vim patch 7.4.1770 (`guicolors` option) < https://github.com/vim/vim/commit/8a633e3427b47286869aa4b96f2bfc1fe65b25cd >
" < https://github.com/neovim/neovim/wiki/Following-HEAD#20160511 >
if (has("termguicolors"))
  set termguicolors
endif

map <C-o> :NERDTreeToggle<CR>

execute pathogen#infect()
call pathogen#helptags()
