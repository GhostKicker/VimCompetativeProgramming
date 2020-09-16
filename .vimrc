set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'lervag/vimtex'
call vundle#end()            " required
filetype plugin indent on    " required

" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
" see :h vundle for more details or wiki for FAQ

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

colorscheme desert

let teach = 0
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

function! ClearSource()
    silent execute "normal :!cp $HOME/VimProject/templates/core.cpp $HOME/VimProject/source.cpp \<CR>"
    redraw!
endfunction

func SpellCheckRu()
    set spell spelllang=ru
endfunction

func SpellCheckEng()
    set spell spelllang=en
endfunction

func OpenLatex(name)
    echo "$HOME/VimLatex/".a:name."/".a:name.".tex"
    execute "normal :o $HOME/VimLatex/".a:name."/".a:name.".tex"
    if filereadable("$HOME/VimLatex/".a:name."/".a:name.".tex")
        silent execute "normal :e $HOME/VimLatex/".a:name."/".a:name.".tex"
    else
        echo a:name." does not exist"
    endif
endfunction 

func CreateLatex(name)
    silent execute "normal :!mkdir ~/VimLatex/".a:name."\<CR>"
    silent execute "normal :!touch ~/VimLatex/".a:name."/".a:name.".tex\<CR>"
    call OpenLatex(a:name)
endfunction
"======================================


autocmd filetype cpp nnoremap <silent> <F6> <C-w>h:wa <bar> :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -g  % -o %:r 2>&1 \| tee VimProject/CompileMessage.txt && gdb %:r <CR>
autocmd filetype cpp nnoremap <silent> <F5> <C-w>h:wa <bar> :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -O2 % -o %:r 2>&1 \| tee VimProject/CompileMessage.txt && %:r <CR>
autocmd filetype py nnoremap <silent> <F5> <C-w>h:wa <bar> :!python3 %<CR>
 
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

set langmap=ФИСВУАПРШОЛДЬТЩЗЙКЫЕГМЦЧНЯ;ABCDEFGHIJKLMNOPQRSTUVWXYZ,фисвуапршолдьтщзйкыегмцчня;abcdefghijklmnopqrstuvwxyz
autocmd filetype tex nnoremap j gj
autocmd filetype tex nnoremap k gk
autocmd filetype tex vnoremap j gj
autocmd filetype tex vnoremap k gk
autocmd filetype tex nnoremap о gj
autocmd filetype tex nnoremap л gk
autocmd filetype tex vnoremap о gj
autocmd filetype tex vnoremap л gk
autocmd filetype tex vnoremap <Up> g<Up>
autocmd filetype tex vnoremap <Down> g<Down>
autocmd filetype tex nnoremap <Up> g<Up>
autocmd filetype tex nnoremap <Down> g<Down> 


