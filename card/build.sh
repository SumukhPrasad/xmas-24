has_param() {
	local term="$1"
	shift
	for arg; do
		if [[ $arg == "$term" ]]; then
			return 0
		fi
	done
	return 1
}

echo "\033[1mCompiling with XeLaTeX...\033[0m"
xelatex --file-line-error --synctex=1 "card.tex"
echo
echo "\033[1mRecompiling...\033[0m"
xelatex --file-line-error --synctex=1 "card.tex"
echo

if has_param '-removeaux' "$@"; then
	echo "\033[1mRemoving AUX files...\033[0m"
	rm card.aux
	rm card.log 
	rm card.synctex.gz
	echo
fi

open ./card.pdf

echo "\033[1mDone.\033[0m"
