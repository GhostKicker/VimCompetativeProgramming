set nocompatible              " be iMproved, required
filetype off                  " required
set lazyredraw
syntax on
set visualbell
set number
set ruler
set guifont=consolas
set et ts=4 sw=4 ai "expandtab tabstop shiftwidth autoindent
set sta si "smarttab smartindent
"=======================================
set encoding=utf-8
set t_Co=256


if teach == 1
    syntax off
    colorscheme shine
endif


set splitright
set splitbelow

set hlsearch
set incsearch
set autoread

set guioptions-=T
set guioptions-=m

set mouse=a
set showcmd

set whichwrap+=<,>,[,]
set backspace=indent,eol,start
"========================================
function! Setup()
    vs $HOME/VimProject/source.cpp
    silent only!
    silent tabonly!
    vs $HOME/VimProject/input.txt
    sp $HOME/VimProject/output.txt
    tabnew $HOME/VimProject/CompileMessage.txt
    tabp
    silent execute "normal \<C-w>h"
endfunction
call Setup()

function! ClearSource()
    silent execute "normal :!cp $HOME/VimProject/templates/core.cpp $HOME/VimProject/source.cpp \<CR>"
    redraw!
endfunction

"======================================


nmap <silent> <F6> <C-w>h:wa <bar> :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -g  % -o %:r 2>&1 \| tee VimProject/CompileMessage.txt && gdb %:r <CR>
imap <silent> <F6> <Esc><F6>
nmap <silent> <F5> <C-w>h:wa <bar> :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -O2 % -o %:r 2>&1 \| tee VimProject/CompileMessage.txt && %:r <CR>
imap <silent> <F5> <Esc><F5>

nmap <C-s> :w<CR>
vmap <C-s> <ESC><C-s>v
imap <expr> <C-s> col('.') == 1 ? "\<ESC>\<C-s>i" : "\<ESC>\<C-s>a"
 
vmap <C-c> "+y

nmap <C-a> ggVG

nmap <C-v> "+gp
vmap <C-v> "+gp
imap <C-v> <esc><C-v>a

nnoremap <C-b> <C-v>

inoremap ( ()<Left>
inoremap [ []<Left>
inoremap { {}<Left>
inoremap <expr> )  strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")" 
inoremap <expr> ]  strpart(getline('.'), col('.')-1, 1) == "]" ? "\<Right>" : "]" 
inoremap <expr> }  strpart(getline('.'), col('.')-1, 1) == "}" ? "\<Right>" : "}" 

inoremap <expr> <Enter> strpart(getline('.'), col('.')-2, 2) != "{}" ? "\<Enter>" : "\<CR>\<Tab>\<CR>\<Up>\<Esc>$a"
