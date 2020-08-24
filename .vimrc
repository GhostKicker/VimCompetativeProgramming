set lazyredraw
syntax on
set visualbell
set number
set ruler
set guifont=consolas
set expandtab ts=4 sw=4 ai
"=======================================
set encoding=utf-8
set t_Co=256

colorscheme desert

let teach = 0


set splitright
set splitbelow

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

set whichwrap+=<,>,[,]
set backspace=indent,eol,start

nmap <C-s> :w<CR>
vmap <C-s> <ESC><C-s>v
imap <expr> <A-s> col('.') == 1 ? "\<ESC><C-s>\<CR>i" : "\<ESC><C-s>\<CR>a"
 
vnoremap <C-c> "+y

nmap <C-a> ggVG

nmap <C-v> "+gp
vmap <C-v> "+gp
imap <C-v> <esc><C-v>a

nnoremap <C-b> <C-v>

nmap <C-z> u
vmap <C-z> <ESC><C-z>v
imap <C-z> <ESC><C-z>a

func SetupCProg()
    source $HOME/VimProject/_vimrc_local.vim
endf

func SetupLatex()
    source $HOME/VimLatex/_vimrc_local.vim
endf

func SetupPython()
    source $HOME/VimPython/_vimrc_local.vim
endf

function GoBack()
    silent tabnew
    silent tabonly!
    source $HOME/.vimrc
endfunction

nmap <F5> :call SetupCProg()<CR>
nmap <F6> :call SetupLatex()<CR>
nmap <F7> :call SetupPython()<CR>
nmap <F11> :call GoBack()<CR>

