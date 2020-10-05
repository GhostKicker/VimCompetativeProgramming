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


syntax on
colorscheme desert
let g:netrw_liststyle = 3

"wildmenu lazyredraw visualbell number ruler expandtab tabstop shiftwidth autoindent smarttab smartindent
set wmnu lz vb nu ru et ts=4 sw=4 ai sta si 
set gfn=consolas "guifont
set encoding=utf-8
set t_Co=256

set spr sb "splitright splitbelow
set hls is ar "hlsearch incsearch autoread

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
    silent execute "normal \<C-w>h\<C-w>k"
endfunction

function! ClearSource()
if has('unix')
    silent !cp $HOME/VimProject/templates/core.cpp $HOME/VimProject/source.cpp
endif
if has('win32')
    silent !copy \%userprofile\%\\VimProject\\templates\\core.cpp \%userprofile\%\\VimProject\\source.cpp
endif
    redraw!
endfunction

"======================================

if has('win32')
    nnoremap <silent> <F6> :wa<CR><C-w>h<C-w>k :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -g  % -o %:r 2> VimProject/CompileMessage.txt && echo SUCCESS && gdb %:r.exe \|\| echo FAIL <CR>
    nnoremap <silent> <F5> :wa<CR><C-w>h<C-w>k :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -O2 % -o %:r 2> VimProject/CompileMessage.txt && echo SUCCESS && %:r.exe \|\| echo FAIL <CR>
endif
if has('unix')
    nnoremap <silent> <F6> :wa<CR><C-w>h<C-w>k :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -g  % -o %:r 2> VimProject/CompileMessage.txt && echo SUCCESS && gdb %:r \|\| echo FAIL <CR>
    nnoremap <silent> <F5> :wa<CR><C-w>h<C-w>k :!g++ -D_MY -Wall -Wno-unused-result -std=c++17 -O2 % -o %:r 2> VimProject/CompileMessage.txt && echo SUCCESS && %:r \|\| echo FAIL <CR>
endif
 
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

"-----ONLY--LOCAL------
let teach = 0
if teach == 1
    syntax off
    colorscheme shine
endif


"----------LATEX----------

let g:tex_flavor = 'latex'
let g:vimtex_view_general_viewer = 'SumatraPDF'
let g:vimtex_view_general_options
    \ = '-reuse-instance -forward-search @tex @line @pdf'
let g:vimtex_view_general_options_latexmk = '-reuse-instance'
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
