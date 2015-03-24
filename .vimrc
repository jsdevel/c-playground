let foo = expand('%:p:h')
let &path.=",".foo."/src/include,"
let syntastic_c_include_dirs = [ './src/include' ]
let g:syntastic_c_auto_refresh_includes = 1
