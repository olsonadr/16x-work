let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/cs/cs162/labs/lab-7-olsonadr
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
$argadd debugging-1.cpp
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabrewind
edit debugging-1.txt
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 101 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 101 + 101) / 203)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 6 - ((5 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 042|
wincmd w
argglobal
if bufexists("debugging-1.cpp") | buffer debugging-1.cpp | else | edit debugging-1.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 21 - ((20 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
21
normal! 021|
wincmd w
exe 'vert 1resize ' . ((&columns * 101 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 101 + 101) / 203)
tabnext
edit debugging-2.txt
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 101 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 101 + 101) / 203)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 5 - ((4 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
5
normal! 012|
wincmd w
argglobal
if bufexists("debugging-2.cpp") | buffer debugging-2.cpp | else | edit debugging-2.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 52 - ((47 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
52
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 101 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 101 + 101) / 203)
tabnext
edit debugging-3.txt
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 101 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 101 + 101) / 203)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 21 - ((20 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
21
normal! 0161|
wincmd w
argglobal
if bufexists("debugging-3.cpp") | buffer debugging-3.cpp | else | edit debugging-3.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 61 - ((9 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
61
normal! 048|
wincmd w
exe 'vert 1resize ' . ((&columns * 101 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 101 + 101) / 203)
tabnext
edit data.tsv
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 8 - ((7 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 034|
tabnext
edit dynarray.hpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 87 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 115 + 101) / 203)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 17 - ((16 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
17
normal! 025|
wincmd w
argglobal
if bufexists("dynarray.cpp") | buffer dynarray.cpp | else | edit dynarray.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 38 - ((32 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
38
normal! 014|
wincmd w
exe 'vert 1resize ' . ((&columns * 87 + 101) / 203)
exe 'vert 2resize ' . ((&columns * 115 + 101) / 203)
tabnext
edit debugging-demo.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabnext
edit Makefile
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabnext
edit README.md
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabnext 3
badd +1 debugging-1.cpp
badd +1 Makefile
badd +1 README.md
badd +1 data.tsv
badd +1 debugging-2.cpp
badd +1 debugging-3.cpp
badd +1 debugging-demo.cpp
badd +1 dynarray.cpp
badd +17 dynarray.hpp
badd +6 debugging-1.txt
badd +5 debugging-2.txt
badd +21 debugging-3.txt
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOIc
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
