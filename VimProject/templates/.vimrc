syntax on
set visualbell
set number
set ruler
set guifont=consolas
set expandtab ts=4 sw=4 ai
"=======================================
set encoding=utf-8
set t_Co=256
" set background=light
colorscheme desert

set smarttab
set autoindent
set smartindent
set cindent

set showmatch
set hlsearch
set incsearch
set autoread

set guioptions-=T
set guioptions-=m

set mouse=a
set showcmd

set nowrap
set whichwrap+=<,>,[,]
set backspace=indent,eol,start
"========================================
func Setup()
    sp core.txt
    silent only!
    silent tabonly!
    silent e C:/Users/afadeev/output.txt
    silent vs source.cpp
    silent execute "normal \<C-w>\<C-w>"
    silent sp C:/Users/afadeev/input.txt
    silent tabnew .vimrc
    silent tabnew CSES.txt
    silent tabnext
    silent execute "normal \<C-w>h"
endfunction

func CompRun()
    let tmp = system("fc /b source.cpp prevcomp.cpp")
    let comp = system("echo %errorlevel%")
    let good = system("echo 0")
    if (comp == good)
        execute("normal !%:r <CR>")
    else
        execute("normal !g++ -D_MY -Wall -Wno-unused-result -std=c++17   -O2   % -o %:r && %:r <CR>")
    endif
endfunction

"=========================================
autocmd filetype py nmap <silent> <F5> <C-w>h:wa <bar> :silent !cls <CR> :!python %:r <CR>
autocmd filetype cpp nmap <silent> <F5> <C-w>h:wa <bar> :silent !cls <CR> :!g++ -D_MY -Wall -Wno-unused-result -std=c++17   -O2   % -o %:r && %:r <CR>
autocmd filetype cpp nmap <silent> <F6> <C-w>h:wa <bar> :silent !cls <CR> :!g++ -D_MY -Wall -Wno-unused-result -std=c++17   -O2   % -o %:r <CR>
autocmd filetype cpp nmap <silent> <F7> <C-w>h:wa <bar> :silent !%:r <CR>
" to do: build-run without terminal
"        show compilation output in terminal
"        auto compile-run

map <silent> <F12> <ESC>:call Setup()<CR>

nmap <C-s> :w<CR>
vmap <C-s> <ESC><C-s>v
imap <expr> <C-s> col('.') == 1 ? "\<ESC>\<C-s>i" : "\<ESC>\<C-s>a"
 
vmap <C-c> "+y

nmap <C-a> ggVG

nmap <C-v> "+gp
vmap <C-v> "+gp
imap <C-v> <esc><C-v>a

nmap <C-z> u
vmap <C-z> <ESC><C-z>v
imap <C-z> <ESC><C-z>a

inoremap ( ()<Left>
inoremap [ []<Left>
inoremap { {}<Left>
inoremap <expr> )  strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")" 
inoremap <expr> ]  strpart(getline('.'), col('.')-1, 1) == "]" ? "\<Right>" : "]" 
inoremap <expr> }  strpart(getline('.'), col('.')-1, 1) == "}" ? "\<Right>" : "}" 

inoremap <expr> <Enter> strpart(getline('.'), col('.')-2, 2) != "{}" ? "\<Enter>" : "\<CR>\<Tab>\<CR>\<Up>\<Right>\<Right>\<Right>\<Right>"

nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
