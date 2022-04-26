ifndef VERBOSE
.SILENT:
endif
LOGIN=xsovam00
SRC=pro.cpp 
HDR=pro.h
TEST-FILE=test.sh
TMPDIR=tmp-prl
TESTSTRING=ABCDEFG

.PHONY:run

test: 
	echo 'bash -e $(TEST-FILE) $(TESTSTRING)'
	bash -e $(TEST-FILE) $(TESTSTRING)

doc: clean $(LOGIN).pdf
	evince $(LOGIN).pdf &

merlin: pack
	ssh merlin "mkdir -p $(TMPDIR)"
	scp $(LOGIN).zip merlin:$(TMPDIR)
	ssh merlin "PATH=$$PATH:/usr/local/share/OpenMPI/bin && cd $(TMPDIR) && unzip -oqq $(LOGIN).zip && echo 'bash -e $(TEST-FILE) $(TESTSTRING)' && bash -e $(TEST-FILE) $(TESTSTRING)"
	ssh merlin "rm -rf $(TMPDIR)"

pack: $(LOGIN).pdf
	zip -r $(LOGIN).zip $(SRC) $(HDR) $(TEST-FILE) $(LOGIN).pdf

$(LOGIN).pdf: $(LOGIN).tex
	pdflatex $(LOGIN).tex
	pdflatex $(LOGIN).tex

clean:
	rm -rf $(LOGIN).pdf *.zip *.aux *.log *.out *.fdb_latexmk *.fls *.synctex.gz